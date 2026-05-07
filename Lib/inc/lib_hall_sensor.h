#ifndef __LIB_HALL_SENSOR_H
#define __LIB_HALL_SENSOR_H

#include "py32f4xx_hal.h"
#include "bsp_adc_dma.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define ROW_COUNT          5
#define COL_COUNT          14
#define SCAN_ROUNDS        3      
#define SETTLING_TIME_US   35 //50     

typedef struct {
    uint16_t idele_adc;       // 空闲adc
	  uint16_t drift_cnt;      //动态追踪计数器
	
	
	
	
	
	
	
	
	
    uint16_t actuation_point; // 触发值
    uint16_t rt_press_sens;   // 按下RT
    uint16_t rt_release_sens; // 释放RT
    uint16_t top_deadzone;    // 顶部死区
    uint16_t bottom_deadzone; // 底部死区
    
    uint16_t max_offset;      // 最大偏移量
    uint16_t min_offset;      // 最小偏移量
    uint8_t  is_pressed;      // 按压值判断
    uint8_t  in_rt_cycle;     // RT判断
	
} Key_t;

extern Key_t keys[ROW_COUNT][COL_COUNT];
extern volatile uint8_t g_scan_complete;
extern const uint8_t key_mask[ROW_COUNT][COL_COUNT];

void lib_hall_sensor_init(void);
void lib_hall_sensor_calibration(void);
void lib_hall_sensor_task(void);


void select_row(uint8_t index);
void ROW_ALL_OFF(void);

#endif
