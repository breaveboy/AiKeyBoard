#ifndef __BSP_BOARD_H__
#define __BSP_BOARD_H__

#include "py32f4xx_hal.h"
// ==========================================================
//  ADC 磁轴按键矩阵配置
// ==========================================================
#define ADC_CHANNELS_COUNT       14    // ADC 通道数量（列数）
#define MATRIX_ROWS_COUNT        5     // 矩阵行数

// 行控制引脚配置 (ROW1-ROW5) - 低电平有效
#define ROW1_PIN                 GPIO_PIN_6
#define ROW1_PORT                GPIOC
#define ROW2_PIN                 GPIO_PIN_7
#define ROW2_PORT                GPIOC
#define ROW3_PIN                 GPIO_PIN_8
#define ROW3_PORT                GPIOC
#define ROW4_PIN                 GPIO_PIN_9
#define ROW4_PORT                GPIOC
#define ROW5_PIN                 GPIO_PIN_10
#define ROW5_PORT                GPIOC

#define ROW_ALL_PINS             (ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN | ROW5_PIN)
#define ROW_ALL_PORT             GPIOC

// ADC 列通道配置 (AIN0-AIN13) - 连接霍尔传感器
#define ADC_COL0_PIN             GPIO_PIN_0
#define ADC_COL0_PORT            GPIOA
#define ADC_COL1_PIN             GPIO_PIN_1
#define ADC_COL1_PORT            GPIOA
#define ADC_COL2_PIN             GPIO_PIN_2
#define ADC_COL2_PORT            GPIOA
#define ADC_COL3_PIN             GPIO_PIN_3
#define ADC_COL3_PORT            GPIOA
#define ADC_COL4_PIN             GPIO_PIN_4
#define ADC_COL4_PORT            GPIOA
#define ADC_COL5_PIN             GPIO_PIN_5
#define ADC_COL5_PORT            GPIOA
#define ADC_COL6_PIN             GPIO_PIN_6
#define ADC_COL6_PORT            GPIOA
#define ADC_COL7_PIN             GPIO_PIN_7
#define ADC_COL7_PORT            GPIOA
#define ADC_COL8_PIN             GPIO_PIN_0
#define ADC_COL8_PORT            GPIOB
#define ADC_COL9_PIN             GPIO_PIN_1
#define ADC_COL9_PORT            GPIOB
#define ADC_COL10_PIN            GPIO_PIN_0
#define ADC_COL10_PORT           GPIOC
#define ADC_COL11_PIN            GPIO_PIN_1
#define ADC_COL11_PORT           GPIOC
#define ADC_COL12_PIN            GPIO_PIN_2
#define ADC_COL12_PORT           GPIOC
#define ADC_COL13_PIN            GPIO_PIN_3
#define ADC_COL13_PORT           GPIOC

// ADC 通道映射 - 对应内部 ADC 通道号
#define ADC_COL0_CH              ADC_CHANNEL_0
#define ADC_COL1_CH              ADC_CHANNEL_1
#define ADC_COL2_CH              ADC_CHANNEL_2
#define ADC_COL3_CH              ADC_CHANNEL_3
#define ADC_COL4_CH              ADC_CHANNEL_4
#define ADC_COL5_CH              ADC_CHANNEL_5
#define ADC_COL6_CH              ADC_CHANNEL_6
#define ADC_COL7_CH              ADC_CHANNEL_7
#define ADC_COL8_CH              ADC_CHANNEL_8
#define ADC_COL9_CH              ADC_CHANNEL_9
#define ADC_COL10_CH             ADC_CHANNEL_10
#define ADC_COL11_CH             ADC_CHANNEL_11
#define ADC_COL12_CH             ADC_CHANNEL_12
#define ADC_COL13_CH             ADC_CHANNEL_13

// ADC 配置参数
#define ADC_RESOLUTION           ADC_RESOLUTION_12B      // 12位分辨率
#define ADC_SAMPLETIME           ADC_SAMPLETIME_28CYCLES_5  // 采样时间
#define ADC_CLOCK_DIV            RCC_ADCPCLK2_DIV8      // ADC 时钟分频

// ==========================================================
//  WS2812 LED 配置 (SPI DMA)
// ==========================================================
#define LED_EN_PIN               GPIO_PIN_14    // LED 使能引脚
#define LED_EN_PORT              GPIOB
#define LED_DAT_PIN              GPIO_PIN_15    // LED 数据引脚 (SPI2_MOSI)
#define LED_DAT_PORT             GPIOB
#define LED_DAT_AF               GPIO_AF3_SPI2  // 复用功能

#define LED_SPI_INSTANCE         SPI2                     // SPI 外设
#define LED_DMA_CHANNEL          DMA1_Channel2            // DMA 通道

// ==========================================================
//  调试串口配置  TXPA9 AF2
// ==========================================================
#define DEBUG_USART_INSTANCE     USART1          // 调试串口外设
#define DEBUG_USART_BAUDRATE     115200          // 默认波特率

#define DEBUG_USART_TX_PIN       GPIO_PIN_9      // TX 引脚
#define DEBUG_USART_TX_PORT      GPIOA
#define DEBUG_USART_TX_AF        GPIO_AF2_USART1

#define DEBUG_USART_RX_PIN       GPIO_PIN_10     // RX 引脚
#define DEBUG_USART_RX_PORT      GPIOA
#define DEBUG_USART_RX_AF        GPIO_AF2_USART1

#define DEBUG_USART_IRQ          USART1_IRQn
#define DEBUG_USART_IRQHandler   USART1_IRQHandler

// ==========================================================
//  任务定时器配置
// ==========================================================
#define TASK_TIM_INSTANCE        TIM6            // 任务调度定时器
#define TASK_TIM_IRQ             TIM6_IRQn
#define TASK_TIM_IRQHandler      TIM6_IRQHandler
#define TASK_TIM_PRESCALER       (1000 - 1)     // 预分频
#define TASK_TIM_PERIOD          (SystemCoreClock / 1000000 - 1)  // 周期

// ==========================================================
//  时钟使能宏定义
// ==========================================================
#define RCC_ROW_PORT_CLK_ENABLE()    __HAL_RCC_GPIOC_CLK_ENABLE()
#define RCC_ADC_PORTA_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define RCC_ADC_PORTB_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()
#define RCC_ADC_PORTC_CLK_ENABLE()   __HAL_RCC_GPIOC_CLK_ENABLE()
#define RCC_ADC_CLK_ENABLE()         __HAL_RCC_ADC1_CLK_ENABLE()
#define RCC_DMA_CLK_ENABLE()         __HAL_RCC_DMA1_CLK_ENABLE()
#define RCC_SPI2_CLK_ENABLE()        __HAL_RCC_SPI2_CLK_ENABLE()
#define RCC_USART1_CLK_ENABLE()      __HAL_RCC_USART1_CLK_ENABLE()
#define RCC_TIM6_CLK_ENABLE()        __HAL_RCC_TIM6_CLK_ENABLE()

#endif
