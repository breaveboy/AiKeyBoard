### 一、时钟源配置

位置： main.c:38-71
配置项 值 说明 HSI 频率 8 MHz 内部高速时钟 (HSI\_VALUE = 8000000) HSE 状态 OFF 外部晶振关闭 PLL 状态 OFF 锁相环关闭 系统时钟源 HSI 使用内部 8MHz

### 二、各总线时钟计算

```
ClkInitstruct.SYSCLKSource    = 
RCC_SYSCLKSOURCE_HSI;    // 系统时钟 = HSI = 8MHz
ClkInitstruct.AHBCLKDivider   = 
RCC_SYSCLK_DIV1;         // AHB = 8MHz ÷ 1 = 8MHz
ClkInitstruct.APB1CLKDivider  = 
RCC_HCLK_DIV1;           // APB1 = 8MHz ÷ 1 = 8MHz
ClkInitstruct.APB2CLKDivider  = 
RCC_HCLK_DIV2;           // APB2 = 8MHz ÷ 2 = 4MHz
```

### 三、SPI 时钟计算

```
#define LED_SPI_INSTANCE         SPI2
#define LED_SPI_BAUDRATE         
SPI_BAUDRATEPRESCALER_16
```

参数 值 SPI 实例 SPI2 SPI2 挂载总线 APB1 APB1 时钟 8 MHz SPI 分频系数 16

SPI 时钟计算公式：

```
SPI 时钟 = APB1 时钟 ÷ 分频系数
        = 8 MHz ÷ 16
        = 500 kHz
```

### 四、时钟总览表

项目 频率 HSI 内部时钟 8 MHz SYSCLK 系统时钟 8 MHz HCLK AHB 总线 8 MHz PCLK1 APB1 总线 8 MHz PCLK2 APB2 总线 4 MHz SPI2 时钟 (WS2812) 500 kHz

### 五、外设挂载总线

外设 挂载总线 总线时钟 SPI2 (WS2812) APB1 8 MHz USART1 (调试串口) APB2 4 MHz ADC1 APB2 4 MHz TIM6 APB1 8 MHz

### 六、总结

- 系统主频：8 MHz （使用 HSI 内部时钟）
- SPI2 时钟：500 kHz （8 MHz ÷ 16）
- 适合驱动 WS2812 LED（时序要求不高）
  这就是所有时钟的分析！

