#include "App.h"
#include "lib_config.h"
#include "bsp_uart.h"
#include "usb_config.h"
#include "lib_ws2812.h"
#include "lib_hall_sensor.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
/*

USB ?υτ
 ?????? Interface 0????????? HID
 ??    ?????? Class = 0x03
 ??    ?????? Protocol = 0x01 Keyboard
 ??    ?????? Endpoint = 0x81
 ??    ?????? Report ID????????§µ???? 8 ???????
 ??
 ?????? Interface 1????????? HID
      ?????? Class = 0x03
      ?????? Protocol = 0x00
      ?????? Endpoint OUT = 0x02
      ?????? Endpoint IN  = 0x82
      ?????? Report ID = 0x05
*/
/* --- ??????? --- */
static bool report_dirty = false;   // USB ????????????
static bool g_led_dirty = false;    // ???????????????
static uint8_t last_key_state[ROW_COUNT][COL_COUNT] = {0};  // ?????????????
static uint8_t last_fn_state[ROW_COUNT][COL_COUNT] = {0};   // ?????????????

/* --- USB ????? --- */
extern volatile uint8_t hid_state; 
#ifndef HID_STATE_IDLE
    #define HID_STATE_IDLE 0  
#endif
#ifndef HID_STATE_BUSY
    #define HID_STATE_BUSY 1
#endif
#ifndef HID_INT_EP
    #define HID_INT_EP  0x81
#endif

/* --- ???????????? --- */
#define KEY_NONE    0x00
#define KEY_FN      0xF0
#define KEY_LIGHT   0xF1
#define KEY_WINLOCK 0xF2
#define KEY_MAC     0xF3
#define KEY_WIN     0xF4

/* --- ????????? --- */
typedef enum {
    LIGHT_MODE_OFF = 0,
    LIGHT_MODE_BREATH,
    LIGHT_MODE_RAINBOW,
    LIGHT_MODE_KEY_PRESS,
    LIGHT_MODE_STATIC,
	  LIGHT_MODE_COLLIDE, //???????????
	  LIGHT_MODE_DAZZLE_MARQUEE, // ???????????????
    LIGHT_MODE_MAX  //??????????
} LightMode_t;

static LightMode_t g_light_mode = LIGHT_MODE_OFF;
static uint8_t g_pending_internal_key = KEY_NONE; 
static uint32_t ws2812_tick = 0;

/* --- ???????? (60% ????) --- */
static const uint8_t g_key_map[5][14] = {
    {0x29, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2D, 0x2E, 0x2A},
    {0x2B, 0x14, 0x1A, 0x08, 0x15, 0x17, 0x1C, 0x18, 0x0C, 0x12, 0x13, 0x2F, 0x30, 0x31},
    {0x39, 0x04, 0x16, 0x07, 0x09, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x33, 0x34, KEY_NONE, 0x28},
    {0xE1, 0x00, 0x1D, 0x1B, 0x06, 0x19, 0x05, 0x11, 0x10, 0x36, 0x37, 0x38, KEY_NONE, 0xE5},
    {0xE0, 0xE3, 0xE2, KEY_NONE, KEY_NONE, KEY_NONE, 0x2C, KEY_NONE, KEY_NONE, KEY_NONE, 0xE6, 0x65, 0xE4, KEY_FN}
};

static const uint8_t g_fn_key_map[5][14] = {
    {0x35, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, KEY_NONE},
    {KEY_NONE, KEY_NONE, 0x52, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
    {KEY_NONE, 0x50, 0x51, 0x4F, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
    {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE},
    {KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_LIGHT,/*?????*/ KEY_NONE, KEY_NONE, KEY_FN}
};


/* --- 1. ????? --- */
void App_init(void) {
    report_dirty = false;
    g_led_dirty = true;  //???????????????????????
    memset(last_key_state, 0, sizeof(last_key_state));
    memset(last_fn_state, 0, sizeof(last_fn_state));
    g_light_mode = LIGHT_MODE_OFF;
}

/* --- 2. ??????? (1ms) --- */
void App_adkey_scan_task(void) {
    lib_hall_sensor_task(); // ??????
    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {
            if (key_mask[r][c] == 0) continue; //???????????
            if (keys[r][c].is_pressed != last_key_state[r][c]) {
                last_key_state[r][c] = keys[r][c].is_pressed;
                report_dirty = true; // ????????????
            }
        }
    }
}

/* --- 3. USB ???????? (1ms) --- */
void App_usb_process_task(void) {
    if (!report_dirty) return; // ???????????????
    
	
	

    uint8_t current_report[8] = {0};
    uint8_t key_count = 0;
    bool fn_pressed = false;

    // A. ??? Fn ??
    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {
            if (keys[r][c].is_pressed && g_key_map[r][c] == KEY_FN) { fn_pressed = true; break; }
        }
    }

    // B. ???????
    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        for (uint8_t c = 0; c < COL_COUNT; c++) {
            if (key_mask[r][c] == 0 || !keys[r][c].is_pressed) {
                last_fn_state[r][c] = 0; continue;
            }
            uint8_t code = fn_pressed ? g_fn_key_map[r][c] : g_key_map[r][c];
            if (code == KEY_NONE) code = g_key_map[r][c];
            if (code == KEY_NONE || code == KEY_FN) continue;

            if (code >= 0xF0) { // ?????
                if (last_fn_state[r][c] == 0) { g_pending_internal_key = code; last_fn_state[r][c] = 1; }
                continue;
            }
            if (code >= 0xE0 && code <= 0xE7) { // ??????
                current_report[0] |= (1U << (code - 0xE0));
            } else if (key_count < 6) { // ?????
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
    } else { report_dirty = false; }
}

/* --- 4. ?????? (10ms) --- */
static void App_handle_internal_key(uint8_t code) {
    if (code == KEY_LIGHT) {
        g_light_mode = (g_light_mode + 1) % LIGHT_MODE_MAX;
        ws2812_tick = 0;
        lib_ws2812_set_all(0, 0, 0); // ???????
        g_led_dirty = true;
    }
}
//???????????
void App_led_logic_task(void) {
    if (g_pending_internal_key != KEY_NONE) {
        App_handle_internal_key(g_pending_internal_key);
        g_pending_internal_key = KEY_NONE;
    }
}

/* --- 5. ????? (25ms) --- */
void App_led_animation_task(void) {
    switch (g_light_mode) {
        case LIGHT_MODE_BREATH:  lib_ws2812_breath_mode(++ws2812_tick); g_led_dirty = true; break;
        case LIGHT_MODE_RAINBOW: lib_ws2812_rainbow_mode(++ws2812_tick); g_led_dirty = true; break;
        case LIGHT_MODE_STATIC:  lib_ws2812_set_all(30, 180, 255); g_led_dirty = true; break;
        case LIGHT_MODE_KEY_PRESS:
            for (uint8_t r = 0; r < ROW_COUNT; r++) {
                for (uint8_t c = 0; c < COL_COUNT; c++) {
                    if (key_mask[r][c] == 0) continue;
                    if (keys[r][c].is_pressed) lib_ws2812_set_key_color(r,c,0,255,255);
                    else lib_ws2812_set_key_color(r,c,0,0,0);
                }
            }
            g_led_dirty = true;
            break;
				case LIGHT_MODE_COLLIDE: lib_ws2812_collide_ripple_mode(++ws2812_tick);g_led_dirty=true;break;
        case LIGHT_MODE_DAZZLE_MARQUEE: lib_ws2812_dazzle_marquee_mode(++ws2812_tick); g_led_dirty = true; 
    break;
        default: break;
    }
}

/* --- 6. ?????? (30ms) --- */
void App_led_display_task(void) {
    if (g_led_dirty) {
        if (lib_ws2812_update() == 0) g_led_dirty = false;
    }
}