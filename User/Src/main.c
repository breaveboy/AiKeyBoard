#include "main.h"
#include "bsp_config.h"

#include "usb_config.h"


#include <string.h>
static void APP_SystemClockConfig(void);
/* --- 宏定义与配置 --- */
#define ROW_COUNT          5
#define COL_COUNT          14
#define SCAN_ROUNDS        3      // 运行时每波扫描3次取平均
#define SETTLING_TIME_US   50     // 行切换后等待电压稳定的时间

/* --- 全局变量 --- */
ADC_HandleTypeDef AdcHandle;
DMA_HandleTypeDef HdmaCh1;

volatile uint8_t  g_current_row = 0;    // 当前扫描行 (0-4)
volatile uint8_t  g_scan_round = 0;     // 当前轮次 (0-2)
volatile uint8_t  g_scan_complete = 0;  // 一波扫描完成标志

uint16_t gADCxConvertedData[14];        // DMA 直接搬运的目标（14路）
uint16_t g_adc_raw_col[5][14] = {0};    // 原始累加缓冲区

/* --- 逻辑结构体 --- */
typedef struct {
    uint16_t idele_adc;       // 校准基准值
    uint16_t actuation_point; // AP点
    uint16_t rt_press_sens;   // RT按下灵敏度
    uint16_t rt_release_sens; // RT抬起灵敏度
    uint16_t top_deadzone;    // 顶部死区
    uint16_t bottom_deadzone; // 底部死区
    
    uint16_t max_offset;      // 按下过程中的最高点
    uint16_t min_offset;      // 抬起过程中的最低点
    uint8_t  is_pressed;      // 逻辑按下状态
    uint8_t  in_rt_cycle;     // 是否进入RT激活状态
} Key_t;

Key_t keys[5][14];

/* --- 掩码与灯效索引 --- */
const uint8_t key_mask[5][14] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1}
};

const uint8_t led_map[5][14] = {
    {0,1,2,3,4,5,6,7,8,9,10,11,12,13},
    {14,15,16,17,18,19,20,21,22,23,24,25,26,27},
    {28,29,30,31,32,33,34,35,36,37,38,39,255,40},
    {41,255,42,43,44,45,46,47,48,49,50,51,255,52},
    {53,54,55,255,255,255,56,255,255,255,57,58,59,60}
};
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
    GPIO_InitStruct.Pin =  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_InitStruct.Pin  = GPIO_PIN_0 | GPIO_PIN_1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    // 3. 配置 PC0 - PC3
    GPIO_InitStruct.Pin  = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
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
        ADC_CHANNEL_0, ADC_CHANNEL_1, ADC_CHANNEL_2, ADC_CHANNEL_3, // PA0, PA1, PA2, PA3
        ADC_CHANNEL_4, ADC_CHANNEL_5, ADC_CHANNEL_6, ADC_CHANNEL_7, // PA4, PA5, PA6, PA7
        ADC_CHANNEL_8, ADC_CHANNEL_9,                               // PB0, PB1
        ADC_CHANNEL_10, ADC_CHANNEL_11, ADC_CHANNEL_12, ADC_CHANNEL_13 // PC0, PC1, PC2, PC3
    };
     // 3. 循环配置 14 个 Rank
    sConfig.SamplingTime = ADC_SAMPLETIME_5CYCLES_5; // 统一采用 28.5 周期，平衡速度和精度
    for (uint8_t i = 0; i < 14; i++)
    {
       sConfig.Channel = channel_map[i];
       sConfig.Rank = i+1;
       HAL_ADC_ConfigChannel(&AdcHandle, &sConfig);
    }
		//adc的校准
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
	  //开启dma的中断
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 1, 0); // 设置优先级，数字越小优先级越高
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);        // 开启 DMA1 通道1 的中断响应
}


#define ADC_DMA1_CH1_ALL_FLAGS (DMA_IFCR_CGIF1 | DMA_IFCR_CTCIF1 | DMA_IFCR_CHTIF1 | DMA_IFCR_CTEIF1)
static void adc_dma_fast_init(void)
{
    ADC1->CR2 |= ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_DMA | ADC_CR2_EXTTRIG;

    DMA1_Channel1->CCR &= ~DMA_CCR_EN;
    DMA1_Channel1->CPAR = (uint32_t)&ADC1->DR;
    DMA1_Channel1->CMAR = (uint32_t)gADCxConvertedData;
    DMA1_Channel1->CNDTR = 14;
    DMA1_Channel1->CCR = DMA_CCR_MINC | DMA_CCR_PSIZE_0 | DMA_CCR_MSIZE_0 | DMA_CCR_PL;
    DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS;
}

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

// 非阻塞启动 DMA 采集
#define ADC_DMA1_CH1_ALL_FLAGS (DMA_IFCR_CGIF1 | DMA_IFCR_CTCIF1 | DMA_IFCR_CHTIF1 | DMA_IFCR_CTEIF1)
void adc_dma_start_it(void) {
    DMA1_Channel1->CCR &= ~DMA_CCR_EN;
    DMA1_Channel1->CMAR = (uint32_t)gADCxConvertedData;
    DMA1_Channel1->CNDTR = 14;
    DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS; // 核心：强制清除上次残留
    ADC1->SR = ~(ADC_SR_EOC | ADC_SR_STRT);
    
    DMA1_Channel1->CCR |= (DMA_CCR_TCIE | DMA_CCR_EN);
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

// 核心中断：链式触发逻辑
void DMA1_Channel1_IRQHandler(void) {
    if(DMA1->ISR & DMA_ISR_TCIF1) {
        DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS;
        DMA1_Channel1->CCR &= ~DMA_CCR_EN;

        // 1. 数据累加
        for(uint8_t c = 0; c < 14; c++) {
            g_adc_raw_col[g_current_row][c] += gADCxConvertedData[c];
        }

        // 2. 状态机：切换行或轮次
        g_current_row++;
        if(g_current_row < 5) {
            select_row(g_current_row);
            Bsp_Delay_Us(SETTLING_TIME_US);
            adc_dma_start_it();
        } else {
            g_current_row = 0;
            g_scan_round++;
            if(g_scan_round < SCAN_ROUNDS) {
                select_row(0);
                Bsp_Delay_Us(SETTLING_TIME_US);
                adc_dma_start_it();
            } else {
                g_scan_complete = 1; // 标记扫描全结束，等待 main 处理
            }
        }
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

void key_init_calibration(void) {
    printf("Calibration Start...\r\n");
    g_scan_complete = 0;
    g_scan_round = 0;
    g_current_row = 0;
    memset(g_adc_raw_col, 0, sizeof(g_adc_raw_col));

    select_row(0);
    Bsp_Delay_Us(100); // 校准给更长稳定时间
    adc_dma_start_it();

    while(!g_scan_complete); // 等待三轮扫完

    for(uint8_t r = 0; r < 5; r++) {
        for(uint8_t c = 0; c < 14; c++) {
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

/* --- 主循环 --- */

int main(void) {
    HAL_Init();
    APP_SystemClockConfig();
   
    bsp_usart_init(115200);
    GPIO_Config();
    APP_AdcConfig();
    adc_dma_fast_init();

    // 1. 系统校准
    key_init_calibration();

    // 2. 第一次“点火”启动运行扫描
    g_scan_complete = 0;
    g_scan_round = 0;
    g_current_row = 0;
    select_row(0);
    Bsp_Delay_Us(SETTLING_TIME_US);
    adc_dma_start_it();

    while (1) {
        if (g_scan_complete == 1) {
            for(uint8_t r = 0; r < 5; r++) {
                for (uint8_t c = 0; c < 14; c++) {
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
            adc_dma_start_it();
        }
    }
}











static void APP_USBInit(void)
{
    //初始化USB时钟
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  SET_BIT(RCC->CFGR1,RCC_CFGR1_USBSELHSI48_Msk);
  __HAL_RCC_USB_CLK_ENABLE();

  hid_keyboard_init();

  /* Enable USB interrupt */
  NVIC_EnableIRQ(USBD_IRQn);
}


static void APP_SystemClockConfig(void)
{
    RCC_OscInitTypeDef  OscInitstruct = {0};
    RCC_ClkInitTypeDef  ClkInitstruct = {0};

    OscInitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE |
                                    RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSI48M;
    OscInitstruct.HSEState        = RCC_HSE_ON;
    OscInitstruct.HSEFreq         = RCC_HSE_8_16MHz;
    OscInitstruct.HSI48MState     = RCC_HSI48M_ON;
    OscInitstruct.HSIState        = RCC_HSI_ON;
    OscInitstruct.LSEState        = RCC_LSE_OFF;
    OscInitstruct.LSEDriver       = RCC_LSEDRIVE_HIGH;
    OscInitstruct.LSIState        = RCC_LSI_OFF;
    OscInitstruct.PLL.PLLState    = RCC_PLL_ON;
    OscInitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
    OscInitstruct.PLL.PLLMUL      = RCC_CFGR_PLLMULL18;
    if (HAL_RCC_OscConfig(&OscInitstruct) != HAL_OK)
    {
        APP_ErrorHandler();
    }

    ClkInitstruct.ClockType       = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    ClkInitstruct.SYSCLKSource    = RCC_SYSCLKSOURCE_PLLCLK;
    ClkInitstruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;
    ClkInitstruct.APB1CLKDivider  = RCC_HCLK_DIV1;
    ClkInitstruct.APB2CLKDivider  = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&ClkInitstruct, FLASH_LATENCY_6) != HAL_OK)
    {
        APP_ErrorHandler();
    }
}

void APP_ErrorHandler(void)
{
    while (1)
    {
    }
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    while (1)
    {
    }
}
#endif /* USE_FULL_ASSERT */
