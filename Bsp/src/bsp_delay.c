#include "bsp_delay.h"

/**
 * @brief          微秒延时
 * @param          us [in],微秒
 * @note           硬件延时已验证 HSI 8Mhz PLL x18 144Mhz 5us-5.1us 10us-10.2us 100us-101us 1000us-1000us 优化03
 */
void Bsp_Delay_Us(uint32_t us) 
{
    volatile uint8_t i;
    while ( us-- )
    {
        i = 15;
        while ( i-- )
        {
            __nop();
        }
    }
}

/**
 * @brief          毫秒延时
 * @param          ms [in],毫秒
 * @note           硬件延时 已验证 HSI 8Mhz PLL x18 144Mhz 1ms-1.01ms 10ms-10ms 1000ms-1010ms 优化03
 */
void Bsp_Delay_Ms(uint32_t ms)
{
    while ( ms-- )
    {
        Bsp_Delay_Us(1000);
    }
}
