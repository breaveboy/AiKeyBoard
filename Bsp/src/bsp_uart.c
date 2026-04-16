#include "bsp_uart.h"

#ifdef HAL_UART_MODULE_ENABLED
UART_HandleTypeDef DebugUartHandle;
#endif

void bsp_usart_init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    RCC_USART1_CLK_ENABLE();
    RCC_ADC_PORTA_CLK_ENABLE();

    GPIO_InitStruct.Pin       = DEBUG_USART_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = DEBUG_USART_TX_AF;
    HAL_GPIO_Init((GPIO_TypeDef*)DEBUG_USART_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin       = DEBUG_USART_RX_PIN;
    GPIO_InitStruct.Alternate = DEBUG_USART_RX_AF;
    HAL_GPIO_Init((GPIO_TypeDef*)DEBUG_USART_RX_PORT, &GPIO_InitStruct);

#ifdef HAL_UART_MODULE_ENABLED
    DebugUartHandle.Instance          = DEBUG_USART_INSTANCE;
    DebugUartHandle.Init.BaudRate     = baudrate;
    DebugUartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
    DebugUartHandle.Init.StopBits     = UART_STOPBITS_1;
    DebugUartHandle.Init.Parity       = UART_PARITY_NONE;
    DebugUartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    DebugUartHandle.Init.Mode         = UART_MODE_TX_RX;
    DebugUartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    DebugUartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&DebugUartHandle) != HAL_OK) {
        while (1);
    }
    HAL_NVIC_SetPriority(DEBUG_USART_IRQ, 0, 1);
    HAL_NVIC_EnableIRQ(DEBUG_USART_IRQ);
#endif
}

void bsp_uart_send_byte(uint8_t ch)
{
#ifdef HAL_UART_MODULE_ENABLED
    HAL_UART_Transmit(&DebugUartHandle, &ch, 1, 10);
#endif
}

void bsp_uart_send_string(char *str)
{
    while (*str) {
        bsp_uart_send_byte((uint8_t)*str++);
    }
}

int fputc(int ch, FILE *f)
{
#ifdef HAL_UART_MODULE_ENABLED
    HAL_UART_Transmit(&DebugUartHandle, (uint8_t *)&ch, 1, 1000);
#endif
    return (ch);
}
