#include "App.h"
#include "lib_config.h"
#include "bsp_uart.h"
#include "usb_config.h"
#include "lib_ws2812.h"
#include "lib_hall_sensor.h"
#include <stdio.h>
#include <string.h>
#include "usbd_core.h"
#include "usbd_hid.h"

#define HID_KEY_A_CODE 0x04

static uint8_t last_modifiers = 0;
static uint8_t last_keys[6] = {0};
static bool report_dirty = false;
static bool g_led_dirty = false;
static uint8_t last_key_state[ROW_COUNT][COL_COUNT] = {0};

void App_init(void)
{
    last_modifiers = 0;
    memset(last_keys, 0, sizeof(last_keys));
    report_dirty = false;
    g_led_dirty = false;
    memset(last_key_state, 0, sizeof(last_key_state));

   
}

void App_adkey_scan_task(void)
{
    lib_hall_sensor_task();

    // 按键联动灯光逻辑
    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {
            // 增加掩码判断，只处理有效的按键
            if (key_mask[r][c] == 0) continue;

            if (keys[r][c].is_pressed != last_key_state[r][c]) {
                last_key_state[r][c] = keys[r][c].is_pressed;
                if (keys[r][c].is_pressed) {
                    // 按下时显示青色 (0, 255, 255)
                    lib_ws2812_set_key_color(r, c, 0, 255, 255);
                } else {
                    // 松开时关闭
                    lib_ws2812_set_key_color(r, c, 0, 0, 0);
                }
                g_led_dirty = true;
            }
        }
    }
}

void App_display_task(void)
{
    if (g_led_dirty) {
        if (lib_ws2812_update() == 0) { // 0 is HAL_OK
            g_led_dirty = false;
        }
    }
}


#if 0
void App_usb_process_task(void)
{
    if (report_dirty && hid_keyboard_is_ready()) {
        hid_keyboard_send_report(last_modifiers, last_keys);
        report_dirty = false;
    }
}
#endif


void App_usb_test_task(void)
{


printf("success_send");
	
}

static uint32_t ws2812_tick = 0;

void App_ws2812_breath_task(void)
{
    ws2812_tick++;
    lib_ws2812_breath_mode(ws2812_tick);
}

void App_ws2812_rainbow_task(void)
{
    ws2812_tick++;
    lib_ws2812_rainbow_mode(ws2812_tick);
}
