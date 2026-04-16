#ifndef __BSP_UART_H
#define __BSP_UART_H

#include "py32f4xx_hal.h"
#include "bsp_board.h"
#include <stdio.h>

void bsp_usart_init(uint32_t baudrate);
void bsp_uart_send_byte(uint8_t ch);
void bsp_uart_send_string(char *str);

#endif