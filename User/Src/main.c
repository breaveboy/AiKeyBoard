#include "main.h"
#include "bsp_config.h"
#include "usb_config.h"
#include "lib_config.h"

#include "task.h"
#include "App.h"
#include "bsp_tim.h"
#include <string.h>



static void APP_SystemClockConfig(void);
static void APP_USBInit(void);

/* --- 主循环 --- */
int main(void) {
    HAL_Init();
    APP_SystemClockConfig();
   
    bsp_usart_init(115200);
    bsp_tim_init();
     
	  bsp_spi_dma_init();
	  lib_ws2812_init();
	
	   
    // 初始化霍尔传感器（包含 GPIO 和 ADC DMA 初始化）
    lib_hall_sensor_init();
    // 1. 系统校准
    lib_hall_sensor_calibration();

	   
	
	
	
	
    // 2. 初始化 App 层
    App_init();
    APP_USBInit();
		
		
		
		
		
		
		
		
    // 3. 启动运行扫描
    g_scan_complete = 0;
    select_row(0);
    Bsp_Delay_Us(SETTLING_TIME_US);
    bsp_adc_dma_start();
//   
//		for(uint8_t r=0;r<5;r++){
//			for(uint8_t c=0;c<14;c++){
//			
//				lib_ws2812_set_key_color(r,c,255,0,0);
//				lib_ws2812_update();
//				Bsp_Delay_Ms(200);
//			}
//		} 
	
    while (1) {
        Task_exec();
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
