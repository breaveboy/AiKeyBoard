#include "App_usb.h"
#include "App_key.h"
#include "lib_hall_sensor.h"
#include "usbd_core.h"
#include <string.h>

#ifndef HID_STATE_IDLE
#define HID_STATE_IDLE 0
#endif
#ifndef HID_STATE_BUSY
#define HID_STATE_BUSY 1
#endif
#ifndef HID_INT_EP
#define HID_INT_EP 0x81
#endif

// 0x81 IN 端点忙超时保护，避免 PC 未取走上一包后长期不能打字。
#define HID_BUSY_TIMEOUT_TICKS 20

extern volatile uint8_t hid_state;


// USB 键盘发送任务：只根据 keys[][] 生成标准 8 字节 HID report。
void App_usb_process_task(void)
{
    static uint8_t last_report[8] = {0};
    static uint8_t busy_ticks = 0;

    // 如果上一次 IN 包长时间未完成，主动恢复状态并允许后续重试。
    if (hid_state == HID_STATE_BUSY) {
        if (++busy_ticks < HID_BUSY_TIMEOUT_TICKS) {
            return;
        }

        (void)usbd_ep_flush(HID_INT_EP);
        hid_state = HID_STATE_IDLE;
        busy_ticks = 0;
        memset(last_report, 0xFF, sizeof(last_report));
        report_dirty = true;
    }

    // 没有按键状态变化时不占用 USB 总线。
    if (!report_dirty) {
        return;
    }

    uint8_t current_report[8] = {0};
    uint8_t key_count = 0;
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
            if (code == KEY_NONE || code == KEY_FN) {
                continue;
            }

            if (code >= 0xF0) {
                continue;
            }

            if (code >= 0xE0 && code <= 0xE7) {
                current_report[0] |= (1U << (code - 0xE0));
            } else if (key_count < 6) {
                current_report[2 + key_count++] = code;
            }
        }
    }

    if (memcmp(current_report, last_report, sizeof(current_report)) == 0) {
        report_dirty = false;
        return;
    }

    // 发送失败时保留 report_dirty，下次任务继续尝试发送。
    int ret = usbd_ep_start_write(HID_INT_EP, current_report, sizeof(current_report));

    if (ret == 0) {
        hid_state = HID_STATE_BUSY;
        busy_ticks = 0;
        memcpy(last_report, current_report, sizeof(last_report));
        report_dirty = false;
    } else {
        report_dirty = true;

        if (ret == -2 || ret == -3) {
            if (ret == -3) {
                (void)usbd_ep_flush(HID_INT_EP);
                memset(last_report, 0xFF, sizeof(last_report));
            }
            hid_state = HID_STATE_IDLE;
        }
    }
}
