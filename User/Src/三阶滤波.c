#include "main.h"
#include "bsp_delay.h"
const uint8_t key_mask[5][14] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1}
};

uint8_t keys[255]; // 随便给个大小
void lib_hall_sensor_task(void) {
    // 空函数
}
static void APP_SystemClockConfig(void);
ADC_HandleTypeDef AdcHandle;
DMA_HandleTypeDef HdmaCh1;
uint16_t gADCxConvertedData[14];

volatile uint8_t g_adc_complete = 0; // ADC 采集完成标志位
uint8_t g_current_row = 0;           // 当前正在扫描的行 (0~4)
uint16_t filtered_data[5][14];           // 存整个键盘 5x14 的纯净数据



// ==========================================
// 3. 三级滤波算法配置与核心变量
// ==========================================
#define COL_NUM 14
#define EMA_SHIFT 3             // 滤波系数：值越大越平滑，延迟也略高 (建议 2, 3, 4)
#define HYSTERESIS_DEADZONE 4   // 死区阈值：屏蔽静止时的底噪跳动 (建议 3~6)

static uint16_t raw_history[5][14][3] = {0}; 
static uint32_t ema_accumulator[5][14] = {0}; 
static uint16_t logical_output[5][14] = {0};  

// --- 算法一：快速中值滤波 (取3个数的中间值) ---
static inline uint16_t fast_median(uint16_t a, uint16_t b, uint16_t c) {
    uint16_t tmp;
    if (a > b) { tmp = a; a = b; b = tmp; }
    if (b > c) { tmp = b; b = c; c = tmp; }
    if (a > b) { tmp = a; a = b; b = tmp; }
    return b;
}

// --- 核心：处理单列通道的数据 ---
uint16_t process_hall_filter(uint8_t row, uint8_t col, uint16_t new_raw) {
    // 1. 三阶中值滤波
    raw_history[row][col][0] = raw_history[row][col][1];
    raw_history[row][col][1] = raw_history[row][col][2];
    raw_history[row][col][2] = new_raw;
    uint16_t median_val = fast_median(raw_history[row][col][0], raw_history[row][col][1], raw_history[row][col][2]);

    // 2. 高精度 EMA 滑动平均
    if (ema_accumulator[row][col] == 0) { ema_accumulator[row][col] = median_val << EMA_SHIFT; }
    ema_accumulator[row][col] += median_val - (ema_accumulator[row][col] >> EMA_SHIFT);
    uint16_t ema_val = ema_accumulator[row][col] >> EMA_SHIFT;

    // 3. 迟滞死区滤波
    int16_t delta = (int16_t)ema_val - (int16_t)logical_output[row][col];
    if (delta > HYSTERESIS_DEADZONE) {
        logical_output[row][col] = ema_val - HYSTERESIS_DEADZONE;
    } else if (delta < -HYSTERESIS_DEADZONE) {
        logical_output[row][col] = ema_val + HYSTERESIS_DEADZONE;
    }
    return logical_output[row][col];
}






void row_col_gpio_init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;   // <--- 核心补全：推挽输出
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;   // 软启动，降低 EMI 和 VDD 振铃
    GPIO_InitStruct.Pull  = GPIO_NOPULL;           // 无需内部上下拉

    // 配置行输出
    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
  
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_8;
   
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 配置模拟列
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void row_all_off(void) {
    // 将所有行控制脚拉高（关闭 PMOS）
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_SET);
}
void select_row(uint8_t row_index) {
    row_all_off(); 
    switch(row_index) {
        case 0: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET); break; // 第 0 行
        case 1: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET); break; // 第 1 行
        case 2: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET); break; // 第 2 行
        case 3: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET); break; // 第 3 行
        case 4: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET); break; // 第 4 行
    }
}

void bsp_adc_dma_init(void)
{
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

    // 循环配置 14 个 Rank
    sConfig.SamplingTime = ADC_SAMPLETIME_5CYCLES_5;   ///ADC_SAMPLETIME_5CYCLES_5; 
    for (uint8_t i = 0; i < 14; i++)
    {
       sConfig.Channel = channel_map[i];
       sConfig.Rank = i + 1;
       HAL_ADC_ConfigChannel(&AdcHandle, &sConfig);
    }

    // ADC 的校准6
    HAL_ADCEx_Calibration_Start(&AdcHandle);

    // Fast init logic
    ADC1->CR2 |= ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_DMA | ADC_CR2_EXTTRIG;

    DMA1_Channel1->CCR &= ~DMA_CCR_EN;
    DMA1_Channel1->CPAR = (uint32_t)&ADC1->DR;
    DMA1_Channel1->CMAR = (uint32_t)gADCxConvertedData;
    DMA1_Channel1->CNDTR = 14;
    DMA1_Channel1->CCR = DMA_CCR_MINC | DMA_CCR_PSIZE_0 | DMA_CCR_MSIZE_0 | DMA_CCR_PL;
    DMA1->IFCR = (DMA_IFCR_CGIF1 | DMA_IFCR_CTCIF1 | DMA_IFCR_CHTIF1 | DMA_IFCR_CTEIF1);
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
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

    // 开启 DMA 的中断
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 1, 0); 
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);        
}
#define ADC_DMA1_CH1_ALL_FLAGS (DMA_IFCR_CGIF1 | DMA_IFCR_CTCIF1 | DMA_IFCR_CHTIF1 | DMA_IFCR_CTEIF1)
void bsp_adc_dma_start(void)
{ 
	 
    DMA1_Channel1->CCR &= ~DMA_CCR_EN;
    DMA1_Channel1->CMAR = (uint32_t)gADCxConvertedData;
    DMA1_Channel1->CNDTR = 14;
    DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS; 
    ADC1->SR = ~(ADC_SR_EOC | ADC_SR_STRT);
    
    DMA1_Channel1->CCR |= (DMA_CCR_TCIE | DMA_CCR_EN);
    ADC1->CR2 |= ADC_CR2_SWSTART;
}



void DMA1_Channel1_IRQHandler(void) {
	
	//传输完成的中断
    if(DMA1->ISR & (DMA_ISR_TCIF1 | DMA_ISR_TEIF1)) {
        DMA1->IFCR = ADC_DMA1_CH1_ALL_FLAGS; //清除标志位
        DMA1_Channel1->CCR &= ~DMA_CCR_EN;  //停止当前的dma

        g_adc_complete = 1; // 通知主循环：数据搬运完毕，可以开始滤波了！

    }
}


int main(void) {
    HAL_Init();
    APP_SystemClockConfig();
    
    row_col_gpio_init();
    bsp_adc_dma_init();

    // 1. 设置硬件状态：只开启 PC9 行，其余拉高
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_SET);
    HAL_Delay(10); 
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
    
  

    // 2. 触发第一次采集
    bsp_adc_dma_start();
    
   
    while (1) {
        
        if(g_adc_complete){
             g_adc_complete=0; //清除中断标志为
             //判断是否无效的adc数值
            for(uint8_t c=0;c<14;c++){
                if(key_mask[g_current_row][c]==1){
                   filtered_data[g_current_row][c] = process_hall_filter(g_current_row, c, gADCxConvertedData[c]);
 
                }else {
                    // 无效按键直接赋 0，跳过计算节省 CPU
                    filtered_data[g_current_row][c] = 0;
                }
            
            }
        
            // 2. 切换到下一行
            g_current_row++;
            if (g_current_row >= 5) {
                g_current_row = 0; // 全盘扫完，归零
          
            }
            
             // 3. 硬件切行
            select_row(g_current_row);
            Bsp_Delay_Us(30);
            bsp_adc_dma_start(); 
        }
 
    }
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
