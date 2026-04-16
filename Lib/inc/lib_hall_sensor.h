#ifndef __LIB_HALL_SENSOR_H
#define __LIB_HALL_SENSOR_H

#include "py32f4xx_hal.h"
#include "bsp_adc_dma.h"
#include <stdbool.h>

// ==========================================================
//  配置参数
// ==========================================================
#define HALL_DEPTH_MAX          1000
#define HALL_CALIB_DEFAULT_MIN  2048
#define HALL_CALIB_DEFAULT_MAX  4000

// 按键按下/释放阈值 (0-1000)
#define HALL_THRESHOLD_PRESS    300   // 按下阈值
#define HALL_THRESHOLD_RELEASE  200   // 释放阈值（带迟滞）

// 消抖计数
#define HALL_DEBOUNCE_CNT       3

// ==========================================================
//  按键状态枚举
// ==========================================================
typedef enum {
    KEY_STATE_RELEASED = 0,   // 已释放
    KEY_STATE_PRESSED,        // 已按下
    KEY_STATE_DEBOUNCE_PRESS, // 按下消抖中
    KEY_STATE_DEBOUNCE_RELEASE // 释放消抖中
} key_state_t;

// ==========================================================
//  按键数据结构体
// ==========================================================
typedef struct {
    uint16_t min_adc;
    uint16_t max_adc;
    uint16_t range;
    bool     is_valid;
} hall_config_t;

typedef struct {
    key_state_t state;        // 当前状态
    uint8_t     debounce_cnt;  // 消抖计数器
    uint16_t    last_depth;    // 上次深度
    bool        was_pressed;   // 上一次扫描是否按下
} key_data_t;

// ==========================================================
//  函数声明
// ==========================================================
void lib_hall_init(void);
bool lib_hall_is_key_valid(uint8_t row, uint8_t col);
uint16_t lib_hall_get_depth(uint8_t row, uint8_t col);

// 按键状态扫描函数
void lib_hall_scan_all(void);
bool lib_hall_is_pressed(uint8_t row, uint8_t col);
bool lib_hall_just_pressed(uint8_t row, uint8_t col);
bool lib_hall_just_released(uint8_t row, uint8_t col);

#endif