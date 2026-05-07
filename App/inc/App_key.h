#ifndef __APP_KEY_H__
#define __APP_KEY_H__

#include "lib_hall_sensor.h"
#include <stdint.h>
#include <stdbool.h>

#define KEY_NONE       0x00
#define KEY_FN         0xF0
#define KEY_LIGHT      0xF1
#define KEY_WINLOCK    0xF2
#define KEY_MAC        0xF3
#define KEY_WIN        0xF4
#define KEY_AI_TRIGGER 0xF5
#define KEY_AI_CONFIRM 0xF6
#define KEY_AI_CANCEL  0xF7

extern bool report_dirty;
extern uint8_t last_key_state[ROW_COUNT][COL_COUNT];
extern uint8_t last_fn_state[ROW_COUNT][COL_COUNT];
extern const uint8_t g_key_map[ROW_COUNT][COL_COUNT];
extern const uint8_t g_fn_key_map[ROW_COUNT][COL_COUNT];

void App_adkey_scan_task(void);
void App_handle_internal_key(uint8_t code);

#endif
