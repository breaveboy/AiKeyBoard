#include "App_key.h"
#include "App_protocol.h"
#include "App_lighting.h"
#include "lib_hall_sensor.h"
#include "lib_ws2812.h"
#include "usbd_core.h"
#include <string.h>

// USB 键盘报告脏标志：按键状态变化后置位。
bool report_dirty = false;
uint8_t last_key_state[ROW_COUNT][COL_COUNT] = {0};
uint8_t last_fn_state[ROW_COUNT][COL_COUNT] = {0};

// 普通层键位表：只描述键位到 HID keycode 的映射。
const uint8_t g_key_map[ROW_COUNT][COL_COUNT] = {
    {0x29, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2D, 0x2E, 0x2A},
    {0x2B, 0x14, 0x1A, 0x08, 0x15, 0x17, 0x1C, 0x18, 0x0C, 0x12, 0x13, 0x2F, 0x30, 0x31},
    {0x39, 0x04, 0x16, 0x07, 0x09, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x33, 0x34, KEY_NONE, 0x28},
    {0xE1, 0x00, 0x1D, 0x1B, 0x06, 0x19, 0x05, 0x11, 0x10, 0x36, 0x37, 0x38, KEY_NONE, 0xE5},
    {0xE0, 0xE3, 0xE2, KEY_NONE, KEY_NONE, KEY_NONE, 0x2C, KEY_NONE, KEY_NONE, KEY_NONE, 0xE6, 0x65, 0xE4, KEY_FN}
};

// Fn 层键位表：KEY_LIGHT / KEY_AI_* 这类 0xF0 以上键值只在固件内部处理。
const uint8_t g_fn_key_map[ROW_COUNT][COL_COUNT] = {
    {0x35, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x4C},
    {KEY_NONE, KEY_NONE, 0x52, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
    {KEY_NONE, 0x50, 0x51, 0x4F, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
    {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
    {KEY_NONE, KEY_NONE, KEY_LIGHT, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_AI_TRIGGER, KEY_AI_CONFIRM, KEY_FN}
};

extern bool g_led_dirty;
extern LightMode_t g_light_mode;
extern uint32_t ws2812_tick;

// 处理 Fn 组合内部功能键，如 Fn+Alt 切换灯光、AI 触发键上报。
static void App_process_internal_keys(void);
// 自定义 HID 冒泡上报，用于主动通知上位机 AI 按键事件。
void App_send_bubble_report(uint8_t bubble_param, uint8_t ai_action);

// 动态基准追踪：仅在按键未按下且偏差很小时缓慢修正 idle_adc。
static void update_baseline_tracking(Key_t *k, uint16_t cur_adc)
{
    if (k->is_pressed) {
        k->drift_cnt = 0;
        return;
    }   

    int32_t diff = (int32_t)k->idele_adc - (int32_t)cur_adc;

    if (diff < 30 && diff > -30) {
        k->drift_cnt++;
        if (k->drift_cnt > 1000) {
            if (diff > 0) {
                k->idele_adc--;
            } else if (diff < 0) {
                k->idele_adc++;
            }
            k->drift_cnt = 0;
        }
    } else {
        k->drift_cnt = 0;
    }
}

// AP/RT 判断：根据整帧 ADC 中的当前值更新单键按下状态。
static uint8_t process_key_logic(Key_t *k, uint16_t cur_adc)
{
    int32_t diff = (int32_t)k->idele_adc - (int32_t)cur_adc;
    int16_t offset = (diff > 0) ? (int16_t)diff : 0;

    if (offset < k->top_deadzone) {
        k->is_pressed = 0;
        k->in_rt_cycle = 0;
        k->max_offset = 0;
        k->min_offset = 0;
        return 0;
    }

    if (offset > k->bottom_deadzone) {
        offset = k->bottom_deadzone;
    }

    if (!k->is_pressed) {
        if (offset < k->min_offset) {
            k->min_offset = offset;
        }

        uint16_t trigger_line = k->in_rt_cycle ? (k->min_offset + k->rt_press_sens) : k->actuation_point;
        if (offset >= trigger_line) {
            k->is_pressed = 1;
            k->in_rt_cycle = 1;
            k->max_offset = offset;
        }
    } else {
        if (offset > k->max_offset) {
            k->max_offset = offset;
        }

        uint16_t release_line = k->max_offset - k->rt_release_sens;
        if (offset <= release_line) {
            k->is_pressed = 0;
            k->min_offset = offset;
        }
    }

    return k->is_pressed;
}

// 按键判断任务：只在一整帧 5x14 ADC 数据采满后执行。
void App_adkey_scan_task(void)
{
    if (!g_scan_complete) {
        return;
    }

    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {
            if (key_mask[r][c] == 0) {
                continue;
            }

            Key_t *k = &keys[r][c];
            // 按键判断只使用采集层提供的整帧滤波结果。
            uint16_t adc = g_hall_adc_frame[r][c];

            update_baseline_tracking(k, adc);
            process_key_logic(k, adc);

            if (k->is_pressed != last_key_state[r][c]) {
                last_key_state[r][c] = k->is_pressed;
                report_dirty = true;
            }
        }
    }

    // 内部功能键不依赖 USB 键盘端点，避免 0x81 忙时影响灯光切换。
    App_process_internal_keys();
    lib_hall_sensor_release_frame();
}

// 处理 Fn 组合内部功能键，如 Fn+Alt 切换灯光、AI 触发键上报。
static void App_process_internal_keys(void)
{
    bool fn_pressed = false;

    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {
            if (key_mask[r][c] == 0) {
                continue;
            }

            if (keys[r][c].is_pressed && g_key_map[r][c] == KEY_FN) {
                fn_pressed = true;
                break;
            }
        }
    }

    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {
            if (key_mask[r][c] == 0 || !keys[r][c].is_pressed) {
                last_fn_state[r][c] = 0;
                continue;
            }

            uint8_t code = fn_pressed ? g_fn_key_map[r][c] : g_key_map[r][c];
            if (code == KEY_NONE) {
                code = g_key_map[r][c];
            }

            if (code >= 0xF0 && code != KEY_FN) {
                if (last_fn_state[r][c] == 0) {
                    App_handle_internal_key(code);
                    last_fn_state[r][c] = 1;
                }
            }
        }
    }
}

// 内部功能键分发入口：这些键不会作为普通键盘 HID 发给 PC。
void App_handle_internal_key(uint8_t code)
{
    if (code == KEY_LIGHT) {
        g_light_mode = (LightMode_t)((g_light_mode + 1) % LIGHT_MODE_MAX);
        ws2812_tick = 0;
        lib_ws2812_set_all(0, 0, 0);
        g_led_dirty = true;
    } else if (code == KEY_AI_TRIGGER) {
        App_send_bubble_report(BPARAM_AI_KEY_TRIG, AI_ACT_TRIGGER);
    } else if (code == KEY_AI_CONFIRM) {
        App_send_bubble_report(BPARAM_AI_KEY_TRIG, AI_ACT_CONFIRM);
    } else if (code == KEY_AI_CANCEL) {
        App_send_bubble_report(BPARAM_AI_KEY_TRIG, AI_ACT_CANCEL);
    }
}

// 自定义 HID 冒泡上报，用于主动通知上位机 AI 按键事件。
void App_send_bubble_report(uint8_t bubble_param, uint8_t ai_action)
{
    static Packet_t bubble_pkt;

    memset(&bubble_pkt, 0, sizeof(Packet_t));

    bubble_pkt.report_id  = PROTOCOL_REPORT_ID;
    bubble_pkt.cmd_id     = CMD_BUBBLE_RPT;
    bubble_pkt.cmd_param  = bubble_param;
    bubble_pkt.reserved   = 0;
    bubble_pkt.total_pkts = 1;
    bubble_pkt.cur_pkt    = 1;
    bubble_pkt.data_len   = 2;

    bubble_pkt.payload[0] = ai_action;
    bubble_pkt.payload[1] = 0x00;

    bubble_pkt.crc = App_protocol_sum((uint8_t *)&bubble_pkt);

    usbd_ep_start_write(PROTOCOL_PKT_ACK_EP, (uint8_t *)&bubble_pkt, PROTOCOL_PKT_SIZE);
}
