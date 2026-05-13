#include "bsp_adc_dma.h"
#include "bsp_gpio.h"

ADC_HandleTypeDef AdcHandle;
DMA_HandleTypeDef HdmaCh1;
uint16_t gADCxConvertedData[ADC_CHANNELS_COUNT];

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
    sConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;   ///ADC_SAMPLETIME_5CYCLES_5; 
    for (uint8_t i = 0; i < 14; i++)
    {
       sConfig.Channel = channel_map[i];
       sConfig.Rank = i + 1;
       HAL_ADC_ConfigChannel(&AdcHandle, &sConfig);
    }

    // ADC 的校准
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
