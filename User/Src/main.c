#include "main.h"
#include "bsp_config.h"
#include "lib_ws2812.h"
#include "usb_config.h"
#include "task.h"
#include "App.h"
static void APP_SystemClockConfig(void);
static void APP_USBInit(void);

#if 0
static ADC_HandleTypeDef hadc1;
static void adc1_ch1_init(){
  
	ADC_ChannelConfTypeDef sConfig = {0};
	GPIO_InitTypeDef GPIO_Init={0};
   //PC6  row4 PC7 row3
	 //PA0  chanel0
	 //开启dma进行搬运
  __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_ADC1_CLK_ENABLE();

	//初始化引脚PA0
	GPIO_Init.Pin=GPIO_PIN_0;
	GPIO_Init.Mode=GPIO_MODE_ANALOG;
	GPIO_Init.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&GPIO_Init);
	/////PC6
	GPIO_Init.Pin=GPIO_PIN_6;
	GPIO_Init.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC,&GPIO_Init);
  /////////adc///////////
	
	hadc1.Instance = ADC1;
	hadc1.Init.Resolution            = ADC_RESOLUTION_12B;
	hadc1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
	hadc1.Init.ScanConvMode          = ADC_SCAN_DISABLE;  //扫描模式
	hadc1.Init.ContinuousConvMode    = DISABLE;  //循环模式
	hadc1.Init.NbrOfConversion       = 1;      //1个通道
	hadc1.Init.DiscontinuousConvMode = DISABLE;  //不连续转换模式
	hadc1.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
	HAL_ADC_Init(&hadc1);

	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_41CYCLES_5;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	HAL_ADCEx_Calibration_Start(&hadc1);

	
	
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET);
	
}
static void get_adc(){
      HAL_ADC_Start(&hadc1);                         // 启动 ADC 转换
	  HAL_Delay(20);
	  //判断是否转换完成
	  if(HAL_ADC_PollForConversion(&hadc1,10)==HAL_OK){
			uint32_t adc_value = HAL_ADC_GetValue(&hadc1);
			float ad_uc=(adc_value*3.3)/4095;
			printf("adc = %u\r\n", adc_value);
			printf("ad_us=%f\r\n",ad_uc);
		
		}
     HAL_ADC_Stop(&hadc1); 
   
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
    // adc1_ch1_init();
    // HAL_Delay(50);
    // printf("init_success\r\n");
	  ///app初始化
	 
	
	
	
	
    while (1)
    {
      
		  // hid_keyboard_test();
			Task_exec();
       
    }
}
static void APP_USBInit(void)
{
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
