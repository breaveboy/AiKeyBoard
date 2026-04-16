#include "bsp_spi_dma.h"
#include "bsp_gpio.h"

SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi2_tx;
//8Mhz主频，spi发送0xc0是0 发送0xF8是1
void bsp_spi_dma_init(void)
{
    GPIO_InitTypeDef GPIO_Init = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();
    RCC_SPI2_CLK_ENABLE();
    RCC_DMA_CLK_ENABLE();
    //引脚初始化
    bsp_led_en_init();
    GPIO_Init.Pin = LED_DAT_PIN;
    GPIO_Init.Mode = GPIO_MODE_AF_PP;
    GPIO_Init.Alternate = LED_DAT_AF;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(LED_DAT_PORT, &GPIO_Init);
    //配置dma
    hdma_spi2_tx.Instance = LED_DMA_CHANNEL;   
    hdma_spi2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;   //内存到外设
    hdma_spi2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi2_tx.Init.MemInc = DMA_MINC_ENABLE;   //内存自增
    hdma_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;  //单字节
    hdma_spi2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;     //单字节
    hdma_spi2_tx.Init.Mode = DMA_NORMAL;  //正常模式
    hdma_spi2_tx.Init.Priority = DMA_PRIORITY_HIGH; 
    HAL_DMA_Init(&hdma_spi2_tx);
    __HAL_LINKDMA(&hspi2, hdmatx, hdma_spi2_tx);  //建立关联

    hspi2.Instance = LED_SPI_INSTANCE;    //spi2
    hspi2.Init.Mode = SPI_MODE_MASTER;    //mosi主
    hspi2.Init.Direction = SPI_DIRECTION_2LINES; //全双工
    hspi2.Init.DataSize = SPI_DATASIZE_8BIT;   //单字节
    hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;  //第一边沿
    hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;      //第一相位
    hspi2.Init.NSS = SPI_NSS_SOFT;              //软触发 
    hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;     //高字节
    HAL_SPI_Init(&hspi2);

    HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
}

//启动dma搬运数据
HAL_StatusTypeDef bsp_spi_dma_send(uint8_t *pData, uint16_t len)
{
    if (hspi2.State != HAL_SPI_STATE_READY) {
        return HAL_BUSY;
    }
    return HAL_SPI_Transmit_DMA(&hspi2, pData, len);
}
//配置中断处理函数
void DMA1_Channel2_IRQHandler(void) {
    HAL_DMA_IRQHandler(&hdma_spi2_tx);
}


