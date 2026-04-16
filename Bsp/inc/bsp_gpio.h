#ifndef __BSP_GPIO_H__
#define __BSP_GPIO_H__

#include "py32f4xx_hal.h"
#include "bsp_board.h"

// ==========================================================
//  按键矩阵行控制 GPIO 函数
// ==========================================================

/**
 * @brief  初始化按键矩阵的行控制引脚
 * @note   配置为推挽输出，初始状态全部拉高（关闭）
 */
void bsp_key_matrix_row_init(void);

/**
 * @brief  设置指定行的电平状态
 * @param  row_idx: 行索引 (0-4)
 * @param  state: GPIO_PIN_SET 或 GPIO_PIN_RESET
 */
void bsp_key_matrix_row_set(uint8_t row_idx, GPIO_PinState state);

/**
 * @brief  设置所有行的电平状态
 * @param  state: GPIO_PIN_SET 或 GPIO_PIN_RESET
 */
void bsp_key_matrix_row_all_set(GPIO_PinState state);

/**
 * @brief  选择扫描某一行（拉低该行，其他行拉高）
 * @param  row_idx: 行索引 (0-4)
 */
void bsp_key_matrix_row_select(uint8_t row_idx);

// ==========================================================
//  LED 使能控制 GPIO 函数
// ==========================================================

/**
 * @brief  初始化 LED 使能引脚
 * @note   配置为推挽输出，初始状态拉低
 */
void bsp_led_en_init(void);

/**
 * @brief  设置 LED 使能引脚电平
 * @param  state: GPIO_PIN_SET 或 GPIO_PIN_RESET
 */
void bsp_led_en_set(GPIO_PinState state);

// ==========================================================
//  统一初始化函数
// ==========================================================

/**
 * @brief  统一初始化键盘相关的所有 GPIO
 */
void bsp_keyboard_gpio_init(void);

#endif
