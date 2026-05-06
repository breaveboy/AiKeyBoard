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

extern volatile uint8_t hid_state;

void App_usb_process_task(void) {
    if (!report_dirty) return;

    uint8_t current_report[8] = {0};
    uint8_t key_count = 0;
    bool fn_pressed = false;

    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {
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
            if (code == KEY_NONE) code = g_key_map[r][c];
            if (code == KEY_NONE || code == KEY_FN) continue;

            if (code >= 0xF0) {
                if (last_fn_state[r][c] == 0) {
                    App_handle_internal_key(code);
                    last_fn_state[r][c] = 1;
                }
                continue;
            }
            if (code >= 0xE0 && code <= 0xE7) {
                current_report[0] |= (1U << (code - 0xE0));
            } else if (key_count < 6) {
                current_report[2 + key_count++] = code;
            }
        }
    }

    static uint8_t last_report[8] = {0};
    if (memcmp(current_report, last_report, 8) != 0) {
        if (usbd_ep_start_write(HID_INT_EP, current_report, 8) == 0) {
            hid_state = HID_STATE_BUSY;
            memcpy(last_report, current_report, 8);
            report_dirty = false;
        }
    } else {
        report_dirty = false;
    }
}
