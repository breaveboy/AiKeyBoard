#include "bsp_spi_dma.h"
#include "bsp_gpio.h"

SPI_HandleTypeDef hspi21;
DMA_HandleTypeDef hdma_spi2_tx1;
//8Mhz?????spi????0xc0??0 ????0xF8??1
void bsp_spi_dma_init(void)
{
    GPIO_InitTypeDef GPIO_Init = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();
    RCC_SPI2_CLK_ENABLE();
    RCC_DMA_CLK_ENABLE();
    //????????
    bsp_led_en_init();
    GPIO_Init.Pin = LED_DAT_PIN;
    GPIO_Init.Mode = GPIO_MODE_AF_PP;
    GPIO_Init.Alternate = LED_DAT_AF;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(LED_DAT_PORT, &GPIO_Init);
    //????dma
    hdma_spi2_tx1.Instance = LED_DMA_CHANNEL;   
    hdma_spi2_tx1.Init.Direction = DMA_MEMORY_TO_PERIPH;   //??��????
    hdma_spi2_tx1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi2_tx1.Init.MemInc = DMA_MINC_ENABLE;   //???????
    hdma_spi2_tx1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;  //?????
    hdma_spi2_tx1.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;     //?????
    hdma_spi2_tx1.Init.Mode = DMA_NORMAL;  //??????
    hdma_spi2_tx1.Init.Priority = DMA_PRIORITY_HIGH; 
    HAL_DMA_Init(&hdma_spi2_tx1);
    __HAL_LINKDMA(&hspi21, hdmatx, hdma_spi2_tx1);  //????????

    hspi21.Instance = LED_SPI_INSTANCE;    //spi2
    hspi21.Init.Mode = SPI_MODE_MASTER;    //mosi??
    hspi21.Init.Direction = SPI_DIRECTION_2LINES; //????
    hspi21.Init.DataSize = SPI_DATASIZE_8BIT;   //?????
    hspi21.Init.CLKPolarity = SPI_POLARITY_LOW;  //???????
    hspi21.Init.CLKPhase = SPI_PHASE_1EDGE;      //?????��
    hspi21.Init.NSS = SPI_NSS_SOFT;              //?????? 
    hspi21.Init.FirstBit = SPI_FIRSTBIT_MSB;     //?????
    hspi21.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    HAL_SPI_Init(&hspi21);

    HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
}

void DMA1_Channel2_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_spi2_tx1);
}

//????dma????????
HAL_StatusTypeDef bsp_spi_dma_send(uint8_t *pData, uint16_t len)
{
    if (hspi21.State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }
    return HAL_SPI_Transmit_DMA(&hspi21, pData, len);
}
// //?????��????????
// void DMA1_Channel2_IRQHandler(void) {
//     HAL_DMA_IRQHandler(&hdma_spi2_tx1);
// }

