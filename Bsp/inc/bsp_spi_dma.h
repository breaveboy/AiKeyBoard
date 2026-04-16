#ifndef __BSP_SPI_DMA_H__
#define __BSP_SPI_DMA_H__

#include "py32f4xx_hal.h"
#include "bsp_board.h"

void bsp_spi_dma_init(void);
HAL_StatusTypeDef bsp_spi_dma_send(uint8_t *pData, uint16_t len);

#endif
