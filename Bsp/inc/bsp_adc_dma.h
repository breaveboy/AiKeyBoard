#ifndef __BSP_ADC_DMA_H__
#define __BSP_ADC_DMA_H__

#include "py32f4xx_hal.h"
#include "bsp_board.h"

extern ADC_HandleTypeDef AdcHandle;
extern DMA_HandleTypeDef HdmaCh1;
extern uint16_t gADCxConvertedData[ADC_CHANNELS_COUNT];

void bsp_adc_dma_init(void);
void bsp_adc_dma_start(void);

#endif
