#include "App_key.h"
#include "App_protocol.h"
#include "App_lighting.h"
#include "App_debug.h"
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
    //{0xE0, 0xE3, 0xE2, KEY_NONE, KEY_NONE, KEY_NONE, 0x2C, KEY_NONE, KEY_NONE, KEY_NONE, 0xE6, 0x65, 0xE4, KEY_FN}
    {0xE0, 0xE3, 0xE2, KEY_NONE, KEY_NONE, KEY_NONE, 0x2C, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_FN}
};

// Fn 层键位表：KEY_LIGHT / KEY_AI_* 这类 0xF0 以上键值只在固件内部处理。
const uint8_t g_fn_key_map[ROW_COUNT][COL_COUNT] = {
    {0x35, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x4C},
    {KEY_NONE, KEY_NONE, 0x52, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
    {KEY_NONE, 0x50, 0x51, 0x4F, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
    {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
    {KEY_NONE, KEY_NONE, KEY_LIGHT, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_AI_TRIGGER, KEY_AI_CONFIRM,KEY_AI_CANCEL , KEY_FN}
};

extern bool g_led_dirty;
extern LightMode_t g_light_mode;
extern uint32_t ws2812_tick;

// 处理 Fn 组合内部功能键，如 Fn+Alt 切换灯光、AI 触发键上报。
static void App_process_internal_keys(void);
// 自定义 HID 冒泡上报，用于主动通知上位机 AI 按键事件。
void App_send_bubble_report(uint8_t bubble_param, uint8_t ai_action);

// 终极优化版：非对称环境基准追踪算法
static void update_baseline_tracking(Key_t *k, uint16_t cur_adc)
{
    // 【安全红线】如果按键处于按下状态，绝对不进行追踪，清零计数器并返回
    if (k->is_pressed) {
        k->drift_cnt = 0; 
        return;
    }   
    
    // 计算当前基准值与实际读数的差值
    int32_t diff = (int32_t)k->idele_adc - (int32_t)cur_adc;

    // ========================================================================
    // 如果物理实际读数大于基准值（即 diff < 0），说明基准值之前被拉低（污染）了。
    // 由于物理大值是 100% 安全的，无需任何计数，直接、瞬间将基准值同步为当前实际值！
    // =========================================================================
    if (diff < 0) {
        k->idele_adc = cur_adc; // 瞬间恢复物理原位，死锁瞬间解除
        k->drift_cnt = 0;
        return;
    }

    // =========================================================================
    // 只有当微小偏差处于 (0, 15) 的极窄区间内，才认为是温漂。
    // 如果偏差大于等于 15，说明绝对是人在碰按键（或手搭在上面），此时立即停止追踪并清零！
    // =========================================================================
    if (diff > 0 && diff < 15) {   
        k->drift_cnt++;  
        // 7.5周期扫描极快，这里设置 5000 次（约 1 ~ 2秒）完全静止才微调 1 个单位
        if (k->drift_cnt > 5000) {
            k->idele_adc--;     // 极其缓慢地往下校准 1 个单位
            k->drift_cnt = 0;   
        }
    } 
    // 偏差太大（>=15），说明是人手的主动按压，立即清零，保护基准值不被拉低
    else {
        k->drift_cnt = 0; 
    }
}
// AP/RT 判断旧版：保留用于对比，当前使用下面的优化版。
#if 0
//按键没有按下时候进行idele_adc的校准，防止无法打字
static void update_baseline_tracking(Key_t *k, uint16_t cur_adc)
{
    if (k->is_pressed) {
        k->drift_cnt = 0; //校准计数器清零
        return;
    }   
    
    //记录插值
    int32_t diff = (int32_t)k->idele_adc - (int32_t)cur_adc;

    if (diff < 100 && diff > -100) {   //温漂原来是30
        k->drift_cnt++;  // 发现偏差了，观察一段时间
        //////偏差示例10000次进行调整
        if (k->drift_cnt > 1000) {
            if (diff > 0) {
                k->idele_adc--;// 基准值往当前读数挪 1 个单位
            } else if (diff < 0) {
                k->idele_adc++;
            }
            k->drift_cnt = 0;// 改完后，重新开始观察
        }
    } else {
        k->drift_cnt = 0;// 如果偏差突然很大，说明用户可能要按键了，停止校准
    }
}
// AP/RT 判断：根据整帧 ADC 中的当前值更新单键按下状态。
static uint8_t process_key_logic(Key_t *k, uint16_t cur_adc)
{   
    // 计算按下去的深度（Offset）。数值越大，按得越深。
    int32_t diff = (int32_t)k->idele_adc - (int32_t)cur_adc;  
    int16_t offset = (diff > 0) ? (int16_t)diff : 0;
    // 顶部死区：按下的深度还没超过 80（很浅），直接判定为没按。
    if (offset < k->top_deadzone) {
        k->is_pressed = 0;
        k->in_rt_cycle = 0;// 退出动态触发循环
        k->max_offset = 0;
        k->min_offset = 0;
        return 0;
    }
     // 底部保护：防止按得太深超过了硬件限制。
    if (offset > k->bottom_deadzone) {
        offset = k->bottom_deadzone;
    }

    if (!k->is_pressed) { //没有按下
         //记录按下过程中的最小值
        if (offset < k->min_offset) {
            k->min_offset = offset;
        }
       // 计算触发线。如果是第一次按，用固定触发点；如果是连点，用RT动态点。
        uint16_t trigger_line = k->in_rt_cycle ? (k->min_offset + k->rt_press_sens) : k->actuation_point;
        
        if (offset >= trigger_line) {
            k->is_pressed = 1;//触发成功，判断为按下
            k->in_rt_cycle = 1;
            k->max_offset = offset; // 开始记录按下后的最深点
        }
    } else {  //已经按下
          // 记录按下后的最深点
        if (offset > k->max_offset) {  
            k->max_offset = offset;
        }
         //抬起判定。只要从最深点回弹了 rt_release_sens 的距离，立即松开。
        uint16_t release_line = k->max_offset - k->rt_release_sens;
        if (offset <= release_line) {
            k->is_pressed = 0;
            k->min_offset = offset;
        }
    }

    return k->is_pressed;
}
#endif

//物理行程        ADC 偏差 (Offset)      状态变量与参数工作机制
//【松开状态】 ───? Offset = 0
//   │                                ┌──────────────────────────────────────────────┐
//   │            [0 ~ 150]           │ 1. 顶部死区 (top_deadzone = 150)             │
//   │                                │ ── 运行变量状态:                              │
//   │                                │    is_pressed = 0, in_rt_cycle = 0           │
//   │                                │    max_offset = 0, min_offset = 0            │
//   ▼                                │ ── 特殊变量:                                  │
//                                    │    drift_cnt (漂移计数器) 在此区间工作。       │
//                                    │    若值在此长期微幅偏离0，则重校准 idle_adc。 │
//                ....................└──────────────────────────────────────────────┘
//   │            Offset = 150 (退出顶部死区边界)
//   │
//   │            [150 ~ 350]         ┌──────────────────────────────────────────────┐
//   │                                │ 2. 预备触发区                                 │
//   │                                │ ── 运行变量状态:                              │
//   │                                │    is_pressed = 0, in_rt_cycle = 0           │
//   ▼                                │    (即使在此区间起伏，也不会触发 RT 判定)     │
//                ....................└──────────────────────────────────────────────┘
//   │            Offset = 350 (静态触发点 actuation_point)
//   │                                ┌──────────────────────────────────────────────┐
//   │                                │ 【临界事件】：首次下按越过 350                  │
//   │                                │  ── 状态跃迁:                                 │
//   │                                │     is_pressed 0 -> 1                        │
//   │                                │     in_rt_cycle 0 -> 1                       │
//   ▼                                └──────────────────────────────────────────────┘
//   │            [350 ~ 1050]        ┌──────────────────────────────────────────────┐
//   │                                │ 3. RT 有效工作区间 (灵敏度 50)                │
//   │                                │ ── 运行变量状态:                              │
//   │                                │    in_rt_cycle = 1 (RT 保持激活)              │
//   │                                │ ── 动态跟踪变量:                              │
//   │                                │    max_offset: 实时记录下压过程中的最高峰。     │
//   │                                │    min_offset: 实时记录抬起过程中的最低谷。     │
//   │                                │ ── 触发规则:                                  │
//   │                                │    抬起：Offset < (max_offset - 50) -> 松开    │
//   ▼                                │    再按：Offset > (min_offset + 50) -> 按下    │
//                ....................└──────────────────────────────────────────────┘
//   │            Offset = 1050 (底端死区 bottom_deadzone)
//   │                                ┌──────────────────────────────────────────────┐
//   │            [1050 ~ 最大值]     │ 4. 底部死区                                  │
//   │                                │ ── 运行变量状态:                              │
//   │                                │    in_rt_cycle = 1                           │
//   │                                │ ── 限制机制:                                  │
//   │                                │    max_offset 停止向上更新（锁定在 1050 附近），│
//   ▼                                │    防止触底形变导致的压力抖动。               │
//【触底状态】 ───? Offset = Max (约1150)└──────────────────────────────────────────────┘










// AP/RT 判断优化版：首次按压用 AP，松开后进入 RT 动态触发循环。
static uint8_t process_key_logic(Key_t *k, uint16_t cur_adc)
{
    // 计算按下深度。数值越大，按得越深。
    int32_t diff = (int32_t)k->idele_adc - (int32_t)cur_adc;
    uint16_t offset = (diff > 0) ? (uint16_t)diff : 0U;

    // 完全回到顶部死区：退出 RT 循环，下次重新使用固定触发点。
    if (offset < k->top_deadzone) {
        k->is_pressed = 0;
        k->in_rt_cycle = 0;
        k->max_offset = 0;
        k->min_offset = offset;
        return 0;
    }

    // 底部保护：限制最大行程，避免异常 ADC 值影响判断。
    if (offset > k->bottom_deadzone) {
        offset = k->bottom_deadzone;
    }

    if (!k->is_pressed) {
        uint16_t trigger_line;

        if (k->in_rt_cycle) {
            // RT 循环中：持续记录松开后的最浅位置。
            if (offset < k->min_offset) {
                k->min_offset = offset;
            }

            trigger_line = k->min_offset + k->rt_press_sens;
            if (trigger_line > k->bottom_deadzone) {
                trigger_line = k->bottom_deadzone;
            }
        } else {
            // 首次触发：使用固定 AP。
            trigger_line = k->actuation_point;
        }

        if (offset >= trigger_line) {
            k->is_pressed = 1;
            k->max_offset = offset;
        }
    } else {
        // 已经按下：持续记录本次按压的最深位置。
        if (offset > k->max_offset) {
            k->max_offset = offset;
        }

        // 防止 uint16_t 下溢。
        uint16_t release_line = 0;
        if (k->max_offset > k->rt_release_sens) {
            release_line = k->max_offset - k->rt_release_sens;
        }

        if (offset <= release_line) {
            k->is_pressed = 0;
            k->in_rt_cycle = 1;
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
                App_debug_key_change_tick();
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

    /* Share endpoint 0x82 with command ACKs through the protocol TX queue. */
    (void)App_protocol_send_packet(&bubble_pkt);
}
