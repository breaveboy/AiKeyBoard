/* lib_ws2812.h - WS2812 LED library header */
#ifndef __LIB_WS2812_H__
#define __LIB_WS2812_H__

#include "bsp_board.h"
#include "bsp_spi_dma.h"
#include <stdbool.h>
#include <stdint.h>

// 根据实际灯带长度修改
#define WS2812_LED_NUM            61U
#define WS2812_BITS_PER_LED       24U
#define WS2812_RESET_LEN          120U
#define WS2812_TX_BUFFER_SIZE     ((WS2812_LED_NUM * WS2812_BITS_PER_LED) + WS2812_RESET_LEN)


// 每一个位对应的 SPI 数据字节
// 9MHz 下，1个 bit 约 111ns
// 0: 高电平 222ns (0xC0: 11000000)
// 1: 高电平 555ns (0xF8: 11111000)
#define WS_BIT_0                  0xE0U
#define WS_BIT_1                  0xF8U
// 复位信号：WS2812 需要至少 50us 低电平。9MHz速率下，约 60 字节的 0x00 足够
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} ws2812_color_t;

void lib_ws2812_init(void);
bool lib_ws2812_set_pixel(uint16_t led_index, uint8_t r, uint8_t g, uint8_t b);
bool lib_ws2812_set_key_color(uint8_t row, uint8_t col, uint8_t r, uint8_t g, uint8_t b);
void lib_ws2812_set_all(uint8_t r, uint8_t g, uint8_t b);
void lib_ws2812_update(void);
void lib_ws2812_clear(void);

#endif /* __LIB_WS2812_H__ */
