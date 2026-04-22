#include "main.h"
#include "bsp_config.h"
#include "lib_ws2812.h"
#include "usb_config.h"
#include "task.h"
#include "App.h"
static void APP_SystemClockConfig(void);
static void APP_USBInit(void);
#if 1


volatile uint8_t adc_done_flag = 0; // 转换完成标志
ADC_HandleTypeDef AdcHandle;
DMA_HandleTypeDef HdmaCh1;
uint16_t   gADCxConvertedData[3];
void GPIO_Config(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // 配置 PC6 row4- PC9 row1 PA8 row0
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		
    // 配置 PA0, PA1, PA2 为模拟输入
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void APP_AdcConfig(void)
{
  ADC_ChannelConfTypeDef   sConfig = {0};
  RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInit = {0};

  __HAL_RCC_ADC1_CLK_ENABLE();

  RCC_PeriphCLKInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  RCC_PeriphCLKInit.AdcClockSelection    = RCC_ADCPCLK2_DIV8;
  HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInit);

  AdcHandle.Instance = ADC1;

  AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;
  AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  AdcHandle.Init.ScanConvMode          = ADC_SCAN_ENABLE;
  AdcHandle.Init.ContinuousConvMode    = DISABLE;
  AdcHandle.Init.NbrOfConversion       = 3;
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;
  AdcHandle.Init.NbrOfDiscConversion   = 0;
  AdcHandle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;

  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  sConfig.Channel      = ADC_CHANNEL_0;
  sConfig.Rank         = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;
  HAL_ADC_ConfigChannel(&AdcHandle, &sConfig);

  sConfig.Channel      = ADC_CHANNEL_1;
  sConfig.Rank         = ADC_REGULAR_RANK_2;
  HAL_ADC_ConfigChannel(&AdcHandle, &sConfig);

  sConfig.Channel      = ADC_CHANNEL_2;
  sConfig.Rank         = ADC_REGULAR_RANK_3;
  HAL_ADC_ConfigChannel(&AdcHandle, &sConfig);
}




void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin  = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 ;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HdmaCh1.Instance                 = DMA1_Channel1;
  HdmaCh1.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  HdmaCh1.Init.PeriphInc           = DMA_PINC_DISABLE;
  HdmaCh1.Init.MemInc              = DMA_MINC_ENABLE;
  HdmaCh1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  HdmaCh1.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
  HdmaCh1.Init.Mode                = DMA_NORMAL;
  HdmaCh1.Init.Priority            = DMA_PRIORITY_VERY_HIGH;

  HAL_DMA_DeInit(&HdmaCh1);
  HAL_DMA_Init(&HdmaCh1);

  HAL_DMA_ChannelMap(&HdmaCh1, DMA_CHANNEL_MAP_ADC1);
  __HAL_LINKDMA(hadc, DMA_Handle, HdmaCh1);
}


//切换行
static void select_row(uint8_t index){
    // 1. 首先将所有行置为高电平 (截止状态)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9 | GPIO_PIN_8 | GPIO_PIN_7 | GPIO_PIN_6, GPIO_PIN_SET); // Row1-4 
   // 2. 将目标行置为低电平 (导通状态)
   switch (index)
   {
    case 0: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET); break;
    case 1: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET); break;
    case 2: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET); break;
    case 3: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET); break;
    case 4: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET); break;
    default: break; // 索引错误时不导通任何行
   }
    // 3. 关键：切换引脚后需要极短的延迟让电压稳定（由于引脚电容和霍尔响应）
    // 对于磁轴键盘，这里通常使用几个 NOP 指令或者 1-5微秒延迟
    for(volatile int i=0; i<100; i++); 
}

#endif


int main(void)
{  
    HAL_Init();
    APP_SystemClockConfig();
	
	  //////timer初始化
  	bsp_tim_init();
    bsp_usart_init(115200);
	  ////////ws2812初始化
    bsp_spi_dma_init();
    lib_ws2812_init();
    printf("init_success\r\n");
    
    
    APP_USBInit();
    // ///////////adc
     GPIO_Config();
    APP_AdcConfig();
    printf("init_success\r\n");
	  ///app初始化
		
		if (HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)
		{
			APP_ErrorHandler();
		}
	  select_row(4); // 选中某一行
 
		
		while (1){
		gADCxConvertedData[0] = 0;
    gADCxConvertedData[1] = 0;
    gADCxConvertedData[2] = 0;

    HAL_StatusTypeDef ret = HAL_ADC_Start_DMA(&AdcHandle, (uint32_t *)gADCxConvertedData, 3);
    printf("HAL_ADC_Start_DMA ret = %d\r\n", ret);

    HAL_Delay(10);

    printf("Channel1: %u\r\n", gADCxConvertedData[0]);
    printf("Channel2: %u\r\n", gADCxConvertedData[1]);
    printf("Channel3: %u\r\n", gADCxConvertedData[2]);

    HAL_ADC_Stop_DMA(&AdcHandle);

    HAL_Delay(1000);
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
