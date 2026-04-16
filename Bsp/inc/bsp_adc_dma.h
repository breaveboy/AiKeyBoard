#ifndef __BSP_ADC_DMA_H__
#define __BSP_ADC_DMA_H__

#include "py32f4xx_hal.h"
#include "bsp_board.h"

// ==========================================================
//  5x14 ADC 磁轴按键矩阵扫描模块
//  使用 DMA 自动采集，数据存入二维数组
// ==========================================================

/**
 * @brief  ADC 原始数据矩阵
 * @note   Lib 层访问方式：g_adc_raw_matrix[row][col]
 *         row: 0-4 (行), col: 0-13 (列)
 */
extern uint32_t g_adc_raw_matrix[MATRIX_ROWS_COUNT][ADC_CHANNELS_COUNT];

/**
 * @brief  初始化 ADC DMA 矩阵扫描模块
 * @note   初始化 GPIO、ADC、DMA 并开启校准
 */
void bsp_adc_dma_init(void);

/**
 * @brief  启动 ADC DMA 自动扫描
 * @note   启动后会自动循环扫描 5行 x 14列 的数据
 */
void bsp_adc_dma_start(void);

#endif
