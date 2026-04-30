#include "main.h"
#include "bsp_config.h"
#include "lib_ws2812.h"
#include "usb_config.h"
#include "task.h"
#include "App.h"
#include <stdlib.h> // 必须包含 abs 函数
static void APP_SystemClockConfig(void);
static void APP_USBInit(void);
#if 1

/* --- 变量定义 --- */
ADC_HandleTypeDef AdcHandle;
DMA_HandleTypeDef HdmaCh1;

/* --- 1. 常量与配置定义 --- */
#define ROW_COUNT 5
#define COL_COUNT 14
volatile uint8_t g_current_row = 0;           // 当前行
volatile uint8_t g_scan_complete = 0;         // 61按键扫描完毕的标志
volatile uint16_t gADCxConvertedData[14];     // 14路adc的数值
volatile uint16_t g_adc_raw_col[5][14] = {0}; // 存61路adc的数值
volatile uint8_t g_scan_round = 0;            // 当前扫描的轮次数 (0, 1, 2)
uint16_t g_adc_filtered[5][14] = {0};         // 存放计算平均值后的新数组


///* --- 按键逻辑定义 --- */
// #define RT_SENSITIVITY 30
// #define PRESS_DEADBAND 80

// typedef struct {
//     uint16_t idle_adc;//校准值
//     uint16_t cur_dac; //当前值
//     int16_t max_offset;
//     int16_t min_offset;
//     uint8_t is_pressed;
// } Key_t;

// Key_t keys[5][14];
// 定义参数


#define SCAN_ROUNDS  3  // 运行时滤波
#define CALIB_ROUNDS 16 // 校准时滤波

// 按键的结构体
typedef struct {
    // 配置参数
    uint16_t idele_adc; // 空闲adc数值

    uint16_t actuation_point; // 触发行程的阈值
    uint16_t rt_press_sens;   // 按下的灵敏度
    uint16_t rt_release_sens; // 抬起的灵敏度
    uint16_t top_deadzone;    // 顶部死区
    uint16_t bottom_deadzone; // 底部死区

    // 运行是状态
    uint16_t max_offset; // 按下峰值
    uint16_t min_offset; // 抬起谷值
    uint8_t is_pressed;  // 逻辑开关判断
    uint8_t in_rt_cycle; // 激活的Rt判断

} Key_t;

// 定义全局的按键数值
Key_t keys[5][14] = {0};


////////////////////////////////////////////////////////////bsp层初始化/////////////////////////////////////////////////

void GPIO_Config(void) {
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
    GPIO_InitStruct.Pin =
        GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    // 3. 配置 PC0 - PC3
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void APP_AdcConfig(void) {
    ADC_ChannelConfTypeDef sConfig = {0};
    __HAL_RCC_ADC1_CLK_ENABLE();
    // 配置 ADC 外设时钟
    RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInit = {0};
    RCC_PeriphCLKInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    RCC_PeriphCLKInit.AdcClockSelection = RCC_ADCPCLK2_DIV12;
    HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInit);
    AdcHandle.Instance = ADC1;
    AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
    AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    AdcHandle.Init.ScanConvMode = ADC_SCAN_ENABLE;
    AdcHandle.Init.ContinuousConvMode = DISABLE;
    AdcHandle.Init.NbrOfConversion = 14;
    AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;

    HAL_ADC_Init(&AdcHandle);
    uint32_t channel_map[14] = {
        ADC_CHANNEL_0,  ADC_CHANNEL_1,  ADC_CHANNEL_2,  ADC_CHANNEL_3, // PA0, PA1, PA2, PA3
        ADC_CHANNEL_4,  ADC_CHANNEL_5,  ADC_CHANNEL_6,  ADC_CHANNEL_7, // PA4, PA5, PA6, PA7
        ADC_CHANNEL_8,  ADC_CHANNEL_9,                                 // PB0, PB1
        ADC_CHANNEL_10, ADC_CHANNEL_11, ADC_CHANNEL_12, ADC_CHANNEL_13 // PC0, PC1, PC2, PC3
    };
    // 3. 循环配置 14 个 Rank
    sConfig.SamplingTime = ADC_SAMPLETIME_5CYCLES_5; // 统一采用 28.5 周期，平衡速度和精度
    for (uint8_t i = 0; i < 14; i++) {
        sConfig.Channel = channel_map[i];
        sConfig.Rank = i + 1;
        HAL_ADC_ConfigChannel(&AdcHandle, &sConfig);
    }
    // adc的校准
    HAL_ADCEx_Calibration_Start(&AdcHandle);
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc) {
    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    HdmaCh1.Instance = DMA1_Channel1;
    HdmaCh1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    HdmaCh1.Init.PeriphInc = DMA_PINC_DISABLE;
    HdmaCh1.Init.MemInc = DMA_MINC_ENABLE;
    HdmaCh1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    HdmaCh1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    HdmaCh1.Init.Mode = DMA_NORMAL;
    HdmaCh1.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    HAL_DMA_DeInit(&HdmaCh1);
    HAL_DMA_Init(&HdmaCh1);
    HAL_DMA_ChannelMap(&HdmaCh1, DMA_CHANNEL_MAP_ADC1);
    __HAL_LINKDMA(hadc, DMA_Handle, HdmaCh1);
    // 开启dma的中断
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 1, 0); // 设置优先级，数字越小优先级越高
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);         // 开启 DMA1 通道1 的中断响应
}
/* --- 业务逻辑 --- */
static void select_row(uint8_t index) {
    SET_IO(GPIOA, GPIO_PIN_8); // 高电平
    SET_IO(GPIOC, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
    Bsp_Delay_Us(50);
    if (index == 0) {
        CLR_IO(GPIOA, GPIO_PIN_8);
    } else if (index == 1) {
        CLR_IO(GPIOC, GPIO_PIN_9);
    } else if (index == 2) {
        CLR_IO(GPIOC, GPIO_PIN_8);
    } else if (index == 3) {
        CLR_IO(GPIOC, GPIO_PIN_7);
    } else if (index == 4) {
        CLR_IO(GPIOC, GPIO_PIN_6);
    }


    //    switch (index) {
    //        case 0: CLR_IO(GPIOA, GPIO_PIN_8); break; //低电平
    //        case 1: CLR_IO(GPIOC, GPIO_PIN_9); break;
    //        case 2: CLR_IO(GPIOC, GPIO_PIN_8); break;
    //        case 3: CLR_IO(GPIOC, GPIO_PIN_7); break;
    //        case 4: CLR_IO(GPIOC, GPIO_PIN_6); break;
    //    }
}

// void process_key_scan(uint8_t r, uint8_t c, uint16_t raw_adc) {
//     Key_t* k = &keys[r][c];
//     int16_t current_offset = abs((int16_t)k->idle_adc - (int16_t)raw_adc);

//    if (!k->is_pressed) {
//        if (current_offset < k->min_offset) k->min_offset = current_offset;
//        if (current_offset > k->min_offset + RT_SENSITIVITY && current_offset > PRESS_DEADBAND) {
//            k->is_pressed = 1;
//            k->max_offset = current_offset;
//            //printf("R%d-C%d Press! Offset:%d\r\n", r, c, current_offset);
//        }
//    } else {
//        if (current_offset > k->max_offset) k->max_offset = current_offset;
//        if (current_offset < k->max_offset - RT_SENSITIVITY) {
//            k->is_pressed = 0;
//            k->min_offset = current_offset;
//            //printf("R%d-C%d Up! Offset:%d\r\n", r, c, current_offset);
//        }
//        if (current_offset < PRESS_DEADBAND - 20) {
//            k->is_pressed = 0;
//            k->min_offset = current_offset;
//        }
//    }
//}

#endif
void test() {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);

    HAL_ADC_Start_DMA(&AdcHandle, (uint32_t *)gADCxConvertedData, 14);

    HAL_ADC_Stop_DMA(&AdcHandle);
    while (!__HAL_DMA_GET_FLAG(&HdmaCh1, DMA_ISR_TCIF1))
        ;
    /* Clear DMA Complete Flag */
    __HAL_DMA_CLEAR_FLAG(&HdmaCh1, DMA_IFCR_CTCIF1);
    // 4. 搬运完成，立刻拉低 PA5
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
}

void test2() {
    // --- 开始测试 ---
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET); // 1. 引脚拉高

    HAL_ADC_Start_DMA(&AdcHandle, (uint32_t *)gADCxConvertedData, 14);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET); // 2. 搬运完成，立刻拉低
    // 此时 ADC 正在转换，DMA 正在后台搬运
    while (!__HAL_DMA_GET_FLAG(&HdmaCh1, DMA_ISR_TCIF1))
        ;


    // --- 结束测试 ---

    /* 后续处理 */
    __HAL_DMA_CLEAR_FLAG(&HdmaCh1, DMA_IFCR_CTCIF1);
    HAL_ADC_Stop_DMA(&AdcHandle);

    // 后面再接 printf 打印，printf 的时间千万不要计入引脚拉高期间
    for (int i = 0; i < 14; i++) {
        printf("%u ", gADCxConvertedData[i]);
    }
    printf("\n");

    HAL_Delay(100);
}
///////寄存器快速配置
#define ADC_DMA1_CH1_ALL_FLAGS (DMA_IFCR_CGIF1 | DMA_IFCR_CTCIF1 | DMA_IFCR_CHTIF1 | DMA_IFCR_CTEIF1)
static void adc_dma_fast_init(void) {
    ADC1->CR2 |= ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_DMA | ADC_CR2_EXTTRIG;

    DMA1_Channel1->CCR &= ~DMA_CCR_EN;
    DMA1_Channel1->CPAR = (uint32_t)&ADC1->DR;
    DMA1_Channel1->CMAR = (uint32_t)gADCxConvertedData;
    DMA1_Channel1->CNDTR = 14;
    DMA1_Channel1->CCR = DMA_CCR_MINC | DMA_CCR_PSIZE_0 | DMA_CCR_MSIZE_0 | DMA_CCR_PL;
    DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS;
}
// 寄存器方式阻塞搬运
void adc_dma_start(void) {
    DMA1_Channel1->CCR &= ~DMA_CCR_EN;                  // 关闭dma的通道
    DMA1_Channel1->CMAR = (uint32_t)gADCxConvertedData; // 设置目标地址
    DMA1_Channel1->CNDTR = 14;                          // 14个通道
    DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS;                // 清除中断

    ADC1->SR = ~(ADC_SR_EOC | ADC_SR_STRT); // 清除 ADC 历史状态标志
    DMA1_Channel1->CCR |= DMA_CCR_EN;       // DMA1_Channel1->CCR |= DMA_CCR_EN;
    ADC1->CR2 |= ADC_CR2_SWSTART;           // 正式触发 ADC 启动转换。

    while ((DMA1->ISR & DMA_ISR_TCIF1) == 0U) {
    }

    DMA1_Channel1->CCR &= ~DMA_CCR_EN;
    DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS;
}


///////////////////////非阻塞方式///////////////////////////////
void adc_dma_start_it() {
    DMA1_Channel1->CCR &= ~DMA_CCR_EN;                  // 关闭dma的通道
    DMA1_Channel1->CMAR = (uint32_t)gADCxConvertedData; // 设置目标地址
    DMA1_Channel1->CNDTR = 14;                          // 14个通道
    DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS;                // 清除中断
    ADC1->SR = ~(ADC_SR_EOC | ADC_SR_STRT);             // 清除 ADC 历史状态标志

    // 开启传输完成中断 (TCIE)
    DMA1_Channel1->CCR |= (DMA_CCR_TCIE | DMA_CCR_EN);
    ADC1->CR2 |= ADC_CR2_SWSTART; // 触发ADC启动
}

#define ROW_ALL_OFF()  SET_IO(GPIOA, GPIO_PIN_8);SET_IO(GPIOC, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9)

// dma的中断服务函数
void DMA1_Channel1_IRQHandler(void) {
    if (DMA1->ISR & DMA_ISR_TCIF1) {
        // 清除中断标志位
        DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS;
        DMA1_Channel1->CCR &= ~DMA_CCR_EN;

        ROW_ALL_OFF();
        // 2.将采集到的14路adc放到
        for (uint8_t c = 0; c < 14; c++) {
            g_adc_raw_col[g_current_row][c] += gADCxConvertedData[c];
        }

        // 递增行
        g_current_row++;
        Bsp_Delay_Us(20);
        if (g_current_row < 5) {
            // 切换下一行
            if (g_current_row == 0) {
                CLR_IO(GPIOA, GPIO_PIN_8);
            } else if (g_current_row == 1) {
                CLR_IO(GPIOC, GPIO_PIN_9);
            } else if (g_current_row == 2) {
                CLR_IO(GPIOC, GPIO_PIN_8);
            } else if (g_current_row == 3) {
                CLR_IO(GPIOC, GPIO_PIN_7);
            } else if (g_current_row == 4) {
                CLR_IO(GPIOC, GPIO_PIN_6);
            }
            // us及延时
            Bsp_Delay_Us(10);
            adc_dma_start_it();

        } else {
            // 扫描完毕
            g_current_row = 0;
            g_scan_round++;
            Bsp_Delay_Us(20);

            // 三次判断
            if (g_scan_round < 3) {
                if (g_current_row == 0) {
                    CLR_IO(GPIOA, GPIO_PIN_8);
                } else if (g_current_row == 1) {
                    CLR_IO(GPIOC, GPIO_PIN_9);
                } else if (g_current_row == 2) {
                    CLR_IO(GPIOC, GPIO_PIN_8);
                } else if (g_current_row == 3) {
                    CLR_IO(GPIOC, GPIO_PIN_7);
                } else if (g_current_row == 4) {
                    CLR_IO(GPIOC, GPIO_PIN_6);
                }
                // 标志位1
                //   g_scan_complete=1;
                Bsp_Delay_Us(10);
                adc_dma_start_it();
            } else {
                g_scan_complete = 1; // 通知 main 循环处理数据
            }
        }
    }
}


////dma的中断服务函数
// void DMA1_Channel1_IRQHandler(void){
//	 SET_IO(GPIOA,GPIO_PIN_9);
//	if(DMA1->ISR & DMA_ISR_TCIF1){
//
//	   //清除中断标志位
//		 DMA1->IFCR=ADC_DMA1_CH1_ALL_FLAGS;
//	   DMA1_Channel1->CCR &= ~DMA_CCR_EN;
//		 //2.将采集到的14路adc放到
//		 for(uint8_t c=0;c<14;c++){
//		    g_adc_raw_col[g_current_row][c]=gADCxConvertedData[c];
//		 }
//		 //递增行
//		 g_current_row++;
//		 if(g_current_row<5){
//		    //切换下一行
//			  select_row(g_current_row);
//			  //us及延时
//			  Bsp_Delay_Us(500);
//			  adc_dma_start_it();
//
//		 }else{ //扫描完毕
//		    g_current_row=0;
//			 select_row(g_current_row);
//			 //标志位1
//			//  g_scan_complete=1;
//			 	  Bsp_Delay_Us(500);
//			 adc_dma_start_it();
//
//		 }
//
//	}
//
//    CLR_IO(GPIOA,GPIO_PIN_9);
// }
////////////////////////////////////////////////lib层///////////////////////////////////
extern volatile uint32_t g_cnt;


// 对应 61 颗按键的灯位图
// 255 表示该位置没有按键，也没有灯
const uint8_t led_index_map[5][14] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},                // Row 0: 0-13
    {14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27},      // Row 1: 14-27
    {28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 255, 40},     // Row 2: [12]是空, 13是第40颗灯
    {41, 255, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 255, 52},    // Row 3: [1],[12]空
    {53, 54, 55, 255, 255, 255, 56, 255, 255, 255, 57, 58, 59, 60} // Row 4: 底部
};

uint16_t get_led_index(uint8_t r, uint8_t c) {
    if (r >= 5 || c >= 14)
        return 0xFFFF; // 越界保护

    uint8_t idx = led_index_map[r][c];
    if (idx == 255)
        return 0xFFFF; // 返回无效索引

    return (uint16_t)idx;
}

// 按键实现逻辑 RT 死区，以及触发点
uint8_t process_key_logic(Key_t *k, uint16_t cur_adc) {
    // 计算当前偏移量,行程
    int16_t offset = (int16_t)k->idele_adc - cur_adc;
    if (offset <= 0) {
        offset = 0;
    }
    // 判断顶部死区
    if (offset < k->top_deadzone) {
        k->is_pressed = 0;  // 没有按压
        k->in_rt_cycle = 0; // 没有激活RT
        k->max_offset = 0;
        k->min_offset = 0;
        return 0;
    }
    // 判断底部死区
    if (offset > k->bottom_deadzone) {
        offset = k->bottom_deadzone;
    }

    // 动态判断RT和AP的状态机
    if (!k->is_pressed) {
        // 没有按下-》按下
        if (offset < k->min_offset) {
            k->min_offset = offset;
        }
        // 计算当前的触发
        uint16_t trigger_line = k->in_rt_cycle ? (k->min_offset + k->rt_press_sens) : (k->actuation_point);
        // 判断是否按下
        if (offset >= trigger_line) {
            k->is_pressed = 1;
            k->in_rt_cycle = 1; // 激活RT
            k->max_offset = offset;
        }

    } else {
        // 当前状态是：已经按下-》尝试断开
        if (offset > k->max_offset) {
            k->max_offset = offset;
        }
        // 计算当前断开的阈值  最高点-抬起灵敏度
        uint16_t release_line = k->max_offset - (k->rt_release_sens);

        if (offset <= release_line) {
            k->is_pressed = 0;
            k->min_offset = offset;
        }
    }
    return k->is_pressed;
}
// 获取 idle_adc 并初始化行程参数
void key_init_calibration(void) {
    g_scan_complete = 0;
    g_scan_round = 0;
    g_current_row = 0;
    select_row(0);
    adc_dma_start_it(); // 开启搬运数据  //3次滤波
    while (!g_scan_complete) {
        ;
    }
    for (uint8_t r = 0; r < 5; r++) {
        for (uint8_t c = 0; c < 14; c++) {
            g_adc_filtered[r][c] = g_adc_raw_col[r][c] / 3;
            g_adc_raw_col[r][c] = 0; // 及时清零累加器
        }
    }
    // 写入初始按钮的参数值

    for (uint8_t r = 0; r < 5; r++) {
        for (uint8_t c = 0; c < 14; c++) {
            // 按钮的空闲adc数值
            keys[r][c].idele_adc = g_adc_filtered[r][c];
            // 默认磁轴参数
            keys[r][c].actuation_point = 500;
            keys[r][c].top_deadzone = 60;
            keys[r][c].bottom_deadzone = 880;
            keys[r][c].rt_press_sens = 40;
            keys[r][c].rt_release_sens = 40;


            keys[r][c].is_pressed = 0;
            keys[r][c].in_rt_cycle = 0;
            keys[r][c].max_offset = 0;
            keys[r][c].min_offset = 0;
        }
    }

    // 4. 校准彻底结束，把状态重置为 0，准备进入 main 循环
    g_scan_complete = 0;
    g_scan_round = 0;
    g_current_row = 0;
    select_row(0);
    Bsp_Delay_Us(50);   // 这里延时也建议调大到 50us 提高稳定性
    adc_dma_start_it(); // 重启中断链
    printf("All Keys Configured. Base ADC[0,0]:%d\r\n", keys[0][0].idele_adc);
}

const uint8_t key_mask[5][14] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // ??0?У???? (14??)
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // ??1?У???? (14??)
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1}, // ??2?У?[12]???? (13??)
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1}, // ??3?У?[1]??[12]???? (12??)
    {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1}  // ??4?У??????????λ (8??)
};


uint8_t data_cl[2] = {0};
int main(void) {
    HAL_Init();
    APP_SystemClockConfig();

    //////timer初始化
    bsp_tim_init();
    bsp_usart_init(115200);
    ////////ws2812初始化
    bsp_spi_dma_init();
    lib_ws2812_init();


    // APP_USBInit();
    //  ///////////adc
    GPIO_Config();
    APP_AdcConfig();


    adc_dma_fast_init();

    // --- 关键：手动启动第一轮扫描的第 0 行 ---
    key_init_calibration();
    printf("init_success");

    // adc_keys_initscan();
    //	  uint32_t  cur_cnt=0;
    //	  g_current_row = 0;
    //    g_scan_complete = 0;
    //    select_row(0);
    //    Bsp_Delay_Us(20);
    //    adc_dma_start_it();
    //    printf("init_success");

    while (1) {
        if (g_scan_complete == 1) {
            for (uint8_t r = 0; r < 5; r++) {
                for (uint8_t c = 0; c < 14; c++) {
                    if (key_mask[r][c] == 0)
                        continue;
                    // 1. 直接除以 3 求平均值
                    uint16_t cur_avg_adc = g_adc_raw_col[r][c] / 3;
                    // 清零累加器，为下一波的3次扫描做准备！
                    g_adc_raw_col[r][c] = 0;


                    uint8_t last_state = keys[r][c].is_pressed;
                    // 执行逻辑判断
                    uint8_t cur_state = process_key_logic(&keys[r][c], cur_avg_adc);
                    if (last_state != cur_state) {
                        last_state = cur_state;
                        if (cur_state == 1) {
                            data_cl[0] = r;
                            data_cl[1] = c;
                        }
                    }
                }


                // 4. 重置状态，重新开启下一波扫描
                g_scan_complete = 0; // 清除完成标志
                g_scan_round = 0;    // 轮次归零
                g_current_row = 0;   // 行号归零

                select_row(0);      // 重新选中第一行
                Bsp_Delay_Us(20);   // 必须延时，确保电压稳定
                adc_dma_start_it(); // 启动 DMA，开启新的一波中断
            }
        }
    }
}


static void APP_USBInit(void) {
    // 初始化USB时钟
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    SET_BIT(RCC->CFGR1, RCC_CFGR1_USBSELHSI48_Msk);
    __HAL_RCC_USB_CLK_ENABLE();

    hid_keyboard_init();

    /* Enable USB interrupt */
    NVIC_EnableIRQ(USBD_IRQn);
}


static void APP_SystemClockConfig(void) {
    RCC_OscInitTypeDef OscInitstruct = {0};
    RCC_ClkInitTypeDef ClkInitstruct = {0};

    OscInitstruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE |
                                   RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSI48M;
    OscInitstruct.HSEState = RCC_HSE_ON;
    OscInitstruct.HSEFreq = RCC_HSE_8_16MHz;
    OscInitstruct.HSI48MState = RCC_HSI48M_ON;
    OscInitstruct.HSIState = RCC_HSI_ON;
    OscInitstruct.LSEState = RCC_LSE_OFF;
    OscInitstruct.LSEDriver = RCC_LSEDRIVE_HIGH;
    OscInitstruct.LSIState = RCC_LSI_OFF;
    OscInitstruct.PLL.PLLState = RCC_PLL_ON;
    OscInitstruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    OscInitstruct.PLL.PLLMUL = RCC_CFGR_PLLMULL18;
    if (HAL_RCC_OscConfig(&OscInitstruct) != HAL_OK) {
        APP_ErrorHandler();
    }

    ClkInitstruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    ClkInitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    ClkInitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    ClkInitstruct.APB1CLKDivider = RCC_HCLK_DIV1;
    ClkInitstruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&ClkInitstruct, FLASH_LATENCY_6) != HAL_OK) {
        APP_ErrorHandler();
    }
}

void APP_ErrorHandler(void) {
    while (1) {
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {
    while (1) {
    }
}
#endif /* USE_FULL_ASSERT */
