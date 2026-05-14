/**
  ******************************************************************************
  *          .,:,,,                                        .::,,,,::.
  *        .::::,,;;,                                  .,;;:,,.....:i:
  *        :i,.::::,;i:.      ....,,::::::::::,.....   .;i:,.  ......;i.
  *        :;..:::;::::i;,,:::;:,,,,,,,,,,,..,.,,:::iri:. .,:irsr:,.;i.
  *        ;;..,::::;;;;ri,,,.                    ...,,:;s1s1ssrr;,.;r,
  *        :;. ,::;ii;:,     . .....................     .;iirri;;;,,;i,
  *        ,i. .;ri:.   ... ..............................  .,,:;:,,,;i:
  *        :s,.;r:... ......................................... .::;::s;
  *        ,1r::. .............,,,.,,,:,,.........................,;iir;
  *        ,s;...........     ..::.,,;:,,.          ................,;1s
  *       :i,..,.              .,:,,,::,.          .......... ........;1,
  *      ir,....:rrssr;:,       ,,,.,::.     .r5S9989398G95hr;. .....,.:s,
  *     ;r,..,s9855513XHAG3i   .,,,,,,,,.  ,S931,.,,.;s;s&BHHA8s.,...,..:r:
  *    :r;..rGGh,  :SAG;;G@BS:.,,,,,,,,,,.r83:      hHH1sXMBHHHM3..,,,,,.ir.
  *   ,si,.1GS,   sBMAAX&MBMB5,,,,,,,:,,.:&8       3@HXHBMBHBBH#X,.,,.,,,,rr
  *   ;1:,,SH:   .A@&&B#&8H#BS,,,,,,,,,.,5XS,     3@MHABM&59M#As..,,,,,,:,is,
  *  .rr,,,;9&1   hBHHBB&8AMGr,,,,,,,,,,,:h&&9s;   r9&BMHBHMB9:  . ..,,,,;ri.
  *  :1:....:5&XSi;r8BMBHHA9r:,......,,,,:ii19GG88899XHHH&GSr.      ....,:rs.
  *  ;s.     .:sS8G8GG889hi.        ....,,:;:,.:irssrriii:,.        ....,,i1,
  *  ;1,         ..,....,,isssi;,        .,,.                      .....,.i1,
  *  ;h:               i9HHBMBBHAX9:         .                     ....,,,rs,
  *  ,1i..            :A#MBBBBMHB##s                             .....,,,;si.
  *  .r1,..        ,..;3BMBBBHBB#Bh.     ..                    .....,,,,,i1;
  *   :h;..       .,..;,1XBMMMMBXs,.,, .. :: ,.               .....,,,,,,ss.
  *    ih: ..    .;;;, ;;:s58A3i,..    ,. ,.:,,.             ....,,,,,:,s1,
  *    .s1,....   .,;sh,  ,iSAXs;.    ,.  ,,.i85            ....,,,,,,:i1;
  *     .rh: ...     rXG9XBBM#M#MHAX3hss13&&HHXr         ......,,,,,,,ih;
  *      .s5: .....    i598X&&A&AAAAAA&XG851r:       .........,,,,:,,sh;
  *      . ihr, ...  .         ..                    .........,,,,,;11:.
  *         ,s1i. ...  ..,,,..,,,,.,,.,,.,..       .........,,.,,.;s5i.
  *          .:s1r,......................       ...............;shs,
  *          . .:shr:.  ....     .            ..............,ishs.
  *              .,issr;,... ............................,is1s;.
  *                 .,is1si;:,.....................,:;ir1sr;,
  *                    ..:isssssrrii;:::::::;;iirsssssr;:..
  *                         .,::iiirsssssssssrri;;:.
  *						
  *
  ******************************************************************************
-----------------------------------------------File Info------------------------------------------------
** File Name:               main.c 
** Created date:            2026.5.1
** author:                  杨万里
** Version:                 V0.1
** Descriptions:            demo 
**--------------------------------------------------------------------------------------------------------
*/



#include "main.h"
#include "bsp_config.h"
#include "usb_config.h"
#include "lib_config.h"

#include "task.h"
#include "App.h"
#include "bsp_tim.h"
#include <string.h>
#include "SEGGER_RTT.h"


static void APP_SystemClockConfig(void);
static void APP_USBInit(void);



//配置a10和a9的初始化
void  debug_init(){
    //PA10 PA9
    GPIO_InitTypeDef GPIO_t;
    //配置时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();
    //配置初始模式
	GPIO_t.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_t.Pull  = GPIO_NOPULL;
    GPIO_t.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_t.Pin   = GPIO_PIN_9|GPIO_PIN_10;
	HAL_GPIO_Init(GPIOA, &GPIO_t);
}
extern volatile uint8_t g_adc_complete ;
extern volatile uint8_t g_current_row ; 
void lib_hall_sensor_dump_init_adc(void)
{
    uint16_t adc_snapshot[ROW_COUNT][COL_COUNT] = {0};

    printf("\r\nADC init snapshot start\r\n");

    g_adc_complete = 0;
  

    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        select_row(r);
        Bsp_Delay_Us(SETTLING_TIME_US);

        g_adc_complete = 0;
       
        bsp_adc_dma_start();

        while (!g_adc_complete) {
        }

        g_adc_complete = 0;

        
        for (uint8_t c = 0; c < COL_COUNT; c++) {
            adc_snapshot[r][c] = gADCxConvertedData[c];
        }
    }

    for (uint8_t r = 0; r < ROW_COUNT; r++) {
        printf("row %d:", r);
        for (uint8_t c = 0; c < COL_COUNT; c++) {
            printf(" %4d", adc_snapshot[r][c]);
        }
        printf("\r\n");
    }

    g_current_row = 0;
    select_row(0);

    printf("ADC init snapshot end\r\n\r\n");
}


/* --- 主循环 --- */
int main(void) {
    HAL_Init();
    APP_SystemClockConfig();
    ///////////////////////////////板层初始化////////////
    bsp_usart_init(115200);
    bsp_tim_init();                 //1ms一次中断
    //debug_init();   
    //bsp_spi_dma_init();              
  
	SEGGER_RTT_printf(0, "init \r\n");
	printf("init \r\n");
	
    ///////////////////////////////驱动层初始化//////////////
    lib_ws2812_init();
    // 初始化霍尔传感器（包含 GPIO 和 ADC DMA 初始化）
    lib_hall_sensor_init();
    // 1. 系统校准
    lib_hall_sensor_calibration();

    
	 
	
	///////////////////////////////业务层初始化//////////////////
    // 2. 初始化 App 层
    App_init();
    APP_USBInit();
	
    
    // 3. 启动运行扫描
    g_scan_complete = 0;
    select_row(0);
    Bsp_Delay_Us(SETTLING_TIME_US);
    bsp_adc_dma_start();
    printf("success init ok\r\n");
    
    
    while (1) {
        lib_hall_sensor_task();  // 只做 ADC 完成后的当前行处理
        Task_exec();
    }
}


//修改前的代码
static void APP_USBInit(void)
{  
  SEGGER_RTT_printf(0, "usb i\r\n");
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
    OscInitstruct.HSI48MState     = RCC_HSI48M_ON;  //usb的时钟打开
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
