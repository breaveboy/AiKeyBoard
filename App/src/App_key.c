#include "App_key.h"
#include "App_protocol.h"
#include "App_lighting.h"
#include "lib_hall_sensor.h"
#include "lib_ws2812.h"
#include "usbd_core.h"
#include <string.h>

bool report_dirty = false;
uint8_t last_key_state[ROW_COUNT][COL_COUNT] = {0};
uint8_t last_fn_state[ROW_COUNT][COL_COUNT] = {0};
//按键键码表
const uint8_t g_key_map[ROW_COUNT][COL_COUNT] = {
    {0x29, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2D, 0x2E, 0x2A},
    {0x2B, 0x14, 0x1A, 0x08, 0x15, 0x17, 0x1C, 0x18, 0x0C, 0x12, 0x13, 0x2F, 0x30, 0x31},
    {0x39, 0x04, 0x16, 0x07, 0x09, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x33, 0x34, KEY_NONE, 0x28},
    {0xE1, 0x00, 0x1D, 0x1B, 0x06, 0x19, 0x05, 0x11, 0x10, 0x36, 0x37, 0x38, KEY_NONE, 0xE5},
    {0xE0, 0xE3, 0xE2, KEY_NONE, KEY_NONE, KEY_NONE, 0x2C, KEY_NONE, KEY_NONE, KEY_NONE, 0xE6, 0x65, 0xE4, KEY_FN}
};
//fn层的键码表
const uint8_t g_fn_key_map[ROW_COUNT][COL_COUNT] = {
    {0x35, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x4C},
    {KEY_NONE, KEY_NONE, 0x52, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
    {KEY_NONE, 0x50, 0x51, 0x4F, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
    {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
    {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_LIGHT, KEY_AI_TRIGGER, KEY_AI_CONFIRM, KEY_FN}
};

extern bool g_led_dirty;
extern LightMode_t g_light_mode;
extern uint32_t ws2812_tick;

void App_send_bubble_report(uint8_t bubble_param, uint8_t ai_action);



//按键扫描任务
void App_adkey_scan_task(void) {
    lib_hall_sensor_task();
    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {
            if (key_mask[r][c] == 0) continue;
            if (keys[r][c].is_pressed != last_key_state[r][c]) {
                last_key_state[r][c] = keys[r][c].is_pressed;
                report_dirty = true;  //按下设置按下标志位
            }
        }
    }
}
/////////////////////////fn的内部处理///////////////////////////////////
void App_handle_internal_key(uint8_t code) {
    if (code == KEY_LIGHT) {
        //g_light_mode = (LightMode_t)(g_light_mode + 1) % LIGHT_MODE_MAX;
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




//////////////////////////////////////////////冒泡上传/////////////////////////////////
void App_send_bubble_report(uint8_t bubble_param, uint8_t ai_action) {
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
