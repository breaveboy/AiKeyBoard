




#include "main.h"
#include "bsp_config.h"
#include "lib_ws2812.h"
#include <stdio.h> // 必须包含此头文件以使用 FILE 和 printf
static void APP_SystemClockConfig(void);


int main(void)
{
    HAL_Init();
    APP_SystemClockConfig();
    bsp_usart_init(115200);
  
	  
    while (1)
    {
      printf("hello");
			HAL_Delay(200);
    }
}









static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef  OscInitstruct = {0};
  RCC_ClkInitTypeDef  ClkInitstruct = {0};

  OscInitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE |
                                  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSI48M;
  OscInitstruct.HSEState        = RCC_HSE_ON;                              /* Enable HSE */
  OscInitstruct.HSEFreq         = RCC_HSE_8_16MHz;                        /* HSE working frequency range: 16M~32M */
  OscInitstruct.HSI48MState     = RCC_HSI48M_ON;                          /* Enable HSI48M */
  OscInitstruct.HSIState        = RCC_HSI_ON;                              /* Enable HSI */
  OscInitstruct.LSEState        = RCC_LSE_OFF;                             /* Disable LSE */
  OscInitstruct.LSEDriver       = RCC_LSEDRIVE_HIGH;                       /* Drive capability level: High */
  OscInitstruct.LSIState        = RCC_LSI_OFF;                             /* Disable LSI */
  OscInitstruct.PLL.PLLState    = RCC_PLL_ON;                              /* Enable PLL */
  OscInitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;                       /* PLL clock source: HSE */
  OscInitstruct.PLL.PLLMUL      = RCC_CFGR_PLLMULL18;                            /* PLL multiplication factor is 5 */
  /* Configure Oscillators */
  if(HAL_RCC_OscConfig(&OscInitstruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  ClkInitstruct.ClockType       = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  ClkInitstruct.SYSCLKSource    = RCC_SYSCLKSOURCE_PLLCLK;              /* SYSCLK source select as PLL */
  ClkInitstruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;                      /* AHB clock not divided */
  ClkInitstruct.APB1CLKDivider  = RCC_HCLK_DIV1;                        /* APB1 clock not divided */
  ClkInitstruct.APB2CLKDivider  = RCC_HCLK_DIV1;                        /* APB2 clock not divided */
  /* Configure Clocks */
  if(HAL_RCC_ClockConfig(&ClkInitstruct, FLASH_LATENCY_6) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  /* Infinite loop */
  while (1)
  {
  }
}





#if 0
#include "main.h"
#include "task.h"
//#include "App.h"
#include "bsp_config.h"
//#include "usb_config.h"
static void APP_SystemClockConfig(void);
volatile uint8_t count = 0;





void ws218_init(){
    


}
int main(void)
{
    HAL_Init();
    APP_SystemClockConfig();
    

    //////////////输出/////////////////////
    bsp_usart_init(DEBUG_USART_BAUDRATE);
    bsp_adc_dma_init();
    bsp_spi_dma_init();
    bsp_tim_init();

    App_init();

    //hid_keyboard_init();
    //bsp_adc_dma_start();

    

    while (1)
    {
        //Task_exec();
    }
}

static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef  OscInitstruct = {0};
  RCC_ClkInitTypeDef  ClkInitstruct = {0};
  
  OscInitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE | 
                                  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSI48M;
  OscInitstruct.HSEState        = RCC_HSE_ON;                                /* ENABLE HSE */
  OscInitstruct.HSEFreq         = RCC_HSE_4_8MHz;                   /* Choose HSE frequency of 16-32MHz */
  

	OscInitstruct.HSI48MState     = RCC_HSI48M_OFF;                           /* Close HSI48M */
  OscInitstruct.HSIState        = RCC_HSI_ON;                               /* Enable HSI */
  OscInitstruct.LSEState        = RCC_LSE_OFF;                              /* Close LSE */
/* OscInitstruct.LSEDriver       = RCC_LSEDRIVE_HIGH; */                    /* Drive capability level: high */
  OscInitstruct.LSIState        = RCC_LSI_OFF;  

	/* Close LSI */
  OscInitstruct.PLL.PLLState    = RCC_PLL_ON;                              /* Close PLL */
  OscInitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;                    /* PLL clock source selection HSE */
  OscInitstruct.PLL.PLLMUL      = RCC_PLL_MUL18;                          /* PLL clock source 6-fold frequency */
  /* Configure oscillator */
  if(HAL_RCC_OscConfig(&OscInitstruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  ClkInitstruct.ClockType       = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  ClkInitstruct.SYSCLKSource    = RCC_SYSCLKSOURCE_PLLCLK;                 /* System clock selection HSI */
  ClkInitstruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;                      /* AHB clock 1 division */
  ClkInitstruct.APB1CLKDivider  = RCC_HCLK_DIV1;                        /* APB1 clock 1 division */
  ClkInitstruct.APB2CLKDivider  = RCC_HCLK_DIV2;                        /* APB2 clock 2 division */
  /* Configure Clock */
  if(HAL_RCC_ClockConfig(&ClkInitstruct, FLASH_LATENCY_0) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  /* Infinite loop */
  while (1)
  {
  }
}
#endif
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line)  */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
