#include "lib_hall_sensor.h"
#include "bsp_delay.h"

/* --- 全局变量 --- */
volatile uint8_t  g_current_row = 0;    // 当前扫描行 (0-4)
volatile uint8_t  g_scan_round = 0;     // 当前轮次 (0-2)
volatile uint8_t  g_scan_complete = 0;  // 一波扫描完成标志

uint16_t g_adc_raw_col[ROW_COUNT][COL_COUNT] = {0};    // 原始累加缓冲区

Key_t keys[ROW_COUNT][COL_COUNT];

const uint8_t key_mask[ROW_COUNT][COL_COUNT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1}
};

/* --- 硬件底层驱动 --- */

void ROW_ALL_OFF(void) {
    SET_IO(GPIOA, GPIO_PIN_8);
    SET_IO(GPIOC, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
}

void select_row(uint8_t index) {
    ROW_ALL_OFF();
    switch(index) {
        case 0: CLR_IO(GPIOA, GPIO_PIN_8); break;
        case 1: CLR_IO(GPIOC, GPIO_PIN_9); break;
        case 2: CLR_IO(GPIOC, GPIO_PIN_8); break;
        case 3: CLR_IO(GPIOC, GPIO_PIN_7); break;
        case 4: CLR_IO(GPIOC, GPIO_PIN_6); break;
    }
}

/* --- 业务逻辑 --- */

uint8_t process_key_logic(Key_t* k, uint16_t cur_adc) {
    // 1. 计算偏移量（防止负数溢出）
    int32_t diff = (int32_t)k->idele_adc - (int32_t)cur_adc;
    int16_t offset = (diff > 0) ? (int16_t)diff : 0;

    // 2. 顶部死区判断
    if (offset < k->top_deadzone) {
        k->is_pressed = 0;
        k->in_rt_cycle = 0;
        k->max_offset = 0;
        k->min_offset = 0;
        return 0;
    }

    // 3. 底部死区限制
    if (offset > k->bottom_deadzone) offset = k->bottom_deadzone;

    // 4. RT 与 AP 逻辑状态机
    if (!k->is_pressed) {
        if (offset < k->min_offset) k->min_offset = offset;
        uint16_t trigger_line = k->in_rt_cycle ? (k->min_offset + k->rt_press_sens) : k->actuation_point;
        if (offset >= trigger_line) {
            k->is_pressed = 1;
            k->in_rt_cycle = 1;
            k->max_offset = offset;
        }
    } else {
        if (offset > k->max_offset) k->max_offset = offset;
        uint16_t release_line = k->max_offset - k->rt_release_sens;
        if (offset <= release_line) {
            k->is_pressed = 0;
            k->min_offset = offset;
        }
    }
    return k->is_pressed;
}

void lib_hall_sensor_init(void) {
    // 1. 初始化 GPIO (由 main.c 中的 GPIO_Config 移过来，但也可以调用 bsp_gpio.c 中的函数)
    // 这里保持原样逻辑，直接在 lib 中初始化需要的 GPIO
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 配置行扫描：PC6-9, PA8
    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 配置列模拟输入：// PA0-PA7(8) + PB0-PB1(2) + PC0-PC3(4) = 14
    GPIO_InitStruct.Pin =  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_InitStruct.Pin  = GPIO_PIN_0 | GPIO_PIN_1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    // 3. 配置 PC0 - PC3
    GPIO_InitStruct.Pin  = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // 2. 初始化 ADC DMA
    bsp_adc_dma_init();
}

void lib_hall_sensor_calibration(void) {
    printf("Calibration Start...\r\n");
    g_scan_complete = 0;
    g_scan_round = 0;
    g_current_row = 0;
    memset(g_adc_raw_col, 0, sizeof(g_adc_raw_col));

    select_row(0);
    Bsp_Delay_Us(100); // 校准给更长稳定时间
    bsp_adc_dma_start();

    while(!g_scan_complete); // 等待三轮扫完

    for(uint8_t r = 0; r < ROW_COUNT; r++) {
        for(uint8_t c = 0; c < COL_COUNT; c++) {
            keys[r][c].idele_adc = g_adc_raw_col[r][c] / SCAN_ROUNDS;
            g_adc_raw_col[r][c] = 0; // 必须清零累加器！
            
            keys[r][c].actuation_point = 350;
            keys[r][c].top_deadzone = 80;
            keys[r][c].bottom_deadzone = 1050;
            keys[r][c].rt_press_sens = 50;
            keys[r][c].rt_release_sens = 50;
            keys[r][c].is_pressed = 0;
        }
    }
    
    // 关键复位：确保 main 启动正常
    g_scan_complete = 0;
    g_scan_round = 0;
    g_current_row = 0;
    printf("Calibration OK!\r\n");
}

void lib_hall_sensor_task(void) {
    if (g_scan_complete == 1) {
        for(uint8_t r = 0; r < ROW_COUNT; r++) {
            for (uint8_t c = 0; c < COL_COUNT; c++) {
                if (key_mask[r][c] == 0) {
                    g_adc_raw_col[r][c] = 0;
                    continue;
                }

                uint16_t avg_adc = g_adc_raw_col[r][c] / SCAN_ROUNDS;
                g_adc_raw_col[r][c] = 0; // 处理完即清零

                Key_t *k = &keys[r][c];
                uint8_t old_s = k->is_pressed;
                process_key_logic(k, avg_adc);

                // 只有状态变化才处理灯光或串口
                if (old_s != k->is_pressed) {
                    if (k->is_pressed) {
                        printf("P[%d,%d] ADC:%d\r\n", r, c, avg_adc);
                    } else {
                        printf("R[%d,%d]\r\n", r, c);
                    }
                }
            }
        }

        // 3. 一波逻辑处理结束，重启新的一波扫描
        g_scan_complete = 0;
        g_scan_round = 0;
        g_current_row = 0;
        select_row(0);
        Bsp_Delay_Us(SETTLING_TIME_US);
        bsp_adc_dma_start();
    }
}

// 核心中断：链式触发逻辑
#define ADC_DMA1_CH1_ALL_FLAGS (DMA_IFCR_CGIF1 | DMA_IFCR_CTCIF1 | DMA_IFCR_CHTIF1 | DMA_IFCR_CTEIF1)
void DMA1_Channel1_IRQHandler(void) {
    if(DMA1->ISR & DMA_ISR_TCIF1) {
        DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS;
        DMA1_Channel1->CCR &= ~DMA_CCR_EN;

        // 1. 数据累加
        for(uint8_t c = 0; c < COL_COUNT; c++) {
            g_adc_raw_col[g_current_row][c] += gADCxConvertedData[c];
        }

        // 2. 状态机：切换行或轮次
        g_current_row++;
        if(g_current_row < ROW_COUNT) {
            select_row(g_current_row);
            Bsp_Delay_Us(SETTLING_TIME_US);
            bsp_adc_dma_start();
        } else {
            g_current_row = 0;
            g_scan_round++;
            if(g_scan_round < SCAN_ROUNDS) {
                select_row(0);
                Bsp_Delay_Us(SETTLING_TIME_US);
                bsp_adc_dma_start();
            } else {
                g_scan_complete = 1; // 标记扫描全结束，等待 task 处理
            }
        }
    }
}