#include "bsp_adc_dma.h"
#include "bsp_gpio.h"

// ADC 句柄
static ADC_HandleTypeDef    AdcHandle;
// DMA 句柄
static DMA_HandleTypeDef    HdmaCh1;
// ADC 原始数据矩阵 [行][列]
uint32_t g_adc_raw_matrix[MATRIX_ROWS_COUNT][ADC_CHANNELS_COUNT];
// 当前扫描的行索引
static volatile uint8_t current_row = 0;

// ADC 通道映射表
static const uint32_t adc_channels[ADC_CHANNELS_COUNT] = {
    ADC_COL0_CH, ADC_COL1_CH, ADC_COL2_CH, ADC_COL3_CH,
    ADC_COL4_CH, ADC_COL5_CH, ADC_COL6_CH, ADC_COL7_CH,
    ADC_COL8_CH, ADC_COL9_CH, ADC_COL10_CH, ADC_COL11_CH,
    ADC_COL12_CH, ADC_COL13_CH
};

/**
 * @brief  初始化 ADC 列引脚为模拟输入模式
 */
static void adc_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_Init = {0};

    // 使能 ADC 引脚所在端口的时钟
    RCC_ADC_PORTA_CLK_ENABLE();
    RCC_ADC_PORTB_CLK_ENABLE();
    RCC_ADC_PORTC_CLK_ENABLE();

    // 配置为模拟输入模式
    GPIO_Init.Mode = GPIO_MODE_ANALOG;
    GPIO_Init.Pull = GPIO_NOPULL;

    // PA0-PA7 (AIN0-AIN7)
    GPIO_Init.Pin = ADC_COL0_PIN | ADC_COL1_PIN | ADC_COL2_PIN | ADC_COL3_PIN |
                    ADC_COL4_PIN | ADC_COL5_PIN | ADC_COL6_PIN | ADC_COL7_PIN;
    HAL_GPIO_Init((GPIO_TypeDef*)ADC_COL0_PORT, &GPIO_Init);

    // PB0-PB1 (AIN8-AIN9)
    GPIO_Init.Pin = ADC_COL8_PIN | ADC_COL9_PIN;
    HAL_GPIO_Init((GPIO_TypeDef*)ADC_COL8_PORT, &GPIO_Init);

    // PC0-PC3 (AIN10-AIN13)
    GPIO_Init.Pin = ADC_COL10_PIN | ADC_COL11_PIN | ADC_COL12_PIN | ADC_COL13_PIN;
    HAL_GPIO_Init((GPIO_TypeDef*)ADC_COL10_PORT, &GPIO_Init);
}

/**
 * @brief  初始化 ADC 和 DMA 外设
 */
static void adc_dma_init(void)
{
    // 使能 ADC 和 DMA 时钟
    RCC_ADC_CLK_ENABLE();
    RCC_DMA_CLK_ENABLE();

    // 配置 ADC 外设时钟
    RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInit = {0};
    RCC_PeriphCLKInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    RCC_PeriphCLKInit.AdcClockSelection = ADC_CLOCK_DIV;
    HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInit);

    // 配置 DMA1_Channel1
    HdmaCh1.Instance = DMA1_Channel1;
    HdmaCh1.Init.Direction           = DMA_PERIPH_TO_MEMORY;  // 外设到内存
    HdmaCh1.Init.PeriphInc           = DMA_PINC_DISABLE;       // 外设地址不增量
    HdmaCh1.Init.MemInc              = DMA_MINC_ENABLE;        // 内存地址增量
    HdmaCh1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;    // 32位对齐
    HdmaCh1.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
    HdmaCh1.Init.Mode                = DMA_CIRCULAR;           // 循环模式
    HdmaCh1.Init.Priority            = DMA_PRIORITY_HIGH;
    HAL_DMA_Init(&HdmaCh1);
    // 关联 ADC 和 DMA
    __HAL_LINKDMA(&AdcHandle, DMA_Handle, HdmaCh1);

    // 配置 ADC1
    AdcHandle.Instance = ADC1;
    AdcHandle.Init.Resolution            = ADC_RESOLUTION;       // 分辨率
    AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;  // 右对齐
    AdcHandle.Init.ScanConvMode          = ADC_SCAN_ENABLE;      // 开启扫描模式
    AdcHandle.Init.ContinuousConvMode    = ENABLE;               // 连续转换
    AdcHandle.Init.NbrOfConversion       = ADC_CHANNELS_COUNT;   // 14个通道
    AdcHandle.Init.DiscontinuousConvMode = DISABLE;
    AdcHandle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;   // 软件触发
    HAL_ADC_Init(&AdcHandle);

    // 配置 14 个 ADC 通道
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.SamplingTime = ADC_SAMPLETIME;  // 采样时间
    for (int i = 0; i < ADC_CHANNELS_COUNT; i++) {
        sConfig.Channel = adc_channels[i];
        sConfig.Rank    = ADC_REGULAR_RANK_1 + i;  // 第 1 到 第 14 顺位
        HAL_ADC_ConfigChannel(&AdcHandle, &sConfig);
    }

    // ADC 校准
    HAL_ADCEx_Calibration_Start(&AdcHandle);

    // 配置 DMA 中断
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

/**
 * @brief  统一初始化 ADC DMA 矩阵扫描模块
 */
void bsp_adc_dma_init(void)
{
    // 初始化按键矩阵行控制引脚
    bsp_key_matrix_row_init();
    // 初始化 ADC 列引脚
    adc_gpio_init();
    // 初始化 ADC 和 DMA 外设
    adc_dma_init();
}

/**
 * @brief  切换到指定行并等待稳定
 * @param  row_idx: 行索引 (0-4)
 */
static void switch_row(uint8_t row_idx)
{
    // 选择扫描行
    bsp_key_matrix_row_select(row_idx);
    // 延时等待信号稳定
    for(volatile uint32_t i = 0; i < 300; i++);
}

/**
 * @brief  启动 ADC DMA 自动扫描
 */
void bsp_adc_dma_start(void)
{
    // 从第 0 行开始
    current_row = 0;
    // 切换到第 0 行
    switch_row(current_row);
    // 启动 ADC DMA，数据存入第 0 行
    HAL_ADC_Start_DMA(&AdcHandle, (uint32_t*)g_adc_raw_matrix[0], ADC_CHANNELS_COUNT);
}

/**
 * @brief  ADC DMA 传输完成回调函数
 * @note   一行采集完成后自动切换到下一行
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    // 索引指向下一行
    current_row++;
    if (current_row >= MATRIX_ROWS_COUNT) {
        current_row = 0;  // 循环回第 0 行
    }
    // 切换到下一行
    switch_row(current_row);
    // 继续采集，数据存入对应行
    HAL_ADC_Start_DMA(hadc, (uint32_t*)g_adc_raw_matrix[current_row], ADC_CHANNELS_COUNT);
}

/**
 * @brief  DMA1_Channel1 中断服务程序
 */
void DMA1_Channel1_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&HdmaCh1);
}
