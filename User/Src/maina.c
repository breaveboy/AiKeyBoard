#include "main.h"
#include "bsp_config.h"
#include "lib_ws2812.h"
#include "usb_config.h"
#include "task.h"
#include "App.h"

static void APP_SystemClockConfig(void);

void row_col_gpio(){
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


}
int main(void) {
    HAL_Init();
    APP_SystemClockConfig();

 
    bsp_tim_init();
    
    row_col_gpio();
   
    
    
    //关闭所有的行
    SET_IO(GPIOA, GPIO_PIN_8);
    SET_IO(GPIOC, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9);
    
    //拉拉低
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);

    while (1) {
        
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
