#include "App.h"
#include "lib_config.h"
#include "bsp_uart.h"
#include "usb_config.h"
#include <stdio.h>
#include <string.h>

#define HID_KEY_A_CODE 0x04

static uint8_t last_modifiers = 0;
static uint8_t last_keys[6] = {0};

void App_init(void)
{
    last_modifiers = 0;
    memset(last_keys, 0, sizeof(last_keys));
}

void App_adkey_scan_task(void)
{
    lib_hall_scan_all();
}

void App_logic_handler_task(void)
{
    uint8_t current_modifiers = 0;
    uint8_t current_keys[6] = {0};
    uint8_t key_idx = 0;

    for (uint8_t r = 0; r < MATRIX_ROWS_COUNT; r++) {
        for (uint8_t c = 0; c < ADC_CHANNELS_COUNT; c++) {
            if (lib_hall_is_pressed(r, c)) {
                uint8_t code = lib_key_get_code(r, c);

                if (lib_key_is_modifier(r, c)) {
                    current_modifiers |= lib_key_get_modifier_mask(r, c);
                } else {
                    if (key_idx < 6 && code != 0) {
                        current_keys[key_idx++] = code;
                    }
                }

                if (lib_hall_just_pressed(r, c)) {
                    printf("[DOWN] Row=%d, Col=%d, Code=0x%02X\n", r, c, code);
                }
            }

            if (lib_hall_just_released(r, c)) {
                uint8_t code = lib_key_get_code(r, c);
                printf("[UP]   Row=%d, Col=%d, Code=0x%02X\n", r, c, code);
            }
        }
    }

    bool report_changed = false;

    if (current_modifiers != last_modifiers) {
        report_changed = true;
    }

    for (uint8_t i = 0; i < 6; i++) {
        if (current_keys[i] != last_keys[i]) {
            report_changed = true;
            break;
        }
    }

    if (report_changed) {
        last_modifiers = current_modifiers;
        memcpy(last_keys, current_keys, sizeof(last_keys));
    }
}

void App_usb_process_task(void)
{
    if (hid_keyboard_is_ready()) {
        hid_keyboard_send_report(last_modifiers, last_keys);
    }
}

void App_usb_test_task(void)
{
    static const uint8_t key_a[6] = {HID_KEY_A_CODE, 0, 0, 0, 0, 0};
    static uint8_t phase = 0;

    if (!hid_keyboard_is_ready()) {
        return;
    }

    if ((phase & 0x01U) == 0U) {
        hid_keyboard_send_report(0, (uint8_t *)key_a);
    } else {
        hid_keyboard_send_report(0, NULL);
    }

    phase++;
    if (phase >= 10U) {
        phase = 0;
    }
}
