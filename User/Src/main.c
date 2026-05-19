#include "main.h"
#include "bsp_config.h"
#include "usb_config.h"
#include "lib_config.h"
#include "task.h"
#include "App.h"
#include "bsp_tim.h"
#include "SEGGER_RTT.h"

static void APP_SystemClockConfig(void);
// USB 初始化：注册标准键盘 HID 和自定义 HID 两个接口。
static void APP_USBInit(void);

// 固件入口：初始化外设、校准磁轴、启动 USB 和第一帧 ADC 扫描。
int main(void)
{
        HAL_Init();
    APP_SystemClockConfig();

    bsp_usart_init(115200);
    bsp_tim_init();

    SEGGER_RTT_printf(0, "init \r\n");
    printf("init \r\n");

    lib_ws2812_init();
    lib_hall_sensor_init();
    lib_hall_sensor_calibration();

    App_init();
    APP_USBInit();

    // 初始化完成后只启动第一帧，后续帧由按键任务释放后重启。
    lib_hall_sensor_start_scan();
    printf("success init ok\r\n");

    // 主循环只跑任务调度，各模块职责在任务表中拆分。
    while (1) {
        Task_exec();
    }
}

// USB 初始化：注册标准键盘 HID 和自定义 HID 两个接口。
static void APP_USBInit(void)
{
    SEGGER_RTT_printf(0, "usb i\r\n");

    __HAL_RCC_SYSCFG_CLK_ENABLE();
    SET_BIT(RCC->CFGR1, RCC_CFGR1_USBSELHSI48_Msk);
    __HAL_RCC_USB_CLK_ENABLE();

    hid_keyboard_init();
    NVIC_EnableIRQ(USBD_IRQn);
}

static void APP_SystemClockConfig(void)
{
    RCC_OscInitTypeDef OscInitstruct = {0};
    RCC_ClkInitTypeDef ClkInitstruct = {0};

    OscInitstruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI |
                                   RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_LSI |
                                   RCC_OSCILLATORTYPE_HSI48M;
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

    ClkInitstruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                              RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    ClkInitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    ClkInitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    ClkInitstruct.APB1CLKDivider = RCC_HCLK_DIV1;
    ClkInitstruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&ClkInitstruct, FLASH_LATENCY_6) != HAL_OK) {
        APP_ErrorHandler();
    }
}

void APP_ErrorHandler(void)
{
    // 主循环只跑任务调度，各模块职责在任务表中拆分。
    while (1) {
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
    // 主循环只跑任务调度，各模块职责在任务表中拆分。
    while (1) {
    }
}
#endif
