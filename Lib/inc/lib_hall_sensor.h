#ifndef __LIB_HALL_SENSOR_H
#define __LIB_HALL_SENSOR_H

#include "py32f4xx_hal.h"
#include "bsp_adc_dma.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define ROW_COUNT          5    //5行
#define COL_COUNT          14
#define SETTLING_TIME_US   35  //切换行的时间是35us

// 单键运行参数：校准基准、触发点、RT 灵敏度和当前按压状态。
typedef struct {
    uint16_t idele_adc;   //基准值
    uint16_t drift_cnt;   //温漂的技术值

    uint16_t actuation_point;  //固定触发点
    uint16_t rt_press_sens;    //RT 灵敏度
    uint16_t rt_release_sens;
    uint16_t top_deadzone;
    uint16_t bottom_deadzone;

    uint16_t max_offset;
    uint16_t min_offset;
    uint8_t  is_pressed;
    uint8_t  in_rt_cycle;
} Key_t;

// 按键状态数组由 App_key 任务消费和更新。
extern Key_t keys[ROW_COUNT][COL_COUNT];
// 一整帧滤波后的 ADC 数据，行列布局为 5 x 14。
extern uint16_t g_hall_adc_frame[ROW_COUNT][COL_COUNT];
// 置 1 表示 g_hall_adc_frame 已经采满一帧，等待按键任务处理。
extern volatile uint8_t g_scan_complete;
extern const uint8_t key_mask[ROW_COUNT][COL_COUNT];

// 初始化霍尔矩阵 GPIO 和 ADC DMA。
void lib_hall_sensor_init(void);
// 上电校准每个按键的空闲 ADC 基准。
void lib_hall_sensor_calibration(void);
// 启动一帧 5 行扫描。
void lib_hall_sensor_start_scan(void);
// 按键任务处理完当前帧后调用，用于启动下一帧扫描。
void lib_hall_sensor_release_frame(void);
// ADC 采集任务：DMA 每完成一行，就滤波写入 g_hall_adc_frame。
void lib_hall_sensor_task(void);

void select_row(uint8_t index);
void ROW_ALL_OFF(void);

#endif
