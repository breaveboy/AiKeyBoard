/**
******************************************************************************
* @file    py32f410xB.h
* @brief   CMSIS Cortex-M4 Device Peripheral Access Layer Header File.
*          This file contains all the peripheral register's definitions, bits
*          definitions and memory mapping for PY32F4xx devices.
* @version v1.0.0
*
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

#ifndef __PY32F410xB_H
#define __PY32F410xB_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
* @brief Configuration of the Cortex-M4 Processor and Core Peripherals
*/
#define __CM4_REV                 0x0001U  /*!< Core revision r0p1                            */
#define __MPU_PRESENT             0U       /*!< PY32F4xx provides an MPU                      */
#define __NVIC_PRIO_BITS          3U       /*!< PY32F4xx uses 3 Bits for the Priority Levels  */
#define __Vendor_SysTickConfig    0U       /*!< Set to 1 if different SysTick Config is used  */
#define __FPU_PRESENT             1U       /*!< FPU present                                   */

/**
 * @brief PY32F4xx Interrupt Number Definition, according to the selected device
 *        in @ref Library_configuration_section
 */
typedef enum
{
  /******  Cortex-M4 Processor Exceptions Numbers **************************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  HardFault_IRQn              = -13,    /*!< 3 Cortex-M4 Hard Fault Interrupt                                  */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
  TAMPER_IRQn                 = 2,      /*!< Tamper Interrupt                                                  */
  RTC_IRQn                    = 3,      /*!< RTC global Interrupt                                              */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                              */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                              */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                              */
  EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                              */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                              */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                              */
  EXTI9_5_IRQn                = 11,     /*!< External Line[5:9] Interrupt                                      */
  EXTI15_10_IRQn              = 12,     /*!< External Line[15:10] Interrupt                                    */
  DMA1_Channel1_IRQn          = 13,     /*!< DMA1 Channel 1 global Interrupt                                   */
  DMA1_Channel2_IRQn          = 14,     /*!< DMA1 Channel 2 global Interrupt                                   */
  DMA1_Channel3_IRQn          = 15,     /*!< DMA1 Channel 3 global Interrupt                                   */
  DMA1_Channel4_IRQn          = 16,     /*!< DMA1 Channel 4 global Interrupt                                   */
  DMA1_Channel5_IRQn          = 17,     /*!< DMA1 Channel 5 global Interrupt                                   */
  DMA1_Channel6_IRQn          = 18,     /*!< DMA1 Channel 6 global Interrupt                                   */
  DMA1_Channel7_IRQn          = 19,     /*!< DMA1 Channel 7 global Interrupt                                   */
  DMA1_Channel8_IRQn          = 20,     /*!< DMA1 Channel 8 global Interrupt                                   */
  ADC_IRQn                    = 21,     /*!< ADC global Interrupt                                              */
  TIM1_BRK_IRQn               = 22,     /*!< TIM1 global Interrupt                                             */
  TIM1_UP_IRQn                = 23,     /*!< TIM1 Update Interrupt global Interrupt                            */
  TIM1_TRG_COM_IRQn           = 24,     /*!< TIM1 Trigger and Commutation Interrupt global interrupt           */
  TIM1_CC_IRQn                = 25,     /*!< TIM1 Capture Compare Interrupt                                    */
  TIM2_IRQn                   = 26,     /*!< TIM2 global Interrupt                                             */
  TIM3_IRQn                   = 27,     /*!< TIM3 global Interrupt                                             */
  TIM4_IRQn                   = 28,     /*!< TIM4 global Interrupt                                             */
  TIM6_IRQn                   = 29,     /*!< TIM6 global Interrupt                                             */
  TIM7_IRQn                   = 30,     /*!< TIM7 global Interrupt                                             */
  TIM15_IRQn                  = 31,     /*!< TIM15 global Interrupt                                            */
  TIM16_IRQn                  = 32,     /*!< TIM16 global Interrupt                                            */
  TIM17_IRQn                  = 33,     /*!< TIM17 global Interrupt                                            */
  PWM1_IRQn                   = 34,     /*!< PWM1 global Interrupt                                             */
  PWM2_IRQn                   = 35,     /*!< PWM2 global Interrupt                                             */
  PWM3_IRQn                   = 36,     /*!< PWM3 global Interrupt                                             */
  PWM4_IRQn                   = 37,     /*!< PWM4 global Interrupt                                             */
  LPTIM_IRQn                  = 38,     /*!< LPTIM global Interrupt                                            */
  SPI1_IRQn                   = 39,     /*!< SPI1 global Interrupt                                             */
  SPI2_IRQn                   = 40,     /*!< SPI2 global Interrupt                                             */
  USART_IRQn                  = 41,     /*!< USART global Interrupt                                            */
  UART1_IRQn                  = 42,     /*!< UART1 global Interrupt                                            */
  UART2_IRQn                  = 43,     /*!< UART2 global Interrupt                                            */
  LPUART_IRQn                 = 44,     /*!< LPUART global Interrupt                                           */
  RTC_Alarm_IRQn              = 45,     /*!< RTC Alarm through EXTI Line Interrupt                             */
  I2C1_EV_IRQn                = 46,     /*!< I2C1 Event Interrupt                                              */
  I2C1_ER_IRQn                = 47,     /*!< I2C1 Error Interrupt                                              */
  I2C2_EV_IRQn                = 48,     /*!< I2C2 Event Interrupt                                              */
  I2C2_ER_IRQn                = 49,     /*!< I2C2 Error Interrupt                                              */
  COMP1_IRQn                  = 50,     /*!< COMP1 global Interrupt                                            */
  COMP2_IRQn                  = 51,     /*!< COMP2 global Interrupt                                            */
  OPA2_IRQn                   = 52,     /*!< OPA2 global Interrupt                                             */
} IRQn_Type;

#include "core_cm4.h"             /* Cortex-M4 processor and core peripherals */
#include "system_py32f4xx.h"
#include <stdint.h>

/**
* @brief ADC Registers
  */
/**
* @brief ADC Registers
*/
typedef struct
{
   __IO uint32_t ISR;              /*!< ADC ISR Register,                   Address offset: 0x00  */
   __IO uint32_t IER;              /*!< ADC IER Register,                   Address offset: 0x04  */
   __IO uint32_t CR;               /*!< ADC CR Register,                    Address offset: 0x08  */
   __IO uint32_t CFGR;             /*!< ADC CFGR Register,                  Address offset: 0x0C  */
   __IO uint32_t CFGR2;            /*!< ADC CFGR2 Register,                 Address offset: 0x10  */
   __IO uint32_t SMPR1;            /*!< ADC SMPR1 Register,                 Address offset: 0x14  */
   __IO uint32_t SMPR2;            /*!< ADC SMPR2 Register,                 Address offset: 0x18  */
   __IO uint32_t RESERVED1;         
   __IO uint32_t SMPR3;            /*!< ADC SMPR3 Register,                 Address offset: 0x20  */
   __IO uint32_t TR1;              /*!< ADC TR1 Register,                   Address offset: 0x24  */
   __IO uint32_t TR2;              /*!< ADC TR2 Register,                   Address offset: 0x28  */
   __IO uint32_t RESERVED2;         
   __IO uint32_t TR3;              /*!< ADC TR3 Register,                   Address offset: 0x30  */
   __IO uint32_t SQR1;             /*!< ADC SQR1 Register,                  Address offset: 0x34  */
   __IO uint32_t SQR2;             /*!< ADC SQR2 Register,                  Address offset: 0x38  */
   __IO uint32_t SQR3;             /*!< ADC SQR3 Register,                  Address offset: 0x3C  */
   __IO uint32_t SQR4;             /*!< ADC SQR4 Register,                  Address offset: 0x40  */
   __IO uint32_t RESERVED3[2];      
   __IO uint32_t DR;               /*!< ADC DR Register,                    Address offset: 0x4C  */
   __IO uint32_t JSQR;             /*!< ADC JSQR Register,                  Address offset: 0x50  */
   __IO uint32_t RESERVED4[3];      
   __IO uint32_t OFR1;             /*!< ADC OFR1 Register,                  Address offset: 0x60  */
   __IO uint32_t OFR2;             /*!< ADC OFR2 Register,                  Address offset: 0x64  */
   __IO uint32_t OFR3;             /*!< ADC OFR3 Register,                  Address offset: 0x68  */
   __IO uint32_t OFR4;             /*!< ADC OFR4 Register,                  Address offset: 0x6C  */
   __IO uint32_t RESERVED5[4];      
   __IO uint32_t JDR1;             /*!< ADC JDR1 Register,                  Address offset: 0x80  */
   __IO uint32_t JDR2;             /*!< ADC JDR2 Register,                  Address offset: 0x84  */
   __IO uint32_t JDR3;             /*!< ADC JDR3 Register,                  Address offset: 0x88  */
   __IO uint32_t JDR4;             /*!< ADC JDR4 Register,                  Address offset: 0x8C  */
   __IO uint32_t RESERVED6[4];      
   __IO uint32_t AWD2CR;           /*!< ADC AWD2CR Register,                Address offset: 0xA0  */
   __IO uint32_t AWD3CR;           /*!< ADC AWD3CR Register,                Address offset: 0xA4  */
   __IO uint32_t RESERVED7[3];      
   __IO uint32_t CALFACT;          /*!< ADC CALFACT Register,               Address offset: 0xB4  */
   __IO uint32_t RESERVED8[2];      
   __IO uint32_t GCOMP;            /*!< ADC GCOMP Register,                 Address offset: 0xC0  */
   __IO uint32_t RESERVED9[145];    
   __IO uint32_t CCR;              /*!< ADCX CCR Register,                  Address offset: 0x308  */
} ADC_TypeDef;


typedef struct
{
  __IO uint32_t CCR;          /*!< ADC common configuration register,     Address offset: 0x300 + 0x08 */
} ADC_Common_TypeDef;

/**
  * @brief Comparator
  */
typedef struct
{
  __IO uint32_t CSR;              /*!< COMP control and status register,           Address offset: 0x00 */
  __IO uint32_t FR;               /*!< COMP filter register,                       Address offset: 0x04 */
} COMP_TypeDef;

typedef struct
{
  __IO uint32_t CSR_ODD;       /*!< COMP control and status register located in register of comparator instance 1, used for bits common to several COMP instances,  Address offset: 0x00 */
  __IO uint32_t FR_ODD;
  uint32_t RESERVED0[2];        /*Reserved*/
  __IO uint32_t CSR_EVEN;      /*!< COMP control and status register located in register of comparator instance 2, used for bits common to several COMP instances, Address offset: 0x010 */
  __IO uint32_t FR_EVEN;
} COMP_Common_TypeDef;

/**
* @brief CRC Registers
*/
typedef struct
{
   __IO uint32_t DR;               /*!< CRC DR Register,                    Address offset: 0x00  */
   __IO uint32_t IDR;              /*!< CRC IDR Register,                   Address offset: 0x04  */
   __IO uint32_t CR;               /*!< CRC CR Register,                    Address offset: 0x08  */
} CRC_TypeDef;

/**
* @brief DBGMCU Registers
*/
typedef struct
{
    __IO uint32_t IDCODE;      /*!< DBGMCU desc IDCODE, Address offset: 0x00 */
    __IO uint32_t CR1;         /*!< DBGMCU desc CR1,    Address offset: 0x04 */
    __IO uint32_t CR2;         /*!< DBGMCU desc CR2,    Address offset: 0x04 */
}DBGMCU_TypeDef;

/**
* @brief DMA Controller Registers
*/
typedef struct
{
  __IO uint32_t ISR;              /*!< DMA interrupt status register,                 Address offset: 0x00 */
  __IO uint32_t IFCR;             /*!< DMA interrupt flag clear register,             Address offset: 0x04 */
} DMA_TypeDef;

typedef struct
{
  __IO uint32_t CCR;              /*!< DMA channel x configuration register        */
  __IO uint32_t CNDTR;            /*!< DMA channel x number of data register       */
  __IO uint32_t CPAR;             /*!< DMA channel x peripheral address register   */
  __IO uint32_t CMAR;             /*!< DMA channel x memory address register       */
  __IO uint32_t CNBTR;            /*!< DMA channel x CNBTR register               */
} DMA_Channel_TypeDef;

/**
* @brief EXTI Registers
*/
typedef struct
{
   __IO uint32_t IMR;              /*!< EXTI IMR Register,                  Address offset: 0x00  */
   __IO uint32_t EMR;              /*!< EXTI EMR Register,                  Address offset: 0x04  */
   __IO uint32_t RTSR;             /*!< EXTI RTSR Register,                 Address offset: 0x08  */
   __IO uint32_t FTSR;             /*!< EXTI FTSR Register,                 Address offset: 0x0C  */
   __IO uint32_t SWIER;            /*!< EXTI SWIER Register,                Address offset: 0x10  */
   __IO uint32_t PR;               /*!< EXTI PR Register,                   Address offset: 0x14  */
} EXTI_TypeDef;

/**
* @brief FMC Registers
*/
typedef struct
{
   __IO uint32_t ACR;              /*!< FLASH ACR Register,                 Address offset: 0x00  */
   __IO uint32_t RESERVED1;         
   __IO uint32_t KEYR;             /*!< FLASH KEYR Register,                Address offset: 0x08  */
   __IO uint32_t OPTKEYR;          /*!< FLASH OPTKEYR Register,             Address offset: 0x0C  */
   __IO uint32_t SR;               /*!< FLASH SR Register,                  Address offset: 0x10  */
   __IO uint32_t CR;               /*!< FLASH CR Register,                  Address offset: 0x14  */
   __IO uint32_t ECCR;             /*!< FLASH ECCR Register,                Address offset: 0x18  */
   __IO uint32_t RESERVED2;         
   __IO uint32_t OPTR1;            /*!< FLASH OPTR1 Register,               Address offset: 0x20  */
   __IO uint32_t OPTR2;            /*!< FLASH OPTR2 Register,               Address offset: 0x24  */
   __IO uint32_t RESERVED3;         
   __IO uint32_t BANK0_WRPR;       /*!< FLASH BANK0_WRPR Register,          Address offset: 0x2C  */
   __IO uint32_t BANK1_WRPR;       /*!< FLASH BANK1_WRPR Register,          Address offset: 0x30  */
   __IO uint32_t PCROP0SR;         /*!< FLASH PCROP0SR Register,            Address offset: 0x34  */
   __IO uint32_t PCROP0ER;         /*!< FLASH PCROP0ER Register,            Address offset: 0x38  */
   __IO uint32_t PCROP1SR;         /*!< FLASH PCROP1SR Register,            Address offset: 0x3C  */
   __IO uint32_t PCROP1ER;         /*!< FLASH PCROP1ER Register,            Address offset: 0x40  */
} FLASH_TypeDef;

/**
* @brief General Purpose I/O
*/
typedef struct
{
    __IO uint32_t MODER;       /*!< GPIO port mode register,               Address offset: 0x00      */
    __IO uint32_t OTYPER;      /*!< GPIO port output type register,        Address offset: 0x04      */
    __IO uint32_t OSPEEDR;     /*!< GPIO port output speed register,       Address offset: 0x08      */
    __IO uint32_t PUPDR;       /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
    __IO uint32_t IDR;         /*!< GPIO port input data register,         Address offset: 0x10      */
    __IO uint32_t ODR;         /*!< GPIO port output data register,        Address offset: 0x14      */
    __IO uint32_t BSRR;        /*!< GPIO port bit set/reset  register,     Address offset: 0x18      */
    __IO uint32_t LCKR;        /*!< GPIO port configuration lock register, Address offset: 0x1C      */
    __IO uint32_t AFR[2];      /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
    __IO uint32_t BRR;         /*!< GPIO Bit Reset register,               Address offset: 0x28      */
} GPIO_TypeDef;

/**
* @brief I2C Registers
*/
typedef struct
{
   __IO uint32_t CR1;              /*!< I2C CR1 Register,                   Address offset: 0x00  */
   __IO uint32_t CR2;              /*!< I2C CR2 Register,                   Address offset: 0x04  */
   __IO uint32_t OAR1;             /*!< I2C OAR1 Register,                  Address offset: 0x08  */
   __IO uint32_t OAR2;             /*!< I2C OAR2 Register,                  Address offset: 0x0C  */
   __IO uint32_t DR;               /*!< I2C DR Register,                    Address offset: 0x10  */
   __IO uint32_t SR1;              /*!< I2C SR1 Register,                   Address offset: 0x14  */
   __IO uint32_t SR2;              /*!< I2C SR2 Register,                   Address offset: 0x18  */
   __IO uint32_t CCR;              /*!< I2C CCR Register,                   Address offset: 0x1C  */
   __IO uint32_t TRISE;            /*!< I2C TRISE Register,                 Address offset: 0x20  */
   __IO uint32_t TIMEOUTR;         /*!< I2C TIMEOUTR Register,              Address offset: 0x24  */
} I2C_TypeDef;

/**
* @brief IWDG Registers
*/
typedef struct
{
   __IO uint32_t KR;               /*!< IWDG KR Register,                   Address offset: 0x0  */
   __IO uint32_t PR;               /*!< IWDG PR Register,                   Address offset: 0x4  */
   __IO uint32_t RLR;              /*!< IWDG RLR Register,                  Address offset: 0x8  */
   __IO uint32_t SR;               /*!< IWDG SR Register,                   Address offset: 0xC  */
}IWDG_TypeDef;

/**
* @brief LPTIM Registers
*/
typedef struct
{
  __IO uint32_t ISR;              /*!< LPTIM Interrupt and Status register,                Address offset: 0x00 */
  __IO uint32_t ICR;              /*!< LPTIM Interrupt Clear register,                     Address offset: 0x04 */
  __IO uint32_t IER;              /*!< LPTIM Interrupt Enable register,                    Address offset: 0x08 */
  __IO uint32_t CFGR;             /*!< LPTIM Configuration register,                       Address offset: 0x0C */
  __IO uint32_t CR;               /*!< LPTIM Control register,                             Address offset: 0x10 */
  __IO uint32_t CMP;              /*!< LPTIM CMP register,                                 Address offset: 0x14 */
  __IO uint32_t ARR;              /*!< LPTIM Autoreload register,                          Address offset: 0x18 */
  __IO uint32_t CNT;              /*!< LPTIM Counter register,                             Address offset: 0x1C */
  __IO uint32_t OR;               /*!< LPTIM OR register,                                  Address offset: 0x20 */
} LPTIM_TypeDef;

/**
* @brief OPA Registers
*/
typedef struct
{
   __IO uint32_t CSR;              /*!< OPA CSR Register,                  Address offset: 0x04  */
   __IO uint32_t RESERVED1[6];      
   __IO uint32_t FR;               /*!< OPA FR Register,                   Address offset: 0x20  */   
   __IO uint32_t INTR;             /*!< OPA INTR Register,                 Address offset: 0x24  */
} OPA_TypeDef;

/**
* @brief PWR Registers
*/
typedef struct
{
   __IO uint32_t CR1;              /*!< PWR CR1 Register,                   Address offset: 0x00  */
   __IO uint32_t CR2;              /*!< PWR CR2 Register,                   Address offset: 0x04  */
   __IO uint32_t CR3;              /*!< PWR CR3 Register,                   Address offset: 0x08  */
   __IO uint32_t CR4;              /*!< PWR CR4 Register,                   Address offset: 0x0C  */
   __IO uint32_t SR;               /*!< PWR SR Register,                    Address offset: 0x10  */
   __IO uint32_t SCR;              /*!< PWR SCR Register,                   Address offset: 0x14  */
} PWR_TypeDef;

/**
* @brief RCC Registers
*/
typedef struct
{
   __IO uint32_t CR;               /*!< RCC CR Register,                    Address offset: 0x00  */
   __IO uint32_t CFGR;             /*!< RCC CFGR Register,                  Address offset: 0x04  */
   __IO uint32_t CIR;              /*!< RCC CIR Register,                   Address offset: 0x08  */
   __IO uint32_t RESERVED1[7];      
   __IO uint32_t AHBRSTR;          /*!< RCC AHBRSTR Register,               Address offset: 0x28  */
   __IO uint32_t RESERVED2[3];      
   __IO uint32_t APB1RSTR1;        /*!< RCC APB1RSTR1 Register,             Address offset: 0x38  */
   __IO uint32_t APB1RSTR2;        /*!< RCC APB1RSTR2 Register,             Address offset: 0x3C  */
   __IO uint32_t APB2RSTR;         /*!< RCC APB2RSTR Register,              Address offset: 0x40  */
   __IO uint32_t RESERVED3;         
   __IO uint32_t AHBENR;           /*!< RCC AHBENR Register,                Address offset: 0x48  */
   __IO uint32_t RESERVED4[3];      
   __IO uint32_t APB1ENR1;         /*!< RCC APB1ENR1 Register,              Address offset: 0x58  */
   __IO uint32_t APB1ENR2;         /*!< RCC APB1ENR2 Register,              Address offset: 0x5C  */
   __IO uint32_t APB2ENR;          /*!< RCC APB2ENR Register,               Address offset: 0x60  */
   __IO uint32_t RESERVED5;         
   __IO uint32_t CCIPR;            /*!< RCC CCIPR Register,                 Address offset: 0x68  */
   __IO uint32_t RESERVED6;         
   __IO uint32_t BDCR;             /*!< RCC BDCR Register,                  Address offset: 0x70  */
   __IO uint32_t CSR;              /*!< RCC CSR Register,                   Address offset: 0x74  */
   __IO uint32_t CFGR1;            /*!< RCC CFGR1 Register,                 Address offset: 0x78  */
   __IO uint32_t CFGR2;            /*!< RCC CFGR2 Register,                 Address offset: 0x7C  */
   __IO uint32_t CFGR3;            /*!< RCC CFGR3 Register,                 Address offset: 0x80  */
} RCC_TypeDef;

/**
* @brief RTC Registers
*/
typedef struct
{
   __IO uint32_t CRH;              /*!< RTC CRH Register,                   Address offset: 0x00  */
   __IO uint32_t CRL;              /*!< RTC CRL Register,                   Address offset: 0x04  */
   __IO uint32_t PRLH;             /*!< RTC PRLH Register,                  Address offset: 0x08  */
   __IO uint32_t PRLL;             /*!< RTC PRLL Register,                  Address offset: 0x0C  */
   __IO uint32_t DIVH;             /*!< RTC DIVH Register,                  Address offset: 0x10  */
   __IO uint32_t DIVL;             /*!< RTC DIVL Register,                  Address offset: 0x14  */
   __IO uint32_t CNTH;             /*!< RTC CNTH Register,                  Address offset: 0x18  */
   __IO uint32_t CNTL;             /*!< RTC CNTL Register,                  Address offset: 0x1C  */
   __IO uint32_t ALRH;             /*!< RTC ALRH Register,                  Address offset: 0x20  */
   __IO uint32_t ALRL;             /*!< RTC ALRL Register,                  Address offset: 0x24  */
   __IO uint32_t RESERVED1[2];      
   __IO uint32_t TMPCFGR;          /*!< RTC TMPCFGR Register,               Address offset: 0x30  */
   __IO uint32_t TMPCSR;           /*!< RTC TMPCSR Register,                Address offset: 0x34  */
   __IO uint32_t CALIBR;           /*!< RTC CALIBR Register,                Address offset: 0x38  */
   __IO uint32_t RESERVED2;         
   __IO uint32_t BKPDR0;           /*!< RTC BKPDR0 Register,                Address offset: 0x40  */
   __IO uint32_t BKPDR1;           /*!< RTC BKPDR1 Register,                Address offset: 0x44  */
   __IO uint32_t BKPDR2;           /*!< RTC BKPDR2 Register,                Address offset: 0x48  */
   __IO uint32_t BKPDR3;           /*!< RTC BKPDR3 Register,                Address offset: 0x4C  */
   __IO uint32_t BKPDR4;           /*!< RTC BKPDR4 Register,                Address offset: 0x50  */
} RTC_TypeDef;

/**
* @brief SPI Registers
*/
typedef struct
{
   __IO uint32_t CR1;              /*!< SPI CR1 Register,                   Address offset: 0x00  */
   __IO uint32_t CR2;              /*!< SPI CR2 Register,                   Address offset: 0x04  */
   __IO uint32_t SR;               /*!< SPI SR Register,                    Address offset: 0x08  */
   __IO uint32_t DR;               /*!< SPI DR Register,                    Address offset: 0x0C  */
   __IO uint32_t CRCPR;            /*!< SPI CRCPR Register,                 Address offset: 0x10  */
   __IO uint32_t RXCRCR;           /*!< SPI RXCRCR Register,                Address offset: 0x14  */
   __IO uint32_t TXCRCR;           /*!< SPI TXCRCR Register,                Address offset: 0x18  */
   __IO uint32_t I2SCFGR;          /*!< SPI I2SCFGR Register,               Address offset: 0x1C  */
   __IO uint32_t I2SPR;            /*!< SPI I2SPR Register,                 Address offset: 0x20  */
} SPI_TypeDef;


/**
* @brief SYSCFG Registers
*/
typedef struct
{
   __IO uint32_t CFGR[4];          /*!< SYSCFG configuration register,   Address offset: 0x00 ~ 0x0F */
   __IO uint32_t RESERVED1;
   __IO uint32_t EXTICR[4];        /*!< SYSCFG external interrupt configuration registers,   Address offset: 0x14-0x23 */
   __IO uint32_t PAENS;            /*!< SYSCFG desc PAENS,   Address offset: 0x24 */
   __IO uint32_t PBENS;            /*!< SYSCFG desc PBENS,   Address offset: 0x28 */
   __IO uint32_t PCENS;            /*!< SYSCFG desc PCENS,   Address offset: 0x2C */
   __IO uint32_t PDENS;            /*!< SYSCFG desc PDENS,   Address offset: 0x30 */
   __IO uint32_t RESERVED2[3];
   __IO uint32_t COMP_ANA2ENR;     /*!< COMP ANA2ENR Register, Address offset: 0x40  */
} SYSCFG_TypeDef;

/**
* @brief TIM Registers
*/
typedef struct
{
   __IO uint32_t CR1;              /*!< TIM CR1 Register,                  Address offset: 0x0000  */
   __IO uint32_t CR2;              /*!< TIM CR2 Register,                  Address offset: 0x0004  */
   __IO uint32_t SMCR;             /*!< TIM SMCR Register,                 Address offset: 0x0008  */
   __IO uint32_t DIER;             /*!< TIM DIER Register,                 Address offset: 0x000C  */
   __IO uint32_t SR;               /*!< TIM SR Register,                   Address offset: 0x0010  */
   __IO uint32_t EGR;              /*!< TIM EGR Register,                  Address offset: 0x0014  */
   __IO uint32_t CCMR1;            /*!< TIM CCMR1 Register,                Address offset: 0x0018  */
   __IO uint32_t CCMR2;            /*!< TIM CCMR2 Register,                Address offset: 0x001C  */
   __IO uint32_t CCER;             /*!< TIM CCER Register,                 Address offset: 0x0020  */
   __IO uint32_t CNT;              /*!< TIM CNT Register,                  Address offset: 0x0024  */
   __IO uint32_t PSC;              /*!< TIM PSC Register,                  Address offset: 0x0028  */
   __IO uint32_t ARR;              /*!< TIM ARR Register,                  Address offset: 0x002C  */
   __IO uint32_t RCR;              /*!< TIM RCR Register,                  Address offset: 0x0030  */
   __IO uint32_t CCR1;             /*!< TIM CCR1 Register,                 Address offset: 0x0034  */
   __IO uint32_t CCR2;             /*!< TIM CCR2 Register,                 Address offset: 0x0038  */
   __IO uint32_t CCR3;             /*!< TIM CCR3 Register,                 Address offset: 0x003C  */
   __IO uint32_t CCR4;             /*!< TIM CCR4 Register,                 Address offset: 0x0040  */
   __IO uint32_t BDTR;             /*!< TIM BDTR Register,                 Address offset: 0x0044  */
   __IO uint32_t CCR5;             /*!< TIM CCR5 Register,                 Address offset: 0x0048  */
   __IO uint32_t CCR6;             /*!< TIM CCR6 Register,                 Address offset: 0x004C  */
   __IO uint32_t CCMR3;            /*!< TIM CCMR3 Register,                Address offset: 0x0050  */
   __IO uint32_t RESERVED1[2];      
   __IO uint32_t TISEL;            /*!< TIM TISEL Register,                Address offset: 0x005C  */
   __IO uint32_t AF1;              /*!< TIM AF1 Register,                  Address offset: 0x0060  */
   __IO uint32_t AF2;              /*!< TIM AF2 Register,                  Address offset: 0x0064  */
   __IO uint32_t RESERVED2[221];    
   __IO uint32_t DCR;              /*!< TIM DCR Register,                  Address offset: 0x03DC  */
   __IO uint32_t DMAR;             /*!< TIM DMAR Register,                 Address offset: 0x03E0  */
} TIM_TypeDef;

/**
* @brief PWM Registers
*/
typedef struct
{
   __IO uint32_t CR1;              /*!< PWM CR1 Register,                   Address offset: 0x0000  */
   __IO uint32_t CR2;              /*!< PWM CR2 Register,                   Address offset: 0x0004  */
   __IO uint32_t SMCR;             /*!< PWM SMCR Register,                  Address offset: 0x0008  */
   __IO uint32_t DIER;             /*!< PWM DIER Register,                  Address offset: 0x000C  */
   __IO uint32_t SR;               /*!< PWM SR Register,                    Address offset: 0x0010  */
   __IO uint32_t EGR;              /*!< PWM EGR Register,                   Address offset: 0x0014  */
   __IO uint32_t CMR;              /*!< PWM CMR Register,                   Address offset: 0x0018  */
   __IO uint32_t RESERVED1;         
   __IO uint32_t CER;              /*!< PWM CER Register,                   Address offset: 0x0020  */
   __IO uint32_t CNT;              /*!< PWM CNT Register,                   Address offset: 0x0024  */
   __IO uint32_t PSC;              /*!< PWM PSC Register,                   Address offset: 0x0028  */
   __IO uint32_t ARR;              /*!< PWM ARR Register,                   Address offset: 0x002C  */
   __IO uint32_t RESERVED2;         
   __IO uint32_t CCR1;             /*!< PWM CCR1 Register,                  Address offset: 0x0034  */
   __IO uint32_t CCR2;             /*!< PWM CCR2 Register,                  Address offset: 0x0038  */
   __IO uint32_t CCR3;             /*!< PWM CCR3 Register,                  Address offset: 0x003C  */
   __IO uint32_t CCR4;             /*!< PWM CCR4 Register,                  Address offset: 0x0040  */
   __IO uint32_t BDTR;             /*!< PWM BDTR Register,                  Address offset: 0x0044  */
   __IO uint32_t DCR;              /*!< PWM DCR Register,                   Address offset: 0x48  */
   __IO uint32_t DMAR;             /*!< PWM DMAR Register,                  Address offset: 0x4C  */
} PWM_TypeDef;

/**
* @brief USART Registers
*/
typedef struct
{
   __IO uint32_t SR;               /*!< USART SR Register,                  Address offset: 0x00  */
   __IO uint32_t DR;               /*!< USART DR Register,                  Address offset: 0x04  */
   __IO uint32_t BRR;              /*!< USART BRR Register,                 Address offset: 0x08  */
   __IO uint32_t CR1;              /*!< USART CR1 Register,                 Address offset: 0x0C  */
   __IO uint32_t CR2;              /*!< USART CR2 Register,                 Address offset: 0x10  */
   __IO uint32_t CR3;              /*!< USART CR3 Register,                 Address offset: 0x14  */
   __IO uint32_t GTPR;             /*!< USART GTPR Register,                Address offset: 0x18  */
   __IO uint32_t RTOR;             /*!< USART RTOR Register,                Address offset: 0x1C  */
} USART_TypeDef;


/**
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */
typedef struct
{
  __IO uint32_t DR;          /*!< UART DR Register,           Address offset: 0x00  */
  __IO uint32_t BRR;         /*!< UART BRR register,          Address offset: 0x04  */
  __IO uint32_t RESERVED1;   
  __IO uint32_t RESERVED2;        /*!< UART BUSY  register 1,      Address offset: 0x0C  */
  __IO uint32_t SR;          /*!< UART SR  register 2,        Address offset: 0x10  */
  __IO uint32_t CR1;         /*!< UART Control register 1,    Address offset: 0x14  */
  __IO uint32_t CR2;         /*!< UART Control register 2,    Address offset: 0x18  */
  __IO uint32_t CR3;         /*!< UART Control register 3,    Address offset: 0x1C  */
  __IO uint32_t RAR;         /*!< UART RAR register,          Address offset: 0x20  */
  __IO uint32_t TAR;         /*!< UART TAR register,          Address offset: 0x24  */
  __IO uint32_t BRRF;        /*!< UART BRRF register,         Address offset: 0x28  */
} UART_TypeDef;

/**
* @brief LPUART Registers
*/
typedef struct
{
   __IO uint32_t CR1;              /*!< LPUART CR1 Register,                Address offset: 0x00  */
   __IO uint32_t CR2;              /*!< LPUART CR2 Register,                Address offset: 0x04  */
   __IO uint32_t CR3;              /*!< LPUART CR3 Register,                Address offset: 0x08  */
   __IO uint32_t BRR;              /*!< LPUART BRR Register,                Address offset: 0x0C  */
   __IO uint32_t RESERVED1[2];      
   __IO uint32_t RQR;              /*!< LPUART RQR Register,                Address offset: 0x18  */
   __IO uint32_t ISR;              /*!< LPUART ISR Register,                Address offset: 0x1C  */
   __IO uint32_t ICR;              /*!< LPUART ICR Register,                Address offset: 0x20  */
   __IO uint32_t RDR;              /*!< LPUART RDR Register,                Address offset: 0x24  */
   __IO uint32_t TDR;              /*!< LPUART TDR Register,                Address offset: 0x28  */
   __IO uint32_t PRESC;            /*!< LPUART PRESC Register,              Address offset: 0x2C  */
} LPUART_TypeDef;

/**
* @brief WWDG Registers
*/
typedef struct
{
   __IO uint32_t CR;               /*!< WWDR CR Register,                   Address offset: 0x0  */
   __IO uint32_t CFR;              /*!< WWDG CFR Register,                  Address offset: 0x4  */
   __IO uint32_t SR;               /*!< WWDG SR Register,                   Address offset: 0x8  */
}WWDG_TypeDef;

/*!< Peripheral memory map */
#define FLASH_BASE            (0x08000000UL)                         /*!< FLASH base address */
#define FLASH_END             (0x0801FFFFUL)                         /*!< FLASH end address */
#define FLASH_SIZE            (FLASH_END - FLASH_BASE + 1)
#define FLASH_PAGE_SIZE       (0x00000080UL)                         /*!< FLASH Page Size, 128 Bytes */
#define FLASH_PAGE_NB         (FLASH_SIZE / FLASH_PAGE_SIZE)
#define FLASH_SECTOR_SIZE     (0x00001000UL)                         /*!< FLASH Sector Size, 4096 Bytes */
#define FLASH_SECTOR_NB       (FLASH_SIZE / FLASH_SECTOR_SIZE)
#define SRAM1_BASE            (0x20000000UL)                         /*!< SRAM1(up to 96 KB) base address */
#define PERIPH_BASE           (0x40000000UL)                         /*!< Peripheral base address */
#define SRAM1_BB_BASE         (0x22000000UL)                         /*!< SRAM1(96 KB) base address in the bit-band region */
#define PERIPH_BB_BASE        (0x42000000UL)                         /*!< Peripheral base address in the bit-band region */
#define OB_BASE               (0x1FFF1100UL)                         /*!< Flash Option Bytes base address */
#define UID_BASE              (0x1FFF1380UL)                         /*!< Unique device ID register base address */

/* Legacy defines */
#define SRAM_BASE             SRAM1_BASE

#define APB1PERIPH_BASE                        PERIPH_BASE
#define APB2PERIPH_BASE                        (PERIPH_BASE + 0x00010000UL)
#define AHBPERIPH_BASE                         (PERIPH_BASE + 0x00020000UL)

/*!< APB1 peripherals */
#define TIM2_BASE                              (0x40000000UL)
#define TIM3_BASE                              (0x40000400UL)
#define TIM4_BASE                              (0x40000800UL)
#define TIM6_BASE                              (0x40001000UL)
#define TIM7_BASE                              (0x40001400UL)
#define RTC_BASE                               (0x40002800UL)
#define WWDG_BASE                              (0x40002C00UL)
#define IWDG_BASE                              (0x40003000UL)
#define PWM1_BASE                              (0x40003400UL)
#define SPI2_BASE                              (0x40003800UL)
#define PWM2_BASE                              (0x40004000UL)
#define UART1_BASE                             (0x40004C00UL)
#define UART2_BASE                             (0x40005000UL)
#define I2C1_BASE                              (0x40005400UL)
#define I2C2_BASE                              (0x40005800UL)
#define PWR_BASE                               (0x40007000UL)
#define LPTIM1_BASE                            (0x40007C00UL)
#define LPUART1_BASE                           (0x40008000UL)

/*!< APB2 peripherals */
#define SYSCFG_BASE                            (0x40010000UL)
#define EXTI_BASE                              (0x40010400UL)
#define ADC1_BASE                              (0x40012400UL)
#define ADC_COMMON_BASE                        (ADC1_BASE + 0x00000308UL)
#define TIM1_BASE                              (0x40012C00UL)
#define SPI1_BASE                              (0x40013000UL)
#define USART1_BASE                            (0x40013800UL)
#define PWM3_BASE                              (0x40014000UL)
#define TIM15_BASE                             (0x40015800UL)
#define TIM16_BASE                             (0x40015C00UL)
#define TIM17_BASE                             (0x40016000UL)
#define COMP1_BASE                             (0x40016C00UL)
#define COMP2_BASE                             (0x40016C10UL)
#define OPA_BASE                               (0x40017000UL)
#define OPA1_BASE                              (0x40017000UL)
#define OPA2_BASE                              (0x40017004UL)
#define PWM4_BASE                              (0x40017800UL)

/*!< AHB1 peripherals */
#define DMA1_BASE                              (AHBPERIPH_BASE + 0x00000000UL)
#define RCC_BASE                               (AHBPERIPH_BASE + 0x1000)
#define FLASH_R_BASE                           (AHBPERIPH_BASE + 0x2000) /*!< Flash registers base address */
#define CRC_BASE                               (AHBPERIPH_BASE + 0x3000)
#define GPIOA_BASE                             (AHBPERIPH_BASE + 0x4000)
#define GPIOB_BASE                             (AHBPERIPH_BASE + 0x4400)
#define GPIOC_BASE                             (AHBPERIPH_BASE + 0x4800)
#define GPIOD_BASE                             (AHBPERIPH_BASE + 0x4C00)

#define DMA1_Channel1_BASE                     (AHBPERIPH_BASE + 0x00000008UL)
#define DMA1_Channel2_BASE                     (AHBPERIPH_BASE + 0x0000001CUL)
#define DMA1_Channel3_BASE                     (AHBPERIPH_BASE + 0x00000030UL)
#define DMA1_Channel4_BASE                     (AHBPERIPH_BASE + 0x00000044UL)
#define DMA1_Channel5_BASE                     (AHBPERIPH_BASE + 0x00000058UL)
#define DMA1_Channel6_BASE                     (AHBPERIPH_BASE + 0x0000006CUL)
#define DMA1_Channel7_BASE                     (AHBPERIPH_BASE + 0x00000080UL)
#define DMA1_Channel8_BASE                     (AHBPERIPH_BASE + 0x00000094UL)

/* Debug MCU registers base address */
#define DBGMCU_BASE                            (0xE0042000UL)

#define ADC1                                   ((ADC_TypeDef *) ADC1_BASE)
#define ADC_COMMON                             ((ADC_Common_TypeDef *) ADC_COMMON_BASE)
#define COMP1                                  ((COMP_TypeDef *) COMP1_BASE)
#define COMP2                                  ((COMP_TypeDef *) COMP2_BASE)
#define COMP12_COMMON                          ((COMP_Common_TypeDef *) COMP1_BASE)
#define CRC                                    ((CRC_TypeDef *) CRC_BASE)
#define DBGMCU                                 ((DBGMCU_TypeDef *) DBGMCU_BASE)

#define DMA1                                   ((DMA_TypeDef *)DMA1_BASE)
#define DMA1_Channel1                          ((DMA_Channel_TypeDef *)DMA1_Channel1_BASE)
#define DMA1_Channel2                          ((DMA_Channel_TypeDef *)DMA1_Channel2_BASE)
#define DMA1_Channel3                          ((DMA_Channel_TypeDef *)DMA1_Channel3_BASE)
#define DMA1_Channel4                          ((DMA_Channel_TypeDef *)DMA1_Channel4_BASE)
#define DMA1_Channel5                          ((DMA_Channel_TypeDef *)DMA1_Channel5_BASE)
#define DMA1_Channel6                          ((DMA_Channel_TypeDef *)DMA1_Channel6_BASE)
#define DMA1_Channel7                          ((DMA_Channel_TypeDef *)DMA1_Channel7_BASE)
#define DMA1_Channel8                          ((DMA_Channel_TypeDef *)DMA1_Channel8_BASE)
#define EXTI                                   ((EXTI_TypeDef *) EXTI_BASE)
#define FLASH                                  ((FLASH_TypeDef *) FLASH_R_BASE)
#define OB                                     ((OB_TypeDef *) OB_BASE)
#define OPA                                    ((OPA_TypeDef *) OPA_BASE)
#define OPA1                                   ((OPA_TypeDef *) OPA1_BASE)
#define OPA2                                   ((OPA_TypeDef *) OPA2_BASE)
#define GPIOA                                  ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB                                  ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC                                  ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD                                  ((GPIO_TypeDef *) GPIOD_BASE)
#define I2C1                                   ((I2C_TypeDef *) I2C1_BASE)
#define I2C2                                   ((I2C_TypeDef *) I2C2_BASE)
#define IWDG                                   ((IWDG_TypeDef *) IWDG_BASE)
#define LPTIM                                  ((LPTIM_TypeDef *) LPTIM_BASE)
#define LPTIM1                                 ((LPTIM_TypeDef *) LPTIM1_BASE)
#define LPUART1                                ((LPUART_TypeDef *) LPUART1_BASE)
#define PWR                                    ((PWR_TypeDef *) PWR_BASE)
#define RCC                                    ((RCC_TypeDef *) RCC_BASE)
#define RTC                                    ((RTC_TypeDef *) RTC_BASE)
#define SPI1                                   ((SPI_TypeDef *) SPI1_BASE)
#define SPI2                                   ((SPI_TypeDef *) SPI2_BASE)
#define SYSCFG                                 ((SYSCFG_TypeDef *) SYSCFG_BASE)
#define PWM1                                   ((PWM_TypeDef *) PWM1_BASE)
#define PWM2                                   ((PWM_TypeDef *) PWM2_BASE)
#define PWM3                                   ((PWM_TypeDef *) PWM3_BASE)
#define PWM4                                   ((PWM_TypeDef *) PWM4_BASE)
#define TIM1                                   ((TIM_TypeDef *) TIM1_BASE)
#define TIM2                                   ((TIM_TypeDef *) TIM2_BASE)
#define TIM3                                   ((TIM_TypeDef *) TIM3_BASE)
#define TIM4                                   ((TIM_TypeDef *) TIM4_BASE)
#define TIM6                                   ((TIM_TypeDef *) TIM6_BASE)
#define TIM7                                   ((TIM_TypeDef *) TIM7_BASE)
#define TIM8                                   ((TIM_TypeDef *) TIM8_BASE)
#define TIM15                                  ((TIM_TypeDef *) TIM15_BASE)
#define TIM16                                  ((TIM_TypeDef *) TIM16_BASE)
#define TIM17                                  ((TIM_TypeDef *) TIM17_BASE)
#define USART1                                 ((USART_TypeDef *) USART1_BASE)
#define UART1                                  ((UART_TypeDef *) UART1_BASE)
#define UART2                                  ((UART_TypeDef *) UART2_BASE)
#define WWDG                                   ((WWDG_TypeDef *) WWDG_BASE)

/********************************************************************************************************************/
/********************************* ADC ******************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for ADC_ISR register **********************************************/
#define ADC_ISR_ADRDY_Pos                         (0U)
#define ADC_ISR_ADRDY_Msk                         (0x1UL<<ADC_ISR_ADRDY_Pos)                        /*!< 0x00000001 */
#define ADC_ISR_ADRDY                             ADC_ISR_ADRDY_Msk   
#define ADC_ISR_EOSMP_Pos                         (1U)
#define ADC_ISR_EOSMP_Msk                         (0x1UL<<ADC_ISR_EOSMP_Pos)                        /*!< 0x00000002 */
#define ADC_ISR_EOSMP                             ADC_ISR_EOSMP_Msk                                 
#define ADC_ISR_EOC_Pos                           (2U)
#define ADC_ISR_EOC_Msk                           (0x1UL<<ADC_ISR_EOC_Pos)                          /*!< 0x00000004 */
#define ADC_ISR_EOC                               ADC_ISR_EOC_Msk                                   
#define ADC_ISR_EOS_Pos                           (3U)
#define ADC_ISR_EOS_Msk                           (0x1UL<<ADC_ISR_EOS_Pos)                          /*!< 0x00000008 */
#define ADC_ISR_EOS                               ADC_ISR_EOS_Msk                                   
#define ADC_ISR_OVR_Pos                           (4U)
#define ADC_ISR_OVR_Msk                           (0x1UL<<ADC_ISR_OVR_Pos)                          /*!< 0x00000010 */
#define ADC_ISR_OVR                               ADC_ISR_OVR_Msk                                   
#define ADC_ISR_JEOC_Pos                          (5U)
#define ADC_ISR_JEOC_Msk                          (0x1UL<<ADC_ISR_JEOC_Pos)                         /*!< 0x00000020 */
#define ADC_ISR_JEOC                              ADC_ISR_JEOC_Msk                                  
#define ADC_ISR_JEOS_Pos                          (6U)
#define ADC_ISR_JEOS_Msk                          (0x1UL<<ADC_ISR_JEOS_Pos)                         /*!< 0x00000040 */
#define ADC_ISR_JEOS                              ADC_ISR_JEOS_Msk                                  
#define ADC_ISR_AWD1_Pos                          (7U)
#define ADC_ISR_AWD1_Msk                          (0x1UL<<ADC_ISR_AWD1_Pos)                         /*!< 0x00000080 */
#define ADC_ISR_AWD1                              ADC_ISR_AWD1_Msk                                  
#define ADC_ISR_AWD2_Pos                          (8U)
#define ADC_ISR_AWD2_Msk                          (0x1UL<<ADC_ISR_AWD2_Pos)                         /*!< 0x00000100 */
#define ADC_ISR_AWD2                              ADC_ISR_AWD2_Msk                                  
#define ADC_ISR_AWD3_Pos                          (9U)
#define ADC_ISR_AWD3_Msk                          (0x1UL<<ADC_ISR_AWD3_Pos)                         /*!< 0x00000200 */
#define ADC_ISR_AWD3                              ADC_ISR_AWD3_Msk                                  
#define ADC_ISR_EOCAL_Pos                         (11U)
#define ADC_ISR_EOCAL_Msk                         (0x1UL<<ADC_ISR_EOCAL_Pos)                        /*!< 0x00000800 */
#define ADC_ISR_EOCAL                             ADC_ISR_EOCAL_Msk                                 

/********************************* Bit definition for ADC_IER register **********************************************/
#define ADC_IER_ADRDYIE_Pos                       (0U)
#define ADC_IER_ADRDYIE_Msk                       (0x1UL<<ADC_IER_ADRDYIE_Pos)                      /*!< 0x00000001 */
#define ADC_IER_ADRDYIE                           ADC_IER_ADRDYIE_Msk                               
#define ADC_IER_EOSMPIE_Pos                       (1U)
#define ADC_IER_EOSMPIE_Msk                       (0x1UL<<ADC_IER_EOSMPIE_Pos)                      /*!< 0x00000002 */
#define ADC_IER_EOSMPIE                           ADC_IER_EOSMPIE_Msk                               
#define ADC_IER_EOCIE_Pos                         (2U)
#define ADC_IER_EOCIE_Msk                         (0x1UL<<ADC_IER_EOCIE_Pos)                        /*!< 0x00000004 */
#define ADC_IER_EOCIE                             ADC_IER_EOCIE_Msk                                 
#define ADC_IER_EOSIE_Pos                         (3U)
#define ADC_IER_EOSIE_Msk                         (0x1UL<<ADC_IER_EOSIE_Pos)                        /*!< 0x00000008 */
#define ADC_IER_EOSIE                             ADC_IER_EOSIE_Msk                                 
#define ADC_IER_OVRIE_Pos                         (4U)
#define ADC_IER_OVRIE_Msk                         (0x1UL<<ADC_IER_OVRIE_Pos)                        /*!< 0x00000010 */
#define ADC_IER_OVRIE                             ADC_IER_OVRIE_Msk                                 
#define ADC_IER_JEOCIE_Pos                        (5U)
#define ADC_IER_JEOCIE_Msk                        (0x1UL<<ADC_IER_JEOCIE_Pos)                       /*!< 0x00000020 */
#define ADC_IER_JEOCIE                            ADC_IER_JEOCIE_Msk                                
#define ADC_IER_JEOSIE_Pos                        (6U)
#define ADC_IER_JEOSIE_Msk                        (0x1UL<<ADC_IER_JEOSIE_Pos)                       /*!< 0x00000040 */
#define ADC_IER_JEOSIE                            ADC_IER_JEOSIE_Msk                                
#define ADC_IER_AWD1IE_Pos                        (7U)
#define ADC_IER_AWD1IE_Msk                        (0x1UL<<ADC_IER_AWD1IE_Pos)                       /*!< 0x00000080 */
#define ADC_IER_AWD1IE                            ADC_IER_AWD1IE_Msk                                
#define ADC_IER_AWD2IE_Pos                        (8U)
#define ADC_IER_AWD2IE_Msk                        (0x1UL<<ADC_IER_AWD2IE_Pos)                       /*!< 0x00000100 */
#define ADC_IER_AWD2IE                            ADC_IER_AWD2IE_Msk                                
#define ADC_IER_AWD3IE_Pos                        (9U)
#define ADC_IER_AWD3IE_Msk                        (0x1UL<<ADC_IER_AWD3IE_Pos)                       /*!< 0x00000200 */
#define ADC_IER_AWD3IE                            ADC_IER_AWD3IE_Msk                                
#define ADC_IER_EOCALIE_Pos                       (11U)
#define ADC_IER_EOCALIE_Msk                       (0x1UL<<ADC_IER_EOCALIE_Pos)                      /*!< 0x00000800 */
#define ADC_IER_EOCALIE                           ADC_IER_EOCALIE_Msk                               

/********************************* Bit definition for ADC_CR register ***********************************************/
#define ADC_CR_ADEN_Pos                           (0U)
#define ADC_CR_ADEN_Msk                           (0x1UL<<ADC_CR_ADEN_Pos)                          /*!< 0x00000001 */
#define ADC_CR_ADEN                               ADC_CR_ADEN_Msk                                   
#define ADC_CR_ADDIS_Pos                          (1U)
#define ADC_CR_ADDIS_Msk                          (0x1UL<<ADC_CR_ADDIS_Pos)                         /*!< 0x00000002 */
#define ADC_CR_ADDIS                              ADC_CR_ADDIS_Msk                                  
#define ADC_CR_ADSTART_Pos                        (2U)
#define ADC_CR_ADSTART_Msk                        (0x1UL<<ADC_CR_ADSTART_Pos)                       /*!< 0x00000004 */
#define ADC_CR_ADSTART                            ADC_CR_ADSTART_Msk                                
#define ADC_CR_JADSTART_Pos                       (3U)
#define ADC_CR_JADSTART_Msk                       (0x1UL<<ADC_CR_JADSTART_Pos)                      /*!< 0x00000008 */
#define ADC_CR_JADSTART                           ADC_CR_JADSTART_Msk                               
#define ADC_CR_ADSTP_Pos                          (4U)
#define ADC_CR_ADSTP_Msk                          (0x1UL<<ADC_CR_ADSTP_Pos)                         /*!< 0x00000010 */
#define ADC_CR_ADSTP                              ADC_CR_ADSTP_Msk                                  
#define ADC_CR_JADSTP_Pos                         (5U)
#define ADC_CR_JADSTP_Msk                         (0x1UL<<ADC_CR_JADSTP_Pos)                        /*!< 0x00000020 */
#define ADC_CR_JADSTP                             ADC_CR_JADSTP_Msk                                 
#define ADC_CR_RSTCAL_Pos                         (27U)
#define ADC_CR_RSTCAL_Msk                         (0x1UL<<ADC_CR_RSTCAL_Pos)                        /*!< 0x08000000 */
#define ADC_CR_RSTCAL                             ADC_CR_RSTCAL_Msk                                 
#define ADC_CR_ADCAL_Pos                          (31U)
#define ADC_CR_ADCAL_Msk                          (0x1UL<<ADC_CR_ADCAL_Pos)                         /*!< 0x80000000 */
#define ADC_CR_ADCAL                              ADC_CR_ADCAL_Msk                                  

/********************************* Bit definition for ADC_CFGR register *********************************************/
#define ADC_CFGR_DMAEN_Pos                        (0U)
#define ADC_CFGR_DMAEN_Msk                        (0x1UL<<ADC_CFGR_DMAEN_Pos)                       /*!< 0x00000001 */
#define ADC_CFGR_DMAEN                            ADC_CFGR_DMAEN_Msk                                
#define ADC_CFGR_DMACFG_Pos                       (1U)
#define ADC_CFGR_DMACFG_Msk                       (0x1UL<<ADC_CFGR_DMACFG_Pos)                      /*!< 0x00000002 */
#define ADC_CFGR_DMACFG                           ADC_CFGR_DMACFG_Msk                               
#define ADC_CFGR_RES_Pos                          (3U)
#define ADC_CFGR_RES_Msk                          (0x3UL<<ADC_CFGR_RES_Pos)                         /*!< 0x00000018 */
#define ADC_CFGR_RES                              ADC_CFGR_RES_Msk
#define ADC_CFGR_RES_0                            (0x1UL<<ADC_CFGR_RES_Pos)                         /*!< 0x00000008 */
#define ADC_CFGR_RES_1                            (0x2UL<<ADC_CFGR_RES_Pos)                         /*!< 0x00000010 */
#define ADC_CFGR_EXTSEL_Pos                       (5U)
#define ADC_CFGR_EXTSEL_Msk                       (0x1FUL<<ADC_CFGR_EXTSEL_Pos)                     /*!< 0x000003E0 */
#define ADC_CFGR_EXTSEL                           ADC_CFGR_EXTSEL_Msk
#define ADC_CFGR_EXTSEL_0                         (0x1UL<<ADC_CFGR_EXTSEL_Pos)                      /*!< 0x00000020 */
#define ADC_CFGR_EXTSEL_1                         (0x2UL<<ADC_CFGR_EXTSEL_Pos)                      /*!< 0x00000040 */
#define ADC_CFGR_EXTSEL_2                         (0x4UL<<ADC_CFGR_EXTSEL_Pos)                      /*!< 0x00000080 */
#define ADC_CFGR_EXTSEL_3                         (0x8UL<<ADC_CFGR_EXTSEL_Pos)                      /*!< 0x00000100 */
#define ADC_CFGR_EXTSEL_4                         (0x10UL<<ADC_CFGR_EXTSEL_Pos)                     /*!< 0x00000200 */
#define ADC_CFGR_EXTEN_Pos                        (10U)
#define ADC_CFGR_EXTEN_Msk                        (0x3UL<<ADC_CFGR_EXTEN_Pos)                       /*!< 0x00000C00 */
#define ADC_CFGR_EXTEN                            ADC_CFGR_EXTEN_Msk
#define ADC_CFGR_EXTEN_0                          (0x1UL<<ADC_CFGR_EXTEN_Pos)                       /*!< 0x00000400 */
#define ADC_CFGR_EXTEN_1                          (0x2UL<<ADC_CFGR_EXTEN_Pos)                       /*!< 0x00000800 */
#define ADC_CFGR_OVRMOD_Pos                       (12U)
#define ADC_CFGR_OVRMOD_Msk                       (0x1UL<<ADC_CFGR_OVRMOD_Pos)                      /*!< 0x00001000 */
#define ADC_CFGR_OVRMOD                           ADC_CFGR_OVRMOD_Msk                               
#define ADC_CFGR_CONT_Pos                         (13U)
#define ADC_CFGR_CONT_Msk                         (0x1UL<<ADC_CFGR_CONT_Pos)                        /*!< 0x00002000 */
#define ADC_CFGR_CONT                             ADC_CFGR_CONT_Msk                                 
#define ADC_CFGR_AUTDLY_Pos                       (14U)
#define ADC_CFGR_AUTDLY_Msk                       (0x1UL<<ADC_CFGR_AUTDLY_Pos)                      /*!< 0x00004000 */
#define ADC_CFGR_AUTDLY                           ADC_CFGR_AUTDLY_Msk                               
#define ADC_CFGR_ALIGN_Pos                        (15U)
#define ADC_CFGR_ALIGN_Msk                        (0x1UL<<ADC_CFGR_ALIGN_Pos)                       /*!< 0x00008000 */
#define ADC_CFGR_ALIGN                            ADC_CFGR_ALIGN_Msk                                
#define ADC_CFGR_DISCEN_Pos                       (16U)
#define ADC_CFGR_DISCEN_Msk                       (0x1UL<<ADC_CFGR_DISCEN_Pos)                      /*!< 0x00010000 */
#define ADC_CFGR_DISCEN                           ADC_CFGR_DISCEN_Msk                               
#define ADC_CFGR_DISCNUM_Pos                      (17U)
#define ADC_CFGR_DISCNUM_Msk                      (0x7UL<<ADC_CFGR_DISCNUM_Pos)                     /*!< 0x000E0000 */
#define ADC_CFGR_DISCNUM                          ADC_CFGR_DISCNUM_Msk
#define ADC_CFGR_DISCNUM_0                        (0x1UL<<ADC_CFGR_DISCNUM_Pos)                     /*!< 0x00020000 */
#define ADC_CFGR_DISCNUM_1                        (0x2UL<<ADC_CFGR_DISCNUM_Pos)                     /*!< 0x00040000 */
#define ADC_CFGR_DISCNUM_2                        (0x4UL<<ADC_CFGR_DISCNUM_Pos)                     /*!< 0x00080000 */
#define ADC_CFGR_JDISCEN_Pos                      (20U)
#define ADC_CFGR_JDISCEN_Msk                      (0x1UL<<ADC_CFGR_JDISCEN_Pos)                     /*!< 0x00100000 */
#define ADC_CFGR_JDISCEN                          ADC_CFGR_JDISCEN_Msk                              
#define ADC_CFGR_AWD1SGL_Pos                      (22U)
#define ADC_CFGR_AWD1SGL_Msk                      (0x1UL<<ADC_CFGR_AWD1SGL_Pos)                     /*!< 0x00400000 */
#define ADC_CFGR_AWD1SGL                          ADC_CFGR_AWD1SGL_Msk                              
#define ADC_CFGR_AWD1EN_Pos                       (23U)
#define ADC_CFGR_AWD1EN_Msk                       (0x1UL<<ADC_CFGR_AWD1EN_Pos)                      /*!< 0x00800000 */
#define ADC_CFGR_AWD1EN                           ADC_CFGR_AWD1EN_Msk                               
#define ADC_CFGR_JAWD1EN_Pos                      (24U)
#define ADC_CFGR_JAWD1EN_Msk                      (0x1UL<<ADC_CFGR_JAWD1EN_Pos)                     /*!< 0x01000000 */
#define ADC_CFGR_JAWD1EN                          ADC_CFGR_JAWD1EN_Msk                              
#define ADC_CFGR_JAUTO_Pos                        (25U)
#define ADC_CFGR_JAUTO_Msk                        (0x1UL<<ADC_CFGR_JAUTO_Pos)                       /*!< 0x02000000 */
#define ADC_CFGR_JAUTO                            ADC_CFGR_JAUTO_Msk                                
#define ADC_CFGR_AWD1CH_Pos                       (26U)
#define ADC_CFGR_AWD1CH_Msk                       (0x1FUL<<ADC_CFGR_AWD1CH_Pos)                     /*!< 0x7C000000 */
#define ADC_CFGR_AWD1CH                           ADC_CFGR_AWD1CH_Msk
#define ADC_CFGR_AWD1CH_0                         (0x1UL<<ADC_CFGR_AWD1CH_Pos)                      /*!< 0x04000000 */
#define ADC_CFGR_AWD1CH_1                         (0x2UL<<ADC_CFGR_AWD1CH_Pos)                      /*!< 0x08000000 */
#define ADC_CFGR_AWD1CH_2                         (0x4UL<<ADC_CFGR_AWD1CH_Pos)                      /*!< 0x10000000 */
#define ADC_CFGR_AWD1CH_3                         (0x8UL<<ADC_CFGR_AWD1CH_Pos)                      /*!< 0x20000000 */
#define ADC_CFGR_AWD1CH_4                         (0x10UL<<ADC_CFGR_AWD1CH_Pos)                     /*!< 0x40000000 */

/********************************* Bit definition for ADC_CFGR2 register ********************************************/
#define ADC_CFGR2_ROVSE_Pos                       (0U)
#define ADC_CFGR2_ROVSE_Msk                       (0x1UL<<ADC_CFGR2_ROVSE_Pos)                      /*!< 0x00000001 */
#define ADC_CFGR2_ROVSE                           ADC_CFGR2_ROVSE_Msk                               
#define ADC_CFGR2_JOVSE_Pos                       (1U)
#define ADC_CFGR2_JOVSE_Msk                       (0x1UL<<ADC_CFGR2_JOVSE_Pos)                      /*!< 0x00000002 */
#define ADC_CFGR2_JOVSE                           ADC_CFGR2_JOVSE_Msk                               
#define ADC_CFGR2_OVSR_Pos                        (2U)
#define ADC_CFGR2_OVSR_Msk                        (0x7UL<<ADC_CFGR2_OVSR_Pos)                       /*!< 0x0000001C */
#define ADC_CFGR2_OVSR                            ADC_CFGR2_OVSR_Msk
#define ADC_CFGR2_OVSR_0                          (0x1UL<<ADC_CFGR2_OVSR_Pos)                       /*!< 0x00000004 */
#define ADC_CFGR2_OVSR_1                          (0x2UL<<ADC_CFGR2_OVSR_Pos)                       /*!< 0x00000008 */
#define ADC_CFGR2_OVSR_2                          (0x4UL<<ADC_CFGR2_OVSR_Pos)                       /*!< 0x00000010 */
#define ADC_CFGR2_OVSS_Pos                        (5U)
#define ADC_CFGR2_OVSS_Msk                        (0xFUL<<ADC_CFGR2_OVSS_Pos)                       /*!< 0x000001E0 */
#define ADC_CFGR2_OVSS                            ADC_CFGR2_OVSS_Msk
#define ADC_CFGR2_OVSS_0                          (0x1UL<<ADC_CFGR2_OVSS_Pos)                       /*!< 0x00000020 */
#define ADC_CFGR2_OVSS_1                          (0x2UL<<ADC_CFGR2_OVSS_Pos)                       /*!< 0x00000040 */
#define ADC_CFGR2_OVSS_2                          (0x4UL<<ADC_CFGR2_OVSS_Pos)                       /*!< 0x00000080 */
#define ADC_CFGR2_OVSS_3                          (0x8UL<<ADC_CFGR2_OVSS_Pos)                       /*!< 0x00000100 */
#define ADC_CFGR2_TROVS_Pos                       (9U)
#define ADC_CFGR2_TROVS_Msk                       (0x1UL<<ADC_CFGR2_TROVS_Pos)                      /*!< 0x00000200 */
#define ADC_CFGR2_TROVS                           ADC_CFGR2_TROVS_Msk                               
#define ADC_CFGR2_ROVSM_Pos                       (10U)
#define ADC_CFGR2_ROVSM_Msk                       (0x1UL<<ADC_CFGR2_ROVSM_Pos)                      /*!< 0x00000400 */
#define ADC_CFGR2_ROVSM                           ADC_CFGR2_ROVSM_Msk                               
#define ADC_CFGR2_GCOMP_Pos                       (16U)
#define ADC_CFGR2_GCOMP_Msk                       (0x1UL<<ADC_CFGR2_GCOMP_Pos)                      /*!< 0x00010000 */
#define ADC_CFGR2_GCOMP                           ADC_CFGR2_GCOMP_Msk                               
#define ADC_CFGR2_CALNUM_Pos                      (28U)
#define ADC_CFGR2_CALNUM_Msk                      (0x7UL<<ADC_CFGR2_CALNUM_Pos)                     /*!< 0x70000000 */
#define ADC_CFGR2_CALNUM                          ADC_CFGR2_CALNUM_Msk
#define ADC_CFGR2_CALNUM_0                        (0x1UL<<ADC_CFGR2_CALNUM_Pos)                     /*!< 0x10000000 */
#define ADC_CFGR2_CALNUM_1                        (0x2UL<<ADC_CFGR2_CALNUM_Pos)                     /*!< 0x20000000 */
#define ADC_CFGR2_CALNUM_2                        (0x4UL<<ADC_CFGR2_CALNUM_Pos)                     /*!< 0x40000000 */

/********************************* Bit definition for ADC_SMPR1 register ********************************************/
#define ADC_SMPR1_SMP0_Pos                        (0U)
#define ADC_SMPR1_SMP0_Msk                        (0x7UL<<ADC_SMPR1_SMP0_Pos)                       /*!< 0x00000007 */
#define ADC_SMPR1_SMP0                            ADC_SMPR1_SMP0_Msk
#define ADC_SMPR1_SMP0_0                          (0x1UL<<ADC_SMPR1_SMP0_Pos)                       /*!< 0x00000001 */
#define ADC_SMPR1_SMP0_1                          (0x2UL<<ADC_SMPR1_SMP0_Pos)                       /*!< 0x00000002 */
#define ADC_SMPR1_SMP0_2                          (0x4UL<<ADC_SMPR1_SMP0_Pos)                       /*!< 0x00000004 */
#define ADC_SMPR1_SMP1_Pos                        (3U)
#define ADC_SMPR1_SMP1_Msk                        (0x7UL<<ADC_SMPR1_SMP1_Pos)                       /*!< 0x00000038 */
#define ADC_SMPR1_SMP1                            ADC_SMPR1_SMP1_Msk
#define ADC_SMPR1_SMP1_0                          (0x1UL<<ADC_SMPR1_SMP1_Pos)                       /*!< 0x00000008 */
#define ADC_SMPR1_SMP1_1                          (0x2UL<<ADC_SMPR1_SMP1_Pos)                       /*!< 0x00000010 */
#define ADC_SMPR1_SMP1_2                          (0x4UL<<ADC_SMPR1_SMP1_Pos)                       /*!< 0x00000020 */
#define ADC_SMPR1_SMP2_Pos                        (6U)
#define ADC_SMPR1_SMP2_Msk                        (0x7UL<<ADC_SMPR1_SMP2_Pos)                       /*!< 0x000001C0 */
#define ADC_SMPR1_SMP2                            ADC_SMPR1_SMP2_Msk
#define ADC_SMPR1_SMP2_0                          (0x1UL<<ADC_SMPR1_SMP2_Pos)                       /*!< 0x00000040 */
#define ADC_SMPR1_SMP2_1                          (0x2UL<<ADC_SMPR1_SMP2_Pos)                       /*!< 0x00000080 */
#define ADC_SMPR1_SMP2_2                          (0x4UL<<ADC_SMPR1_SMP2_Pos)                       /*!< 0x00000100 */
#define ADC_SMPR1_SMP3_Pos                        (9U)
#define ADC_SMPR1_SMP3_Msk                        (0x7UL<<ADC_SMPR1_SMP3_Pos)                       /*!< 0x00000E00 */
#define ADC_SMPR1_SMP3                            ADC_SMPR1_SMP3_Msk
#define ADC_SMPR1_SMP3_0                          (0x1UL<<ADC_SMPR1_SMP3_Pos)                       /*!< 0x00000200 */
#define ADC_SMPR1_SMP3_1                          (0x2UL<<ADC_SMPR1_SMP3_Pos)                       /*!< 0x00000400 */
#define ADC_SMPR1_SMP3_2                          (0x4UL<<ADC_SMPR1_SMP3_Pos)                       /*!< 0x00000800 */
#define ADC_SMPR1_SMP4_Pos                        (12U)
#define ADC_SMPR1_SMP4_Msk                        (0x7UL<<ADC_SMPR1_SMP4_Pos)                       /*!< 0x00007000 */
#define ADC_SMPR1_SMP4                            ADC_SMPR1_SMP4_Msk
#define ADC_SMPR1_SMP4_0                          (0x1UL<<ADC_SMPR1_SMP4_Pos)                       /*!< 0x00001000 */
#define ADC_SMPR1_SMP4_1                          (0x2UL<<ADC_SMPR1_SMP4_Pos)                       /*!< 0x00002000 */
#define ADC_SMPR1_SMP4_2                          (0x4UL<<ADC_SMPR1_SMP4_Pos)                       /*!< 0x00004000 */
#define ADC_SMPR1_SMP5_Pos                        (15U)
#define ADC_SMPR1_SMP5_Msk                        (0x7UL<<ADC_SMPR1_SMP5_Pos)                       /*!< 0x00038000 */
#define ADC_SMPR1_SMP5                            ADC_SMPR1_SMP5_Msk
#define ADC_SMPR1_SMP5_0                          (0x1UL<<ADC_SMPR1_SMP5_Pos)                       /*!< 0x00008000 */
#define ADC_SMPR1_SMP5_1                          (0x2UL<<ADC_SMPR1_SMP5_Pos)                       /*!< 0x00010000 */
#define ADC_SMPR1_SMP5_2                          (0x4UL<<ADC_SMPR1_SMP5_Pos)                       /*!< 0x00020000 */
#define ADC_SMPR1_SMP6_Pos                        (18U)
#define ADC_SMPR1_SMP6_Msk                        (0x7UL<<ADC_SMPR1_SMP6_Pos)                       /*!< 0x001C0000 */
#define ADC_SMPR1_SMP6                            ADC_SMPR1_SMP6_Msk
#define ADC_SMPR1_SMP6_0                          (0x1UL<<ADC_SMPR1_SMP6_Pos)                       /*!< 0x00040000 */
#define ADC_SMPR1_SMP6_1                          (0x2UL<<ADC_SMPR1_SMP6_Pos)                       /*!< 0x00080000 */
#define ADC_SMPR1_SMP6_2                          (0x4UL<<ADC_SMPR1_SMP6_Pos)                       /*!< 0x00100000 */
#define ADC_SMPR1_SMP7_Pos                        (21U)
#define ADC_SMPR1_SMP7_Msk                        (0x7UL<<ADC_SMPR1_SMP7_Pos)                       /*!< 0x00E00000 */
#define ADC_SMPR1_SMP7                            ADC_SMPR1_SMP7_Msk
#define ADC_SMPR1_SMP7_0                          (0x1UL<<ADC_SMPR1_SMP7_Pos)                       /*!< 0x00200000 */
#define ADC_SMPR1_SMP7_1                          (0x2UL<<ADC_SMPR1_SMP7_Pos)                       /*!< 0x00400000 */
#define ADC_SMPR1_SMP7_2                          (0x4UL<<ADC_SMPR1_SMP7_Pos)                       /*!< 0x00800000 */
#define ADC_SMPR1_SMP8_Pos                        (24U)
#define ADC_SMPR1_SMP8_Msk                        (0x7UL<<ADC_SMPR1_SMP8_Pos)                       /*!< 0x07000000 */
#define ADC_SMPR1_SMP8                            ADC_SMPR1_SMP8_Msk
#define ADC_SMPR1_SMP8_0                          (0x1UL<<ADC_SMPR1_SMP8_Pos)                       /*!< 0x01000000 */
#define ADC_SMPR1_SMP8_1                          (0x2UL<<ADC_SMPR1_SMP8_Pos)                       /*!< 0x02000000 */
#define ADC_SMPR1_SMP8_2                          (0x4UL<<ADC_SMPR1_SMP8_Pos)                       /*!< 0x04000000 */
#define ADC_SMPR1_SMP9_Pos                        (27U)
#define ADC_SMPR1_SMP9_Msk                        (0x7UL<<ADC_SMPR1_SMP9_Pos)                       /*!< 0x38000000 */
#define ADC_SMPR1_SMP9                            ADC_SMPR1_SMP9_Msk
#define ADC_SMPR1_SMP9_0                          (0x1UL<<ADC_SMPR1_SMP9_Pos)                       /*!< 0x08000000 */
#define ADC_SMPR1_SMP9_1                          (0x2UL<<ADC_SMPR1_SMP9_Pos)                       /*!< 0x10000000 */
#define ADC_SMPR1_SMP9_2                          (0x4UL<<ADC_SMPR1_SMP9_Pos)                       /*!< 0x20000000 */

/********************************* Bit definition for ADC_SMPR2 register ********************************************/
#define ADC_SMPR2_SMP10_Pos                       (0U)
#define ADC_SMPR2_SMP10_Msk                       (0x7UL<<ADC_SMPR2_SMP10_Pos)                      /*!< 0x00000007 */
#define ADC_SMPR2_SMP10                           ADC_SMPR2_SMP10_Msk
#define ADC_SMPR2_SMP10_0                         (0x1UL<<ADC_SMPR2_SMP10_Pos)                      /*!< 0x00000001 */
#define ADC_SMPR2_SMP10_1                         (0x2UL<<ADC_SMPR2_SMP10_Pos)                      /*!< 0x00000002 */
#define ADC_SMPR2_SMP10_2                         (0x4UL<<ADC_SMPR2_SMP10_Pos)                      /*!< 0x00000004 */
#define ADC_SMPR2_SMP11_Pos                       (3U)
#define ADC_SMPR2_SMP11_Msk                       (0x7UL<<ADC_SMPR2_SMP11_Pos)                      /*!< 0x00000038 */
#define ADC_SMPR2_SMP11                           ADC_SMPR2_SMP11_Msk
#define ADC_SMPR2_SMP11_0                         (0x1UL<<ADC_SMPR2_SMP11_Pos)                      /*!< 0x00000008 */
#define ADC_SMPR2_SMP11_1                         (0x2UL<<ADC_SMPR2_SMP11_Pos)                      /*!< 0x00000010 */
#define ADC_SMPR2_SMP11_2                         (0x4UL<<ADC_SMPR2_SMP11_Pos)                      /*!< 0x00000020 */
#define ADC_SMPR2_SMP12_Pos                       (6U)
#define ADC_SMPR2_SMP12_Msk                       (0x7UL<<ADC_SMPR2_SMP12_Pos)                      /*!< 0x000001C0 */
#define ADC_SMPR2_SMP12                           ADC_SMPR2_SMP12_Msk
#define ADC_SMPR2_SMP12_0                         (0x1UL<<ADC_SMPR2_SMP12_Pos)                      /*!< 0x00000040 */
#define ADC_SMPR2_SMP12_1                         (0x2UL<<ADC_SMPR2_SMP12_Pos)                      /*!< 0x00000080 */
#define ADC_SMPR2_SMP12_2                         (0x4UL<<ADC_SMPR2_SMP12_Pos)                      /*!< 0x00000100 */
#define ADC_SMPR2_SMP13_Pos                       (9U)
#define ADC_SMPR2_SMP13_Msk                       (0x7UL<<ADC_SMPR2_SMP13_Pos)                      /*!< 0x00000E00 */
#define ADC_SMPR2_SMP13                           ADC_SMPR2_SMP13_Msk
#define ADC_SMPR2_SMP13_0                         (0x1UL<<ADC_SMPR2_SMP13_Pos)                      /*!< 0x00000200 */
#define ADC_SMPR2_SMP13_1                         (0x2UL<<ADC_SMPR2_SMP13_Pos)                      /*!< 0x00000400 */
#define ADC_SMPR2_SMP13_2                         (0x4UL<<ADC_SMPR2_SMP13_Pos)                      /*!< 0x00000800 */
#define ADC_SMPR2_SMP14_Pos                       (12U)
#define ADC_SMPR2_SMP14_Msk                       (0x7UL<<ADC_SMPR2_SMP14_Pos)                      /*!< 0x00007000 */
#define ADC_SMPR2_SMP14                           ADC_SMPR2_SMP14_Msk
#define ADC_SMPR2_SMP14_0                         (0x1UL<<ADC_SMPR2_SMP14_Pos)                      /*!< 0x00001000 */
#define ADC_SMPR2_SMP14_1                         (0x2UL<<ADC_SMPR2_SMP14_Pos)                      /*!< 0x00002000 */
#define ADC_SMPR2_SMP14_2                         (0x4UL<<ADC_SMPR2_SMP14_Pos)                      /*!< 0x00004000 */
#define ADC_SMPR2_SMP15_Pos                       (15U)
#define ADC_SMPR2_SMP15_Msk                       (0x7UL<<ADC_SMPR2_SMP15_Pos)                      /*!< 0x00038000 */
#define ADC_SMPR2_SMP15                           ADC_SMPR2_SMP15_Msk
#define ADC_SMPR2_SMP15_0                         (0x1UL<<ADC_SMPR2_SMP15_Pos)                      /*!< 0x00008000 */
#define ADC_SMPR2_SMP15_1                         (0x2UL<<ADC_SMPR2_SMP15_Pos)                      /*!< 0x00010000 */
#define ADC_SMPR2_SMP15_2                         (0x4UL<<ADC_SMPR2_SMP15_Pos)                      /*!< 0x00020000 */
#define ADC_SMPR2_SMP16_Pos                       (18U)
#define ADC_SMPR2_SMP16_Msk                       (0x7UL<<ADC_SMPR2_SMP16_Pos)                      /*!< 0x001C0000 */
#define ADC_SMPR2_SMP16                           ADC_SMPR2_SMP16_Msk
#define ADC_SMPR2_SMP16_0                         (0x1UL<<ADC_SMPR2_SMP16_Pos)                      /*!< 0x00040000 */
#define ADC_SMPR2_SMP16_1                         (0x2UL<<ADC_SMPR2_SMP16_Pos)                      /*!< 0x00080000 */
#define ADC_SMPR2_SMP16_2                         (0x4UL<<ADC_SMPR2_SMP16_Pos)                      /*!< 0x00100000 */
#define ADC_SMPR2_SMP17_Pos                       (21U)
#define ADC_SMPR2_SMP17_Msk                       (0x7UL<<ADC_SMPR2_SMP17_Pos)                      /*!< 0x00E00000 */
#define ADC_SMPR2_SMP17                           ADC_SMPR2_SMP17_Msk
#define ADC_SMPR2_SMP17_0                         (0x1UL<<ADC_SMPR2_SMP17_Pos)                      /*!< 0x00200000 */
#define ADC_SMPR2_SMP17_1                         (0x2UL<<ADC_SMPR2_SMP17_Pos)                      /*!< 0x00400000 */
#define ADC_SMPR2_SMP17_2                         (0x4UL<<ADC_SMPR2_SMP17_Pos)                      /*!< 0x00800000 */
#define ADC_SMPR2_SMP18_Pos                       (24U)
#define ADC_SMPR2_SMP18_Msk                       (0x7UL<<ADC_SMPR2_SMP18_Pos)                      /*!< 0x07000000 */
#define ADC_SMPR2_SMP18                           ADC_SMPR2_SMP18_Msk
#define ADC_SMPR2_SMP18_0                         (0x1UL<<ADC_SMPR2_SMP18_Pos)                      /*!< 0x01000000 */
#define ADC_SMPR2_SMP18_1                         (0x2UL<<ADC_SMPR2_SMP18_Pos)                      /*!< 0x02000000 */
#define ADC_SMPR2_SMP18_2                         (0x4UL<<ADC_SMPR2_SMP18_Pos)                      /*!< 0x04000000 */
#define ADC_SMPR2_SMP19_Pos                       (27U)
#define ADC_SMPR2_SMP19_Msk                       (0x7UL<<ADC_SMPR2_SMP19_Pos)                      /*!< 0x38000000 */
#define ADC_SMPR2_SMP19                           ADC_SMPR2_SMP19_Msk
#define ADC_SMPR2_SMP19_0                         (0x1UL<<ADC_SMPR2_SMP19_Pos)                      /*!< 0x08000000 */
#define ADC_SMPR2_SMP19_1                         (0x2UL<<ADC_SMPR2_SMP19_Pos)                      /*!< 0x10000000 */
#define ADC_SMPR2_SMP19_2                         (0x4UL<<ADC_SMPR2_SMP19_Pos)                      /*!< 0x20000000 */

/********************************* Bit definition for ADC_SMPR3 register ********************************************/
#define ADC_SMPR3_SMP20_Pos                       (0U)
#define ADC_SMPR3_SMP20_Msk                       (0x7UL<<ADC_SMPR3_SMP20_Pos)                      /*!< 0x00000007 */
#define ADC_SMPR3_SMP20                           ADC_SMPR3_SMP20_Msk
#define ADC_SMPR3_SMP20_0                         (0x1UL<<ADC_SMPR3_SMP20_Pos)                      /*!< 0x00000001 */
#define ADC_SMPR3_SMP20_1                         (0x2UL<<ADC_SMPR3_SMP20_Pos)                      /*!< 0x00000002 */
#define ADC_SMPR3_SMP20_2                         (0x4UL<<ADC_SMPR3_SMP20_Pos)                      /*!< 0x00000004 */

/********************************* Bit definition for ADC_TR1 register **********************************************/
#define ADC_TR1_LT1_Pos                           (0U)
#define ADC_TR1_LT1_Msk                           (0xFFFUL<<ADC_TR1_LT1_Pos)                        /*!< 0x00000FFF */
#define ADC_TR1_LT1                               ADC_TR1_LT1_Msk
#define ADC_TR1_AWDFILT_Pos                       (12U)
#define ADC_TR1_AWDFILT_Msk                       (0x7UL<<ADC_TR1_AWDFILT_Pos)                      /*!< 0x00007000 */
#define ADC_TR1_AWDFILT                           ADC_TR1_AWDFILT_Msk
#define ADC_TR1_AWDFILT_0                         (0x1UL<<ADC_TR1_AWDFILT_Pos)                      /*!< 0x00001000 */
#define ADC_TR1_AWDFILT_1                         (0x2UL<<ADC_TR1_AWDFILT_Pos)                      /*!< 0x00002000 */
#define ADC_TR1_AWDFILT_2                         (0x4UL<<ADC_TR1_AWDFILT_Pos)                      /*!< 0x00004000 */
#define ADC_TR1_HT1_Pos                           (16U)
#define ADC_TR1_HT1_Msk                           (0xFFFUL<<ADC_TR1_HT1_Pos)                        /*!< 0x0FFF0000 */
#define ADC_TR1_HT1                               ADC_TR1_HT1_Msk

/********************************* Bit definition for ADC_TR2 register **********************************************/
#define ADC_TR2_LT2_Pos                           (0U)
#define ADC_TR2_LT2_Msk                           (0xFFUL<<ADC_TR2_LT2_Pos)                         /*!< 0x000000FF */
#define ADC_TR2_LT2                               ADC_TR2_LT2_Msk
#define ADC_TR2_HT2_Pos                           (16U)
#define ADC_TR2_HT2_Msk                           (0xFFUL<<ADC_TR2_HT2_Pos)                         /*!< 0x00FF0000 */
#define ADC_TR2_HT2                               ADC_TR2_HT2_Msk

/********************************* Bit definition for ADC_TR3 register **********************************************/
#define ADC_TR3_LT3_Pos                           (0U)
#define ADC_TR3_LT3_Msk                           (0xFFUL<<ADC_TR3_LT3_Pos)                         /*!< 0x000000FF */
#define ADC_TR3_LT3                               ADC_TR3_LT3_Msk
#define ADC_TR3_HT3_Pos                           (16U)
#define ADC_TR3_HT3_Msk                           (0xFFUL<<ADC_TR3_HT3_Pos)                         /*!< 0x00FF0000 */
#define ADC_TR3_HT3                               ADC_TR3_HT3_Msk

/********************************* Bit definition for ADC_SQR1 register *********************************************/
#define ADC_SQR1_L_Pos                            (0U)
#define ADC_SQR1_L_Msk                            (0xFUL<<ADC_SQR1_L_Pos)                           /*!< 0x0000000F */
#define ADC_SQR1_L                                ADC_SQR1_L_Msk
#define ADC_SQR1_L_0                              (0x1UL<<ADC_SQR1_L_Pos)                           /*!< 0x00000001 */
#define ADC_SQR1_L_1                              (0x2UL<<ADC_SQR1_L_Pos)                           /*!< 0x00000002 */
#define ADC_SQR1_L_2                              (0x4UL<<ADC_SQR1_L_Pos)                           /*!< 0x00000004 */
#define ADC_SQR1_L_3                              (0x8UL<<ADC_SQR1_L_Pos)                           /*!< 0x00000008 */
#define ADC_SQR1_SQ1_Pos                          (6U)
#define ADC_SQR1_SQ1_Msk                          (0x1FUL<<ADC_SQR1_SQ1_Pos)                        /*!< 0x000007C0 */
#define ADC_SQR1_SQ1                              ADC_SQR1_SQ1_Msk
#define ADC_SQR1_SQ1_0                            (0x1UL<<ADC_SQR1_SQ1_Pos)                         /*!< 0x00000040 */
#define ADC_SQR1_SQ1_1                            (0x2UL<<ADC_SQR1_SQ1_Pos)                         /*!< 0x00000080 */
#define ADC_SQR1_SQ1_2                            (0x4UL<<ADC_SQR1_SQ1_Pos)                         /*!< 0x00000100 */
#define ADC_SQR1_SQ1_3                            (0x8UL<<ADC_SQR1_SQ1_Pos)                         /*!< 0x00000200 */
#define ADC_SQR1_SQ1_4                            (0x10UL<<ADC_SQR1_SQ1_Pos)                        /*!< 0x00000400 */
#define ADC_SQR1_SQ2_Pos                          (12U)
#define ADC_SQR1_SQ2_Msk                          (0x1FUL<<ADC_SQR1_SQ2_Pos)                        /*!< 0x0001F000 */
#define ADC_SQR1_SQ2                              ADC_SQR1_SQ2_Msk
#define ADC_SQR1_SQ2_0                            (0x1UL<<ADC_SQR1_SQ2_Pos)                         /*!< 0x00001000 */
#define ADC_SQR1_SQ2_1                            (0x2UL<<ADC_SQR1_SQ2_Pos)                         /*!< 0x00002000 */
#define ADC_SQR1_SQ2_2                            (0x4UL<<ADC_SQR1_SQ2_Pos)                         /*!< 0x00004000 */
#define ADC_SQR1_SQ2_3                            (0x8UL<<ADC_SQR1_SQ2_Pos)                         /*!< 0x00008000 */
#define ADC_SQR1_SQ2_4                            (0x10UL<<ADC_SQR1_SQ2_Pos)                        /*!< 0x00010000 */
#define ADC_SQR1_SQ3_Pos                          (18U)
#define ADC_SQR1_SQ3_Msk                          (0x1FUL<<ADC_SQR1_SQ3_Pos)                        /*!< 0x007C0000 */
#define ADC_SQR1_SQ3                              ADC_SQR1_SQ3_Msk
#define ADC_SQR1_SQ3_0                            (0x1UL<<ADC_SQR1_SQ3_Pos)                         /*!< 0x00040000 */
#define ADC_SQR1_SQ3_1                            (0x2UL<<ADC_SQR1_SQ3_Pos)                         /*!< 0x00080000 */
#define ADC_SQR1_SQ3_2                            (0x4UL<<ADC_SQR1_SQ3_Pos)                         /*!< 0x00100000 */
#define ADC_SQR1_SQ3_3                            (0x8UL<<ADC_SQR1_SQ3_Pos)                         /*!< 0x00200000 */
#define ADC_SQR1_SQ3_4                            (0x10UL<<ADC_SQR1_SQ3_Pos)                        /*!< 0x00400000 */
#define ADC_SQR1_SQ4_Pos                          (24U)
#define ADC_SQR1_SQ4_Msk                          (0x1FUL<<ADC_SQR1_SQ4_Pos)                        /*!< 0x1F000000 */
#define ADC_SQR1_SQ4                              ADC_SQR1_SQ4_Msk
#define ADC_SQR1_SQ4_0                            (0x1UL<<ADC_SQR1_SQ4_Pos)                         /*!< 0x01000000 */
#define ADC_SQR1_SQ4_1                            (0x2UL<<ADC_SQR1_SQ4_Pos)                         /*!< 0x02000000 */
#define ADC_SQR1_SQ4_2                            (0x4UL<<ADC_SQR1_SQ4_Pos)                         /*!< 0x04000000 */
#define ADC_SQR1_SQ4_3                            (0x8UL<<ADC_SQR1_SQ4_Pos)                         /*!< 0x08000000 */
#define ADC_SQR1_SQ4_4                            (0x10UL<<ADC_SQR1_SQ4_Pos)                        /*!< 0x10000000 */

/********************************* Bit definition for ADC_SQR2 register *********************************************/
#define ADC_SQR2_SQ5_Pos                          (0U)
#define ADC_SQR2_SQ5_Msk                          (0x1FUL<<ADC_SQR2_SQ5_Pos)                        /*!< 0x0000001F */
#define ADC_SQR2_SQ5                              ADC_SQR2_SQ5_Msk
#define ADC_SQR2_SQ5_0                            (0x1UL<<ADC_SQR2_SQ5_Pos)                         /*!< 0x00000001 */
#define ADC_SQR2_SQ5_1                            (0x2UL<<ADC_SQR2_SQ5_Pos)                         /*!< 0x00000002 */
#define ADC_SQR2_SQ5_2                            (0x4UL<<ADC_SQR2_SQ5_Pos)                         /*!< 0x00000004 */
#define ADC_SQR2_SQ5_3                            (0x8UL<<ADC_SQR2_SQ5_Pos)                         /*!< 0x00000008 */
#define ADC_SQR2_SQ5_4                            (0x10UL<<ADC_SQR2_SQ5_Pos)                        /*!< 0x00000010 */
#define ADC_SQR2_SQ6_Pos                          (6U)
#define ADC_SQR2_SQ6_Msk                          (0x1FUL<<ADC_SQR2_SQ6_Pos)                        /*!< 0x000007C0 */
#define ADC_SQR2_SQ6                              ADC_SQR2_SQ6_Msk
#define ADC_SQR2_SQ6_0                            (0x1UL<<ADC_SQR2_SQ6_Pos)                         /*!< 0x00000040 */
#define ADC_SQR2_SQ6_1                            (0x2UL<<ADC_SQR2_SQ6_Pos)                         /*!< 0x00000080 */
#define ADC_SQR2_SQ6_2                            (0x4UL<<ADC_SQR2_SQ6_Pos)                         /*!< 0x00000100 */
#define ADC_SQR2_SQ6_3                            (0x8UL<<ADC_SQR2_SQ6_Pos)                         /*!< 0x00000200 */
#define ADC_SQR2_SQ6_4                            (0x10UL<<ADC_SQR2_SQ6_Pos)                        /*!< 0x00000400 */
#define ADC_SQR2_SQ7_Pos                          (12U)
#define ADC_SQR2_SQ7_Msk                          (0x1FUL<<ADC_SQR2_SQ7_Pos)                        /*!< 0x0001F000 */
#define ADC_SQR2_SQ7                              ADC_SQR2_SQ7_Msk
#define ADC_SQR2_SQ7_0                            (0x1UL<<ADC_SQR2_SQ7_Pos)                         /*!< 0x00001000 */
#define ADC_SQR2_SQ7_1                            (0x2UL<<ADC_SQR2_SQ7_Pos)                         /*!< 0x00002000 */
#define ADC_SQR2_SQ7_2                            (0x4UL<<ADC_SQR2_SQ7_Pos)                         /*!< 0x00004000 */
#define ADC_SQR2_SQ7_3                            (0x8UL<<ADC_SQR2_SQ7_Pos)                         /*!< 0x00008000 */
#define ADC_SQR2_SQ7_4                            (0x10UL<<ADC_SQR2_SQ7_Pos)                        /*!< 0x00010000 */
#define ADC_SQR2_SQ8_Pos                          (18U)
#define ADC_SQR2_SQ8_Msk                          (0x1FUL<<ADC_SQR2_SQ8_Pos)                        /*!< 0x007C0000 */
#define ADC_SQR2_SQ8                              ADC_SQR2_SQ8_Msk
#define ADC_SQR2_SQ8_0                            (0x1UL<<ADC_SQR2_SQ8_Pos)                         /*!< 0x00040000 */
#define ADC_SQR2_SQ8_1                            (0x2UL<<ADC_SQR2_SQ8_Pos)                         /*!< 0x00080000 */
#define ADC_SQR2_SQ8_2                            (0x4UL<<ADC_SQR2_SQ8_Pos)                         /*!< 0x00100000 */
#define ADC_SQR2_SQ8_3                            (0x8UL<<ADC_SQR2_SQ8_Pos)                         /*!< 0x00200000 */
#define ADC_SQR2_SQ8_4                            (0x10UL<<ADC_SQR2_SQ8_Pos)                        /*!< 0x00400000 */
#define ADC_SQR2_SQ9_Pos                          (24U)
#define ADC_SQR2_SQ9_Msk                          (0x1FUL<<ADC_SQR2_SQ9_Pos)                        /*!< 0x1F000000 */
#define ADC_SQR2_SQ9                              ADC_SQR2_SQ9_Msk
#define ADC_SQR2_SQ9_0                            (0x1UL<<ADC_SQR2_SQ9_Pos)                         /*!< 0x01000000 */
#define ADC_SQR2_SQ9_1                            (0x2UL<<ADC_SQR2_SQ9_Pos)                         /*!< 0x02000000 */
#define ADC_SQR2_SQ9_2                            (0x4UL<<ADC_SQR2_SQ9_Pos)                         /*!< 0x04000000 */
#define ADC_SQR2_SQ9_3                            (0x8UL<<ADC_SQR2_SQ9_Pos)                         /*!< 0x08000000 */
#define ADC_SQR2_SQ9_4                            (0x10UL<<ADC_SQR2_SQ9_Pos)                        /*!< 0x10000000 */

/********************************* Bit definition for ADC_SQR3 register *********************************************/
#define ADC_SQR3_SQ10_Pos                         (0U)
#define ADC_SQR3_SQ10_Msk                         (0x1FUL<<ADC_SQR3_SQ10_Pos)                       /*!< 0x0000001F */
#define ADC_SQR3_SQ10                             ADC_SQR3_SQ10_Msk
#define ADC_SQR3_SQ10_0                           (0x1UL<<ADC_SQR3_SQ10_Pos)                        /*!< 0x00000001 */
#define ADC_SQR3_SQ10_1                           (0x2UL<<ADC_SQR3_SQ10_Pos)                        /*!< 0x00000002 */
#define ADC_SQR3_SQ10_2                           (0x4UL<<ADC_SQR3_SQ10_Pos)                        /*!< 0x00000004 */
#define ADC_SQR3_SQ10_3                           (0x8UL<<ADC_SQR3_SQ10_Pos)                        /*!< 0x00000008 */
#define ADC_SQR3_SQ10_4                           (0x10UL<<ADC_SQR3_SQ10_Pos)                       /*!< 0x00000010 */
#define ADC_SQR3_SQ11_Pos                         (6U)
#define ADC_SQR3_SQ11_Msk                         (0x1FUL<<ADC_SQR3_SQ11_Pos)                       /*!< 0x000007C0 */
#define ADC_SQR3_SQ11                             ADC_SQR3_SQ11_Msk
#define ADC_SQR3_SQ11_0                           (0x1UL<<ADC_SQR3_SQ11_Pos)                        /*!< 0x00000040 */
#define ADC_SQR3_SQ11_1                           (0x2UL<<ADC_SQR3_SQ11_Pos)                        /*!< 0x00000080 */
#define ADC_SQR3_SQ11_2                           (0x4UL<<ADC_SQR3_SQ11_Pos)                        /*!< 0x00000100 */
#define ADC_SQR3_SQ11_3                           (0x8UL<<ADC_SQR3_SQ11_Pos)                        /*!< 0x00000200 */
#define ADC_SQR3_SQ11_4                           (0x10UL<<ADC_SQR3_SQ11_Pos)                       /*!< 0x00000400 */
#define ADC_SQR3_SQ12_Pos                         (12U)
#define ADC_SQR3_SQ12_Msk                         (0x1FUL<<ADC_SQR3_SQ12_Pos)                       /*!< 0x0001F000 */
#define ADC_SQR3_SQ12                             ADC_SQR3_SQ12_Msk
#define ADC_SQR3_SQ12_0                           (0x1UL<<ADC_SQR3_SQ12_Pos)                        /*!< 0x00001000 */
#define ADC_SQR3_SQ12_1                           (0x2UL<<ADC_SQR3_SQ12_Pos)                        /*!< 0x00002000 */
#define ADC_SQR3_SQ12_2                           (0x4UL<<ADC_SQR3_SQ12_Pos)                        /*!< 0x00004000 */
#define ADC_SQR3_SQ12_3                           (0x8UL<<ADC_SQR3_SQ12_Pos)                        /*!< 0x00008000 */
#define ADC_SQR3_SQ12_4                           (0x10UL<<ADC_SQR3_SQ12_Pos)                       /*!< 0x00010000 */
#define ADC_SQR3_SQ13_Pos                         (18U)
#define ADC_SQR3_SQ13_Msk                         (0x1FUL<<ADC_SQR3_SQ13_Pos)                       /*!< 0x007C0000 */
#define ADC_SQR3_SQ13                             ADC_SQR3_SQ13_Msk
#define ADC_SQR3_SQ13_0                           (0x1UL<<ADC_SQR3_SQ13_Pos)                        /*!< 0x00040000 */
#define ADC_SQR3_SQ13_1                           (0x2UL<<ADC_SQR3_SQ13_Pos)                        /*!< 0x00080000 */
#define ADC_SQR3_SQ13_2                           (0x4UL<<ADC_SQR3_SQ13_Pos)                        /*!< 0x00100000 */
#define ADC_SQR3_SQ13_3                           (0x8UL<<ADC_SQR3_SQ13_Pos)                        /*!< 0x00200000 */
#define ADC_SQR3_SQ13_4                           (0x10UL<<ADC_SQR3_SQ13_Pos)                       /*!< 0x00400000 */
#define ADC_SQR3_SQ14_Pos                         (24U)
#define ADC_SQR3_SQ14_Msk                         (0x1FUL<<ADC_SQR3_SQ14_Pos)                       /*!< 0x1F000000 */
#define ADC_SQR3_SQ14                             ADC_SQR3_SQ14_Msk
#define ADC_SQR3_SQ14_0                           (0x1UL<<ADC_SQR3_SQ14_Pos)                        /*!< 0x01000000 */
#define ADC_SQR3_SQ14_1                           (0x2UL<<ADC_SQR3_SQ14_Pos)                        /*!< 0x02000000 */
#define ADC_SQR3_SQ14_2                           (0x4UL<<ADC_SQR3_SQ14_Pos)                        /*!< 0x04000000 */
#define ADC_SQR3_SQ14_3                           (0x8UL<<ADC_SQR3_SQ14_Pos)                        /*!< 0x08000000 */
#define ADC_SQR3_SQ14_4                           (0x10UL<<ADC_SQR3_SQ14_Pos)                       /*!< 0x10000000 */

/********************************* Bit definition for ADC_SQR4 register *********************************************/
#define ADC_SQR4_SQ15_Pos                         (0U)
#define ADC_SQR4_SQ15_Msk                         (0x1FUL<<ADC_SQR4_SQ15_Pos)                       /*!< 0x0000001F */
#define ADC_SQR4_SQ15                             ADC_SQR4_SQ15_Msk
#define ADC_SQR4_SQ15_0                           (0x1UL<<ADC_SQR4_SQ15_Pos)                        /*!< 0x00000001 */
#define ADC_SQR4_SQ15_1                           (0x2UL<<ADC_SQR4_SQ15_Pos)                        /*!< 0x00000002 */
#define ADC_SQR4_SQ15_2                           (0x4UL<<ADC_SQR4_SQ15_Pos)                        /*!< 0x00000004 */
#define ADC_SQR4_SQ15_3                           (0x8UL<<ADC_SQR4_SQ15_Pos)                        /*!< 0x00000008 */
#define ADC_SQR4_SQ15_4                           (0x10UL<<ADC_SQR4_SQ15_Pos)                       /*!< 0x00000010 */
#define ADC_SQR4_SQ16_Pos                         (6U)
#define ADC_SQR4_SQ16_Msk                         (0x1FUL<<ADC_SQR4_SQ16_Pos)                       /*!< 0x000007C0 */
#define ADC_SQR4_SQ16                             ADC_SQR4_SQ16_Msk
#define ADC_SQR4_SQ16_0                           (0x1UL<<ADC_SQR4_SQ16_Pos)                        /*!< 0x00000040 */
#define ADC_SQR4_SQ16_1                           (0x2UL<<ADC_SQR4_SQ16_Pos)                        /*!< 0x00000080 */
#define ADC_SQR4_SQ16_2                           (0x4UL<<ADC_SQR4_SQ16_Pos)                        /*!< 0x00000100 */
#define ADC_SQR4_SQ16_3                           (0x8UL<<ADC_SQR4_SQ16_Pos)                        /*!< 0x00000200 */
#define ADC_SQR4_SQ16_4                           (0x10UL<<ADC_SQR4_SQ16_Pos)                       /*!< 0x00000400 */

/********************************* Bit definition for ADC_DR register ***********************************************/
#define ADC_DR_RDATA_Pos                          (0U)
#define ADC_DR_RDATA_Msk                          (0xFFFFUL<<ADC_DR_RDATA_Pos)                      /*!< 0x0000FFFF */
#define ADC_DR_RDATA                              ADC_DR_RDATA_Msk

/********************************* Bit definition for ADC_JSQR register *********************************************/
#define ADC_JSQR_JL_Pos                           (0U)
#define ADC_JSQR_JL_Msk                           (0x3UL<<ADC_JSQR_JL_Pos)                          /*!< 0x00000003 */
#define ADC_JSQR_JL                               ADC_JSQR_JL_Msk
#define ADC_JSQR_JL_0                             (0x1UL<<ADC_JSQR_JL_Pos)                          /*!< 0x00000001 */
#define ADC_JSQR_JL_1                             (0x2UL<<ADC_JSQR_JL_Pos)                          /*!< 0x00000002 */
#define ADC_JSQR_JEXTSEL_Pos                      (2U)
#define ADC_JSQR_JEXTSEL_Msk                      (0x1FUL<<ADC_JSQR_JEXTSEL_Pos)                    /*!< 0x0000007C */
#define ADC_JSQR_JEXTSEL                          ADC_JSQR_JEXTSEL_Msk
#define ADC_JSQR_JEXTSEL_0                        (0x1UL<<ADC_JSQR_JEXTSEL_Pos)                     /*!< 0x00000004 */
#define ADC_JSQR_JEXTSEL_1                        (0x2UL<<ADC_JSQR_JEXTSEL_Pos)                     /*!< 0x00000008 */
#define ADC_JSQR_JEXTSEL_2                        (0x4UL<<ADC_JSQR_JEXTSEL_Pos)                     /*!< 0x00000010 */
#define ADC_JSQR_JEXTSEL_3                        (0x8UL<<ADC_JSQR_JEXTSEL_Pos)                     /*!< 0x00000020 */
#define ADC_JSQR_JEXTSEL_4                        (0x10UL<<ADC_JSQR_JEXTSEL_Pos)                    /*!< 0x00000040 */
#define ADC_JSQR_JEXTEN_Pos                       (7U)
#define ADC_JSQR_JEXTEN_Msk                       (0x3UL<<ADC_JSQR_JEXTEN_Pos)                      /*!< 0x00000180 */
#define ADC_JSQR_JEXTEN                           ADC_JSQR_JEXTEN_Msk
#define ADC_JSQR_JEXTEN_0                         (0x1UL<<ADC_JSQR_JEXTEN_Pos)                      /*!< 0x00000080 */
#define ADC_JSQR_JEXTEN_1                         (0x2UL<<ADC_JSQR_JEXTEN_Pos)                      /*!< 0x00000100 */
#define ADC_JSQR_JSQ1_Pos                         (9U)
#define ADC_JSQR_JSQ1_Msk                         (0x1FUL<<ADC_JSQR_JSQ1_Pos)                       /*!< 0x00003E00 */
#define ADC_JSQR_JSQ1                             ADC_JSQR_JSQ1_Msk
#define ADC_JSQR_JSQ1_0                           (0x1UL<<ADC_JSQR_JSQ1_Pos)                        /*!< 0x00000200 */
#define ADC_JSQR_JSQ1_1                           (0x2UL<<ADC_JSQR_JSQ1_Pos)                        /*!< 0x00000400 */
#define ADC_JSQR_JSQ1_2                           (0x4UL<<ADC_JSQR_JSQ1_Pos)                        /*!< 0x00000800 */
#define ADC_JSQR_JSQ1_3                           (0x8UL<<ADC_JSQR_JSQ1_Pos)                        /*!< 0x00001000 */
#define ADC_JSQR_JSQ1_4                           (0x10UL<<ADC_JSQR_JSQ1_Pos)                       /*!< 0x00002000 */
#define ADC_JSQR_JSQ2_Pos                         (15U)
#define ADC_JSQR_JSQ2_Msk                         (0x1FUL<<ADC_JSQR_JSQ2_Pos)                       /*!< 0x000F8000 */
#define ADC_JSQR_JSQ2                             ADC_JSQR_JSQ2_Msk
#define ADC_JSQR_JSQ2_0                           (0x1UL<<ADC_JSQR_JSQ2_Pos)                        /*!< 0x00008000 */
#define ADC_JSQR_JSQ2_1                           (0x2UL<<ADC_JSQR_JSQ2_Pos)                        /*!< 0x00010000 */
#define ADC_JSQR_JSQ2_2                           (0x4UL<<ADC_JSQR_JSQ2_Pos)                        /*!< 0x00020000 */
#define ADC_JSQR_JSQ2_3                           (0x8UL<<ADC_JSQR_JSQ2_Pos)                        /*!< 0x00040000 */
#define ADC_JSQR_JSQ2_4                           (0x10UL<<ADC_JSQR_JSQ2_Pos)                       /*!< 0x00080000 */
#define ADC_JSQR_JSQ3_Pos                         (21U)
#define ADC_JSQR_JSQ3_Msk                         (0x1FUL<<ADC_JSQR_JSQ3_Pos)                       /*!< 0x03E00000 */
#define ADC_JSQR_JSQ3                             ADC_JSQR_JSQ3_Msk
#define ADC_JSQR_JSQ3_0                           (0x1UL<<ADC_JSQR_JSQ3_Pos)                        /*!< 0x00200000 */
#define ADC_JSQR_JSQ3_1                           (0x2UL<<ADC_JSQR_JSQ3_Pos)                        /*!< 0x00400000 */
#define ADC_JSQR_JSQ3_2                           (0x4UL<<ADC_JSQR_JSQ3_Pos)                        /*!< 0x00800000 */
#define ADC_JSQR_JSQ3_3                           (0x8UL<<ADC_JSQR_JSQ3_Pos)                        /*!< 0x01000000 */
#define ADC_JSQR_JSQ3_4                           (0x10UL<<ADC_JSQR_JSQ3_Pos)                       /*!< 0x02000000 */
#define ADC_JSQR_JSQ4_Pos                         (27U)
#define ADC_JSQR_JSQ4_Msk                         (0x1FUL<<ADC_JSQR_JSQ4_Pos)                       /*!< 0xF8000000 */
#define ADC_JSQR_JSQ4                             ADC_JSQR_JSQ4_Msk
#define ADC_JSQR_JSQ4_0                           (0x1UL<<ADC_JSQR_JSQ4_Pos)                        /*!< 0x08000000 */
#define ADC_JSQR_JSQ4_1                           (0x2UL<<ADC_JSQR_JSQ4_Pos)                        /*!< 0x10000000 */
#define ADC_JSQR_JSQ4_2                           (0x4UL<<ADC_JSQR_JSQ4_Pos)                        /*!< 0x20000000 */
#define ADC_JSQR_JSQ4_3                           (0x8UL<<ADC_JSQR_JSQ4_Pos)                        /*!< 0x40000000 */
#define ADC_JSQR_JSQ4_4                           (0x10UL<<ADC_JSQR_JSQ4_Pos)                       /*!< 0x80000000 */

/********************************* Bit definition for ADC_OFR1 register *********************************************/
#define ADC_OFR1_OFFSET1_Pos                      (0U)
#define ADC_OFR1_OFFSET1_Msk                      (0xFFFUL<<ADC_OFR1_OFFSET1_Pos)                   /*!< 0x00000FFF */
#define ADC_OFR1_OFFSET1                          ADC_OFR1_OFFSET1_Msk
#define ADC_OFR1_OFFSETPOS_Pos                    (24U)
#define ADC_OFR1_OFFSETPOS_Msk                    (0x1UL<<ADC_OFR1_OFFSETPOS_Pos)                   /*!< 0x01000000 */
#define ADC_OFR1_OFFSETPOS                        ADC_OFR1_OFFSETPOS_Msk                            
#define ADC_OFR1_SATEN_Pos                        (25U)
#define ADC_OFR1_SATEN_Msk                        (0x1UL<<ADC_OFR1_SATEN_Pos)                       /*!< 0x02000000 */
#define ADC_OFR1_SATEN                            ADC_OFR1_SATEN_Msk                                
#define ADC_OFR1_OFFSET1_CH_Pos                   (26U)
#define ADC_OFR1_OFFSET1_CH_Msk                   (0x1FUL<<ADC_OFR1_OFFSET1_CH_Pos)                 /*!< 0x7C000000 */
#define ADC_OFR1_OFFSET1_CH                       ADC_OFR1_OFFSET1_CH_Msk
#define ADC_OFR1_OFFSET1_CH_0                     (0x1UL<<ADC_OFR1_OFFSET1_CH_Pos)                  /*!< 0x04000000 */
#define ADC_OFR1_OFFSET1_CH_1                     (0x2UL<<ADC_OFR1_OFFSET1_CH_Pos)                  /*!< 0x08000000 */
#define ADC_OFR1_OFFSET1_CH_2                     (0x4UL<<ADC_OFR1_OFFSET1_CH_Pos)                  /*!< 0x10000000 */
#define ADC_OFR1_OFFSET1_CH_3                     (0x8UL<<ADC_OFR1_OFFSET1_CH_Pos)                  /*!< 0x20000000 */
#define ADC_OFR1_OFFSET1_CH_4                     (0x10UL<<ADC_OFR1_OFFSET1_CH_Pos)                 /*!< 0x40000000 */
#define ADC_OFR1_OFFSET1_EN_Pos                   (31U)
#define ADC_OFR1_OFFSET1_EN_Msk                   (0x1UL<<ADC_OFR1_OFFSET1_EN_Pos)                  /*!< 0x80000000 */
#define ADC_OFR1_OFFSET1_EN                       ADC_OFR1_OFFSET1_EN_Msk                           

/********************************* Bit definition for ADC_OFR2 register *********************************************/
#define ADC_OFR2_OFFSET2_Pos                      (0U)
#define ADC_OFR2_OFFSET2_Msk                      (0xFFFUL<<ADC_OFR2_OFFSET2_Pos)                   /*!< 0x00000FFF */
#define ADC_OFR2_OFFSET2                          ADC_OFR2_OFFSET2_Msk
#define ADC_OFR2_OFFSET2_CH_Pos                   (26U)
#define ADC_OFR2_OFFSET2_CH_Msk                   (0x1FUL<<ADC_OFR2_OFFSET2_CH_Pos)                 /*!< 0x7C000000 */
#define ADC_OFR2_OFFSET2_CH                       ADC_OFR2_OFFSET2_CH_Msk
#define ADC_OFR2_OFFSET2_CH_0                     (0x1UL<<ADC_OFR2_OFFSET2_CH_Pos)                  /*!< 0x04000000 */
#define ADC_OFR2_OFFSET2_CH_1                     (0x2UL<<ADC_OFR2_OFFSET2_CH_Pos)                  /*!< 0x08000000 */
#define ADC_OFR2_OFFSET2_CH_2                     (0x4UL<<ADC_OFR2_OFFSET2_CH_Pos)                  /*!< 0x10000000 */
#define ADC_OFR2_OFFSET2_CH_3                     (0x8UL<<ADC_OFR2_OFFSET2_CH_Pos)                  /*!< 0x20000000 */
#define ADC_OFR2_OFFSET2_CH_4                     (0x10UL<<ADC_OFR2_OFFSET2_CH_Pos)                 /*!< 0x40000000 */
#define ADC_OFR2_OFFSET2_EN_Pos                   (31U)
#define ADC_OFR2_OFFSET2_EN_Msk                   (0x1UL<<ADC_OFR2_OFFSET2_EN_Pos)                  /*!< 0x80000000 */
#define ADC_OFR2_OFFSET2_EN                       ADC_OFR2_OFFSET2_EN_Msk                           

/********************************* Bit definition for ADC_OFR3 register *********************************************/
#define ADC_OFR3_OFFSET3_Pos                      (0U)
#define ADC_OFR3_OFFSET3_Msk                      (0xFFFUL<<ADC_OFR3_OFFSET3_Pos)                   /*!< 0x00000FFF */
#define ADC_OFR3_OFFSET3                          ADC_OFR3_OFFSET3_Msk
#define ADC_OFR3_OFFSET3_CH_Pos                   (26U)
#define ADC_OFR3_OFFSET3_CH_Msk                   (0x1FUL<<ADC_OFR3_OFFSET3_CH_Pos)                 /*!< 0x7C000000 */
#define ADC_OFR3_OFFSET3_CH                       ADC_OFR3_OFFSET3_CH_Msk
#define ADC_OFR3_OFFSET3_CH_0                     (0x1UL<<ADC_OFR3_OFFSET3_CH_Pos)                  /*!< 0x04000000 */
#define ADC_OFR3_OFFSET3_CH_1                     (0x2UL<<ADC_OFR3_OFFSET3_CH_Pos)                  /*!< 0x08000000 */
#define ADC_OFR3_OFFSET3_CH_2                     (0x4UL<<ADC_OFR3_OFFSET3_CH_Pos)                  /*!< 0x10000000 */
#define ADC_OFR3_OFFSET3_CH_3                     (0x8UL<<ADC_OFR3_OFFSET3_CH_Pos)                  /*!< 0x20000000 */
#define ADC_OFR3_OFFSET3_CH_4                     (0x10UL<<ADC_OFR3_OFFSET3_CH_Pos)                 /*!< 0x40000000 */
#define ADC_OFR3_OFFSET3_EN_Pos                   (31U)
#define ADC_OFR3_OFFSET3_EN_Msk                   (0x1UL<<ADC_OFR3_OFFSET3_EN_Pos)                  /*!< 0x80000000 */
#define ADC_OFR3_OFFSET3_EN                       ADC_OFR3_OFFSET3_EN_Msk                           

/********************************* Bit definition for ADC_OFR4 register *********************************************/
#define ADC_OFR4_OFFSET4_Pos                      (0U)
#define ADC_OFR4_OFFSET4_Msk                      (0xFFFUL<<ADC_OFR4_OFFSET4_Pos)                   /*!< 0x00000FFF */
#define ADC_OFR4_OFFSET4                          ADC_OFR4_OFFSET4_Msk
#define ADC_OFR4_OFFSET4_CH_Pos                   (26U)
#define ADC_OFR4_OFFSET4_CH_Msk                   (0x1FUL<<ADC_OFR4_OFFSET4_CH_Pos)                 /*!< 0x7C000000 */
#define ADC_OFR4_OFFSET4_CH                       ADC_OFR4_OFFSET4_CH_Msk
#define ADC_OFR4_OFFSET4_CH_0                     (0x1UL<<ADC_OFR4_OFFSET4_CH_Pos)                  /*!< 0x04000000 */
#define ADC_OFR4_OFFSET4_CH_1                     (0x2UL<<ADC_OFR4_OFFSET4_CH_Pos)                  /*!< 0x08000000 */
#define ADC_OFR4_OFFSET4_CH_2                     (0x4UL<<ADC_OFR4_OFFSET4_CH_Pos)                  /*!< 0x10000000 */
#define ADC_OFR4_OFFSET4_CH_3                     (0x8UL<<ADC_OFR4_OFFSET4_CH_Pos)                  /*!< 0x20000000 */
#define ADC_OFR4_OFFSET4_CH_4                     (0x10UL<<ADC_OFR4_OFFSET4_CH_Pos)                 /*!< 0x40000000 */
#define ADC_OFR4_OFFSET4_EN_Pos                   (31U)
#define ADC_OFR4_OFFSET4_EN_Msk                   (0x1UL<<ADC_OFR4_OFFSET4_EN_Pos)                  /*!< 0x80000000 */
#define ADC_OFR4_OFFSET4_EN                       ADC_OFR4_OFFSET4_EN_Msk                           

/********************************* Bit definition for ADC_JDR1 register *********************************************/
#define ADC_JDR1_JDATA_Pos                        (0U)
#define ADC_JDR1_JDATA_Msk                        (0xFFFFUL<<ADC_JDR1_JDATA_Pos)                    /*!< 0x0000FFFF */
#define ADC_JDR1_JDATA                            ADC_JDR1_JDATA_Msk

/********************************* Bit definition for ADC_JDR2 register *********************************************/
#define ADC_JDR2_JDATA_Pos                        (0U)
#define ADC_JDR2_JDATA_Msk                        (0xFFFFUL<<ADC_JDR2_JDATA_Pos)                    /*!< 0x0000FFFF */
#define ADC_JDR2_JDATA                            ADC_JDR2_JDATA_Msk

/********************************* Bit definition for ADC_JDR3 register *********************************************/
#define ADC_JDR3_JDATA_Pos                        (0U)
#define ADC_JDR3_JDATA_Msk                        (0xFFFFUL<<ADC_JDR3_JDATA_Pos)                    /*!< 0x0000FFFF */
#define ADC_JDR3_JDATA                            ADC_JDR3_JDATA_Msk

/********************************* Bit definition for ADC_JDR4 register *********************************************/
#define ADC_JDR4_JDATA_Pos                        (0U)
#define ADC_JDR4_JDATA_Msk                        (0xFFFFUL<<ADC_JDR4_JDATA_Pos)                    /*!< 0x0000FFFF */
#define ADC_JDR4_JDATA                            ADC_JDR4_JDATA_Msk

/********************************* Bit definition for ADC_AWD2CR register *******************************************/
#define ADC_AWD2CR_AWD2CH_Pos                     (0U)
#define ADC_AWD2CR_AWD2CH_Msk                     (0x1FFFFFUL<<ADC_AWD2CR_AWD2CH_Pos)               /*!< 0x001FFFFF */
#define ADC_AWD2CR_AWD2CH                         ADC_AWD2CR_AWD2CH_Msk
#define ADC_AWD2CR_AWD2CH_0            (0x00001UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00000001 */
#define ADC_AWD2CR_AWD2CH_1            (0x00002UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00000002 */
#define ADC_AWD2CR_AWD2CH_2            (0x00004UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00000004 */
#define ADC_AWD2CR_AWD2CH_3            (0x00008UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00000008 */
#define ADC_AWD2CR_AWD2CH_4            (0x00010UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00000010 */
#define ADC_AWD2CR_AWD2CH_5            (0x00020UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00000020 */
#define ADC_AWD2CR_AWD2CH_6            (0x00040UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00000040 */
#define ADC_AWD2CR_AWD2CH_7            (0x00080UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00000080 */
#define ADC_AWD2CR_AWD2CH_8            (0x00100UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00000100 */
#define ADC_AWD2CR_AWD2CH_9            (0x00200UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00000200 */
#define ADC_AWD2CR_AWD2CH_10           (0x00400UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00000400 */
#define ADC_AWD2CR_AWD2CH_11           (0x00800UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00000800 */
#define ADC_AWD2CR_AWD2CH_12           (0x01000UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00001000 */
#define ADC_AWD2CR_AWD2CH_13           (0x02000UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00002000 */
#define ADC_AWD2CR_AWD2CH_14           (0x04000UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00004000 */
#define ADC_AWD2CR_AWD2CH_15           (0x08000UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00008000 */
#define ADC_AWD2CR_AWD2CH_16           (0x10000UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00010000 */
#define ADC_AWD2CR_AWD2CH_17           (0x20000UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00020000 */
#define ADC_AWD2CR_AWD2CH_18           (0x40000UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00040000 */
#define ADC_AWD2CR_AWD2CH_19           (0x80000UL << ADC_AWD2CR_AWD2CH_Pos)    /*!< 0x00080000 */
#define ADC_AWD2CR_AWD2CH_20           (0x100000UL << ADC_AWD2CR_AWD2CH_Pos)   /*!< 0x00100000 */


/********************************* Bit definition for ADC_AWD3CR register *******************************************/
#define ADC_AWD3CR_AWD3CH_Pos          (0U)
#define ADC_AWD3CR_AWD3CH_Msk          (0x1FFFFFUL<<ADC_AWD3CR_AWD3CH_Pos)     /*!< 0x001FFFFF */
#define ADC_AWD3CR_AWD3CH              ADC_AWD3CR_AWD3CH_Msk
#define ADC_AWD3CR_AWD3CH_0            (0x00001UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00000001 */
#define ADC_AWD3CR_AWD3CH_1            (0x00002UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00000002 */
#define ADC_AWD3CR_AWD3CH_2            (0x00004UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00000004 */
#define ADC_AWD3CR_AWD3CH_3            (0x00008UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00000008 */
#define ADC_AWD3CR_AWD3CH_4            (0x00010UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00000010 */
#define ADC_AWD3CR_AWD3CH_5            (0x00020UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00000020 */
#define ADC_AWD3CR_AWD3CH_6            (0x00040UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00000040 */
#define ADC_AWD3CR_AWD3CH_7            (0x00080UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00000080 */
#define ADC_AWD3CR_AWD3CH_8            (0x00100UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00000100 */
#define ADC_AWD3CR_AWD3CH_9            (0x00200UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00000200 */
#define ADC_AWD3CR_AWD3CH_10           (0x00400UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00000400 */
#define ADC_AWD3CR_AWD3CH_11           (0x00800UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00000800 */
#define ADC_AWD3CR_AWD3CH_12           (0x01000UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00001000 */
#define ADC_AWD3CR_AWD3CH_13           (0x02000UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00002000 */
#define ADC_AWD3CR_AWD3CH_14           (0x04000UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00004000 */
#define ADC_AWD3CR_AWD3CH_15           (0x08000UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00008000 */
#define ADC_AWD3CR_AWD3CH_16           (0x10000UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00010000 */
#define ADC_AWD3CR_AWD3CH_17           (0x20000UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00020000 */
#define ADC_AWD3CR_AWD3CH_18           (0x40000UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00040000 */
#define ADC_AWD3CR_AWD3CH_19           (0x40000UL << ADC_AWD3CR_AWD3CH_Pos)    /*!< 0x00080000 */
#define ADC_AWD3CR_AWD3CH_20           (0x100000UL << ADC_AWD3CR_AWD3CH_Pos)   /*!< 0x00100000 */

/********************************* Bit definition for ADC_CALFACT register ******************************************/
#define ADC_CALFACT_OFFSUC_Pos                    (20U)
#define ADC_CALFACT_OFFSUC_Msk                    (0x1UL<<ADC_CALFACT_OFFSUC_Pos)                   /*!< 0x00100000 */
#define ADC_CALFACT_OFFSUC                        ADC_CALFACT_OFFSUC_Msk                            
#define ADC_CALFACT_CAPSUC_Pos                    (21U)
#define ADC_CALFACT_CAPSUC_Msk                    (0x1UL<<ADC_CALFACT_CAPSUC_Pos)                   /*!< 0x00200000 */
#define ADC_CALFACT_CAPSUC                        ADC_CALFACT_CAPSUC_Msk                            
#define ADC_CALFACT_CALON_Pos                     (22U)
#define ADC_CALFACT_CALON_Msk                     (0x1UL<<ADC_CALFACT_CALON_Pos)                    /*!< 0x00400000 */
#define ADC_CALFACT_CALON                         ADC_CALFACT_CALON_Msk                             

/********************************* Bit definition for ADC_GCOMP register ********************************************/
#define ADC_GCOMP_GCOMPCOEFF_Pos                  (0U)
#define ADC_GCOMP_GCOMPCOEFF_Msk                  (0x3FFFUL<<ADC_GCOMP_GCOMPCOEFF_Pos)              /*!< 0x00003FFF */
#define ADC_GCOMP_GCOMPCOEFF                      ADC_GCOMP_GCOMPCOEFF_Msk

/********************************* Bit definition for ADC_CCR register *********************************************/
#define ADC_CCR_VREFBUFEN_Pos                    (5U)
#define ADC_CCR_VREFBUFEN_Msk                    (0x1UL<<ADC_CCR_VREFBUFEN_Pos)                   /*!< 0x00000020 */
#define ADC_CCR_VREFBUFEN                        ADC_CCR_VREFBUFEN_Msk                            
#define ADC_CCR_VREFBUFSEL_Pos                   (6U)
#define ADC_CCR_VREFBUFSEL_Msk                   (0x7UL<<ADC_CCR_VREFBUFSEL_Pos)                  /*!< 0x000001C0 */
#define ADC_CCR_VREFBUFSEL                       ADC_CCR_VREFBUFSEL_Msk
#define ADC_CCR_VREFBUFSEL_0                     (0x1UL<<ADC_CCR_VREFBUFSEL_Pos)                  /*!< 0x00000040 */
#define ADC_CCR_VREFBUFSEL_1                     (0x2UL<<ADC_CCR_VREFBUFSEL_Pos)                  /*!< 0x00000080 */
#define ADC_CCR_VREFBUFSEL_2                     (0x4UL<<ADC_CCR_VREFBUFSEL_Pos)                  /*!< 0x00000100 */
#define ADC_CCR_CKMODE_Pos                       (16U)
#define ADC_CCR_CKMODE_Msk                       (0x3UL<<ADC_CCR_CKMODE_Pos)                      /*!< 0x00030000 */
#define ADC_CCR_CKMODE                           ADC_CCR_CKMODE_Msk
#define ADC_CCR_CKMODE_0                         (0x1UL<<ADC_CCR_CKMODE_Pos)                      /*!< 0x00010000 */
#define ADC_CCR_CKMODE_1                         (0x2UL<<ADC_CCR_CKMODE_Pos)                      /*!< 0x00020000 */
#define ADC_CCR_PRESC_Pos                        (18U)
#define ADC_CCR_PRESC_Msk                        (0xFUL<<ADC_CCR_PRESC_Pos)                       /*!< 0x003C0000 */
#define ADC_CCR_PRESC                            ADC_CCR_PRESC_Msk
#define ADC_CCR_PRESC_0                          (0x1UL<<ADC_CCR_PRESC_Pos)                       /*!< 0x00040000 */
#define ADC_CCR_PRESC_1                          (0x2UL<<ADC_CCR_PRESC_Pos)                       /*!< 0x00080000 */
#define ADC_CCR_PRESC_2                          (0x4UL<<ADC_CCR_PRESC_Pos)                       /*!< 0x00100000 */
#define ADC_CCR_PRESC_3                          (0x8UL<<ADC_CCR_PRESC_Pos)                       /*!< 0x00200000 */
#define ADC_CCR_VREFEN_Pos                       (22U)
#define ADC_CCR_VREFEN_Msk                       (0x1UL<<ADC_CCR_VREFEN_Pos)                      /*!< 0x00400000 */
#define ADC_CCR_VREFEN                           ADC_CCR_VREFEN_Msk                               
#define ADC_CCR_VSENSESEL_Pos                    (23U)
#define ADC_CCR_VSENSESEL_Msk                    (0x1UL<<ADC_CCR_VSENSESEL_Pos)                   /*!< 0x00800000 */
#define ADC_CCR_VSENSESEL                        ADC_CCR_VSENSESEL_Msk                            
#define ADC_CCR_PWRMODE_Pos                      (25U)
#define ADC_CCR_PWRMODE_Msk                      (0x7UL<<ADC_CCR_PWRMODE_Pos)                     /*!< 0x0E000000 */
#define ADC_CCR_PWRMODE                          ADC_CCR_PWRMODE_Msk
#define ADC_CCR_PWRMODE_0                        (0x1UL<<ADC_CCR_PWRMODE_Pos)                     /*!< 0x02000000 */
#define ADC_CCR_PWRMODE_1                        (0x2UL<<ADC_CCR_PWRMODE_Pos)                     /*!< 0x04000000 */
#define ADC_CCR_PWRMODE_2                        (0x4UL<<ADC_CCR_PWRMODE_Pos)                     /*!< 0x08000000 */
#define ADC_CCR_VREFSEL_Pos                      (28U)
#define ADC_CCR_VREFSEL_Msk                      (0x1UL<<ADC_CCR_VREFSEL_Pos)                     /*!< 0x10000000 */
#define ADC_CCR_VREFSEL                          ADC_CCR_VREFSEL_Msk                              
#define ADC_CCR_DIFF_EN_Pos                      (29U)
#define ADC_CCR_DIFF_EN_Msk                      (0x1UL<<ADC_CCR_DIFF_EN_Pos)                     /*!< 0x20000000 */
#define ADC_CCR_DIFF_EN                          ADC_CCR_DIFF_EN_Msk                              

/****************************************************************************/
/*                                                                          */
/*                      Analog Comparators (COMP)                           */
/*                                                                          */
/****************************************************************************/
/**********************  Bit definition for COMP_CSR register  **************/
#define COMP_CSR_EN_Pos            (0U)
#define COMP_CSR_EN_Msk            (0x1UL << COMP_CSR_EN_Pos)                  /*!< 0x00000001 */
#define COMP_CSR_EN                COMP_CSR_EN_Msk                             /*!< Comparator enable */
#define COMP_CSR_COMP1_EN          COMP_CSR_EN
#define COMP_CSR_COMP2_EN          COMP_CSR_EN

#define COMP_CSR_INNSEL_Pos        (3U)
#define COMP_CSR_INNSEL_Msk        (0x3UL << COMP_CSR_INNSEL_Pos)              /*!< 0x00000038 */
#define COMP_CSR_INNSEL            COMP_CSR_INNSEL_Msk                         /*!< desc INNSEL */
#define COMP_CSR_INNSEL_0          (0x1UL << COMP_CSR_INNSEL_Pos)              /*!< 0x00000004 */
#define COMP_CSR_INNSEL_1          (0x2UL << COMP_CSR_INNSEL_Pos)              /*!< 0x00000008 */

#define COMP_CSR_INPSEL_Pos        (9U)
#define COMP_CSR_INPSEL_Msk        (0x1UL << COMP_CSR_INPSEL_Pos)              /*!< 0x00000200 */
#define COMP_CSR_INPSEL            COMP_CSR_INPSEL_Msk                         /*!< Comparator plus minus selection */

#define COMP_CSR_WINMODE_Pos       (11U)
#define COMP_CSR_WINMODE_Msk       (0x1UL << COMP_CSR_WINMODE_Pos)             /*!< 0x00000800 */
#define COMP_CSR_WINMODE           COMP_CSR_WINMODE_Msk                        /*!< Pair of comparators window mode. Bit intended to be used with COMP common instance (COMP_Common_TypeDef) */

#define COMP_CSR_BLANKSEL_Pos      (12U)
#define COMP_CSR_BLANKSEL_Msk      (0x7UL << COMP_CSR_BLANKSEL_Pos)           /*!< 0x00000800 */
#define COMP_CSR_BLANKSEL          COMP_CSR_BLANKSEL_Msk                      /*!< Pair of comparators window mode. Bit intended to be used with COMP common instance (COMP_Common_TypeDef) */
#define COMP_CSR_BLANKSEL_0        (0x1UL << COMP_CSR_BLANKSEL_Pos)             /*!< 0x00040000 */
#define COMP_CSR_BLANKSEL_1        (0x2UL << COMP_CSR_BLANKSEL_Pos)             /*!< 0x00080000 */ 
#define COMP_CSR_BLANKSEL_2        (0x4UL << COMP_CSR_BLANKSEL_Pos)             /*!< 0x00080000 */ 

#define COMP_CSR_POLARITY_Pos      (15U)
#define COMP_CSR_POLARITY_Msk      (0x1UL << COMP_CSR_POLARITY_Pos)            /*!< 0x00008000 */
#define COMP_CSR_POLARITY          COMP_CSR_POLARITY_Msk                       /*!< Comparator output polarity */

#define COMP_CSR_HYST_Pos          (16U)
#define COMP_CSR_HYST_Msk          (0x1UL << COMP_CSR_HYST_Pos)                /*!< 0x00010000 */
#define COMP_CSR_HYST              COMP_CSR_HYST_Msk                           /*!< Comparator hysteresis enable */
/*DEFINE FOR COMP1 CSR_HYST*/
#define COMP1_CSR_HYST_Pos         (16U)
#define COMP1_CSR_HYST_Msk         (0x1UL << COMP1_CSR_HYST_Pos)                /*!< 0x00010000 */
#define COMP1_CSR_HYST             COMP1_CSR_HYST_Msk                           /*!< Comparator1 hysteresis enable */
/*DEFINE FOR COMP2 CSR_HYST*/
#define COMP2_CSR_HYST_Pos         (1U)
#define COMP2_CSR_HYST_Msk         (0x1UL << COMP2_CSR_HYST_Pos)                /*!< 0x00000002 */
#define COMP2_CSR_HYST             COMP2_CSR_HYST_Msk                           /*!< Comparator2 hysteresis enable */

#define COMP_CSR_VCDIV_EN_Pos      (17U)
#define COMP_CSR_VCDIV_EN_Msk      (0x1UL << COMP_CSR_VCDIV_EN_Pos)            /*!< 0x00020000 */
#define COMP_CSR_VCDIV_EN          COMP_CSR_VCDIV_EN_Msk                       /*!< desc VCDIV_EN */

#define COMP_CSR_PWRMODE_Pos       (18U)
#define COMP_CSR_PWRMODE_Msk       (0x3UL << COMP_CSR_PWRMODE_Pos)             /*!< 0x000C0000 */
#define COMP_CSR_PWRMODE           COMP_CSR_PWRMODE_Msk                        /*!< Comparator power mode */
#define COMP_CSR_PWRMODE_0         (0x1UL << COMP_CSR_PWRMODE_Pos)             /*!< 0x00040000 */
#define COMP_CSR_PWRMODE_1         (0x2UL << COMP_CSR_PWRMODE_Pos)             /*!< 0x00080000 */

#define COMP_CSR_VCDIV_Pos         (20U)
#define COMP_CSR_VCDIV_Msk         (0xFFUL << COMP_CSR_VCDIV_Pos)              /*!< 0x0FF00000 */
#define COMP_CSR_VCDIV             COMP_CSR_VCDIV_Msk                          /*!< VCDIV[27:20] bits (desc VCDIV) */
#define COMP_CSR_VCDIV_0           (0x1UL << COMP_CSR_VCDIV_Pos)               /*!< 0x00100000 */
#define COMP_CSR_VCDIV_1           (0x2UL << COMP_CSR_VCDIV_Pos)               /*!< 0x00200000 */
#define COMP_CSR_VCDIV_2           (0x4UL << COMP_CSR_VCDIV_Pos)               /*!< 0x00400000 */
#define COMP_CSR_VCDIV_3           (0x8UL << COMP_CSR_VCDIV_Pos)               /*!< 0x00800000 */
#define COMP_CSR_VCDIV_4           (0x10UL << COMP_CSR_VCDIV_Pos)              /*!< 0x01000000 */
#define COMP_CSR_VCDIV_5           (0x20UL << COMP_CSR_VCDIV_Pos)              /*!< 0x02000000 */
#define COMP_CSR_VCDIV_6           (0x40UL << COMP_CSR_VCDIV_Pos)              /*!< 0x04000000 */
#define COMP_CSR_VCDIV_7           (0x80UL << COMP_CSR_VCDIV_Pos)              /*!< 0x08000000 */

#define COMP_CSR_VCSEL_Pos         (28U)
#define COMP_CSR_VCSEL_Msk         (0x1UL << COMP_CSR_VCSEL_Pos)               /*!< 0x10000000 */
#define COMP_CSR_VCSEL             COMP_CSR_VCSEL_Msk                          /*!< desc VCSEL */

#define COMP_CSR_TIM_EXTI_OUT_SEL_Pos         (29U)
#define COMP_CSR_TIM_EXTI_OUT_SEL_Msk         (0x1UL << COMP_CSR_TIM_EXTI_OUT_SEL_Pos)               /*!< 0x02000000 */
#define COMP_CSR_TIM_EXTI_OUT_SEL             COMP_CSR_TIM_EXTI_OUT_SEL_Msk                          /*!< COMP output to TIM/EXTI selection */

#define COMP_CSR_COMP_OUT_Pos      (30U)
#define COMP_CSR_COMP_OUT_Msk      (0x1UL << COMP_CSR_COMP_OUT_Pos)            /*!< 0x40000000 */
#define COMP_CSR_COMP_OUT          COMP_CSR_COMP_OUT_Msk                       /*!< COMP output status */

#define COMP_CSR_LOCK_Pos          (31U)
#define COMP_CSR_LOCK_Msk          (0x1UL << COMP_CSR_LOCK_Pos)                /*!< 0x80000000 */
#define COMP_CSR_LOCK              COMP_CSR_LOCK_Msk                           /*!< desc COMP_OUT */

/**********************  Bit definition for COMP_FR register  ***************/
#define COMP_FR_FLTEN_Pos          (0U)
#define COMP_FR_FLTEN_Msk          (0x1UL << COMP_FR_FLTEN_Pos)                /*!< 0x00000001 */
#define COMP_FR_FLTEN              COMP_FR_FLTEN_Msk                           /*!< Comparator filter enable */
#define COMP_FR_FLTCNT_Pos         (16U)
#define COMP_FR_FLTCNT_Msk         (0xFFFFUL << COMP_FR_FLTCNT_Pos)            /*!< 0xFFFF0000 */
#define COMP_FR_FLTCNT             COMP_FR_FLTCNT_Msk                          /*!< Comparator filter counter */

/********************************************************************************************************************/
/********************************* CRC ******************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for CRC_DR register ***********************************************/
#define CRC_DR_DR_Pos                             (0U)
#define CRC_DR_DR_Msk                             (0xFFFFFFFFUL<<CRC_DR_DR_Pos)                     /*!< 0xFFFFFFFF */
#define CRC_DR_DR                                 CRC_DR_DR_Msk                                     /*!< CRC data */

/********************************* Bit definition for CRC_IDR register **********************************************/
#define CRC_IDR_IDR_Pos                           (0U)
#define CRC_IDR_IDR_Msk                           (0xFFUL<<CRC_IDR_IDR_Pos)                         /*!< 0xFF */
#define CRC_IDR_IDR                               CRC_IDR_IDR_Msk                                   /*!< CRC independent data */

/********************************* Bit definition for CRC_CR register ***********************************************/
#define CRC_CR_RESET_Pos                          (0U)
#define CRC_CR_RESET_Msk                          (0x1UL<<CRC_CR_RESET_Pos)                         /*!< 0x00000001 */
#define CRC_CR_RESET                              CRC_CR_RESET_Msk                                  /*!< CRC software reset */

/********************************************************************************************************************/
/********************************* DBG ******************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for DBGMCU_IDCODE register ****************************************/
#define DBGMCU_IDCODE_REV_ID_Pos                   (0U)
#define DBGMCU_IDCODE_REV_ID_Msk                   (0xFFFFFFFFUL << DBGMCU_IDCODE_REV_ID_Pos)          /*!< 0xFFFFFFFF */
#define DBGMCU_IDCODE_REV_ID                       DBGMCU_IDCODE_REV_ID_Msk                            /*!< REV_ID[31:0] bits (desc REV_ID) */

/********************************* Bit definition for DBGMCU_CR1 register *******************************************/
#define DBGMCU_CR1_DBG_SLEEP_Pos                   (0U)
#define DBGMCU_CR1_DBG_SLEEP_Msk                   (0x1UL << DBGMCU_CR1_DBG_SLEEP_Pos)                /*!< 0x00000001 */
#define DBGMCU_CR1_DBG_SLEEP                       DBGMCU_CR1_DBG_SLEEP_Msk                           /*!< desc DBG_SLEEP */
#define DBGMCU_CR1_DBG_STOP_Pos                    (1U)
#define DBGMCU_CR1_DBG_STOP_Msk                    (0x1UL << DBGMCU_CR1_DBG_STOP_Pos)                 /*!< 0x00000002 */
#define DBGMCU_CR1_DBG_STOP                        DBGMCU_CR1_DBG_STOP_Msk                            /*!< desc DBG_STOP */
#define DBGMCU_CR1_DBG_STDBY_Pos                   (2U)
#define DBGMCU_CR1_DBG_STDBY_Msk                   (0x1UL << DBGMCU_CR1_DBG_STDBY_Pos)                /*!< 0x00000004 */
#define DBGMCU_CR1_DBG_STDBY                       DBGMCU_CR1_DBG_STDBY_Msk                           /*!< desc DBG_STDBY */
#define DBGMCU_CR1_DBG_IWDG_STOP_Pos               (8U)
#define DBGMCU_CR1_DBG_IWDG_STOP_Msk               (0x1UL << DBGMCU_CR1_DBG_IWDG_STOP_Pos)            /*!< 0x00000100 */
#define DBGMCU_CR1_DBG_IWDG_STOP                   DBGMCU_CR1_DBG_IWDG_STOP_Msk                       /*!< desc DBG_IWDG_STOP */
#define DBGMCU_CR1_DBG_WWDG_STOP_Pos               (9U)
#define DBGMCU_CR1_DBG_WWDG_STOP_Msk               (0x1UL << DBGMCU_CR1_DBG_WWDG_STOP_Pos)            /*!< 0x00000200 */
#define DBGMCU_CR1_DBG_WWDG_STOP                   DBGMCU_CR1_DBG_WWDG_STOP_Msk                       /*!< desc DBG_WWDG_STOP */
#define DBGMCU_CR1_DBG_TIM1_STOP_Pos               (10U)
#define DBGMCU_CR1_DBG_TIM1_STOP_Msk               (0x1UL << DBGMCU_CR1_DBG_TIM1_STOP_Pos)            /*!< 0x00000400 */
#define DBGMCU_CR1_DBG_TIM1_STOP                   DBGMCU_CR1_DBG_TIM1_STOP_Msk                       /*!< desc DBG_TIM1_STOP */
#define DBGMCU_CR1_DBG_TIM2_STOP_Pos               (11U)
#define DBGMCU_CR1_DBG_TIM2_STOP_Msk               (0x1UL << DBGMCU_CR1_DBG_TIM2_STOP_Pos)            /*!< 0x00000800 */
#define DBGMCU_CR1_DBG_TIM2_STOP                   DBGMCU_CR1_DBG_TIM2_STOP_Msk                       /*!< desc DBG_TIM2_STOP */
#define DBGMCU_CR1_DBG_TIM3_STOP_Pos               (12U)
#define DBGMCU_CR1_DBG_TIM3_STOP_Msk               (0x1UL << DBGMCU_CR1_DBG_TIM3_STOP_Pos)            /*!< 0x00001000 */
#define DBGMCU_CR1_DBG_TIM3_STOP                   DBGMCU_CR1_DBG_TIM3_STOP_Msk                       /*!< desc DBG_TIM3_STOP */
#define DBGMCU_CR1_DBG_TIM4_STOP_Pos               (13U)
#define DBGMCU_CR1_DBG_TIM4_STOP_Msk               (0x1UL << DBGMCU_CR1_DBG_TIM4_STOP_Pos)            /*!< 0x00002000 */
#define DBGMCU_CR1_DBG_TIM4_STOP                   DBGMCU_CR1_DBG_TIM4_STOP_Msk                       /*!< desc DBG_TIM4_STOP */
#define DBGMCU_CR1_DBG_I2C1_SMBUS_TIMEOUT_Pos      (15U)
#define DBGMCU_CR1_DBG_I2C1_SMBUS_TIMEOUT_Msk      (0x1UL << DBGMCU_CR1_DBG_I2C1_SMBUS_TIMEOUT_Pos)   /*!< 0x00008000 */
#define DBGMCU_CR1_DBG_I2C1_SMBUS_TIMEOUT          DBGMCU_CR1_DBG_I2C1_SMBUS_TIMEOUT_Msk              /*!< desc DBG_I2C1_SMBUS_TIMEOUT */
#define DBGMCU_CR1_DBG_I2C2_SMBUS_TIMEOUT_Pos      (16U)
#define DBGMCU_CR1_DBG_I2C2_SMBUS_TIMEOUT_Msk      (0x1UL << DBGMCU_CR1_DBG_I2C2_SMBUS_TIMEOUT_Pos)   /*!< 0x00010000 */
#define DBGMCU_CR1_DBG_I2C2_SMBUS_TIMEOUT          DBGMCU_CR1_DBG_I2C2_SMBUS_TIMEOUT_Msk              /*!< desc DBG_I2C2_SMBUS_TIMEOUT */
#define DBGMCU_CR1_DBG_TIM6_STOP_Pos               (19U)
#define DBGMCU_CR1_DBG_TIM6_STOP_Msk               (0x1UL << DBGMCU_CR1_DBG_TIM6_STOP_Pos)            /*!< 0x00080000 */
#define DBGMCU_CR1_DBG_TIM6_STOP                   DBGMCU_CR1_DBG_TIM6_STOP_Msk                       /*!< desc DBG_TIM6_STOP */
#define DBGMCU_CR1_DBG_TIM7_STOP_Pos               (20U)
#define DBGMCU_CR1_DBG_TIM7_STOP_Msk               (0x1UL << DBGMCU_CR1_DBG_TIM7_STOP_Pos)            /*!< 0x00100000 */
#define DBGMCU_CR1_DBG_TIM7_STOP                   DBGMCU_CR1_DBG_TIM7_STOP_Msk                       /*!< desc DBG_TIM7_STOP */

/********************************* Bit definition for DBGMCU_CR2 register *******************************************/
#define DBGMCU_CR2_DBG_TIM15_STOP_Pos              (3U)
#define DBGMCU_CR2_DBG_TIM15_STOP_Msk              (0x1UL << DBGMCU_CR2_DBG_TIM15_STOP_Pos)           /*!< 0x00000008 */
#define DBGMCU_CR2_DBG_TIM15_STOP                  DBGMCU_CR2_DBG_TIM15_STOP_Msk                      /*!< desc DBG_TIM15_STOP */

#define DBGMCU_CR2_DBG_TIM16_STOP_Pos              (4U)
#define DBGMCU_CR2_DBG_TIM16_STOP_Msk              (0x1UL << DBGMCU_CR2_DBG_TIM16_STOP_Pos)           /*!< 0x00000010 */
#define DBGMCU_CR2_DBG_TIM16_STOP                  DBGMCU_CR2_DBG_TIM16_STOP_Msk                      /*!< desc DBG_TIM16_STOP */

#define DBGMCU_CR2_DBG_TIM17_STOP_Pos              (5U)
#define DBGMCU_CR2_DBG_TIM17_STOP_Msk              (0x1UL << DBGMCU_CR2_DBG_TIM17_STOP_Pos)           /*!< 0x00000020 */
#define DBGMCU_CR2_DBG_TIM17_STOP                  DBGMCU_CR2_DBG_TIM17_STOP_Msk                      /*!< desc DBG_TIM17_STOP */

#define DBGMCU_CR2_DBG_LPTIM_STOP_Pos              (8U)
#define DBGMCU_CR2_DBG_LPTIM_STOP_Msk              (0x1UL << DBGMCU_CR2_DBG_LPTIM_STOP_Pos)           /*!< 0x00000100 */
#define DBGMCU_CR2_DBG_LPTIM_STOP                  DBGMCU_CR2_DBG_LPTIM_STOP_Msk                      /*!< desc DBG_LPTIM_STOP */

#define DBGMCU_CR2_DBG_PWM1_STOP_Pos               (9U)
#define DBGMCU_CR2_DBG_PWM1_STOP_Msk               (0x1UL << DBGMCU_CR2_DBG_PWM1_STOP_Pos)            /*!< 0x00000200 */
#define DBGMCU_CR2_DBG_PWM1_STOP                   DBGMCU_CR2_DBG_PWM1_STOP_Msk                       /*!< desc DBG_PWM1_STOP */

#define DBGMCU_CR2_DBG_PWM2_STOP_Pos               (10U)
#define DBGMCU_CR2_DBG_PWM2_STOP_Msk               (0x1UL << DBGMCU_CR2_DBG_PWM2_STOP_Pos)            /*!< 0x00000400 */
#define DBGMCU_CR2_DBG_PWM2_STOP                   DBGMCU_CR2_DBG_PWM2_STOP_Msk                       /*!< desc DBG_PWM2_STOP */

#define DBGMCU_CR2_DBG_PWM3_STOP_Pos               (11U)
#define DBGMCU_CR2_DBG_PWM3_STOP_Msk               (0x1UL << DBGMCU_CR2_DBG_PWM3_STOP_Pos)            /*!< 0x00000800 */
#define DBGMCU_CR2_DBG_PWM3_STOP                   DBGMCU_CR2_DBG_PWM3_STOP_Msk                       /*!< desc DBG_PWM3_STOP */

#define DBGMCU_CR2_DBG_PWM4_STOP_Pos               (12U)
#define DBGMCU_CR2_DBG_PWM4_STOP_Msk               (0x1UL << DBGMCU_CR2_DBG_PWM4_STOP_Pos)            /*!< 0x00001000 */
#define DBGMCU_CR2_DBG_PWM4_STOP                   DBGMCU_CR2_DBG_PWM4_STOP_Msk                       /*!< desc DBG_PWM4_STOP */

/********************************************************************************************************************/
/********************************* DMA ******************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for DMA_ISR register **********************************************/
#define DMA_ISR_TCIF1_Pos                         (0U)
#define DMA_ISR_TCIF1_Msk                         (0x1UL<<DMA_ISR_TCIF1_Pos)                        /*!< 0x00000001 */
#define DMA_ISR_TCIF1                             DMA_ISR_TCIF1_Msk                                 /*!< Transfer Complete Flag for Channel 1 */
#define DMA_ISR_BTCIF1_Pos                        (1U)
#define DMA_ISR_BTCIF1_Msk                        (0x1UL<<DMA_ISR_BTCIF1_Pos)                       /*!< 0x00000002 */
#define DMA_ISR_BTCIF1                            DMA_ISR_BTCIF1_Msk                                /*!< Block Transfer Complete Flag for Channel 1 */
#define DMA_ISR_HBTIF1_Pos                        (2U)
#define DMA_ISR_HBTIF1_Msk                        (0x1UL<<DMA_ISR_HBTIF1_Pos)                       /*!< 0x00000004 */
#define DMA_ISR_HBTIF1                            DMA_ISR_HBTIF1_Msk                                /*!< Half Block Transfer Complete Flag for Channel 1 */
#define DMA_ISR_TEIF1_Pos                         (3U)
#define DMA_ISR_TEIF1_Msk                         (0x1UL<<DMA_ISR_TEIF1_Pos)                        /*!< 0x00000008 */
#define DMA_ISR_TEIF1                             DMA_ISR_TEIF1_Msk                                 /*!< Transfer Error Flag for Channel 1 */
#define DMA_ISR_TCIF2_Pos                         (4U)
#define DMA_ISR_TCIF2_Msk                         (0x1UL<<DMA_ISR_TCIF2_Pos)                        /*!< 0x00000010 */
#define DMA_ISR_TCIF2                             DMA_ISR_TCIF2_Msk                                 /*!< Transfer Complete Flag for Channel 2 */
#define DMA_ISR_BTCIF2_Pos                        (5U)
#define DMA_ISR_BTCIF2_Msk                        (0x1UL<<DMA_ISR_BTCIF2_Pos)                       /*!< 0x00000020 */
#define DMA_ISR_BTCIF2                            DMA_ISR_BTCIF2_Msk                                /*!< Block Transfer Complete Flag for Channel 2 */
#define DMA_ISR_HBTIF2_Pos                        (6U)
#define DMA_ISR_HBTIF2_Msk                        (0x1UL<<DMA_ISR_HBTIF2_Pos)                       /*!< 0x00000040 */
#define DMA_ISR_HBTIF2                            DMA_ISR_HBTIF2_Msk                                /*!< Half Block Transfer Complete Flag for Channel 2 */
#define DMA_ISR_TEIF2_Pos                         (7U)
#define DMA_ISR_TEIF2_Msk                         (0x1UL<<DMA_ISR_TEIF2_Pos)                        /*!< 0x00000080 */
#define DMA_ISR_TEIF2                             DMA_ISR_TEIF2_Msk                                 /*!< Transfer Error Flag for Channel 2 */
#define DMA_ISR_TCIF3_Pos                         (8U)
#define DMA_ISR_TCIF3_Msk                         (0x1UL<<DMA_ISR_TCIF3_Pos)                        /*!< 0x00000100 */
#define DMA_ISR_TCIF3                             DMA_ISR_TCIF3_Msk                                 /*!< Transfer Complete Flag for Channel 3 */
#define DMA_ISR_BTCIF3_Pos                        (9U)
#define DMA_ISR_BTCIF3_Msk                        (0x1UL<<DMA_ISR_BTCIF3_Pos)                       /*!< 0x00000200 */
#define DMA_ISR_BTCIF3                            DMA_ISR_BTCIF3_Msk                                /*!< Block Transfer Complete Flag for Channel 3 */
#define DMA_ISR_HBTIF3_Pos                        (10U)
#define DMA_ISR_HBTIF3_Msk                        (0x1UL<<DMA_ISR_HBTIF3_Pos)                       /*!< 0x00000400 */
#define DMA_ISR_HBTIF3                            DMA_ISR_HBTIF3_Msk                                /*!< Half Block Transfer Complete Flag for Channel 3 */
#define DMA_ISR_TEIF3_Pos                         (11U)
#define DMA_ISR_TEIF3_Msk                         (0x1UL<<DMA_ISR_TEIF3_Pos)                        /*!< 0x00000800 */
#define DMA_ISR_TEIF3                             DMA_ISR_TEIF3_Msk                                 /*!< Transfer Error Flag for Channel 3 */
#define DMA_ISR_TCIF4_Pos                         (12U)
#define DMA_ISR_TCIF4_Msk                         (0x1UL<<DMA_ISR_TCIF4_Pos)                        /*!< 0x00001000 */
#define DMA_ISR_TCIF4                             DMA_ISR_TCIF4_Msk                                 /*!< Transfer Complete Flag for Channel 4 */
#define DMA_ISR_BTCIF4_Pos                        (13U)
#define DMA_ISR_BTCIF4_Msk                        (0x1UL<<DMA_ISR_BTCIF4_Pos)                       /*!< 0x00002000 */
#define DMA_ISR_BTCIF4                            DMA_ISR_BTCIF4_Msk                                /*!< Block Transfer Complete Flag for Channel 4 */
#define DMA_ISR_HBTIF4_Pos                        (14U)
#define DMA_ISR_HBTIF4_Msk                        (0x1UL<<DMA_ISR_HBTIF4_Pos)                       /*!< 0x00004000 */
#define DMA_ISR_HBTIF4                            DMA_ISR_HBTIF4_Msk                                /*!< Half Block Transfer Complete Flag for Channel 4 */
#define DMA_ISR_TEIF4_Pos                         (15U)
#define DMA_ISR_TEIF4_Msk                         (0x1UL<<DMA_ISR_TEIF4_Pos)                        /*!< 0x00008000 */
#define DMA_ISR_TEIF4                             DMA_ISR_TEIF4_Msk                                 /*!< Transfer Error Flag for Channel 4 */
#define DMA_ISR_TCIF5_Pos                         (16U)
#define DMA_ISR_TCIF5_Msk                         (0x1UL<<DMA_ISR_TCIF5_Pos)                        /*!< 0x00010000 */
#define DMA_ISR_TCIF5                             DMA_ISR_TCIF5_Msk                                 /*!< Transfer Complete Flag for Channel 5 */
#define DMA_ISR_BTCIF5_Pos                        (17U)
#define DMA_ISR_BTCIF5_Msk                        (0x1UL<<DMA_ISR_BTCIF5_Pos)                       /*!< 0x00020000 */
#define DMA_ISR_BTCIF5                            DMA_ISR_BTCIF5_Msk                                /*!< Block Transfer Complete Flag for Channel 5 */
#define DMA_ISR_HBTIF5_Pos                        (18U)
#define DMA_ISR_HBTIF5_Msk                        (0x1UL<<DMA_ISR_HBTIF5_Pos)                       /*!< 0x00040000 */
#define DMA_ISR_HBTIF5                            DMA_ISR_HBTIF5_Msk                                /*!< Half Block Transfer Complete Flag for Channel 5 */
#define DMA_ISR_TEIF5_Pos                         (19U)
#define DMA_ISR_TEIF5_Msk                         (0x1UL<<DMA_ISR_TEIF5_Pos)                        /*!< 0x00080000 */
#define DMA_ISR_TEIF5                             DMA_ISR_TEIF5_Msk                                 /*!< Transfer Error Flag for Channel 5 */
#define DMA_ISR_TCIF6_Pos                         (20U)
#define DMA_ISR_TCIF6_Msk                         (0x1UL<<DMA_ISR_TCIF6_Pos)                        /*!< 0x00100000 */
#define DMA_ISR_TCIF6                             DMA_ISR_TCIF6_Msk                                 /*!< Transfer Complete Flag for Channel 6 */
#define DMA_ISR_BTCIF6_Pos                        (21U)
#define DMA_ISR_BTCIF6_Msk                        (0x1UL<<DMA_ISR_BTCIF6_Pos)                       /*!< 0x00200000 */
#define DMA_ISR_BTCIF6                            DMA_ISR_BTCIF6_Msk                                /*!< Block Transfer Complete Flag for Channel 6 */
#define DMA_ISR_HBTIF6_Pos                        (22U)
#define DMA_ISR_HBTIF6_Msk                        (0x1UL<<DMA_ISR_HBTIF6_Pos)                       /*!< 0x00400000 */
#define DMA_ISR_HBTIF6                            DMA_ISR_HBTIF6_Msk                                /*!< Half Block Transfer Complete Flag for Channel 6 */
#define DMA_ISR_TEIF6_Pos                         (23U)
#define DMA_ISR_TEIF6_Msk                         (0x1UL<<DMA_ISR_TEIF6_Pos)                        /*!< 0x00800000 */
#define DMA_ISR_TEIF6                             DMA_ISR_TEIF6_Msk                                 /*!< Transfer Error Flag for Channel 6 */
#define DMA_ISR_TCIF7_Pos                         (24U)
#define DMA_ISR_TCIF7_Msk                         (0x1UL<<DMA_ISR_TCIF7_Pos)                        /*!< 0x01000000 */
#define DMA_ISR_TCIF7                             DMA_ISR_TCIF7_Msk                                 /*!< Transfer Complete Flag for Channel 7 */
#define DMA_ISR_BTCIF7_Pos                        (25U)
#define DMA_ISR_BTCIF7_Msk                        (0x1UL<<DMA_ISR_BTCIF7_Pos)                       /*!< 0x02000000 */
#define DMA_ISR_BTCIF7                            DMA_ISR_BTCIF7_Msk                                /*!< Block Transfer Complete Flag for Channel 7 */
#define DMA_ISR_HBTIF7_Pos                        (26U)
#define DMA_ISR_HBTIF7_Msk                        (0x1UL<<DMA_ISR_HBTIF7_Pos)                       /*!< 0x04000000 */
#define DMA_ISR_HBTIF7                            DMA_ISR_HBTIF7_Msk                                /*!< Half Block Transfer Complete Flag for Channel 7 */
#define DMA_ISR_TEIF7_Pos                         (27U)
#define DMA_ISR_TEIF7_Msk                         (0x1UL<<DMA_ISR_TEIF7_Pos)                        /*!< 0x08000000 */
#define DMA_ISR_TEIF7                             DMA_ISR_TEIF7_Msk                                 /*!< Transfer Error Flag for Channel 7 */
#define DMA_ISR_TCIF8_Pos                         (28U)
#define DMA_ISR_TCIF8_Msk                         (0x1UL<<DMA_ISR_TCIF8_Pos)                        /*!< 0x10000000 */
#define DMA_ISR_TCIF8                             DMA_ISR_TCIF8_Msk                                 /*!< Transfer Complete Flag for Channel 8 */
#define DMA_ISR_BTCIF8_Pos                        (29U)
#define DMA_ISR_BTCIF8_Msk                        (0x1UL<<DMA_ISR_BTCIF8_Pos)                       /*!< 0x20000000 */
#define DMA_ISR_BTCIF8                            DMA_ISR_BTCIF8_Msk                                /*!< Block Transfer Complete Flag for Channel 8 */
#define DMA_ISR_HBTIF8_Pos                        (30U)
#define DMA_ISR_HBTIF8_Msk                        (0x1UL<<DMA_ISR_HBTIF8_Pos)                       /*!< 0x40000000 */
#define DMA_ISR_HBTIF8                            DMA_ISR_HBTIF8_Msk                                /*!< Half Block Transfer Complete Flag for Channel 8 */
#define DMA_ISR_TEIF8_Pos                         (31U)
#define DMA_ISR_TEIF8_Msk                         (0x1UL<<DMA_ISR_TEIF78_Pos)                        /*!< 0x80000000 */
#define DMA_ISR_TEIF8                             DMA_ISR_TEIF8_Msk                                 /*!< Transfer Error Flag for Channel 8 */

/********************************* Bit definition for DMA_IFCR register *********************************************/
#define DMA_IFCR_CTCIF1_Pos                       (0U)
#define DMA_IFCR_CTCIF1_Msk                       (0x1UL<<DMA_IFCR_CTCIF1_Pos)                      /*!< 0x00000001 */
#define DMA_IFCR_CTCIF1                           DMA_IFCR_CTCIF1_Msk                               /*!< Transfer Complete Flag Clear for Channel 1 */
#define DMA_IFCR_CBTCIF1_Pos                      (1U)
#define DMA_IFCR_CBTCIF1_Msk                      (0x1UL<<DMA_IFCR_CBTCIF1_Pos)                     /*!< 0x00000002 */
#define DMA_IFCR_CBTCIF1                          DMA_IFCR_CBTCIF1_Msk                              /*!< Block Transfer Complete Flag Clear for Channel 1 */
#define DMA_IFCR_CHBTIF1_Pos                      (2U)
#define DMA_IFCR_CHBTIF1_Msk                      (0x1UL<<DMA_IFCR_CHBTIF1_Pos)                     /*!< 0x00000004 */
#define DMA_IFCR_CHBTIF1                          DMA_IFCR_CHBTIF1_Msk                              /*!< Half Block Transfer Complete Flag Clear for Channel 1 */
#define DMA_IFCR_CTEIF1_Pos                       (3U)
#define DMA_IFCR_CTEIF1_Msk                       (0x1UL<<DMA_IFCR_CTEIF1_Pos)                      /*!< 0x00000008 */
#define DMA_IFCR_CTEIF1                           DMA_IFCR_CTEIF1_Msk                               /*!< Transfer Error Flag Clear for Channel 1 */
#define DMA_IFCR_CTCIF2_Pos                       (4U)
#define DMA_IFCR_CTCIF2_Msk                       (0x1UL<<DMA_IFCR_CTCIF2_Pos)                      /*!< 0x00000010 */
#define DMA_IFCR_CTCIF2                           DMA_IFCR_CTCIF2_Msk                               /*!< Transfer Complete Flag Clear for Channel 2 */
#define DMA_IFCR_CBTCIF2_Pos                      (5U)
#define DMA_IFCR_CBTCIF2_Msk                      (0x1UL<<DMA_IFCR_CBTCIF2_Pos)                     /*!< 0x00000020 */
#define DMA_IFCR_CBTCIF2                          DMA_IFCR_CBTCIF2_Msk                              /*!< Block Transfer Complete Flag Clear for Channel 2 */
#define DMA_IFCR_CHBTIF2_Pos                      (6U)
#define DMA_IFCR_CHBTIF2_Msk                      (0x1UL<<DMA_IFCR_CHBTIF2_Pos)                     /*!< 0x00000040 */
#define DMA_IFCR_CHBTIF2                          DMA_IFCR_CHBTIF2_Msk                              /*!< Half Block Transfer Complete Flag Clear for Channel 2 */
#define DMA_IFCR_CTEIF2_Pos                       (7U)
#define DMA_IFCR_CTEIF2_Msk                       (0x1UL<<DMA_IFCR_CTEIF2_Pos)                      /*!< 0x00000080 */
#define DMA_IFCR_CTEIF2                           DMA_IFCR_CTEIF2_Msk                               /*!< Transfer Error Flag Clear for Channel 2 */
#define DMA_IFCR_CTCIF3_Pos                       (8U)
#define DMA_IFCR_CTCIF3_Msk                       (0x1UL<<DMA_IFCR_CTCIF3_Pos)                      /*!< 0x00000100 */
#define DMA_IFCR_CTCIF3                           DMA_IFCR_CTCIF3_Msk                               /*!< Transfer Complete Flag Clear for Channel 3 */
#define DMA_IFCR_CBTCIF3_Pos                      (9U)
#define DMA_IFCR_CBTCIF3_Msk                      (0x1UL<<DMA_IFCR_CBTCIF3_Pos)                     /*!< 0x00000200 */
#define DMA_IFCR_CBTCIF3                          DMA_IFCR_CBTCIF3_Msk                              /*!< Block Transfer Complete Flag Clear for Channel 3 */
#define DMA_IFCR_CHBTIF3_Pos                      (10U)
#define DMA_IFCR_CHBTIF3_Msk                      (0x1UL<<DMA_IFCR_CHBTIF3_Pos)                     /*!< 0x00000400 */
#define DMA_IFCR_CHBTIF3                          DMA_IFCR_CHBTIF3_Msk                              /*!< Half Block Transfer Complete Flag Clear for Channel 3 */
#define DMA_IFCR_CTEIF3_Pos                       (11U)
#define DMA_IFCR_CTEIF3_Msk                       (0x1UL<<DMA_IFCR_CTEIF3_Pos)                      /*!< 0x00000800 */
#define DMA_IFCR_CTEIF3                           DMA_IFCR_CTEIF3_Msk                               /*!< Transfer Error Flag Clear for Channel 3 */
#define DMA_IFCR_CTCIF4_Pos                       (12U)
#define DMA_IFCR_CTCIF4_Msk                       (0x1UL<<DMA_IFCR_CTCIF4_Pos)                      /*!< 0x00001000 */
#define DMA_IFCR_CTCIF4                           DMA_IFCR_CTCIF4_Msk                               /*!< Transfer Complete Flag Clear for Channel 4 */
#define DMA_IFCR_CBTCIF4_Pos                      (13U)
#define DMA_IFCR_CBTCIF4_Msk                      (0x1UL<<DMA_IFCR_CBTCIF4_Pos)                     /*!< 0x00002000 */
#define DMA_IFCR_CBTCIF4                          DMA_IFCR_CBTCIF4_Msk                              /*!< Block Transfer Complete Flag Clear for Channel 4 */
#define DMA_IFCR_CHBTIF4_Pos                      (14U)
#define DMA_IFCR_CHBTIF4_Msk                      (0x1UL<<DMA_IFCR_CHBTIF4_Pos)                     /*!< 0x00004000 */
#define DMA_IFCR_CHBTIF4                          DMA_IFCR_CHBTIF4_Msk                              /*!< Half Block Transfer Complete Flag Clear for Channel 4 */
#define DMA_IFCR_CTEIF4_Pos                       (15U)
#define DMA_IFCR_CTEIF4_Msk                       (0x1UL<<DMA_IFCR_CTEIF4_Pos)                      /*!< 0x00008000 */
#define DMA_IFCR_CTEIF4                           DMA_IFCR_CTEIF4_Msk                               /*!< Transfer Error Flag Clear for Channel 4 */
#define DMA_IFCR_CTCIF5_Pos                       (16U)
#define DMA_IFCR_CTCIF5_Msk                       (0x1UL<<DMA_IFCR_CTCIF5_Pos)                      /*!< 0x00010000 */
#define DMA_IFCR_CTCIF5                           DMA_IFCR_CTCIF5_Msk                               /*!< Transfer Complete Flag Clear for Channel 5 */
#define DMA_IFCR_CBTCIF5_Pos                      (17U)
#define DMA_IFCR_CBTCIF5_Msk                      (0x1UL<<DMA_IFCR_CBTCIF5_Pos)                     /*!< 0x00020000 */
#define DMA_IFCR_CBTCIF5                          DMA_IFCR_CBTCIF5_Msk                              /*!< Block Transfer Complete Flag Clear for Channel 5 */
#define DMA_IFCR_CHBTIF5_Pos                      (18U)
#define DMA_IFCR_CHBTIF5_Msk                      (0x1UL<<DMA_IFCR_CHBTIF5_Pos)                     /*!< 0x00040000 */
#define DMA_IFCR_CHBTIF5                          DMA_IFCR_CHBTIF5_Msk                              /*!< Half Block Transfer Complete Flag Clear for Channel 5 */
#define DMA_IFCR_CTEIF5_Pos                       (19U)
#define DMA_IFCR_CTEIF5_Msk                       (0x1UL<<DMA_IFCR_CTEIF5_Pos)                      /*!< 0x00080000 */
#define DMA_IFCR_CTEIF5                           DMA_IFCR_CTEIF5_Msk                               /*!< Transfer Error Flag Clear for Channel 5 */
#define DMA_IFCR_CTCIF6_Pos                       (20U)
#define DMA_IFCR_CTCIF6_Msk                       (0x1UL<<DMA_IFCR_CTCIF6_Pos)                      /*!< 0x00100000 */
#define DMA_IFCR_CTCIF6                           DMA_IFCR_CTCIF6_Msk                               /*!< Transfer Complete Flag Clear for Channel 6 */
#define DMA_IFCR_CBTCIF6_Pos                      (21U)
#define DMA_IFCR_CBTCIF6_Msk                      (0x1UL<<DMA_IFCR_CBTCIF6_Pos)                     /*!< 0x00200000 */
#define DMA_IFCR_CBTCIF6                          DMA_IFCR_CBTCIF6_Msk                              /*!< Block Transfer Complete Flag Clear for Channel 6 */
#define DMA_IFCR_CHBTIF6_Pos                      (22U)
#define DMA_IFCR_CHBTIF6_Msk                      (0x1UL<<DMA_IFCR_CHBTIF6_Pos)                     /*!< 0x00400000 */
#define DMA_IFCR_CHBTIF6                          DMA_IFCR_CHBTIF6_Msk                              /*!< Half Block Transfer Complete Flag Clear for Channel 6 */
#define DMA_IFCR_CTEIF6_Pos                       (23U)
#define DMA_IFCR_CTEIF6_Msk                       (0x1UL<<DMA_IFCR_CTEIF6_Pos)                      /*!< 0x00800000 */
#define DMA_IFCR_CTEIF6                           DMA_IFCR_CTEIF6_Msk                               /*!< Transfer Error Flag Clear for Channel 6 */
#define DMA_IFCR_CTCIF7_Pos                       (24U)
#define DMA_IFCR_CTCIF7_Msk                       (0x1UL<<DMA_IFCR_CTCIF7_Pos)                      /*!< 0x01000000 */
#define DMA_IFCR_CTCIF7                           DMA_IFCR_CTCIF7_Msk                               /*!< Transfer Complete Flag Clear for Channel 7 */
#define DMA_IFCR_CBTCIF7_Pos                      (25U)
#define DMA_IFCR_CBTCIF7_Msk                      (0x1UL<<DMA_IFCR_CBTCIF7_Pos)                     /*!< 0x02000000 */
#define DMA_IFCR_CBTCIF7                          DMA_IFCR_CBTCIF7_Msk                              /*!< Block Transfer Complete Flag Clear for Channel 7 */
#define DMA_IFCR_CHBTIF7_Pos                      (26U)
#define DMA_IFCR_CHBTIF7_Msk                      (0x1UL<<DMA_IFCR_CHBTIF7_Pos)                     /*!< 0x04000000 */
#define DMA_IFCR_CHBTIF7                          DMA_IFCR_CHBTIF7_Msk                              /*!< Half Block Transfer Complete Flag Clear for Channel 7 */
#define DMA_IFCR_CTEIF7_Pos                       (27U)
#define DMA_IFCR_CTEIF7_Msk                       (0x1UL<<DMA_IFCR_CTEIF7_Pos)                      /*!< 0x08000000 */
#define DMA_IFCR_CTEIF7                           DMA_IFCR_CTEIF7_Msk                               /*!< Transfer Error Flag Clear for Channel 7 */
#define DMA_IFCR_CTCIF8_Pos                       (28U)
#define DMA_IFCR_CTCIF8_Msk                       (0x1UL<<DMA_IFCR_CTCIF8_Pos)                      /*!< 0x10000000 */
#define DMA_IFCR_CTCIF8                           DMA_IFCR_CTCIF8_Msk                               /*!< Transfer Complete Flag Clear for Channel 8 */
#define DMA_IFCR_CBTCIF8_Pos                      (29U)
#define DMA_IFCR_CBTCIF8_Msk                      (0x1UL<<DMA_IFCR_CBTCIF8_Pos)                     /*!< 0x20000000 */
#define DMA_IFCR_CBTCIF8                          DMA_IFCR_CBTCIF8_Msk                              /*!< Block Transfer Complete Flag Clear for Channel 8 */
#define DMA_IFCR_CHBTIF8_Pos                      (30U)
#define DMA_IFCR_CHBTIF8_Msk                      (0x1UL<<DMA_IFCR_CHBTIF8_Pos)                     /*!< 0x40000000 */
#define DMA_IFCR_CHBTIF8                          DMA_IFCR_CHBTIF8_Msk                              /*!< Half Block Transfer Complete Flag Clear for Channel 8 */
#define DMA_IFCR_CTEIF8_Pos                       (31U)
#define DMA_IFCR_CTEIF8_Msk                       (0x1UL<<DMA_IFCR_CTEIF8_Pos)                      /*!< 0x80000000 */
#define DMA_IFCR_CTEIF8                           DMA_IFCR_CTEIF8_Msk                               /*!< Transfer Error Flag Clear for Channel 8 */

/********************************* Bit definition for DMA_CCR register *********************************************/
#define DMA_CCR_EN_Pos                           (0U)
#define DMA_CCR_EN_Msk                           (0x1UL<<DMA_CCR_EN_Pos)                          /*!< 0x00000001 */
#define DMA_CCR_EN                               DMA_CCR_EN_Msk                                   /*!< Channel Enable */
#define DMA_CCR_TCIE_Pos                         (1U)
#define DMA_CCR_TCIE_Msk                         (0x1UL<<DMA_CCR_TCIE_Pos)                        /*!< 0x00000002 */
#define DMA_CCR_TCIE                             DMA_CCR_TCIE_Msk                                 /*!< Transfer Complete Interrupt Enable */
#define DMA_CCR_BTCIE_Pos                        (2U)
#define DMA_CCR_BTCIE_Msk                        (0x1UL<<DMA_CCR_BTCIE_Pos)                       /*!< 0x00000004 */
#define DMA_CCR_BTCIE                            DMA_CCR_BTCIE_Msk                                /*!< Block Transfer Complete Interrupt Enable */
#define DMA_CCR_HBTIE_Pos                        (3U)
#define DMA_CCR_HBTIE_Msk                        (0x1UL<<DMA_CCR_HBTIE_Pos)                       /*!< 0x00000008 */
#define DMA_CCR_HBTIE                            DMA_CCR_HBTIE_Msk                                /*!< Half Block Transfer Complete Interrupt Enable */
#define DMA_CCR_TEIE_Pos                         (4U)
#define DMA_CCR_TEIE_Msk                         (0x1UL<<DMA_CCR_TEIE_Pos)                        /*!< 0x00000010 */
#define DMA_CCR_TEIE                             DMA_CCR_TEIE_Msk                                 /*!< Transfer Error Interrupt Enable */
#define DMA_CCR_DIR_Pos                          (5U)
#define DMA_CCR_DIR_Msk                          (0x1UL<<DMA_CCR_DIR_Pos)                         /*!< 0x00000020 */
#define DMA_CCR_DIR                              DMA_CCR_DIR_Msk                                  /*!< Data Transfer Direction */
#define DMA_CCR_CIRC_Pos                         (6U)
#define DMA_CCR_CIRC_Msk                         (0x1UL<<DMA_CCR_CIRC_Pos)                        /*!< 0x00000040 */
#define DMA_CCR_CIRC                             DMA_CCR_CIRC_Msk                                 /*!< Circular Mode */
#define DMA_CCR_TRANST_Pos                       (7U)
#define DMA_CCR_TRANST_Msk                       (0x1UL<<DMA_CCR_TRANST_Pos)                      /*!< 0x00000080 */
#define DMA_CCR_TRANST                           DMA_CCR_TRANST_Msk                               /*!< Transfer Type */
#define DMA_CCR_PINC_Pos                         (8U)
#define DMA_CCR_PINC_Msk                         (0x3UL<<DMA_CCR_PINC_Pos)                        /*!< 0x00000300 */
#define DMA_CCR_PINC                             DMA_CCR_PINC_Msk                                 /*!< Peripheral Increment Mode */
#define DMA_CCR_PINC_0                           (0x1UL<<DMA_CCR_PINC_Pos)                        /*!< 0x00000100 */
#define DMA_CCR_PINC_1                           (0x2UL<<DMA_CCR_PINC_Pos)                        /*!< 0x00000200 */
#define DMA_CCR_MINC_Pos                         (10U)
#define DMA_CCR_MINC_Msk                         (0x3UL<<DMA_CCR_MINC_Pos)                        /*!< 0x00000C00 */
#define DMA_CCR_MINC                             DMA_CCR_MINC_Msk                                 /*!< Memory Increment Mode */
#define DMA_CCR_MINC_0                           (0x1UL<<DMA_CCR_MINC_Pos)                        /*!< 0x00000400 */
#define DMA_CCR_MINC_1                           (0x2UL<<DMA_CCR_MINC_Pos)                        /*!< 0x00000800 */
#define DMA_CCR_PSIZE_Pos                        (12U)
#define DMA_CCR_PSIZE_Msk                        (0x3UL<<DMA_CCR_PSIZE_Pos)                       /*!< 0x00003000 */
#define DMA_CCR_PSIZE                            DMA_CCR_PSIZE_Msk                                /*!< Peripheral Size */
#define DMA_CCR_PSIZE_0                          (0x1UL<<DMA_CCR_PSIZE_Pos)                       /*!< 0x00001000 */
#define DMA_CCR_PSIZE_1                          (0x2UL<<DMA_CCR_PSIZE_Pos)                       /*!< 0x00002000 */
#define DMA_CCR_MSIZE_Pos                        (14U)
#define DMA_CCR_MSIZE_Msk                        (0x3UL<<DMA_CCR_MSIZE_Pos)                       /*!< 0x0000C000 */
#define DMA_CCR_MSIZE                            DMA_CCR_MSIZE_Msk                                /*!< Memory Size */
#define DMA_CCR_MSIZE_0                          (0x1UL<<DMA_CCR_MSIZE_Pos)                       /*!< 0x00004000 */
#define DMA_CCR_MSIZE_1                          (0x2UL<<DMA_CCR_MSIZE_Pos)                       /*!< 0x00008000 */
#define DMA_CCR_PL_Pos                           (16U)
#define DMA_CCR_PL_Msk                           (0x7UL<<DMA_CCR_PL_Pos)                          /*!< 0x00070000 */
#define DMA_CCR_PL                               DMA_CCR_PL_Msk                                   /*!< Priority Level */
#define DMA_CCR_PL_0                             (0x1UL<<DMA_CCR_PL_Pos)                          /*!< 0x00010000 */
#define DMA_CCR_PL_1                             (0x2UL<<DMA_CCR_PL_Pos)                          /*!< 0x00020000 */
#define DMA_CCR_PL_2                             (0x4UL<<DMA_CCR_PL_Pos)                          /*!< 0x00040000 */
#define DMA_CCR_MEM2MEM_Pos                      (19U)
#define DMA_CCR_MEM2MEM_Msk                      (0x1UL<<DMA_CCR_MEM2MEM_Pos)                     /*!< 0x00080000 */
#define DMA_CCR_MEM2MEM                          DMA_CCR_MEM2MEM_Msk                              /*!< Memory-to-memory Mode */
#define DMA_CCR_PNORLD_Pos                       (20U)
#define DMA_CCR_PNORLD_Msk                       (0x1UL<<DMA_CCR_PNORLD_Pos)                      /*!< 0x00100000 */
#define DMA_CCR_PNORLD                           DMA_CCR_PNORLD_Msk                               /*!< Peripheral No Reload */
#define DMA_CCR_MNORLD_Pos                       (21U)
#define DMA_CCR_MNORLD_Msk                       (0x1UL<<DMA_CCR_MNORLD_Pos)                      /*!< 0x00200000 */
#define DMA_CCR_MNORLD                           DMA_CCR_MNORLD_Msk                               /*!< Memory No Reload */
#define DMA_CCR_BTCSUSP_Pos                      (22U)
#define DMA_CCR_BTCSUSP_Msk                      (0x1UL<<DMA_CCR_BTCSUSP_Pos)                     /*!< 0x00400000 */
#define DMA_CCR_BTCSUSP                          DMA_CCR_BTCSUSP_Msk                              /*!< Suspend in Block Transfer Complete Interrupt */
#define DMA_CCR_M2MARB_Pos                       (23U)
#define DMA_CCR_M2MARB_Msk                       (0x1UL<<DMA_CCR_M2MARB_Pos)                      /*!< 0x00800000 */
#define DMA_CCR_M2MARB                           DMA_CCR_M2MARB_Msk                               /*!< Memory-to-memory Mode Arbitration */

/********************************* Bit definition for DMA_CNDTR register *******************************************/
#define DMA_CNDTR_NDT_Pos                        (0U)
#define DMA_CNDTR_NDT_Msk                        (0xFFFFUL<<DMA_CNDTR_NDT_Pos)                    /*!< 0x0000FFFF */
#define DMA_CNDTR_NDT                            DMA_CNDTR_NDT_Msk                                /*!< Number of Data to Transfer */

/********************************* Bit definition for DMA_CPAR register ********************************************/
#define DMA_CPAR_PA_Pos                          (0U)
#define DMA_CPAR_PA_Msk                          (0xFFFFFFFFUL<<DMA_CPAR_PA_Pos)                  /*!< 0xFFFFFFFF */
#define DMA_CPAR_PA                              DMA_CPAR_PA_Msk                                  /*!< Peripheral Address */

/********************************* Bit definition for DMA_CMAR register ********************************************/
#define DMA_CMAR_MA_Pos                          (0U)
#define DMA_CMAR_MA_Msk                          (0xFFFFFFFFUL<<DMA_CMAR_MA_Pos)                  /*!< 0xFFFFFFFF */
#define DMA_CMAR_MA                              DMA_CMAR_MA_Msk                                  /*!< Memory Address */

/********************************* Bit definition for DMA_CCCFGR register ******************************************/
#define DMA_CNBTR_NBT_Pos                        (0U)
#define DMA_CNBTR_NBT_Msk                        (0xFFUL<<DMA_CNBTR_NBT_Pos)                      /*!< 0x000000FF */
#define DMA_CNBTR_NBT                            DMA_CNBTR_NBT_Msk                                /*!< Number of Block to Loop Transfer */
#define DMA_CNBTR_NDTL_Pos                       (16U)
#define DMA_CNBTR_NDTL_Msk                       (0xFFFFUL<<DMA_CNBTR_NDTL_Pos)                   /*!< 0xFFFF0000 */
#define DMA_CNBTR_NDTL                           DMA_CNBTR_NDTL_Msk                               /*!< Number of Data to Transfer Last Loop */

/********************************************************************************************************************/
/********************************* EXTI *****************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for EXTI_IMR register *********************************************/
#define EXTI_IMR_IMR0_Pos                          (0U)
#define EXTI_IMR_IMR0_Msk                          (0x1UL<<EXTI_IMR_IMR0_Pos)                       /*!< 0x00000001 */
#define EXTI_IMR_IMR0                              EXTI_IMR_IMR0_Msk                                
#define EXTI_IMR_IMR1_Pos                          (1U)
#define EXTI_IMR_IMR1_Msk                          (0x1UL<<EXTI_IMR_IMR1_Pos)                       /*!< 0x00000002 */
#define EXTI_IMR_IMR1                              EXTI_IMR_IMR1_Msk                                
#define EXTI_IMR_IMR2_Pos                          (2U)
#define EXTI_IMR_IMR2_Msk                          (0x1UL<<EXTI_IMR_IMR2_Pos)                       /*!< 0x00000004 */
#define EXTI_IMR_IMR2                              EXTI_IMR_IMR2_Msk                                
#define EXTI_IMR_IMR3_Pos                          (3U)
#define EXTI_IMR_IMR3_Msk                          (0x1UL<<EXTI_IMR_IMR3_Pos)                       /*!< 0x00000008 */
#define EXTI_IMR_IMR3                              EXTI_IMR_IMR3_Msk                                
#define EXTI_IMR_IMR4_Pos                          (4U)
#define EXTI_IMR_IMR4_Msk                          (0x1UL<<EXTI_IMR_IMR4_Pos)                       /*!< 0x00000010 */
#define EXTI_IMR_IMR4                              EXTI_IMR_IMR4_Msk                                
#define EXTI_IMR_IMR5_Pos                          (5U)
#define EXTI_IMR_IMR5_Msk                          (0x1UL<<EXTI_IMR_IMR5_Pos)                       /*!< 0x00000020 */
#define EXTI_IMR_IMR5                              EXTI_IMR_IMR5_Msk                                
#define EXTI_IMR_IMR6_Pos                          (6U)
#define EXTI_IMR_IMR6_Msk                          (0x1UL<<EXTI_IMR_IMR6_Pos)                       /*!< 0x00000040 */
#define EXTI_IMR_IMR6                              EXTI_IMR_IMR6_Msk                                
#define EXTI_IMR_IMR7_Pos                          (7U)
#define EXTI_IMR_IMR7_Msk                          (0x1UL<<EXTI_IMR_IMR7_Pos)                       /*!< 0x00000080 */
#define EXTI_IMR_IMR7                              EXTI_IMR_IMR7_Msk                                
#define EXTI_IMR_IMR8_Pos                          (8U)
#define EXTI_IMR_IMR8_Msk                          (0x1UL<<EXTI_IMR_IMR8_Pos)                       /*!< 0x00000100 */
#define EXTI_IMR_IMR8                              EXTI_IMR_IMR8_Msk                                
#define EXTI_IMR_IMR9_Pos                          (9U)
#define EXTI_IMR_IMR9_Msk                          (0x1UL<<EXTI_IMR_IMR9_Pos)                       /*!< 0x00000200 */
#define EXTI_IMR_IMR9                              EXTI_IMR_IMR9_Msk                                
#define EXTI_IMR_IMR10_Pos                         (10U)
#define EXTI_IMR_IMR10_Msk                         (0x1UL<<EXTI_IMR_IMR10_Pos)                      /*!< 0x00000400 */
#define EXTI_IMR_IMR10                             EXTI_IMR_IMR10_Msk                               
#define EXTI_IMR_IMR11_Pos                         (11U)
#define EXTI_IMR_IMR11_Msk                         (0x1UL<<EXTI_IMR_IMR11_Pos)                      /*!< 0x00000800 */
#define EXTI_IMR_IMR11                             EXTI_IMR_IMR11_Msk                               
#define EXTI_IMR_IMR12_Pos                         (12U)
#define EXTI_IMR_IMR12_Msk                         (0x1UL<<EXTI_IMR_IMR12_Pos)                      /*!< 0x00001000 */
#define EXTI_IMR_IMR12                             EXTI_IMR_IMR12_Msk                               
#define EXTI_IMR_IMR13_Pos                         (13U)
#define EXTI_IMR_IMR13_Msk                         (0x1UL<<EXTI_IMR_IMR13_Pos)                      /*!< 0x00002000 */
#define EXTI_IMR_IMR13                             EXTI_IMR_IMR13_Msk                               
#define EXTI_IMR_IMR14_Pos                         (14U)
#define EXTI_IMR_IMR14_Msk                         (0x1UL<<EXTI_IMR_IMR14_Pos)                      /*!< 0x00004000 */
#define EXTI_IMR_IMR14                             EXTI_IMR_IMR14_Msk                               
#define EXTI_IMR_IMR15_Pos                         (15U)
#define EXTI_IMR_IMR15_Msk                         (0x1UL<<EXTI_IMR_IMR15_Pos)                      /*!< 0x00008000 */
#define EXTI_IMR_IMR15                             EXTI_IMR_IMR15_Msk                               
#define EXTI_IMR_IMR16_Pos                         (16U)
#define EXTI_IMR_IMR16_Msk                         (0x1UL<<EXTI_IMR_IMR16_Pos)                      /*!< 0x00010000 */
#define EXTI_IMR_IMR16                             EXTI_IMR_IMR16_Msk                               
#define EXTI_IMR_IMR17_Pos                         (17U)
#define EXTI_IMR_IMR17_Msk                         (0x1UL<<EXTI_IMR_IMR17_Pos)                      /*!< 0x00020000 */
#define EXTI_IMR_IMR17                             EXTI_IMR_IMR17_Msk                               
#define EXTI_IMR_IMR18_Pos                         (18U)
#define EXTI_IMR_IMR18_Msk                         (0x1UL<<EXTI_IMR_IMR18_Pos)                      /*!< 0x00040000 */
#define EXTI_IMR_IMR18                             EXTI_IMR_IMR18_Msk                               
#define EXTI_IMR_IMR19_Pos                         (19U)
#define EXTI_IMR_IMR19_Msk                         (0x1UL<<EXTI_IMR_IMR19_Pos)                      /*!< 0x00080000 */
#define EXTI_IMR_IMR19                             EXTI_IMR_IMR19_Msk                               
#define EXTI_IMR_IMR20_Pos                         (20U)
#define EXTI_IMR_IMR20_Msk                         (0x1UL<<EXTI_IMR_IMR20_Pos)                      /*!< 0x00100000 */
#define EXTI_IMR_IMR20                             EXTI_IMR_IMR20_Msk                               
#define EXTI_IMR_IMR21_Pos                         (21U)
#define EXTI_IMR_IMR21_Msk                         (0x1UL<<EXTI_IMR_IMR21_Pos)                      /*!< 0x00200000 */
#define EXTI_IMR_IMR21                             EXTI_IMR_IMR21_Msk                               
#define EXTI_IMR_IMR22_Pos                         (22U)
#define EXTI_IMR_IMR22_Msk                         (0x1UL<<EXTI_IMR_IMR22_Pos)                      /*!< 0x00400000 */
#define EXTI_IMR_IMR22                             EXTI_IMR_IMR22_Msk                               
#define EXTI_IMR_IMR23_Pos                         (23U)
#define EXTI_IMR_IMR23_Msk                         (0x1UL<<EXTI_IMR_IMR23_Pos)                      /*!< 0x00800000 */
#define EXTI_IMR_IMR23                             EXTI_IMR_IMR23_Msk                               

/********************************* Bit definition for EXTI_EMR register *********************************************/
#define EXTI_EMR_EMR0_Pos                          (0U)
#define EXTI_EMR_EMR0_Msk                          (0x1UL<<EXTI_EMR_EMR0_Pos)                       /*!< 0x00000001 */
#define EXTI_EMR_EMR0                              EXTI_EMR_EMR0_Msk                                
#define EXTI_EMR_EMR1_Pos                          (1U)
#define EXTI_EMR_EMR1_Msk                          (0x1UL<<EXTI_EMR_EMR1_Pos)                       /*!< 0x00000002 */
#define EXTI_EMR_EMR1                              EXTI_EMR_EMR1_Msk                                
#define EXTI_EMR_EMR2_Pos                          (2U)
#define EXTI_EMR_EMR2_Msk                          (0x1UL<<EXTI_EMR_EMR2_Pos)                       /*!< 0x00000004 */
#define EXTI_EMR_EMR2                              EXTI_EMR_EMR2_Msk                                
#define EXTI_EMR_EMR3_Pos                          (3U)
#define EXTI_EMR_EMR3_Msk                          (0x1UL<<EXTI_EMR_EMR3_Pos)                       /*!< 0x00000008 */
#define EXTI_EMR_EMR3                              EXTI_EMR_EMR3_Msk                                
#define EXTI_EMR_EMR4_Pos                          (4U)
#define EXTI_EMR_EMR4_Msk                          (0x1UL<<EXTI_EMR_EMR4_Pos)                       /*!< 0x00000010 */
#define EXTI_EMR_EMR4                              EXTI_EMR_EMR4_Msk                                
#define EXTI_EMR_EMR5_Pos                          (5U)
#define EXTI_EMR_EMR5_Msk                          (0x1UL<<EXTI_EMR_EMR5_Pos)                       /*!< 0x00000020 */
#define EXTI_EMR_EMR5                              EXTI_EMR_EMR5_Msk                                
#define EXTI_EMR_EMR6_Pos                          (6U)
#define EXTI_EMR_EMR6_Msk                          (0x1UL<<EXTI_EMR_EMR6_Pos)                       /*!< 0x00000040 */
#define EXTI_EMR_EMR6                              EXTI_EMR_EMR6_Msk                                
#define EXTI_EMR_EMR7_Pos                          (7U)
#define EXTI_EMR_EMR7_Msk                          (0x1UL<<EXTI_EMR_EMR7_Pos)                       /*!< 0x00000080 */
#define EXTI_EMR_EMR7                              EXTI_EMR_EMR7_Msk                                
#define EXTI_EMR_EMR8_Pos                          (8U)
#define EXTI_EMR_EMR8_Msk                          (0x1UL<<EXTI_EMR_EMR8_Pos)                       /*!< 0x00000100 */
#define EXTI_EMR_EMR8                              EXTI_EMR_EMR8_Msk                                
#define EXTI_EMR_EMR9_Pos                          (9U)
#define EXTI_EMR_EMR9_Msk                          (0x1UL<<EXTI_EMR_EMR9_Pos)                       /*!< 0x00000200 */
#define EXTI_EMR_EMR9                              EXTI_EMR_EMR9_Msk                                
#define EXTI_EMR_EMR10_Pos                         (10U)
#define EXTI_EMR_EMR10_Msk                         (0x1UL<<EXTI_EMR_EMR10_Pos)                      /*!< 0x00000400 */
#define EXTI_EMR_EMR10                             EXTI_EMR_EMR10_Msk                               
#define EXTI_EMR_EMR11_Pos                         (11U)
#define EXTI_EMR_EMR11_Msk                         (0x1UL<<EXTI_EMR_EMR11_Pos)                      /*!< 0x00000800 */
#define EXTI_EMR_EMR11                             EXTI_EMR_EMR11_Msk                               
#define EXTI_EMR_EMR12_Pos                         (12U)
#define EXTI_EMR_EMR12_Msk                         (0x1UL<<EXTI_EMR_EMR12_Pos)                      /*!< 0x00001000 */
#define EXTI_EMR_EMR12                             EXTI_EMR_EMR12_Msk                               
#define EXTI_EMR_EMR13_Pos                         (13U)
#define EXTI_EMR_EMR13_Msk                         (0x1UL<<EXTI_EMR_EMR13_Pos)                      /*!< 0x00002000 */
#define EXTI_EMR_EMR13                             EXTI_EMR_EMR13_Msk                               
#define EXTI_EMR_EMR14_Pos                         (14U)
#define EXTI_EMR_EMR14_Msk                         (0x1UL<<EXTI_EMR_EMR14_Pos)                      /*!< 0x00004000 */
#define EXTI_EMR_EMR14                             EXTI_EMR_EMR14_Msk                               
#define EXTI_EMR_EMR15_Pos                         (15U)
#define EXTI_EMR_EMR15_Msk                         (0x1UL<<EXTI_EMR_EMR15_Pos)                      /*!< 0x00008000 */
#define EXTI_EMR_EMR15                             EXTI_EMR_EMR15_Msk                               
#define EXTI_EMR_EMR16_Pos                         (16U)
#define EXTI_EMR_EMR16_Msk                         (0x1UL<<EXTI_EMR_EMR16_Pos)                      /*!< 0x00010000 */
#define EXTI_EMR_EMR16                             EXTI_EMR_EMR16_Msk                               
#define EXTI_EMR_EMR17_Pos                         (17U)
#define EXTI_EMR_EMR17_Msk                         (0x1UL<<EXTI_EMR_EMR17_Pos)                      /*!< 0x00020000 */
#define EXTI_EMR_EMR17                             EXTI_EMR_EMR17_Msk                               
#define EXTI_EMR_EMR18_Pos                         (18U)
#define EXTI_EMR_EMR18_Msk                         (0x1UL<<EXTI_EMR_EMR18_Pos)                      /*!< 0x00040000 */
#define EXTI_EMR_EMR18                             EXTI_EMR_EMR18_Msk                               
#define EXTI_EMR_EMR19_Pos                         (19U)
#define EXTI_EMR_EMR19_Msk                         (0x1UL<<EXTI_EMR_EMR19_Pos)                      /*!< 0x00080000 */
#define EXTI_EMR_EMR19                             EXTI_EMR_EMR19_Msk                               
#define EXTI_EMR_EMR20_Pos                         (20U)
#define EXTI_EMR_EMR20_Msk                         (0x1UL<<EXTI_EMR_EMR20_Pos)                      /*!< 0x00100000 */
#define EXTI_EMR_EMR20                             EXTI_EMR_EMR20_Msk                               
#define EXTI_EMR_EMR21_Pos                         (21U)
#define EXTI_EMR_EMR21_Msk                         (0x1UL<<EXTI_EMR_EMR21_Pos)                      /*!< 0x00200000 */
#define EXTI_EMR_EMR21                             EXTI_EMR_EMR21_Msk                               
#define EXTI_EMR_EMR22_Pos                         (22U)
#define EXTI_EMR_EMR22_Msk                         (0x1UL<<EXTI_EMR_EMR22_Pos)                      /*!< 0x00400000 */
#define EXTI_EMR_EMR22                             EXTI_EMR_EMR22_Msk                               
#define EXTI_EMR_EMR23_Pos                         (23U)
#define EXTI_EMR_EMR23_Msk                         (0x1UL<<EXTI_EMR_EMR23_Pos)                      /*!< 0x00800000 */
#define EXTI_EMR_EMR23                             EXTI_EMR_EMR23_Msk                               

/********************************* Bit definition for EXTI_RTSR register ********************************************/
#define EXTI_RTSR_RTSR0_Pos                       (0U)
#define EXTI_RTSR_RTSR0_Msk                       (0x1UL<<EXTI_RTSR_RTSR0_Pos)                      /*!< 0x00000001 */
#define EXTI_RTSR_RTSR0                           EXTI_RTSR_RTSR0_Msk                               
#define EXTI_RTSR_RTSR1_Pos                       (1U)
#define EXTI_RTSR_RTSR1_Msk                       (0x1UL<<EXTI_RTSR_RTSR1_Pos)                      /*!< 0x00000002 */
#define EXTI_RTSR_RTSR1                           EXTI_RTSR_RTSR1_Msk                               
#define EXTI_RTSR_RTSR2_Pos                       (2U)
#define EXTI_RTSR_RTSR2_Msk                       (0x1UL<<EXTI_RTSR_RTSR2_Pos)                      /*!< 0x00000004 */
#define EXTI_RTSR_RTSR2                           EXTI_RTSR_RTSR2_Msk                               
#define EXTI_RTSR_RTSR3_Pos                       (3U)
#define EXTI_RTSR_RTSR3_Msk                       (0x1UL<<EXTI_RTSR_RTSR3_Pos)                      /*!< 0x00000008 */
#define EXTI_RTSR_RTSR3                           EXTI_RTSR_RTSR3_Msk                               
#define EXTI_RTSR_RTSR4_Pos                       (4U)
#define EXTI_RTSR_RTSR4_Msk                       (0x1UL<<EXTI_RTSR_RTSR4_Pos)                      /*!< 0x00000010 */
#define EXTI_RTSR_RTSR4                           EXTI_RTSR_RTSR4_Msk                               
#define EXTI_RTSR_RTSR5_Pos                       (5U)
#define EXTI_RTSR_RTSR5_Msk                       (0x1UL<<EXTI_RTSR_RTSR5_Pos)                      /*!< 0x00000020 */
#define EXTI_RTSR_RTSR5                           EXTI_RTSR_RTSR5_Msk                               
#define EXTI_RTSR_RTSR6_Pos                       (6U)
#define EXTI_RTSR_RTSR6_Msk                       (0x1UL<<EXTI_RTSR_RTSR6_Pos)                      /*!< 0x00000040 */
#define EXTI_RTSR_RTSR6                           EXTI_RTSR_RTSR6_Msk                               
#define EXTI_RTSR_RTSR7_Pos                       (7U)
#define EXTI_RTSR_RTSR7_Msk                       (0x1UL<<EXTI_RTSR_RTSR7_Pos)                      /*!< 0x00000080 */
#define EXTI_RTSR_RTSR7                           EXTI_RTSR_RTSR7_Msk                               
#define EXTI_RTSR_RTSR8_Pos                       (8U)
#define EXTI_RTSR_RTSR8_Msk                       (0x1UL<<EXTI_RTSR_RTSR8_Pos)                      /*!< 0x00000100 */
#define EXTI_RTSR_RTSR8                           EXTI_RTSR_RTSR8_Msk                               
#define EXTI_RTSR_RTSR9_Pos                       (9U)
#define EXTI_RTSR_RTSR9_Msk                       (0x1UL<<EXTI_RTSR_RTSR9_Pos)                      /*!< 0x00000200 */
#define EXTI_RTSR_RTSR9                           EXTI_RTSR_RTSR9_Msk                               
#define EXTI_RTSR_RTSR10_Pos                      (10U)
#define EXTI_RTSR_RTSR10_Msk                      (0x1UL<<EXTI_RTSR_RTSR10_Pos)                     /*!< 0x00000400 */
#define EXTI_RTSR_RTSR10                          EXTI_RTSR_RTSR10_Msk                              
#define EXTI_RTSR_RTSR11_Pos                      (11U)
#define EXTI_RTSR_RTSR11_Msk                      (0x1UL<<EXTI_RTSR_RTSR11_Pos)                     /*!< 0x00000800 */
#define EXTI_RTSR_RTSR11                          EXTI_RTSR_RTSR11_Msk                              
#define EXTI_RTSR_RTSR12_Pos                      (12U)
#define EXTI_RTSR_RTSR12_Msk                      (0x1UL<<EXTI_RTSR_RTSR12_Pos)                     /*!< 0x00001000 */
#define EXTI_RTSR_RTSR12                          EXTI_RTSR_RTSR12_Msk                              
#define EXTI_RTSR_RTSR13_Pos                      (13U)
#define EXTI_RTSR_RTSR13_Msk                      (0x1UL<<EXTI_RTSR_RTSR13_Pos)                     /*!< 0x00002000 */
#define EXTI_RTSR_RTSR13                          EXTI_RTSR_RTSR13_Msk                              
#define EXTI_RTSR_RTSR14_Pos                      (14U)
#define EXTI_RTSR_RTSR14_Msk                      (0x1UL<<EXTI_RTSR_RTSR14_Pos)                     /*!< 0x00004000 */
#define EXTI_RTSR_RTSR14                          EXTI_RTSR_RTSR14_Msk                              
#define EXTI_RTSR_RTSR15_Pos                      (15U)
#define EXTI_RTSR_RTSR15_Msk                      (0x1UL<<EXTI_RTSR_RTSR15_Pos)                     /*!< 0x00008000 */
#define EXTI_RTSR_RTSR15                          EXTI_RTSR_RTSR15_Msk                              
#define EXTI_RTSR_RTSR16_Pos                      (16U)
#define EXTI_RTSR_RTSR16_Msk                      (0x1UL<<EXTI_RTSR_RTSR16_Pos)                     /*!< 0x00010000 */
#define EXTI_RTSR_RTSR16                          EXTI_RTSR_RTSR16_Msk                              
#define EXTI_RTSR_RTSR17_Pos                      (17U)
#define EXTI_RTSR_RTSR17_Msk                      (0x1UL<<EXTI_RTSR_RTSR17_Pos)                     /*!< 0x00020000 */
#define EXTI_RTSR_RTSR17                          EXTI_RTSR_RTSR17_Msk                              
#define EXTI_RTSR_RTSR18_Pos                      (18U)
#define EXTI_RTSR_RTSR18_Msk                      (0x1UL<<EXTI_RTSR_RTSR18_Pos)                     /*!< 0x00040000 */
#define EXTI_RTSR_RTSR18                          EXTI_RTSR_RTSR18_Msk                              
#define EXTI_RTSR_RTSR19_Pos                      (19U)
#define EXTI_RTSR_RTSR19_Msk                      (0x1UL<<EXTI_RTSR_RTSR19_Pos)                     /*!< 0x00080000 */
#define EXTI_RTSR_RTSR19                          EXTI_RTSR_RTSR19_Msk                              

/********************************* Bit definition for EXTI_FTSR register ********************************************/
#define EXTI_FTSR_FTSR0_Pos                       (0U)
#define EXTI_FTSR_FTSR0_Msk                       (0x1UL<<EXTI_FTSR_FTSR0_Pos)                      /*!< 0x00000001 */
#define EXTI_FTSR_FTSR0                           EXTI_FTSR_FTSR0_Msk                               
#define EXTI_FTSR_FTSR1_Pos                       (1U)
#define EXTI_FTSR_FTSR1_Msk                       (0x1UL<<EXTI_FTSR_FTSR1_Pos)                      /*!< 0x00000002 */
#define EXTI_FTSR_FTSR1                           EXTI_FTSR_FTSR1_Msk                               
#define EXTI_FTSR_FTSR2_Pos                       (2U)
#define EXTI_FTSR_FTSR2_Msk                       (0x1UL<<EXTI_FTSR_FTSR2_Pos)                      /*!< 0x00000004 */
#define EXTI_FTSR_FTSR2                           EXTI_FTSR_FTSR2_Msk                               
#define EXTI_FTSR_FTSR3_Pos                       (3U)
#define EXTI_FTSR_FTSR3_Msk                       (0x1UL<<EXTI_FTSR_FTSR3_Pos)                      /*!< 0x00000008 */
#define EXTI_FTSR_FTSR3                           EXTI_FTSR_FTSR3_Msk                               
#define EXTI_FTSR_FTSR4_Pos                       (4U)
#define EXTI_FTSR_FTSR4_Msk                       (0x1UL<<EXTI_FTSR_FTSR4_Pos)                      /*!< 0x00000010 */
#define EXTI_FTSR_FTSR4                           EXTI_FTSR_FTSR4_Msk                               
#define EXTI_FTSR_FTSR5_Pos                       (5U)
#define EXTI_FTSR_FTSR5_Msk                       (0x1UL<<EXTI_FTSR_FTSR5_Pos)                      /*!< 0x00000020 */
#define EXTI_FTSR_FTSR5                           EXTI_FTSR_FTSR5_Msk                               
#define EXTI_FTSR_FTSR6_Pos                       (6U)
#define EXTI_FTSR_FTSR6_Msk                       (0x1UL<<EXTI_FTSR_FTSR6_Pos)                      /*!< 0x00000040 */
#define EXTI_FTSR_FTSR6                           EXTI_FTSR_FTSR6_Msk                               
#define EXTI_FTSR_FTSR7_Pos                       (7U)
#define EXTI_FTSR_FTSR7_Msk                       (0x1UL<<EXTI_FTSR_FTSR7_Pos)                      /*!< 0x00000080 */
#define EXTI_FTSR_FTSR7                           EXTI_FTSR_FTSR7_Msk                               
#define EXTI_FTSR_FTSR8_Pos                       (8U)
#define EXTI_FTSR_FTSR8_Msk                       (0x1UL<<EXTI_FTSR_FTSR8_Pos)                      /*!< 0x00000100 */
#define EXTI_FTSR_FTSR8                           EXTI_FTSR_FTSR8_Msk                               
#define EXTI_FTSR_FTSR9_Pos                       (9U)
#define EXTI_FTSR_FTSR9_Msk                       (0x1UL<<EXTI_FTSR_FTSR9_Pos)                      /*!< 0x00000200 */
#define EXTI_FTSR_FTSR9                           EXTI_FTSR_FTSR9_Msk                               
#define EXTI_FTSR_FTSR10_Pos                      (10U)
#define EXTI_FTSR_FTSR10_Msk                      (0x1UL<<EXTI_FTSR_FTSR10_Pos)                     /*!< 0x00000400 */
#define EXTI_FTSR_FTSR10                          EXTI_FTSR_FTSR10_Msk                              
#define EXTI_FTSR_FTSR11_Pos                      (11U)
#define EXTI_FTSR_FTSR11_Msk                      (0x1UL<<EXTI_FTSR_FTSR11_Pos)                     /*!< 0x00000800 */
#define EXTI_FTSR_FTSR11                          EXTI_FTSR_FTSR11_Msk                              
#define EXTI_FTSR_FTSR12_Pos                      (12U)
#define EXTI_FTSR_FTSR12_Msk                      (0x1UL<<EXTI_FTSR_FTSR12_Pos)                     /*!< 0x00001000 */
#define EXTI_FTSR_FTSR12                          EXTI_FTSR_FTSR12_Msk                              
#define EXTI_FTSR_FTSR13_Pos                      (13U)
#define EXTI_FTSR_FTSR13_Msk                      (0x1UL<<EXTI_FTSR_FTSR13_Pos)                     /*!< 0x00002000 */
#define EXTI_FTSR_FTSR13                          EXTI_FTSR_FTSR13_Msk                              
#define EXTI_FTSR_FTSR14_Pos                      (14U)
#define EXTI_FTSR_FTSR14_Msk                      (0x1UL<<EXTI_FTSR_FTSR14_Pos)                     /*!< 0x00004000 */
#define EXTI_FTSR_FTSR14                          EXTI_FTSR_FTSR14_Msk                              
#define EXTI_FTSR_FTSR15_Pos                      (15U)
#define EXTI_FTSR_FTSR15_Msk                      (0x1UL<<EXTI_FTSR_FTSR15_Pos)                     /*!< 0x00008000 */
#define EXTI_FTSR_FTSR15                          EXTI_FTSR_FTSR15_Msk                              
#define EXTI_FTSR_FTSR16_Pos                      (16U)
#define EXTI_FTSR_FTSR16_Msk                      (0x1UL<<EXTI_FTSR_FTSR16_Pos)                     /*!< 0x00010000 */
#define EXTI_FTSR_FTSR16                          EXTI_FTSR_FTSR16_Msk                              
#define EXTI_FTSR_FTSR17_Pos                      (17U)
#define EXTI_FTSR_FTSR17_Msk                      (0x1UL<<EXTI_FTSR_FTSR17_Pos)                     /*!< 0x00020000 */
#define EXTI_FTSR_FTSR17                          EXTI_FTSR_FTSR17_Msk                              
#define EXTI_FTSR_FTSR18_Pos                      (18U)
#define EXTI_FTSR_FTSR18_Msk                      (0x1UL<<EXTI_FTSR_FTSR18_Pos)                     /*!< 0x00040000 */
#define EXTI_FTSR_FTSR18                          EXTI_FTSR_FTSR18_Msk                              
#define EXTI_FTSR_FTSR19_Pos                      (19U)
#define EXTI_FTSR_FTSR19_Msk                      (0x1UL<<EXTI_FTSR_FTSR19_Pos)                     /*!< 0x00080000 */
#define EXTI_FTSR_FTSR19                          EXTI_FTSR_FTSR19_Msk                              

/********************************* Bit definition for EXTI_SWIER register *******************************************/
#define EXTI_SWIER_SWIER0_Pos                     (0U)
#define EXTI_SWIER_SWIER0_Msk                     (0x1UL<<EXTI_SWIER_SWIER0_Pos)                    /*!< 0x00000001 */
#define EXTI_SWIER_SWIER0                         EXTI_SWIER_SWIER0_Msk                             
#define EXTI_SWIER_SWIER1_Pos                     (1U)
#define EXTI_SWIER_SWIER1_Msk                     (0x1UL<<EXTI_SWIER_SWIER1_Pos)                    /*!< 0x00000002 */
#define EXTI_SWIER_SWIER1                         EXTI_SWIER_SWIER1_Msk                             
#define EXTI_SWIER_SWIER2_Pos                     (2U)
#define EXTI_SWIER_SWIER2_Msk                     (0x1UL<<EXTI_SWIER_SWIER2_Pos)                    /*!< 0x00000004 */
#define EXTI_SWIER_SWIER2                         EXTI_SWIER_SWIER2_Msk                             
#define EXTI_SWIER_SWIER3_Pos                     (3U)
#define EXTI_SWIER_SWIER3_Msk                     (0x1UL<<EXTI_SWIER_SWIER3_Pos)                    /*!< 0x00000008 */
#define EXTI_SWIER_SWIER3                         EXTI_SWIER_SWIER3_Msk                             
#define EXTI_SWIER_SWIER4_Pos                     (4U)
#define EXTI_SWIER_SWIER4_Msk                     (0x1UL<<EXTI_SWIER_SWIER4_Pos)                    /*!< 0x00000010 */
#define EXTI_SWIER_SWIER4                         EXTI_SWIER_SWIER4_Msk                             
#define EXTI_SWIER_SWIER5_Pos                     (5U)
#define EXTI_SWIER_SWIER5_Msk                     (0x1UL<<EXTI_SWIER_SWIER5_Pos)                    /*!< 0x00000020 */
#define EXTI_SWIER_SWIER5                         EXTI_SWIER_SWIER5_Msk                             
#define EXTI_SWIER_SWIER6_Pos                     (6U)
#define EXTI_SWIER_SWIER6_Msk                     (0x1UL<<EXTI_SWIER_SWIER6_Pos)                    /*!< 0x00000040 */
#define EXTI_SWIER_SWIER6                         EXTI_SWIER_SWIER6_Msk                             
#define EXTI_SWIER_SWIER7_Pos                     (7U)
#define EXTI_SWIER_SWIER7_Msk                     (0x1UL<<EXTI_SWIER_SWIER7_Pos)                    /*!< 0x00000080 */
#define EXTI_SWIER_SWIER7                         EXTI_SWIER_SWIER7_Msk                             
#define EXTI_SWIER_SWIER8_Pos                     (8U)
#define EXTI_SWIER_SWIER8_Msk                     (0x1UL<<EXTI_SWIER_SWIER8_Pos)                    /*!< 0x00000100 */
#define EXTI_SWIER_SWIER8                         EXTI_SWIER_SWIER8_Msk                             
#define EXTI_SWIER_SWIER9_Pos                     (9U)
#define EXTI_SWIER_SWIER9_Msk                     (0x1UL<<EXTI_SWIER_SWIER9_Pos)                    /*!< 0x00000200 */
#define EXTI_SWIER_SWIER9                         EXTI_SWIER_SWIER9_Msk                             
#define EXTI_SWIER_SWIER10_Pos                    (10U)
#define EXTI_SWIER_SWIER10_Msk                    (0x1UL<<EXTI_SWIER_SWIER10_Pos)                   /*!< 0x00000400 */
#define EXTI_SWIER_SWIER10                        EXTI_SWIER_SWIER10_Msk                            
#define EXTI_SWIER_SWIER11_Pos                    (11U)
#define EXTI_SWIER_SWIER11_Msk                    (0x1UL<<EXTI_SWIER_SWIER11_Pos)                   /*!< 0x00000800 */
#define EXTI_SWIER_SWIER11                        EXTI_SWIER_SWIER11_Msk                            
#define EXTI_SWIER_SWIER12_Pos                    (12U)
#define EXTI_SWIER_SWIER12_Msk                    (0x1UL<<EXTI_SWIER_SWIER12_Pos)                   /*!< 0x00001000 */
#define EXTI_SWIER_SWIER12                        EXTI_SWIER_SWIER12_Msk                            
#define EXTI_SWIER_SWIER13_Pos                    (13U)
#define EXTI_SWIER_SWIER13_Msk                    (0x1UL<<EXTI_SWIER_SWIER13_Pos)                   /*!< 0x00002000 */
#define EXTI_SWIER_SWIER13                        EXTI_SWIER_SWIER13_Msk                            
#define EXTI_SWIER_SWIER14_Pos                    (14U)
#define EXTI_SWIER_SWIER14_Msk                    (0x1UL<<EXTI_SWIER_SWIER14_Pos)                   /*!< 0x00004000 */
#define EXTI_SWIER_SWIER14                        EXTI_SWIER_SWIER14_Msk                            
#define EXTI_SWIER_SWIER15_Pos                    (15U)
#define EXTI_SWIER_SWIER15_Msk                    (0x1UL<<EXTI_SWIER_SWIER15_Pos)                   /*!< 0x00008000 */
#define EXTI_SWIER_SWIER15                        EXTI_SWIER_SWIER15_Msk                            
#define EXTI_SWIER_SWIER16_Pos                    (16U)
#define EXTI_SWIER_SWIER16_Msk                    (0x1UL<<EXTI_SWIER_SWIER16_Pos)                   /*!< 0x00010000 */
#define EXTI_SWIER_SWIER16                        EXTI_SWIER_SWIER16_Msk                            
#define EXTI_SWIER_SWIER17_Pos                    (17U)
#define EXTI_SWIER_SWIER17_Msk                    (0x1UL<<EXTI_SWIER_SWIER17_Pos)                   /*!< 0x00020000 */
#define EXTI_SWIER_SWIER17                        EXTI_SWIER_SWIER17_Msk                            
#define EXTI_SWIER_SWIER18_Pos                    (18U)
#define EXTI_SWIER_SWIER18_Msk                    (0x1UL<<EXTI_SWIER_SWIER18_Pos)                   /*!< 0x00040000 */
#define EXTI_SWIER_SWIER18                        EXTI_SWIER_SWIER18_Msk                            
#define EXTI_SWIER_SWIER19_Pos                    (19U)
#define EXTI_SWIER_SWIER19_Msk                    (0x1UL<<EXTI_SWIER_SWIER19_Pos)                   /*!< 0x00080000 */
#define EXTI_SWIER_SWIER19                        EXTI_SWIER_SWIER19_Msk                            

/********************************* Bit definition for EXTI_PR register **********************************************/
#define EXTI_PR_PR0_Pos                           (0U)
#define EXTI_PR_PR0_Msk                           (0x1UL<<EXTI_PR_PR0_Pos)                          /*!< 0x00000001 */
#define EXTI_PR_PR0                               EXTI_PR_PR0_Msk                                   
#define EXTI_PR_PR1_Pos                           (1U)
#define EXTI_PR_PR1_Msk                           (0x1UL<<EXTI_PR_PR1_Pos)                          /*!< 0x00000002 */
#define EXTI_PR_PR1                               EXTI_PR_PR1_Msk                                   
#define EXTI_PR_PR2_Pos                           (2U)
#define EXTI_PR_PR2_Msk                           (0x1UL<<EXTI_PR_PR2_Pos)                          /*!< 0x00000004 */
#define EXTI_PR_PR2                               EXTI_PR_PR2_Msk                                   
#define EXTI_PR_PR3_Pos                           (3U)
#define EXTI_PR_PR3_Msk                           (0x1UL<<EXTI_PR_PR3_Pos)                          /*!< 0x00000008 */
#define EXTI_PR_PR3                               EXTI_PR_PR3_Msk                                   
#define EXTI_PR_PR4_Pos                           (4U)
#define EXTI_PR_PR4_Msk                           (0x1UL<<EXTI_PR_PR4_Pos)                          /*!< 0x00000010 */
#define EXTI_PR_PR4                               EXTI_PR_PR4_Msk                                   
#define EXTI_PR_PR5_Pos                           (5U)
#define EXTI_PR_PR5_Msk                           (0x1UL<<EXTI_PR_PR5_Pos)                          /*!< 0x00000020 */
#define EXTI_PR_PR5                               EXTI_PR_PR5_Msk                                   
#define EXTI_PR_PR6_Pos                           (6U)
#define EXTI_PR_PR6_Msk                           (0x1UL<<EXTI_PR_PR6_Pos)                          /*!< 0x00000040 */
#define EXTI_PR_PR6                               EXTI_PR_PR6_Msk                                   
#define EXTI_PR_PR7_Pos                           (7U)
#define EXTI_PR_PR7_Msk                           (0x1UL<<EXTI_PR_PR7_Pos)                          /*!< 0x00000080 */
#define EXTI_PR_PR7                               EXTI_PR_PR7_Msk                                   
#define EXTI_PR_PR8_Pos                           (8U)
#define EXTI_PR_PR8_Msk                           (0x1UL<<EXTI_PR_PR8_Pos)                          /*!< 0x00000100 */
#define EXTI_PR_PR8                               EXTI_PR_PR8_Msk                                   
#define EXTI_PR_PR9_Pos                           (9U)
#define EXTI_PR_PR9_Msk                           (0x1UL<<EXTI_PR_PR9_Pos)                          /*!< 0x00000200 */
#define EXTI_PR_PR9                               EXTI_PR_PR9_Msk                                   
#define EXTI_PR_PR10_Pos                          (10U)
#define EXTI_PR_PR10_Msk                          (0x1UL<<EXTI_PR_PR10_Pos)                         /*!< 0x00000400 */
#define EXTI_PR_PR10                              EXTI_PR_PR10_Msk                                  
#define EXTI_PR_PR11_Pos                          (11U)
#define EXTI_PR_PR11_Msk                          (0x1UL<<EXTI_PR_PR11_Pos)                         /*!< 0x00000800 */
#define EXTI_PR_PR11                              EXTI_PR_PR11_Msk                                  
#define EXTI_PR_PR12_Pos                          (12U)
#define EXTI_PR_PR12_Msk                          (0x1UL<<EXTI_PR_PR12_Pos)                         /*!< 0x00001000 */
#define EXTI_PR_PR12                              EXTI_PR_PR12_Msk                                  
#define EXTI_PR_PR13_Pos                          (13U)
#define EXTI_PR_PR13_Msk                          (0x1UL<<EXTI_PR_PR13_Pos)                         /*!< 0x00002000 */
#define EXTI_PR_PR13                              EXTI_PR_PR13_Msk                                  
#define EXTI_PR_PR14_Pos                          (14U)
#define EXTI_PR_PR14_Msk                          (0x1UL<<EXTI_PR_PR14_Pos)                         /*!< 0x00004000 */
#define EXTI_PR_PR14                              EXTI_PR_PR14_Msk                                  
#define EXTI_PR_PR15_Pos                          (15U)
#define EXTI_PR_PR15_Msk                          (0x1UL<<EXTI_PR_PR15_Pos)                         /*!< 0x00008000 */
#define EXTI_PR_PR15                              EXTI_PR_PR15_Msk                                  
#define EXTI_PR_PR16_Pos                          (16U)
#define EXTI_PR_PR16_Msk                          (0x1UL<<EXTI_PR_PR16_Pos)                         /*!< 0x00010000 */
#define EXTI_PR_PR16                              EXTI_PR_PR16_Msk                                  
#define EXTI_PR_PR17_Pos                          (17U)
#define EXTI_PR_PR17_Msk                          (0x1UL<<EXTI_PR_PR17_Pos)                         /*!< 0x00020000 */
#define EXTI_PR_PR17                              EXTI_PR_PR17_Msk                                  
#define EXTI_PR_PR18_Pos                          (18U)
#define EXTI_PR_PR18_Msk                          (0x1UL<<EXTI_PR_PR18_Pos)                         /*!< 0x00040000 */
#define EXTI_PR_PR18                              EXTI_PR_PR18_Msk                                  
#define EXTI_PR_PR19_Pos                          (19U)
#define EXTI_PR_PR19_Msk                          (0x1UL<<EXTI_PR_PR19_Pos)                         /*!< 0x00080000 */
#define EXTI_PR_PR19                              EXTI_PR_PR19_Msk                                  

/********************************************************************************************************************/
/********************************* FLASH ****************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for FLASH_ACR register ********************************************/
#define FLASH_ACR_LATENCY_Pos                     (0U)
#define FLASH_ACR_LATENCY_Msk                     (0xFUL<<FLASH_ACR_LATENCY_Pos)                    /*!< 0x0000000F */
#define FLASH_ACR_LATENCY                         FLASH_ACR_LATENCY_Msk                             /*!< Latency */
#define FLASH_ACR_LATENCY_0                       (0x1UL<<FLASH_ACR_LATENCY_Pos)                    /*!< 0x00000001 */
#define FLASH_ACR_LATENCY_1                       (0x2UL<<FLASH_ACR_LATENCY_Pos)                    /*!< 0x00000002 */
#define FLASH_ACR_LATENCY_2                       (0x4UL<<FLASH_ACR_LATENCY_Pos)                    /*!< 0x00000004 */
#define FLASH_ACR_LATENCY_3                       (0x8UL<<FLASH_ACR_LATENCY_Pos)                    /*!< 0x00000008 */
#define FLASH_ACR_PRFTEN_Pos                      (8U)
#define FLASH_ACR_PRFTEN_Msk                      (0x1UL<<FLASH_ACR_PRFTEN_Pos)                     /*!< 0x00000100 */
#define FLASH_ACR_PRFTEN                          FLASH_ACR_PRFTEN_Msk                              
#define FLASH_ACR_ICEN_Pos                        (9U)
#define FLASH_ACR_ICEN_Msk                        (0x1UL<<FLASH_ACR_ICEN_Pos)                       /*!< 0x00000200 */
#define FLASH_ACR_ICEN                            FLASH_ACR_ICEN_Msk                                
#define FLASH_ACR_DCEN_Pos                        (10U)
#define FLASH_ACR_DCEN_Msk                        (0x1UL<<FLASH_ACR_DCEN_Pos)                       /*!< 0x00000400 */
#define FLASH_ACR_DCEN                            FLASH_ACR_DCEN_Msk                                

/********************************* Bit definition for FLASH_KEYR register *******************************************/
#define FLASH_KEYR_KEY_Pos                        (0U)
#define FLASH_KEYR_KEY_Msk                        (0xFFFFFFFFUL<<FLASH_KEYR_KEY_Pos)                /*!< 0xFFFFFFFF */
#define FLASH_KEYR_KEY                            FLASH_KEYR_KEY_Msk                                /*!< Flash CR key */

/********************************* Bit definition for FLASH_OPTKEYR register ****************************************/
#define FLASH_OPTKEYR_OPTKEY_Pos                  (0U)
#define FLASH_OPTKEYR_OPTKEY_Msk                  (0xFFFFFFFFUL<<FLASH_OPTKEYR_OPTKEY_Pos)          /*!< 0xFFFFFFFF */
#define FLASH_OPTKEYR_OPTKEY                      FLASH_OPTKEYR_OPTKEY_Msk                          /*!< Flash Option key */

/********************************* Bit definition for FLASH_SR register *********************************************/
#define FLASH_SR_EOP_Pos                          (0U)
#define FLASH_SR_EOP_Msk                          (0x1UL<<FLASH_SR_EOP_Pos)                         /*!< 0x00000001 */
#define FLASH_SR_EOP                              FLASH_SR_EOP_Msk                                  /*!< End of operation */
#define FLASH_SR_WRPERR_Pos                       (4U)
#define FLASH_SR_WRPERR_Msk                       (0x1UL<<FLASH_SR_WRPERR_Pos)                      /*!< 0x00000010 */
#define FLASH_SR_WRPERR                           FLASH_SR_WRPERR_Msk                               /*!< Write protection error */
#define FLASH_SR_RDERR_Pos                        (14U)
#define FLASH_SR_RDERR_Msk                        (0x1UL<<FLASH_SR_RDERR_Pos)                       /*!< 0x00004000 */
#define FLASH_SR_RDERR                            FLASH_SR_RDERR_Msk                                
#define FLASH_SR_OPTVERR_Pos                      (15U)
#define FLASH_SR_OPTVERR_Msk                      (0x1UL<<FLASH_SR_OPTVERR_Pos)                     /*!< 0x00008000 */
#define FLASH_SR_OPTVERR                          FLASH_SR_OPTVERR_Msk                              /*!< Option and trimming bits loading validity error */
#define FLASH_SR_BSY0_Pos                         (16U)
#define FLASH_SR_BSY0_Msk                         (0x1UL<<FLASH_SR_BSY0_Pos)                        /*!< 0x00010000 */
#define FLASH_SR_BSY0                             FLASH_SR_BSY0_Msk                                 /*!< Bank0 Busy */
#define FLASH_SR_BSY1_Pos                         (17U)
#define FLASH_SR_BSY1_Msk                         (0x1UL<<FLASH_SR_BSY1_Pos)                        /*!< 0x00020000 */
#define FLASH_SR_BSY1                             FLASH_SR_BSY1_Msk                                 /*!< Bank1 Busy */

/********************************* Bit definition for FLASH_CR register *********************************************/
#define FLASH_CR_PG_Pos                           (0U)
#define FLASH_CR_PG_Msk                           (0x1UL<<FLASH_CR_PG_Pos)                          /*!< 0x00000001 */
#define FLASH_CR_PG                               FLASH_CR_PG_Msk                                   /*!< Page Program */
#define FLASH_CR_PER_Pos                          (1U)
#define FLASH_CR_PER_Msk                          (0x1UL<<FLASH_CR_PER_Pos)                         /*!< 0x00000002 */
#define FLASH_CR_PER                              FLASH_CR_PER_Msk                                  /*!< Page Erase */
#define FLASH_CR_MER0_Pos                         (2U)
#define FLASH_CR_MER0_Msk                         (0x1UL<<FLASH_CR_MER0_Pos)                        /*!< 0x00000004 */
#define FLASH_CR_MER0                             FLASH_CR_MER0_Msk                                 /*!< Bank 0 Mass Erase */
#define FLASH_CR_MER1_Pos                         (3U)
#define FLASH_CR_MER1_Msk                         (0x1UL<<FLASH_CR_MER1_Pos)                        /*!< 0x00000008 */
#define FLASH_CR_MER1                             FLASH_CR_MER1_Msk                                 /*!< Bank 1 Mass Erase */
#define FLASH_CR_SER_Pos                          (11U)
#define FLASH_CR_SER_Msk                          (0x1UL<<FLASH_CR_SER_Pos)                         /*!< 0x00000800 */
#define FLASH_CR_SER                              FLASH_CR_SER_Msk                                  /*!< Sector Erase */
#define FLASH_CR_OPTSTRT_Pos                      (17U)
#define FLASH_CR_OPTSTRT_Msk                      (0x1UL<<FLASH_CR_OPTSTRT_Pos)                     /*!< 0x00020000 */
#define FLASH_CR_OPTSTRT                          FLASH_CR_OPTSTRT_Msk                              /*!< Option bytes Programming Start */
#define FLASH_CR_PGSTRT_Pos                       (19U)
#define FLASH_CR_PGSTRT_Msk                       (0x1UL<<FLASH_CR_PGSTRT_Pos)                      /*!< 0x00080000 */
#define FLASH_CR_PGSTRT                           FLASH_CR_PGSTRT_Msk                               /*!< Programming Start */
#define FLASH_CR_EOPIE_Pos                        (24U)
#define FLASH_CR_EOPIE_Msk                        (0x1UL<<FLASH_CR_EOPIE_Pos)                       /*!< 0x01000000 */
#define FLASH_CR_EOPIE                            FLASH_CR_EOPIE_Msk                                /*!< End of operation interrupt enable */
#define FLASH_CR_ERRIE_Pos                        (25U)
#define FLASH_CR_ERRIE_Msk                        (0x1UL<<FLASH_CR_ERRIE_Pos)                       /*!< 0x02000000 */
#define FLASH_CR_ERRIE                            FLASH_CR_ERRIE_Msk                                /*!< Error interrupt enable */
#define FLASH_CR_RDERRIE_Pos                      (26U)
#define FLASH_CR_RDERRIE_Msk                      (0x1UL<<FLASH_CR_RDERRIE_Pos)                     /*!< 0x04000000 */
#define FLASH_CR_RDERRIE                          FLASH_CR_RDERRIE_Msk                              
#define FLASH_CR_OBL_LAUNCH_Pos                   (27U)
#define FLASH_CR_OBL_LAUNCH_Msk                   (0x1UL<<FLASH_CR_OBL_LAUNCH_Pos)                  /*!< 0x08000000 */
#define FLASH_CR_OBL_LAUNCH                       FLASH_CR_OBL_LAUNCH_Msk                           /*!< Force the option bytes loading */
#define FLASH_CR_OPTLOCK_Pos                      (30U)
#define FLASH_CR_OPTLOCK_Msk                      (0x1UL<<FLASH_CR_OPTLOCK_Pos)                     /*!< 0x40000000 */
#define FLASH_CR_OPTLOCK                          FLASH_CR_OPTLOCK_Msk                              /*!< Option Lock */
#define FLASH_CR_LOCK_Pos                         (31U)
#define FLASH_CR_LOCK_Msk                         (0x1UL<<FLASH_CR_LOCK_Pos)                        /*!< 0x80000000 */
#define FLASH_CR_LOCK                             FLASH_CR_LOCK_Msk                                 /*!< Lock */

/********************************* Bit definition for FLASH_OPTR1 register ******************************************/
#define FLASH_OPTR1_RDP_Pos                       (0U)
#define FLASH_OPTR1_RDP_Msk                       (0xFFUL<<FLASH_OPTR1_RDP_Pos)                     /*!< 0x000000FF */
#define FLASH_OPTR1_RDP                           FLASH_OPTR1_RDP_Msk                               /*!< Read Protection */
#define FLASH_OPTR1_IWDG_STOP_Pos                 (9U)
#define FLASH_OPTR1_IWDG_STOP_Msk                 (0x1UL<<FLASH_OPTR1_IWDG_STOP_Pos)                /*!< 0x00000200 */
#define FLASH_OPTR1_IWDG_STOP                     FLASH_OPTR1_IWDG_STOP_Msk                         
#define FLASH_OPTR1_IWDG_STDBY_Pos                (10U)
#define FLASH_OPTR1_IWDG_STDBY_Msk                (0x1UL<<FLASH_OPTR1_IWDG_STDBY_Pos)               /*!< 0x00000400 */
#define FLASH_OPTR1_IWDG_STDBY                    FLASH_OPTR1_IWDG_STDBY_Msk                        
#define FLASH_OPTR1_BFB_Pos                       (11U)
#define FLASH_OPTR1_BFB_Msk                       (0x1UL<<FLASH_OPTR1_BFB_Pos)                      /*!< 0x00000800 */
#define FLASH_OPTR1_BFB                           FLASH_OPTR1_BFB_Msk                               
#define FLASH_OPTR1_IWDG_SW_Pos                   (12U)
#define FLASH_OPTR1_IWDG_SW_Msk                   (0x1UL<<FLASH_OPTR1_IWDG_SW_Pos)                  /*!< 0x00001000 */
#define FLASH_OPTR1_IWDG_SW                       FLASH_OPTR1_IWDG_SW_Msk                           /*!< IWDG Software Enable */
#define FLASH_OPTR1_NRST_STOP_Pos                 (13U)
#define FLASH_OPTR1_NRST_STOP_Msk                 (0x1UL<<FLASH_OPTR1_NRST_STOP_Pos)                /*!< 0x00002000 */
#define FLASH_OPTR1_NRST_STOP                     FLASH_OPTR1_NRST_STOP_Msk                         
#define FLASH_OPTR1_NRST_STDBY_Pos                (14U)
#define FLASH_OPTR1_NRST_STDBY_Msk                (0x1UL<<FLASH_OPTR1_NRST_STDBY_Pos)               /*!< 0x00004000 */
#define FLASH_OPTR1_NRST_STDBY                    FLASH_OPTR1_NRST_STDBY_Msk                        
#define FLASH_OPTR1_WWDG_SW_Pos                   (15U)
#define FLASH_OPTR1_WWDG_SW_Msk                   (0x1UL<<FLASH_OPTR1_WWDG_SW_Pos)                  /*!< 0x00008000 */
#define FLASH_OPTR1_WWDG_SW                       FLASH_OPTR1_WWDG_SW_Msk                           

/********************************* Bit definition for FLASH_OPTR2 register ******************************************/
#define FLASH_OPTR2_ACC_CTRL_Pos                  (5U)
#define FLASH_OPTR2_ACC_CTRL_Msk                  (0x7UL<<FLASH_OPTR2_ACC_CTRL_Pos)                 /*!< 0x000000E0 */
#define FLASH_OPTR2_ACC_CTRL                      FLASH_OPTR2_ACC_CTRL_Msk
#define FLASH_OPTR2_ACC_CTRL_0                    (0x1UL<<FLASH_OPTR2_ACC_CTRL_Pos)                 /*!< 0x00000020 */
#define FLASH_OPTR2_ACC_CTRL_1                    (0x2UL<<FLASH_OPTR2_ACC_CTRL_Pos)                 /*!< 0x00000040 */
#define FLASH_OPTR2_ACC_CTRL_2                    (0x4UL<<FLASH_OPTR2_ACC_CTRL_Pos)                 /*!< 0x00000080 */
#define FLASH_OPTR2_NBOOT1_Pos                    (8U)
#define FLASH_OPTR2_NBOOT1_Msk                    (0x1UL<<FLASH_OPTR2_NBOOT1_Pos)                   /*!< 0x00000100 */
#define FLASH_OPTR2_NBOOT1                        FLASH_OPTR2_NBOOT1_Msk                            
#define FLASH_OPTR2_NRST_MODE_Pos                 (9U)
#define FLASH_OPTR2_NRST_MODE_Msk                 (0x3UL<<FLASH_OPTR2_NRST_MODE_Pos)                /*!< 0x00000600 */
#define FLASH_OPTR2_NRST_MODE                     FLASH_OPTR2_NRST_MODE_Msk
#define FLASH_OPTR2_NRST_MODE_0                   (0x1UL<<FLASH_OPTR2_NRST_MODE_Pos)                /*!< 0x00000200 */
#define FLASH_OPTR2_NRST_MODE_1                   (0x2UL<<FLASH_OPTR2_NRST_MODE_Pos)                /*!< 0x00000400 */
#define FLASH_OPTR2_NSWBOOT0_Pos                  (13U)
#define FLASH_OPTR2_NSWBOOT0_Msk                  (0x1UL<<FLASH_OPTR2_NSWBOOT0_Pos)                 /*!< 0x00002000 */
#define FLASH_OPTR2_NSWBOOT0                      FLASH_OPTR2_NSWBOOT0_Msk                          
#define FLASH_OPTR2_NBOOT0_Pos                    (14U)
#define FLASH_OPTR2_NBOOT0_Msk                    (0x1UL<<FLASH_OPTR2_NBOOT0_Pos)                   /*!< 0x00004000 */
#define FLASH_OPTR2_NBOOT0                        FLASH_OPTR2_NBOOT0_Msk                            
#define FLASH_OPTR2_BOOT_LOCK_Pos                 (15U)
#define FLASH_OPTR2_BOOT_LOCK_Msk                 (0x1UL<<FLASH_OPTR2_BOOT_LOCK_Pos)                /*!< 0x00008000 */
#define FLASH_OPTR2_BOOT_LOCK                     FLASH_OPTR2_BOOT_LOCK_Msk                         

/********************************* Bit definition for FLASH_BANK0_WRPR register *************************************/
#define FLASH_BANK0_WRPR_BANK0_WRPR_Pos           (0U)
#define FLASH_BANK0_WRPR_BANK0_WRPR_Msk           (0xFFFFUL<<FLASH_BANK0_WRPR_BANK0_WRPR_Pos)       /*!< 0x0000FFFF */
#define FLASH_BANK0_WRPR_BANK0_WRPR               FLASH_BANK0_WRPR_BANK0_WRPR_Msk                   /*!< Write Protection Disable */

/********************************* Bit definition for FLASH_BANK1_WRPR register *************************************/
#define FLASH_BANK1_WRPR_BANK1_WRPR_Pos           (0U)
#define FLASH_BANK1_WRPR_BANK1_WRPR_Msk           (0xFFFFUL<<FLASH_BANK1_WRPR_BANK1_WRPR_Pos)       /*!< 0x0000FFFF */
#define FLASH_BANK1_WRPR_BANK1_WRPR               FLASH_BANK1_WRPR_BANK1_WRPR_Msk                   /*!< Write Protection Disable */

/********************************* Bit definition for FLASH_PCROP0SR register ***************************************/
#define FLASH_PCROP0SR_PCROP0SR_Pos               (0U)
#define FLASH_PCROP0SR_PCROP0SR_Msk               (0x1FFUL<<FLASH_PCROP0SR_PCROP0SR_Pos)            /*!< 0x000001FF */
#define FLASH_PCROP0SR_PCROP0SR                   FLASH_PCROP0SR_PCROP0SR_Msk

/********************************* Bit definition for FLASH_PCROP0ER register ***************************************/
#define FLASH_PCROP0ER_PCROP0ER_Pos               (0U)
#define FLASH_PCROP0ER_PCROP0ER_Msk               (0x1FFUL<<FLASH_PCROP0ER_PCROP0ER_Pos)            /*!< 0x000001FF */
#define FLASH_PCROP0ER_PCROP0ER                   FLASH_PCROP0ER_PCROP0ER_Msk

/********************************* Bit definition for FLASH_PCROP1SR register ***************************************/
#define FLASH_PCROP1SR_PCROP1SR_Pos               (0U)
#define FLASH_PCROP1SR_PCROP1SR_Msk               (0x1FFUL<<FLASH_PCROP1SR_PCROP1SR_Pos)            /*!< 0x000001FF */
#define FLASH_PCROP1SR_PCROP1SR                   FLASH_PCROP1SR_PCROP1SR_Msk

/********************************* Bit definition for FLASH_PCROP1ER register ***************************************/
#define FLASH_PCROP1ER_PCROP1ER_Pos               (0U)
#define FLASH_PCROP1ER_PCROP1ER_Msk               (0x1FFUL<<FLASH_PCROP1ER_PCROP1ER_Pos)            /*!< 0x000001FF */
#define FLASH_PCROP1ER_PCROP1ER                   FLASH_PCROP1ER_PCROP1ER_Msk

/********************************* Bit definition for FLASH_KEY register ********************************************/
#define FLASH_KEY1_Pos                            (0U)
#define FLASH_KEY1_Msk                            (0x45670123UL << FLASH_KEY1_Pos)                  /*!< 0x45670123 */
#define FLASH_KEY1                                FLASH_KEY1_Msk                                    /*!< Flash program erase key1 */
#define FLASH_KEY2_Pos                            (0U)
#define FLASH_KEY2_Msk                            (0xCDEF89ABUL << FLASH_KEY2_Pos)                  /*!< 0xCDEF89AB */
#define FLASH_KEY2                                FLASH_KEY2_Msk                                    /*!< Flash program erase key2: used with FLASH_PEKEY1 to unlock the write access to the FPEC. */

#define FLASH_OPTKEY1_Pos                         (0U)
#define FLASH_OPTKEY1_Msk                         (0x08192A3BUL << FLASH_OPTKEY1_Pos)               /*!< 0x08192A3B */
#define FLASH_OPTKEY1                             FLASH_OPTKEY1_Msk                                 /*!< Flash option key1 */
#define FLASH_OPTKEY2_Pos                         (0U)
#define FLASH_OPTKEY2_Msk                         (0x4C5D6E7FUL << FLASH_OPTKEY2_Pos)               /*!< 0x4C5D6E7F */
#define FLASH_OPTKEY2                             FLASH_OPTKEY2_Msk                                 /*!< Flash option key2: used with FLASH_OPTKEY1 to unlock the write access to the option byte block */

/*********************  Bits Define For Peripheral GPIO  *********************/
/*!< GPIO_MODER */
#define GPIO_MODER_MODE0_Pos                      (0U)
#define GPIO_MODER_MODE0_Msk                      (0x3UL << GPIO_MODER_MODE0_Pos)                   /*!< 0x00000003 */
#define GPIO_MODER_MODE0                          GPIO_MODER_MODE0_Msk                              /*!< MODE0[1:0] bits (desc MODE0) */
#define GPIO_MODER_MODE0_0                        (0x1UL << GPIO_MODER_MODE0_Pos)                   /*!< 0x00000001 */
#define GPIO_MODER_MODE0_1                        (0x2UL << GPIO_MODER_MODE0_Pos)                   /*!< 0x00000002 */

#define GPIO_MODER_MODE1_Pos                      (2U)
#define GPIO_MODER_MODE1_Msk                      (0x3UL << GPIO_MODER_MODE1_Pos)                   /*!< 0x0000000C */
#define GPIO_MODER_MODE1                          GPIO_MODER_MODE1_Msk                              /*!< MODE1[3:2] bits (desc MODE1) */
#define GPIO_MODER_MODE1_0                        (0x1UL << GPIO_MODER_MODE1_Pos)                   /*!< 0x00000004 */
#define GPIO_MODER_MODE1_1                        (0x2UL << GPIO_MODER_MODE1_Pos)                   /*!< 0x00000008 */

#define GPIO_MODER_MODE2_Pos                      (4U)
#define GPIO_MODER_MODE2_Msk                      (0x3UL << GPIO_MODER_MODE2_Pos)                   /*!< 0x00000030 */
#define GPIO_MODER_MODE2                          GPIO_MODER_MODE2_Msk                              /*!< MODE2[5:4] bits (desc MODE2) */
#define GPIO_MODER_MODE2_0                        (0x1UL << GPIO_MODER_MODE2_Pos)                   /*!< 0x00000010 */
#define GPIO_MODER_MODE2_1                        (0x2UL << GPIO_MODER_MODE2_Pos)                   /*!< 0x00000020 */

#define GPIO_MODER_MODE3_Pos                      (6U)
#define GPIO_MODER_MODE3_Msk                      (0x3UL << GPIO_MODER_MODE3_Pos)                   /*!< 0x000000C0 */
#define GPIO_MODER_MODE3                          GPIO_MODER_MODE3_Msk                              /*!< MODE3[7:6] bits (desc MODE3) */
#define GPIO_MODER_MODE3_0                        (0x1UL << GPIO_MODER_MODE3_Pos)                   /*!< 0x00000040 */
#define GPIO_MODER_MODE3_1                        (0x2UL << GPIO_MODER_MODE3_Pos)                   /*!< 0x00000080 */

#define GPIO_MODER_MODE4_Pos                      (8U)
#define GPIO_MODER_MODE4_Msk                      (0x3UL << GPIO_MODER_MODE4_Pos)                   /*!< 0x00000300 */
#define GPIO_MODER_MODE4                          GPIO_MODER_MODE4_Msk                              /*!< MODE4[9:8] bits (desc MODE4) */
#define GPIO_MODER_MODE4_0                        (0x1UL << GPIO_MODER_MODE4_Pos)                   /*!< 0x00000100 */
#define GPIO_MODER_MODE4_1                        (0x2UL << GPIO_MODER_MODE4_Pos)                   /*!< 0x00000200 */

#define GPIO_MODER_MODE5_Pos                      (10U)
#define GPIO_MODER_MODE5_Msk                      (0x3UL << GPIO_MODER_MODE5_Pos)                   /*!< 0x00000C00 */
#define GPIO_MODER_MODE5                          GPIO_MODER_MODE5_Msk                              /*!< MODE5[11:10] bits (desc MODE5) */
#define GPIO_MODER_MODE5_0                        (0x1UL << GPIO_MODER_MODE5_Pos)                   /*!< 0x00000400 */
#define GPIO_MODER_MODE5_1                        (0x2UL << GPIO_MODER_MODE5_Pos)                   /*!< 0x00000800 */

#define GPIO_MODER_MODE6_Pos                      (12U)
#define GPIO_MODER_MODE6_Msk                      (0x3UL << GPIO_MODER_MODE6_Pos)                   /*!< 0x00003000 */
#define GPIO_MODER_MODE6                          GPIO_MODER_MODE6_Msk                              /*!< MODE6[13:12] bits (desc MODE6) */
#define GPIO_MODER_MODE6_0                        (0x1UL << GPIO_MODER_MODE6_Pos)                   /*!< 0x00001000 */
#define GPIO_MODER_MODE6_1                        (0x2UL << GPIO_MODER_MODE6_Pos)                   /*!< 0x00002000 */

#define GPIO_MODER_MODE7_Pos                      (14U)
#define GPIO_MODER_MODE7_Msk                      (0x3UL << GPIO_MODER_MODE7_Pos)                   /*!< 0x0000C000 */
#define GPIO_MODER_MODE7                          GPIO_MODER_MODE7_Msk                              /*!< MODE7[15:14] bits (desc MODE7) */
#define GPIO_MODER_MODE7_0                        (0x1UL << GPIO_MODER_MODE7_Pos)                   /*!< 0x00004000 */
#define GPIO_MODER_MODE7_1                        (0x2UL << GPIO_MODER_MODE7_Pos)                   /*!< 0x00008000 */

#define GPIO_MODER_MODE8_Pos                      (16U)
#define GPIO_MODER_MODE8_Msk                      (0x3UL << GPIO_MODER_MODE8_Pos)                   /*!< 0x00030000 */
#define GPIO_MODER_MODE8                          GPIO_MODER_MODE8_Msk                              /*!< MODE8[17:16] bits (desc MODE8) */
#define GPIO_MODER_MODE8_0                        (0x1UL << GPIO_MODER_MODE8_Pos)                   /*!< 0x00010000 */
#define GPIO_MODER_MODE8_1                        (0x2UL << GPIO_MODER_MODE8_Pos)                   /*!< 0x00020000 */

#define GPIO_MODER_MODE9_Pos                      (18U)
#define GPIO_MODER_MODE9_Msk                      (0x3UL << GPIO_MODER_MODE9_Pos)                   /*!< 0x000C0000 */
#define GPIO_MODER_MODE9                          GPIO_MODER_MODE9_Msk                              /*!< MODE9[19:18] bits (desc MODE9) */
#define GPIO_MODER_MODE9_0                        (0x1UL << GPIO_MODER_MODE9_Pos)                   /*!< 0x00040000 */
#define GPIO_MODER_MODE9_1                        (0x2UL << GPIO_MODER_MODE9_Pos)                   /*!< 0x00080000 */

#define GPIO_MODER_MODE10_Pos                     (20U)
#define GPIO_MODER_MODE10_Msk                     (0x3UL << GPIO_MODER_MODE10_Pos)                  /*!< 0x00300000 */
#define GPIO_MODER_MODE10                         GPIO_MODER_MODE10_Msk                             /*!< MODE10[21:20] bits (desc MODE10) */
#define GPIO_MODER_MODE10_0                       (0x1UL << GPIO_MODER_MODE10_Pos)                  /*!< 0x00100000 */
#define GPIO_MODER_MODE10_1                       (0x2UL << GPIO_MODER_MODE10_Pos)                  /*!< 0x00200000 */

#define GPIO_MODER_MODE11_Pos                     (22U)
#define GPIO_MODER_MODE11_Msk                     (0x3UL << GPIO_MODER_MODE11_Pos)                  /*!< 0x00C00000 */
#define GPIO_MODER_MODE11                         GPIO_MODER_MODE11_Msk                             /*!< MODE11[23:22] bits (desc MODE11) */
#define GPIO_MODER_MODE11_0                       (0x1UL << GPIO_MODER_MODE11_Pos)                  /*!< 0x00400000 */
#define GPIO_MODER_MODE11_1                       (0x2UL << GPIO_MODER_MODE11_Pos)                  /*!< 0x00800000 */

#define GPIO_MODER_MODE12_Pos                     (24U)
#define GPIO_MODER_MODE12_Msk                     (0x3UL << GPIO_MODER_MODE12_Pos)                  /*!< 0x03000000 */
#define GPIO_MODER_MODE12                         GPIO_MODER_MODE12_Msk                             /*!< MODE12[25:24] bits (desc MODE12) */
#define GPIO_MODER_MODE12_0                       (0x1UL << GPIO_MODER_MODE12_Pos)                  /*!< 0x01000000 */
#define GPIO_MODER_MODE12_1                       (0x2UL << GPIO_MODER_MODE12_Pos)                  /*!< 0x02000000 */

#define GPIO_MODER_MODE13_Pos                     (26U)
#define GPIO_MODER_MODE13_Msk                     (0x3UL << GPIO_MODER_MODE13_Pos)                  /*!< 0x0C000000 */
#define GPIO_MODER_MODE13                         GPIO_MODER_MODE13_Msk                             /*!< MODE13[27:26] bits (desc MODE13) */
#define GPIO_MODER_MODE13_0                       (0x1UL << GPIO_MODER_MODE13_Pos)                  /*!< 0x04000000 */
#define GPIO_MODER_MODE13_1                       (0x2UL << GPIO_MODER_MODE13_Pos)                  /*!< 0x08000000 */

#define GPIO_MODER_MODE14_Pos                     (28U)
#define GPIO_MODER_MODE14_Msk                     (0x3UL << GPIO_MODER_MODE14_Pos)                  /*!< 0x30000000 */
#define GPIO_MODER_MODE14                         GPIO_MODER_MODE14_Msk                             /*!< MODE14[29:28] bits (desc MODE14) */
#define GPIO_MODER_MODE14_0                       (0x1UL << GPIO_MODER_MODE14_Pos)                  /*!< 0x10000000 */
#define GPIO_MODER_MODE14_1                       (0x2UL << GPIO_MODER_MODE14_Pos)                  /*!< 0x20000000 */

#define GPIO_MODER_MODE15_Pos                     (30U)
#define GPIO_MODER_MODE15_Msk                     (0x3UL << GPIO_MODER_MODE15_Pos)                  /*!< 0xC0000000 */
#define GPIO_MODER_MODE15                         GPIO_MODER_MODE15_Msk                             /*!< MODE15[31:30] bits (desc MODE15) */
#define GPIO_MODER_MODE15_0                       (0x1UL << GPIO_MODER_MODE15_Pos)                  /*!< 0x40000000 */
#define GPIO_MODER_MODE15_1                       (0x2UL << GPIO_MODER_MODE15_Pos)                  /*!< 0x80000000 */

/*!< GPIO_OTYPER */
#define GPIO_OTYPER_OT0_Pos                       (0U)
#define GPIO_OTYPER_OT0_Msk                       (0x1UL << GPIO_OTYPER_OT0_Pos)                    /*!< 0x00000001 */
#define GPIO_OTYPER_OT0                           GPIO_OTYPER_OT0_Msk                               /*!< desc OT0 */
#define GPIO_OTYPER_OT1_Pos                       (1U)
#define GPIO_OTYPER_OT1_Msk                       (0x1UL << GPIO_OTYPER_OT1_Pos)                    /*!< 0x00000002 */
#define GPIO_OTYPER_OT1                           GPIO_OTYPER_OT1_Msk                               /*!< desc OT1 */
#define GPIO_OTYPER_OT2_Pos                       (2U)
#define GPIO_OTYPER_OT2_Msk                       (0x1UL << GPIO_OTYPER_OT2_Pos)                    /*!< 0x00000004 */
#define GPIO_OTYPER_OT2                           GPIO_OTYPER_OT2_Msk                               /*!< desc OT2 */
#define GPIO_OTYPER_OT3_Pos                       (3U)
#define GPIO_OTYPER_OT3_Msk                       (0x1UL << GPIO_OTYPER_OT3_Pos)                    /*!< 0x00000008 */
#define GPIO_OTYPER_OT3                           GPIO_OTYPER_OT3_Msk                               /*!< desc OT3 */
#define GPIO_OTYPER_OT4_Pos                       (4U)
#define GPIO_OTYPER_OT4_Msk                       (0x1UL << GPIO_OTYPER_OT4_Pos)                    /*!< 0x00000010 */
#define GPIO_OTYPER_OT4                           GPIO_OTYPER_OT4_Msk                               /*!< desc OT4 */
#define GPIO_OTYPER_OT5_Pos                       (5U)
#define GPIO_OTYPER_OT5_Msk                       (0x1UL << GPIO_OTYPER_OT5_Pos)                    /*!< 0x00000020 */
#define GPIO_OTYPER_OT5                           GPIO_OTYPER_OT5_Msk                               /*!< desc OT5 */
#define GPIO_OTYPER_OT6_Pos                       (6U)
#define GPIO_OTYPER_OT6_Msk                       (0x1UL << GPIO_OTYPER_OT6_Pos)                    /*!< 0x00000040 */
#define GPIO_OTYPER_OT6                           GPIO_OTYPER_OT6_Msk                               /*!< desc OT6 */
#define GPIO_OTYPER_OT7_Pos                       (7U)
#define GPIO_OTYPER_OT7_Msk                       (0x1UL << GPIO_OTYPER_OT7_Pos)                    /*!< 0x00000080 */
#define GPIO_OTYPER_OT7                           GPIO_OTYPER_OT7_Msk                               /*!< desc OT7 */
#define GPIO_OTYPER_OT8_Pos                       (8U)
#define GPIO_OTYPER_OT8_Msk                       (0x1UL << GPIO_OTYPER_OT8_Pos)                    /*!< 0x00000100 */
#define GPIO_OTYPER_OT8                           GPIO_OTYPER_OT8_Msk                               /*!< desc OT8 */
#define GPIO_OTYPER_OT9_Pos                       (9U)
#define GPIO_OTYPER_OT9_Msk                       (0x1UL << GPIO_OTYPER_OT9_Pos)                    /*!< 0x00000200 */
#define GPIO_OTYPER_OT9                           GPIO_OTYPER_OT9_Msk                               /*!< desc OT9 */
#define GPIO_OTYPER_OT10_Pos                      (10U)
#define GPIO_OTYPER_OT10_Msk                      (0x1UL << GPIO_OTYPER_OT10_Pos)                   /*!< 0x00000400 */
#define GPIO_OTYPER_OT10                          GPIO_OTYPER_OT10_Msk                              /*!< desc OT10 */
#define GPIO_OTYPER_OT11_Pos                      (11U)
#define GPIO_OTYPER_OT11_Msk                      (0x1UL << GPIO_OTYPER_OT11_Pos)                   /*!< 0x00000800 */
#define GPIO_OTYPER_OT11                          GPIO_OTYPER_OT11_Msk                              /*!< desc OT11 */
#define GPIO_OTYPER_OT12_Pos                      (12U)
#define GPIO_OTYPER_OT12_Msk                      (0x1UL << GPIO_OTYPER_OT12_Pos)                   /*!< 0x00001000 */
#define GPIO_OTYPER_OT12                          GPIO_OTYPER_OT12_Msk                              /*!< desc OT12 */
#define GPIO_OTYPER_OT13_Pos                      (13U)
#define GPIO_OTYPER_OT13_Msk                      (0x1UL << GPIO_OTYPER_OT13_Pos)                   /*!< 0x00002000 */
#define GPIO_OTYPER_OT13                          GPIO_OTYPER_OT13_Msk                              /*!< desc OT13 */
#define GPIO_OTYPER_OT14_Pos                      (14U)
#define GPIO_OTYPER_OT14_Msk                      (0x1UL << GPIO_OTYPER_OT14_Pos)                   /*!< 0x00004000 */
#define GPIO_OTYPER_OT14                          GPIO_OTYPER_OT14_Msk                              /*!< desc OT14 */
#define GPIO_OTYPER_OT15_Pos                      (15U)
#define GPIO_OTYPER_OT15_Msk                      (0x1UL << GPIO_OTYPER_OT15_Pos)                   /*!< 0x00008000 */
#define GPIO_OTYPER_OT15                          GPIO_OTYPER_OT15_Msk                              /*!< desc OT15 */

/*!< GPIO_OSPEEDR */
#define GPIO_OSPEEDR_OSPEED0_Pos                  (0U)
#define GPIO_OSPEEDR_OSPEED0_Msk                  (0x3UL << GPIO_OSPEEDR_OSPEED0_Pos)               /*!< 0x00000003 */
#define GPIO_OSPEEDR_OSPEED0                      GPIO_OSPEEDR_OSPEED0_Msk                          /*!< OSPEED0[1:0] bits (desc OSPEED0) */
#define GPIO_OSPEEDR_OSPEED0_0                    (0x1UL << GPIO_OSPEEDR_OSPEED0_Pos)               /*!< 0x00000001 */
#define GPIO_OSPEEDR_OSPEED0_1                    (0x2UL << GPIO_OSPEEDR_OSPEED0_Pos)               /*!< 0x00000002 */

#define GPIO_OSPEEDR_OSPEED1_Pos                  (2U)
#define GPIO_OSPEEDR_OSPEED1_Msk                  (0x3UL << GPIO_OSPEEDR_OSPEED1_Pos)               /*!< 0x0000000C */
#define GPIO_OSPEEDR_OSPEED1                      GPIO_OSPEEDR_OSPEED1_Msk                          /*!< OSPEED1[3:2] bits (desc OSPEED1) */
#define GPIO_OSPEEDR_OSPEED1_0                    (0x1UL << GPIO_OSPEEDR_OSPEED1_Pos)               /*!< 0x00000004 */
#define GPIO_OSPEEDR_OSPEED1_1                    (0x2UL << GPIO_OSPEEDR_OSPEED1_Pos)               /*!< 0x00000008 */

#define GPIO_OSPEEDR_OSPEED2_Pos                  (4U)
#define GPIO_OSPEEDR_OSPEED2_Msk                  (0x3UL << GPIO_OSPEEDR_OSPEED2_Pos)               /*!< 0x00000030 */
#define GPIO_OSPEEDR_OSPEED2                      GPIO_OSPEEDR_OSPEED2_Msk                          /*!< OSPEED2[5:4] bits (desc OSPEED2) */
#define GPIO_OSPEEDR_OSPEED2_0                    (0x1UL << GPIO_OSPEEDR_OSPEED2_Pos)               /*!< 0x00000010 */
#define GPIO_OSPEEDR_OSPEED2_1                    (0x2UL << GPIO_OSPEEDR_OSPEED2_Pos)               /*!< 0x00000020 */

#define GPIO_OSPEEDR_OSPEED3_Pos                  (6U)
#define GPIO_OSPEEDR_OSPEED3_Msk                  (0x3UL << GPIO_OSPEEDR_OSPEED3_Pos)               /*!< 0x000000C0 */
#define GPIO_OSPEEDR_OSPEED3                      GPIO_OSPEEDR_OSPEED3_Msk                          /*!< OSPEED3[7:6] bits (desc OSPEED3) */
#define GPIO_OSPEEDR_OSPEED3_0                    (0x1UL << GPIO_OSPEEDR_OSPEED3_Pos)               /*!< 0x00000040 */
#define GPIO_OSPEEDR_OSPEED3_1                    (0x2UL << GPIO_OSPEEDR_OSPEED3_Pos)               /*!< 0x00000080 */

#define GPIO_OSPEEDR_OSPEED4_Pos                  (8U)
#define GPIO_OSPEEDR_OSPEED4_Msk                  (0x3UL << GPIO_OSPEEDR_OSPEED4_Pos)               /*!< 0x00000300 */
#define GPIO_OSPEEDR_OSPEED4                      GPIO_OSPEEDR_OSPEED4_Msk                          /*!< OSPEED4[9:8] bits (desc OSPEED4) */
#define GPIO_OSPEEDR_OSPEED4_0                    (0x1UL << GPIO_OSPEEDR_OSPEED4_Pos)               /*!< 0x00000100 */
#define GPIO_OSPEEDR_OSPEED4_1                    (0x2UL << GPIO_OSPEEDR_OSPEED4_Pos)               /*!< 0x00000200 */

#define GPIO_OSPEEDR_OSPEED5_Pos                  (10U)
#define GPIO_OSPEEDR_OSPEED5_Msk                  (0x3UL << GPIO_OSPEEDR_OSPEED5_Pos)               /*!< 0x00000C00 */
#define GPIO_OSPEEDR_OSPEED5                      GPIO_OSPEEDR_OSPEED5_Msk                          /*!< OSPEED5[11:10] bits (desc OSPEED5) */
#define GPIO_OSPEEDR_OSPEED5_0                    (0x1UL << GPIO_OSPEEDR_OSPEED5_Pos)               /*!< 0x00000400 */
#define GPIO_OSPEEDR_OSPEED5_1                    (0x2UL << GPIO_OSPEEDR_OSPEED5_Pos)               /*!< 0x00000800 */

#define GPIO_OSPEEDR_OSPEED6_Pos                  (12U)
#define GPIO_OSPEEDR_OSPEED6_Msk                  (0x3UL << GPIO_OSPEEDR_OSPEED6_Pos)               /*!< 0x00003000 */
#define GPIO_OSPEEDR_OSPEED6                      GPIO_OSPEEDR_OSPEED6_Msk                          /*!< OSPEED6[13:12] bits (desc OSPEED6) */
#define GPIO_OSPEEDR_OSPEED6_0                    (0x1UL << GPIO_OSPEEDR_OSPEED6_Pos)               /*!< 0x00001000 */
#define GPIO_OSPEEDR_OSPEED6_1                    (0x2UL << GPIO_OSPEEDR_OSPEED6_Pos)               /*!< 0x00002000 */

#define GPIO_OSPEEDR_OSPEED7_Pos                  (14U)
#define GPIO_OSPEEDR_OSPEED7_Msk                  (0x3UL << GPIO_OSPEEDR_OSPEED7_Pos)               /*!< 0x0000C000 */
#define GPIO_OSPEEDR_OSPEED7                      GPIO_OSPEEDR_OSPEED7_Msk                          /*!< OSPEED7[15:14] bits (desc OSPEED7) */
#define GPIO_OSPEEDR_OSPEED7_0                    (0x1UL << GPIO_OSPEEDR_OSPEED7_Pos)               /*!< 0x00004000 */
#define GPIO_OSPEEDR_OSPEED7_1                    (0x2UL << GPIO_OSPEEDR_OSPEED7_Pos)               /*!< 0x00008000 */

#define GPIO_OSPEEDR_OSPEED8_Pos                  (16U)
#define GPIO_OSPEEDR_OSPEED8_Msk                  (0x3UL << GPIO_OSPEEDR_OSPEED8_Pos)               /*!< 0x00030000 */
#define GPIO_OSPEEDR_OSPEED8                      GPIO_OSPEEDR_OSPEED8_Msk                          /*!< OSPEED8[17:16] bits (desc OSPEED8) */
#define GPIO_OSPEEDR_OSPEED8_0                    (0x1UL << GPIO_OSPEEDR_OSPEED8_Pos)               /*!< 0x00010000 */
#define GPIO_OSPEEDR_OSPEED8_1                    (0x2UL << GPIO_OSPEEDR_OSPEED8_Pos)               /*!< 0x00020000 */

#define GPIO_OSPEEDR_OSPEED9_Pos                  (18U)
#define GPIO_OSPEEDR_OSPEED9_Msk                  (0x3UL << GPIO_OSPEEDR_OSPEED9_Pos)               /*!< 0x000C0000 */
#define GPIO_OSPEEDR_OSPEED9                      GPIO_OSPEEDR_OSPEED9_Msk                          /*!< OSPEED9[19:18] bits (desc OSPEED9) */
#define GPIO_OSPEEDR_OSPEED9_0                    (0x1UL << GPIO_OSPEEDR_OSPEED9_Pos)               /*!< 0x00040000 */
#define GPIO_OSPEEDR_OSPEED9_1                    (0x2UL << GPIO_OSPEEDR_OSPEED9_Pos)               /*!< 0x00080000 */

#define GPIO_OSPEEDR_OSPEED10_Pos                 (20U)
#define GPIO_OSPEEDR_OSPEED10_Msk                 (0x3UL << GPIO_OSPEEDR_OSPEED10_Pos)              /*!< 0x00300000 */
#define GPIO_OSPEEDR_OSPEED10                     GPIO_OSPEEDR_OSPEED10_Msk                         /*!< OSPEED10[21:20] bits (desc OSPEED10) */
#define GPIO_OSPEEDR_OSPEED10_0                   (0x1UL << GPIO_OSPEEDR_OSPEED10_Pos)              /*!< 0x00100000 */
#define GPIO_OSPEEDR_OSPEED10_1                   (0x2UL << GPIO_OSPEEDR_OSPEED10_Pos)              /*!< 0x00200000 */

#define GPIO_OSPEEDR_OSPEED11_Pos                 (22U)
#define GPIO_OSPEEDR_OSPEED11_Msk                 (0x3UL << GPIO_OSPEEDR_OSPEED11_Pos)              /*!< 0x00C00000 */
#define GPIO_OSPEEDR_OSPEED11                     GPIO_OSPEEDR_OSPEED11_Msk                         /*!< OSPEED11[23:22] bits (desc OSPEED11) */
#define GPIO_OSPEEDR_OSPEED11_0                   (0x1UL << GPIO_OSPEEDR_OSPEED11_Pos)              /*!< 0x00400000 */
#define GPIO_OSPEEDR_OSPEED11_1                   (0x2UL << GPIO_OSPEEDR_OSPEED11_Pos)              /*!< 0x00800000 */

#define GPIO_OSPEEDR_OSPEED12_Pos                 (24U)
#define GPIO_OSPEEDR_OSPEED12_Msk                 (0x3UL << GPIO_OSPEEDR_OSPEED12_Pos)              /*!< 0x03000000 */
#define GPIO_OSPEEDR_OSPEED12                     GPIO_OSPEEDR_OSPEED12_Msk                         /*!< OSPEED12[25:24] bits (desc OSPEED12) */
#define GPIO_OSPEEDR_OSPEED12_0                   (0x1UL << GPIO_OSPEEDR_OSPEED12_Pos)              /*!< 0x01000000 */
#define GPIO_OSPEEDR_OSPEED12_1                   (0x2UL << GPIO_OSPEEDR_OSPEED12_Pos)              /*!< 0x02000000 */

#define GPIO_OSPEEDR_OSPEED13_Pos                 (26U)
#define GPIO_OSPEEDR_OSPEED13_Msk                 (0x3UL << GPIO_OSPEEDR_OSPEED13_Pos)              /*!< 0x0C000000 */
#define GPIO_OSPEEDR_OSPEED13                     GPIO_OSPEEDR_OSPEED13_Msk                         /*!< OSPEED13[27:26] bits (desc OSPEED13) */
#define GPIO_OSPEEDR_OSPEED13_0                   (0x1UL << GPIO_OSPEEDR_OSPEED13_Pos)              /*!< 0x04000000 */
#define GPIO_OSPEEDR_OSPEED13_1                   (0x2UL << GPIO_OSPEEDR_OSPEED13_Pos)              /*!< 0x08000000 */

#define GPIO_OSPEEDR_OSPEED14_Pos                 (28U)
#define GPIO_OSPEEDR_OSPEED14_Msk                 (0x3UL << GPIO_OSPEEDR_OSPEED14_Pos)              /*!< 0x30000000 */
#define GPIO_OSPEEDR_OSPEED14                     GPIO_OSPEEDR_OSPEED14_Msk                         /*!< OSPEED14[29:28] bits (desc OSPEED14) */
#define GPIO_OSPEEDR_OSPEED14_0                   (0x1UL << GPIO_OSPEEDR_OSPEED14_Pos)              /*!< 0x10000000 */
#define GPIO_OSPEEDR_OSPEED14_1                   (0x2UL << GPIO_OSPEEDR_OSPEED14_Pos)              /*!< 0x20000000 */

#define GPIO_OSPEEDR_OSPEED15_Pos                 (30U)
#define GPIO_OSPEEDR_OSPEED15_Msk                 (0x3UL << GPIO_OSPEEDR_OSPEED15_Pos)              /*!< 0xC0000000 */
#define GPIO_OSPEEDR_OSPEED15                     GPIO_OSPEEDR_OSPEED15_Msk                         /*!< OSPEED15[31:30] bits (desc OSPEED15) */
#define GPIO_OSPEEDR_OSPEED15_0                   (0x1UL << GPIO_OSPEEDR_OSPEED15_Pos)              /*!< 0x40000000 */
#define GPIO_OSPEEDR_OSPEED15_1                   (0x2UL << GPIO_OSPEEDR_OSPEED15_Pos)              /*!< 0x80000000 */

/*!< GPIO_PUPDR */
#define GPIO_PUPDR_PUPD0_Pos                      (0U)
#define GPIO_PUPDR_PUPD0_Msk                      (0x3UL << GPIO_PUPDR_PUPD0_Pos)                   /*!< 0x00000003 */
#define GPIO_PUPDR_PUPD0                          GPIO_PUPDR_PUPD0_Msk                              /*!< PUPD0[1:0] bits (desc PUPD0) */
#define GPIO_PUPDR_PUPD0_0                        (0x1UL << GPIO_PUPDR_PUPD0_Pos)                   /*!< 0x00000001 */
#define GPIO_PUPDR_PUPD0_1                        (0x2UL << GPIO_PUPDR_PUPD0_Pos)                   /*!< 0x00000002 */

#define GPIO_PUPDR_PUPD1_Pos                      (2U)
#define GPIO_PUPDR_PUPD1_Msk                      (0x3UL << GPIO_PUPDR_PUPD1_Pos)                   /*!< 0x0000000C */
#define GPIO_PUPDR_PUPD1                          GPIO_PUPDR_PUPD1_Msk                              /*!< PUPD1[3:2] bits (desc PUPD1) */
#define GPIO_PUPDR_PUPD1_0                        (0x1UL << GPIO_PUPDR_PUPD1_Pos)                   /*!< 0x00000004 */
#define GPIO_PUPDR_PUPD1_1                        (0x2UL << GPIO_PUPDR_PUPD1_Pos)                   /*!< 0x00000008 */

#define GPIO_PUPDR_PUPD2_Pos                      (4U)
#define GPIO_PUPDR_PUPD2_Msk                      (0x3UL << GPIO_PUPDR_PUPD2_Pos)                   /*!< 0x00000030 */
#define GPIO_PUPDR_PUPD2                          GPIO_PUPDR_PUPD2_Msk                              /*!< PUPD2[5:4] bits (desc PUPD2) */
#define GPIO_PUPDR_PUPD2_0                        (0x1UL << GPIO_PUPDR_PUPD2_Pos)                   /*!< 0x00000010 */
#define GPIO_PUPDR_PUPD2_1                        (0x2UL << GPIO_PUPDR_PUPD2_Pos)                   /*!< 0x00000020 */

#define GPIO_PUPDR_PUPD3_Pos                      (6U)
#define GPIO_PUPDR_PUPD3_Msk                      (0x3UL << GPIO_PUPDR_PUPD3_Pos)                   /*!< 0x000000C0 */
#define GPIO_PUPDR_PUPD3                          GPIO_PUPDR_PUPD3_Msk                              /*!< PUPD3[7:6] bits (desc PUPD3) */
#define GPIO_PUPDR_PUPD3_0                        (0x1UL << GPIO_PUPDR_PUPD3_Pos)                   /*!< 0x00000040 */
#define GPIO_PUPDR_PUPD3_1                        (0x2UL << GPIO_PUPDR_PUPD3_Pos)                   /*!< 0x00000080 */

#define GPIO_PUPDR_PUPD4_Pos                      (8U)
#define GPIO_PUPDR_PUPD4_Msk                      (0x3UL << GPIO_PUPDR_PUPD4_Pos)                   /*!< 0x00000300 */
#define GPIO_PUPDR_PUPD4                          GPIO_PUPDR_PUPD4_Msk                              /*!< PUPD4[9:8] bits (desc PUPD4) */
#define GPIO_PUPDR_PUPD4_0                        (0x1UL << GPIO_PUPDR_PUPD4_Pos)                   /*!< 0x00000100 */
#define GPIO_PUPDR_PUPD4_1                        (0x2UL << GPIO_PUPDR_PUPD4_Pos)                   /*!< 0x00000200 */

#define GPIO_PUPDR_PUPD5_Pos                      (10U)
#define GPIO_PUPDR_PUPD5_Msk                      (0x3UL << GPIO_PUPDR_PUPD5_Pos)                   /*!< 0x00000C00 */
#define GPIO_PUPDR_PUPD5                          GPIO_PUPDR_PUPD5_Msk                              /*!< PUPD5[11:10] bits (desc PUPD5) */
#define GPIO_PUPDR_PUPD5_0                        (0x1UL << GPIO_PUPDR_PUPD5_Pos)                   /*!< 0x00000400 */
#define GPIO_PUPDR_PUPD5_1                        (0x2UL << GPIO_PUPDR_PUPD5_Pos)                   /*!< 0x00000800 */

#define GPIO_PUPDR_PUPD6_Pos                      (12U)
#define GPIO_PUPDR_PUPD6_Msk                      (0x3UL << GPIO_PUPDR_PUPD6_Pos)                   /*!< 0x00003000 */
#define GPIO_PUPDR_PUPD6                          GPIO_PUPDR_PUPD6_Msk                              /*!< PUPD6[13:12] bits (desc PUPD6) */
#define GPIO_PUPDR_PUPD6_0                        (0x1UL << GPIO_PUPDR_PUPD6_Pos)                   /*!< 0x00001000 */
#define GPIO_PUPDR_PUPD6_1                        (0x2UL << GPIO_PUPDR_PUPD6_Pos)                   /*!< 0x00002000 */

#define GPIO_PUPDR_PUPD7_Pos                      (14U)
#define GPIO_PUPDR_PUPD7_Msk                      (0x3UL << GPIO_PUPDR_PUPD7_Pos)                   /*!< 0x0000C000 */
#define GPIO_PUPDR_PUPD7                          GPIO_PUPDR_PUPD7_Msk                              /*!< PUPD7[15:14] bits (desc PUPD7) */
#define GPIO_PUPDR_PUPD7_0                        (0x1UL << GPIO_PUPDR_PUPD7_Pos)                   /*!< 0x00004000 */
#define GPIO_PUPDR_PUPD7_1                        (0x2UL << GPIO_PUPDR_PUPD7_Pos)                   /*!< 0x00008000 */

#define GPIO_PUPDR_PUPD8_Pos                      (16U)
#define GPIO_PUPDR_PUPD8_Msk                      (0x3UL << GPIO_PUPDR_PUPD8_Pos)                   /*!< 0x00030000 */
#define GPIO_PUPDR_PUPD8                          GPIO_PUPDR_PUPD8_Msk                              /*!< PUPD8[17:16] bits (desc PUPD8) */
#define GPIO_PUPDR_PUPD8_0                        (0x1UL << GPIO_PUPDR_PUPD8_Pos)                   /*!< 0x00010000 */
#define GPIO_PUPDR_PUPD8_1                        (0x2UL << GPIO_PUPDR_PUPD8_Pos)                   /*!< 0x00020000 */

#define GPIO_PUPDR_PUPD9_Pos                      (18U)
#define GPIO_PUPDR_PUPD9_Msk                      (0x3UL << GPIO_PUPDR_PUPD9_Pos)                   /*!< 0x000C0000 */
#define GPIO_PUPDR_PUPD9                          GPIO_PUPDR_PUPD9_Msk                              /*!< PUPD9[19:18] bits (desc PUPD9) */
#define GPIO_PUPDR_PUPD9_0                        (0x1UL << GPIO_PUPDR_PUPD9_Pos)                   /*!< 0x00040000 */
#define GPIO_PUPDR_PUPD9_1                        (0x2UL << GPIO_PUPDR_PUPD9_Pos)                   /*!< 0x00080000 */

#define GPIO_PUPDR_PUPD10_Pos                     (20U)
#define GPIO_PUPDR_PUPD10_Msk                     (0x3UL << GPIO_PUPDR_PUPD10_Pos)                  /*!< 0x00300000 */
#define GPIO_PUPDR_PUPD10                         GPIO_PUPDR_PUPD10_Msk                             /*!< PUPD10[21:20] bits (desc PUPD10) */
#define GPIO_PUPDR_PUPD10_0                       (0x1UL << GPIO_PUPDR_PUPD10_Pos)                  /*!< 0x00100000 */
#define GPIO_PUPDR_PUPD10_1                       (0x2UL << GPIO_PUPDR_PUPD10_Pos)                  /*!< 0x00200000 */

#define GPIO_PUPDR_PUPD11_Pos                     (22U)
#define GPIO_PUPDR_PUPD11_Msk                     (0x3UL << GPIO_PUPDR_PUPD11_Pos)                  /*!< 0x00C00000 */
#define GPIO_PUPDR_PUPD11                         GPIO_PUPDR_PUPD11_Msk                             /*!< PUPD11[23:22] bits (desc PUPD11) */
#define GPIO_PUPDR_PUPD11_0                       (0x1UL << GPIO_PUPDR_PUPD11_Pos)                  /*!< 0x00400000 */
#define GPIO_PUPDR_PUPD11_1                       (0x2UL << GPIO_PUPDR_PUPD11_Pos)                  /*!< 0x00800000 */

#define GPIO_PUPDR_PUPD12_Pos                     (24U)
#define GPIO_PUPDR_PUPD12_Msk                     (0x3UL << GPIO_PUPDR_PUPD12_Pos)                  /*!< 0x03000000 */
#define GPIO_PUPDR_PUPD12                         GPIO_PUPDR_PUPD12_Msk                             /*!< PUPD12[25:24] bits (desc PUPD12) */
#define GPIO_PUPDR_PUPD12_0                       (0x1UL << GPIO_PUPDR_PUPD12_Pos)                  /*!< 0x01000000 */
#define GPIO_PUPDR_PUPD12_1                       (0x2UL << GPIO_PUPDR_PUPD12_Pos)                  /*!< 0x02000000 */

#define GPIO_PUPDR_PUPD13_Pos                     (26U)
#define GPIO_PUPDR_PUPD13_Msk                     (0x3UL << GPIO_PUPDR_PUPD13_Pos)                  /*!< 0x0C000000 */
#define GPIO_PUPDR_PUPD13                         GPIO_PUPDR_PUPD13_Msk                             /*!< PUPD13[27:26] bits (desc PUPD13) */
#define GPIO_PUPDR_PUPD13_0                       (0x1UL << GPIO_PUPDR_PUPD13_Pos)                  /*!< 0x04000000 */
#define GPIO_PUPDR_PUPD13_1                       (0x2UL << GPIO_PUPDR_PUPD13_Pos)                  /*!< 0x08000000 */

#define GPIO_PUPDR_PUPD14_Pos                     (28U)
#define GPIO_PUPDR_PUPD14_Msk                     (0x3UL << GPIO_PUPDR_PUPD14_Pos)                  /*!< 0x30000000 */
#define GPIO_PUPDR_PUPD14                         GPIO_PUPDR_PUPD14_Msk                             /*!< PUPD14[29:28] bits (desc PUPD14) */
#define GPIO_PUPDR_PUPD14_0                       (0x1UL << GPIO_PUPDR_PUPD14_Pos)                  /*!< 0x10000000 */
#define GPIO_PUPDR_PUPD14_1                       (0x2UL << GPIO_PUPDR_PUPD14_Pos)                  /*!< 0x20000000 */

#define GPIO_PUPDR_PUPD15_Pos                     (30U)
#define GPIO_PUPDR_PUPD15_Msk                     (0x3UL << GPIO_PUPDR_PUPD15_Pos)                  /*!< 0xC0000000 */
#define GPIO_PUPDR_PUPD15                         GPIO_PUPDR_PUPD15_Msk                             /*!< PUPD15[31:30] bits (desc PUPD15) */
#define GPIO_PUPDR_PUPD15_0                       (0x1UL << GPIO_PUPDR_PUPD15_Pos)                  /*!< 0x40000000 */
#define GPIO_PUPDR_PUPD15_1                       (0x2UL << GPIO_PUPDR_PUPD15_Pos)                  /*!< 0x80000000 */

/*!< GPIO_IDR */
#define GPIO_IDR_ID0_Pos                          (0U)
#define GPIO_IDR_ID0_Msk                          (0x1UL << GPIO_IDR_ID0_Pos)                       /*!< 0x00000001 */
#define GPIO_IDR_ID0                              GPIO_IDR_ID0_Msk                                  /*!< desc ID0 */
#define GPIO_IDR_ID1_Pos                          (1U)
#define GPIO_IDR_ID1_Msk                          (0x1UL << GPIO_IDR_ID1_Pos)                       /*!< 0x00000002 */
#define GPIO_IDR_ID1                              GPIO_IDR_ID1_Msk                                  /*!< desc ID1 */
#define GPIO_IDR_ID2_Pos                          (2U)
#define GPIO_IDR_ID2_Msk                          (0x1UL << GPIO_IDR_ID2_Pos)                       /*!< 0x00000004 */
#define GPIO_IDR_ID2                              GPIO_IDR_ID2_Msk                                  /*!< desc ID2 */
#define GPIO_IDR_ID3_Pos                          (3U)
#define GPIO_IDR_ID3_Msk                          (0x1UL << GPIO_IDR_ID3_Pos)                       /*!< 0x00000008 */
#define GPIO_IDR_ID3                              GPIO_IDR_ID3_Msk                                  /*!< desc ID3 */
#define GPIO_IDR_ID4_Pos                          (4U)
#define GPIO_IDR_ID4_Msk                          (0x1UL << GPIO_IDR_ID4_Pos)                       /*!< 0x00000010 */
#define GPIO_IDR_ID4                              GPIO_IDR_ID4_Msk                                  /*!< desc ID4 */
#define GPIO_IDR_ID5_Pos                          (5U)
#define GPIO_IDR_ID5_Msk                          (0x1UL << GPIO_IDR_ID5_Pos)                       /*!< 0x00000020 */
#define GPIO_IDR_ID5                              GPIO_IDR_ID5_Msk                                  /*!< desc ID5 */
#define GPIO_IDR_ID6_Pos                          (6U)
#define GPIO_IDR_ID6_Msk                          (0x1UL << GPIO_IDR_ID6_Pos)                       /*!< 0x00000040 */
#define GPIO_IDR_ID6                              GPIO_IDR_ID6_Msk                                  /*!< desc ID6 */
#define GPIO_IDR_ID7_Pos                          (7U)
#define GPIO_IDR_ID7_Msk                          (0x1UL << GPIO_IDR_ID7_Pos)                       /*!< 0x00000080 */
#define GPIO_IDR_ID7                              GPIO_IDR_ID7_Msk                                  /*!< desc ID7 */
#define GPIO_IDR_ID8_Pos                          (8U)
#define GPIO_IDR_ID8_Msk                          (0x1UL << GPIO_IDR_ID8_Pos)                       /*!< 0x00000100 */
#define GPIO_IDR_ID8                              GPIO_IDR_ID8_Msk                                  /*!< desc ID8 */
#define GPIO_IDR_ID9_Pos                          (9U)
#define GPIO_IDR_ID9_Msk                          (0x1UL << GPIO_IDR_ID9_Pos)                       /*!< 0x00000200 */
#define GPIO_IDR_ID9                              GPIO_IDR_ID9_Msk                                  /*!< desc ID9 */
#define GPIO_IDR_ID10_Pos                         (10U)
#define GPIO_IDR_ID10_Msk                         (0x1UL << GPIO_IDR_ID10_Pos)                      /*!< 0x00000400 */
#define GPIO_IDR_ID10                             GPIO_IDR_ID10_Msk                                 /*!< desc ID10 */
#define GPIO_IDR_ID11_Pos                         (11U)
#define GPIO_IDR_ID11_Msk                         (0x1UL << GPIO_IDR_ID11_Pos)                      /*!< 0x00000800 */
#define GPIO_IDR_ID11                             GPIO_IDR_ID11_Msk                                 /*!< desc ID11 */
#define GPIO_IDR_ID12_Pos                         (12U)
#define GPIO_IDR_ID12_Msk                         (0x1UL << GPIO_IDR_ID12_Pos)                      /*!< 0x00001000 */
#define GPIO_IDR_ID12                             GPIO_IDR_ID12_Msk                                 /*!< desc ID12 */
#define GPIO_IDR_ID13_Pos                         (13U)
#define GPIO_IDR_ID13_Msk                         (0x1UL << GPIO_IDR_ID13_Pos)                      /*!< 0x00002000 */
#define GPIO_IDR_ID13                             GPIO_IDR_ID13_Msk                                 /*!< desc ID13 */
#define GPIO_IDR_ID14_Pos                         (14U)
#define GPIO_IDR_ID14_Msk                         (0x1UL << GPIO_IDR_ID14_Pos)                      /*!< 0x00004000 */
#define GPIO_IDR_ID14                             GPIO_IDR_ID14_Msk                                 /*!< desc ID14 */
#define GPIO_IDR_ID15_Pos                         (15U)
#define GPIO_IDR_ID15_Msk                         (0x1UL << GPIO_IDR_ID15_Pos)                      /*!< 0x00008000 */
#define GPIO_IDR_ID15                             GPIO_IDR_ID15_Msk                                 /*!< desc ID15 */

/*!< GPIO_ODR */
#define GPIO_ODR_OD0_Pos                          (0U)
#define GPIO_ODR_OD0_Msk                          (0x1UL << GPIO_ODR_OD0_Pos)                       /*!< 0x00000001 */
#define GPIO_ODR_OD0                              GPIO_ODR_OD0_Msk                                  /*!< desc OD0 */
#define GPIO_ODR_OD1_Pos                          (1U)
#define GPIO_ODR_OD1_Msk                          (0x1UL << GPIO_ODR_OD1_Pos)                       /*!< 0x00000002 */
#define GPIO_ODR_OD1                              GPIO_ODR_OD1_Msk                                  /*!< desc OD1 */
#define GPIO_ODR_OD2_Pos                          (2U)
#define GPIO_ODR_OD2_Msk                          (0x1UL << GPIO_ODR_OD2_Pos)                       /*!< 0x00000004 */
#define GPIO_ODR_OD2                              GPIO_ODR_OD2_Msk                                  /*!< desc OD2 */
#define GPIO_ODR_OD3_Pos                          (3U)
#define GPIO_ODR_OD3_Msk                          (0x1UL << GPIO_ODR_OD3_Pos)                       /*!< 0x00000008 */
#define GPIO_ODR_OD3                              GPIO_ODR_OD3_Msk                                  /*!< desc OD3 */
#define GPIO_ODR_OD4_Pos                          (4U)
#define GPIO_ODR_OD4_Msk                          (0x1UL << GPIO_ODR_OD4_Pos)                       /*!< 0x00000010 */
#define GPIO_ODR_OD4                              GPIO_ODR_OD4_Msk                                  /*!< desc OD4 */
#define GPIO_ODR_OD5_Pos                          (5U)
#define GPIO_ODR_OD5_Msk                          (0x1UL << GPIO_ODR_OD5_Pos)                       /*!< 0x00000020 */
#define GPIO_ODR_OD5                              GPIO_ODR_OD5_Msk                                  /*!< desc OD5 */
#define GPIO_ODR_OD6_Pos                          (6U)
#define GPIO_ODR_OD6_Msk                          (0x1UL << GPIO_ODR_OD6_Pos)                       /*!< 0x00000040 */
#define GPIO_ODR_OD6                              GPIO_ODR_OD6_Msk                                  /*!< desc OD6 */
#define GPIO_ODR_OD7_Pos                          (7U)
#define GPIO_ODR_OD7_Msk                          (0x1UL << GPIO_ODR_OD7_Pos)                       /*!< 0x00000080 */
#define GPIO_ODR_OD7                              GPIO_ODR_OD7_Msk                                  /*!< desc OD7 */
#define GPIO_ODR_OD8_Pos                          (8U)
#define GPIO_ODR_OD8_Msk                          (0x1UL << GPIO_ODR_OD8_Pos)                       /*!< 0x00000100 */
#define GPIO_ODR_OD8                              GPIO_ODR_OD8_Msk                                  /*!< desc OD8 */
#define GPIO_ODR_OD9_Pos                          (9U)
#define GPIO_ODR_OD9_Msk                          (0x1UL << GPIO_ODR_OD9_Pos)                       /*!< 0x00000200 */
#define GPIO_ODR_OD9                              GPIO_ODR_OD9_Msk                                  /*!< desc OD9 */
#define GPIO_ODR_OD10_Pos                         (10U)
#define GPIO_ODR_OD10_Msk                         (0x1UL << GPIO_ODR_OD10_Pos)                      /*!< 0x00000400 */
#define GPIO_ODR_OD10                             GPIO_ODR_OD10_Msk                                 /*!< desc OD10 */
#define GPIO_ODR_OD11_Pos                         (11U)
#define GPIO_ODR_OD11_Msk                         (0x1UL << GPIO_ODR_OD11_Pos)                      /*!< 0x00000800 */
#define GPIO_ODR_OD11                             GPIO_ODR_OD11_Msk                                 /*!< desc OD11 */
#define GPIO_ODR_OD12_Pos                         (12U)
#define GPIO_ODR_OD12_Msk                         (0x1UL << GPIO_ODR_OD12_Pos)                      /*!< 0x00001000 */
#define GPIO_ODR_OD12                             GPIO_ODR_OD12_Msk                                 /*!< desc OD12 */
#define GPIO_ODR_OD13_Pos                         (13U)
#define GPIO_ODR_OD13_Msk                         (0x1UL << GPIO_ODR_OD13_Pos)                      /*!< 0x00002000 */
#define GPIO_ODR_OD13                             GPIO_ODR_OD13_Msk                                 /*!< desc OD13 */
#define GPIO_ODR_OD14_Pos                         (14U)
#define GPIO_ODR_OD14_Msk                         (0x1UL << GPIO_ODR_OD14_Pos)                      /*!< 0x00004000 */
#define GPIO_ODR_OD14                             GPIO_ODR_OD14_Msk                                 /*!< desc OD14 */
#define GPIO_ODR_OD15_Pos                         (15U)
#define GPIO_ODR_OD15_Msk                         (0x1UL << GPIO_ODR_OD15_Pos)                      /*!< 0x00008000 */
#define GPIO_ODR_OD15                             GPIO_ODR_OD15_Msk                                 /*!< desc OD15 */

/*!< GPIO_BSRR */
#define GPIO_BSRR_BS0_Pos                         (0U)
#define GPIO_BSRR_BS0_Msk                         (0x1UL << GPIO_BSRR_BS0_Pos)                      /*!< 0x00000001 */
#define GPIO_BSRR_BS0                             GPIO_BSRR_BS0_Msk                                 /*!< desc BS0 */
#define GPIO_BSRR_BS1_Pos                         (1U)
#define GPIO_BSRR_BS1_Msk                         (0x1UL << GPIO_BSRR_BS1_Pos)                      /*!< 0x00000002 */
#define GPIO_BSRR_BS1                             GPIO_BSRR_BS1_Msk                                 /*!< desc BS1 */
#define GPIO_BSRR_BS2_Pos                         (2U)
#define GPIO_BSRR_BS2_Msk                         (0x1UL << GPIO_BSRR_BS2_Pos)                      /*!< 0x00000004 */
#define GPIO_BSRR_BS2                             GPIO_BSRR_BS2_Msk                                 /*!< desc BS2 */
#define GPIO_BSRR_BS3_Pos                         (3U)
#define GPIO_BSRR_BS3_Msk                         (0x1UL << GPIO_BSRR_BS3_Pos)                      /*!< 0x00000008 */
#define GPIO_BSRR_BS3                             GPIO_BSRR_BS3_Msk                                 /*!< desc BS3 */
#define GPIO_BSRR_BS4_Pos                         (4U)
#define GPIO_BSRR_BS4_Msk                         (0x1UL << GPIO_BSRR_BS4_Pos)                      /*!< 0x00000010 */
#define GPIO_BSRR_BS4                             GPIO_BSRR_BS4_Msk                                 /*!< desc BS4 */
#define GPIO_BSRR_BS5_Pos                         (5U)
#define GPIO_BSRR_BS5_Msk                         (0x1UL << GPIO_BSRR_BS5_Pos)                      /*!< 0x00000020 */
#define GPIO_BSRR_BS5                             GPIO_BSRR_BS5_Msk                                 /*!< desc BS5 */
#define GPIO_BSRR_BS6_Pos                         (6U)
#define GPIO_BSRR_BS6_Msk                         (0x1UL << GPIO_BSRR_BS6_Pos)                      /*!< 0x00000040 */
#define GPIO_BSRR_BS6                             GPIO_BSRR_BS6_Msk                                 /*!< desc BS6 */
#define GPIO_BSRR_BS7_Pos                         (7U)
#define GPIO_BSRR_BS7_Msk                         (0x1UL << GPIO_BSRR_BS7_Pos)                      /*!< 0x00000080 */
#define GPIO_BSRR_BS7                             GPIO_BSRR_BS7_Msk                                 /*!< desc BS7 */
#define GPIO_BSRR_BS8_Pos                         (8U)
#define GPIO_BSRR_BS8_Msk                         (0x1UL << GPIO_BSRR_BS8_Pos)                      /*!< 0x00000100 */
#define GPIO_BSRR_BS8                             GPIO_BSRR_BS8_Msk                                 /*!< desc BS8 */
#define GPIO_BSRR_BS9_Pos                         (9U)
#define GPIO_BSRR_BS9_Msk                         (0x1UL << GPIO_BSRR_BS9_Pos)                      /*!< 0x00000200 */
#define GPIO_BSRR_BS9                             GPIO_BSRR_BS9_Msk                                 /*!< desc BS9 */
#define GPIO_BSRR_BS10_Pos                        (10U)
#define GPIO_BSRR_BS10_Msk                        (0x1UL << GPIO_BSRR_BS10_Pos)                     /*!< 0x00000400 */
#define GPIO_BSRR_BS10                            GPIO_BSRR_BS10_Msk                                /*!< desc BS10 */
#define GPIO_BSRR_BS11_Pos                        (11U)
#define GPIO_BSRR_BS11_Msk                        (0x1UL << GPIO_BSRR_BS11_Pos)                     /*!< 0x00000800 */
#define GPIO_BSRR_BS11                            GPIO_BSRR_BS11_Msk                                /*!< desc BS11 */
#define GPIO_BSRR_BS12_Pos                        (12U)
#define GPIO_BSRR_BS12_Msk                        (0x1UL << GPIO_BSRR_BS12_Pos)                     /*!< 0x00001000 */
#define GPIO_BSRR_BS12                            GPIO_BSRR_BS12_Msk                                /*!< desc BS12 */
#define GPIO_BSRR_BS13_Pos                        (13U)
#define GPIO_BSRR_BS13_Msk                        (0x1UL << GPIO_BSRR_BS13_Pos)                     /*!< 0x00002000 */
#define GPIO_BSRR_BS13                            GPIO_BSRR_BS13_Msk                                /*!< desc BS13 */
#define GPIO_BSRR_BS14_Pos                        (14U)
#define GPIO_BSRR_BS14_Msk                        (0x1UL << GPIO_BSRR_BS14_Pos)                     /*!< 0x00004000 */
#define GPIO_BSRR_BS14                            GPIO_BSRR_BS14_Msk                                /*!< desc BS14 */
#define GPIO_BSRR_BS15_Pos                        (15U)
#define GPIO_BSRR_BS15_Msk                        (0x1UL << GPIO_BSRR_BS15_Pos)                     /*!< 0x00008000 */
#define GPIO_BSRR_BS15                            GPIO_BSRR_BS15_Msk                                /*!< desc BS15 */
#define GPIO_BSRR_BR0_Pos                         (16U)
#define GPIO_BSRR_BR0_Msk                         (0x1UL << GPIO_BSRR_BR0_Pos)                      /*!< 0x00010000 */
#define GPIO_BSRR_BR0                             GPIO_BSRR_BR0_Msk                                 /*!< desc BR0 */
#define GPIO_BSRR_BR1_Pos                         (17U)
#define GPIO_BSRR_BR1_Msk                         (0x1UL << GPIO_BSRR_BR1_Pos)                      /*!< 0x00020000 */
#define GPIO_BSRR_BR1                             GPIO_BSRR_BR1_Msk                                 /*!< desc BR1 */
#define GPIO_BSRR_BR2_Pos                         (18U)
#define GPIO_BSRR_BR2_Msk                         (0x1UL << GPIO_BSRR_BR2_Pos)                      /*!< 0x00040000 */
#define GPIO_BSRR_BR2                             GPIO_BSRR_BR2_Msk                                 /*!< desc BR2 */
#define GPIO_BSRR_BR3_Pos                         (19U)
#define GPIO_BSRR_BR3_Msk                         (0x1UL << GPIO_BSRR_BR3_Pos)                      /*!< 0x00080000 */
#define GPIO_BSRR_BR3                             GPIO_BSRR_BR3_Msk                                 /*!< desc BR3 */
#define GPIO_BSRR_BR4_Pos                         (20U)
#define GPIO_BSRR_BR4_Msk                         (0x1UL << GPIO_BSRR_BR4_Pos)                      /*!< 0x00100000 */
#define GPIO_BSRR_BR4                             GPIO_BSRR_BR4_Msk                                 /*!< desc BR4 */
#define GPIO_BSRR_BR5_Pos                         (21U)
#define GPIO_BSRR_BR5_Msk                         (0x1UL << GPIO_BSRR_BR5_Pos)                      /*!< 0x00200000 */
#define GPIO_BSRR_BR5                             GPIO_BSRR_BR5_Msk                                 /*!< desc BR5 */
#define GPIO_BSRR_BR6_Pos                         (22U)
#define GPIO_BSRR_BR6_Msk                         (0x1UL << GPIO_BSRR_BR6_Pos)                      /*!< 0x00400000 */
#define GPIO_BSRR_BR6                             GPIO_BSRR_BR6_Msk                                 /*!< desc BR6 */
#define GPIO_BSRR_BR7_Pos                         (23U)
#define GPIO_BSRR_BR7_Msk                         (0x1UL << GPIO_BSRR_BR7_Pos)                      /*!< 0x00800000 */
#define GPIO_BSRR_BR7                             GPIO_BSRR_BR7_Msk                                 /*!< desc BR7 */
#define GPIO_BSRR_BR8_Pos                         (24U)
#define GPIO_BSRR_BR8_Msk                         (0x1UL << GPIO_BSRR_BR8_Pos)                      /*!< 0x01000000 */
#define GPIO_BSRR_BR8                             GPIO_BSRR_BR8_Msk                                 /*!< desc BR8 */
#define GPIO_BSRR_BR9_Pos                         (25U)
#define GPIO_BSRR_BR9_Msk                         (0x1UL << GPIO_BSRR_BR9_Pos)                      /*!< 0x02000000 */
#define GPIO_BSRR_BR9                             GPIO_BSRR_BR9_Msk                                 /*!< desc BR9 */
#define GPIO_BSRR_BR10_Pos                        (26U)
#define GPIO_BSRR_BR10_Msk                        (0x1UL << GPIO_BSRR_BR10_Pos)                     /*!< 0x04000000 */
#define GPIO_BSRR_BR10                            GPIO_BSRR_BR10_Msk                                /*!< desc BR10 */
#define GPIO_BSRR_BR11_Pos                        (27U)
#define GPIO_BSRR_BR11_Msk                        (0x1UL << GPIO_BSRR_BR11_Pos)                     /*!< 0x08000000 */
#define GPIO_BSRR_BR11                            GPIO_BSRR_BR11_Msk                                /*!< desc BR11 */
#define GPIO_BSRR_BR12_Pos                        (28U)
#define GPIO_BSRR_BR12_Msk                        (0x1UL << GPIO_BSRR_BR12_Pos)                     /*!< 0x10000000 */
#define GPIO_BSRR_BR12                            GPIO_BSRR_BR12_Msk                                /*!< desc BR12 */
#define GPIO_BSRR_BR13_Pos                        (29U)
#define GPIO_BSRR_BR13_Msk                        (0x1UL << GPIO_BSRR_BR13_Pos)                     /*!< 0x20000000 */
#define GPIO_BSRR_BR13                            GPIO_BSRR_BR13_Msk                                /*!< desc BR13 */
#define GPIO_BSRR_BR14_Pos                        (30U)
#define GPIO_BSRR_BR14_Msk                        (0x1UL << GPIO_BSRR_BR14_Pos)                     /*!< 0x40000000 */
#define GPIO_BSRR_BR14                            GPIO_BSRR_BR14_Msk                                /*!< desc BR14 */
#define GPIO_BSRR_BR15_Pos                        (31U)
#define GPIO_BSRR_BR15_Msk                        (0x1UL << GPIO_BSRR_BR15_Pos)                     /*!< 0x80000000 */
#define GPIO_BSRR_BR15                            GPIO_BSRR_BR15_Msk                                /*!< desc BR15 */

/*!< GPIO_LCKR */
#define GPIO_LCKR_LCK0_Pos                        (0U)
#define GPIO_LCKR_LCK0_Msk                        (0x1UL << GPIO_LCKR_LCK0_Pos)                     /*!< 0x00000001 */
#define GPIO_LCKR_LCK0                            GPIO_LCKR_LCK0_Msk                                /*!< desc LCK0 */
#define GPIO_LCKR_LCK1_Pos                        (1U)
#define GPIO_LCKR_LCK1_Msk                        (0x1UL << GPIO_LCKR_LCK1_Pos)                     /*!< 0x00000002 */
#define GPIO_LCKR_LCK1                            GPIO_LCKR_LCK1_Msk                                /*!< desc LCK1 */
#define GPIO_LCKR_LCK2_Pos                        (2U)
#define GPIO_LCKR_LCK2_Msk                        (0x1UL << GPIO_LCKR_LCK2_Pos)                     /*!< 0x00000004 */
#define GPIO_LCKR_LCK2                            GPIO_LCKR_LCK2_Msk                                /*!< desc LCK2 */
#define GPIO_LCKR_LCK3_Pos                        (3U)
#define GPIO_LCKR_LCK3_Msk                        (0x1UL << GPIO_LCKR_LCK3_Pos)                     /*!< 0x00000008 */
#define GPIO_LCKR_LCK3                            GPIO_LCKR_LCK3_Msk                                /*!< desc LCK3 */
#define GPIO_LCKR_LCK4_Pos                        (4U)
#define GPIO_LCKR_LCK4_Msk                        (0x1UL << GPIO_LCKR_LCK4_Pos)                     /*!< 0x00000010 */
#define GPIO_LCKR_LCK4                            GPIO_LCKR_LCK4_Msk                                /*!< desc LCK4 */
#define GPIO_LCKR_LCK5_Pos                        (5U)
#define GPIO_LCKR_LCK5_Msk                        (0x1UL << GPIO_LCKR_LCK5_Pos)                     /*!< 0x00000020 */
#define GPIO_LCKR_LCK5                            GPIO_LCKR_LCK5_Msk                                /*!< desc LCK5 */
#define GPIO_LCKR_LCK6_Pos                        (6U)
#define GPIO_LCKR_LCK6_Msk                        (0x1UL << GPIO_LCKR_LCK6_Pos)                     /*!< 0x00000040 */
#define GPIO_LCKR_LCK6                            GPIO_LCKR_LCK6_Msk                                /*!< desc LCK6 */
#define GPIO_LCKR_LCK7_Pos                        (7U)
#define GPIO_LCKR_LCK7_Msk                        (0x1UL << GPIO_LCKR_LCK7_Pos)                     /*!< 0x00000080 */
#define GPIO_LCKR_LCK7                            GPIO_LCKR_LCK7_Msk                                /*!< desc LCK7 */
#define GPIO_LCKR_LCK8_Pos                        (8U)
#define GPIO_LCKR_LCK8_Msk                        (0x1UL << GPIO_LCKR_LCK8_Pos)                     /*!< 0x00000100 */
#define GPIO_LCKR_LCK8                            GPIO_LCKR_LCK8_Msk                                /*!< desc LCK8 */
#define GPIO_LCKR_LCK9_Pos                        (9U)
#define GPIO_LCKR_LCK9_Msk                        (0x1UL << GPIO_LCKR_LCK9_Pos)                     /*!< 0x00000200 */
#define GPIO_LCKR_LCK9                            GPIO_LCKR_LCK9_Msk                                /*!< desc LCK9 */
#define GPIO_LCKR_LCK10_Pos                       (10U)
#define GPIO_LCKR_LCK10_Msk                       (0x1UL << GPIO_LCKR_LCK10_Pos)                    /*!< 0x00000400 */
#define GPIO_LCKR_LCK10                           GPIO_LCKR_LCK10_Msk                               /*!< desc LCK10 */
#define GPIO_LCKR_LCK11_Pos                       (11U)
#define GPIO_LCKR_LCK11_Msk                       (0x1UL << GPIO_LCKR_LCK11_Pos)                    /*!< 0x00000800 */
#define GPIO_LCKR_LCK11                           GPIO_LCKR_LCK11_Msk                               /*!< desc LCK11 */
#define GPIO_LCKR_LCK12_Pos                       (12U)
#define GPIO_LCKR_LCK12_Msk                       (0x1UL << GPIO_LCKR_LCK12_Pos)                    /*!< 0x00001000 */
#define GPIO_LCKR_LCK12                           GPIO_LCKR_LCK12_Msk                               /*!< desc LCK12 */
#define GPIO_LCKR_LCK13_Pos                       (13U)
#define GPIO_LCKR_LCK13_Msk                       (0x1UL << GPIO_LCKR_LCK13_Pos)                    /*!< 0x00002000 */
#define GPIO_LCKR_LCK13                           GPIO_LCKR_LCK13_Msk                               /*!< desc LCK13 */
#define GPIO_LCKR_LCK14_Pos                       (14U)
#define GPIO_LCKR_LCK14_Msk                       (0x1UL << GPIO_LCKR_LCK14_Pos)                    /*!< 0x00004000 */
#define GPIO_LCKR_LCK14                           GPIO_LCKR_LCK14_Msk                               /*!< desc LCK14 */
#define GPIO_LCKR_LCK15_Pos                       (15U)
#define GPIO_LCKR_LCK15_Msk                       (0x1UL << GPIO_LCKR_LCK15_Pos)                    /*!< 0x00008000 */
#define GPIO_LCKR_LCK15                           GPIO_LCKR_LCK15_Msk                               /*!< desc LCK15 */
#define GPIO_LCKR_LCKK_Pos                        (16U)
#define GPIO_LCKR_LCKK_Msk                        (0x1UL << GPIO_LCKR_LCKK_Pos)                     /*!< 0x00010000 */
#define GPIO_LCKR_LCKK                            GPIO_LCKR_LCKK_Msk                                /*!< desc LCKK */

/*!< GPIO_AFRL */
#define GPIO_AFRL_AFSEL0_Pos                      (0U)
#define GPIO_AFRL_AFSEL0_Msk                      (0xFUL << GPIO_AFRL_AFSEL0_Pos)                   /*!< 0x0000000F */
#define GPIO_AFRL_AFSEL0                          GPIO_AFRL_AFSEL0_Msk                              /*!< AFSEL0[3:0] bits (desc AFSEL0) */
#define GPIO_AFRL_AFSEL0_0                        (0x1UL << GPIO_AFRL_AFSEL0_Pos)                   /*!< 0x00000001 */
#define GPIO_AFRL_AFSEL0_1                        (0x2UL << GPIO_AFRL_AFSEL0_Pos)                   /*!< 0x00000002 */
#define GPIO_AFRL_AFSEL0_2                        (0x4UL << GPIO_AFRL_AFSEL0_Pos)                   /*!< 0x00000004 */
#define GPIO_AFRL_AFSEL0_3                        (0x8UL << GPIO_AFRL_AFSEL0_Pos)                   /*!< 0x00000008 */

#define GPIO_AFRL_AFSEL1_Pos                      (4U)
#define GPIO_AFRL_AFSEL1_Msk                      (0xFUL << GPIO_AFRL_AFSEL1_Pos)                   /*!< 0x000000F0 */
#define GPIO_AFRL_AFSEL1                          GPIO_AFRL_AFSEL1_Msk                              /*!< AFSEL1[7:4] bits (desc AFSEL1) */
#define GPIO_AFRL_AFSEL1_0                        (0x1UL << GPIO_AFRL_AFSEL1_Pos)                   /*!< 0x00000010 */
#define GPIO_AFRL_AFSEL1_1                        (0x2UL << GPIO_AFRL_AFSEL1_Pos)                   /*!< 0x00000020 */
#define GPIO_AFRL_AFSEL1_2                        (0x4UL << GPIO_AFRL_AFSEL1_Pos)                   /*!< 0x00000040 */
#define GPIO_AFRL_AFSEL1_3                        (0x8UL << GPIO_AFRL_AFSEL1_Pos)                   /*!< 0x00000080 */

#define GPIO_AFRL_AFSEL2_Pos                      (8U)
#define GPIO_AFRL_AFSEL2_Msk                      (0xFUL << GPIO_AFRL_AFSEL2_Pos)                   /*!< 0x00000F00 */
#define GPIO_AFRL_AFSEL2                          GPIO_AFRL_AFSEL2_Msk                              /*!< AFSEL2[11:8] bits (desc AFSEL2) */
#define GPIO_AFRL_AFSEL2_0                        (0x1UL << GPIO_AFRL_AFSEL2_Pos)                   /*!< 0x00000100 */
#define GPIO_AFRL_AFSEL2_1                        (0x2UL << GPIO_AFRL_AFSEL2_Pos)                   /*!< 0x00000200 */
#define GPIO_AFRL_AFSEL2_2                        (0x4UL << GPIO_AFRL_AFSEL2_Pos)                   /*!< 0x00000400 */
#define GPIO_AFRL_AFSEL2_3                        (0x8UL << GPIO_AFRL_AFSEL2_Pos)                   /*!< 0x00000800 */

#define GPIO_AFRL_AFSEL3_Pos                      (12U)
#define GPIO_AFRL_AFSEL3_Msk                      (0xFUL << GPIO_AFRL_AFSEL3_Pos)                   /*!< 0x0000F000 */
#define GPIO_AFRL_AFSEL3                          GPIO_AFRL_AFSEL3_Msk                              /*!< AFSEL3[15:12] bits (desc AFSEL3) */
#define GPIO_AFRL_AFSEL3_0                        (0x1UL << GPIO_AFRL_AFSEL3_Pos)                   /*!< 0x00001000 */
#define GPIO_AFRL_AFSEL3_1                        (0x2UL << GPIO_AFRL_AFSEL3_Pos)                   /*!< 0x00002000 */
#define GPIO_AFRL_AFSEL3_2                        (0x4UL << GPIO_AFRL_AFSEL3_Pos)                   /*!< 0x00004000 */
#define GPIO_AFRL_AFSEL3_3                        (0x8UL << GPIO_AFRL_AFSEL3_Pos)                   /*!< 0x00008000 */

#define GPIO_AFRL_AFSEL4_Pos                      (16U)
#define GPIO_AFRL_AFSEL4_Msk                      (0xFUL << GPIO_AFRL_AFSEL4_Pos)                   /*!< 0x000F0000 */
#define GPIO_AFRL_AFSEL4                          GPIO_AFRL_AFSEL4_Msk                              /*!< AFSEL4[19:16] bits (desc AFSEL4) */
#define GPIO_AFRL_AFSEL4_0                        (0x1UL << GPIO_AFRL_AFSEL4_Pos)                   /*!< 0x00010000 */
#define GPIO_AFRL_AFSEL4_1                        (0x2UL << GPIO_AFRL_AFSEL4_Pos)                   /*!< 0x00020000 */
#define GPIO_AFRL_AFSEL4_2                        (0x4UL << GPIO_AFRL_AFSEL4_Pos)                   /*!< 0x00040000 */
#define GPIO_AFRL_AFSEL4_3                        (0x8UL << GPIO_AFRL_AFSEL4_Pos)                   /*!< 0x00080000 */

#define GPIO_AFRL_AFSEL5_Pos                      (20U)
#define GPIO_AFRL_AFSEL5_Msk                      (0xFUL << GPIO_AFRL_AFSEL5_Pos)                   /*!< 0x00F00000 */
#define GPIO_AFRL_AFSEL5                          GPIO_AFRL_AFSEL5_Msk                              /*!< AFSEL5[23:20] bits (desc AFSEL5) */
#define GPIO_AFRL_AFSEL5_0                        (0x1UL << GPIO_AFRL_AFSEL5_Pos)                   /*!< 0x00100000 */
#define GPIO_AFRL_AFSEL5_1                        (0x2UL << GPIO_AFRL_AFSEL5_Pos)                   /*!< 0x00200000 */
#define GPIO_AFRL_AFSEL5_2                        (0x4UL << GPIO_AFRL_AFSEL5_Pos)                   /*!< 0x00400000 */
#define GPIO_AFRL_AFSEL5_3                        (0x8UL << GPIO_AFRL_AFSEL5_Pos)                   /*!< 0x00800000 */

#define GPIO_AFRL_AFSEL6_Pos                      (24U)
#define GPIO_AFRL_AFSEL6_Msk                      (0xFUL << GPIO_AFRL_AFSEL6_Pos)                   /*!< 0x0F000000 */
#define GPIO_AFRL_AFSEL6                          GPIO_AFRL_AFSEL6_Msk                              /*!< AFSEL6[27:24] bits (desc AFSEL6) */
#define GPIO_AFRL_AFSEL6_0                        (0x1UL << GPIO_AFRL_AFSEL6_Pos)                   /*!< 0x01000000 */
#define GPIO_AFRL_AFSEL6_1                        (0x2UL << GPIO_AFRL_AFSEL6_Pos)                   /*!< 0x02000000 */
#define GPIO_AFRL_AFSEL6_2                        (0x4UL << GPIO_AFRL_AFSEL6_Pos)                   /*!< 0x04000000 */
#define GPIO_AFRL_AFSEL6_3                        (0x8UL << GPIO_AFRL_AFSEL6_Pos)                   /*!< 0x08000000 */

#define GPIO_AFRL_AFSEL7_Pos                      (28U)
#define GPIO_AFRL_AFSEL7_Msk                      (0xFUL << GPIO_AFRL_AFSEL7_Pos)                   /*!< 0xF0000000 */
#define GPIO_AFRL_AFSEL7                          GPIO_AFRL_AFSEL7_Msk                              /*!< AFSEL7[31:28] bits (desc AFSEL7) */
#define GPIO_AFRL_AFSEL7_0                        (0x1UL << GPIO_AFRL_AFSEL7_Pos)                   /*!< 0x10000000 */
#define GPIO_AFRL_AFSEL7_1                        (0x2UL << GPIO_AFRL_AFSEL7_Pos)                   /*!< 0x20000000 */
#define GPIO_AFRL_AFSEL7_2                        (0x4UL << GPIO_AFRL_AFSEL7_Pos)                   /*!< 0x40000000 */
#define GPIO_AFRL_AFSEL7_3                        (0x8UL << GPIO_AFRL_AFSEL7_Pos)                   /*!< 0x80000000 */

/*!< GPIO_AFRH */
#define GPIO_AFRH_AFSEL8_Pos                      (0U)
#define GPIO_AFRH_AFSEL8_Msk                      (0xFUL << GPIO_AFRH_AFSEL8_Pos)                   /*!< 0x0000000F */
#define GPIO_AFRH_AFSEL8                          GPIO_AFRH_AFSEL8_Msk                              /*!< AFSEL8[3:0] bits (desc AFSEL8) */
#define GPIO_AFRH_AFSEL8_0                        (0x1UL << GPIO_AFRH_AFSEL8_Pos)                   /*!< 0x00000001 */
#define GPIO_AFRH_AFSEL8_1                        (0x2UL << GPIO_AFRH_AFSEL8_Pos)                   /*!< 0x00000002 */
#define GPIO_AFRH_AFSEL8_2                        (0x4UL << GPIO_AFRH_AFSEL8_Pos)                   /*!< 0x00000004 */
#define GPIO_AFRH_AFSEL8_3                        (0x8UL << GPIO_AFRH_AFSEL8_Pos)                   /*!< 0x00000008 */

#define GPIO_AFRH_AFSEL9_Pos                      (4U)
#define GPIO_AFRH_AFSEL9_Msk                      (0xFUL << GPIO_AFRH_AFSEL9_Pos)                   /*!< 0x000000F0 */
#define GPIO_AFRH_AFSEL9                          GPIO_AFRH_AFSEL9_Msk                              /*!< AFSEL9[7:4] bits (desc AFSEL9) */
#define GPIO_AFRH_AFSEL9_0                        (0x1UL << GPIO_AFRH_AFSEL9_Pos)                   /*!< 0x00000010 */
#define GPIO_AFRH_AFSEL9_1                        (0x2UL << GPIO_AFRH_AFSEL9_Pos)                   /*!< 0x00000020 */
#define GPIO_AFRH_AFSEL9_2                        (0x4UL << GPIO_AFRH_AFSEL9_Pos)                   /*!< 0x00000040 */
#define GPIO_AFRH_AFSEL9_3                        (0x8UL << GPIO_AFRH_AFSEL9_Pos)                   /*!< 0x00000080 */

#define GPIO_AFRH_AFSEL10_Pos                     (8U)
#define GPIO_AFRH_AFSEL10_Msk                     (0xFUL << GPIO_AFRH_AFSEL10_Pos)                  /*!< 0x00000F00 */
#define GPIO_AFRH_AFSEL10                         GPIO_AFRH_AFSEL10_Msk                             /*!< AFSEL10[11:8] bits (desc AFSEL10) */
#define GPIO_AFRH_AFSEL10_0                       (0x1UL << GPIO_AFRH_AFSEL10_Pos)                  /*!< 0x00000100 */
#define GPIO_AFRH_AFSEL10_1                       (0x2UL << GPIO_AFRH_AFSEL10_Pos)                  /*!< 0x00000200 */
#define GPIO_AFRH_AFSEL10_2                       (0x4UL << GPIO_AFRH_AFSEL10_Pos)                  /*!< 0x00000400 */
#define GPIO_AFRH_AFSEL10_3                       (0x8UL << GPIO_AFRH_AFSEL10_Pos)                  /*!< 0x00000800 */

#define GPIO_AFRH_AFSEL11_Pos                     (12U)
#define GPIO_AFRH_AFSEL11_Msk                     (0xFUL << GPIO_AFRH_AFSEL11_Pos)                  /*!< 0x0000F000 */
#define GPIO_AFRH_AFSEL11                         GPIO_AFRH_AFSEL11_Msk                             /*!< AFSEL11[15:12] bits (desc AFSEL11) */
#define GPIO_AFRH_AFSEL11_0                       (0x1UL << GPIO_AFRH_AFSEL11_Pos)                  /*!< 0x00001000 */
#define GPIO_AFRH_AFSEL11_1                       (0x2UL << GPIO_AFRH_AFSEL11_Pos)                  /*!< 0x00002000 */
#define GPIO_AFRH_AFSEL11_2                       (0x4UL << GPIO_AFRH_AFSEL11_Pos)                  /*!< 0x00004000 */
#define GPIO_AFRH_AFSEL11_3                       (0x8UL << GPIO_AFRH_AFSEL11_Pos)                  /*!< 0x00008000 */

#define GPIO_AFRH_AFSEL12_Pos                     (16U)
#define GPIO_AFRH_AFSEL12_Msk                     (0xFUL << GPIO_AFRH_AFSEL12_Pos)                  /*!< 0x000F0000 */
#define GPIO_AFRH_AFSEL12                         GPIO_AFRH_AFSEL12_Msk                             /*!< AFSEL12[19:16] bits (desc AFSEL12) */
#define GPIO_AFRH_AFSEL12_0                       (0x1UL << GPIO_AFRH_AFSEL12_Pos)                  /*!< 0x00010000 */
#define GPIO_AFRH_AFSEL12_1                       (0x2UL << GPIO_AFRH_AFSEL12_Pos)                  /*!< 0x00020000 */
#define GPIO_AFRH_AFSEL12_2                       (0x4UL << GPIO_AFRH_AFSEL12_Pos)                  /*!< 0x00040000 */
#define GPIO_AFRH_AFSEL12_3                       (0x8UL << GPIO_AFRH_AFSEL12_Pos)                  /*!< 0x00080000 */

#define GPIO_AFRH_AFSEL13_Pos                     (20U)
#define GPIO_AFRH_AFSEL13_Msk                     (0xFUL << GPIO_AFRH_AFSEL13_Pos)                  /*!< 0x00F00000 */
#define GPIO_AFRH_AFSEL13                         GPIO_AFRH_AFSEL13_Msk                             /*!< AFSEL13[23:20] bits (desc AFSEL13) */
#define GPIO_AFRH_AFSEL13_0                       (0x1UL << GPIO_AFRH_AFSEL13_Pos)                  /*!< 0x00100000 */
#define GPIO_AFRH_AFSEL13_1                       (0x2UL << GPIO_AFRH_AFSEL13_Pos)                  /*!< 0x00200000 */
#define GPIO_AFRH_AFSEL13_2                       (0x4UL << GPIO_AFRH_AFSEL13_Pos)                  /*!< 0x00400000 */
#define GPIO_AFRH_AFSEL13_3                       (0x8UL << GPIO_AFRH_AFSEL13_Pos)                  /*!< 0x00800000 */

#define GPIO_AFRH_AFSEL14_Pos                     (24U)
#define GPIO_AFRH_AFSEL14_Msk                     (0xFUL << GPIO_AFRH_AFSEL14_Pos)                  /*!< 0x0F000000 */
#define GPIO_AFRH_AFSEL14                         GPIO_AFRH_AFSEL14_Msk                             /*!< AFSEL14[27:24] bits (desc AFSEL14) */
#define GPIO_AFRH_AFSEL14_0                       (0x1UL << GPIO_AFRH_AFSEL14_Pos)                  /*!< 0x01000000 */
#define GPIO_AFRH_AFSEL14_1                       (0x2UL << GPIO_AFRH_AFSEL14_Pos)                  /*!< 0x02000000 */
#define GPIO_AFRH_AFSEL14_2                       (0x4UL << GPIO_AFRH_AFSEL14_Pos)                  /*!< 0x04000000 */
#define GPIO_AFRH_AFSEL14_3                       (0x8UL << GPIO_AFRH_AFSEL14_Pos)                  /*!< 0x08000000 */

#define GPIO_AFRH_AFSEL15_Pos                     (28U)
#define GPIO_AFRH_AFSEL15_Msk                     (0xFUL << GPIO_AFRH_AFSEL15_Pos)                  /*!< 0xF0000000 */
#define GPIO_AFRH_AFSEL15                         GPIO_AFRH_AFSEL15_Msk                             /*!< AFSEL15[31:28] bits (desc AFSEL15) */
#define GPIO_AFRH_AFSEL15_0                       (0x1UL << GPIO_AFRH_AFSEL15_Pos)                  /*!< 0x10000000 */
#define GPIO_AFRH_AFSEL15_1                       (0x2UL << GPIO_AFRH_AFSEL15_Pos)                  /*!< 0x20000000 */
#define GPIO_AFRH_AFSEL15_2                       (0x4UL << GPIO_AFRH_AFSEL15_Pos)                  /*!< 0x40000000 */
#define GPIO_AFRH_AFSEL15_3                       (0x8UL << GPIO_AFRH_AFSEL15_Pos)                  /*!< 0x80000000 */

/*!< GPIO_BRR */
#define GPIO_BRR_BR0_Pos                          (0U)
#define GPIO_BRR_BR0_Msk                          (0x1UL << GPIO_BRR_BR0_Pos)                       /*!< 0x00000001 */
#define GPIO_BRR_BR0                              GPIO_BRR_BR0_Msk                                  /*!< desc BR0 */
#define GPIO_BRR_BR1_Pos                          (1U)
#define GPIO_BRR_BR1_Msk                          (0x1UL << GPIO_BRR_BR1_Pos)                       /*!< 0x00000002 */
#define GPIO_BRR_BR1                              GPIO_BRR_BR1_Msk                                  /*!< desc BR1 */
#define GPIO_BRR_BR2_Pos                          (2U)
#define GPIO_BRR_BR2_Msk                          (0x1UL << GPIO_BRR_BR2_Pos)                       /*!< 0x00000004 */
#define GPIO_BRR_BR2                              GPIO_BRR_BR2_Msk                                  /*!< desc BR2 */
#define GPIO_BRR_BR3_Pos                          (3U)
#define GPIO_BRR_BR3_Msk                          (0x1UL << GPIO_BRR_BR3_Pos)                       /*!< 0x00000008 */
#define GPIO_BRR_BR3                              GPIO_BRR_BR3_Msk                                  /*!< desc BR3 */
#define GPIO_BRR_BR4_Pos                          (4U)
#define GPIO_BRR_BR4_Msk                          (0x1UL << GPIO_BRR_BR4_Pos)                       /*!< 0x00000010 */
#define GPIO_BRR_BR4                              GPIO_BRR_BR4_Msk                                  /*!< desc BR4 */
#define GPIO_BRR_BR5_Pos                          (5U)
#define GPIO_BRR_BR5_Msk                          (0x1UL << GPIO_BRR_BR5_Pos)                       /*!< 0x00000020 */
#define GPIO_BRR_BR5                              GPIO_BRR_BR5_Msk                                  /*!< desc BR5 */
#define GPIO_BRR_BR6_Pos                          (6U)
#define GPIO_BRR_BR6_Msk                          (0x1UL << GPIO_BRR_BR6_Pos)                       /*!< 0x00000040 */
#define GPIO_BRR_BR6                              GPIO_BRR_BR6_Msk                                  /*!< desc BR6 */
#define GPIO_BRR_BR7_Pos                          (7U)
#define GPIO_BRR_BR7_Msk                          (0x1UL << GPIO_BRR_BR7_Pos)                       /*!< 0x00000080 */
#define GPIO_BRR_BR7                              GPIO_BRR_BR7_Msk                                  /*!< desc BR7 */
#define GPIO_BRR_BR8_Pos                          (8U)
#define GPIO_BRR_BR8_Msk                          (0x1UL << GPIO_BRR_BR8_Pos)                       /*!< 0x00000100 */
#define GPIO_BRR_BR8                              GPIO_BRR_BR8_Msk                                  /*!< desc BR8 */
#define GPIO_BRR_BR9_Pos                          (9U)
#define GPIO_BRR_BR9_Msk                          (0x1UL << GPIO_BRR_BR9_Pos)                       /*!< 0x00000200 */
#define GPIO_BRR_BR9                              GPIO_BRR_BR9_Msk                                  /*!< desc BR9 */
#define GPIO_BRR_BR10_Pos                         (10U)
#define GPIO_BRR_BR10_Msk                         (0x1UL << GPIO_BRR_BR10_Pos)                      /*!< 0x00000400 */
#define GPIO_BRR_BR10                             GPIO_BRR_BR10_Msk                                 /*!< desc BR10 */
#define GPIO_BRR_BR11_Pos                         (11U)
#define GPIO_BRR_BR11_Msk                         (0x1UL << GPIO_BRR_BR11_Pos)                      /*!< 0x00000800 */
#define GPIO_BRR_BR11                             GPIO_BRR_BR11_Msk                                 /*!< desc BR11 */
#define GPIO_BRR_BR12_Pos                         (12U)
#define GPIO_BRR_BR12_Msk                         (0x1UL << GPIO_BRR_BR12_Pos)                      /*!< 0x00001000 */
#define GPIO_BRR_BR12                             GPIO_BRR_BR12_Msk                                 /*!< desc BR12 */
#define GPIO_BRR_BR13_Pos                         (13U)
#define GPIO_BRR_BR13_Msk                         (0x1UL << GPIO_BRR_BR13_Pos)                      /*!< 0x00002000 */
#define GPIO_BRR_BR13                             GPIO_BRR_BR13_Msk                                 /*!< desc BR13 */
#define GPIO_BRR_BR14_Pos                         (14U)
#define GPIO_BRR_BR14_Msk                         (0x1UL << GPIO_BRR_BR14_Pos)                      /*!< 0x00004000 */
#define GPIO_BRR_BR14                             GPIO_BRR_BR14_Msk                                 /*!< desc BR14 */
#define GPIO_BRR_BR15_Pos                         (15U)
#define GPIO_BRR_BR15_Msk                         (0x1UL << GPIO_BRR_BR15_Pos)                      /*!< 0x00008000 */
#define GPIO_BRR_BR15                             GPIO_BRR_BR15_Msk                                 /*!< desc BR15 */

/********************************************************************************************************************/
/********************************* OPA ******************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for OPA_CSR register *******************************************/
#define OPA_CSR_OPAEN_Pos                      (0U)
#define OPA_CSR_OPAEN_Msk                      (0x1UL<<OPA_CSR_OPAEN_Pos)                     /*!< 0x00000001 */
#define OPA_CSR_OPAEN                          OPA_CSR_OPAEN_Msk                              /*!< OPA Enable */
#define OPA_CSR_OPA_CMP_CR_Pos                 (1U)
#define OPA_CSR_OPA_CMP_CR_Msk                 (0x1UL<<OPA_CSR_OPA_CMP_CR_Pos)                /*!< 0x00000002 */
#define OPA_CSR_OPA_CMP_CR                     OPA_CSR_OPA_CMP_CR_Msk                         /*!< OPA2 or COMP selection */
#define OPA_CSR_OPAINTOEN_Pos                  (8U)
#define OPA_CSR_OPAINTOEN_Msk                  (0x1UL<<OPA_CSR_OPAINTOEN_Pos)                 /*!< 0x00000100 */
#define OPA_CSR_OPAINTOEN                      OPA_CSR_OPAINTOEN_Msk                          /*!< OPA internal output enable */
#define OPA_CSR_OPA_CMP_OUT_Pos                (30U)
#define OPA_CSR_OPA_CMP_OUT_Msk                (0x1UL<<OPA_CSR_OPA_CMP_OUT_Pos)               /*!< 0x40000000 */
#define OPA_CSR_OPA_CMP_OUT                    OPA_CSR_OPA_CMP_OUT_Msk                        /*!< OPA2 change COMP output level */
#define OPA_CSR_LOCK_Pos                       (31U)
#define OPA_CSR_LOCK_Msk                       (0x1UL<<OPA_CSR_LOCK_Pos)                      /*!< 0x80000000 */
#define OPA_CSR_LOCK                           OPA_CSR_LOCK_Msk                               /*!< OPA_CSR register Lock */

/*********************************** Bit definition for OPA_FR register ******************************************/
#define OPA_FR_FLTEN_Pos                       (0U)
#define OPA_FR_FLTEN_Msk                       (0x1UL<<OPA_FR_FLTEN_Pos)                      /*!< 0x00000001 */
#define OPA_FR_FLTEN                           OPA_FR_FLTEN_Msk                               /*!< OPA2 Digital Filter Enable */
#define OPA_FR_FLTCNT_Pos                      (16U)
#define OPA_FR_FLTCNT_Msk                      (0xFFFFUL<<OPA_FR_FLTCNT_Pos)                  /*!< 0xFFFF0000 */
#define OPA_FR_FLTCNT                          OPA_FR_FLTCNT_Msk                              /*!< OPA2 Sample Filter Counter */

/********************************** Bit definition for OPA_FINT register *****************************************/
#define OPA_INTR_INTEN_Pos                     (0U)
#define OPA_INTR_INTEN_Msk                     (0x1UL<<OPA_INTR_INTEN_Pos)                    /*!< 0x00000001 */
#define OPA_INTR_INTEN                         OPA_INTR_INTEN_Msk                             /*!< OPA2 Interrupt Enable */
#define OPA_INTR_INTIF_Pos                     (1U)
#define OPA_INTR_INTIF_Msk                     (0x1UL<<OPA_INTR_INTIF_Pos)                    /*!< 0x00000002 */
#define OPA_INTR_INTIF                         OPA_INTR_INTIF_Msk                             /*!< OPA2 Interrupt Flag */
#define OPA_INTR_CINTIF_Pos                    (2U)
#define OPA_INTR_CINTIF_Msk                    (0x1UL<<OPA_INTR_CINTIF_Pos)                   /*!< 0x00000004 */
#define OPA_INTR_CINTIF                        OPA_INTR_CINTIF_Msk                            /*!< OPA2 Interrupt Flag Clear */

/********************************************************************************************************************/
/********************************* I2C ******************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for I2C_CR1 register **********************************************/
#define I2C_CR1_PE_Pos                            (0U)
#define I2C_CR1_PE_Msk                            (0x1UL<<I2C_CR1_PE_Pos)                           /*!< 0x00000001 */
#define I2C_CR1_PE                                I2C_CR1_PE_Msk                                    /*!< Peripheral enable */
#define I2C_CR1_SMBUS_Pos                         (1U)
#define I2C_CR1_SMBUS_Msk                         (0x1UL<<I2C_CR1_SMBUS_Pos)                        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                             I2C_CR1_SMBUS_Msk                                 /*!< SMBus mode */
#define I2C_CR1_WUPEN_Pos                         (2U)
#define I2C_CR1_WUPEN_Msk                         (0x1UL<<I2C_CR1_WUPEN_Pos)                        /*!< 0x00000004 */
#define I2C_CR1_WUPEN                             I2C_CR1_WUPEN_Msk                                 /*!< Wakeup from Stop mode enable */
#define I2C_CR1_SMBTYPE_Pos                       (3U)
#define I2C_CR1_SMBTYPE_Msk                       (0x1UL<<I2C_CR1_SMBTYPE_Pos)                      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                           I2C_CR1_SMBTYPE_Msk                               /*!< SMBus type */
#define I2C_CR1_ENARP_Pos                         (4U)
#define I2C_CR1_ENARP_Msk                         (0x1UL<<I2C_CR1_ENARP_Pos)                        /*!< 0x00000010 */
#define I2C_CR1_ENARP                             I2C_CR1_ENARP_Msk                                 /*!< ARP enable */
#define I2C_CR1_ENPEC_Pos                         (5U)
#define I2C_CR1_ENPEC_Msk                         (0x1UL<<I2C_CR1_ENPEC_Pos)                        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                             I2C_CR1_ENPEC_Msk                                 /*!< PEC enable */
#define I2C_CR1_ENGC_Pos                          (6U)
#define I2C_CR1_ENGC_Msk                          (0x1UL<<I2C_CR1_ENGC_Pos)                         /*!< 0x00000040 */
#define I2C_CR1_ENGC                              I2C_CR1_ENGC_Msk                                  /*!< General call enable */
#define I2C_CR1_NOSTRETCH_Pos                     (7U)
#define I2C_CR1_NOSTRETCH_Msk                     (0x1UL<<I2C_CR1_NOSTRETCH_Pos)                    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                         I2C_CR1_NOSTRETCH_Msk                             /*!< Clock stretching disable (Slave mode) */
#define I2C_CR1_START_Pos                         (8U)
#define I2C_CR1_START_Msk                         (0x1UL<<I2C_CR1_START_Pos)                        /*!< 0x00000100 */
#define I2C_CR1_START                             I2C_CR1_START_Msk                                 /*!< Start generation */
#define I2C_CR1_STOP_Pos                          (9U)
#define I2C_CR1_STOP_Msk                          (0x1UL<<I2C_CR1_STOP_Pos)                         /*!< 0x00000200 */
#define I2C_CR1_STOP                              I2C_CR1_STOP_Msk                                  /*!< Stop generation */
#define I2C_CR1_ACK_Pos                           (10U)
#define I2C_CR1_ACK_Msk                           (0x1UL<<I2C_CR1_ACK_Pos)                          /*!< 0x00000400 */
#define I2C_CR1_ACK                               I2C_CR1_ACK_Msk                                   /*!< Acknowledge enable */
#define I2C_CR1_POS_Pos                           (11U)
#define I2C_CR1_POS_Msk                           (0x1UL<<I2C_CR1_POS_Pos)                          /*!< 0x00000800 */
#define I2C_CR1_POS                               I2C_CR1_POS_Msk                                   /*!< Acknowledge(for data reception) */
#define I2C_CR1_PEC_Pos                           (12U)
#define I2C_CR1_PEC_Msk                           (0x1UL<<I2C_CR1_PEC_Pos)                          /*!< 0x00001000 */
#define I2C_CR1_PEC                               I2C_CR1_PEC_Msk                                   /*!< Packet error checking */
#define I2C_CR1_ALERT_Pos                         (13U)
#define I2C_CR1_ALERT_Msk                         (0x1UL<<I2C_CR1_ALERT_Pos)                        /*!< 0x00002000 */
#define I2C_CR1_ALERT                             I2C_CR1_ALERT_Msk                                 /*!< SMBus alert */
#define I2C_CR1_SWRST_Pos                         (15U)
#define I2C_CR1_SWRST_Msk                         (0x1UL<<I2C_CR1_SWRST_Pos)                        /*!< 0x00008000 */
#define I2C_CR1_SWRST                             I2C_CR1_SWRST_Msk                                 /*!< Software reset */
#define I2C_CR1_WKUP_DIV_Pos                      (16U)
#define I2C_CR1_WKUP_DIV_Msk                      (0x3UL<<I2C_CR1_WKUP_DIV_Pos)                     /*!< 0x00030000 */
#define I2C_CR1_WKUP_DIV                          I2C_CR1_WKUP_DIV_Msk                              /*!< PCLK division */
#define I2C_CR1_WKUP_DIV_0                        (0x1UL<<I2C_CR1_WKUP_DIV_Pos)                     /*!< 0x00010000 */
#define I2C_CR1_WKUP_DIV_1                        (0x2UL<<I2C_CR1_WKUP_DIV_Pos)                     /*!< 0x00020000 */
#define I2C_CR1_WKUP_CNT_Pos                      (18U)
#define I2C_CR1_WKUP_CNT_Msk                      (0x3UL<<I2C_CR1_WKUP_CNT_Pos)                     /*!< 0x000C0000 */
#define I2C_CR1_WKUP_CNT                          I2C_CR1_WKUP_CNT_Msk                              /*!< Timeout count number */
#define I2C_CR1_WKUP_CNT_0                        (0x1UL<<I2C_CR1_WKUP_CNT_Pos)                     /*!< 0x00040000 */
#define I2C_CR1_WKUP_CNT_1                        (0x2UL<<I2C_CR1_WKUP_CNT_Pos)                     /*!< 0x00080000 */

/********************************* Bit definition for I2C_CR2 register **********************************************/
#define I2C_CR2_FREQ_Pos                          (0U)
#define I2C_CR2_FREQ_Msk                          (0x7FUL<<I2C_CR2_FREQ_Pos)                        /*!< 0x0000007F */
#define I2C_CR2_FREQ                              I2C_CR2_FREQ_Msk                                  /*!< Peripheral clock frequency */
#define I2C_CR2_ITERREN_Pos                       (8U)
#define I2C_CR2_ITERREN_Msk                       (0x1UL<<I2C_CR2_ITERREN_Pos)                      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                           I2C_CR2_ITERREN_Msk                               /*!< Error interrupt enable */
#define I2C_CR2_ITEVTEN_Pos                       (9U)
#define I2C_CR2_ITEVTEN_Msk                       (0x1UL<<I2C_CR2_ITEVTEN_Pos)                      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                           I2C_CR2_ITEVTEN_Msk                               /*!< Event interrupt enable */
#define I2C_CR2_ITBUFEN_Pos                       (10U)
#define I2C_CR2_ITBUFEN_Msk                       (0x1UL<<I2C_CR2_ITBUFEN_Pos)                      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                           I2C_CR2_ITBUFEN_Msk                               /*!< Buffer interrupt enable */
#define I2C_CR2_DMAEN_Pos                         (11U)
#define I2C_CR2_DMAEN_Msk                         (0x1UL<<I2C_CR2_DMAEN_Pos)                        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                             I2C_CR2_DMAEN_Msk                                 /*!< DMA requests enable */
#define I2C_CR2_LAST_Pos                          (12U)
#define I2C_CR2_LAST_Msk                          (0x1UL<<I2C_CR2_LAST_Pos)                         /*!< 0x00001000 */
#define I2C_CR2_LAST                              I2C_CR2_LAST_Msk                                  /*!< DMA last transfer */

/********************************* Bit definition for I2C_OAR1 register *********************************************/
/*!< I2C_OAR1 */
#define I2C_OAR1_ADD0_Pos                         (0U)
#define I2C_OAR1_ADD0_Msk                         (0x1UL << I2C_OAR1_ADD0_Pos)                      /*!< 0x00000001 */
#define I2C_OAR1_ADD0                             I2C_OAR1_ADD0_Msk                                 /*!< desc ADD0 */

#define I2C_OAR1_ADD1_Pos                         (1U)
#define I2C_OAR1_ADD1_Msk                         (0x1UL << I2C_OAR1_ADD1_Pos)                      /*!< 0x00000002 */
#define I2C_OAR1_ADD1                             I2C_OAR1_ADD1_Msk                                 /*!< Bit 1 */
#define I2C_OAR1_ADD2_Pos                         (2U)
#define I2C_OAR1_ADD2_Msk                         (0x1UL << I2C_OAR1_ADD2_Pos)                      /*!< 0x00000004 */
#define I2C_OAR1_ADD2                             I2C_OAR1_ADD2_Msk                                 /*!< Bit 2 */
#define I2C_OAR1_ADD3_Pos                         (3U)
#define I2C_OAR1_ADD3_Msk                         (0x1UL << I2C_OAR1_ADD3_Pos)                      /*!< 0x00000008 */
#define I2C_OAR1_ADD3                             I2C_OAR1_ADD3_Msk                                 /*!< Bit 3 */
#define I2C_OAR1_ADD4_Pos                         (4U)
#define I2C_OAR1_ADD4_Msk                         (0x1UL << I2C_OAR1_ADD4_Pos)                      /*!< 0x00000010 */
#define I2C_OAR1_ADD4                             I2C_OAR1_ADD4_Msk                                 /*!< Bit 4 */
#define I2C_OAR1_ADD5_Pos                         (5U)
#define I2C_OAR1_ADD5_Msk                         (0x1UL << I2C_OAR1_ADD5_Pos)                      /*!< 0x00000020 */
#define I2C_OAR1_ADD5                             I2C_OAR1_ADD5_Msk                                 /*!< Bit 5 */
#define I2C_OAR1_ADD6_Pos                         (6U)
#define I2C_OAR1_ADD6_Msk                         (0x1UL << I2C_OAR1_ADD6_Pos)                      /*!< 0x00000040 */
#define I2C_OAR1_ADD6                             I2C_OAR1_ADD6_Msk                                 /*!< Bit 6 */
#define I2C_OAR1_ADD7_Pos                         (7U)
#define I2C_OAR1_ADD7_Msk                         (0x1UL << I2C_OAR1_ADD7_Pos)                      /*!< 0x00000080 */
#define I2C_OAR1_ADD7                             I2C_OAR1_ADD7_Msk                                 /*!< Bit 7 */
#define I2C_OAR1_ADD8_Pos                         (8U)
#define I2C_OAR1_ADD8_Msk                         (0x1UL << I2C_OAR1_ADD8_Pos)                      /*!< 0x00000100 */
#define I2C_OAR1_ADD8                             I2C_OAR1_ADD8_Msk                                 /*!< Bit 8 */
#define I2C_OAR1_ADD9_Pos                         (9U)
#define I2C_OAR1_ADD9_Msk                         (0x1UL << I2C_OAR1_ADD9_Pos)                      /*!< 0x00000200 */
#define I2C_OAR1_ADD9                             I2C_OAR1_ADD9_Msk                                 /*!< Bit 9 */

#define I2C_OAR1_ADD1_7                           0x000000FEU                                       /*!< Interface Address */
#define I2C_OAR1_ADD8_9                           0x00000300U                                       /*!< Interface Address */

#define I2C_OAR1_ADDMODE_Pos                      (15U)
#define I2C_OAR1_ADDMODE_Msk                      (0x1UL<<I2C_OAR1_ADDMODE_Pos)                     /*!< 0x00008000 */
#define I2C_OAR1_ADDMODE                          I2C_OAR1_ADDMODE_Msk                              /*!< Addressing mode (slave mode) */

/********************************* Bit definition for I2C_OAR2 register *********************************************/
#define I2C_OAR2_ENDUAL_Pos                       (0U)
#define I2C_OAR2_ENDUAL_Msk                       (0x1UL<<I2C_OAR2_ENDUAL_Pos)                      /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL                           I2C_OAR2_ENDUAL_Msk                               /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos                         (1U)
#define I2C_OAR2_ADD2_Msk                         (0x7FUL<<I2C_OAR2_ADD2_Pos)                       /*!< 0x000000FE */
#define I2C_OAR2_ADD2                             I2C_OAR2_ADD2_Msk                                 /*!< Interface address */
#define I2C_OAR2_OA2MSK_Pos                       (8U)
#define I2C_OAR2_OA2MSK_Msk                       (0x7UL<<I2C_OAR2_OA2MSK_Pos)                      /*!< 0x00000700 */
#define I2C_OAR2_OA2MSK                           I2C_OAR2_OA2MSK_Msk                               /*!< Own Address 2 masks */
#define I2C_OAR2_OA2MSK_0                         (0x1UL<<I2C_OAR2_OA2MSK_Pos)                      /*!< 0x00000100 */
#define I2C_OAR2_OA2MSK_1                         (0x2UL<<I2C_OAR2_OA2MSK_Pos)                      /*!< 0x00000200 */
#define I2C_OAR2_OA2MSK_2                         (0x4UL<<I2C_OAR2_OA2MSK_Pos)                      /*!< 0x00000400 */

/********************************* Bit definition for I2C_DR register ***********************************************/
#define I2C_DR_DR_Pos                             (0U)
#define I2C_DR_DR_Msk                             (0xFFUL<<I2C_DR_DR_Pos)                           /*!< 0x000000FF */
#define I2C_DR_DR                                 I2C_DR_DR_Msk                                     /*!< 8-bit data register */

/********************************* Bit definition for I2C_SR1 register **********************************************/
#define I2C_SR1_SB_Pos                            (0U)
#define I2C_SR1_SB_Msk                            (0x1UL<<I2C_SR1_SB_Pos)                           /*!< 0x00000001 */
#define I2C_SR1_SB                                I2C_SR1_SB_Msk                                    /*!< Start bit (Master mode) */
#define I2C_SR1_ADDR_Pos                          (1U)
#define I2C_SR1_ADDR_Msk                          (0x1UL<<I2C_SR1_ADDR_Pos)                         /*!< 0x00000002 */
#define I2C_SR1_ADDR                              I2C_SR1_ADDR_Msk                                  /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos                           (2U)
#define I2C_SR1_BTF_Msk                           (0x1UL<<I2C_SR1_BTF_Pos)                          /*!< 0x00000004 */
#define I2C_SR1_BTF                               I2C_SR1_BTF_Msk                                   /*!< Byte transfer finished */
#define I2C_SR1_ADD10_Pos                         (3U)
#define I2C_SR1_ADD10_Msk                         (0x1UL<<I2C_SR1_ADD10_Pos)                        /*!< 0x00000008 */
#define I2C_SR1_ADD10                             I2C_SR1_ADD10_Msk                                 /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_STOPF_Pos                         (4U)
#define I2C_SR1_STOPF_Msk                         (0x1UL<<I2C_SR1_STOPF_Pos)                        /*!< 0x00000010 */
#define I2C_SR1_STOPF                             I2C_SR1_STOPF_Msk                                 /*!< Stop detection (slave mode) */
#define I2C_SR1_RXNE_Pos                          (6U)
#define I2C_SR1_RXNE_Msk                          (0x1UL<<I2C_SR1_RXNE_Pos)                         /*!< 0x00000040 */
#define I2C_SR1_RXNE                              I2C_SR1_RXNE_Msk                                  /*!< Data register not empty (receivers) */
#define I2C_SR1_TXE_Pos                           (7U)
#define I2C_SR1_TXE_Msk                           (0x1UL<<I2C_SR1_TXE_Pos)                          /*!< 0x00000080 */
#define I2C_SR1_TXE                               I2C_SR1_TXE_Msk                                   /*!< Data register empty (transmitters) */
#define I2C_SR1_BERR_Pos                          (8U)
#define I2C_SR1_BERR_Msk                          (0x1UL<<I2C_SR1_BERR_Pos)                         /*!< 0x00000100 */
#define I2C_SR1_BERR                              I2C_SR1_BERR_Msk                                  /*!< Bus error */
#define I2C_SR1_ARLO_Pos                          (9U)
#define I2C_SR1_ARLO_Msk                          (0x1UL<<I2C_SR1_ARLO_Pos)                         /*!< 0x00000200 */
#define I2C_SR1_ARLO                              I2C_SR1_ARLO_Msk                                  /*!< Arbitration lost (master mode) */
#define I2C_SR1_AF_Pos                            (10U)
#define I2C_SR1_AF_Msk                            (0x1UL<<I2C_SR1_AF_Pos)                           /*!< 0x00000400 */
#define I2C_SR1_AF                                I2C_SR1_AF_Msk                                    /*!< Acknowledge failure */
#define I2C_SR1_OVR_Pos                           (11U)
#define I2C_SR1_OVR_Msk                           (0x1UL<<I2C_SR1_OVR_Pos)                          /*!< 0x00000800 */
#define I2C_SR1_OVR                               I2C_SR1_OVR_Msk                                   /*!< Overrun/Underrun */
#define I2C_SR1_PECERR_Pos                        (12U)
#define I2C_SR1_PECERR_Msk                        (0x1UL<<I2C_SR1_PECERR_Pos)                       /*!< 0x00001000 */
#define I2C_SR1_PECERR                            I2C_SR1_PECERR_Msk                                /*!< PEC Error in reception */
#define I2C_SR1_TIMEOUT_Pos                       (14U)
#define I2C_SR1_TIMEOUT_Msk                       (0x1UL<<I2C_SR1_TIMEOUT_Pos)                      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                           I2C_SR1_TIMEOUT_Msk                               /*!< Timeout or Tlow error */
#define I2C_SR1_SMBALERT_Pos                      (15U)
#define I2C_SR1_SMBALERT_Msk                      (0x1UL<<I2C_SR1_SMBALERT_Pos)                     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                          I2C_SR1_SMBALERT_Msk                              /*!< SMBus alert */

/********************************* Bit definition for I2C_SR2 register **********************************************/
#define I2C_SR2_MSL_Pos                           (0U)
#define I2C_SR2_MSL_Msk                           (0x1UL<<I2C_SR2_MSL_Pos)                          /*!< 0x00000001 */
#define I2C_SR2_MSL                               I2C_SR2_MSL_Msk                                   /*!< Master/slave */
#define I2C_SR2_BUSY_Pos                          (1U)
#define I2C_SR2_BUSY_Msk                          (0x1UL<<I2C_SR2_BUSY_Pos)                         /*!< 0x00000002 */
#define I2C_SR2_BUSY                              I2C_SR2_BUSY_Msk                                  /*!< Bus busy */
#define I2C_SR2_TRA_Pos                           (2U)
#define I2C_SR2_TRA_Msk                           (0x1UL<<I2C_SR2_TRA_Pos)                          /*!< 0x00000004 */
#define I2C_SR2_TRA                               I2C_SR2_TRA_Msk                                   /*!< Transmitter/receiver */
#define I2C_SR2_GENCALL_Pos                       (4U)
#define I2C_SR2_GENCALL_Msk                       (0x1UL<<I2C_SR2_GENCALL_Pos)                      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                           I2C_SR2_GENCALL_Msk                               /*!< General call address (Slave mode) */
#define I2C_SR2_SMBDEFAULT_Pos                    (5U)
#define I2C_SR2_SMBDEFAULT_Msk                    (0x1UL<<I2C_SR2_SMBDEFAULT_Pos)                   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                        I2C_SR2_SMBDEFAULT_Msk                            /*!< SMBus device default address (Slave mode) */
#define I2C_SR2_SMBHOST_Pos                       (6U)
#define I2C_SR2_SMBHOST_Msk                       (0x1UL<<I2C_SR2_SMBHOST_Pos)                      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                           I2C_SR2_SMBHOST_Msk                               /*!< SMBus host header (Slave mode) */
#define I2C_SR2_DUALF_Pos                         (7U)
#define I2C_SR2_DUALF_Msk                         (0x1UL<<I2C_SR2_DUALF_Pos)                        /*!< 0x00000080 */
#define I2C_SR2_DUALF                             I2C_SR2_DUALF_Msk                                 /*!< Dual flag (Slave mode) */
#define I2C_SR2_PEC_Pos                           (8U)
#define I2C_SR2_PEC_Msk                           (0xFFUL<<I2C_SR2_PEC_Pos)                         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                               I2C_SR2_PEC_Msk                                   /*!< Packet error checking register */

/********************************* Bit definition for I2C_CCR register **********************************************/
#define I2C_CCR_CCR_Pos                           (0U)
#define I2C_CCR_CCR_Msk                           (0xFFFUL<<I2C_CCR_CCR_Pos)                        /*!< 0x00000FFF */
#define I2C_CCR_CCR                               I2C_CCR_CCR_Msk                                   /*!< Clock control register in Fm/Sm mode (Master mode) */
#define I2C_CCR_FP_Pos                            (13U)
#define I2C_CCR_FP_Msk                            (0x1UL<<I2C_CCR_FP_Pos)                           /*!< 0x00002000 */
#define I2C_CCR_FP                                I2C_CCR_FP_Msk                                    /*!< I2C quick enhancement mode selection */
#define I2C_CCR_DUTY_Pos                          (14U)
#define I2C_CCR_DUTY_Msk                          (0x1UL<<I2C_CCR_DUTY_Pos)                         /*!< 0x00004000 */
#define I2C_CCR_DUTY                              I2C_CCR_DUTY_Msk                                  /*!< Fm mode duty cycle */
#define I2C_CCR_FS_Pos                            (15U)
#define I2C_CCR_FS_Msk                            (0x1UL<<I2C_CCR_FS_Pos)                           /*!< 0x00008000 */
#define I2C_CCR_FS                                I2C_CCR_FS_Msk                                    /*!< I2C master mode selection */

/********************************* Bit definition for I2C_TRISE register ********************************************/
#define I2C_TRISE_TRISE_Pos                       (0U)
#define I2C_TRISE_TRISE_Msk                       (0x7FUL<<I2C_TRISE_TRISE_Pos)                     /*!< 0x0000007F */
#define I2C_TRISE_TRISE                           I2C_TRISE_TRISE_Msk                               /*!< Maximum rise time in Fm+/Fm/Sm mode (Master mode) */
#define I2C_TRISE_THOLDDATA_Pos                   (7U)
#define I2C_TRISE_THOLDDATA_Msk                   (0x1FUL<<I2C_TRISE_THOLDDATA_Pos)                 /*!< 0x00000F80 */
#define I2C_TRISE_THOLDDATA                       I2C_TRISE_THOLDDATA_Msk                           /*!< Data hold time */
#define I2C_TRISE_THOLDDATA_0                     (0x1UL<<I2C_TRISE_THOLDDATA_Pos)                  /*!< 0x00000080 */
#define I2C_TRISE_THOLDDATA_1                     (0x2UL<<I2C_TRISE_THOLDDATA_Pos)                  /*!< 0x00000100 */
#define I2C_TRISE_THOLDDATA_2                     (0x4UL<<I2C_TRISE_THOLDDATA_Pos)                  /*!< 0x00000200 */
#define I2C_TRISE_THOLDDATA_3                     (0x8UL<<I2C_TRISE_THOLDDATA_Pos)                  /*!< 0x00000400 */
#define I2C_TRISE_THOLDDATA_4                     (0x10UL<<I2C_TRISE_THOLDDATA_Pos)                 /*!< 0x00000800 */
#define I2C_TRISE_THOLDDATA_SEL_Pos               (12U)
#define I2C_TRISE_THOLDDATA_SEL_Msk               (0x1UL<<I2C_TRISE_THOLDDATA_SEL_Pos)              /*!< 0x00001000 */
#define I2C_TRISE_THOLDDATA_SEL                   I2C_TRISE_THOLDDATA_SEL_Msk                       /*!< Data hold time select */

/********************************* Bit definition for I2C_TIMEOUTR register *****************************************/
#define I2C_TIMEOUTR_TIMEOUTA_Pos                 (0U)
#define I2C_TIMEOUTR_TIMEOUTA_Msk                 (0xFFFUL<<I2C_TIMEOUTR_TIMEOUTA_Pos)              /*!< 0x00000FFF */
#define I2C_TIMEOUTR_TIMEOUTA                     I2C_TIMEOUTR_TIMEOUTA_Msk                         /*!< Bus Timeout A */
#define I2C_TIMEOUTR_TIDLE_Pos                    (12U)
#define I2C_TIMEOUTR_TIDLE_Msk                    (0x1UL<<I2C_TIMEOUTR_TIDLE_Pos)                   /*!< 0x00001000 */
#define I2C_TIMEOUTR_TIDLE                        I2C_TIMEOUTR_TIDLE_Msk                            /*!< Idle clock timeout detection */
#define I2C_TIMEOUTR_TIMEOUTEN_Pos                (15U)
#define I2C_TIMEOUTR_TIMEOUTEN_Msk                (0x1UL<<I2C_TIMEOUTR_TIMEOUTEN_Pos)               /*!< 0x00008000 */
#define I2C_TIMEOUTR_TIMEOUTEN                    I2C_TIMEOUTR_TIMEOUTEN_Msk                        /*!< Clock timeout enable */
#define I2C_TIMEOUTR_TIMEOUTB_Pos                 (16U)
#define I2C_TIMEOUTR_TIMEOUTB_Msk                 (0xFFFUL<<I2C_TIMEOUTR_TIMEOUTB_Pos)              /*!< 0x0FFF0000 */
#define I2C_TIMEOUTR_TIMEOUTB                     I2C_TIMEOUTR_TIMEOUTB_Msk                         /*!< Bus timeout B */
#define I2C_TIMEOUTR_TEXTEN_Pos                   (31U)
#define I2C_TIMEOUTR_TEXTEN_Msk                   (0x1UL<<I2C_TIMEOUTR_TEXTEN_Pos)                  /*!< 0x80000000 */
#define I2C_TIMEOUTR_TEXTEN                       I2C_TIMEOUTR_TEXTEN_Msk                           /*!< Extended clock timeout enable */

/********************************************************************************************************************/
/********************************* IWDG *****************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for IWDG_KR register **********************************************/
#define IWDG_KR_KEY_Pos                           (0U)
#define IWDG_KR_KEY_Msk                           (0xFFFFUL<<IWDG_KR_KEY_Pos)                       /*!< 0x0000FFFF */
#define IWDG_KR_KEY                               IWDG_KR_KEY_Msk                                   /*!< IWDG KEY */

/********************************* Bit definition for IWDG_PR register **********************************************/
#define IWDG_PR_PR_Pos                            (0U)
#define IWDG_PR_PR_Msk                            (0x7UL<<IWDG_PR_PR_Pos)                           /*!< 0x00000007 */
#define IWDG_PR_PR                                IWDG_PR_PR_Msk                                    /*!< IWDG preload */
#define IWDG_PR_PR_0                              (0x1UL<<IWDG_PR_PR_Pos)                           /*!< 0x00000001 */
#define IWDG_PR_PR_1                              (0x2UL<<IWDG_PR_PR_Pos)                           /*!< 0x00000002 */
#define IWDG_PR_PR_2                              (0x4UL<<IWDG_PR_PR_Pos)                           /*!< 0x00000004 */

/********************************* Bit definition for IWDG_RLR register *********************************************/
#define IWDG_RLR_RL_Pos                           (0U)
#define IWDG_RLR_RL_Msk                           (0xFFFUL<<IWDG_RLR_RL_Pos)                        /*!< 0x00000FFF */
#define IWDG_RLR_RL                               IWDG_RLR_RL_Msk                                   /*!< IWDG reload */

/********************************* Bit definition for IWDG_SR register **********************************************/
#define IWDG_SR_PVU_Pos                           (0U)
#define IWDG_SR_PVU_Msk                           (0x1UL<<IWDG_SR_PVU_Pos)                          /*!< 0x00000001 */
#define IWDG_SR_PVU                               IWDG_SR_PVU_Msk                                   /*!< Watchdog prescaler value update */
#define IWDG_SR_RVU_Pos                           (1U)
#define IWDG_SR_RVU_Msk                           (0x1UL<<IWDG_SR_RVU_Pos)                          /*!< 0x00000002 */
#define IWDG_SR_RVU                               IWDG_SR_RVU_Msk                                   /*!< Watchdog counter reload value update */

/********************************************************************************************************************/
/********************************* LPTIM ****************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for LPTIM_ISR register ********************************************/
#define LPTIM_ISR_CMPM_Pos                        (0U)
#define LPTIM_ISR_CMPM_Msk                        (0x1UL<<LPTIM_ISR_CMPM_Pos)                       /*!< 0x00000001 */
#define LPTIM_ISR_CMPM                            LPTIM_ISR_CMPM_Msk                                /*!< Compare match */
#define LPTIM_ISR_ARRM_Pos                        (1U)
#define LPTIM_ISR_ARRM_Msk                        (0x1UL<<LPTIM_ISR_ARRM_Pos)                       /*!< 0x00000002 */
#define LPTIM_ISR_ARRM                            LPTIM_ISR_ARRM_Msk                                /*!< Autoreload match */
#define LPTIM_ISR_EXTTRIG_Pos                     (2U)
#define LPTIM_ISR_EXTTRIG_Msk                     (0x1UL<<LPTIM_ISR_EXTTRIG_Pos)                    /*!< 0x00000004 */
#define LPTIM_ISR_EXTTRIG                         LPTIM_ISR_EXTTRIG_Msk                             /*!< External trigger edge event */
#define LPTIM_ISR_CMPOK_Pos                       (3U)
#define LPTIM_ISR_CMPOK_Msk                       (0x1UL<<LPTIM_ISR_CMPOK_Pos)                      /*!< 0x00000008 */
#define LPTIM_ISR_CMPOK                           LPTIM_ISR_CMPOK_Msk                               /*!< Compare register update OK */
#define LPTIM_ISR_ARROK_Pos                       (4U)
#define LPTIM_ISR_ARROK_Msk                       (0x1UL<<LPTIM_ISR_ARROK_Pos)                      /*!< 0x00000010 */
#define LPTIM_ISR_ARROK                           LPTIM_ISR_ARROK_Msk                               /*!< Autoreload register update OK */
#define LPTIM_ISR_UP_Pos                          (5U)
#define LPTIM_ISR_UP_Msk                          (0x1UL<<LPTIM_ISR_UP_Pos)                         /*!< 0x00000020 */
#define LPTIM_ISR_UP                              LPTIM_ISR_UP_Msk                                  /*!< Counter direction change down to up */
#define LPTIM_ISR_DOWN_Pos                        (6U)
#define LPTIM_ISR_DOWN_Msk                        (0x1UL<<LPTIM_ISR_DOWN_Pos)                       /*!< 0x00000040 */
#define LPTIM_ISR_DOWN                            LPTIM_ISR_DOWN_Msk                                /*!< Counter direction change up to down */

/********************************* Bit definition for LPTIM_ICR register ********************************************/
#define LPTIM_ICR_CMPMCF_Pos                      (0U)
#define LPTIM_ICR_CMPMCF_Msk                      (0x1UL<<LPTIM_ICR_CMPMCF_Pos)                     /*!< 0x00000001 */
#define LPTIM_ICR_CMPMCF                          LPTIM_ICR_CMPMCF_Msk                              /*!< Compare match clear flag */
#define LPTIM_ICR_ARRMCF_Pos                      (1U)
#define LPTIM_ICR_ARRMCF_Msk                      (0x1UL<<LPTIM_ICR_ARRMCF_Pos)                     /*!< 0x00000002 */
#define LPTIM_ICR_ARRMCF                          LPTIM_ICR_ARRMCF_Msk                              /*!< Autoreload match clear flag */
#define LPTIM_ICR_EXTTRIGCF_Pos                   (2U)
#define LPTIM_ICR_EXTTRIGCF_Msk                   (0x1UL<<LPTIM_ICR_EXTTRIGCF_Pos)                  /*!< 0x00000004 */
#define LPTIM_ICR_EXTTRIGCF                       LPTIM_ICR_EXTTRIGCF_Msk                           /*!< External trigger valid edge clear flag */
#define LPTIM_ICR_CMPOKCF_Pos                     (3U)
#define LPTIM_ICR_CMPOKCF_Msk                     (0x1UL<<LPTIM_ICR_CMPOKCF_Pos)                    /*!< 0x00000008 */
#define LPTIM_ICR_CMPOKCF                         LPTIM_ICR_CMPOKCF_Msk                             /*!< Compare register update OK clear flag */
#define LPTIM_ICR_ARROKCF_Pos                     (4U)
#define LPTIM_ICR_ARROKCF_Msk                     (0x1UL<<LPTIM_ICR_ARROKCF_Pos)                    /*!< 0x00000010 */
#define LPTIM_ICR_ARROKCF                         LPTIM_ICR_ARROKCF_Msk                             /*!< Autoreload register update OK clear flag */
#define LPTIM_ICR_UPCF_Pos                        (5U)
#define LPTIM_ICR_UPCF_Msk                        (0x1UL<<LPTIM_ICR_UPCF_Pos)                       /*!< 0x00000020 */
#define LPTIM_ICR_UPCF                            LPTIM_ICR_UPCF_Msk                                /*!< Direction change to UP clear flag */
#define LPTIM_ICR_DOWNCF_Pos                      (6U)
#define LPTIM_ICR_DOWNCF_Msk                      (0x1UL<<LPTIM_ICR_DOWNCF_Pos)                     /*!< 0x00000040 */
#define LPTIM_ICR_DOWNCF                          LPTIM_ICR_DOWNCF_Msk                              /*!< Direction change to down clear flag */

/********************************* Bit definition for LPTIM_IER register ********************************************/
#define LPTIM_IER_CMPMIE_Pos                      (0U)
#define LPTIM_IER_CMPMIE_Msk                      (0x1UL<<LPTIM_IER_CMPMIE_Pos)                     /*!< 0x00000001 */
#define LPTIM_IER_CMPMIE                          LPTIM_IER_CMPMIE_Msk                              /*!< Compare match Interrupt Enable */
#define LPTIM_IER_ARRMIE_Pos                      (1U)
#define LPTIM_IER_ARRMIE_Msk                      (0x1UL<<LPTIM_IER_ARRMIE_Pos)                     /*!< 0x00000002 */
#define LPTIM_IER_ARRMIE                          LPTIM_IER_ARRMIE_Msk                              /*!< Autoreload match Interrupt Enable */
#define LPTIM_IER_EXTTRIGIE_Pos                   (2U)
#define LPTIM_IER_EXTTRIGIE_Msk                   (0x1UL<<LPTIM_IER_EXTTRIGIE_Pos)                  /*!< 0x00000004 */
#define LPTIM_IER_EXTTRIGIE                       LPTIM_IER_EXTTRIGIE_Msk                           /*!< External trigger valid edge Interrupt Enable */
#define LPTIM_IER_CMPOKIE_Pos                     (3U)
#define LPTIM_IER_CMPOKIE_Msk                     (0x1UL<<LPTIM_IER_CMPOKIE_Pos)                    /*!< 0x00000008 */
#define LPTIM_IER_CMPOKIE                         LPTIM_IER_CMPOKIE_Msk                             /*!< Compare register update OK Interrupt Enable */
#define LPTIM_IER_ARROKIE_Pos                     (4U)
#define LPTIM_IER_ARROKIE_Msk                     (0x1UL<<LPTIM_IER_ARROKIE_Pos)                    /*!< 0x00000010 */
#define LPTIM_IER_ARROKIE                         LPTIM_IER_ARROKIE_Msk                             /*!< Autoreload register update OK Interrupt Enable */
#define LPTIM_IER_UPIE_Pos                        (5U)
#define LPTIM_IER_UPIE_Msk                        (0x1UL<<LPTIM_IER_UPIE_Pos)                       /*!< 0x00000020 */
#define LPTIM_IER_UPIE                            LPTIM_IER_UPIE_Msk                                /*!< Direction change to UP Interrupt Enable */
#define LPTIM_IER_DOWNIE_Pos                      (6U)
#define LPTIM_IER_DOWNIE_Msk                      (0x1UL<<LPTIM_IER_DOWNIE_Pos)                     /*!< 0x00000040 */
#define LPTIM_IER_DOWNIE                          LPTIM_IER_DOWNIE_Msk                              /*!< Direction change to down Interrupt Enable */

/********************************* Bit definition for LPTIM_CFGR register *******************************************/
#define LPTIM_CFGR_CKSEL_Pos                      (0U)
#define LPTIM_CFGR_CKSEL_Msk                      (0x1UL<<LPTIM_CFGR_CKSEL_Pos)                     /*!< 0x00000001 */
#define LPTIM_CFGR_CKSEL                          LPTIM_CFGR_CKSEL_Msk                              /*!< Clock selector */
#define LPTIM_CFGR_CKPOL_Pos                      (1U)
#define LPTIM_CFGR_CKPOL_Msk                      (0x3UL<<LPTIM_CFGR_CKPOL_Pos)                     /*!< 0x00000006 */
#define LPTIM_CFGR_CKPOL                          LPTIM_CFGR_CKPOL_Msk                              /*!< Clock Polarity */
#define LPTIM_CFGR_CKPOL_0                        (0x1UL<<LPTIM_CFGR_CKPOL_Pos)                     /*!< 0x00000002 */
#define LPTIM_CFGR_CKPOL_1                        (0x2UL<<LPTIM_CFGR_CKPOL_Pos)                     /*!< 0x00000004 */
#define LPTIM_CFGR_CKFLT_Pos                      (3U)
#define LPTIM_CFGR_CKFLT_Msk                      (0x3UL<<LPTIM_CFGR_CKFLT_Pos)                     /*!< 0x00000018 */
#define LPTIM_CFGR_CKFLT                          LPTIM_CFGR_CKFLT_Msk                              /*!< Configurable digital filter for external clock */
#define LPTIM_CFGR_CKFLT_0                        (0x1UL<<LPTIM_CFGR_CKFLT_Pos)                     /*!< 0x00000008 */
#define LPTIM_CFGR_CKFLT_1                        (0x2UL<<LPTIM_CFGR_CKFLT_Pos)                     /*!< 0x00000010 */
#define LPTIM_CFGR_TRGFLT_Pos                     (6U)
#define LPTIM_CFGR_TRGFLT_Msk                     (0x3UL<<LPTIM_CFGR_TRGFLT_Pos)                    /*!< 0x000000C0 */
#define LPTIM_CFGR_TRGFLT                         LPTIM_CFGR_TRGFLT_Msk                             /*!< Configurable digital filter for trigger */
#define LPTIM_CFGR_TRGFLT_0                       (0x1UL<<LPTIM_CFGR_TRGFLT_Pos)                    /*!< 0x00000040 */
#define LPTIM_CFGR_TRGFLT_1                       (0x2UL<<LPTIM_CFGR_TRGFLT_Pos)                    /*!< 0x00000080 */
#define LPTIM_CFGR_PRESC_Pos                      (9U)
#define LPTIM_CFGR_PRESC_Msk                      (0x7UL<<LPTIM_CFGR_PRESC_Pos)                     /*!< 0x00000E00 */
#define LPTIM_CFGR_PRESC                          LPTIM_CFGR_PRESC_Msk                              /*!< Clock prescaler */
#define LPTIM_CFGR_PRESC_0                        (0x1UL<<LPTIM_CFGR_PRESC_Pos)                     /*!< 0x00000200 */
#define LPTIM_CFGR_PRESC_1                        (0x2UL<<LPTIM_CFGR_PRESC_Pos)                     /*!< 0x00000400 */
#define LPTIM_CFGR_PRESC_2                        (0x4UL<<LPTIM_CFGR_PRESC_Pos)                     /*!< 0x00000800 */
#define LPTIM_CFGR_TRIGSEL_Pos                    (13U)
#define LPTIM_CFGR_TRIGSEL_Msk                    (0x7UL<<LPTIM_CFGR_TRIGSEL_Pos)                   /*!< 0x0000E000 */
#define LPTIM_CFGR_TRIGSEL                        LPTIM_CFGR_TRIGSEL_Msk                            /*!< Trigger selector */
#define LPTIM_CFGR_TRIGSEL_0                      (0x1UL<<LPTIM_CFGR_TRIGSEL_Pos)                   /*!< 0x00002000 */
#define LPTIM_CFGR_TRIGSEL_1                      (0x2UL<<LPTIM_CFGR_TRIGSEL_Pos)                   /*!< 0x00004000 */
#define LPTIM_CFGR_TRIGSEL_2                      (0x4UL<<LPTIM_CFGR_TRIGSEL_Pos)                   /*!< 0x00008000 */
#define LPTIM_CFGR_TRIGEN_Pos                     (17U)
#define LPTIM_CFGR_TRIGEN_Msk                     (0x3UL<<LPTIM_CFGR_TRIGEN_Pos)                    /*!< 0x00060000 */
#define LPTIM_CFGR_TRIGEN                         LPTIM_CFGR_TRIGEN_Msk                             /*!< Trigger enable and polarity */
#define LPTIM_CFGR_TRIGEN_0                       (0x1UL<<LPTIM_CFGR_TRIGEN_Pos)                    /*!< 0x00020000 */
#define LPTIM_CFGR_TRIGEN_1                       (0x2UL<<LPTIM_CFGR_TRIGEN_Pos)                    /*!< 0x00040000 */
#define LPTIM_CFGR_TIMOUT_Pos                     (19U)
#define LPTIM_CFGR_TIMOUT_Msk                     (0x1UL<<LPTIM_CFGR_TIMOUT_Pos)                    /*!< 0x00080000 */
#define LPTIM_CFGR_TIMOUT                         LPTIM_CFGR_TIMOUT_Msk                             /*!<  Timeout enable */
#define LPTIM_CFGR_WAVE_Pos                       (20U)
#define LPTIM_CFGR_WAVE_Msk                       (0x1UL<<LPTIM_CFGR_WAVE_Pos)                      /*!< 0x00100000 */
#define LPTIM_CFGR_WAVE                           LPTIM_CFGR_WAVE_Msk                               /*!< Waveform shape */
#define LPTIM_CFGR_WAVPOL_Pos                     (21U)
#define LPTIM_CFGR_WAVPOL_Msk                     (0x1UL<<LPTIM_CFGR_WAVPOL_Pos)                    /*!< 0x00200000 */
#define LPTIM_CFGR_WAVPOL                         LPTIM_CFGR_WAVPOL_Msk                             /*!< Waveform shape polarity */
#define LPTIM_CFGR_PRELOAD_Pos                    (22U)
#define LPTIM_CFGR_PRELOAD_Msk                    (0x1UL<<LPTIM_CFGR_PRELOAD_Pos)                   /*!< 0x00400000 */
#define LPTIM_CFGR_PRELOAD                        LPTIM_CFGR_PRELOAD_Msk                            /*!< Registers update mode */
#define LPTIM_CFGR_COUNTMODE_Pos                  (23U)
#define LPTIM_CFGR_COUNTMODE_Msk                  (0x1UL<<LPTIM_CFGR_COUNTMODE_Pos)                 /*!< 0x00800000 */
#define LPTIM_CFGR_COUNTMODE                      LPTIM_CFGR_COUNTMODE_Msk                          /*!< Enable Counter Mode */
#define LPTIM_CFGR_ENC_Pos                        (24U)
#define LPTIM_CFGR_ENC_Msk                        (0x1UL<<LPTIM_CFGR_ENC_Pos)                       /*!< 0x01000000 */
#define LPTIM_CFGR_ENC                            LPTIM_CFGR_ENC_Msk                                /*!< Encoder mode enable */

/********************************* Bit definition for LPTIM_CR register *********************************************/
#define LPTIM_CR_ENABLE_Pos                       (0U)
#define LPTIM_CR_ENABLE_Msk                       (0x1UL<<LPTIM_CR_ENABLE_Pos)                      /*!< 0x00000001 */
#define LPTIM_CR_ENABLE                           LPTIM_CR_ENABLE_Msk                               /*!< LPTIM enable */
#define LPTIM_CR_SNGSTRT_Pos                      (1U)
#define LPTIM_CR_SNGSTRT_Msk                      (0x1UL<<LPTIM_CR_SNGSTRT_Pos)                     /*!< 0x00000002 */
#define LPTIM_CR_SNGSTRT                          LPTIM_CR_SNGSTRT_Msk                              /*!< LPTIM start in Single mode */
#define LPTIM_CR_CNTSTRT_Pos                      (2U)
#define LPTIM_CR_CNTSTRT_Msk                      (0x1UL<<LPTIM_CR_CNTSTRT_Pos)                     /*!< 0x00000004 */
#define LPTIM_CR_CNTSTRT                          LPTIM_CR_CNTSTRT_Msk                              /*!< Timer start in Continuous mode */
#define LPTIM_CR_COUNTRST_Pos                     (3U)
#define LPTIM_CR_COUNTRST_Msk                     (0x1UL<<LPTIM_CR_COUNTRST_Pos)                    /*!< 0x00000008 */
#define LPTIM_CR_COUNTRST                         LPTIM_CR_COUNTRST_Msk                             /*!< Counter reset */
#define LPTIM_CR_RSTARE_Pos                       (4U)
#define LPTIM_CR_RSTARE_Msk                       (0x1UL<<LPTIM_CR_RSTARE_Pos)                      /*!< 0x00000010 */
#define LPTIM_CR_RSTARE                           LPTIM_CR_RSTARE_Msk                               /*!< Reset after read enable */

/********************************* Bit definition for LPTIM_CMP register ********************************************/
#define LPTIM_CMP_CMP_Pos                         (0U)
#define LPTIM_CMP_CMP_Msk                         (0xFFFFUL<<LPTIM_CMP_CMP_Pos)                     /*!< 0xFFFF */
#define LPTIM_CMP_CMP                             LPTIM_CMP_CMP_Msk                                 /*!< Compare value */

/********************************* Bit definition for LPTIM_ARR register ********************************************/
#define LPTIM_ARR_ARR_Pos                         (0U)
#define LPTIM_ARR_ARR_Msk                         (0xFFFFUL<<LPTIM_ARR_ARR_Pos)                     /*!< 0xFFFF */
#define LPTIM_ARR_ARR                             LPTIM_ARR_ARR_Msk                                 /*!< Auto reload value */

/********************************* Bit definition for LPTIM_CNT register ********************************************/
#define LPTIM_CNT_CNT_Pos                         (0U)
#define LPTIM_CNT_CNT_Msk                         (0xFFFFUL<<LPTIM_CNT_CNT_Pos)                     /*!< 0xFFFF */
#define LPTIM_CNT_CNT                             LPTIM_CNT_CNT_Msk                                 /*!< Counter value */

/********************************* Bit definition for LPTIM_OR register *********************************************/
#define LPTIM_OR_IN1_Pos                          (0U)
#define LPTIM_OR_IN1_Msk                          (0xDUL<<LPTIM_OR_IN1_Pos)                         /*!< 0x0000000D */
#define LPTIM_OR_IN1                              LPTIM_OR_IN1_Msk                                  /*!< LPTimer input 1 remap extension */
#define LPTIM_OR_IN1_0                            (0x1UL<<LPTIM_OR_IN1_Pos)                         /*!< 0x00000001 */
#define LPTIM_OR_IN1_1                            (0x4UL<<LPTIM_OR_IN1_Pos)                         /*!< 0x00000004 */
#define LPTIM_OR_IN1_2                            (0x8UL<<LPTIM_OR_IN1_Pos)                         /*!< 0x00000008 */
#define LPTIM_OR_IN2_Pos                          (1U)
#define LPTIM_OR_IN2_Msk                          (0x19UL<<LPTIM_OR_IN2_Pos)                        /*!< 0x00000032 */
#define LPTIM_OR_IN2                              LPTIM_OR_IN2_Msk                                  /*!< LPTimer input 2 remap extension */
#define LPTIM_OR_IN2_0                            (0x1UL<<LPTIM_OR_IN2_Pos)                         /*!< 0x00000002 */
#define LPTIM_OR_IN2_1                            (0x8UL<<LPTIM_OR_IN2_Pos)                         /*!< 0x00000010 */
#define LPTIM_OR_IN2_2                            (0x10UL<<LPTIM_OR_IN2_Pos)                        /*!< 0x00000020 */

/********************************************************************************************************************/
/********************************* LPUART ***************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for LPUART_CR1 register *******************************************/
#define LPUART_CR1_UE_Pos                         (0U)
#define LPUART_CR1_UE_Msk                         (0x1UL<<LPUART_CR1_UE_Pos)                        /*!< 0x00000001 */
#define LPUART_CR1_UE                             LPUART_CR1_UE_Msk                                 /*!< LPUART enabled */
#define LPUART_CR1_UESM_Pos                       (1U)
#define LPUART_CR1_UESM_Msk                       (0x1UL<<LPUART_CR1_UESM_Pos)                      /*!< 0x00000002 */
#define LPUART_CR1_UESM                           LPUART_CR1_UESM_Msk                               /*!< LPUART enabled in Stop mode */
#define LPUART_CR1_RE_Pos                         (2U)
#define LPUART_CR1_RE_Msk                         (0x1UL<<LPUART_CR1_RE_Pos)                        /*!< 0x00000004 */
#define LPUART_CR1_RE                             LPUART_CR1_RE_Msk                                 /*!< Receive enable */
#define LPUART_CR1_TE_Pos                         (3U)
#define LPUART_CR1_TE_Msk                         (0x1UL<<LPUART_CR1_TE_Pos)                        /*!< 0x00000008 */
#define LPUART_CR1_TE                             LPUART_CR1_TE_Msk                                 /*!< Transfer enable */
#define LPUART_CR1_IDLEIE_Pos                     (4U)
#define LPUART_CR1_IDLEIE_Msk                     (0x1UL<<LPUART_CR1_IDLEIE_Pos)                    /*!< 0x00000010 */
#define LPUART_CR1_IDLEIE                         LPUART_CR1_IDLEIE_Msk                             /*!< IDLE interrupt enable */
#define LPUART_CR1_RXFNEIE_Pos                    (5U)
#define LPUART_CR1_RXFNEIE_Msk                    (0x1UL<<LPUART_CR1_RXFNEIE_Pos)                   /*!< 0x00000020 */
#define LPUART_CR1_RXFNEIE                        LPUART_CR1_RXFNEIE_Msk                            /*!< RXFIFO non-null interrupt enable */
#define LPUART_CR1_TCIE_Pos                       (6U)
#define LPUART_CR1_TCIE_Msk                       (0x1UL<<LPUART_CR1_TCIE_Pos)                      /*!< 0x00000040 */
#define LPUART_CR1_TCIE                           LPUART_CR1_TCIE_Msk                               /*!< End of Transfer interrupt enabled */
#define LPUART_CR1_TXFNFIE_Pos                    (7U)
#define LPUART_CR1_TXFNFIE_Msk                    (0x1UL<<LPUART_CR1_TXFNFIE_Pos)                   /*!< 0x00000080 */
#define LPUART_CR1_TXFNFIE                        LPUART_CR1_TXFNFIE_Msk                            /*!< TXFIFO is not full interrupt enabled */
#define LPUART_CR1_PEIE_Pos                       (8U)
#define LPUART_CR1_PEIE_Msk                       (0x1UL<<LPUART_CR1_PEIE_Pos)                      /*!< 0x00000100 */
#define LPUART_CR1_PEIE                           LPUART_CR1_PEIE_Msk                               /*!< PE interrupt enable */
#define LPUART_CR1_PS_Pos                         (9U)
#define LPUART_CR1_PS_Msk                         (0x1UL<<LPUART_CR1_PS_Pos)                        /*!< 0x00000200 */
#define LPUART_CR1_PS                             LPUART_CR1_PS_Msk                                 /*!< Parity selection */
#define LPUART_CR1_PCE_Pos                        (10U)
#define LPUART_CR1_PCE_Msk                        (0x1UL<<LPUART_CR1_PCE_Pos)                       /*!< 0x00000400 */
#define LPUART_CR1_PCE                            LPUART_CR1_PCE_Msk                                /*!< Parity control */
#define LPUART_CR1_WAKE_Pos                       (11U)
#define LPUART_CR1_WAKE_Msk                       (0x1UL<<LPUART_CR1_WAKE_Pos)                      /*!< 0x00000800 */
#define LPUART_CR1_WAKE                           LPUART_CR1_WAKE_Msk                               /*!< Receive wake-up mode */
#define LPUART_CR1_M0_Pos                         (12U)
#define LPUART_CR1_M0_Msk                         (0x1UL<<LPUART_CR1_M0_Pos)                        /*!< 0x00001000 */
#define LPUART_CR1_M0                             LPUART_CR1_M0_Msk                                 /*!< Configure the word length in combination with M1 */
#define LPUART_CR1_MME_Pos                        (13U)
#define LPUART_CR1_MME_Msk                        (0x1UL<<LPUART_CR1_MME_Pos)                       /*!< 0x00002000 */
#define LPUART_CR1_MME                            LPUART_CR1_MME_Msk                                /*!< Silent mode enabled */
#define LPUART_CR1_CMIE_Pos                       (14U)
#define LPUART_CR1_CMIE_Msk                       (0x1UL<<LPUART_CR1_CMIE_Pos)                      /*!< 0x00004000 */
#define LPUART_CR1_CMIE                           LPUART_CR1_CMIE_Msk                               /*!< Character match interrupt enabled */
#define LPUART_CR1_DEDT_Pos                       (16U)
#define LPUART_CR1_DEDT_Msk                       (0x1FUL<<LPUART_CR1_DEDT_Pos)                     /*!< 0x001F0000 */
#define LPUART_CR1_DEDT                           LPUART_CR1_DEDT_Msk                               /*!< The time between the transmit frame stop bit and the invalid DE (driver enable) signal */
#define LPUART_CR1_DEDT_0                         (0x1UL<<LPUART_CR1_DEDT_Pos)                      /*!< 0x00010000 */
#define LPUART_CR1_DEDT_1                         (0x2UL<<LPUART_CR1_DEDT_Pos)                      /*!< 0x00020000 */
#define LPUART_CR1_DEDT_2                         (0x4UL<<LPUART_CR1_DEDT_Pos)                      /*!< 0x00040000 */
#define LPUART_CR1_DEDT_3                         (0x8UL<<LPUART_CR1_DEDT_Pos)                      /*!< 0x00080000 */
#define LPUART_CR1_DEDT_4                         (0x10UL<<LPUART_CR1_DEDT_Pos)                     /*!< 0x00100000 */
#define LPUART_CR1_DEAT_Pos                       (21U)
#define LPUART_CR1_DEAT_Msk                       (0x1FUL<<LPUART_CR1_DEAT_Pos)                     /*!< 0x03E00000 */
#define LPUART_CR1_DEAT                           LPUART_CR1_DEAT_Msk                               /*!< The time between the DE (driver enable) signal validity and the start bit */
#define LPUART_CR1_DEAT_0                         (0x1UL<<LPUART_CR1_DEAT_Pos)                      /*!< 0x00200000 */
#define LPUART_CR1_DEAT_1                         (0x2UL<<LPUART_CR1_DEAT_Pos)                      /*!< 0x00400000 */
#define LPUART_CR1_DEAT_2                         (0x4UL<<LPUART_CR1_DEAT_Pos)                      /*!< 0x00800000 */
#define LPUART_CR1_DEAT_3                         (0x8UL<<LPUART_CR1_DEAT_Pos)                      /*!< 0x01000000 */
#define LPUART_CR1_DEAT_4                         (0x10UL<<LPUART_CR1_DEAT_Pos)                     /*!< 0x02000000 */
#define LPUART_CR1_M1_Pos                         (28U)
#define LPUART_CR1_M1_Msk                         (0x1UL<<LPUART_CR1_M1_Pos)                        /*!< 0x10000000 */
#define LPUART_CR1_M1                             LPUART_CR1_M1_Msk                                 /*!< The value of {M1,M0} the configurate length */
#define LPUART_CR1_FIFOEN_Pos                     (29U)
#define LPUART_CR1_FIFOEN_Msk                     (0x1UL<<LPUART_CR1_FIFOEN_Pos)                    /*!< 0x20000000 */
#define LPUART_CR1_FIFOEN                         LPUART_CR1_FIFOEN_Msk                             /*!< FIFO mode enabled */
#define LPUART_CR1_TXFEIE_Pos                     (30U)
#define LPUART_CR1_TXFEIE_Msk                     (0x1UL<<LPUART_CR1_TXFEIE_Pos)                    /*!< 0x40000000 */
#define LPUART_CR1_TXFEIE                         LPUART_CR1_TXFEIE_Msk                             /*!< TXFIFO null interrupt enabled */
#define LPUART_CR1_RXFFIE_Pos                     (31U)
#define LPUART_CR1_RXFFIE_Msk                     (0x1UL<<LPUART_CR1_RXFFIE_Pos)                    /*!< 0x80000000 */
#define LPUART_CR1_RXFFIE                         LPUART_CR1_RXFFIE_Msk                             /*!< RXFIFO full interrupt enabled */

/********************************* Bit definition for LPUART_CR2 register *******************************************/
#define LPUART_CR2_ADDM7_Pos                      (4U)
#define LPUART_CR2_ADDM7_Msk                      (0x1UL<<LPUART_CR2_ADDM7_Pos)                     /*!< 0x00000010 */
#define LPUART_CR2_ADDM7                          LPUART_CR2_ADDM7_Msk                              /*!< 7bit/4bit address detection configuration */
#define LPUART_CR2_STOP_Pos                       (12U)
#define LPUART_CR2_STOP_Msk                       (0x3UL<<LPUART_CR2_STOP_Pos)                      /*!< 0x00003000 */
#define LPUART_CR2_STOP                           LPUART_CR2_STOP_Msk                               /*!< Stop bit configuration */
#define LPUART_CR2_STOP_0                         (0x1UL<<LPUART_CR2_STOP_Pos)                      /*!< 0x00001000 */
#define LPUART_CR2_STOP_1                         (0x2UL<<LPUART_CR2_STOP_Pos)                      /*!< 0x00002000 */
#define LPUART_CR2_SWAP_Pos                       (15U)
#define LPUART_CR2_SWAP_Msk                       (0x1UL<<LPUART_CR2_SWAP_Pos)                      /*!< 0x00008000 */
#define LPUART_CR2_SWAP                           LPUART_CR2_SWAP_Msk                               /*!< TX/RX pin interchangeable */
#define LPUART_CR2_RXINV_Pos                      (16U)
#define LPUART_CR2_RXINV_Msk                      (0x1UL<<LPUART_CR2_RXINV_Pos)                     /*!< 0x00010000 */
#define LPUART_CR2_RXINV                          LPUART_CR2_RXINV_Msk                              /*!< The RX pin is active level inverting */
#define LPUART_CR2_TXINV_Pos                      (17U)
#define LPUART_CR2_TXINV_Msk                      (0x1UL<<LPUART_CR2_TXINV_Pos)                     /*!< 0x00020000 */
#define LPUART_CR2_TXINV                          LPUART_CR2_TXINV_Msk                              /*!< TX pin active level inverted */
#define LPUART_CR2_DATAINV_Pos                    (18U)
#define LPUART_CR2_DATAINV_Msk                    (0x1UL<<LPUART_CR2_DATAINV_Pos)                   /*!< 0x00040000 */
#define LPUART_CR2_DATAINV                        LPUART_CR2_DATAINV_Msk                            /*!< Inverse binary data processing */
#define LPUART_CR2_MSBFIRST_Pos                   (19U)
#define LPUART_CR2_MSBFIRST_Msk                   (0x1UL<<LPUART_CR2_MSBFIRST_Pos)                  /*!< 0x00080000 */
#define LPUART_CR2_MSBFIRST                       LPUART_CR2_MSBFIRST_Msk                           /*!< MSB first */
#define LPUART_CR2_TXOE_ALWAYS_ON_Pos             (20U)
#define LPUART_CR2_TXOE_ALWAYS_ON_Msk             (0x1UL<<LPUART_CR2_TXOE_ALWAYS_ON_Pos)            /*!< 0x00100000 */
#define LPUART_CR2_TXOE_ALWAYS_ON                 LPUART_CR2_TXOE_ALWAYS_ON_Msk                     /*!< LPUART output control */
#define LPUART_CR2_ADD_Pos                        (24U)
#define LPUART_CR2_ADD_Msk                        (0xFFUL<<LPUART_CR2_ADD_Pos)                      /*!< 0xFF000000 */
#define LPUART_CR2_ADD                            LPUART_CR2_ADD_Msk                                /*!< LPUART address */

/********************************* Bit definition for LPUART_CR3 register *******************************************/
#define LPUART_CR3_EIE_Pos                        (0U)
#define LPUART_CR3_EIE_Msk                        (0x1UL<<LPUART_CR3_EIE_Pos)                       /*!< 0x00000001 */
#define LPUART_CR3_EIE                            LPUART_CR3_EIE_Msk                                /*!< Error interrupts are enabled */
#define LPUART_CR3_HDSEL_Pos                      (3U)
#define LPUART_CR3_HDSEL_Msk                      (0x1UL<<LPUART_CR3_HDSEL_Pos)                     /*!< 0x00000008 */
#define LPUART_CR3_HDSEL                          LPUART_CR3_HDSEL_Msk                              /*!< Half-duplex selection */
#define LPUART_CR3_DMAR_Pos                       (6U)
#define LPUART_CR3_DMAR_Msk                       (0x1UL<<LPUART_CR3_DMAR_Pos)                      /*!< 0x00000040 */
#define LPUART_CR3_DMAR                           LPUART_CR3_DMAR_Msk                               /*!< Enable DMA on reception */
#define LPUART_CR3_DMAT_Pos                       (7U)
#define LPUART_CR3_DMAT_Msk                       (0x1UL<<LPUART_CR3_DMAT_Pos)                      /*!< 0x00000080 */
#define LPUART_CR3_DMAT                           LPUART_CR3_DMAT_Msk                               /*!< Enable DMA while transmitting */
#define LPUART_CR3_RTSE_Pos                       (8U)
#define LPUART_CR3_RTSE_Msk                       (0x1UL<<LPUART_CR3_RTSE_Pos)                      /*!< 0x00000100 */
#define LPUART_CR3_RTSE                           LPUART_CR3_RTSE_Msk                               /*!< RTS enabled */
#define LPUART_CR3_CTSE_Pos                       (9U)
#define LPUART_CR3_CTSE_Msk                       (0x1UL<<LPUART_CR3_CTSE_Pos)                      /*!< 0x00000200 */
#define LPUART_CR3_CTSE                           LPUART_CR3_CTSE_Msk                               /*!< CTS enabled */
#define LPUART_CR3_CTSIE_Pos                      (10U)
#define LPUART_CR3_CTSIE_Msk                      (0x1UL<<LPUART_CR3_CTSIE_Pos)                     /*!< 0x00000400 */
#define LPUART_CR3_CTSIE                          LPUART_CR3_CTSIE_Msk                              /*!< CTS interrupt enable */
#define LPUART_CR3_OVRDIS_Pos                     (12U)
#define LPUART_CR3_OVRDIS_Msk                     (0x1UL<<LPUART_CR3_OVRDIS_Pos)                    /*!< 0x00001000 */
#define LPUART_CR3_OVRDIS                         LPUART_CR3_OVRDIS_Msk                             /*!< Overrun is prohibited */
#define LPUART_CR3_DDRE_Pos                       (13U)
#define LPUART_CR3_DDRE_Msk                       (0x1UL<<LPUART_CR3_DDRE_Pos)                      /*!< 0x00002000 */
#define LPUART_CR3_DDRE                           LPUART_CR3_DDRE_Msk                               /*!< Whether DMA is disabled when receiving an error */
#define LPUART_CR3_DEM_Pos                        (14U)
#define LPUART_CR3_DEM_Msk                        (0x1UL<<LPUART_CR3_DEM_Pos)                       /*!< 0x00004000 */
#define LPUART_CR3_DEM                            LPUART_CR3_DEM_Msk                                /*!< DE mode enabled */
#define LPUART_CR3_DEP_Pos                        (15U)
#define LPUART_CR3_DEP_Msk                        (0x1UL<<LPUART_CR3_DEP_Pos)                       /*!< 0x00008000 */
#define LPUART_CR3_DEP                            LPUART_CR3_DEP_Msk                                /*!< DE polarity selection */
#define LPUART_CR3_WUS_Pos                        (20U)
#define LPUART_CR3_WUS_Msk                        (0x3UL<<LPUART_CR3_WUS_Pos)                       /*!< 0x00300000 */
#define LPUART_CR3_WUS                            LPUART_CR3_WUS_Msk                                /*!< Low-power wake-up options */
#define LPUART_CR3_WUS_0                          (0x1UL<<LPUART_CR3_WUS_Pos)                       /*!< 0x00100000 */
#define LPUART_CR3_WUS_1                          (0x2UL<<LPUART_CR3_WUS_Pos)                       /*!< 0x00200000 */
#define LPUART_CR3_WUFIE_Pos                      (22U)
#define LPUART_CR3_WUFIE_Msk                      (0x1UL<<LPUART_CR3_WUFIE_Pos)                     /*!< 0x00400000 */
#define LPUART_CR3_WUFIE                          LPUART_CR3_WUFIE_Msk                              /*!< Low-power wake-up interrupt enable */
#define LPUART_CR3_TXFTIE_Pos                     (23U)
#define LPUART_CR3_TXFTIE_Msk                     (0x1UL<<LPUART_CR3_TXFTIE_Pos)                    /*!< 0x00800000 */
#define LPUART_CR3_TXFTIE                         LPUART_CR3_TXFTIE_Msk                             /*!< TXFIFO threshold interrupt enabled */
#define LPUART_CR3_RXFTCFG_Pos                    (25U)
#define LPUART_CR3_RXFTCFG_Msk                    (0x7UL<<LPUART_CR3_RXFTCFG_Pos)                   /*!< 0x0E000000 */
#define LPUART_CR3_RXFTCFG                        LPUART_CR3_RXFTCFG_Msk                            /*!< RXFIFO full threshold configuration */
#define LPUART_CR3_RXFTCFG_0                      (0x1UL<<LPUART_CR3_RXFTCFG_Pos)                   /*!< 0x02000000 */
#define LPUART_CR3_RXFTCFG_1                      (0x2UL<<LPUART_CR3_RXFTCFG_Pos)                   /*!< 0x04000000 */
#define LPUART_CR3_RXFTCFG_2                      (0x4UL<<LPUART_CR3_RXFTCFG_Pos)                   /*!< 0x08000000 */
#define LPUART_CR3_RXFTIE_Pos                     (28U)
#define LPUART_CR3_RXFTIE_Msk                     (0x1UL<<LPUART_CR3_RXFTIE_Pos)                    /*!< 0x10000000 */
#define LPUART_CR3_RXFTIE                         LPUART_CR3_RXFTIE_Msk                             /*!< RXFIFO threshold interrupt enabled */
#define LPUART_CR3_TXFTCFG_Pos                    (29U)
#define LPUART_CR3_TXFTCFG_Msk                    (0x7UL<<LPUART_CR3_TXFTCFG_Pos)                   /*!< 0xE0000000 */
#define LPUART_CR3_TXFTCFG                        LPUART_CR3_TXFTCFG_Msk                            /*!< TXFIFO threshold configuration */
#define LPUART_CR3_TXFTCFG_0                      (0x1UL<<LPUART_CR3_TXFTCFG_Pos)                   /*!< 0x20000000 */
#define LPUART_CR3_TXFTCFG_1                      (0x2UL<<LPUART_CR3_TXFTCFG_Pos)                   /*!< 0x40000000 */
#define LPUART_CR3_TXFTCFG_2                      (0x4UL<<LPUART_CR3_TXFTCFG_Pos)                   /*!< 0x80000000 */

/********************************* Bit definition for LPUART_BRR register *******************************************/
#define LPUART_BRR_BBR_Pos                        (0U)
#define LPUART_BRR_BBR_Msk                        (0xFFFFFUL<<LPUART_BRR_BBR_Pos)                   /*!< 0x000FFFFF */
#define LPUART_BRR_BBR                            LPUART_BRR_BBR_Msk                                /*!< LPUART baud rate */

/********************************* Bit definition for LPUART_RQR register *******************************************/
#define LPUART_RQR_SBKRQ_Pos                      (1U)
#define LPUART_RQR_SBKRQ_Msk                      (0x1UL<<LPUART_RQR_SBKRQ_Pos)                     /*!< 0x00000002 */
#define LPUART_RQR_SBKRQ                          LPUART_RQR_SBKRQ_Msk                              /*!< Send an abort request */
#define LPUART_RQR_MMRQ_Pos                       (2U)
#define LPUART_RQR_MMRQ_Msk                       (0x1UL<<LPUART_RQR_MMRQ_Pos)                      /*!< 0x00000004 */
#define LPUART_RQR_MMRQ                           LPUART_RQR_MMRQ_Msk                               /*!< Silent mode request */
#define LPUART_RQR_RXFRQ_Pos                      (3U)
#define LPUART_RQR_RXFRQ_Msk                      (0x1UL<<LPUART_RQR_RXFRQ_Pos)                     /*!< 0x00000008 */
#define LPUART_RQR_RXFRQ                          LPUART_RQR_RXFRQ_Msk                              /*!< Receive a data refresh request */
#define LPUART_RQR_TXFRQ_Pos                      (4U)
#define LPUART_RQR_TXFRQ_Msk                      (0x1UL<<LPUART_RQR_TXFRQ_Pos)                     /*!< 0x00000010 */
#define LPUART_RQR_TXFRQ                          LPUART_RQR_TXFRQ_Msk                              /*!< Route a data refresh request */

/********************************* Bit definition for LPUART_ISR register *******************************************/
#define LPUART_ISR_PE_Pos                         (0U)
#define LPUART_ISR_PE_Msk                         (0x1UL<<LPUART_ISR_PE_Pos)                        /*!< 0x00000001 */
#define LPUART_ISR_PE                             LPUART_ISR_PE_Msk                                 /*!< Parity error */
#define LPUART_ISR_FE_Pos                         (1U)
#define LPUART_ISR_FE_Msk                         (0x1UL<<LPUART_ISR_FE_Pos)                        /*!< 0x00000002 */
#define LPUART_ISR_FE                             LPUART_ISR_FE_Msk                                 /*!< Frame error flag */
#define LPUART_ISR_NE_Pos                         (2U)
#define LPUART_ISR_NE_Msk                         (0x1UL<<LPUART_ISR_NE_Pos)                        /*!< 0x00000004 */
#define LPUART_ISR_NE                             LPUART_ISR_NE_Msk                                 /*!< START bit noise flag */
#define LPUART_ISR_ORE_Pos                        (3U)
#define LPUART_ISR_ORE_Msk                        (0x1UL<<LPUART_ISR_ORE_Pos)                       /*!< 0x00000008 */
#define LPUART_ISR_ORE                            LPUART_ISR_ORE_Msk                                /*!< Overrun error flag */
#define LPUART_ISR_IDLE_Pos                       (4U)
#define LPUART_ISR_IDLE_Msk                       (0x1UL<<LPUART_ISR_IDLE_Pos)                      /*!< 0x00000010 */
#define LPUART_ISR_IDLE                           LPUART_ISR_IDLE_Msk                               /*!< idle flag */
#define LPUART_ISR_RXFNE_Pos                      (5U)
#define LPUART_ISR_RXFNE_Msk                      (0x1UL<<LPUART_ISR_RXFNE_Pos)                     /*!< 0x00000020 */
#define LPUART_ISR_RXFNE                          LPUART_ISR_RXFNE_Msk                              /*!< RX register not empty */
#define LPUART_ISR_TC_Pos                         (6U)
#define LPUART_ISR_TC_Msk                         (0x1UL<<LPUART_ISR_TC_Pos)                        /*!< 0x00000040 */
#define LPUART_ISR_TC                             LPUART_ISR_TC_Msk                                 /*!< Transmission completion flag */
#define LPUART_ISR_TXFNF_Pos                      (7U)
#define LPUART_ISR_TXFNF_Msk                      (0x1UL<<LPUART_ISR_TXFNF_Pos)                     /*!< 0x00000080 */
#define LPUART_ISR_TXFNF                          LPUART_ISR_TXFNF_Msk                              /*!< TX register not full */
#define LPUART_ISR_CTSIF_Pos                      (9U)
#define LPUART_ISR_CTSIF_Msk                      (0x1UL<<LPUART_ISR_CTSIF_Pos)                     /*!< 0x00000200 */
#define LPUART_ISR_CTSIF                          LPUART_ISR_CTSIF_Msk                              /*!< CTS interrupt flag */
#define LPUART_ISR_CTS_Pos                        (10U)
#define LPUART_ISR_CTS_Msk                        (0x1UL<<LPUART_ISR_CTS_Pos)                       /*!< 0x00000400 */
#define LPUART_ISR_CTS                            LPUART_ISR_CTS_Msk                                /*!< CTS flag */
#define LPUART_ISR_BUSY_Pos                       (16U)
#define LPUART_ISR_BUSY_Msk                       (0x1UL<<LPUART_ISR_BUSY_Pos)                      /*!< 0x00010000 */
#define LPUART_ISR_BUSY                           LPUART_ISR_BUSY_Msk                               /*!< Busy flag */
#define LPUART_ISR_CMF_Pos                        (17U)
#define LPUART_ISR_CMF_Msk                        (0x1UL<<LPUART_ISR_CMF_Pos)                       /*!< 0x00020000 */
#define LPUART_ISR_CMF                            LPUART_ISR_CMF_Msk                                /*!< Address match flag */
#define LPUART_ISR_SBKF_Pos                       (18U)
#define LPUART_ISR_SBKF_Msk                       (0x1UL<<LPUART_ISR_SBKF_Pos)                      /*!< 0x00040000 */
#define LPUART_ISR_SBKF                           LPUART_ISR_SBKF_Msk                               /*!< Send abort flag */
#define LPUART_ISR_RWU_Pos                        (19U)
#define LPUART_ISR_RWU_Msk                        (0x1UL<<LPUART_ISR_RWU_Pos)                       /*!< 0x00080000 */
#define LPUART_ISR_RWU                            LPUART_ISR_RWU_Msk                                /*!< Receive Mute mode wake-up flag */
#define LPUART_ISR_WUF_Pos                        (20U)
#define LPUART_ISR_WUF_Msk                        (0x1UL<<LPUART_ISR_WUF_Pos)                       /*!< 0x00100000 */
#define LPUART_ISR_WUF                            LPUART_ISR_WUF_Msk                                /*!< Wake flag from low-power mode */
#define LPUART_ISR_TEACK_Pos                      (21U)
#define LPUART_ISR_TEACK_Msk                      (0x1UL<<LPUART_ISR_TEACK_Pos)                     /*!< 0x00200000 */
#define LPUART_ISR_TEACK                          LPUART_ISR_TEACK_Msk                              /*!< Transport enable acknowledgement flag */
#define LPUART_ISR_REACK_Pos                      (22U)
#define LPUART_ISR_REACK_Msk                      (0x1UL<<LPUART_ISR_REACK_Pos)                     /*!< 0x00400000 */
#define LPUART_ISR_REACK                          LPUART_ISR_REACK_Msk                              /*!< Receive the enable acknowledgment flag */
#define LPUART_ISR_TXFE_Pos                       (23U)
#define LPUART_ISR_TXFE_Msk                       (0x1UL<<LPUART_ISR_TXFE_Pos)                      /*!< 0x00800000 */
#define LPUART_ISR_TXFE                           LPUART_ISR_TXFE_Msk                               /*!< TXFIFO empty */
#define LPUART_ISR_RXFF_Pos                       (24U)
#define LPUART_ISR_RXFF_Msk                       (0x1UL<<LPUART_ISR_RXFF_Pos)                      /*!< 0x01000000 */
#define LPUART_ISR_RXFF                           LPUART_ISR_RXFF_Msk                               /*!< RXFIFO full logo */
#define LPUART_ISR_RXFT_Pos                       (26U)
#define LPUART_ISR_RXFT_Msk                       (0x1UL<<LPUART_ISR_RXFT_Pos)                      /*!< 0x04000000 */
#define LPUART_ISR_RXFT                           LPUART_ISR_RXFT_Msk                               /*!< RCFIFO threshold flag */
#define LPUART_ISR_TXFT_Pos                       (27U)
#define LPUART_ISR_TXFT_Msk                       (0x1UL<<LPUART_ISR_TXFT_Pos)                      /*!< 0x08000000 */
#define LPUART_ISR_TXFT                           LPUART_ISR_TXFT_Msk                               /*!< TXFIFO threshold flag */

/********************************* Bit definition for LPUART_ICR register *******************************************/
#define LPUART_ICR_PECF_Pos                       (0U)
#define LPUART_ICR_PECF_Msk                       (0x1UL<<LPUART_ICR_PECF_Pos)                      /*!< 0x00000001 */
#define LPUART_ICR_PECF                           LPUART_ICR_PECF_Msk                               /*!< Check value error flag reset */
#define LPUART_ICR_FECF_Pos                       (1U)
#define LPUART_ICR_FECF_Msk                       (0x1UL<<LPUART_ICR_FECF_Pos)                      /*!< 0x00000002 */
#define LPUART_ICR_FECF                           LPUART_ICR_FECF_Msk                               /*!< Frame error flag reset */
#define LPUART_ICR_NECF_Pos                       (2U)
#define LPUART_ICR_NECF_Msk                       (0x1UL<<LPUART_ICR_NECF_Pos)                      /*!< 0x00000004 */
#define LPUART_ICR_NECF                           LPUART_ICR_NECF_Msk                               /*!< Clear the START bit noise flag */
#define LPUART_ICR_ORECF_Pos                      (3U)
#define LPUART_ICR_ORECF_Msk                      (0x1UL<<LPUART_ICR_ORECF_Pos)                     /*!< 0x00000008 */
#define LPUART_ICR_ORECF                          LPUART_ICR_ORECF_Msk                              /*!< Overrun error flag reset */
#define LPUART_ICR_IDLECF_Pos                     (4U)
#define LPUART_ICR_IDLECF_Msk                     (0x1UL<<LPUART_ICR_IDLECF_Pos)                    /*!< 0x00000010 */
#define LPUART_ICR_IDLECF                         LPUART_ICR_IDLECF_Msk                             /*!< Clear idle flag  */
#define LPUART_ICR_TCCF_Pos                       (6U)
#define LPUART_ICR_TCCF_Msk                       (0x1UL<<LPUART_ICR_TCCF_Pos)                      /*!< 0x00000040 */
#define LPUART_ICR_TCCF                           LPUART_ICR_TCCF_Msk                               /*!< Transfer completion flag reset */
#define LPUART_ICR_CTSCF_Pos                      (9U)
#define LPUART_ICR_CTSCF_Msk                      (0x1UL<<LPUART_ICR_CTSCF_Pos)                     /*!< 0x00000200 */
#define LPUART_ICR_CTSCF                          LPUART_ICR_CTSCF_Msk                              /*!< CTS flag reset */
#define LPUART_ICR_CMCF_Pos                       (17U)
#define LPUART_ICR_CMCF_Msk                       (0x1UL<<LPUART_ICR_CMCF_Pos)                      /*!< 0x00020000 */
#define LPUART_ICR_CMCF                           LPUART_ICR_CMCF_Msk                               /*!< Address matching flag reset */
#define LPUART_ICR_WUCF_Pos                       (20U)
#define LPUART_ICR_WUCF_Msk                       (0x1UL<<LPUART_ICR_WUCF_Pos)                      /*!< 0x00100000 */
#define LPUART_ICR_WUCF                           LPUART_ICR_WUCF_Msk                               /*!< Low power wake-up flag reset */

/********************************* Bit definition for LPUART_RDR register *******************************************/
#define LPUART_RDR_RDR_Pos                        (0U)
#define LPUART_RDR_RDR_Msk                        (0x1FFUL<<LPUART_RDR_RDR_Pos)                     /*!< 0x000001FF */
#define LPUART_RDR_RDR                            LPUART_RDR_RDR_Msk                                /*!< Receive Data Register */

/********************************* Bit definition for LPUART_TDR register *******************************************/
#define LPUART_TDR_TDR_Pos                        (0U)
#define LPUART_TDR_TDR_Msk                        (0x1FFUL<<LPUART_TDR_TDR_Pos)                     /*!< 0x000001FF */
#define LPUART_TDR_TDR                            LPUART_TDR_TDR_Msk                                /*!< Transmit Data Register */

/********************************* Bit definition for LPUART_PRESC register *****************************************/
#define LPUART_PRESC_PRESCALER_Pos                (0U)
#define LPUART_PRESC_PRESCALER_Msk                (0xFUL<<LPUART_PRESC_PRESCALER_Pos)               /*!< 0x0000000F */
#define LPUART_PRESC_PRESCALER                    LPUART_PRESC_PRESCALER_Msk                        /*!< Input clock prescaler register */
#define LPUART_PRESC_PRESCALER_0                  (0x1UL<<LPUART_PRESC_PRESCALER_Pos)               /*!< 0x00000001 */
#define LPUART_PRESC_PRESCALER_1                  (0x2UL<<LPUART_PRESC_PRESCALER_Pos)               /*!< 0x00000002 */
#define LPUART_PRESC_PRESCALER_2                  (0x4UL<<LPUART_PRESC_PRESCALER_Pos)               /*!< 0x00000004 */
#define LPUART_PRESC_PRESCALER_3                  (0x8UL<<LPUART_PRESC_PRESCALER_Pos)               /*!< 0x00000008 */

/********************************************************************************************************************/
/********************************* PWR ******************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for PWR_CR1 register **********************************************/
#define PWR_CR1_LPMS_Pos                          (0U)
#define PWR_CR1_LPMS_Msk                          (0x3UL<<PWR_CR1_LPMS_Pos)                         /*!< 0x00000003 */
#define PWR_CR1_LPMS                              PWR_CR1_LPMS_Msk
#define PWR_CR1_LPMS_0                            (0x1UL<<PWR_CR1_LPMS_Pos)                         /*!< 0x00000001 */
#define PWR_CR1_LPMS_1                            (0x2UL<<PWR_CR1_LPMS_Pos)                         /*!< 0x00000002 */
#define PWR_CR1_DBP_Pos                           (8U)
#define PWR_CR1_DBP_Msk                           (0x1UL<<PWR_CR1_DBP_Pos)                          /*!< 0x00000100 */
#define PWR_CR1_DBP                               PWR_CR1_DBP_Msk                                   
#define PWR_CR1_MR_VSEL_Pos                       (12U)
#define PWR_CR1_MR_VSEL_Msk                       (0x3UL<<PWR_CR1_MR_VSEL_Pos)                      /*!< 0x00003000 */
#define PWR_CR1_MR_VSEL                           PWR_CR1_MR_VSEL_Msk
#define PWR_CR1_MR_VSEL_0                         (0x1UL<<PWR_CR1_MR_VSEL_Pos)                      /*!< 0x00001000 */
#define PWR_CR1_MR_VSEL_1                         (0x2UL<<PWR_CR1_MR_VSEL_Pos)                      /*!< 0x00002000 */
#define PWR_CR1_LPR_Pos                           (14U)
#define PWR_CR1_LPR_Msk                           (0x1UL<<PWR_CR1_LPR_Pos)                          /*!< 0x00004000 */
#define PWR_CR1_LPR                               PWR_CR1_LPR_Msk                                   
#define PWR_CR1_HSION_CTRL_Pos                    (16U)
#define PWR_CR1_HSION_CTRL_Msk                    (0x1UL<<PWR_CR1_HSION_CTRL_Pos)                   /*!< 0x00010000 */
#define PWR_CR1_HSION_CTRL                        PWR_CR1_HSION_CTRL_Msk                            
#define PWR_CR1_FLS_WUPT_Pos                      (17U)
#define PWR_CR1_FLS_WUPT_Msk                      (0x3UL<<PWR_CR1_FLS_WUPT_Pos)                     /*!< 0x00060000 */
#define PWR_CR1_FLS_WUPT                          PWR_CR1_FLS_WUPT_Msk
#define PWR_CR1_FLS_WUPT_0                        (0x1UL<<PWR_CR1_FLS_WUPT_Pos)                     /*!< 0x00020000 */
#define PWR_CR1_FLS_WUPT_1                        (0x2UL<<PWR_CR1_FLS_WUPT_Pos)                     /*!< 0x00040000 */
#define PWR_CR1_STDBY_MRRDY_WAIT_Pos              (19U)
#define PWR_CR1_STDBY_MRRDY_WAIT_Msk              (0x3UL<<PWR_CR1_STDBY_MRRDY_WAIT_Pos)             /*!< 0x00180000 */
#define PWR_CR1_STDBY_MRRDY_WAIT                  PWR_CR1_STDBY_MRRDY_WAIT_Msk
#define PWR_CR1_STDBY_MRRDY_WAIT_0                (0x1UL<<PWR_CR1_STDBY_MRRDY_WAIT_Pos)             /*!< 0x00080000 */
#define PWR_CR1_STDBY_MRRDY_WAIT_1                (0x2UL<<PWR_CR1_STDBY_MRRDY_WAIT_Pos)             /*!< 0x00100000 */

/********************************* Bit definition for PWR_CR2 register **********************************************/
#define PWR_CR2_PVDE_Pos                          (0U)
#define PWR_CR2_PVDE_Msk                          (0x1UL<<PWR_CR2_PVDE_Pos)                         /*!< 0x00000001 */
#define PWR_CR2_PVDE                              PWR_CR2_PVDE_Msk                                  
#define PWR_CR2_PLS_Pos                           (1U)
#define PWR_CR2_PLS_Msk                           (0x7UL<<PWR_CR2_PLS_Pos)                          /*!< 0x0000000E */
#define PWR_CR2_PLS                               PWR_CR2_PLS_Msk
#define PWR_CR2_PLS_0                             (0x1UL<<PWR_CR2_PLS_Pos)                          /*!< 0x00000002 */
#define PWR_CR2_PLS_1                             (0x2UL<<PWR_CR2_PLS_Pos)                          /*!< 0x00000004 */
#define PWR_CR2_PLS_2                             (0x4UL<<PWR_CR2_PLS_Pos)                          /*!< 0x00000008 */

/*!< PVD level configuration */
#define PWR_CR2_PLS_LEV0                          0x00000000U                                       /*!< PVD level 1.8V */
#define PWR_CR2_PLS_LEV1                          0x00000002U                                       /*!< PVD level 2.0V */
#define PWR_CR2_PLS_LEV2                          0x00000004U                                       /*!< PVD level 2.2V */
#define PWR_CR2_PLS_LEV3                          0x00000006U                                       /*!< PVD level 2.4V */
#define PWR_CR2_PLS_LEV4                          0x00000008U                                       /*!< PVD level 2.6V */
#define PWR_CR2_PLS_LEV5                          0x0000000AU                                       /*!< PVD level 2.8V */
#define PWR_CR2_PLS_LEV6                          0x0000000CU                                       /*!< PVD level 3.0V */
#define PWR_CR2_PLS_LEV7                          0x0000000EU                                       /*!< PVD_IN */

/* Legacy defines */
#define PWR_CR2_PLS_1V8                           PWR_CR2_PLS_LEV0
#define PWR_CR2_PLS_2V0                           PWR_CR2_PLS_LEV1
#define PWR_CR2_PLS_2V2                           PWR_CR2_PLS_LEV2
#define PWR_CR2_PLS_2V4                           PWR_CR2_PLS_LEV3
#define PWR_CR2_PLS_2V6                           PWR_CR2_PLS_LEV4
#define PWR_CR2_PLS_2V8                           PWR_CR2_PLS_LEV5
#define PWR_CR2_PLS_3V0                           PWR_CR2_PLS_LEV6
#define PWR_CR2_PLS_PVD_IN                        PWR_CR2_PLS_LEV7

#define PWR_CR2_FLTEN_Pos                         (8U)
#define PWR_CR2_FLTEN_Msk                         (0x1UL<<PWR_CR2_FLTEN_Pos)                        /*!< 0x00000100 */
#define PWR_CR2_FLTEN                             PWR_CR2_FLTEN_Msk                                 
#define PWR_CR2_FLT_CTRL_Pos                      (9U)
#define PWR_CR2_FLT_CTRL_Msk                      (0x7UL<<PWR_CR2_FLT_CTRL_Pos)                     /*!< 0x00000E00 */
#define PWR_CR2_FLT_CTRL                          PWR_CR2_FLT_CTRL_Msk
#define PWR_CR2_FLT_CTRL_0                        (0x1UL<<PWR_CR2_FLT_CTRL_Pos)                     /*!< 0x00000200 */
#define PWR_CR2_FLT_CTRL_1                        (0x2UL<<PWR_CR2_FLT_CTRL_Pos)                     /*!< 0x00000400 */
#define PWR_CR2_FLT_CTRL_2                        (0x4UL<<PWR_CR2_FLT_CTRL_Pos)                     /*!< 0x00000800 */

/********************************* Bit definition for PWR_CR3 register **********************************************/
#define PWR_CR3_EWUP1_Pos                         (0U)
#define PWR_CR3_EWUP1_Msk                         (0x1UL<<PWR_CR3_EWUP1_Pos)                        /*!< 0x00000001 */
#define PWR_CR3_EWUP1                             PWR_CR3_EWUP1_Msk                                 
#define PWR_CR3_EWUP2_Pos                         (1U)
#define PWR_CR3_EWUP2_Msk                         (0x1UL<<PWR_CR3_EWUP2_Pos)                        /*!< 0x00000002 */
#define PWR_CR3_EWUP2                             PWR_CR3_EWUP2_Msk                                 
#define PWR_CR3_EWUP3_Pos                         (2U)
#define PWR_CR3_EWUP3_Msk                         (0x1UL<<PWR_CR3_EWUP3_Pos)                        /*!< 0x00000004 */
#define PWR_CR3_EWUP3                             PWR_CR3_EWUP3_Msk                                 
#define PWR_CR3_EWUP4_Pos                         (3U)
#define PWR_CR3_EWUP4_Msk                         (0x1UL<<PWR_CR3_EWUP4_Pos)                        /*!< 0x00000008 */
#define PWR_CR3_EWUP4                             PWR_CR3_EWUP4_Msk                                 
#define PWR_CR3_EWUP5_Pos                         (4U)
#define PWR_CR3_EWUP5_Msk                         (0x1UL<<PWR_CR3_EWUP5_Pos)                        /*!< 0x00000010 */
#define PWR_CR3_EWUP5                             PWR_CR3_EWUP5_Msk                                 
#define PWR_CR3_EWUP_Pos                          (0U)
#define PWR_CR3_EWUP_Msk                          (0x1FUL<<PWR_CR3_EWUP_Pos)                        /*!< 0x00000001 */
#define PWR_CR3_EWUP                              PWR_CR3_EWUP_Msk                                 
#define PWR_CR3_RRS_Pos                           (8U)
#define PWR_CR3_RRS_Msk                           (0x1UL<<PWR_CR3_RRS_Pos)                          /*!< 0x00000100 */
#define PWR_CR3_RRS                               PWR_CR3_RRS_Msk                                   

/********************************* Bit definition for PWR_CR4 register **********************************************/
#define PWR_CR4_WP1_Pos                           (0U)
#define PWR_CR4_WP1_Msk                           (0x1UL<<PWR_CR4_WP1_Pos)                          /*!< 0x00000001 */
#define PWR_CR4_WP1                               PWR_CR4_WP1_Msk                                   
#define PWR_CR4_WP2_Pos                           (1U)
#define PWR_CR4_WP2_Msk                           (0x1UL<<PWR_CR4_WP2_Pos)                          /*!< 0x00000002 */
#define PWR_CR4_WP2                               PWR_CR4_WP2_Msk                                   
#define PWR_CR4_WP3_Pos                           (2U)
#define PWR_CR4_WP3_Msk                           (0x1UL<<PWR_CR4_WP3_Pos)                          /*!< 0x00000004 */
#define PWR_CR4_WP3                               PWR_CR4_WP3_Msk                                   
#define PWR_CR4_WP4_Pos                           (3U)
#define PWR_CR4_WP4_Msk                           (0x1UL<<PWR_CR4_WP4_Pos)                          /*!< 0x00000008 */
#define PWR_CR4_WP4                               PWR_CR4_WP4_Msk                                   
#define PWR_CR4_WP5_Pos                           (4U)
#define PWR_CR4_WP5_Msk                           (0x1UL<<PWR_CR4_WP5_Pos)                          /*!< 0x00000010 */
#define PWR_CR4_WP5                               PWR_CR4_WP5_Msk                                   

/********************************* Bit definition for PWR_SR register ***********************************************/
#define PWR_SR_WUF1_Pos                           (0U)
#define PWR_SR_WUF1_Msk                           (0x1UL<<PWR_SR_WUF1_Pos)                          /*!< 0x00000001 */
#define PWR_SR_WUF1                               PWR_SR_WUF1_Msk                                   
#define PWR_SR_WUF2_Pos                           (1U)
#define PWR_SR_WUF2_Msk                           (0x1UL<<PWR_SR_WUF2_Pos)                          /*!< 0x00000002 */
#define PWR_SR_WUF2                               PWR_SR_WUF2_Msk                                   
#define PWR_SR_WUF3_Pos                           (2U)
#define PWR_SR_WUF3_Msk                           (0x1UL<<PWR_SR_WUF3_Pos)                          /*!< 0x00000004 */
#define PWR_SR_WUF3                               PWR_SR_WUF3_Msk                                   
#define PWR_SR_WUF4_Pos                           (3U)
#define PWR_SR_WUF4_Msk                           (0x1UL<<PWR_SR_WUF4_Pos)                          /*!< 0x00000008 */
#define PWR_SR_WUF4                               PWR_SR_WUF4_Msk                                   
#define PWR_SR_WUF5_Pos                           (4U)
#define PWR_SR_WUF5_Msk                           (0x1UL<<PWR_SR_WUF5_Pos)                          /*!< 0x00000010 */
#define PWR_SR_WUF5                               PWR_SR_WUF5_Msk                                   
#define PWR_SR_WUF_Pos                            (0U)
#define PWR_SR_WUF_Msk                            (0x1FUL<<PWR_SR_WUF_Pos)                          /*!< 0x0000001F */
#define PWR_SR_WUF                                PWR_SR_WUF_Msk                                   
#define PWR_SR_SBF_Pos                            (8U)
#define PWR_SR_SBF_Msk                            (0x1UL<<PWR_SR_SBF_Pos)                           /*!< 0x00000100 */
#define PWR_SR_SBF                                PWR_SR_SBF_Msk                                    
#define PWR_SR_MR_RDY_Pos                         (9U)
#define PWR_SR_MR_RDY_Msk                         (0x1UL<<PWR_SR_MR_RDY_Pos)                        /*!< 0x00000200 */
#define PWR_SR_MR_RDY                             PWR_SR_MR_RDY_Msk                                 
#define PWR_SR_PVDO_Pos                           (16U)
#define PWR_SR_PVDO_Msk                           (0x1UL<<PWR_SR_PVDO_Pos)                          /*!< 0x00010000 */
#define PWR_SR_PVDO                               PWR_SR_PVDO_Msk                                   

/********************************* Bit definition for PWR_SCR register **********************************************/
#define PWR_SCR_CWUF1_Pos                         (0U)
#define PWR_SCR_CWUF1_Msk                         (0x1UL<<PWR_SCR_CWUF1_Pos)                        /*!< 0x00000001 */
#define PWR_SCR_CWUF1                             PWR_SCR_CWUF1_Msk                                 
#define PWR_SCR_CWUF2_Pos                         (1U)
#define PWR_SCR_CWUF2_Msk                         (0x1UL<<PWR_SCR_CWUF2_Pos)                        /*!< 0x00000002 */
#define PWR_SCR_CWUF2                             PWR_SCR_CWUF2_Msk                                 
#define PWR_SCR_CWUF3_Pos                         (2U)
#define PWR_SCR_CWUF3_Msk                         (0x1UL<<PWR_SCR_CWUF3_Pos)                        /*!< 0x00000004 */
#define PWR_SCR_CWUF3                             PWR_SCR_CWUF3_Msk                                 
#define PWR_SCR_CWUF4_Pos                         (3U)
#define PWR_SCR_CWUF4_Msk                         (0x1UL<<PWR_SCR_CWUF4_Pos)                        /*!< 0x00000008 */
#define PWR_SCR_CWUF4                             PWR_SCR_CWUF4_Msk                                 
#define PWR_SCR_CWUF5_Pos                         (4U)
#define PWR_SCR_CWUF5_Msk                         (0x1UL<<PWR_SCR_CWUF5_Pos)                        /*!< 0x00000010 */
#define PWR_SCR_CWUF5                             PWR_SCR_CWUF5_Msk                                 
#define PWR_SCR_CSBF_Pos                          (8U)
#define PWR_SCR_CSBF_Msk                          (0x1UL<<PWR_SCR_CSBF_Pos)                         /*!< 0x00000100 */
#define PWR_SCR_CSBF                              PWR_SCR_CSBF_Msk                                  

/********************************************************************************************************************/
/********************************* RCC ******************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for RCC_CR register ***********************************************/
#define RCC_CR_HSION_Pos                          (0U)
#define RCC_CR_HSION_Msk                          (0x1UL<<RCC_CR_HSION_Pos)                         /*!< 0x00000001 */
#define RCC_CR_HSION                              RCC_CR_HSION_Msk                                  
#define RCC_CR_HSIRDY_Pos                         (1U)
#define RCC_CR_HSIRDY_Msk                         (0x1UL<<RCC_CR_HSIRDY_Pos)                        /*!< 0x00000002 */
#define RCC_CR_HSIRDY                             RCC_CR_HSIRDY_Msk                                 
#define RCC_CR_HSIKERON_Pos                       (2U)
#define RCC_CR_HSIKERON_Msk                       (0x1UL<<RCC_CR_HSIKERON_Pos)                      /*!< 0x00000004 */
#define RCC_CR_HSIKERON                           RCC_CR_HSIKERON_Msk                               
#define RCC_CR_HSITRIM_Pos                        (4U)
#define RCC_CR_HSITRIM_Msk                        (0x7FFUL<<RCC_CR_HSITRIM_Pos)                     /*!< 0x00007FF0 */
#define RCC_CR_HSITRIM                            RCC_CR_HSITRIM_Msk
#define RCC_CR_HSEON_Pos                          (16U)
#define RCC_CR_HSEON_Msk                          (0x1UL<<RCC_CR_HSEON_Pos)                         /*!< 0x00010000 */
#define RCC_CR_HSEON                              RCC_CR_HSEON_Msk                                  
#define RCC_CR_HSERDY_Pos                         (17U)
#define RCC_CR_HSERDY_Msk                         (0x1UL<<RCC_CR_HSERDY_Pos)                        /*!< 0x00020000 */
#define RCC_CR_HSERDY                             RCC_CR_HSERDY_Msk                                 
#define RCC_CR_HSEBYP_Pos                         (18U)
#define RCC_CR_HSEBYP_Msk                         (0x1UL<<RCC_CR_HSEBYP_Pos)                        /*!< 0x00040000 */
#define RCC_CR_HSEBYP                             RCC_CR_HSEBYP_Msk                                 
#define RCC_CR_CSSON_Pos                          (19U)
#define RCC_CR_CSSON_Msk                          (0x1UL<<RCC_CR_CSSON_Pos)                         /*!< 0x00080000 */
#define RCC_CR_CSSON                              RCC_CR_CSSON_Msk                                  
#define RCC_CR_PLLON_Pos                          (24U)
#define RCC_CR_PLLON_Msk                          (0x1UL<<RCC_CR_PLLON_Pos)                         /*!< 0x01000000 */
#define RCC_CR_PLLON                              RCC_CR_PLLON_Msk                                  
#define RCC_CR_PLLRDY_Pos                         (25U)
#define RCC_CR_PLLRDY_Msk                         (0x1UL<<RCC_CR_PLLRDY_Pos)                        /*!< 0x02000000 */
#define RCC_CR_PLLRDY                             RCC_CR_PLLRDY_Msk                                 
#define RCC_CR_HSIFS_Pos                          (26U)
#define RCC_CR_HSIFS_Msk                          (0x3UL<<RCC_CR_HSIFS_Pos)                         /*!< 0x0C000000 */
#define RCC_CR_HSIFS                              RCC_CR_HSIFS_Msk
#define RCC_CR_HSIFS_0                            (0x1UL<<RCC_CR_HSIFS_Pos)                         /*!< 0x04000000 */
#define RCC_CR_HSIFS_1                            (0x2UL<<RCC_CR_HSIFS_Pos)                         /*!< 0x08000000 */

/********************************* Bit definition for RCC_CFGR register *********************************************/
#define RCC_CFGR_SW_Pos                           (0U)
#define RCC_CFGR_SW_Msk                           (0x3UL<<RCC_CFGR_SW_Pos)                          /*!< 0x00000003 */
#define RCC_CFGR_SW                               RCC_CFGR_SW_Msk
#define RCC_CFGR_SW_0                             (0x1UL<<RCC_CFGR_SW_Pos)                          /*!< 0x00000001 */
#define RCC_CFGR_SW_1                             (0x2UL<<RCC_CFGR_SW_Pos)                          /*!< 0x00000002 */
#define RCC_CFGR_SW_HSI                           (0x00000000U)                                      /*!< HSI selected as system clock */
#define RCC_CFGR_SW_HSE                           (0x00000001U)                                      /*!< HSE selected as system clock */
#define RCC_CFGR_SW_PLL                           (0x00000002U)

#define RCC_CFGR_SWS_Pos                          (2U)
#define RCC_CFGR_SWS_Msk                          (0x3UL<<RCC_CFGR_SWS_Pos)                         /*!< 0x0000000C */
#define RCC_CFGR_SWS                              RCC_CFGR_SWS_Msk
#define RCC_CFGR_SWS_0                            (0x1UL<<RCC_CFGR_SWS_Pos)                         /*!< 0x00000004 */
#define RCC_CFGR_SWS_1                            (0x2UL<<RCC_CFGR_SWS_Pos)                         /*!< 0x00000008 */
#define RCC_CFGR_SWS_HSI                          (0x00000000U)                                     /*!< HSI oscillator used as system clock */
#define RCC_CFGR_SWS_HSE                          (0x00000004U)                                     /*!< HSE oscillator used as system clock */
#define RCC_CFGR_SWS_PLL                          (0x00000008U)    

#define RCC_CFGR_HPRE_Pos                         (4U)
#define RCC_CFGR_HPRE_Msk                         (0xFUL<<RCC_CFGR_HPRE_Pos)                        /*!< 0x000000F0 */
#define RCC_CFGR_HPRE                             RCC_CFGR_HPRE_Msk
#define RCC_CFGR_HPRE_0                           (0x1UL<<RCC_CFGR_HPRE_Pos)                        /*!< 0x00000010 */
#define RCC_CFGR_HPRE_1                           (0x2UL<<RCC_CFGR_HPRE_Pos)                        /*!< 0x00000020 */
#define RCC_CFGR_HPRE_2                           (0x4UL<<RCC_CFGR_HPRE_Pos)                        /*!< 0x00000040 */
#define RCC_CFGR_HPRE_3                           (0x8UL<<RCC_CFGR_HPRE_Pos)                        /*!< 0x00000080 */#define RCC_CFGR_HPRE_DIV1                        (0x00000000U)                                     /*!< SYSCLK not divided */
#define RCC_CFGR_HPRE_DIV1                        (0x00000000U)                                     /*!< SYSCLK not divided */
#define RCC_CFGR_HPRE_DIV2                        (0x00000080U)                                     /*!< SYSCLK divided by 2 */
#define RCC_CFGR_HPRE_DIV4                        (0x00000090U)                                     /*!< SYSCLK divided by 4 */
#define RCC_CFGR_HPRE_DIV8                        (0x000000A0U)                                     /*!< SYSCLK divided by 8 */
#define RCC_CFGR_HPRE_DIV16                       (0x000000B0U)                                     /*!< SYSCLK divided by 16 */
#define RCC_CFGR_HPRE_DIV64                       (0x000000C0U)                                     /*!< SYSCLK divided by 64 */
#define RCC_CFGR_HPRE_DIV128                      (0x000000D0U)                                     /*!< SYSCLK divided by 128 */
#define RCC_CFGR_HPRE_DIV256                      (0x000000E0U)                                     /*!< SYSCLK divided by 256 */
#define RCC_CFGR_HPRE_DIV512                      (0x000000F0U) 

#define RCC_CFGR_PPRE1_Pos                        (8U)
#define RCC_CFGR_PPRE1_Msk                        (0x7UL<<RCC_CFGR_PPRE1_Pos)                       /*!< 0x00000700 */
#define RCC_CFGR_PPRE1                            RCC_CFGR_PPRE1_Msk
#define RCC_CFGR_PPRE1_0                          (0x1UL<<RCC_CFGR_PPRE1_Pos)                       /*!< 0x00000100 */
#define RCC_CFGR_PPRE1_1                          (0x2UL<<RCC_CFGR_PPRE1_Pos)                       /*!< 0x00000200 */
#define RCC_CFGR_PPRE1_2                          (0x4UL<<RCC_CFGR_PPRE1_Pos)                       /*!< 0x00000400 */
#define RCC_CFGR_PPRE1_DIV1                       (0x00000000U)                                     /*!< HCLK not divided */
#define RCC_CFGR_PPRE1_DIV2                       (0x00000400U)                                     /*!< HCLK divided by 2 */
#define RCC_CFGR_PPRE1_DIV4                       (0x00000500U)                                     /*!< HCLK divided by 4 */
#define RCC_CFGR_PPRE1_DIV8                       (0x00000600U)                                     /*!< HCLK divided by 8 */
#define RCC_CFGR_PPRE1_DIV16                      (0x00000700U)   

#define RCC_CFGR_PPRE2_Pos                        (11U)
#define RCC_CFGR_PPRE2_Msk                        (0x7UL<<RCC_CFGR_PPRE2_Pos)                       /*!< 0x00003800 */
#define RCC_CFGR_PPRE2                            RCC_CFGR_PPRE2_Msk
#define RCC_CFGR_PPRE2_0                          (0x1UL<<RCC_CFGR_PPRE2_Pos)                       /*!< 0x00000800 */
#define RCC_CFGR_PPRE2_1                          (0x2UL<<RCC_CFGR_PPRE2_Pos)                       /*!< 0x00001000 */
#define RCC_CFGR_PPRE2_2                          (0x4UL<<RCC_CFGR_PPRE2_Pos)                       /*!< 0x00002000 */
#define RCC_CFGR_PPRE2_DIV1                       (0x00000000U)                                     /*!< HCLK not divided */
#define RCC_CFGR_PPRE2_DIV2                       (0x00002000U)                                     /*!< HCLK divided by 2 */
#define RCC_CFGR_PPRE2_DIV4                       (0x00002800U)                                     /*!< HCLK divided by 4 */
#define RCC_CFGR_PPRE2_DIV8                       (0x00003000U)                                     /*!< HCLK divided by 8 */
#define RCC_CFGR_PPRE2_DIV16                      (0x00003800U)                                     /*!< HCLK divided by 16 */

#define RCC_CFGR_MCO_Pos                          (24U)
#define RCC_CFGR_MCO_Msk                          (0xFUL<<RCC_CFGR_MCO_Pos)                         /*!< 0x0F000000 */
#define RCC_CFGR_MCO                              RCC_CFGR_MCO_Msk
#define RCC_CFGR_MCO_0                            (0x1UL<<RCC_CFGR_MCO_Pos)                         /*!< 0x01000000 */
#define RCC_CFGR_MCO_1                            (0x2UL<<RCC_CFGR_MCO_Pos)                         /*!< 0x02000000 */
#define RCC_CFGR_MCO_2                            (0x4UL<<RCC_CFGR_MCO_Pos)                         /*!< 0x04000000 */
#define RCC_CFGR_MCO_3                            (0x8UL<<RCC_CFGR_MCO_Pos)                         /*!< 0x08000000 */

#define RCC_CFGR_MCO_NOCLOCK                      0x00000000U                                       /*!< No clock */
#define RCC_CFGR_MCO_LSE                          0x01000000U                                       /*!< LSE selected as MCO source */
#define RCC_CFGR_MCO_LSI                          0x02000000U                                       /*!< LSI selected as MCO source */
#define RCC_CFGR_MCO_SYSCLK                       0x04000000U                                       /*!< SYSTEM CLOCK selected as MCO source */
#define RCC_CFGR_MCO_HSI                          0x05000000U                                       /*!< HSI16M selected as MCO source*/
#define RCC_CFGR_MCO_HSE                          0x06000000U                                       /*!< HSE selected as MCO source*/
#define RCC_CFGR_MCO_PLL                          0x07000000U                                       /*!< PLL selected as MCO source */
#define RCC_CFGR_MCO_HCLK                         0x08000000U                                       /*!< HCLK selected as MCO source */
#define RCC_CFGR_MCO_PCLK1                        0x09000000U                                       /*!< APB1CLK selected as MCO source */
#define RCC_CFGR_MCO_PCLK2                        0x0A000000U                                       /*!< APB2CLK selected as MCO source */
#define RCC_CFGR_MCO_HSI10M                       0x0B000000U                                       /*!< HSI10M selected as MCO source */

/********************************* Bit definition for RCC_CIR register **********************************************/
#define RCC_CIR_LSIRDYF_Pos                       (0U)
#define RCC_CIR_LSIRDYF_Msk                       (0x1UL<<RCC_CIR_LSIRDYF_Pos)                      /*!< 0x00000001 */
#define RCC_CIR_LSIRDYF                           RCC_CIR_LSIRDYF_Msk                               
#define RCC_CIR_LSERDYF_Pos                       (1U)
#define RCC_CIR_LSERDYF_Msk                       (0x1UL<<RCC_CIR_LSERDYF_Pos)                      /*!< 0x00000002 */
#define RCC_CIR_LSERDYF                           RCC_CIR_LSERDYF_Msk                               
#define RCC_CIR_HSIRDYF_Pos                       (2U)
#define RCC_CIR_HSIRDYF_Msk                       (0x1UL<<RCC_CIR_HSIRDYF_Pos)                      /*!< 0x00000004 */
#define RCC_CIR_HSIRDYF                           RCC_CIR_HSIRDYF_Msk                               
#define RCC_CIR_HSERDYF_Pos                       (3U)
#define RCC_CIR_HSERDYF_Msk                       (0x1UL<<RCC_CIR_HSERDYF_Pos)                      /*!< 0x00000008 */
#define RCC_CIR_HSERDYF                           RCC_CIR_HSERDYF_Msk                               
#define RCC_CIR_PLLRDYF_Pos                       (4U)
#define RCC_CIR_PLLRDYF_Msk                       (0x1UL<<RCC_CIR_PLLRDYF_Pos)                      /*!< 0x00000010 */
#define RCC_CIR_PLLRDYF                           RCC_CIR_PLLRDYF_Msk                               
#define RCC_CIR_CSSF_Pos                          (7U)
#define RCC_CIR_CSSF_Msk                          (0x1UL<<RCC_CIR_CSSF_Pos)                         /*!< 0x00000080 */
#define RCC_CIR_CSSF                              RCC_CIR_CSSF_Msk                                  
#define RCC_CIR_LSIRDYIE_Pos                      (8U)
#define RCC_CIR_LSIRDYIE_Msk                      (0x1UL<<RCC_CIR_LSIRDYIE_Pos)                     /*!< 0x00000100 */
#define RCC_CIR_LSIRDYIE                          RCC_CIR_LSIRDYIE_Msk                              
#define RCC_CIR_LSERDYIE_Pos                      (9U)
#define RCC_CIR_LSERDYIE_Msk                      (0x1UL<<RCC_CIR_LSERDYIE_Pos)                     /*!< 0x00000200 */
#define RCC_CIR_LSERDYIE                          RCC_CIR_LSERDYIE_Msk                              
#define RCC_CIR_HSIRDYIE_Pos                      (10U)
#define RCC_CIR_HSIRDYIE_Msk                      (0x1UL<<RCC_CIR_HSIRDYIE_Pos)                     /*!< 0x00000400 */
#define RCC_CIR_HSIRDYIE                          RCC_CIR_HSIRDYIE_Msk                              
#define RCC_CIR_HSERDYIE_Pos                      (11U)
#define RCC_CIR_HSERDYIE_Msk                      (0x1UL<<RCC_CIR_HSERDYIE_Pos)                     /*!< 0x00000800 */
#define RCC_CIR_HSERDYIE                          RCC_CIR_HSERDYIE_Msk                              
#define RCC_CIR_PLLRDYIE_Pos                      (12U)
#define RCC_CIR_PLLRDYIE_Msk                      (0x1UL<<RCC_CIR_PLLRDYIE_Pos)                     /*!< 0x00001000 */
#define RCC_CIR_PLLRDYIE                          RCC_CIR_PLLRDYIE_Msk                              
#define RCC_CIR_LSIRDYC_Pos                       (16U)
#define RCC_CIR_LSIRDYC_Msk                       (0x1UL<<RCC_CIR_LSIRDYC_Pos)                      /*!< 0x00010000 */
#define RCC_CIR_LSIRDYC                           RCC_CIR_LSIRDYC_Msk                               
#define RCC_CIR_LSERDYC_Pos                       (17U)
#define RCC_CIR_LSERDYC_Msk                       (0x1UL<<RCC_CIR_LSERDYC_Pos)                      /*!< 0x00020000 */
#define RCC_CIR_LSERDYC                           RCC_CIR_LSERDYC_Msk                               
#define RCC_CIR_HSIRDYC_Pos                       (18U)
#define RCC_CIR_HSIRDYC_Msk                       (0x1UL<<RCC_CIR_HSIRDYC_Pos)                      /*!< 0x00040000 */
#define RCC_CIR_HSIRDYC                           RCC_CIR_HSIRDYC_Msk                               
#define RCC_CIR_HSERDYC_Pos                       (19U)
#define RCC_CIR_HSERDYC_Msk                       (0x1UL<<RCC_CIR_HSERDYC_Pos)                      /*!< 0x00080000 */
#define RCC_CIR_HSERDYC                           RCC_CIR_HSERDYC_Msk                               
#define RCC_CIR_PLLRDYC_Pos                       (20U)
#define RCC_CIR_PLLRDYC_Msk                       (0x1UL<<RCC_CIR_PLLRDYC_Pos)                      /*!< 0x00100000 */
#define RCC_CIR_PLLRDYC                           RCC_CIR_PLLRDYC_Msk                               
#define RCC_CIR_CSSC_Pos                          (23U)
#define RCC_CIR_CSSC_Msk                          (0x1UL<<RCC_CIR_CSSC_Pos)                         /*!< 0x00800000 */
#define RCC_CIR_CSSC                              RCC_CIR_CSSC_Msk                                  

/********************************* Bit definition for RCC_AHBRSTR register ******************************************/
#define RCC_AHBRSTR_DMA1RST_Pos                   (0U)
#define RCC_AHBRSTR_DMA1RST_Msk                   (0x1UL<<RCC_AHBRSTR_DMA1RST_Pos)                  /*!< 0x00000001 */
#define RCC_AHBRSTR_DMA1RST                       RCC_AHBRSTR_DMA1RST_Msk                           
#define RCC_AHBRSTR_CRCRST_Pos                    (6U)
#define RCC_AHBRSTR_CRCRST_Msk                    (0x1UL<<RCC_AHBRSTR_CRCRST_Pos)                   /*!< 0x00000040 */
#define RCC_AHBRSTR_CRCRST                        RCC_AHBRSTR_CRCRST_Msk                            
#define RCC_AHBRSTR_IOPARST_Pos                   (8U)
#define RCC_AHBRSTR_IOPARST_Msk                   (0x1UL<<RCC_AHBRSTR_IOPARST_Pos)                  /*!< 0x00000100 */
#define RCC_AHBRSTR_IOPARST                       RCC_AHBRSTR_IOPARST_Msk                           
#define RCC_AHBRSTR_IOPBRST_Pos                   (9U)
#define RCC_AHBRSTR_IOPBRST_Msk                   (0x1UL<<RCC_AHBRSTR_IOPBRST_Pos)                  /*!< 0x00000200 */
#define RCC_AHBRSTR_IOPBRST                       RCC_AHBRSTR_IOPBRST_Msk                           
#define RCC_AHBRSTR_IOPCRST_Pos                   (10U)
#define RCC_AHBRSTR_IOPCRST_Msk                   (0x1UL<<RCC_AHBRSTR_IOPCRST_Pos)                  /*!< 0x00000400 */
#define RCC_AHBRSTR_IOPCRST                       RCC_AHBRSTR_IOPCRST_Msk                           
#define RCC_AHBRSTR_IOPDRST_Pos                   (11U)
#define RCC_AHBRSTR_IOPDRST_Msk                   (0x1UL<<RCC_AHBRSTR_IOPDRST_Pos)                  /*!< 0x00000800 */
#define RCC_AHBRSTR_IOPDRST                       RCC_AHBRSTR_IOPDRST_Msk                           

/********************************* Bit definition for RCC_APB1RSTR1 register ****************************************/
#define RCC_APB1RSTR1_TIM2RST_Pos                 (0U)
#define RCC_APB1RSTR1_TIM2RST_Msk                 (0x1UL<<RCC_APB1RSTR1_TIM2RST_Pos)                /*!< 0x00000001 */
#define RCC_APB1RSTR1_TIM2RST                     RCC_APB1RSTR1_TIM2RST_Msk                         
#define RCC_APB1RSTR1_TIM3RST_Pos                 (1U)
#define RCC_APB1RSTR1_TIM3RST_Msk                 (0x1UL<<RCC_APB1RSTR1_TIM3RST_Pos)                /*!< 0x00000002 */
#define RCC_APB1RSTR1_TIM3RST                     RCC_APB1RSTR1_TIM3RST_Msk                         
#define RCC_APB1RSTR1_TIM4RST_Pos                 (2U)
#define RCC_APB1RSTR1_TIM4RST_Msk                 (0x1UL<<RCC_APB1RSTR1_TIM4RST_Pos)                /*!< 0x00000004 */
#define RCC_APB1RSTR1_TIM4RST                     RCC_APB1RSTR1_TIM4RST_Msk                         
#define RCC_APB1RSTR1_TIM6RST_Pos                 (4U)
#define RCC_APB1RSTR1_TIM6RST_Msk                 (0x1UL<<RCC_APB1RSTR1_TIM6RST_Pos)                /*!< 0x00000010 */
#define RCC_APB1RSTR1_TIM6RST                     RCC_APB1RSTR1_TIM6RST_Msk                         
#define RCC_APB1RSTR1_TIM7RST_Pos                 (5U)
#define RCC_APB1RSTR1_TIM7RST_Msk                 (0x1UL<<RCC_APB1RSTR1_TIM7RST_Pos)                /*!< 0x00000020 */
#define RCC_APB1RSTR1_TIM7RST                     RCC_APB1RSTR1_TIM7RST_Msk                         
#define RCC_APB1RSTR1_WWDGRST_Pos                 (11U)
#define RCC_APB1RSTR1_WWDGRST_Msk                 (0x1UL<<RCC_APB1RSTR1_WWDGRST_Pos)                /*!< 0x00000800 */
#define RCC_APB1RSTR1_WWDGRST                     RCC_APB1RSTR1_WWDGRST_Msk                         
#define RCC_APB1RSTR1_PWM1RST_Pos                 (12U)
#define RCC_APB1RSTR1_PWM1RST_Msk                 (0x1UL<<RCC_APB1RSTR1_PWM1RST_Pos)                /*!< 0x00001000 */
#define RCC_APB1RSTR1_PWM1RST                     RCC_APB1RSTR1_PWM1RST_Msk                         
#define RCC_APB1RSTR1_PWM2RST_Pos                 (13U)
#define RCC_APB1RSTR1_PWM2RST_Msk                 (0x1UL<<RCC_APB1RSTR1_PWM2RST_Pos)                /*!< 0x00002000 */
#define RCC_APB1RSTR1_PWM2RST                     RCC_APB1RSTR1_PWM2RST_Msk                         
#define RCC_APB1RSTR1_SPI2RST_Pos                 (14U)
#define RCC_APB1RSTR1_SPI2RST_Msk                 (0x1UL<<RCC_APB1RSTR1_SPI2RST_Pos)                /*!< 0x00004000 */
#define RCC_APB1RSTR1_SPI2RST                     RCC_APB1RSTR1_SPI2RST_Msk                         
#define RCC_APB1RSTR1_UART1RST_Pos                (19U)
#define RCC_APB1RSTR1_UART1RST_Msk                (0x1UL<<RCC_APB1RSTR1_UART1RST_Pos)               /*!< 0x00080000 */
#define RCC_APB1RSTR1_UART1RST                    RCC_APB1RSTR1_UART1RST_Msk                        
#define RCC_APB1RSTR1_UART2RST_Pos                (20U)
#define RCC_APB1RSTR1_UART2RST_Msk                (0x1UL<<RCC_APB1RSTR1_UART2RST_Pos)               /*!< 0x00100000 */
#define RCC_APB1RSTR1_UART2RST                    RCC_APB1RSTR1_UART2RST_Msk                        
#define RCC_APB1RSTR1_I2C1RST_Pos                 (21U)
#define RCC_APB1RSTR1_I2C1RST_Msk                 (0x1UL<<RCC_APB1RSTR1_I2C1RST_Pos)                /*!< 0x00200000 */
#define RCC_APB1RSTR1_I2C1RST                     RCC_APB1RSTR1_I2C1RST_Msk                         
#define RCC_APB1RSTR1_I2C2RST_Pos                 (22U)
#define RCC_APB1RSTR1_I2C2RST_Msk                 (0x1UL<<RCC_APB1RSTR1_I2C2RST_Pos)                /*!< 0x00400000 */
#define RCC_APB1RSTR1_I2C2RST                     RCC_APB1RSTR1_I2C2RST_Msk                         
#define RCC_APB1RSTR1_PWRRST_Pos                  (28U)
#define RCC_APB1RSTR1_PWRRST_Msk                  (0x1UL<<RCC_APB1RSTR1_PWRRST_Pos)                 /*!< 0x10000000 */
#define RCC_APB1RSTR1_PWRRST                      RCC_APB1RSTR1_PWRRST_Msk                          

/********************************* Bit definition for RCC_APB1RSTR2 register ****************************************/
#define RCC_APB1RSTR2_LPTIM1RST_Pos               (0U)
#define RCC_APB1RSTR2_LPTIM1RST_Msk               (0x1UL<<RCC_APB1RSTR2_LPTIM1RST_Pos)              /*!< 0x00000001 */
#define RCC_APB1RSTR2_LPTIM1RST                   RCC_APB1RSTR2_LPTIM1RST_Msk                       
#define RCC_APB1RSTR2_LPUART1RST_Pos              (1U)
#define RCC_APB1RSTR2_LPUART1RST_Msk              (0x1UL<<RCC_APB1RSTR2_LPUART1RST_Pos)             /*!< 0x00000002 */
#define RCC_APB1RSTR2_LPUART1RST                  RCC_APB1RSTR2_LPUART1RST_Msk                      

/********************************* Bit definition for RCC_APB2RSTR register *****************************************/
#define RCC_APB2RSTR_SYSCFGRST_Pos                (0U)
#define RCC_APB2RSTR_SYSCFGRST_Msk                (0x1UL<<RCC_APB2RSTR_SYSCFGRST_Pos)               /*!< 0x00000001 */
#define RCC_APB2RSTR_SYSCFGRST                    RCC_APB2RSTR_SYSCFGRST_Msk                        
#define RCC_APB2RSTR_ADC1RST_Pos                  (9U)
#define RCC_APB2RSTR_ADC1RST_Msk                  (0x1UL<<RCC_APB2RSTR_ADC1RST_Pos)                 /*!< 0x00000200 */
#define RCC_APB2RSTR_ADC1RST                      RCC_APB2RSTR_ADC1RST_Msk                          
#define RCC_APB2RSTR_TIM1RST_Pos                  (11U)
#define RCC_APB2RSTR_TIM1RST_Msk                  (0x1UL<<RCC_APB2RSTR_TIM1RST_Pos)                 /*!< 0x00000800 */
#define RCC_APB2RSTR_TIM1RST                      RCC_APB2RSTR_TIM1RST_Msk                          
#define RCC_APB2RSTR_SPI1RST_Pos                  (12U)
#define RCC_APB2RSTR_SPI1RST_Msk                  (0x1UL<<RCC_APB2RSTR_SPI1RST_Pos)                 /*!< 0x00001000 */
#define RCC_APB2RSTR_SPI1RST                      RCC_APB2RSTR_SPI1RST_Msk                          
#define RCC_APB2RSTR_USART1RST_Pos                (14U)
#define RCC_APB2RSTR_USART1RST_Msk                (0x1UL<<RCC_APB2RSTR_USART1RST_Pos)               /*!< 0x00004000 */
#define RCC_APB2RSTR_USART1RST                    RCC_APB2RSTR_USART1RST_Msk                        
#define RCC_APB2RSTR_PWM3RST_Pos                  (16U)
#define RCC_APB2RSTR_PWM3RST_Msk                  (0x1UL<<RCC_APB2RSTR_PWM3RST_Pos)                 /*!< 0x00010000 */
#define RCC_APB2RSTR_PWM3RST                      RCC_APB2RSTR_PWM3RST_Msk                          
#define RCC_APB2RSTR_PWM4RST_Pos                  (17U)
#define RCC_APB2RSTR_PWM4RST_Msk                  (0x1UL<<RCC_APB2RSTR_PWM4RST_Pos)                 /*!< 0x00020000 */
#define RCC_APB2RSTR_PWM4RST                      RCC_APB2RSTR_PWM4RST_Msk                          
#define RCC_APB2RSTR_TIM15RST_Pos                 (22U)
#define RCC_APB2RSTR_TIM15RST_Msk                 (0x1UL<<RCC_APB2RSTR_TIM15RST_Pos)                /*!< 0x00400000 */
#define RCC_APB2RSTR_TIM15RST                     RCC_APB2RSTR_TIM15RST_Msk                         
#define RCC_APB2RSTR_TIM16RST_Pos                 (23U)
#define RCC_APB2RSTR_TIM16RST_Msk                 (0x1UL<<RCC_APB2RSTR_TIM16RST_Pos)                /*!< 0x00800000 */
#define RCC_APB2RSTR_TIM16RST                     RCC_APB2RSTR_TIM16RST_Msk                         
#define RCC_APB2RSTR_TIM17RST_Pos                 (24U)
#define RCC_APB2RSTR_TIM17RST_Msk                 (0x1UL<<RCC_APB2RSTR_TIM17RST_Pos)                /*!< 0x01000000 */
#define RCC_APB2RSTR_TIM17RST                     RCC_APB2RSTR_TIM17RST_Msk                         
#define RCC_APB2RSTR_COMPRST_Pos                  (27U)
#define RCC_APB2RSTR_COMPRST_Msk                  (0x1UL<<RCC_APB2RSTR_COMPRST_Pos)                 /*!< 0x08000000 */
#define RCC_APB2RSTR_COMPRST                      RCC_APB2RSTR_COMPRST_Msk                          
#define RCC_APB2RSTR_OPARST_Pos                   (28U)
#define RCC_APB2RSTR_OPARST_Msk                   (0x1UL<<RCC_APB2RSTR_OPARST_Pos)                 /*!< 0x10000000 */
#define RCC_APB2RSTR_OPARST                       RCC_APB2RSTR_OPARST_Msk                         

/********************************* Bit definition for RCC_AHBENR register *******************************************/
#define RCC_AHBENR_DMA1EN_Pos                     (0U)
#define RCC_AHBENR_DMA1EN_Msk                     (0x1UL<<RCC_AHBENR_DMA1EN_Pos)                    /*!< 0x00000001 */
#define RCC_AHBENR_DMA1EN                         RCC_AHBENR_DMA1EN_Msk                             
#define RCC_AHBENR_SRAMEN_Pos                     (2U)
#define RCC_AHBENR_SRAMEN_Msk                     (0x1UL<<RCC_AHBENR_SRAMEN_Pos)                    /*!< 0x00000004 */
#define RCC_AHBENR_SRAMEN                         RCC_AHBENR_SRAMEN_Msk                             
#define RCC_AHBENR_FMCEN_Pos                      (4U)
#define RCC_AHBENR_FMCEN_Msk                      (0x1UL<<RCC_AHBENR_FMCEN_Pos)                     /*!< 0x00000010 */
#define RCC_AHBENR_FMCEN                          RCC_AHBENR_FMCEN_Msk                              
#define RCC_AHBENR_CRCEN_Pos                      (6U)
#define RCC_AHBENR_CRCEN_Msk                      (0x1UL<<RCC_AHBENR_CRCEN_Pos)                     /*!< 0x00000040 */
#define RCC_AHBENR_CRCEN                          RCC_AHBENR_CRCEN_Msk                              
#define RCC_AHBENR_IOPAEN_Pos                     (8U)
#define RCC_AHBENR_IOPAEN_Msk                     (0x1UL<<RCC_AHBENR_IOPAEN_Pos)                    /*!< 0x00000100 */
#define RCC_AHBENR_IOPAEN                         RCC_AHBENR_IOPAEN_Msk                             
#define RCC_AHBENR_IOPBEN_Pos                     (9U)
#define RCC_AHBENR_IOPBEN_Msk                     (0x1UL<<RCC_AHBENR_IOPBEN_Pos)                    /*!< 0x00000200 */
#define RCC_AHBENR_IOPBEN                         RCC_AHBENR_IOPBEN_Msk                             
#define RCC_AHBENR_IOPCEN_Pos                     (10U)
#define RCC_AHBENR_IOPCEN_Msk                     (0x1UL<<RCC_AHBENR_IOPCEN_Pos)                    /*!< 0x00000400 */
#define RCC_AHBENR_IOPCEN                         RCC_AHBENR_IOPCEN_Msk                             
#define RCC_AHBENR_IOPDEN_Pos                     (11U)
#define RCC_AHBENR_IOPDEN_Msk                     (0x1UL<<RCC_AHBENR_IOPDEN_Pos)                    /*!< 0x00000800 */
#define RCC_AHBENR_IOPDEN                         RCC_AHBENR_IOPDEN_Msk                             

/********************************* Bit definition for RCC_APB1ENR1 register *****************************************/
#define RCC_APB1ENR1_TIM2EN_Pos                   (0U)
#define RCC_APB1ENR1_TIM2EN_Msk                   (0x1UL<<RCC_APB1ENR1_TIM2EN_Pos)                  /*!< 0x00000001 */
#define RCC_APB1ENR1_TIM2EN                       RCC_APB1ENR1_TIM2EN_Msk                           
#define RCC_APB1ENR1_TIM3EN_Pos                   (1U)
#define RCC_APB1ENR1_TIM3EN_Msk                   (0x1UL<<RCC_APB1ENR1_TIM3EN_Pos)                  /*!< 0x00000002 */
#define RCC_APB1ENR1_TIM3EN                       RCC_APB1ENR1_TIM3EN_Msk                           
#define RCC_APB1ENR1_TIM4EN_Pos                   (2U)
#define RCC_APB1ENR1_TIM4EN_Msk                   (0x1UL<<RCC_APB1ENR1_TIM4EN_Pos)                  /*!< 0x00000004 */
#define RCC_APB1ENR1_TIM4EN                       RCC_APB1ENR1_TIM4EN_Msk                           
#define RCC_APB1ENR1_TIM6EN_Pos                   (4U)
#define RCC_APB1ENR1_TIM6EN_Msk                   (0x1UL<<RCC_APB1ENR1_TIM6EN_Pos)                  /*!< 0x00000010 */
#define RCC_APB1ENR1_TIM6EN                       RCC_APB1ENR1_TIM6EN_Msk                           
#define RCC_APB1ENR1_TIM7EN_Pos                   (5U)
#define RCC_APB1ENR1_TIM7EN_Msk                   (0x1UL<<RCC_APB1ENR1_TIM7EN_Pos)                  /*!< 0x00000020 */
#define RCC_APB1ENR1_TIM7EN                       RCC_APB1ENR1_TIM7EN_Msk                           
#define RCC_APB1ENR1_WWDGEN_Pos                   (11U)
#define RCC_APB1ENR1_WWDGEN_Msk                   (0x1UL<<RCC_APB1ENR1_WWDGEN_Pos)                  /*!< 0x00000800 */
#define RCC_APB1ENR1_WWDGEN                       RCC_APB1ENR1_WWDGEN_Msk                           
#define RCC_APB1ENR1_PWM1EN_Pos                   (12U)
#define RCC_APB1ENR1_PWM1EN_Msk                   (0x1UL<<RCC_APB1ENR1_PWM1EN_Pos)                  /*!< 0x00001000 */
#define RCC_APB1ENR1_PWM1EN                       RCC_APB1ENR1_PWM1EN_Msk                           
#define RCC_APB1ENR1_PWM2EN_Pos                   (13U)
#define RCC_APB1ENR1_PWM2EN_Msk                   (0x1UL<<RCC_APB1ENR1_PWM2EN_Pos)                  /*!< 0x00002000 */
#define RCC_APB1ENR1_PWM2EN                       RCC_APB1ENR1_PWM2EN_Msk                           
#define RCC_APB1ENR1_SPI2EN_Pos                   (14U)
#define RCC_APB1ENR1_SPI2EN_Msk                   (0x1UL<<RCC_APB1ENR1_SPI2EN_Pos)                  /*!< 0x00004000 */
#define RCC_APB1ENR1_SPI2EN                       RCC_APB1ENR1_SPI2EN_Msk                           
#define RCC_APB1ENR1_UART1EN_Pos                  (19U)
#define RCC_APB1ENR1_UART1EN_Msk                  (0x1UL<<RCC_APB1ENR1_UART1EN_Pos)                 /*!< 0x00080000 */
#define RCC_APB1ENR1_UART1EN                      RCC_APB1ENR1_UART1EN_Msk                          
#define RCC_APB1ENR1_UART2EN_Pos                  (20U)
#define RCC_APB1ENR1_UART2EN_Msk                  (0x1UL<<RCC_APB1ENR1_UART2EN_Pos)                 /*!< 0x00100000 */
#define RCC_APB1ENR1_UART2EN                      RCC_APB1ENR1_UART2EN_Msk                          
#define RCC_APB1ENR1_I2C1EN_Pos                   (21U)
#define RCC_APB1ENR1_I2C1EN_Msk                   (0x1UL<<RCC_APB1ENR1_I2C1EN_Pos)                  /*!< 0x00200000 */
#define RCC_APB1ENR1_I2C1EN                       RCC_APB1ENR1_I2C1EN_Msk                           
#define RCC_APB1ENR1_I2C2EN_Pos                   (22U)
#define RCC_APB1ENR1_I2C2EN_Msk                   (0x1UL<<RCC_APB1ENR1_I2C2EN_Pos)                  /*!< 0x00400000 */
#define RCC_APB1ENR1_I2C2EN                       RCC_APB1ENR1_I2C2EN_Msk                           
#define RCC_APB1ENR1_PWREN_Pos                    (28U)
#define RCC_APB1ENR1_PWREN_Msk                    (0x1UL<<RCC_APB1ENR1_PWREN_Pos)                   /*!< 0x10000000 */
#define RCC_APB1ENR1_PWREN                        RCC_APB1ENR1_PWREN_Msk                            

/********************************* Bit definition for RCC_APB1ENR2 register *****************************************/
#define RCC_APB1ENR2_LPTIM1EN_Pos                 (0U)
#define RCC_APB1ENR2_LPTIM1EN_Msk                 (0x1UL<<RCC_APB1ENR2_LPTIM1EN_Pos)                /*!< 0x00000001 */
#define RCC_APB1ENR2_LPTIM1EN                     RCC_APB1ENR2_LPTIM1EN_Msk                         
#define RCC_APB1ENR2_LPUART1EN_Pos                (1U)
#define RCC_APB1ENR2_LPUART1EN_Msk                (0x1UL<<RCC_APB1ENR2_LPUART1EN_Pos)               /*!< 0x00000002 */
#define RCC_APB1ENR2_LPUART1EN                    RCC_APB1ENR2_LPUART1EN_Msk                        

/********************************* Bit definition for RCC_APB2ENR register ******************************************/
#define RCC_APB2ENR_SYSCFGEN_Pos                  (0U)
#define RCC_APB2ENR_SYSCFGEN_Msk                  (0x1UL<<RCC_APB2ENR_SYSCFGEN_Pos)                 /*!< 0x00000001 */
#define RCC_APB2ENR_SYSCFGEN                      RCC_APB2ENR_SYSCFGEN_Msk                          
#define RCC_APB2ENR_ADC1EN_Pos                    (9U)
#define RCC_APB2ENR_ADC1EN_Msk                    (0x1UL<<RCC_APB2ENR_ADC1EN_Pos)                   /*!< 0x00000200 */
#define RCC_APB2ENR_ADC1EN                        RCC_APB2ENR_ADC1EN_Msk                            
#define RCC_APB2ENR_TIM1EN_Pos                    (11U)
#define RCC_APB2ENR_TIM1EN_Msk                    (0x1UL<<RCC_APB2ENR_TIM1EN_Pos)                   /*!< 0x00000800 */
#define RCC_APB2ENR_TIM1EN                        RCC_APB2ENR_TIM1EN_Msk                            
#define RCC_APB2ENR_SPI1EN_Pos                    (12U)
#define RCC_APB2ENR_SPI1EN_Msk                    (0x1UL<<RCC_APB2ENR_SPI1EN_Pos)                   /*!< 0x00001000 */
#define RCC_APB2ENR_SPI1EN                        RCC_APB2ENR_SPI1EN_Msk                            
#define RCC_APB2ENR_USART1EN_Pos                  (14U)
#define RCC_APB2ENR_USART1EN_Msk                  (0x1UL<<RCC_APB2ENR_USART1EN_Pos)                 /*!< 0x00004000 */
#define RCC_APB2ENR_USART1EN                      RCC_APB2ENR_USART1EN_Msk                          
#define RCC_APB2ENR_PWM3EN_Pos                    (16U)
#define RCC_APB2ENR_PWM3EN_Msk                    (0x1UL<<RCC_APB2ENR_PWM3EN_Pos)                   /*!< 0x00010000 */
#define RCC_APB2ENR_PWM3EN                        RCC_APB2ENR_PWM3EN_Msk                            
#define RCC_APB2ENR_PWM4EN_Pos                    (17U)
#define RCC_APB2ENR_PWM4EN_Msk                    (0x1UL<<RCC_APB2ENR_PWM4EN_Pos)                   /*!< 0x00020000 */
#define RCC_APB2ENR_PWM4EN                        RCC_APB2ENR_PWM4EN_Msk                            
#define RCC_APB2ENR_TIM15EN_Pos                   (22U)
#define RCC_APB2ENR_TIM15EN_Msk                   (0x1UL<<RCC_APB2ENR_TIM15EN_Pos)                  /*!< 0x00400000 */
#define RCC_APB2ENR_TIM15EN                       RCC_APB2ENR_TIM15EN_Msk                           
#define RCC_APB2ENR_TIM16EN_Pos                   (23U)
#define RCC_APB2ENR_TIM16EN_Msk                   (0x1UL<<RCC_APB2ENR_TIM16EN_Pos)                  /*!< 0x00800000 */
#define RCC_APB2ENR_TIM16EN                       RCC_APB2ENR_TIM16EN_Msk                           
#define RCC_APB2ENR_TIM17EN_Pos                   (24U)
#define RCC_APB2ENR_TIM17EN_Msk                   (0x1UL<<RCC_APB2ENR_TIM17EN_Pos)                  /*!< 0x01000000 */
#define RCC_APB2ENR_TIM17EN                       RCC_APB2ENR_TIM17EN_Msk                           
#define RCC_APB2ENR_COMPEN_Pos                    (27U)
#define RCC_APB2ENR_COMPEN_Msk                    (0x1UL<<RCC_APB2ENR_COMPEN_Pos)                   /*!< 0x08000000 */
#define RCC_APB2ENR_COMPEN                        RCC_APB2ENR_COMPEN_Msk                            
#define RCC_APB2ENR_OPAEN_Pos                     (28U)
#define RCC_APB2ENR_OPAEN_Msk                     (0x1UL<<RCC_APB2ENR_OPAEN_Pos)                    /*!< 0x10000000 */
#define RCC_APB2ENR_OPAEN                         RCC_APB2ENR_OPAEN_Msk                           

/********************************* Bit definition for RCC_CCIPR register ********************************************/
#define RCC_CCIPR_USART1SEL_Pos                   (0U)
#define RCC_CCIPR_USART1SEL_Msk                   (0x3UL<<RCC_CCIPR_USART1SEL_Pos)                  /*!< 0x00000003 */
#define RCC_CCIPR_USART1SEL                       RCC_CCIPR_USART1SEL_Msk
#define RCC_CCIPR_USART1SEL_0                     (0x1UL<<RCC_CCIPR_USART1SEL_Pos)                  /*!< 0x00000001 */
#define RCC_CCIPR_USART1SEL_1                     (0x2UL<<RCC_CCIPR_USART1SEL_Pos)                  /*!< 0x00000002 */
#define RCC_CCIPR_LPUART1SEL_Pos                  (12U)
#define RCC_CCIPR_LPUART1SEL_Msk                  (0x3UL<<RCC_CCIPR_LPUART1SEL_Pos)                 /*!< 0x00003000 */
#define RCC_CCIPR_LPUART1SEL                      RCC_CCIPR_LPUART1SEL_Msk
#define RCC_CCIPR_LPUART1SEL_0                    (0x1UL<<RCC_CCIPR_LPUART1SEL_Pos)                 /*!< 0x00001000 */
#define RCC_CCIPR_LPUART1SEL_1                    (0x2UL<<RCC_CCIPR_LPUART1SEL_Pos)                 /*!< 0x00002000 */
#define RCC_CCIPR_LPTIM1SEL_Pos                   (14U)
#define RCC_CCIPR_LPTIM1SEL_Msk                   (0x3UL<<RCC_CCIPR_LPTIM1SEL_Pos)                  /*!< 0x0000C000 */
#define RCC_CCIPR_LPTIM1SEL                       RCC_CCIPR_LPTIM1SEL_Msk
#define RCC_CCIPR_LPTIM1SEL_0                     (0x1UL<<RCC_CCIPR_LPTIM1SEL_Pos)                  /*!< 0x00004000 */
#define RCC_CCIPR_LPTIM1SEL_1                     (0x2UL<<RCC_CCIPR_LPTIM1SEL_Pos)                  /*!< 0x00008000 */
#define RCC_CCIPR_COMP1SEL_Pos                    (16U)
#define RCC_CCIPR_COMP1SEL_Msk                    (0x3UL<<RCC_CCIPR_COMP1SEL_Pos)                   /*!< 0x00030000 */
#define RCC_CCIPR_COMP1SEL                        RCC_CCIPR_COMP1SEL_Msk
#define RCC_CCIPR_COMP1SEL_0                      (0x1UL<<RCC_CCIPR_COMP1SEL_Pos)                   /*!< 0x00010000 */
#define RCC_CCIPR_COMP1SEL_1                      (0x2UL<<RCC_CCIPR_COMP1SEL_Pos)                   /*!< 0x00020000 */
#define RCC_CCIPR_COMP2SEL_Pos                    (18U)
#define RCC_CCIPR_COMP2SEL_Msk                    (0x3UL<<RCC_CCIPR_COMP2SEL_Pos)                   /*!< 0x000C0000 */
#define RCC_CCIPR_COMP2SEL                        RCC_CCIPR_COMP2SEL_Msk
#define RCC_CCIPR_COMP2SEL_0                      (0x1UL<<RCC_CCIPR_COMP2SEL_Pos)                   /*!< 0x00040000 */
#define RCC_CCIPR_COMP2SEL_1                      (0x2UL<<RCC_CCIPR_COMP2SEL_Pos)                   /*!< 0x00080000 */
#define RCC_CCIPR_ADC1SEL_Pos                     (24U)
#define RCC_CCIPR_ADC1SEL_Msk                     (0x3UL<<RCC_CCIPR_ADC1SEL_Pos)                    /*!< 0x03000000 */
#define RCC_CCIPR_ADC1SEL                         RCC_CCIPR_ADC1SEL_Msk
#define RCC_CCIPR_ADC1SEL_0                       (0x1UL<<RCC_CCIPR_ADC1SEL_Pos)                    /*!< 0x01000000 */
#define RCC_CCIPR_ADC1SEL_1                       (0x2UL<<RCC_CCIPR_ADC1SEL_Pos)                    /*!< 0x02000000 */
#define RCC_CCIPR_OPA2SEL_Pos                     (30U)
#define RCC_CCIPR_OPA2SEL_Msk                     (0x3UL<<RCC_CCIPR_OPA2SEL_Pos)                    /*!< 0xC0000000 */
#define RCC_CCIPR_OPA2SEL                         RCC_CCIPR_OPA2SEL_Msk
#define RCC_CCIPR_OPA2SEL_0                       (0x1UL<<RCC_CCIPR_OPA2SEL_Pos)                    /*!< 0x40000000 */
#define RCC_CCIPR_OPA2SEL_1                       (0x2UL<<RCC_CCIPR_OPA2SEL_Pos)                    /*!< 0x80000000 */

/********************************* Bit definition for RCC_BDCR register *********************************************/
#define RCC_BDCR_LSEON_Pos                        (0U)
#define RCC_BDCR_LSEON_Msk                        (0x1UL<<RCC_BDCR_LSEON_Pos)                       /*!< 0x00000001 */
#define RCC_BDCR_LSEON                            RCC_BDCR_LSEON_Msk                                
#define RCC_BDCR_LSERDY_Pos                       (1U)
#define RCC_BDCR_LSERDY_Msk                       (0x1UL<<RCC_BDCR_LSERDY_Pos)                      /*!< 0x00000002 */
#define RCC_BDCR_LSERDY                           RCC_BDCR_LSERDY_Msk                               
#define RCC_BDCR_LSEBYP_Pos                       (2U)
#define RCC_BDCR_LSEBYP_Msk                       (0x1UL<<RCC_BDCR_LSEBYP_Pos)                      /*!< 0x00000004 */
#define RCC_BDCR_LSEBYP                           RCC_BDCR_LSEBYP_Msk                               
#define RCC_BDCR_LSEDRV_Pos                       (3U)
#define RCC_BDCR_LSEDRV_Msk                       (0x3UL<<RCC_BDCR_LSEDRV_Pos)                      /*!< 0x00000018 */
#define RCC_BDCR_LSEDRV                           RCC_BDCR_LSEDRV_Msk
#define RCC_BDCR_LSEDRV_0                         (0x1UL<<RCC_BDCR_LSEDRV_Pos)                      /*!< 0x00000008 */
#define RCC_BDCR_LSEDRV_1                         (0x2UL<<RCC_BDCR_LSEDRV_Pos)                      /*!< 0x00000010 */
#define RCC_BDCR_RTCSEL_Pos                       (8U)
#define RCC_BDCR_RTCSEL_Msk                       (0x3UL<<RCC_BDCR_RTCSEL_Pos)                      /*!< 0x00000300 */
#define RCC_BDCR_RTCSEL                           RCC_BDCR_RTCSEL_Msk
#define RCC_BDCR_RTCSEL_0                         (0x1UL<<RCC_BDCR_RTCSEL_Pos)                      /*!< 0x00000100 */
#define RCC_BDCR_RTCSEL_1                         (0x2UL<<RCC_BDCR_RTCSEL_Pos)                      /*!< 0x00000200 */
#define RCC_BDCR_RTCSEL_NOCLOCK                   0x00000000U                                       /*!< No clock */
#define RCC_BDCR_RTCSEL_LSE                       0x00000100U                                       /*!< LSE oscillator clock used as RTC clock */
#define RCC_BDCR_RTCSEL_LSI                       0x00000200U                                       /*!< LSI oscillator clock used as RTC clock */
#define RCC_BDCR_RTCSEL_HSE_DIV128                0x00000300U 

#define RCC_BDCR_RTCEN_Pos                        (15U)
#define RCC_BDCR_RTCEN_Msk                        (0x1UL<<RCC_BDCR_RTCEN_Pos)                       /*!< 0x00008000 */
#define RCC_BDCR_RTCEN                            RCC_BDCR_RTCEN_Msk                                
#define RCC_BDCR_BDRST_Pos                        (16U)
#define RCC_BDCR_BDRST_Msk                        (0x1UL<<RCC_BDCR_BDRST_Pos)                       /*!< 0x00010000 */
#define RCC_BDCR_BDRST                            RCC_BDCR_BDRST_Msk                                

/********************************* Bit definition for RCC_CSR register **********************************************/
#define RCC_CSR_LSION_Pos                         (0U)
#define RCC_CSR_LSION_Msk                         (0x1UL<<RCC_CSR_LSION_Pos)                        /*!< 0x00000001 */
#define RCC_CSR_LSION                             RCC_CSR_LSION_Msk                                 
#define RCC_CSR_LSIRDY_Pos                        (1U)
#define RCC_CSR_LSIRDY_Msk                        (0x1UL<<RCC_CSR_LSIRDY_Pos)                       /*!< 0x00000002 */
#define RCC_CSR_LSIRDY                            RCC_CSR_LSIRDY_Msk                                
#define RCC_CSR_RMVF_Pos                          (24U)
#define RCC_CSR_RMVF_Msk                          (0x1UL<<RCC_CSR_RMVF_Pos)                         /*!< 0x01000000 */
#define RCC_CSR_RMVF                              RCC_CSR_RMVF_Msk                                  
#define RCC_CSR_OBLRSTF_Pos                       (25U)
#define RCC_CSR_OBLRSTF_Msk                       (0x1UL<<RCC_CSR_OBLRSTF_Pos)                      /*!< 0x02000000 */
#define RCC_CSR_OBLRSTF                           RCC_CSR_OBLRSTF_Msk                               
#define RCC_CSR_PINRSTF_Pos                       (26U)
#define RCC_CSR_PINRSTF_Msk                       (0x1UL<<RCC_CSR_PINRSTF_Pos)                      /*!< 0x04000000 */
#define RCC_CSR_PINRSTF                           RCC_CSR_PINRSTF_Msk                               
#define RCC_CSR_PWRRSTF_Pos                       (27U)
#define RCC_CSR_PWRRSTF_Msk                       (0x1UL<<RCC_CSR_PWRRSTF_Pos)                      /*!< 0x08000000 */
#define RCC_CSR_PWRRSTF                           RCC_CSR_PWRRSTF_Msk                               
#define RCC_CSR_SFTRSTF_Pos                       (28U)
#define RCC_CSR_SFTRSTF_Msk                       (0x1UL<<RCC_CSR_SFTRSTF_Pos)                      /*!< 0x10000000 */
#define RCC_CSR_SFTRSTF                           RCC_CSR_SFTRSTF_Msk                               
#define RCC_CSR_IWDGRSTF_Pos                      (29U)
#define RCC_CSR_IWDGRSTF_Msk                      (0x1UL<<RCC_CSR_IWDGRSTF_Pos)                     /*!< 0x20000000 */
#define RCC_CSR_IWDGRSTF                          RCC_CSR_IWDGRSTF_Msk                              
#define RCC_CSR_WWDGRSTF_Pos                      (30U)
#define RCC_CSR_WWDGRSTF_Msk                      (0x1UL<<RCC_CSR_WWDGRSTF_Pos)                     /*!< 0x40000000 */
#define RCC_CSR_WWDGRSTF                          RCC_CSR_WWDGRSTF_Msk                              
#define RCC_CSR_LPWRRSTF_Pos                      (31U)
#define RCC_CSR_LPWRRSTF_Msk                      (0x1UL<<RCC_CSR_LPWRRSTF_Pos)                     /*!< 0x80000000 */
#define RCC_CSR_LPWRRSTF                          RCC_CSR_LPWRRSTF_Msk                              

/********************************* Bit definition for RCC_CFGR1 register ********************************************/
#define RCC_CFGR1_MCOPRE_Pos                      (0U)
#define RCC_CFGR1_MCOPRE_Msk                      (0xFUL<<RCC_CFGR1_MCOPRE_Pos)                     /*!< 0x0000000F */
#define RCC_CFGR1_MCOPRE                          RCC_CFGR1_MCOPRE_Msk
#define RCC_CFGR1_MCOPRE_0                        (0x1UL<<RCC_CFGR1_MCOPRE_Pos)                     /*!< 0x00000001 */
#define RCC_CFGR1_MCOPRE_1                        (0x2UL<<RCC_CFGR1_MCOPRE_Pos)                     /*!< 0x00000002 */
#define RCC_CFGR1_MCOPRE_2                        (0x4UL<<RCC_CFGR1_MCOPRE_Pos)                     /*!< 0x00000004 */
#define RCC_CFGR1_MCOPRE_3                        (0x8UL<<RCC_CFGR1_MCOPRE_Pos)                     /*!< 0x00000008 */
#define RCC_CFGR1_PVDSEL_Pos                      (29U)
#define RCC_CFGR1_PVDSEL_Msk                      (0x3UL<<RCC_CFGR1_PVDSEL_Pos)                     /*!< 0x60000000 */
#define RCC_CFGR1_PVDSEL                          RCC_CFGR1_PVDSEL_Msk
#define RCC_CFGR1_PVDSEL_0                        (0x1UL<<RCC_CFGR1_PVDSEL_Pos)                     /*!< 0x20000000 */
#define RCC_CFGR1_PVDSEL_1                        (0x2UL<<RCC_CFGR1_PVDSEL_Pos)                     /*!< 0x40000000 */

/********************************* Bit definition for RCC_CFGR2 register ********************************************/
#define RCC_CFGR2_HSEDRV_Pos                      (8U)
#define RCC_CFGR2_HSEDRV_Msk                      (0x3UL<<RCC_CFGR2_HSEDRV_Pos)                     /*!< 0x00000300 */
#define RCC_CFGR2_HSEDRV                          RCC_CFGR2_HSEDRV_Msk
#define RCC_CFGR2_HSEDRV_0                        (0x1UL<<RCC_CFGR2_HSEDRV_Pos)                     /*!< 0x00000100 */
#define RCC_CFGR2_HSEDRV_1                        (0x2UL<<RCC_CFGR2_HSEDRV_Pos)                     /*!< 0x00000200 */

/********************************* Bit definition for RCC_CFGR3 register ********************************************/
#define RCC_CFGR3_PLLSRC_Pos                      (0U)
#define RCC_CFGR3_PLLSRC_Msk                      (0x1UL<<RCC_CFGR3_PLLSRC_Pos)                     /*!< 0x00000001 */
#define RCC_CFGR3_PLLSRC                          RCC_CFGR3_PLLSRC_Msk                              
#define RCC_CFGR3_PLLMUL_Pos                      (8U)
#define RCC_CFGR3_PLLMUL_Msk                      (0x7UL<<RCC_CFGR3_PLLMUL_Pos)                     /*!< 0x00000700 */
#define RCC_CFGR3_PLLMUL                          RCC_CFGR3_PLLMUL_Msk
#define RCC_CFGR3_PLLMUL_0                        (0x1UL<<RCC_CFGR3_PLLMUL_Pos)                     /*!< 0x00000100 */
#define RCC_CFGR3_PLLMUL_1                        (0x2UL<<RCC_CFGR3_PLLMUL_Pos)                     /*!< 0x00000200 */
#define RCC_CFGR3_PLLMUL_2                        (0x4UL<<RCC_CFGR3_PLLMUL_Pos)                     /*!< 0x00000400 */

/********************************************************************************************************************/
/********************************* RTC ******************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for RTC_CRH register **********************************************/
#define RTC_CRH_SECIE_Pos                         (0U)
#define RTC_CRH_SECIE_Msk                         (0x1UL<<RTC_CRH_SECIE_Pos)                        /*!< 0x00000001 */
#define RTC_CRH_SECIE                             RTC_CRH_SECIE_Msk                                 /*!< Second interrupt enable */
#define RTC_CRH_ALRIE_Pos                         (1U)
#define RTC_CRH_ALRIE_Msk                         (0x1UL<<RTC_CRH_ALRIE_Pos)                        /*!< 0x00000002 */
#define RTC_CRH_ALRIE                             RTC_CRH_ALRIE_Msk                                 /*!< Alarm interrupt enable */
#define RTC_CRH_OWIE_Pos                          (2U)
#define RTC_CRH_OWIE_Msk                          (0x1UL<<RTC_CRH_OWIE_Pos)                         /*!< 0x00000004 */
#define RTC_CRH_OWIE                              RTC_CRH_OWIE_Msk                                  /*!< Overflow interrupt enable */

/********************************* Bit definition for RTC_CRL register **********************************************/
#define RTC_CRL_SECF_Pos                          (0U)
#define RTC_CRL_SECF_Msk                          (0x1UL<<RTC_CRL_SECF_Pos)                         /*!< 0x00000001 */
#define RTC_CRL_SECF                              RTC_CRL_SECF_Msk                                  /*!< Second flag */
#define RTC_CRL_ALRF_Pos                          (1U)
#define RTC_CRL_ALRF_Msk                          (0x1UL<<RTC_CRL_ALRF_Pos)                         /*!< 0x00000002 */
#define RTC_CRL_ALRF                              RTC_CRL_ALRF_Msk                                  /*!< Alarm flag */
#define RTC_CRL_OWF_Pos                           (2U)
#define RTC_CRL_OWF_Msk                           (0x1UL<<RTC_CRL_OWF_Pos)                          /*!< 0x00000004 */
#define RTC_CRL_OWF                               RTC_CRL_OWF_Msk                                   /*!< Overflow flag */
#define RTC_CRL_RSF_Pos                           (3U)
#define RTC_CRL_RSF_Msk                           (0x1UL<<RTC_CRL_RSF_Pos)                          /*!< 0x00000008 */
#define RTC_CRL_RSF                               RTC_CRL_RSF_Msk                                   /*!< Registers synchronized flag */
#define RTC_CRL_CNF_Pos                           (4U)
#define RTC_CRL_CNF_Msk                           (0x1UL<<RTC_CRL_CNF_Pos)                          /*!< 0x00000010 */
#define RTC_CRL_CNF                               RTC_CRL_CNF_Msk                                   /*!< Configuration flag */
#define RTC_CRL_RTOFF_Pos                         (5U)
#define RTC_CRL_RTOFF_Msk                         (0x1UL<<RTC_CRL_RTOFF_Pos)                        /*!< 0x00000020 */
#define RTC_CRL_RTOFF                             RTC_CRL_RTOFF_Msk                                 /*!< RTC operation OFF */

/********************************* Bit definition for RTC_PRLH register *********************************************/
#define RTC_PRLH_PRL_Pos                          (0U)
#define RTC_PRLH_PRL_Msk                          (0xFUL<<RTC_PRLH_PRL_Pos)                         /*!< 0x0000000F */
#define RTC_PRLH_PRL                              RTC_PRLH_PRL_Msk                                  /*!< RTC pre-scaler reload value high part */
#define RTC_PRLH_PRL_0                            (0x1UL<<RTC_PRLH_PRL_Pos)                         /*!< 0x00000001 */
#define RTC_PRLH_PRL_1                            (0x2UL<<RTC_PRLH_PRL_Pos)                         /*!< 0x00000002 */
#define RTC_PRLH_PRL_2                            (0x4UL<<RTC_PRLH_PRL_Pos)                         /*!< 0x00000004 */
#define RTC_PRLH_PRL_3                            (0x8UL<<RTC_PRLH_PRL_Pos)                         /*!< 0x00000008 */

/********************************* Bit definition for RTC_PRLL register *********************************************/
#define RTC_PRLL_PRL_Pos                          (0U)
#define RTC_PRLL_PRL_Msk                          (0xFFFFUL<<RTC_PRLL_PRL_Pos)                      /*!< 0x0000FFFF */
#define RTC_PRLL_PRL                              RTC_PRLL_PRL_Msk                                  /*!< RTC pre-scaler reload value low part */

/********************************* Bit definition for RTC_DIVH register *********************************************/
#define RTC_DIVH_RTC_DIV_Pos                      (0U)
#define RTC_DIVH_RTC_DIV_Msk                      (0xFUL<<RTC_DIVH_RTC_DIV_Pos)                     /*!< 0x0000000F */
#define RTC_DIVH_RTC_DIV                          RTC_DIVH_RTC_DIV_Msk                              /*!< RTC clock divider high part */
#define RTC_DIVH_RTC_DIV_0                        (0x1UL<<RTC_DIVH_RTC_DIV_Pos)                     /*!< 0x00000001 */
#define RTC_DIVH_RTC_DIV_1                        (0x2UL<<RTC_DIVH_RTC_DIV_Pos)                     /*!< 0x00000002 */
#define RTC_DIVH_RTC_DIV_2                        (0x4UL<<RTC_DIVH_RTC_DIV_Pos)                     /*!< 0x00000004 */
#define RTC_DIVH_RTC_DIV_3                        (0x8UL<<RTC_DIVH_RTC_DIV_Pos)                     /*!< 0x00000008 */

/********************************* Bit definition for RTC_DIVL register *********************************************/
#define RTC_DIVL_RTC_DIV_Pos                      (0U)
#define RTC_DIVL_RTC_DIV_Msk                      (0xFFFFUL<<RTC_DIVL_RTC_DIV_Pos)                  /*!< 0x0000FFFF */
#define RTC_DIVL_RTC_DIV                          RTC_DIVL_RTC_DIV_Msk                              /*!< RTC clock divider low part */

/********************************* Bit definition for RTC_CNTH register *********************************************/
#define RTC_CNTH_RTC_CNT_Pos                      (0U)
#define RTC_CNTH_RTC_CNT_Msk                      (0xFFFFUL<<RTC_CNTH_RTC_CNT_Pos)                  /*!< 0x0000FFFF */
#define RTC_CNTH_RTC_CNT                          RTC_CNTH_RTC_CNT_Msk                              /*!< RTC counter high part */

/********************************* Bit definition for RTC_CNTL register *********************************************/
#define RTC_CNTL_RTC_CNT_Pos                      (0U)
#define RTC_CNTL_RTC_CNT_Msk                      (0xFFFFUL<<RTC_CNTL_RTC_CNT_Pos)                  /*!< 0x0000FFFF */
#define RTC_CNTL_RTC_CNT                          RTC_CNTL_RTC_CNT_Msk                              /*!< RTC counter high part */

/********************************* Bit definition for RTC_ALRH register *********************************************/
#define RTC_ALRH_RTC_ALR_Pos                      (0U)
#define RTC_ALRH_RTC_ALR_Msk                      (0xFFFFUL<<RTC_ALRH_RTC_ALR_Pos)                  /*!< 0x0000FFFF */
#define RTC_ALRH_RTC_ALR                          RTC_ALRH_RTC_ALR_Msk                              /*!< RTC alarm high part */

/********************************* Bit definition for RTC_ALRL register *********************************************/
#define RTC_ALRL_RTC_ALR_Pos                      (0U)
#define RTC_ALRL_RTC_ALR_Msk                      (0xFFFFUL<<RTC_ALRL_RTC_ALR_Pos)                  /*!< 0x0000FFFF */
#define RTC_ALRL_RTC_ALR                          RTC_ALRL_RTC_ALR_Msk                              /*!< RTC alarm low part */

/********************************* Bit definition for RTC_TMPCFGR register ******************************************/
#define RTC_TMPCFGR_TPE_Pos                       (0U)
#define RTC_TMPCFGR_TPE_Msk                       (0x1UL<<RTC_TMPCFGR_TPE_Pos)                      /*!< 0x00000001 */
#define RTC_TMPCFGR_TPE                           RTC_TMPCFGR_TPE_Msk                               /*!< RTC intrusion detection enable */
#define RTC_TMPCFGR_TPAL_Pos                      (1U)
#define RTC_TMPCFGR_TPAL_Msk                      (0x1UL<<RTC_TMPCFGR_TPAL_Pos)                      /*!< 0x00000002 */
#define RTC_TMPCFGR_TPAL                          RTC_TMPCFGR_TPAL_Msk                              /*!< RTC intrusion detection pin level */

/********************************* Bit definition for RTC_TMPCSR register *******************************************/
#define RTC_TMPCSR_CTE_Pos                        (0U)
#define RTC_TMPCSR_CTE_Msk                        (0x1UL<<RTC_TMPCSR_CTE_Pos)                      /*!< 0x00000001 */
#define RTC_TMPCSR_CTE                            RTC_TMPCSR_CTE_Msk                               /*!< RTC clear intrusion detection event */
#define RTC_TMPCSR_CTI_Pos                        (1U)
#define RTC_TMPCSR_CTI_Msk                        (0x1UL<<RTC_TMPCSR_CTI_Pos)                      /*!< 0x00000002 */
#define RTC_TMPCSR_CTI                            RTC_TMPCSR_CTI_Msk                               /*!< RTC clear intrusion detection interrupt */
#define RTC_TMPCSR_TPIE_Pos                       (2U)
#define RTC_TMPCSR_TPIE_Msk                       (0x1UL<<RTC_TMPCSR_TPIE_Pos)                     /*!< 0x00000004 */
#define RTC_TMPCSR_TPIE                           RTC_TMPCSR_TPIE_Msk                              /*!< RTC intrusion detection interrupt enable */
#define RTC_TMPCSR_TEF_Pos                        (8U)
#define RTC_TMPCSR_TEF_Msk                        (0x1UL<<RTC_TMPCSR_TEF_Pos)                      /*!< 0x00000100 */
#define RTC_TMPCSR_TEF                            RTC_TMPCSR_TEF_Msk                               /*!< RTC clear intrusion detection event flag */
#define RTC_TMPCSR_TIF_Pos                        (9U)
#define RTC_TMPCSR_TIF_Msk                        (0x1UL<<RTC_TMPCSR_TIF_Pos)                      /*!< 0x00000200 */
#define RTC_TMPCSR_TIF                            RTC_TMPCSR_TIF_Msk                               /*!< RTC clear intrusion detection interrupt flag */

/********************************* Bit definition for RTC_CALIBR register *******************************************/
#define RTC_CALIBR_CAL_Pos                        (0U)
#define RTC_CALIBR_CAL_Msk                        (0x7FUL<<RTC_CALIBR_CAL_Pos)                      /*!< 0x0000007F */
#define RTC_CALIBR_CAL                            RTC_CALIBR_CAL_Msk                               /*!< RTC Calibration value */
#define RTC_CALIBR_CCO_Pos                        (7U)
#define RTC_CALIBR_CCO_Msk                        (0x1UL<<RTC_CALIBR_CCO_Pos)                      /*!< 0x00000002 */
#define RTC_CALIBR_CCO                            RTC_CALIBR_CCO_Msk                               /*!< RTC Calibration clock output */
#define RTC_CALIBR_ASOE_Pos                       (8U)
#define RTC_CALIBR_ASOE_Msk                       (0x1UL<<RTC_CALIBR_ASOE_Pos)                     /*!< 0x00000004 */
#define RTC_CALIBR_ASOE                           RTC_CALIBR_ASOE_Msk                              /*!< RTC Alarm or second output enable */
#define RTC_CALIBR_ASOS_Pos                       (9U)
#define RTC_CALIBR_ASOS_Msk                       (0x1UL<<RTC_CALIBR_ASOS_Pos)                     /*!< 0x00000004 */
#define RTC_CALIBR_ASOS                           RTC_CALIBR_ASOS_Msk                              /*!< RTC Alarm or second output selection */

/********************************* Bit definition for RTC_BKPDR0 register ******************************************/
#define RTC_BKPDR0_D_Pos                          (0U)
#define RTC_BKPDR0_D_Msk                          (0xFFFFFFFFUL<<RTC_BKPDR0_D_Pos)                 /*!< 0xFFFFFFFF */
#define RTC_BKPDR0_D                              RTC_BKPDR0_D_Msk                                 /*!< RTC Backup data word0 */

/********************************* Bit definition for RTC_BKPDR1 register ******************************************/
#define RTC_BKPDR1_D_Pos                          (0U)
#define RTC_BKPDR1_D_Msk                          (0xFFFFFFFFUL<<RTC_BKPDR1_D_Pos)                 /*!< 0xFFFFFFFF */
#define RTC_BKPDR1_D                              RTC_BKPDR1_D_Msk                                 /*!< RTC Backup data word1 */

/********************************* Bit definition for RTC_BKPDR2 register ******************************************/
#define RTC_BKPDR2_D_Pos                          (0U)
#define RTC_BKPDR2_D_Msk                          (0xFFFFFFFFUL<<RTC_BKPDR2_D_Pos)                 /*!< 0xFFFFFFFF */
#define RTC_BKPDR2_D                              RTC_BKPDR2_D_Msk                                 /*!< RTC Backup data word2 */

/********************************* Bit definition for RTC_BKPDR3 register ******************************************/
#define RTC_BKPDR3_D_Pos                          (0U)
#define RTC_BKPDR3_D_Msk                          (0xFFFFFFFFUL<<RTC_BKPDR3_D_Pos)                 /*!< 0xFFFFFFFF */
#define RTC_BKPDR3_D                              RTC_BKPDR3_D_Msk                                 /*!< RTC Backup data word3 */

/********************************* Bit definition for RTC_BKPDR4 register ******************************************/
#define RTC_BKPDR4_D_Pos                          (0U)
#define RTC_BKPDR4_D_Msk                          (0xFFFFFFFFUL<<RTC_BKPDR4_D_Pos)                 /*!< 0xFFFFFFFF */
#define RTC_BKPDR4_D                              RTC_BKPDR4_D_Msk                                 /*!< RTC Backup data word4 */

/********************************************************************************************************************/
/********************************* SPI1 *****************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for SPI_CR1 register **********************************************/
#define SPI_CR1_CPHA_Pos                          (0U)
#define SPI_CR1_CPHA_Msk                          (0x1UL<<SPI_CR1_CPHA_Pos)                         /*!< 0x00000001 */
#define SPI_CR1_CPHA                              SPI_CR1_CPHA_Msk                                  /*!< Clock Phase */
#define SPI_CR1_CPOL_Pos                          (1U)
#define SPI_CR1_CPOL_Msk                          (0x1UL<<SPI_CR1_CPOL_Pos)                         /*!< 0x00000002 */
#define SPI_CR1_CPOL                              SPI_CR1_CPOL_Msk                                  /*!< Clock Polarity  */
#define SPI_CR1_MSTR_Pos                          (2U)
#define SPI_CR1_MSTR_Msk                          (0x1UL<<SPI_CR1_MSTR_Pos)                         /*!< 0x00000004 */
#define SPI_CR1_MSTR                              SPI_CR1_MSTR_Msk                                  /*!< Master Selection */
#define SPI_CR1_BR_Pos                            (3U)
#define SPI_CR1_BR_Msk                            (0x7UL<<SPI_CR1_BR_Pos)                           /*!< 0x00000038 */
#define SPI_CR1_BR                                SPI_CR1_BR_Msk                                    /*!< Baud Rate Control */
#define SPI_CR1_BR_0                              (0x1UL<<SPI_CR1_BR_Pos)                           /*!< 0x00000008 */
#define SPI_CR1_BR_1                              (0x2UL<<SPI_CR1_BR_Pos)                           /*!< 0x00000010 */
#define SPI_CR1_BR_2                              (0x4UL<<SPI_CR1_BR_Pos)                           /*!< 0x00000020 */
#define SPI_CR1_SPE_Pos                           (6U)
#define SPI_CR1_SPE_Msk                           (0x1UL<<SPI_CR1_SPE_Pos)                          /*!< 0x00000040 */
#define SPI_CR1_SPE                               SPI_CR1_SPE_Msk                                   /*!< SPI Enable */
#define SPI_CR1_LSBFIRST_Pos                      (7U)
#define SPI_CR1_LSBFIRST_Msk                      (0x1UL<<SPI_CR1_LSBFIRST_Pos)                     /*!< 0x00000080 */
#define SPI_CR1_LSBFIRST                          SPI_CR1_LSBFIRST_Msk                              /*!<  Frame Format */
#define SPI_CR1_SSI_Pos                           (8U)
#define SPI_CR1_SSI_Msk                           (0x1UL<<SPI_CR1_SSI_Pos)                          /*!< 0x00000100 */
#define SPI_CR1_SSI                               SPI_CR1_SSI_Msk                                   /*!< Internal slave select */
#define SPI_CR1_SSM_Pos                           (9U)
#define SPI_CR1_SSM_Msk                           (0x1UL<<SPI_CR1_SSM_Pos)                          /*!< 0x00000200 */
#define SPI_CR1_SSM                               SPI_CR1_SSM_Msk                                   /*!< Software slave management  */
#define SPI_CR1_RXONLY_Pos                        (10U)
#define SPI_CR1_RXONLY_Msk                        (0x1UL<<SPI_CR1_RXONLY_Pos)                       /*!< 0x00000400 */
#define SPI_CR1_RXONLY                            SPI_CR1_RXONLY_Msk                                /*!< Receive only */
#define SPI_CR1_DFF_Pos                           (11U)
#define SPI_CR1_DFF_Msk                           (0x1UL<<SPI_CR1_DFF_Pos)                          /*!< 0x00000800 */
#define SPI_CR1_DFF                               SPI_CR1_DFF_Msk                                   /*!< Data frame format */
#define SPI_CR1_CRCNEXT_Pos                       (12U)
#define SPI_CR1_CRCNEXT_Msk                       (0x1UL << SPI_CR1_CRCNEXT_Pos)                    /*!< 0x00001000 */
#define SPI_CR1_CRCNEXT                           SPI_CR1_CRCNEXT_Msk                               /*!< desc CRCNEXT */
#define SPI_CR1_CRCEN_Pos                         (13U)
#define SPI_CR1_CRCEN_Msk                         (0x1UL << SPI_CR1_CRCEN_Pos)                      /*!< 0x00002000 */
#define SPI_CR1_CRCEN                             SPI_CR1_CRCEN_Msk                                 /*!< desc CRCEN */
#define SPI_CR1_BIDIOE_Pos                        (14U)
#define SPI_CR1_BIDIOE_Msk                        (0x1UL<<SPI_CR1_BIDIOE_Pos)                       /*!< 0x00004000 */
#define SPI_CR1_BIDIOE                            SPI_CR1_BIDIOE_Msk                                /*!< Output enable in bidirectional mode */
#define SPI_CR1_BIDIMODE_Pos                      (15U)
#define SPI_CR1_BIDIMODE_Msk                      (0x1UL<<SPI_CR1_BIDIMODE_Pos)                     /*!< 0x00008000 */
#define SPI_CR1_BIDIMODE                          SPI_CR1_BIDIMODE_Msk                              /*!< Bidirectional data mode enable */

/********************************* Bit definition for SPI_CR2 register **********************************************/
#define SPI_CR2_RXDMAEN_Pos                       (0U)
#define SPI_CR2_RXDMAEN_Msk                       (0x1UL<<SPI_CR2_RXDMAEN_Pos)                      /*!< 0x00000001 */
#define SPI_CR2_RXDMAEN                           SPI_CR2_RXDMAEN_Msk                               /*!< Rx buffer DMA enable */
#define SPI_CR2_TXDMAEN_Pos                       (1U)
#define SPI_CR2_TXDMAEN_Msk                       (0x1UL<<SPI_CR2_TXDMAEN_Pos)                      /*!< 0x00000002 */
#define SPI_CR2_TXDMAEN                           SPI_CR2_TXDMAEN_Msk                               /*!< Tx buffer DMA enable */
#define SPI_CR2_SSOE_Pos                          (2U)
#define SPI_CR2_SSOE_Msk                          (0x1UL<<SPI_CR2_SSOE_Pos)                         /*!< 0x00000004 */
#define SPI_CR2_SSOE                              SPI_CR2_SSOE_Msk                                  /*!< SS Output Enable  */
#define SPI_CR2_CLRTXFIFO_Pos                     (4U)
#define SPI_CR2_CLRTXFIFO_Msk                     (0x1UL<<SPI_CR2_CLRTXFIFO_Pos)                    /*!< 0x00000010 */
#define SPI_CR2_CLRTXFIFO                         SPI_CR2_CLRTXFIFO_Msk                             /*!< Clear FIFO */
#define SPI_CR2_ERRIE_Pos                         (5U)
#define SPI_CR2_ERRIE_Msk                         (0x1UL<<SPI_CR2_ERRIE_Pos)                        /*!< 0x00000020 */
#define SPI_CR2_ERRIE                             SPI_CR2_ERRIE_Msk                                 /*!< Error Interrupt Enable */
#define SPI_CR2_RXNEIE_Pos                        (6U)
#define SPI_CR2_RXNEIE_Msk                        (0x1UL<<SPI_CR2_RXNEIE_Pos)                       /*!< 0x00000040 */
#define SPI_CR2_RXNEIE                            SPI_CR2_RXNEIE_Msk                                /*!< RX buffer Not Empty Interrupt Enable */
#define SPI_CR2_TXEIE_Pos                         (7U)
#define SPI_CR2_TXEIE_Msk                         (0x1UL<<SPI_CR2_TXEIE_Pos)                        /*!< 0x00000080 */
#define SPI_CR2_TXEIE                             SPI_CR2_TXEIE_Msk                                 /*!< Tx buffer Empty Interrupt Enable */
#define SPI_CR2_FRXTH_Pos                         (12U)
#define SPI_CR2_FRXTH_Msk                         (0x1UL<<SPI_CR2_FRXTH_Pos)                        /*!< 0x00001000 */
#define SPI_CR2_FRXTH                             SPI_CR2_FRXTH_Msk                                 /*!< FIFO receive threshold Cycle Sampling*/
#define SPI_CR2_SAMPLE_SELECT_Pos                 (14U)
#define SPI_CR2_SAMPLE_SELECT_Msk                 (0x1UL<<SPI_CR2_SAMPLE_SELECT_Pos)                /*!< 0x00004000 */
#define SPI_CR2_SAMPLE_SELECT                     SPI_CR2_SAMPLE_SELECT_Msk                         /*!< Cycle Sampling*/
#define SPI_CR2_FRF_Pos                           (15U)
#define SPI_CR2_FRF_Msk                           (0x1UL<<SPI_CR2_FRF_Pos)                          /*!< 0x00008000 */
#define SPI_CR2_FRF                               SPI_CR2_FRF_Msk                                   /*!< Frame format */

/********************************* Bit definition for SPI_SR register ***********************************************/
#define SPI_SR_RXNE_Pos                           (0U)
#define SPI_SR_RXNE_Msk                           (0x1UL<<SPI_SR_RXNE_Pos)                          /*!< 0x00000001 */
#define SPI_SR_RXNE                               SPI_SR_RXNE_Msk                                   /*!< Receive buffer Not Empty  */
#define SPI_SR_TXE_Pos                            (1U)
#define SPI_SR_TXE_Msk                            (0x1UL<<SPI_SR_TXE_Pos)                           /*!< 0x00000002 */
#define SPI_SR_TXE                                SPI_SR_TXE_Msk                                    /*!< Transmit buffer Empty  */
#define SPI_SR_CHSIDE_Pos                         (2U)
#define SPI_SR_CHSIDE_Msk                         (0x1UL << SPI_SR_CHSIDE_Pos)                      /*!< 0x00000004 */
#define SPI_SR_CHSIDE                             SPI_SR_CHSIDE_Msk                                 /*!< desc CHSIDE */
#define SPI_SR_UDR_Pos                            (3U)
#define SPI_SR_UDR_Msk                            (0x1UL << SPI_SR_UDR_Pos)                         /*!< 0x00000008 */
#define SPI_SR_UDR                                SPI_SR_UDR_Msk                                    /*!< desc UDR */
#define SPI_SR_CRCERR_Pos                         (4U)
#define SPI_SR_CRCERR_Msk                         (0x1UL << SPI_SR_CRCERR_Pos)                      /*!< 0x00000010 */
#define SPI_SR_CRCERR                             SPI_SR_CRCERR_Msk                                 /*!< desc CRCERR */
#define SPI_SR_MODF_Pos                           (5U)
#define SPI_SR_MODF_Msk                           (0x1UL<<SPI_SR_MODF_Pos)                          /*!< 0x00000020 */
#define SPI_SR_MODF                               SPI_SR_MODF_Msk                                   /*!< Mode fault */
#define SPI_SR_OVR_Pos                            (6U)
#define SPI_SR_OVR_Msk                            (0x1UL<<SPI_SR_OVR_Pos)                           /*!< 0x00000040 */
#define SPI_SR_OVR                                SPI_SR_OVR_Msk                                    /*!<  Overrun flag */
#define SPI_SR_BSY_Pos                            (7U)
#define SPI_SR_BSY_Msk                            (0x1UL<<SPI_SR_BSY_Pos)                           /*!< 0x00000080 */
#define SPI_SR_BSY                                SPI_SR_BSY_Msk                                    /*!< Busy flag  */
#define SPI_SR_FRE_Pos                            (8U)
#define SPI_SR_FRE_Msk                            (0x1UL<<SPI_SR_FRE_Pos)                           /*!< 0x00000100 */
#define SPI_SR_FRE                                SPI_SR_FRE_Msk                                    
#define SPI_SR_FRLVL_Pos                          (9U)
#define SPI_SR_FRLVL_Msk                          (0x3UL<<SPI_SR_FRLVL_Pos)                         /*!< 0x00000600 */
#define SPI_SR_FRLVL                              SPI_SR_FRLVL_Msk                                  /*!< FIFO Reception Level */
#define SPI_SR_FRLVL_0                            (0x1UL<<SPI_SR_FRLVL_Pos)                         /*!< 0x00000200 */
#define SPI_SR_FRLVL_1                            (0x2UL<<SPI_SR_FRLVL_Pos)                         /*!< 0x00000400 */
#define SPI_SR_FTLVL_Pos                          (11U)
#define SPI_SR_FTLVL_Msk                          (0x3UL<<SPI_SR_FTLVL_Pos)                         /*!< 0x00001800 */
#define SPI_SR_FTLVL                              SPI_SR_FTLVL_Msk                                  /*!< FIFO Transmission Level */
#define SPI_SR_FTLVL_0                            (0x1UL<<SPI_SR_FTLVL_Pos)                         /*!< 0x00000800 */
#define SPI_SR_FTLVL_1                            (0x2UL<<SPI_SR_FTLVL_Pos)                         /*!< 0x00001000 */

/********************************* Bit definition for SPI_DR register ***********************************************/
#define SPI_DR_DR_Pos                             (0U)
#define SPI_DR_DR_Msk                             (0xFFFFUL<<SPI_DR_DR_Pos)                         /*!< 0x0000FFFF */
#define SPI_DR_DR                                 SPI_DR_DR_Msk                                     /*!< Data Register */

/********************************* Bit definition for SPI_CRCPR register ********************************************/
#define SPI_CRCPR_CRCPOLY_Pos                     (0U)
#define SPI_CRCPR_CRCPOLY_Msk                     (0xFFFFUL<<SPI_CRCPR_CRCPOLY_Pos)                 /*!< 0x0000FFFF */
#define SPI_CRCPR_CRCPOLY                         SPI_CRCPR_CRCPOLY_Msk                             /*!< CRC polynomial register */

/********************************* Bit definition for SPI_RXCRCR register *******************************************/
#define SPI_RXCRCR_RXCRC_Pos                      (0U)
#define SPI_RXCRCR_RXCRC_Msk                      (0xFFFFUL<<SPI_RXCRCR_RXCRC_Pos)                  /*!< 0x0000FFFF */
#define SPI_RXCRCR_RXCRC                          SPI_RXCRCR_RXCRC_Msk                              /*!< rcv crc reg */

/********************************* Bit definition for SPI_TXCRCR register *******************************************/
#define SPI_TXCRCR_TXCRC_Pos                      (0U)
#define SPI_TXCRCR_TXCRC_Msk                      (0xFFFFUL<<SPI_TXCRCR_TXCRC_Pos)                  /*!< 0x0000FFFF */
#define SPI_TXCRCR_TXCRC                          SPI_TXCRCR_TXCRC_Msk                              /*!< tx crc reg  */

/********************************* Bit definition for SPI_I2SCFGR register ******************************************/
#define SPI_I2SCFGR_CHLEN_Pos                     (0U)
#define SPI_I2SCFGR_CHLEN_Msk                     (0x1UL<<SPI_I2SCFGR_CHLEN_Pos)                    /*!< 0x00000001 */
#define SPI_I2SCFGR_CHLEN                         SPI_I2SCFGR_CHLEN_Msk                             /*!< Channel length (number of bits per audio channel */
#define SPI_I2SCFGR_DATLEN_Pos                    (1U)
#define SPI_I2SCFGR_DATLEN_Msk                    (0x3UL<<SPI_I2SCFGR_DATLEN_Pos)                   /*!< 0x00000006 */
#define SPI_I2SCFGR_DATLEN                        SPI_I2SCFGR_DATLEN_Msk                            /*!< Data length to be transferred */
#define SPI_I2SCFGR_DATLEN_0                      (0x1UL<<SPI_I2SCFGR_DATLEN_Pos)                   /*!< 0x00000002 */
#define SPI_I2SCFGR_DATLEN_1                      (0x2UL<<SPI_I2SCFGR_DATLEN_Pos)                   /*!< 0x00000004 */
#define SPI_I2SCFGR_CKPOL_Pos                     (3U)
#define SPI_I2SCFGR_CKPOL_Msk                     (0x1UL<<SPI_I2SCFGR_CKPOL_Pos)                    /*!< 0x00000008 */
#define SPI_I2SCFGR_CKPOL                         SPI_I2SCFGR_CKPOL_Msk                             /*!< Steady state clock polarity */
#define SPI_I2SCFGR_I2SSTD_Pos                    (4U)
#define SPI_I2SCFGR_I2SSTD_Msk                    (0x3UL<<SPI_I2SCFGR_I2SSTD_Pos)                   /*!< 0x00000030 */
#define SPI_I2SCFGR_I2SSTD                        SPI_I2SCFGR_I2SSTD_Msk                            /*!< I2S standard selection */
#define SPI_I2SCFGR_I2SSTD_0                      (0x1UL<<SPI_I2SCFGR_I2SSTD_Pos)                   /*!< 0x00000010 */
#define SPI_I2SCFGR_I2SSTD_1                      (0x2UL<<SPI_I2SCFGR_I2SSTD_Pos)                   /*!< 0x00000020 */
#define SPI_I2SCFGR_PCMSYNC_Pos                   (7U)
#define SPI_I2SCFGR_PCMSYNC_Msk                   (0x1UL<<SPI_I2SCFGR_PCMSYNC_Pos)                  /*!< 0x00000080 */
#define SPI_I2SCFGR_PCMSYNC                       SPI_I2SCFGR_PCMSYNC_Msk                           /*!< PCM frame synchronization */
#define SPI_I2SCFGR_I2SCFG_Pos                    (8U)
#define SPI_I2SCFGR_I2SCFG_Msk                    (0x3UL<<SPI_I2SCFGR_I2SCFG_Pos)                   /*!< 0x00000300 */
#define SPI_I2SCFGR_I2SCFG                        SPI_I2SCFGR_I2SCFG_Msk                            /*!< I2S configuration mode */
#define SPI_I2SCFGR_I2SCFG_0                      (0x1UL<<SPI_I2SCFGR_I2SCFG_Pos)                   /*!< 0x00000100 */
#define SPI_I2SCFGR_I2SCFG_1                      (0x2UL<<SPI_I2SCFGR_I2SCFG_Pos)                   /*!< 0x00000200 */
#define SPI_I2SCFGR_I2SE_Pos                      (10U)
#define SPI_I2SCFGR_I2SE_Msk                      (0x1UL<<SPI_I2SCFGR_I2SE_Pos)                     /*!< 0x00000400 */
#define SPI_I2SCFGR_I2SE                          SPI_I2SCFGR_I2SE_Msk                              /*!<  I2S enable */
#define SPI_I2SCFGR_I2SMOD_Pos                    (11U)
#define SPI_I2SCFGR_I2SMOD_Msk                    (0x1UL<<SPI_I2SCFGR_I2SMOD_Pos)                   /*!< 0x00000800 */
#define SPI_I2SCFGR_I2SMOD                        SPI_I2SCFGR_I2SMOD_Msk                            /*!< I2S mode selection */

/********************************* Bit definition for SPI_I2SPR register ********************************************/
#define SPI_I2SPR_I2SDIV_Pos                      (0U)
#define SPI_I2SPR_I2SDIV_Msk                      (0xFFUL<<SPI_I2SPR_I2SDIV_Pos)                    /*!< 0x000000FF */
#define SPI_I2SPR_I2SDIV                          SPI_I2SPR_I2SDIV_Msk                              /*!< I2S linear prescaler */
#define SPI_I2SPR_ODD_Pos                         (8U)
#define SPI_I2SPR_ODD_Msk                         (0x1UL<<SPI_I2SPR_ODD_Pos)                        /*!< 0x00000100 */
#define SPI_I2SPR_ODD                             SPI_I2SPR_ODD_Msk                                 /*!< Odd factor for the prescaler */
#define SPI_I2SPR_MCKOE_Pos                       (9U)
#define SPI_I2SPR_MCKOE_Msk                       (0x1UL<<SPI_I2SPR_MCKOE_Pos)                      /*!< 0x00000200 */
#define SPI_I2SPR_MCKOE                           SPI_I2SPR_MCKOE_Msk                               /*!<  Master clock output enable */

#define SPI_I2S_SUPPORT       /*!< I2S support */

/********************************************************************************************************************/
/********************************* SYSCFG ***************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for SYSCFG_CFGR1 register *****************************************/
#define SYSCFG_CFGR1_MEM_MODE_Pos                 (0U)
#define SYSCFG_CFGR1_MEM_MODE_Msk                 (0x3UL<<SYSCFG_CFGR1_MEM_MODE_Pos)                /*!< 0x00000003 */
#define SYSCFG_CFGR1_MEM_MODE                     SYSCFG_CFGR1_MEM_MODE_Msk                         /*!< memory mapping mode */
#define SYSCFG_CFGR1_MEM_MODE_0                   (0x1UL<<SYSCFG_CFGR1_MEM_MODE_Pos)                /*!< 0x00000001 */
#define SYSCFG_CFGR1_MEM_MODE_1                   (0x2UL<<SYSCFG_CFGR1_MEM_MODE_Pos)                /*!< 0x00000002 */
#define SYSCFG_CFGR1_I2C1_FMP_Pos                 (2U)
#define SYSCFG_CFGR1_I2C1_FMP_Msk                 (0x1UL<<SYSCFG_CFGR1_I2C1_FMP_Pos)                /*!< 0x00000004 */
#define SYSCFG_CFGR1_I2C1_FMP                     SYSCFG_CFGR1_I2C1_FMP_Msk                         /*!< I2C1 Fast-mode Plus driving capability activation */
#define SYSCFG_CFGR1_I2C2_FMP_Pos                 (3U)
#define SYSCFG_CFGR1_I2C2_FMP_Msk                 (0x1UL<<SYSCFG_CFGR1_I2C2_FMP_Pos)                /*!< 0x00000008 */
#define SYSCFG_CFGR1_I2C2_FMP                     SYSCFG_CFGR1_I2C2_FMP_Msk                         /*!< I2C2 Fast-mode Plus driving capability activation */
#define SYSCFG_CFGR1_I2C1_FLTEN_Pos               (4U)
#define SYSCFG_CFGR1_I2C1_FLTEN_Msk               (1UL<<SYSCFG_CFGR1_I2C1_FLTEN_Pos)                /*!< 0x00000010 */
#define SYSCFG_CFGR1_I2C1_FLTEN                   SYSCFG_CFGR1_I2C1_FLTEN_Msk                       /*!< I2C1 filter enable */
#define SYSCFG_CFGR1_I2C2_FLTEN_Pos               (5U)
#define SYSCFG_CFGR1_I2C2_FLTEN_Msk               (1UL<<SYSCFG_CFGR1_I2C2_FLTEN_Pos)                /*!< 0x00000020 */
#define SYSCFG_CFGR1_I2C2_FLTEN                   SYSCFG_CFGR1_I2C2_FLTEN_Msk                       /*!< I2C2 filter enable */
                                                                                                   
/********************************* Bit definition for SYSCFG_CFGR2 register *****************************************/
#define SYSCFG_CFGR2_CLL_Pos                      (0U)
#define SYSCFG_CFGR2_CLL_Msk                      (0x1UL<<SYSCFG_CFGR2_CLL_Pos)                     /*!< 0x00000001 */
#define SYSCFG_CFGR2_CLL                          SYSCFG_CFGR2_CLL_Msk                              /*!< core lockup enable */
#define SYSCFG_CFGR2_PVDL_Pos                     (2U)
#define SYSCFG_CFGR2_PVDL_Msk                     (0x1UL<<SYSCFG_CFGR2_PVDL_Pos)                    /*!< 0x00000004 */
#define SYSCFG_CFGR2_PVDL                         SYSCFG_CFGR2_PVDL_Msk                             /*!< pvd lock enable */

/********************************* Bit definition for SYSCFG_CFGR3 register *****************************************/
#define SYSCFG_CFGR3_DMA1_MAP1_Pos                 (0U)
#define SYSCFG_CFGR3_DMA1_MAP1_Msk                 (0x7FUL << SYSCFG_CFGR3_DMA1_MAP1_Pos)             /*!< 0x0000007F */
#define SYSCFG_CFGR3_DMA1_MAP1                     SYSCFG_CFGR3_DMA1_MAP1_Msk                         /*!< DMA1 ch1 mapping */
#define SYSCFG_CFGR3_DMA1_MAP1_0                   (0x1UL << SYSCFG_CFGR3_DMA1_MAP1_Pos)              /*!< 0x00000001 */
#define SYSCFG_CFGR3_DMA1_MAP1_1                   (0x2UL << SYSCFG_CFGR3_DMA1_MAP1_Pos)              /*!< 0x00000002 */
#define SYSCFG_CFGR3_DMA1_MAP1_2                   (0x4UL << SYSCFG_CFGR3_DMA1_MAP1_Pos)              /*!< 0x00000004 */
#define SYSCFG_CFGR3_DMA1_MAP1_3                   (0x8UL << SYSCFG_CFGR3_DMA1_MAP1_Pos)              /*!< 0x00000008 */
#define SYSCFG_CFGR3_DMA1_MAP1_4                   (0x10UL << SYSCFG_CFGR3_DMA1_MAP1_Pos)             /*!< 0x00000010 */
#define SYSCFG_CFGR3_DMA1_MAP1_5                   (0x20UL << SYSCFG_CFGR3_DMA1_MAP1_Pos)             /*!< 0x00000020 */
#define SYSCFG_CFGR3_DMA1_MAP1_6                   (0x40UL << SYSCFG_CFGR3_DMA1_MAP1_Pos)             /*!< 0x00000040 */

#define SYSCFG_CFGR3_DMA1_MAP2_Pos                 (8U)
#define SYSCFG_CFGR3_DMA1_MAP2_Msk                 (0x7FUL << SYSCFG_CFGR3_DMA1_MAP2_Pos)             /*!< 0x00007F00 */
#define SYSCFG_CFGR3_DMA1_MAP2                     SYSCFG_CFGR3_DMA1_MAP2_Msk                         /*!< DMA1 ch2 mapping */
#define SYSCFG_CFGR3_DMA1_MAP2_0                   (0x1UL << SYSCFG_CFGR3_DMA1_MAP2_Pos)              /*!< 0x00000100 */
#define SYSCFG_CFGR3_DMA1_MAP2_1                   (0x2UL << SYSCFG_CFGR3_DMA1_MAP2_Pos)              /*!< 0x00000200 */
#define SYSCFG_CFGR3_DMA1_MAP2_2                   (0x4UL << SYSCFG_CFGR3_DMA1_MAP2_Pos)              /*!< 0x00000400 */
#define SYSCFG_CFGR3_DMA1_MAP2_3                   (0x8UL << SYSCFG_CFGR3_DMA1_MAP2_Pos)              /*!< 0x00000800 */
#define SYSCFG_CFGR3_DMA1_MAP2_4                   (0x10UL << SYSCFG_CFGR3_DMA1_MAP2_Pos)             /*!< 0x00001000 */
#define SYSCFG_CFGR3_DMA1_MAP2_5                   (0x20UL << SYSCFG_CFGR3_DMA1_MAP2_Pos)             /*!< 0x00002000 */
#define SYSCFG_CFGR3_DMA1_MAP2_6                   (0x40UL << SYSCFG_CFGR3_DMA1_MAP2_Pos)             /*!< 0x00004000 */

#define SYSCFG_CFGR3_DMA1_MAP3_Pos                 (16U)
#define SYSCFG_CFGR3_DMA1_MAP3_Msk                 (0x7FUL << SYSCFG_CFGR3_DMA1_MAP3_Pos)             /*!< 0x007F0000 */
#define SYSCFG_CFGR3_DMA1_MAP3                     SYSCFG_CFGR3_DMA1_MAP3_Msk                         /*!< DMA1 ch3 mapping */
#define SYSCFG_CFGR3_DMA1_MAP3_0                   (0x1UL << SYSCFG_CFGR3_DMA1_MAP3_Pos)              /*!< 0x00010000 */
#define SYSCFG_CFGR3_DMA1_MAP3_1                   (0x2UL << SYSCFG_CFGR3_DMA1_MAP3_Pos)              /*!< 0x00020000 */
#define SYSCFG_CFGR3_DMA1_MAP3_2                   (0x4UL << SYSCFG_CFGR3_DMA1_MAP3_Pos)              /*!< 0x00040000 */
#define SYSCFG_CFGR3_DMA1_MAP3_3                   (0x8UL << SYSCFG_CFGR3_DMA1_MAP3_Pos)              /*!< 0x00080000 */
#define SYSCFG_CFGR3_DMA1_MAP3_4                   (0x10UL << SYSCFG_CFGR3_DMA1_MAP3_Pos)             /*!< 0x00100000 */
#define SYSCFG_CFGR3_DMA1_MAP3_5                   (0x20UL << SYSCFG_CFGR3_DMA1_MAP3_Pos)             /*!< 0x00200000 */
#define SYSCFG_CFGR3_DMA1_MAP3_6                   (0x40UL << SYSCFG_CFGR3_DMA1_MAP3_Pos)             /*!< 0x00400000 */

#define SYSCFG_CFGR3_DMA1_MAP4_Pos                 (24U)
#define SYSCFG_CFGR3_DMA1_MAP4_Msk                 (0x7FUL << SYSCFG_CFGR3_DMA1_MAP4_Pos)             /*!< 0x7F000000 */
#define SYSCFG_CFGR3_DMA1_MAP4                     SYSCFG_CFGR3_DMA1_MAP4_Msk                         /*!< DMA1 ch4 mapping */
#define SYSCFG_CFGR3_DMA1_MAP4_0                   (0x1UL << SYSCFG_CFGR3_DMA1_MAP4_Pos)              /*!< 0x01000000 */
#define SYSCFG_CFGR3_DMA1_MAP4_1                   (0x2UL << SYSCFG_CFGR3_DMA1_MAP4_Pos)              /*!< 0x02000000 */
#define SYSCFG_CFGR3_DMA1_MAP4_2                   (0x4UL << SYSCFG_CFGR3_DMA1_MAP4_Pos)              /*!< 0x04000000 */
#define SYSCFG_CFGR3_DMA1_MAP4_3                   (0x8UL << SYSCFG_CFGR3_DMA1_MAP4_Pos)              /*!< 0x08000000 */
#define SYSCFG_CFGR3_DMA1_MAP4_4                   (0x10UL << SYSCFG_CFGR3_DMA1_MAP4_Pos)             /*!< 0x10000000 */
#define SYSCFG_CFGR3_DMA1_MAP4_5                   (0x20UL << SYSCFG_CFGR3_DMA1_MAP4_Pos)             /*!< 0x20000000 */
#define SYSCFG_CFGR3_DMA1_MAP4_6                   (0x40UL << SYSCFG_CFGR3_DMA1_MAP4_Pos)             /*!< 0x40000000 */

/********************************* Bit definition for SYSCFG_CFGR4 register *****************************************/
#define SYSCFG_CFGR4_DMA1_MAP5_Pos                 (0U)
#define SYSCFG_CFGR4_DMA1_MAP5_Msk                 (0x7FUL << SYSCFG_CFGR4_DMA1_MAP5_Pos)             /*!< 0x0000007F */
#define SYSCFG_CFGR4_DMA1_MAP5                     SYSCFG_CFGR4_DMA1_MAP5_Msk                         /*!< DMA1 ch5 mapping */
#define SYSCFG_CFGR4_DMA1_MAP5_0                   (0x1UL << SYSCFG_CFGR4_DMA1_MAP5_Pos)              /*!< 0x00000001 */
#define SYSCFG_CFGR4_DMA1_MAP5_1                   (0x2UL << SYSCFG_CFGR4_DMA1_MAP5_Pos)              /*!< 0x00000002 */
#define SYSCFG_CFGR4_DMA1_MAP5_2                   (0x4UL << SYSCFG_CFGR4_DMA1_MAP5_Pos)              /*!< 0x00000004 */
#define SYSCFG_CFGR4_DMA1_MAP5_3                   (0x8UL << SYSCFG_CFGR4_DMA1_MAP5_Pos)              /*!< 0x00000008 */
#define SYSCFG_CFGR4_DMA1_MAP5_4                   (0x10UL << SYSCFG_CFGR4_DMA1_MAP5_Pos)             /*!< 0x00000010 */
#define SYSCFG_CFGR4_DMA1_MAP5_5                   (0x20UL << SYSCFG_CFGR4_DMA1_MAP5_Pos)             /*!< 0x00000020 */
#define SYSCFG_CFGR4_DMA1_MAP5_6                   (0x40UL << SYSCFG_CFGR4_DMA1_MAP5_Pos)             /*!< 0x00000040 */

#define SYSCFG_CFGR4_DMA1_MAP6_Pos                 (8U)
#define SYSCFG_CFGR4_DMA1_MAP6_Msk                 (0x7FUL << SYSCFG_CFGR4_DMA1_MAP6_Pos)             /*!< 0x00007F00 */
#define SYSCFG_CFGR4_DMA1_MAP6                     SYSCFG_CFGR4_DMA1_MAP6_Msk                         /*!< DMA1 ch6 mapping */
#define SYSCFG_CFGR4_DMA1_MAP6_0                   (0x1UL << SYSCFG_CFGR4_DMA1_MAP6_Pos)              /*!< 0x00000100 */
#define SYSCFG_CFGR4_DMA1_MAP6_1                   (0x2UL << SYSCFG_CFGR4_DMA1_MAP6_Pos)              /*!< 0x00000200 */
#define SYSCFG_CFGR4_DMA1_MAP6_2                   (0x4UL << SYSCFG_CFGR4_DMA1_MAP6_Pos)              /*!< 0x00000400 */
#define SYSCFG_CFGR4_DMA1_MAP6_3                   (0x8UL << SYSCFG_CFGR4_DMA1_MAP6_Pos)              /*!< 0x00000800 */
#define SYSCFG_CFGR4_DMA1_MAP6_4                   (0x10UL << SYSCFG_CFGR4_DMA1_MAP6_Pos)             /*!< 0x00001000 */
#define SYSCFG_CFGR4_DMA1_MAP6_5                   (0x20UL << SYSCFG_CFGR4_DMA1_MAP6_Pos)             /*!< 0x00002000 */
#define SYSCFG_CFGR4_DMA1_MAP6_6                   (0x40UL << SYSCFG_CFGR4_DMA1_MAP6_Pos)             /*!< 0x00004000 */

#define SYSCFG_CFGR4_DMA1_MAP7_Pos                 (16U)
#define SYSCFG_CFGR4_DMA1_MAP7_Msk                 (0x7FUL << SYSCFG_CFGR4_DMA1_MAP7_Pos)             /*!< 0x007F0000 */
#define SYSCFG_CFGR4_DMA1_MAP7                     SYSCFG_CFGR4_DMA1_MAP7_Msk                         /*!< DMA1 ch7 mapping */
#define SYSCFG_CFGR4_DMA1_MAP7_0                   (0x1UL << SYSCFG_CFGR4_DMA1_MAP7_Pos)              /*!< 0x00010000 */
#define SYSCFG_CFGR4_DMA1_MAP7_1                   (0x2UL << SYSCFG_CFGR4_DMA1_MAP7_Pos)              /*!< 0x00020000 */
#define SYSCFG_CFGR4_DMA1_MAP7_2                   (0x4UL << SYSCFG_CFGR4_DMA1_MAP7_Pos)              /*!< 0x00040000 */
#define SYSCFG_CFGR4_DMA1_MAP7_3                   (0x8UL << SYSCFG_CFGR4_DMA1_MAP7_Pos)              /*!< 0x00080000 */
#define SYSCFG_CFGR4_DMA1_MAP7_4                   (0x10UL << SYSCFG_CFGR4_DMA1_MAP7_Pos)             /*!< 0x00100000 */
#define SYSCFG_CFGR4_DMA1_MAP7_5                   (0x20UL << SYSCFG_CFGR4_DMA1_MAP7_Pos)             /*!< 0x00200000 */
#define SYSCFG_CFGR4_DMA1_MAP7_6                   (0x40UL << SYSCFG_CFGR4_DMA1_MAP7_Pos)             /*!< 0x00400000 */

#define SYSCFG_CFGR4_DMA1_MAP8_Pos                 (24U)
#define SYSCFG_CFGR4_DMA1_MAP8_Msk                 (0x7FUL << SYSCFG_CFGR4_DMA1_MAP8_Pos)             /*!< 0x7F000000 */
#define SYSCFG_CFGR4_DMA1_MAP8                     SYSCFG_CFGR4_DMA1_MAP8_Msk                         /*!< DMA1 ch8 mapping */
#define SYSCFG_CFGR4_DMA1_MAP8_0                   (0x1UL << SYSCFG_CFGR4_DMA1_MAP8_Pos)              /*!< 0x01000000 */
#define SYSCFG_CFGR4_DMA1_MAP8_1                   (0x2UL << SYSCFG_CFGR4_DMA1_MAP8_Pos)              /*!< 0x02000000 */
#define SYSCFG_CFGR4_DMA1_MAP8_2                   (0x4UL << SYSCFG_CFGR4_DMA1_MAP8_Pos)              /*!< 0x04000000 */
#define SYSCFG_CFGR4_DMA1_MAP8_3                   (0x8UL << SYSCFG_CFGR4_DMA1_MAP8_Pos)              /*!< 0x08000000 */
#define SYSCFG_CFGR4_DMA1_MAP8_4                   (0x10UL << SYSCFG_CFGR4_DMA1_MAP8_Pos)             /*!< 0x10000000 */
#define SYSCFG_CFGR4_DMA1_MAP8_5                   (0x20UL << SYSCFG_CFGR4_DMA1_MAP8_Pos)             /*!< 0x20000000 */
#define SYSCFG_CFGR4_DMA1_MAP8_6                   (0x40UL << SYSCFG_CFGR4_DMA1_MAP8_Pos)             /*!< 0x40000000 */

/********************************* Bit definition for SYSCFG_EXTICR1 register ***************************************/
#define SYSCFG_EXTICR1_EXTI0_Pos                  (0U)
#define SYSCFG_EXTICR1_EXTI0_Msk                  (0x3UL<<SYSCFG_EXTICR1_EXTI0_Pos)                 /*!< 0x00000003 */
#define SYSCFG_EXTICR1_EXTI0                      SYSCFG_EXTICR1_EXTI0_Msk
#define SYSCFG_EXTICR1_EXTI0_0                    (0x1UL<<SYSCFG_EXTICR1_EXTI0_Pos)                 /*!< 0x00000001 */
#define SYSCFG_EXTICR1_EXTI0_1                    (0x2UL<<SYSCFG_EXTICR1_EXTI0_Pos)                 /*!< 0x00000002 */
#define SYSCFG_EXTICR1_EXTI1_Pos                  (4U)
#define SYSCFG_EXTICR1_EXTI1_Msk                  (0x3UL<<SYSCFG_EXTICR1_EXTI1_Pos)                 /*!< 0x00000030 */
#define SYSCFG_EXTICR1_EXTI1                      SYSCFG_EXTICR1_EXTI1_Msk
#define SYSCFG_EXTICR1_EXTI1_0                    (0x1UL<<SYSCFG_EXTICR1_EXTI1_Pos)                 /*!< 0x00000010 */
#define SYSCFG_EXTICR1_EXTI1_1                    (0x2UL<<SYSCFG_EXTICR1_EXTI1_Pos)                 /*!< 0x00000020 */
#define SYSCFG_EXTICR1_EXTI2_Pos                  (8U)
#define SYSCFG_EXTICR1_EXTI2_Msk                  (0x3UL<<SYSCFG_EXTICR1_EXTI2_Pos)                 /*!< 0x00000300 */
#define SYSCFG_EXTICR1_EXTI2                      SYSCFG_EXTICR1_EXTI2_Msk
#define SYSCFG_EXTICR1_EXTI2_0                    (0x1UL<<SYSCFG_EXTICR1_EXTI2_Pos)                 /*!< 0x00000100 */
#define SYSCFG_EXTICR1_EXTI2_1                    (0x2UL<<SYSCFG_EXTICR1_EXTI2_Pos)                 /*!< 0x00000200 */
#define SYSCFG_EXTICR1_EXTI3_Pos                  (12U)
#define SYSCFG_EXTICR1_EXTI3_Msk                  (0x3UL<<SYSCFG_EXTICR1_EXTI3_Pos)                 /*!< 0x00003000 */
#define SYSCFG_EXTICR1_EXTI3                      SYSCFG_EXTICR1_EXTI3_Msk                          /*!< EXTI 0~3 configuration */
#define SYSCFG_EXTICR1_EXTI3_0                    (0x1UL<<SYSCFG_EXTICR1_EXTI3_Pos)                 /*!< 0x00001000 */
#define SYSCFG_EXTICR1_EXTI3_1                    (0x2UL<<SYSCFG_EXTICR1_EXTI3_Pos)                 /*!< 0x00002000 */

/********************************* Bit definition for SYSCFG_EXTICR2 register ***************************************/
#define SYSCFG_EXTICR2_EXTI4_Pos                  (0U)
#define SYSCFG_EXTICR2_EXTI4_Msk                  (0x3UL<<SYSCFG_EXTICR2_EXTI4_Pos)                 /*!< 0x00000003 */
#define SYSCFG_EXTICR2_EXTI4                      SYSCFG_EXTICR2_EXTI4_Msk
#define SYSCFG_EXTICR2_EXTI4_0                    (0x1UL<<SYSCFG_EXTICR2_EXTI4_Pos)                 /*!< 0x00000001 */
#define SYSCFG_EXTICR2_EXTI4_1                    (0x2UL<<SYSCFG_EXTICR2_EXTI4_Pos)                 /*!< 0x00000002 */
#define SYSCFG_EXTICR2_EXTI5_Pos                  (4U)
#define SYSCFG_EXTICR2_EXTI5_Msk                  (0x3UL<<SYSCFG_EXTICR2_EXTI5_Pos)                 /*!< 0x00000030 */
#define SYSCFG_EXTICR2_EXTI5                      SYSCFG_EXTICR2_EXTI5_Msk
#define SYSCFG_EXTICR2_EXTI5_0                    (0x1UL<<SYSCFG_EXTICR2_EXTI5_Pos)                 /*!< 0x00000010 */
#define SYSCFG_EXTICR2_EXTI5_1                    (0x2UL<<SYSCFG_EXTICR2_EXTI5_Pos)                 /*!< 0x00000020 */
#define SYSCFG_EXTICR2_EXTI6_Pos                  (8U)
#define SYSCFG_EXTICR2_EXTI6_Msk                  (0x3UL<<SYSCFG_EXTICR2_EXTI6_Pos)                 /*!< 0x00000300 */
#define SYSCFG_EXTICR2_EXTI6                      SYSCFG_EXTICR2_EXTI6_Msk
#define SYSCFG_EXTICR2_EXTI6_0                    (0x1UL<<SYSCFG_EXTICR2_EXTI6_Pos)                 /*!< 0x00000100 */
#define SYSCFG_EXTICR2_EXTI6_1                    (0x2UL<<SYSCFG_EXTICR2_EXTI6_Pos)                 /*!< 0x00000200 */
#define SYSCFG_EXTICR2_EXTI7_Pos                  (12U)
#define SYSCFG_EXTICR2_EXTI7_Msk                  (0x3UL<<SYSCFG_EXTICR2_EXTI7_Pos)                 /*!< 0x00003000 */
#define SYSCFG_EXTICR2_EXTI7                      SYSCFG_EXTICR2_EXTI7_Msk                          /*!< EXTI 4~7 configuration */
#define SYSCFG_EXTICR2_EXTI7_0                    (0x1UL<<SYSCFG_EXTICR2_EXTI7_Pos)                 /*!< 0x00001000 */
#define SYSCFG_EXTICR2_EXTI7_1                    (0x2UL<<SYSCFG_EXTICR2_EXTI7_Pos)                 /*!< 0x00002000 */

/********************************* Bit definition for SYSCFG_EXTICR3 register ***************************************/
#define SYSCFG_EXTICR3_EXTI8_Pos                  (0U)
#define SYSCFG_EXTICR3_EXTI8_Msk                  (0x3UL<<SYSCFG_EXTICR3_EXTI8_Pos)                 /*!< 0x00000003 */
#define SYSCFG_EXTICR3_EXTI8                      SYSCFG_EXTICR3_EXTI8_Msk
#define SYSCFG_EXTICR3_EXTI8_0                    (0x1UL<<SYSCFG_EXTICR3_EXTI8_Pos)                 /*!< 0x00000001 */
#define SYSCFG_EXTICR3_EXTI8_1                    (0x2UL<<SYSCFG_EXTICR3_EXTI8_Pos)                 /*!< 0x00000002 */
#define SYSCFG_EXTICR3_EXTI9_Pos                  (4U)
#define SYSCFG_EXTICR3_EXTI9_Msk                  (0x3UL<<SYSCFG_EXTICR3_EXTI9_Pos)                 /*!< 0x00000030 */
#define SYSCFG_EXTICR3_EXTI9                      SYSCFG_EXTICR3_EXTI9_Msk
#define SYSCFG_EXTICR3_EXTI9_0                    (0x1UL<<SYSCFG_EXTICR3_EXTI9_Pos)                 /*!< 0x00000010 */
#define SYSCFG_EXTICR3_EXTI9_1                    (0x2UL<<SYSCFG_EXTICR3_EXTI9_Pos)                 /*!< 0x00000020 */
#define SYSCFG_EXTICR3_EXTI10_Pos                 (8U)
#define SYSCFG_EXTICR3_EXTI10_Msk                 (0x3UL<<SYSCFG_EXTICR3_EXTI10_Pos)                /*!< 0x00000300 */
#define SYSCFG_EXTICR3_EXTI10                     SYSCFG_EXTICR3_EXTI10_Msk
#define SYSCFG_EXTICR3_EXTI10_0                   (0x1UL<<SYSCFG_EXTICR3_EXTI10_Pos)                /*!< 0x00000100 */
#define SYSCFG_EXTICR3_EXTI10_1                   (0x2UL<<SYSCFG_EXTICR3_EXTI10_Pos)                /*!< 0x00000200 */
#define SYSCFG_EXTICR3_EXTI11_Pos                 (12U)
#define SYSCFG_EXTICR3_EXTI11_Msk                 (0x3UL<<SYSCFG_EXTICR3_EXTI11_Pos)                /*!< 0x00003000 */
#define SYSCFG_EXTICR3_EXTI11                     SYSCFG_EXTICR3_EXTI11_Msk                         /*!< EXTI 8~11 configuration */
#define SYSCFG_EXTICR3_EXTI11_0                   (0x1UL<<SYSCFG_EXTICR3_EXTI11_Pos)                /*!< 0x00001000 */
#define SYSCFG_EXTICR3_EXTI11_1                   (0x2UL<<SYSCFG_EXTICR3_EXTI11_Pos)                /*!< 0x00002000 */

/********************************* Bit definition for SYSCFG_EXTICR4 register ***************************************/
#define SYSCFG_EXTICR4_EXTI12_Pos                 (0U)
#define SYSCFG_EXTICR4_EXTI12_Msk                 (0x3UL<<SYSCFG_EXTICR4_EXTI12_Pos)                /*!< 0x00000003 */
#define SYSCFG_EXTICR4_EXTI12                     SYSCFG_EXTICR4_EXTI12_Msk
#define SYSCFG_EXTICR4_EXTI12_0                   (0x1UL<<SYSCFG_EXTICR4_EXTI12_Pos)                /*!< 0x00000001 */
#define SYSCFG_EXTICR4_EXTI12_1                   (0x2UL<<SYSCFG_EXTICR4_EXTI12_Pos)                /*!< 0x00000002 */
#define SYSCFG_EXTICR4_EXTI13_Pos                 (4U)
#define SYSCFG_EXTICR4_EXTI13_Msk                 (0x3UL<<SYSCFG_EXTICR4_EXTI13_Pos)                /*!< 0x00000030 */
#define SYSCFG_EXTICR4_EXTI13                     SYSCFG_EXTICR4_EXTI13_Msk
#define SYSCFG_EXTICR4_EXTI13_0                   (0x1UL<<SYSCFG_EXTICR4_EXTI13_Pos)                /*!< 0x00000010 */
#define SYSCFG_EXTICR4_EXTI13_1                   (0x2UL<<SYSCFG_EXTICR4_EXTI13_Pos)                /*!< 0x00000020 */
#define SYSCFG_EXTICR4_EXTI14_Pos                 (8U)
#define SYSCFG_EXTICR4_EXTI14_Msk                 (0x3UL<<SYSCFG_EXTICR4_EXTI14_Pos)                /*!< 0x00000300 */
#define SYSCFG_EXTICR4_EXTI14                     SYSCFG_EXTICR4_EXTI14_Msk
#define SYSCFG_EXTICR4_EXTI14_0                   (0x1UL<<SYSCFG_EXTICR4_EXTI14_Pos)                /*!< 0x00000100 */
#define SYSCFG_EXTICR4_EXTI14_1                   (0x2UL<<SYSCFG_EXTICR4_EXTI14_Pos)                /*!< 0x00000200 */
#define SYSCFG_EXTICR4_EXTI15_Pos                 (12U)
#define SYSCFG_EXTICR4_EXTI15_Msk                 (0x3UL<<SYSCFG_EXTICR4_EXTI15_Pos)                /*!< 0x00003000 */
#define SYSCFG_EXTICR4_EXTI15                     SYSCFG_EXTICR4_EXTI15_Msk                         /*!< EXTI 12~15 configuration */
#define SYSCFG_EXTICR4_EXTI15_0                   (0x1UL<<SYSCFG_EXTICR4_EXTI15_Pos)                /*!< 0x00001000 */
#define SYSCFG_EXTICR4_EXTI15_1                   (0x2UL<<SYSCFG_EXTICR4_EXTI15_Pos)                /*!< 0x00002000 */

/********************************* Bit definition for PA_ENS register ***********************************************/
#define SYSCFG_PAENS_PA_ENS_Pos                         (0U)
#define SYSCFG_PAENS_PA_ENS_Msk                         (0xFFFFUL<<SYSCFG_PAENS_PA_ENS_Pos)                     /*!< 0x0000FFFF */
#define SYSCFG_PAENS_PA_ENS                             SYSCFG_PAENS_PA_ENS_Msk                                 /*!< GPIOA noise filter enable */

/********************************* Bit definition for PB_ENS register ***********************************************/
#define SYSCFG_PBENS_PB_ENS_Pos                         (0U)
#define SYSCFG_PBENS_PB_ENS_Msk                         (0xFFFFUL<<SYSCFG_PBENS_PB_ENS_Pos)                     /*!< 0x0000FFFF */
#define SYSCFG_PBENS_PB_ENS                             SYSCFG_PBENS_PB_ENS_Msk                                 /*!< GPIOB noise filter enable */

/********************************* Bit definition for PC_ENS register ***********************************************/
#define SYSCFG_PCENS_PC_ENS_Pos                         (0U)
#define SYSCFG_PCENS_PC_ENS_Msk                         (0xFFFFUL<<SYSCFG_PCENS_PC_ENS_Pos)                     /*!< 0x0000FFFF */
#define SYSCFG_PCENS_PC_ENS                             SYSCFG_PCENS_PC_ENS_Msk                                 /*!< GPIOC noise filter enable */

/********************************* Bit definition for PD_ENS register ***********************************************/
#define SYSCFG_PDENS_PD_ENS_Pos                         (0U)
#define SYSCFG_PDENS_PD_ENS_Msk                         (0xFFFUL<<SYSCFG_PDENS_PD_ENS_Pos)                      /*!< 0x00000FFF */
#define SYSCFG_PDENS_PD_ENS                             SYSCFG_PDENS_PD_ENS_Msk                                 /*!< GPIOD noise filter enable */

/********************************* Bit definition for COMP_ANA2ENR register *****************************************/
#define SYSCFG_COMP_ANA2ENR_PA0_ENA2_Pos                (0U)
#define SYSCFG_COMP_ANA2ENR_PA0_ENA2_Msk                (0x1UL<<SYSCFG_COMP_ANA2ENR_PA0_ENA2_Pos)                  /*!< 0x00000001 */
#define SYSCFG_COMP_ANA2ENR_PA0_ENA2                    SYSCFG_COMP_ANA2ENR_PA0_ENA2_Msk                           /*!< GPIOA0 ANA2 enable */
#define SYSCFG_COMP_ANA2ENR_PA1_ENA2_Pos                (1U)
#define SYSCFG_COMP_ANA2ENR_PA1_ENA2_Msk                (0x1UL<<SYSCFG_COMP_ANA2ENR_PA1_ENA2_Pos)                  /*!< 0x00000002 */
#define SYSCFG_COMP_ANA2ENR_PA1_ENA2                    SYSCFG_COMP_ANA2ENR_PA1_ENA2_Msk                           /*!< GPIOA1 ANA2 enable */
#define SYSCFG_COMP_ANA2ENR_PA2_ENA2_Pos                (2U)
#define SYSCFG_COMP_ANA2ENR_PA2_ENA2_Msk                (0x1UL<<SYSCFG_COMP_ANA2ENR_PA2_ENA2_Pos)                  /*!< 0x00000004 */
#define SYSCFG_COMP_ANA2ENR_PA2_ENA2                    SYSCFG_COMP_ANA2ENR_PA2_ENA2_Msk                           /*!< GPIOA2 ANA2 enable */
#define SYSCFG_COMP_ANA2ENR_PA3_ENA2_Pos                (3U)
#define SYSCFG_COMP_ANA2ENR_PA3_ENA2_Msk                (0x1UL<<SYSCFG_COMP_ANA2ENR_PA3_ENA2_Pos)                  /*!< 0x00000008 */
#define SYSCFG_COMP_ANA2ENR_PA3_ENA2                    SYSCFG_COMP_ANA2ENR_PA3_ENA2_Msk                           /*!< GPIOA3 ANA2 enable */
#define SYSCFG_COMP_ANA2ENR_PA4_ENA2_Pos                (4U)
#define SYSCFG_COMP_ANA2ENR_PA4_ENA2_Msk                (0x1UL<<SYSCFG_COMP_ANA2ENR_PA4_ENA2_Pos)                  /*!< 0x00000010 */
#define SYSCFG_COMP_ANA2ENR_PA4_ENA2                    SYSCFG_COMP_ANA2ENR_PA4_ENA2_Msk                           /*!< GPIOA4 ANA2 enable */
#define SYSCFG_COMP_ANA2ENR_PA5_ENA2_Pos                (5U)
#define SYSCFG_COMP_ANA2ENR_PA5_ENA2_Msk                (0x1UL<<SYSCFG_COMP_ANA2ENR_PA5_ENA2_Pos)                  /*!< 0x00000020 */
#define SYSCFG_COMP_ANA2ENR_PA5_ENA2                    SYSCFG_COMP_ANA2ENR_PA5_ENA2_Msk                           /*!< GPIOA5 ANA2 enable */
#define SYSCFG_COMP_ANA2ENR_PA9_ENA2_Pos                (9U)
#define SYSCFG_COMP_ANA2ENR_PA9_ENA2_Msk                (0x1UL<<SYSCFG_COMP_ANA2ENR_PA9_ENA2_Pos)                  /*!< 0x00000200 */
#define SYSCFG_COMP_ANA2ENR_PA9_ENA2                    SYSCFG_COMP_ANA2ENR_PA9_ENA2_Msk                           /*!< GPIOA9 ANA2 enable */
#define SYSCFG_COMP_ANA2ENR_PB1_ENA2_Pos                (17U)
#define SYSCFG_COMP_ANA2ENR_PB1_ENA2_Msk                (0x1UL<<SYSCFG_COMP_ANA2ENR_PB1_ENA2_Pos)                  /*!< 0x00002000 */
#define SYSCFG_COMP_ANA2ENR_PB1_ENA2                    SYSCFG_COMP_ANA2ENR_PB1_ENA2_Msk                           /*!< GPIOB1 ANA2 enable */

/********************************************************************************************************************/
/********************************* TIM1 *****************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for TIM_CR1 register *********************************************/
#define TIM_CR1_CEN_Pos                          (0U)
#define TIM_CR1_CEN_Msk                          (0x1UL << TIM_CR1_CEN_Pos)                    /*!< 0x00000001 */
#define TIM_CR1_CEN                              TIM_CR1_CEN_Msk                               /*!<Counter enable */
#define TIM_CR1_UDIS_Pos                         (1U)
#define TIM_CR1_UDIS_Msk                         (0x1UL << TIM_CR1_UDIS_Pos)                   /*!< 0x00000002 */
#define TIM_CR1_UDIS                             TIM_CR1_UDIS_Msk                              /*!<Update disable */
#define TIM_CR1_URS_Pos                          (2U)
#define TIM_CR1_URS_Msk                          (0x1UL << TIM_CR1_URS_Pos)                    /*!< 0x00000004 */
#define TIM_CR1_URS                              TIM_CR1_URS_Msk                               /*!<Update request source */
#define TIM_CR1_OPM_Pos                          (3U)
#define TIM_CR1_OPM_Msk                          (0x1UL << TIM_CR1_OPM_Pos)                    /*!< 0x00000008 */
#define TIM_CR1_OPM                              TIM_CR1_OPM_Msk                               /*!<One pulse mode */
#define TIM_CR1_DIR_Pos                          (4U)
#define TIM_CR1_DIR_Msk                          (0x1UL << TIM_CR1_DIR_Pos)                    /*!< 0x00000010 */
#define TIM_CR1_DIR                              TIM_CR1_DIR_Msk                               /*!<Direction */
#define TIM_CR1_CMS_Pos                          (5U)
#define TIM_CR1_CMS_Msk                          (0x3UL << TIM_CR1_CMS_Pos)                    /*!< 0x00000060 */
#define TIM_CR1_CMS                              TIM_CR1_CMS_Msk                               /*!<CMS[1:0] bits (Center-aligned mode selection) */
#define TIM_CR1_CMS_0                            (0x1UL << TIM_CR1_CMS_Pos)                    /*!< 0x00000020 */
#define TIM_CR1_CMS_1                            (0x2UL << TIM_CR1_CMS_Pos)                    /*!< 0x00000040 */
#define TIM_CR1_ARPE_Pos                         (7U)
#define TIM_CR1_ARPE_Msk                         (0x1UL << TIM_CR1_ARPE_Pos)                   /*!< 0x00000080 */
#define TIM_CR1_ARPE                             TIM_CR1_ARPE_Msk                              /*!<Auto-reload preload enable */
#define TIM_CR1_CKD_Pos                          (8U)
#define TIM_CR1_CKD_Msk                          (0x3UL << TIM_CR1_CKD_Pos)                    /*!< 0x00000300 */
#define TIM_CR1_CKD                              TIM_CR1_CKD_Msk                               /*!<CKD[1:0] bits (clock division) */
#define TIM_CR1_CKD_0                            (0x1UL << TIM_CR1_CKD_Pos)                    /*!< 0x00000100 */
#define TIM_CR1_CKD_1                            (0x2UL << TIM_CR1_CKD_Pos)                    /*!< 0x00000200 */

/********************************* Bit definition for TIM_CR2 register *********************************************/
#define TIM_CR2_CCPC_Pos                         (0U)
#define TIM_CR2_CCPC_Msk                         (0x1UL << TIM_CR2_CCPC_Pos)                   /*!< 0x00000001 */
#define TIM_CR2_CCPC                             TIM_CR2_CCPC_Msk                              /*!<Capture/Compare Preloaded Control */
#define TIM_CR2_CCUS_Pos                         (2U)
#define TIM_CR2_CCUS_Msk                         (0x1UL << TIM_CR2_CCUS_Pos)                   /*!< 0x00000004 */
#define TIM_CR2_CCUS                             TIM_CR2_CCUS_Msk                              /*!<Capture/Compare Control Update Selection */
#define TIM_CR2_CCDS_Pos                         (3U)
#define TIM_CR2_CCDS_Msk                         (0x1UL << TIM_CR2_CCDS_Pos)                   /*!< 0x00000008 */
#define TIM_CR2_CCDS                             TIM_CR2_CCDS_Msk                              /*!<Capture/Compare DMA Selection */
#define TIM_CR2_MMS_Pos                          (4U)
#define TIM_CR2_MMS_Msk                          (0x200007UL << TIM_CR2_MMS_Pos)               /*!< 0x02000070 */
#define TIM_CR2_MMS                              TIM_CR2_MMS_Msk
#define TIM_CR2_MMS_0                            (0x000001UL << TIM_CR2_MMS_Pos)               /*!< 0x00000010 */
#define TIM_CR2_MMS_1                            (0x000002UL << TIM_CR2_MMS_Pos)               /*!< 0x00000020 */
#define TIM_CR2_MMS_2                            (0x000004UL << TIM_CR2_MMS_Pos)               /*!< 0x00000040 */
#define TIM_CR2_MMS_3                            (0x200000UL << TIM_CR2_MMS_Pos)               /*!< 0x02000000 */
#define TIM_CR2_TI1S_Pos                         (7U)
#define TIM_CR2_TI1S_Msk                         (0x1UL << TIM_CR2_TI1S_Pos)                   /*!< 0x00000080 */
#define TIM_CR2_TI1S                             TIM_CR2_TI1S_Msk                              /*!<TI1 Selection */
#define TIM_CR2_OIS1_Pos                         (8U)
#define TIM_CR2_OIS1_Msk                         (0x1UL << TIM_CR2_OIS1_Pos)                   /*!< 0x00000100 */
#define TIM_CR2_OIS1                             TIM_CR2_OIS1_Msk                              /*!<Output Idle state 1 (OC1 output) */
#define TIM_CR2_OIS1N_Pos                        (9U)
#define TIM_CR2_OIS1N_Msk                        (0x1UL << TIM_CR2_OIS1N_Pos)                  /*!< 0x00000200 */
#define TIM_CR2_OIS1N                            TIM_CR2_OIS1N_Msk                             /*!<Output Idle state 1 (OC1N output) */
#define TIM_CR2_OIS2_Pos                         (10U)
#define TIM_CR2_OIS2_Msk                         (0x1UL << TIM_CR2_OIS2_Pos)                   /*!< 0x00000400 */
#define TIM_CR2_OIS2                             TIM_CR2_OIS2_Msk                              /*!<Output Idle state 2 (OC2 output) */
#define TIM_CR2_OIS2N_Pos                        (11U)
#define TIM_CR2_OIS2N_Msk                        (0x1UL << TIM_CR2_OIS2N_Pos)                  /*!< 0x00000800 */
#define TIM_CR2_OIS2N                            TIM_CR2_OIS2N_Msk                             /*!<Output Idle state 2 (OC2N output) */
#define TIM_CR2_OIS3_Pos                         (12U)
#define TIM_CR2_OIS3_Msk                         (0x1UL << TIM_CR2_OIS3_Pos)                   /*!< 0x00001000 */
#define TIM_CR2_OIS3                             TIM_CR2_OIS3_Msk                              /*!<Output Idle state 3 (OC3 output) */
#define TIM_CR2_OIS3N_Pos                        (13U)
#define TIM_CR2_OIS3N_Msk                        (0x1UL << TIM_CR2_OIS3N_Pos)                  /*!< 0x00002000 */
#define TIM_CR2_OIS3N                            TIM_CR2_OIS3N_Msk                             /*!<Output Idle state 3 (OC3N output) */
#define TIM_CR2_OIS4_Pos                         (14U)
#define TIM_CR2_OIS4_Msk                         (0x1UL << TIM_CR2_OIS4_Pos)                   /*!< 0x00004000 */
#define TIM_CR2_OIS4                             TIM_CR2_OIS4_Msk                              /*!<Output Idle state 4 (OC4 output) */
#define TIM_CR2_OIS5_Pos                         (16U)
#define TIM_CR2_OIS5_Msk                         (0x1UL << TIM_CR2_OIS5_Pos)                   /*!< 0x00010000 */
#define TIM_CR2_OIS5                             TIM_CR2_OIS5_Msk                              /*!<Output Idle state 4 (OC5 output) */
#define TIM_CR2_OIS6_Pos                         (18U)
#define TIM_CR2_OIS6_Msk                         (0x1UL << TIM_CR2_OIS6_Pos)                   /*!< 0x00020000 */
#define TIM_CR2_OIS6                             TIM_CR2_OIS6_Msk                              /*!<Output Idle state 4 (OC6 output) */

/********************************* Bit definition for TIM_SMCR register ********************************************/
#define TIM_SMCR_SMS_Pos                         (0U)
#define TIM_SMCR_SMS_Msk                         (0x00010007UL<<TIM_SMCR_SMS_Pos)                 /*!< 0x00010007 */
#define TIM_SMCR_SMS                             TIM_SMCR_SMS_Msk
#define TIM_SMCR_SMS_0                           (0x1UL<<TIM_SMCR_SMS_Pos)                        /*!< 0x00000001 */
#define TIM_SMCR_SMS_1                           (0x2UL<<TIM_SMCR_SMS_Pos)                        /*!< 0x00000002 */
#define TIM_SMCR_SMS_2                           (0x4UL<<TIM_SMCR_SMS_Pos)                        /*!< 0x00000004 */
#define TIM_SMCR_SMS_3                           (0x10000UL<<TIM_SMCR_SMS_Pos)                    /*!< 0x00010000 */
#define TIM_SMCR_OCCS_Pos                        (3U)
#define TIM_SMCR_OCCS_Msk                        (0x1UL<<TIM_SMCR_OCCS_Pos)                       /*!< 0x00000008 */
#define TIM_SMCR_OCCS                            TIM_SMCR_OCCS_Msk                                
#define TIM_SMCR_TS_Pos                          (4U)
#define TIM_SMCR_TS_Msk                          (0x30007UL<<TIM_SMCR_TS_Pos)                     /*!< 0x00300070 */
#define TIM_SMCR_TS                              TIM_SMCR_TS_Msk
#define TIM_SMCR_TS_0                            (0x1UL<<TIM_SMCR_TS_Pos)                         /*!< 0x00000010 */
#define TIM_SMCR_TS_1                            (0x2UL<<TIM_SMCR_TS_Pos)                         /*!< 0x00000020 */
#define TIM_SMCR_TS_2                            (0x4UL<<TIM_SMCR_TS_Pos)                         /*!< 0x00000040 */
#define TIM_SMCR_TS_3                            (0x10000UL<<TIM_SMCR_TS_Pos)                     /*!< 0x00100000 */
#define TIM_SMCR_TS_4                            (0x20000UL<<TIM_SMCR_TS_Pos)                     /*!< 0x00200000 */
#define TIM_SMCR_MSM_Pos                         (7U)
#define TIM_SMCR_MSM_Msk                         (0x1UL<<TIM_SMCR_MSM_Pos)                        /*!< 0x00000080 */
#define TIM_SMCR_MSM                             TIM_SMCR_MSM_Msk                                 
#define TIM_SMCR_ETF_Pos                         (8U)
#define TIM_SMCR_ETF_Msk                         (0xFUL<<TIM_SMCR_ETF_Pos)                        /*!< 0x00000F00 */
#define TIM_SMCR_ETF                             TIM_SMCR_ETF_Msk
#define TIM_SMCR_ETF_0                           (0x1UL<<TIM_SMCR_ETF_Pos)                        /*!< 0x00000100 */
#define TIM_SMCR_ETF_1                           (0x2UL<<TIM_SMCR_ETF_Pos)                        /*!< 0x00000200 */
#define TIM_SMCR_ETF_2                           (0x4UL<<TIM_SMCR_ETF_Pos)                        /*!< 0x00000400 */
#define TIM_SMCR_ETF_3                           (0x8UL<<TIM_SMCR_ETF_Pos)                        /*!< 0x00000800 */
#define TIM_SMCR_ETPS_Pos                        (12U)
#define TIM_SMCR_ETPS_Msk                        (0x3UL<<TIM_SMCR_ETPS_Pos)                       /*!< 0x00003000 */
#define TIM_SMCR_ETPS                            TIM_SMCR_ETPS_Msk
#define TIM_SMCR_ETPS_0                          (0x1UL<<TIM_SMCR_ETPS_Pos)                       /*!< 0x00001000 */
#define TIM_SMCR_ETPS_1                          (0x2UL<<TIM_SMCR_ETPS_Pos)                       /*!< 0x00002000 */
#define TIM_SMCR_ECE_Pos                         (14U)
#define TIM_SMCR_ECE_Msk                         (0x1UL<<TIM_SMCR_ECE_Pos)                        /*!< 0x00004000 */
#define TIM_SMCR_ECE                             TIM_SMCR_ECE_Msk                                 
#define TIM_SMCR_ETP_Pos                         (15U)
#define TIM_SMCR_ETP_Msk                         (0x1UL<<TIM_SMCR_ETP_Pos)                        /*!< 0x00008000 */
#define TIM_SMCR_ETP                             TIM_SMCR_ETP_Msk                                

/********************************* Bit definition for TIM_DIER register ********************************************/
#define TIM_DIER_UIE_Pos                         (0U)
#define TIM_DIER_UIE_Msk                         (0x1UL << TIM_DIER_UIE_Pos)                   /*!< 0x00000001 */
#define TIM_DIER_UIE                             TIM_DIER_UIE_Msk                              /*!<Update interrupt enable */
#define TIM_DIER_CC1IE_Pos                       (1U)
#define TIM_DIER_CC1IE_Msk                       (0x1UL << TIM_DIER_CC1IE_Pos)                 /*!< 0x00000002 */
#define TIM_DIER_CC1IE                           TIM_DIER_CC1IE_Msk                            /*!<Capture/Compare 1 interrupt enable */
#define TIM_DIER_CC2IE_Pos                       (2U)
#define TIM_DIER_CC2IE_Msk                       (0x1UL << TIM_DIER_CC2IE_Pos)                 /*!< 0x00000004 */
#define TIM_DIER_CC2IE                           TIM_DIER_CC2IE_Msk                            /*!<Capture/Compare 2 interrupt enable */
#define TIM_DIER_CC3IE_Pos                       (3U)
#define TIM_DIER_CC3IE_Msk                       (0x1UL << TIM_DIER_CC3IE_Pos)                 /*!< 0x00000008 */
#define TIM_DIER_CC3IE                           TIM_DIER_CC3IE_Msk                            /*!<Capture/Compare 3 interrupt enable */
#define TIM_DIER_CC4IE_Pos                       (4U)
#define TIM_DIER_CC4IE_Msk                       (0x1UL << TIM_DIER_CC4IE_Pos)                 /*!< 0x00000010 */
#define TIM_DIER_CC4IE                           TIM_DIER_CC4IE_Msk                            /*!<Capture/Compare 4 interrupt enable */
#define TIM_DIER_COMIE_Pos                       (5U)
#define TIM_DIER_COMIE_Msk                       (0x1UL << TIM_DIER_COMIE_Pos)                 /*!< 0x00000020 */
#define TIM_DIER_COMIE                           TIM_DIER_COMIE_Msk                            /*!<COM interrupt enable */
#define TIM_DIER_TIE_Pos                         (6U)
#define TIM_DIER_TIE_Msk                         (0x1UL << TIM_DIER_TIE_Pos)                   /*!< 0x00000040 */
#define TIM_DIER_TIE                             TIM_DIER_TIE_Msk                              /*!<Trigger interrupt enable */
#define TIM_DIER_BIE_Pos                         (7U)
#define TIM_DIER_BIE_Msk                         (0x1UL << TIM_DIER_BIE_Pos)                   /*!< 0x00000080 */
#define TIM_DIER_BIE                             TIM_DIER_BIE_Msk                              /*!<Break interrupt enable */
#define TIM_DIER_UDE_Pos                         (8U)
#define TIM_DIER_UDE_Msk                         (0x1UL << TIM_DIER_UDE_Pos)                   /*!< 0x00000100 */
#define TIM_DIER_UDE                             TIM_DIER_UDE_Msk                              /*!<Update DMA request enable */
#define TIM_DIER_CC1DE_Pos                       (9U)
#define TIM_DIER_CC1DE_Msk                       (0x1UL << TIM_DIER_CC1DE_Pos)                 /*!< 0x00000200 */
#define TIM_DIER_CC1DE                           TIM_DIER_CC1DE_Msk                            /*!<Capture/Compare 1 DMA request enable */
#define TIM_DIER_CC2DE_Pos                       (10U)
#define TIM_DIER_CC2DE_Msk                       (0x1UL << TIM_DIER_CC2DE_Pos)                 /*!< 0x00000400 */
#define TIM_DIER_CC2DE                           TIM_DIER_CC2DE_Msk                            /*!<Capture/Compare 2 DMA request enable */
#define TIM_DIER_CC3DE_Pos                       (11U)
#define TIM_DIER_CC3DE_Msk                       (0x1UL << TIM_DIER_CC3DE_Pos)                 /*!< 0x00000800 */
#define TIM_DIER_CC3DE                           TIM_DIER_CC3DE_Msk                            /*!<Capture/Compare 3 DMA request enable */
#define TIM_DIER_CC4DE_Pos                       (12U)
#define TIM_DIER_CC4DE_Msk                       (0x1UL << TIM_DIER_CC4DE_Pos)                 /*!< 0x00001000 */
#define TIM_DIER_CC4DE                           TIM_DIER_CC4DE_Msk                            /*!<Capture/Compare 4 DMA request enable */
#define TIM_DIER_COMDE_Pos                       (13U)
#define TIM_DIER_COMDE_Msk                       (0x1UL << TIM_DIER_COMDE_Pos)                 /*!< 0x00002000 */
#define TIM_DIER_COMDE                           TIM_DIER_COMDE_Msk                            /*!<COM DMA request enable */
#define TIM_DIER_TDE_Pos                         (14U)
#define TIM_DIER_TDE_Msk                         (0x1UL << TIM_DIER_TDE_Pos)                   /*!< 0x00004000 */
#define TIM_DIER_TDE                             TIM_DIER_TDE_Msk                              /*!<Trigger DMA request enable */       

/********************************* Bit definition for TIM_SR register **********************************************/
#define TIM_SR_UIF_Pos                           (0U)
#define TIM_SR_UIF_Msk                           (0x1UL<<TIM_SR_UIF_Pos)                          /*!< 0x00000001 */
#define TIM_SR_UIF                               TIM_SR_UIF_Msk                                   
#define TIM_SR_CC1IF_Pos                         (1U)
#define TIM_SR_CC1IF_Msk                         (0x1UL<<TIM_SR_CC1IF_Pos)                        /*!< 0x00000002 */
#define TIM_SR_CC1IF                             TIM_SR_CC1IF_Msk                                 
#define TIM_SR_CC2IF_Pos                         (2U)
#define TIM_SR_CC2IF_Msk                         (0x1UL<<TIM_SR_CC2IF_Pos)                        /*!< 0x00000004 */
#define TIM_SR_CC2IF                             TIM_SR_CC2IF_Msk                                 
#define TIM_SR_CC3IF_Pos                         (3U)
#define TIM_SR_CC3IF_Msk                         (0x1UL<<TIM_SR_CC3IF_Pos)                        /*!< 0x00000008 */
#define TIM_SR_CC3IF                             TIM_SR_CC3IF_Msk                                 
#define TIM_SR_CC4IF_Pos                         (4U)
#define TIM_SR_CC4IF_Msk                         (0x1UL<<TIM_SR_CC4IF_Pos)                        /*!< 0x00000010 */
#define TIM_SR_CC4IF                             TIM_SR_CC4IF_Msk                                 
#define TIM_SR_COMIF_Pos                         (5U)
#define TIM_SR_COMIF_Msk                         (0x1UL<<TIM_SR_COMIF_Pos)                        /*!< 0x00000020 */
#define TIM_SR_COMIF                             TIM_SR_COMIF_Msk                                 
#define TIM_SR_TIF_Pos                           (6U)
#define TIM_SR_TIF_Msk                           (0x1UL<<TIM_SR_TIF_Pos)                          /*!< 0x00000040 */
#define TIM_SR_TIF                               TIM_SR_TIF_Msk                                   
#define TIM_SR_BIF_Pos                           (7U)
#define TIM_SR_BIF_Msk                           (0x1UL<<TIM_SR_BIF_Pos)                          /*!< 0x00000080 */
#define TIM_SR_BIF                               TIM_SR_BIF_Msk                                                                   
#define TIM_SR_CC1OF_Pos                         (9U)
#define TIM_SR_CC1OF_Msk                         (0x1UL<<TIM_SR_CC1OF_Pos)                        /*!< 0x00000200 */
#define TIM_SR_CC1OF                             TIM_SR_CC1OF_Msk                                 
#define TIM_SR_CC2OF_Pos                         (10U)
#define TIM_SR_CC2OF_Msk                         (0x1UL<<TIM_SR_CC2OF_Pos)                        /*!< 0x00000400 */
#define TIM_SR_CC2OF                             TIM_SR_CC2OF_Msk                                 
#define TIM_SR_CC3OF_Pos                         (11U)
#define TIM_SR_CC3OF_Msk                         (0x1UL<<TIM_SR_CC3OF_Pos)                        /*!< 0x00000800 */
#define TIM_SR_CC3OF                             TIM_SR_CC3OF_Msk                                 
#define TIM_SR_CC4OF_Pos                         (12U)
#define TIM_SR_CC4OF_Msk                         (0x1UL<<TIM_SR_CC4OF_Pos)                        /*!< 0x00001000 */
#define TIM_SR_CC4OF                             TIM_SR_CC4OF_Msk                                 
#define TIM_SR_SBIF_Pos                          (13U)
#define TIM_SR_SBIF_Msk                          (0x1UL<<TIM_SR_SBIF_Pos)                         /*!< 0x00002000 */
#define TIM_SR_SBIF                              TIM_SR_SBIF_Msk                      
#define TIM_SR_CC5IF_Pos                         (16U)
#define TIM_SR_CC5IF_Msk                         (0x1UL<<TIM_SR_CC5IF_Pos)                        /*!< 0x00010000 */
#define TIM_SR_CC5IF                             TIM_SR_CC5IF_Msk                                 
#define TIM_SR_CC6IF_Pos                         (17U)
#define TIM_SR_CC6IF_Msk                         (0x1UL<<TIM_SR_CC6IF_Pos)                        /*!< 0x00020000 */
#define TIM_SR_CC6IF                             TIM_SR_CC6IF_Msk    
#define TIM_SR_IC1IR_Pos                         (18U)
#define TIM_SR_IC1IR_Msk                         (0x1UL<<TIM_SR_IC1IR_Pos)                        /*!< 0x00040000 */
#define TIM_SR_IC1IR                             TIM_SR_IC1IR_Msk                                 
#define TIM_SR_IC2IR_Pos                         (19U)
#define TIM_SR_IC2IR_Msk                         (0x1UL<<TIM_SR_IC2IR_Pos)                        /*!< 0x00080000 */
#define TIM_SR_IC2IR                             TIM_SR_IC2IR_Msk                                                              
#define TIM_SR_IC3IR_Pos                         (24U)
#define TIM_SR_IC3IR_Msk                         (0x1UL<<TIM_SR_IC3IR_Pos)                        /*!< 0x01000000 */
#define TIM_SR_IC3IR                             TIM_SR_IC3IR_Msk                                 
#define TIM_SR_IC4IR_Pos                         (25U)
#define TIM_SR_IC4IR_Msk                         (0x1UL<<TIM_SR_IC4IR_Pos)                        /*!< 0x02000000 */
#define TIM_SR_IC4IR                             TIM_SR_IC4IR_Msk                                 
#define TIM_SR_IC1IF_Pos                         (26U)
#define TIM_SR_IC1IF_Msk                         (0x1UL<<TIM_SR_IC1IF_Pos)                        /*!< 0x04000000 */
#define TIM_SR_IC1IF                             TIM_SR_IC1IF_Msk                                 
#define TIM_SR_IC2IF_Pos                         (27U)
#define TIM_SR_IC2IF_Msk                         (0x1UL<<TIM_SR_IC2IF_Pos)                        /*!< 0x08000000 */
#define TIM_SR_IC2IF                             TIM_SR_IC2IF_Msk                                 
#define TIM_SR_IC3IF_Pos                         (28U)
#define TIM_SR_IC3IF_Msk                         (0x1UL<<TIM_SR_IC3IF_Pos)                        /*!< 0x10000000 */
#define TIM_SR_IC3IF                             TIM_SR_IC3IF_Msk                                 
#define TIM_SR_IC4IF_Pos                         (29U)
#define TIM_SR_IC4IF_Msk                         (0x1UL<<TIM_SR_IC4IF_Pos)                        /*!< 0x20000000 */
#define TIM_SR_IC4IF                             TIM_SR_IC4IF_Msk                          

/********************************* Bit definition for TIM_EGR register *********************************************/
#define TIM_EGR_UG_Pos                           (0U)
#define TIM_EGR_UG_Msk                           (0x1UL << TIM_EGR_UG_Pos)                     /*!< 0x00000001 */
#define TIM_EGR_UG                               TIM_EGR_UG_Msk                                /*!<Update Generation */
#define TIM_EGR_CC1G_Pos                         (1U)
#define TIM_EGR_CC1G_Msk                         (0x1UL << TIM_EGR_CC1G_Pos)                   /*!< 0x00000002 */
#define TIM_EGR_CC1G                             TIM_EGR_CC1G_Msk                              /*!<Capture/Compare 1 Generation */
#define TIM_EGR_CC2G_Pos                         (2U)
#define TIM_EGR_CC2G_Msk                         (0x1UL << TIM_EGR_CC2G_Pos)                   /*!< 0x00000004 */
#define TIM_EGR_CC2G                             TIM_EGR_CC2G_Msk                              /*!<Capture/Compare 2 Generation */
#define TIM_EGR_CC3G_Pos                         (3U)
#define TIM_EGR_CC3G_Msk                         (0x1UL << TIM_EGR_CC3G_Pos)                   /*!< 0x00000008 */
#define TIM_EGR_CC3G                             TIM_EGR_CC3G_Msk                              /*!<Capture/Compare 3 Generation */
#define TIM_EGR_CC4G_Pos                         (4U)
#define TIM_EGR_CC4G_Msk                         (0x1UL << TIM_EGR_CC4G_Pos)                   /*!< 0x00000010 */
#define TIM_EGR_CC4G                             TIM_EGR_CC4G_Msk                              /*!<Capture/Compare 4 Generation */
#define TIM_EGR_COMG_Pos                         (5U)
#define TIM_EGR_COMG_Msk                         (0x1UL << TIM_EGR_COMG_Pos)                   /*!< 0x00000020 */
#define TIM_EGR_COMG                             TIM_EGR_COMG_Msk                              /*!<Capture/Compare Control Update Generation */
#define TIM_EGR_TG_Pos                           (6U)
#define TIM_EGR_TG_Msk                           (0x1UL << TIM_EGR_TG_Pos)                     /*!< 0x00000040 */
#define TIM_EGR_TG                               TIM_EGR_TG_Msk                                /*!<Trigger Generation */
#define TIM_EGR_BG_Pos                           (7U)
#define TIM_EGR_BG_Msk                           (0x1UL << TIM_EGR_BG_Pos)                     /*!< 0x00000080 */
#define TIM_EGR_BG                               TIM_EGR_BG_Msk                                /*!<Break Generation */                                  

/********************************* Bit definition for TIM_CCMR1 register *******************************************/
#define TIM_CCMR1_CC1S_Pos                       (0U)
#define TIM_CCMR1_CC1S_Msk                       (0x3UL << TIM_CCMR1_CC1S_Pos)                 /*!< 0x00000003 */
#define TIM_CCMR1_CC1S                           TIM_CCMR1_CC1S_Msk                            /*!<CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define TIM_CCMR1_CC1S_0                         (0x1UL << TIM_CCMR1_CC1S_Pos)                 /*!< 0x00000001 */
#define TIM_CCMR1_CC1S_1                         (0x2UL << TIM_CCMR1_CC1S_Pos)                 /*!< 0x00000002 */

#define TIM_CCMR1_OC1FE_Pos                      (2U)
#define TIM_CCMR1_OC1FE_Msk                      (0x1UL << TIM_CCMR1_OC1FE_Pos)                /*!< 0x00000004 */
#define TIM_CCMR1_OC1FE                          TIM_CCMR1_OC1FE_Msk                           /*!<Output Compare 1 Fast enable */
#define TIM_CCMR1_OC1PE_Pos                      (3U)
#define TIM_CCMR1_OC1PE_Msk                      (0x1UL << TIM_CCMR1_OC1PE_Pos)                /*!< 0x00000008 */
#define TIM_CCMR1_OC1PE                          TIM_CCMR1_OC1PE_Msk                           /*!<Output Compare 1 Preload enable */

#define TIM_CCMR1_OC1M_Pos                       (4U)
#define TIM_CCMR1_OC1M_Msk                       (0x1007UL << TIM_CCMR1_OC1M_Pos)              /*!< 0x00010070 */
#define TIM_CCMR1_OC1M                           TIM_CCMR1_OC1M_Msk                            /*!<OC1M[3:0] bits (Output Compare 1 Mode) */
#define TIM_CCMR1_OC1M_0                         (0x1UL << TIM_CCMR1_OC1M_Pos)                 /*!< 0x00000010 */
#define TIM_CCMR1_OC1M_1                         (0x2UL << TIM_CCMR1_OC1M_Pos)                 /*!< 0x00000020 */
#define TIM_CCMR1_OC1M_2                         (0x4UL << TIM_CCMR1_OC1M_Pos)                 /*!< 0x00000040 */
#define TIM_CCMR1_OC1M_3                         (0x1000UL << TIM_CCMR1_OC1M_Pos)              /*!< 0x00010000 */

#define TIM_CCMR1_OC1CE_Pos                      (7U)
#define TIM_CCMR1_OC1CE_Msk                      (0x1UL << TIM_CCMR1_OC1CE_Pos)                /*!< 0x00000080 */
#define TIM_CCMR1_OC1CE                          TIM_CCMR1_OC1CE_Msk                           /*!<Output Compare 1Clear Enable */

#define TIM_CCMR1_CC2S_Pos                       (8U)
#define TIM_CCMR1_CC2S_Msk                       (0x3UL << TIM_CCMR1_CC2S_Pos)                 /*!< 0x00000300 */
#define TIM_CCMR1_CC2S                           TIM_CCMR1_CC2S_Msk                            /*!<CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define TIM_CCMR1_CC2S_0                         (0x1UL << TIM_CCMR1_CC2S_Pos)                 /*!< 0x00000100 */
#define TIM_CCMR1_CC2S_1                         (0x2UL << TIM_CCMR1_CC2S_Pos)                 /*!< 0x00000200 */

#define TIM_CCMR1_OC2FE_Pos                      (10U)
#define TIM_CCMR1_OC2FE_Msk                      (0x1UL << TIM_CCMR1_OC2FE_Pos)                /*!< 0x00000400 */
#define TIM_CCMR1_OC2FE                          TIM_CCMR1_OC2FE_Msk                           /*!<Output Compare 2 Fast enable */
#define TIM_CCMR1_OC2PE_Pos                      (11U)
#define TIM_CCMR1_OC2PE_Msk                      (0x1UL << TIM_CCMR1_OC2PE_Pos)                /*!< 0x00000800 */
#define TIM_CCMR1_OC2PE                          TIM_CCMR1_OC2PE_Msk                           /*!<Output Compare 2 Preload enable */

#define TIM_CCMR1_OC2M_Pos                       (12U)
#define TIM_CCMR1_OC2M_Msk                       (0x1007UL << TIM_CCMR1_OC2M_Pos)              /*!< 0x01007000 */
#define TIM_CCMR1_OC2M                           TIM_CCMR1_OC2M_Msk                            /*!<OC2M[3:0] bits (Output Compare 2 Mode) */
#define TIM_CCMR1_OC2M_0                         (0x1UL << TIM_CCMR1_OC2M_Pos)                 /*!< 0x00001000 */
#define TIM_CCMR1_OC2M_1                         (0x2UL << TIM_CCMR1_OC2M_Pos)                 /*!< 0x00002000 */
#define TIM_CCMR1_OC2M_2                         (0x4UL << TIM_CCMR1_OC2M_Pos)                 /*!< 0x00004000 */
#define TIM_CCMR1_OC2M_3                         (0x1000UL << TIM_CCMR1_OC2M_Pos)              /*!< 0x01000000 */

#define TIM_CCMR1_OC2CE_Pos                      (15U)
#define TIM_CCMR1_OC2CE_Msk                      (0x1UL << TIM_CCMR1_OC2CE_Pos)                /*!< 0x00008000 */
#define TIM_CCMR1_OC2CE                          TIM_CCMR1_OC2CE_Msk                           /*!<Output Compare 2 Clear Enable */

/*---------------------------------------------------------------------------*/
#define TIM_CCMR1_IC1PSC_Pos                     (2U)
#define TIM_CCMR1_IC1PSC_Msk                     (0x3UL << TIM_CCMR1_IC1PSC_Pos)               /*!< 0x0000000C */
#define TIM_CCMR1_IC1PSC                         TIM_CCMR1_IC1PSC_Msk                          /*!<IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define TIM_CCMR1_IC1PSC_0                       (0x1UL << TIM_CCMR1_IC1PSC_Pos)               /*!< 0x00000004 */
#define TIM_CCMR1_IC1PSC_1                       (0x2UL << TIM_CCMR1_IC1PSC_Pos)               /*!< 0x00000008 */

#define TIM_CCMR1_IC1F_Pos                       (4U)
#define TIM_CCMR1_IC1F_Msk                       (0xFUL << TIM_CCMR1_IC1F_Pos)                 /*!< 0x000000F0 */
#define TIM_CCMR1_IC1F                           TIM_CCMR1_IC1F_Msk                            /*!<IC1F[3:0] bits (Input Capture 1 Filter) */
#define TIM_CCMR1_IC1F_0                         (0x1UL << TIM_CCMR1_IC1F_Pos)                 /*!< 0x00000010 */
#define TIM_CCMR1_IC1F_1                         (0x2UL << TIM_CCMR1_IC1F_Pos)                 /*!< 0x00000020 */
#define TIM_CCMR1_IC1F_2                         (0x4UL << TIM_CCMR1_IC1F_Pos)                 /*!< 0x00000040 */
#define TIM_CCMR1_IC1F_3                         (0x8UL << TIM_CCMR1_IC1F_Pos)                 /*!< 0x00000080 */

#define TIM_CCMR1_IC2PSC_Pos                     (10U)
#define TIM_CCMR1_IC2PSC_Msk                     (0x3UL << TIM_CCMR1_IC2PSC_Pos)               /*!< 0x00000C00 */
#define TIM_CCMR1_IC2PSC                         TIM_CCMR1_IC2PSC_Msk                          /*!<IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define TIM_CCMR1_IC2PSC_0                       (0x1UL << TIM_CCMR1_IC2PSC_Pos)               /*!< 0x00000400 */
#define TIM_CCMR1_IC2PSC_1                       (0x2UL << TIM_CCMR1_IC2PSC_Pos)               /*!< 0x00000800 */

#define TIM_CCMR1_IC2F_Pos                       (12U)
#define TIM_CCMR1_IC2F_Msk                       (0xFUL << TIM_CCMR1_IC2F_Pos)                 /*!< 0x0000F000 */
#define TIM_CCMR1_IC2F                           TIM_CCMR1_IC2F_Msk                            /*!<IC2F[3:0] bits (Input Capture 2 Filter) */
#define TIM_CCMR1_IC2F_0                         (0x1UL << TIM_CCMR1_IC2F_Pos)                 /*!< 0x00001000 */
#define TIM_CCMR1_IC2F_1                         (0x2UL << TIM_CCMR1_IC2F_Pos)                 /*!< 0x00002000 */
#define TIM_CCMR1_IC2F_2                         (0x4UL << TIM_CCMR1_IC2F_Pos)                 /*!< 0x00004000 */
#define TIM_CCMR1_IC2F_3                         (0x8UL << TIM_CCMR1_IC2F_Pos)                 /*!< 0x00008000 */

/********************************* Bit definition for TIM_CCMR2 register ********************************************/
#define TIM_CCMR2_CC3S_Pos                       (0U)
#define TIM_CCMR2_CC3S_Msk                       (0x3UL << TIM_CCMR2_CC3S_Pos)                 /*!< 0x00000003 */
#define TIM_CCMR2_CC3S                           TIM_CCMR2_CC3S_Msk                            /*!<CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define TIM_CCMR2_CC3S_0                         (0x1UL << TIM_CCMR2_CC3S_Pos)                 /*!< 0x00000001 */
#define TIM_CCMR2_CC3S_1                         (0x2UL << TIM_CCMR2_CC3S_Pos)                 /*!< 0x00000002 */
               
#define TIM_CCMR2_OC3FE_Pos                      (2U)
#define TIM_CCMR2_OC3FE_Msk                      (0x1UL << TIM_CCMR2_OC3FE_Pos)                /*!< 0x00000004 */
#define TIM_CCMR2_OC3FE                          TIM_CCMR2_OC3FE_Msk                           /*!<Output Compare 3 Fast enable */
#define TIM_CCMR2_OC3PE_Pos                      (3U)
#define TIM_CCMR2_OC3PE_Msk                      (0x1UL << TIM_CCMR2_OC3PE_Pos)                /*!< 0x00000008 */
#define TIM_CCMR2_OC3PE                          TIM_CCMR2_OC3PE_Msk                           /*!<Output Compare 3 Preload enable */
               
#define TIM_CCMR2_OC3M_Pos                       (4U)
#define TIM_CCMR2_OC3M_Msk                       (0x1007UL << TIM_CCMR2_OC3M_Pos)              /*!< 0x00010070 */
#define TIM_CCMR2_OC3M                           TIM_CCMR2_OC3M_Msk                            /*!<OC3M[3:0] bits (Output Compare 3 Mode) */
#define TIM_CCMR2_OC3M_0                         (0x1UL << TIM_CCMR2_OC3M_Pos)                 /*!< 0x00000010 */
#define TIM_CCMR2_OC3M_1                         (0x2UL << TIM_CCMR2_OC3M_Pos)                 /*!< 0x00000020 */
#define TIM_CCMR2_OC3M_2                         (0x4UL << TIM_CCMR2_OC3M_Pos)                 /*!< 0x00000040 */
#define TIM_CCMR2_OC3M_3                         (0x1000UL << TIM_CCMR2_OC3M_Pos)              /*!< 0x00010000 */
               
#define TIM_CCMR2_OC3CE_Pos                      (7U)
#define TIM_CCMR2_OC3CE_Msk                      (0x1UL << TIM_CCMR2_OC3CE_Pos)                /*!< 0x00000080 */
#define TIM_CCMR2_OC3CE                          TIM_CCMR2_OC3CE_Msk                           /*!<Output Compare 3 Clear Enable */
               
#define TIM_CCMR2_CC4S_Pos                       (8U)
#define TIM_CCMR2_CC4S_Msk                       (0x3UL << TIM_CCMR2_CC4S_Pos)                 /*!< 0x00000300 */
#define TIM_CCMR2_CC4S                           TIM_CCMR2_CC4S_Msk                            /*!<CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define TIM_CCMR2_CC4S_0                         (0x1UL << TIM_CCMR2_CC4S_Pos)                 /*!< 0x00000100 */
#define TIM_CCMR2_CC4S_1                         (0x2UL << TIM_CCMR2_CC4S_Pos)                 /*!< 0x00000200 */
               
#define TIM_CCMR2_OC4FE_Pos                      (10U)
#define TIM_CCMR2_OC4FE_Msk                      (0x1UL << TIM_CCMR2_OC4FE_Pos)                /*!< 0x00000400 */
#define TIM_CCMR2_OC4FE                          TIM_CCMR2_OC4FE_Msk                           /*!<Output Compare 4 Fast enable */
#define TIM_CCMR2_OC4PE_Pos                      (11U)
#define TIM_CCMR2_OC4PE_Msk                      (0x1UL << TIM_CCMR2_OC4PE_Pos)                /*!< 0x00000800 */
#define TIM_CCMR2_OC4PE                          TIM_CCMR2_OC4PE_Msk                           /*!<Output Compare 4 Preload enable */
               
#define TIM_CCMR2_OC4M_Pos                       (12U)
#define TIM_CCMR2_OC4M_Msk                       (0x1007UL << TIM_CCMR2_OC4M_Pos)              /*!< 0x01007000 */
#define TIM_CCMR2_OC4M                           TIM_CCMR2_OC4M_Msk                            /*!<OC4M[3:0] bits (Output Compare 4 Mode) */
#define TIM_CCMR2_OC4M_0                         (0x1UL << TIM_CCMR2_OC4M_Pos)                 /*!< 0x00001000 */
#define TIM_CCMR2_OC4M_1                         (0x2UL << TIM_CCMR2_OC4M_Pos)                 /*!< 0x00002000 */
#define TIM_CCMR2_OC4M_2                         (0x4UL << TIM_CCMR2_OC4M_Pos)                 /*!< 0x00004000 */
#define TIM_CCMR2_OC4M_3                         (0x1000UL << TIM_CCMR2_OC4M_Pos)              /*!< 0x01000000 */
               
#define TIM_CCMR2_OC4CE_Pos                      (15U)
#define TIM_CCMR2_OC4CE_Msk                      (0x1UL << TIM_CCMR2_OC4CE_Pos)                /*!< 0x00008000 */
#define TIM_CCMR2_OC4CE                          TIM_CCMR2_OC4CE_Msk                           /*!<Output Compare 4 Clear Enable */

/*---------------------------------------------------------------------------*/
#define TIM_CCMR2_IC3PSC_Pos                     (2U)
#define TIM_CCMR2_IC3PSC_Msk                     (0x3UL << TIM_CCMR2_IC3PSC_Pos)               /*!< 0x0000000C */
#define TIM_CCMR2_IC3PSC                         TIM_CCMR2_IC3PSC_Msk                          /*!<IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define TIM_CCMR2_IC3PSC_0                       (0x1UL << TIM_CCMR2_IC3PSC_Pos)               /*!< 0x00000004 */
#define TIM_CCMR2_IC3PSC_1                       (0x2UL << TIM_CCMR2_IC3PSC_Pos)               /*!< 0x00000008 */
              
#define TIM_CCMR2_IC3F_Pos                       (4U)
#define TIM_CCMR2_IC3F_Msk                       (0xFUL << TIM_CCMR2_IC3F_Pos)                 /*!< 0x000000F0 */
#define TIM_CCMR2_IC3F                           TIM_CCMR2_IC3F_Msk                            /*!<IC3F[3:0] bits (Input Capture 3 Filter) */
#define TIM_CCMR2_IC3F_0                         (0x1UL << TIM_CCMR2_IC3F_Pos)                 /*!< 0x00000010 */
#define TIM_CCMR2_IC3F_1                         (0x2UL << TIM_CCMR2_IC3F_Pos)                 /*!< 0x00000020 */
#define TIM_CCMR2_IC3F_2                         (0x4UL << TIM_CCMR2_IC3F_Pos)                 /*!< 0x00000040 */
#define TIM_CCMR2_IC3F_3                         (0x8UL << TIM_CCMR2_IC3F_Pos)                 /*!< 0x00000080 */
              
#define TIM_CCMR2_IC4PSC_Pos                     (10U)
#define TIM_CCMR2_IC4PSC_Msk                     (0x3UL << TIM_CCMR2_IC4PSC_Pos)               /*!< 0x00000C00 */
#define TIM_CCMR2_IC4PSC                         TIM_CCMR2_IC4PSC_Msk                          /*!<IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define TIM_CCMR2_IC4PSC_0                       (0x1UL << TIM_CCMR2_IC4PSC_Pos)               /*!< 0x00000400 */
#define TIM_CCMR2_IC4PSC_1                       (0x2UL << TIM_CCMR2_IC4PSC_Pos)               /*!< 0x00000800 */
              
#define TIM_CCMR2_IC4F_Pos                       (12U)
#define TIM_CCMR2_IC4F_Msk                       (0xFUL << TIM_CCMR2_IC4F_Pos)                 /*!< 0x0000F000 */
#define TIM_CCMR2_IC4F                           TIM_CCMR2_IC4F_Msk                            /*!<IC4F[3:0] bits (Input Capture 4 Filter) */
#define TIM_CCMR2_IC4F_0                         (0x1UL << TIM_CCMR2_IC4F_Pos)                 /*!< 0x00001000 */
#define TIM_CCMR2_IC4F_1                         (0x2UL << TIM_CCMR2_IC4F_Pos)                 /*!< 0x00002000 */
#define TIM_CCMR2_IC4F_2                         (0x4UL << TIM_CCMR2_IC4F_Pos)                 /*!< 0x00004000 */
#define TIM_CCMR2_IC4F_3                         (0x8UL << TIM_CCMR2_IC4F_Pos)                 /*!< 0x00008000 */

/********************************* Bit definition for TIM_CCER register *********************************************/
#define TIM_CCER_CC1E_Pos                        (0U)
#define TIM_CCER_CC1E_Msk                        (0x1UL << TIM_CCER_CC1E_Pos)                  /*!< 0x00000001 */
#define TIM_CCER_CC1E                            TIM_CCER_CC1E_Msk                             /*!<Capture/Compare 1 output enable */
#define TIM_CCER_CC1P_Pos                        (1U)
#define TIM_CCER_CC1P_Msk                        (0x1UL << TIM_CCER_CC1P_Pos)                  /*!< 0x00000002 */
#define TIM_CCER_CC1P                            TIM_CCER_CC1P_Msk                             /*!<Capture/Compare 1 output Polarity */
#define TIM_CCER_CC1NE_Pos                       (2U)
#define TIM_CCER_CC1NE_Msk                       (0x1UL << TIM_CCER_CC1NE_Pos)                 /*!< 0x00000004 */
#define TIM_CCER_CC1NE                           TIM_CCER_CC1NE_Msk                            /*!<Capture/Compare 1 Complementary output enable */
#define TIM_CCER_CC1NP_Pos                       (3U)
#define TIM_CCER_CC1NP_Msk                       (0x1UL << TIM_CCER_CC1NP_Pos)                 /*!< 0x00000008 */
#define TIM_CCER_CC1NP                           TIM_CCER_CC1NP_Msk                            /*!<Capture/Compare 1 Complementary output Polarity */
#define TIM_CCER_CC2E_Pos                        (4U)
#define TIM_CCER_CC2E_Msk                        (0x1UL << TIM_CCER_CC2E_Pos)                  /*!< 0x00000010 */
#define TIM_CCER_CC2E                            TIM_CCER_CC2E_Msk                             /*!<Capture/Compare 2 output enable */
#define TIM_CCER_CC2P_Pos                        (5U)
#define TIM_CCER_CC2P_Msk                        (0x1UL << TIM_CCER_CC2P_Pos)                  /*!< 0x00000020 */
#define TIM_CCER_CC2P                            TIM_CCER_CC2P_Msk                             /*!<Capture/Compare 2 output Polarity */
#define TIM_CCER_CC2NE_Pos                       (6U)
#define TIM_CCER_CC2NE_Msk                       (0x1UL << TIM_CCER_CC2NE_Pos)                 /*!< 0x00000040 */
#define TIM_CCER_CC2NE                           TIM_CCER_CC2NE_Msk                            /*!<Capture/Compare 2 Complementary output enable */
#define TIM_CCER_CC2NP_Pos                       (7U)
#define TIM_CCER_CC2NP_Msk                       (0x1UL << TIM_CCER_CC2NP_Pos)                 /*!< 0x00000080 */
#define TIM_CCER_CC2NP                           TIM_CCER_CC2NP_Msk                            /*!<Capture/Compare 2 Complementary output Polarity */
#define TIM_CCER_CC3E_Pos                        (8U)
#define TIM_CCER_CC3E_Msk                        (0x1UL << TIM_CCER_CC3E_Pos)                  /*!< 0x00000100 */
#define TIM_CCER_CC3E                            TIM_CCER_CC3E_Msk                             /*!<Capture/Compare 3 output enable */
#define TIM_CCER_CC3P_Pos                        (9U)
#define TIM_CCER_CC3P_Msk                        (0x1UL << TIM_CCER_CC3P_Pos)                  /*!< 0x00000200 */
#define TIM_CCER_CC3P                            TIM_CCER_CC3P_Msk                             /*!<Capture/Compare 3 output Polarity */
#define TIM_CCER_CC3NE_Pos                       (10U)
#define TIM_CCER_CC3NE_Msk                       (0x1UL << TIM_CCER_CC3NE_Pos)                 /*!< 0x00000400 */
#define TIM_CCER_CC3NE                           TIM_CCER_CC3NE_Msk                            /*!<Capture/Compare 3 Complementary output enable */
#define TIM_CCER_CC3NP_Pos                       (11U)
#define TIM_CCER_CC3NP_Msk                       (0x1UL << TIM_CCER_CC3NP_Pos)                 /*!< 0x00000800 */
#define TIM_CCER_CC3NP                           TIM_CCER_CC3NP_Msk                            /*!<Capture/Compare 3 Complementary output Polarity */
#define TIM_CCER_CC4E_Pos                        (12U)
#define TIM_CCER_CC4E_Msk                        (0x1UL << TIM_CCER_CC4E_Pos)                  /*!< 0x00001000 */
#define TIM_CCER_CC4E                            TIM_CCER_CC4E_Msk                             /*!<Capture/Compare 4 output enable */
#define TIM_CCER_CC4P_Pos                        (13U)
#define TIM_CCER_CC4P_Msk                        (0x1UL << TIM_CCER_CC4P_Pos)                  /*!< 0x00002000 */
#define TIM_CCER_CC4P                            TIM_CCER_CC4P_Msk                             /*!<Capture/Compare 4 output Polarity */                      
#define TIM_CCER_CC5E_Pos                        (16U)
#define TIM_CCER_CC5E_Msk                        (0x1UL << TIM_CCER_CC5E_Pos)                  /*!< 0x00010000 */
#define TIM_CCER_CC5E                            TIM_CCER_CC5E_Msk                             /*!<Capture/Compare 5 output enable */
#define TIM_CCER_CC5P_Pos                        (17U)
#define TIM_CCER_CC5P_Msk                        (0x1UL << TIM_CCER_CC5P_Pos)                  /*!< 0x00020000 */
#define TIM_CCER_CC5P                            TIM_CCER_CC5P_Msk                             /*!<Capture/Compare 5 output Polarity */                      
#define TIM_CCER_CC6E_Pos                        (20U)
#define TIM_CCER_CC6E_Msk                        (0x1UL << TIM_CCER_CC6E_Pos)                  /*!< 0x00100000 */
#define TIM_CCER_CC6E                            TIM_CCER_CC6E_Msk                             /*!<Capture/Compare 6 output enable */
#define TIM_CCER_CC6P_Pos                        (21U)
#define TIM_CCER_CC6P_Msk                        (0x1UL << TIM_CCER_CC6P_Pos)                  /*!< 0x00200000 */
#define TIM_CCER_CC6P                            TIM_CCER_CC6P_Msk                             /*!<Capture/Compare 6 output Polarity */                      

/********************************* Bit definition for TIM_CNT register *********************************************/
#define TIM_CNT_CNT_Pos                          (0U)
#define TIM_CNT_CNT_Msk                          (0xFFFFUL<<TIM_CNT_CNT_Pos)                      /*!< 0x0000FFFF */
#define TIM_CNT_CNT                              TIM_CNT_CNT_Msk

/********************************* Bit definition for TIM_PSC register *********************************************/
#define TIM_PSC_PSC_Pos                          (0U)
#define TIM_PSC_PSC_Msk                          (0xFFFFUL<<TIM_PSC_PSC_Pos)                      /*!< 0x0000FFFF */
#define TIM_PSC_PSC                              TIM_PSC_PSC_Msk

/********************************* Bit definition for TIM_ARR register *********************************************/
#define TIM_ARR_ARR_Pos                          (0U)
#define TIM_ARR_ARR_Msk                          (0xFFFFUL<<TIM_ARR_ARR_Pos)                      /*!< 0x0000FFFF */
#define TIM_ARR_ARR                              TIM_ARR_ARR_Msk

/********************************* Bit definition for TIM_RCR register *********************************************/
#define TIM_RCR_REP_Pos                          (0U)
#define TIM_RCR_REP_Msk                          (0xFFFFUL<<TIM_RCR_REP_Pos)                      /*!< 0x0000FFFF */
#define TIM_RCR_REP                              TIM_RCR_REP_Msk

/********************************* Bit definition for TIM_CCR1 register ********************************************/
#define TIM_CCR1_CCR1_Pos                        (0U)
#define TIM_CCR1_CCR1_Msk                        (0xFFFFUL<<TIM_CCR1_CCR1_Pos)                    /*!< 0x0000FFFF */
#define TIM_CCR1_CCR1                            TIM_CCR1_CCR1_Msk
#define TIM_CCR1_CCR1_H_Pos                      (16U)
#define TIM_CCR1_CCR1_H_Msk                      (0xFFFFUL<<TIM_CCR1_CCR1_H_Pos)                  /*!< 0xFFFF0000 */
#define TIM_CCR1_CCR1_H                          TIM_CCR1_CCR1_H_Msk

/********************************* Bit definition for TIM_CCR2 register ********************************************/
#define TIM_CCR2_CCR2_Pos                        (0U)
#define TIM_CCR2_CCR2_Msk                        (0xFFFFUL<<TIM_CCR2_CCR2_Pos)                    /*!< 0x0000FFFF */
#define TIM_CCR2_CCR2                            TIM_CCR2_CCR2_Msk
#define TIM_CCR2_CCR2_H_Pos                      (16U)
#define TIM_CCR2_CCR2_H_Msk                      (0xFFFFUL<<TIM_CCR2_CCR2_H_Pos)                  /*!< 0xFFFF0000 */
#define TIM_CCR2_CCR2_H                          TIM_CCR2_CCR2_H_Msk

/********************************* Bit definition for TIM_CCR3 register ********************************************/
#define TIM_CCR3_CCR3_Pos                        (0U)
#define TIM_CCR3_CCR3_Msk                        (0xFFFFUL<<TIM_CCR3_CCR3_Pos)                    /*!< 0x0000FFFF */
#define TIM_CCR3_CCR3                            TIM_CCR3_CCR3_Msk
#define TIM_CCR3_CCR3_H_Pos                      (16U)
#define TIM_CCR3_CCR3_H_Msk                      (0xFFFFUL<<TIM_CCR3_CCR3_H_Pos)                  /*!< 0xFFFF0000 */
#define TIM_CCR3_CCR3_H                          TIM_CCR3_CCR3_H_Msk

/********************************* Bit definition for TIM_CCR4 register ********************************************/
#define TIM_CCR4_CCR4_Pos                        (0U)
#define TIM_CCR4_CCR4_Msk                        (0xFFFFUL<<TIM_CCR4_CCR4_Pos)                    /*!< 0x0000FFFF */
#define TIM_CCR4_CCR4                            TIM_CCR4_CCR4_Msk

/********************************* Bit definition for TIM_BDTR register ********************************************/
#define TIM_BDTR_DTG_Pos                         (0U)
#define TIM_BDTR_DTG_Msk                         (0xFFUL<<TIM_BDTR_DTG_Pos)                       /*!< 0x000000FF */
#define TIM_BDTR_DTG                             TIM_BDTR_DTG_Msk
#define TIM_BDTR_LOCK_Pos                        (8U)
#define TIM_BDTR_LOCK_Msk                        (0x3UL<<TIM_BDTR_LOCK_Pos)                       /*!< 0x00000300 */
#define TIM_BDTR_LOCK                            TIM_BDTR_LOCK_Msk
#define TIM_BDTR_LOCK_0                          (0x1UL<<TIM_BDTR_LOCK_Pos)                       /*!< 0x00000100 */
#define TIM_BDTR_LOCK_1                          (0x2UL<<TIM_BDTR_LOCK_Pos)                       /*!< 0x00000200 */
#define TIM_BDTR_OSSI_Pos                        (10U)
#define TIM_BDTR_OSSI_Msk                        (0x1UL<<TIM_BDTR_OSSI_Pos)                       /*!< 0x00000400 */
#define TIM_BDTR_OSSI                            TIM_BDTR_OSSI_Msk                                
#define TIM_BDTR_OSSR_Pos                        (11U)
#define TIM_BDTR_OSSR_Msk                        (0x1UL<<TIM_BDTR_OSSR_Pos)                       /*!< 0x00000800 */
#define TIM_BDTR_OSSR                            TIM_BDTR_OSSR_Msk                                
#define TIM_BDTR_BKE_Pos                         (12U)
#define TIM_BDTR_BKE_Msk                         (0x1UL<<TIM_BDTR_BKE_Pos)                        /*!< 0x00001000 */
#define TIM_BDTR_BKE                             TIM_BDTR_BKE_Msk                                 
#define TIM_BDTR_BKP_Pos                         (13U)
#define TIM_BDTR_BKP_Msk                         (0x1UL<<TIM_BDTR_BKP_Pos)                        /*!< 0x00002000 */
#define TIM_BDTR_BKP                             TIM_BDTR_BKP_Msk                                 
#define TIM_BDTR_AOE_Pos                         (14U)
#define TIM_BDTR_AOE_Msk                         (0x1UL<<TIM_BDTR_AOE_Pos)                        /*!< 0x00004000 */
#define TIM_BDTR_AOE                             TIM_BDTR_AOE_Msk                                 
#define TIM_BDTR_MOE_Pos                         (15U)
#define TIM_BDTR_MOE_Msk                         (0x1UL<<TIM_BDTR_MOE_Pos)                        /*!< 0x00008000 */
#define TIM_BDTR_MOE                             TIM_BDTR_MOE_Msk                                 

/********************************* Bit definition for TIM_CCR5 register ********************************************/
#define TIM_CCR5_CCR5_Pos                        (0U)
#define TIM_CCR5_CCR5_Msk                        (0xFFFFUL<<TIM_CCR5_CCR5_Pos)                    /*!< 0x0000FFFF */
#define TIM_CCR5_CCR5                            TIM_CCR5_CCR5_Msk

/********************************* Bit definition for TIM_CCR6 register ********************************************/
#define TIM_CCR6_CCR6_Pos                        (0U)
#define TIM_CCR6_CCR6_Msk                        (0xFFFFUL<<TIM_CCR6_CCR6_Pos)                    /*!< 0x0000FFFF */
#define TIM_CCR6_CCR6                            TIM_CCR6_CCR6_Msk

/********************************* Bit definition for TIM_CCMR3 register ************************************/
#define TIM_CCMR3_OC5FE_Pos                      (2U)
#define TIM_CCMR3_OC5FE_Msk                      (0x1UL<<TIM_CCMR3_OC5FE_Pos)                     /*!< 0x00000004 */
#define TIM_CCMR3_OC5FE                          TIM_CCMR3_OC5FE_Msk                       
#define TIM_CCMR3_OC5PE_Pos                      (3U)
#define TIM_CCMR3_OC5PE_Msk                      (0x1UL<<TIM_CCMR3_OC5PE_Pos)                     /*!< 0x00000008 */
#define TIM_CCMR3_OC5PE                          TIM_CCMR3_OC5PE_Msk                       
#define TIM_CCMR3_OC5M_Pos                       (4U)
#define TIM_CCMR3_OC5M_Msk                       (0x1007UL << TIM_CCMR3_OC5M_Pos)                 /*!< 0x00010070 */
#define TIM_CCMR3_OC5M                           TIM_CCMR3_OC5M_Msk                               /*!<OC5M[3:0] bits (Output Compare 5 Mode) */
#define TIM_CCMR3_OC5M_0                         (0x1UL << TIM_CCMR3_OC5M_Pos)                    /*!< 0x00000010 */
#define TIM_CCMR3_OC5M_1                         (0x2UL << TIM_CCMR3_OC5M_Pos)                    /*!< 0x00000020 */
#define TIM_CCMR3_OC5M_2                         (0x4UL << TIM_CCMR3_OC5M_Pos)                    /*!< 0x00000040 */
#define TIM_CCMR3_OC5M_3                         (0x1000UL << TIM_CCMR3_OC5M_Pos)                 /*!< 0x00010000 */
#define TIM_CCMR3_OC5CE_Pos                      (7U)
#define TIM_CCMR3_OC5CE_Msk                      (0x1UL<<TIM_CCMR3_OC5CE_Pos)                     /*!< 0x00000080 */
#define TIM_CCMR3_OC5CE                          TIM_CCMR3_OC5CE_Msk                       
#define TIM_CCMR3_OC6FE_Pos                      (10U)
#define TIM_CCMR3_OC6FE_Msk                      (0x1UL<<TIM_CCMR3_OC6FE_Pos)                     /*!< 0x00000400 */
#define TIM_CCMR3_OC6FE                          TIM_CCMR3_OC6FE_Msk                       
#define TIM_CCMR3_OC6PE_Pos                      (11U)
#define TIM_CCMR3_OC6PE_Msk                      (0x1UL<<TIM_CCMR3_OC6PE_Pos)                     /*!< 0x00000800 */
#define TIM_CCMR3_OC6PE                          TIM_CCMR3_OC6PE_Msk                       
#define TIM_CCMR3_OC6M_Pos                       (12U)
#define TIM_CCMR3_OC6M_Msk                       (0x1007UL << TIM_CCMR3_OC6M_Pos)                 /*!< 0x01007000 */
#define TIM_CCMR3_OC6M                           TIM_CCMR3_OC6M_Msk                               /*!<OC6M[3:0] bits (Output Compare 6 Mode) */
#define TIM_CCMR3_OC6M_0                         (0x1UL << TIM_CCMR3_OC6M_Pos)                    /*!< 0x00001000 */
#define TIM_CCMR3_OC6M_1                         (0x2UL << TIM_CCMR3_OC6M_Pos)                    /*!< 0x00002000 */
#define TIM_CCMR3_OC6M_2                         (0x4UL << TIM_CCMR3_OC6M_Pos)                    /*!< 0x00004000 */
#define TIM_CCMR3_OC6M_3                         (0x1000UL << TIM_CCMR3_OC6M_Pos)                 /*!< 0x01000000 */
#define TIM_CCMR3_OC6CE_Pos                      (15U)
#define TIM_CCMR3_OC6CE_Msk                      (0x1UL<<TIM_CCMR3_OC6CE_Pos)                     /*!< 0x00008000 */
#define TIM_CCMR3_OC6CE                           TIM_CCMR3_OC6CE_Msk                       
                  
/********************************* Bit definition for TIM_TISEL register *******************************************/
#define TIM_TISEL_TI1SEL_Pos                     (0U)
#define TIM_TISEL_TI1SEL_Msk                     (0xFUL<<TIM_TISEL_TI1SEL_Pos)                    /*!< 0x0000000F */
#define TIM_TISEL_TI1SEL                         TIM_TISEL_TI1SEL_Msk
#define TIM_TISEL_TI1SEL_0                       (0x1UL<<TIM_TISEL_TI1SEL_Pos)                    /*!< 0x00000001 */
#define TIM_TISEL_TI1SEL_1                       (0x2UL<<TIM_TISEL_TI1SEL_Pos)                    /*!< 0x00000002 */
#define TIM_TISEL_TI1SEL_2                       (0x4UL<<TIM_TISEL_TI1SEL_Pos)                    /*!< 0x00000004 */
#define TIM_TISEL_TI1SEL_3                       (0x8UL<<TIM_TISEL_TI1SEL_Pos)                    /*!< 0x00000008 */
#define TIM_TISEL_TI2SEL_Pos                     (8U)
#define TIM_TISEL_TI2SEL_Msk                     (0xFUL<<TIM_TISEL_TI2SEL_Pos)                    /*!< 0x00000F00 */
#define TIM_TISEL_TI2SEL                         TIM_TISEL_TI2SEL_Msk
#define TIM_TISEL_TI2SEL_0                       (0x1UL<<TIM_TISEL_TI2SEL_Pos)                    /*!< 0x00000100 */
#define TIM_TISEL_TI2SEL_1                       (0x2UL<<TIM_TISEL_TI2SEL_Pos)                    /*!< 0x00000200 */
#define TIM_TISEL_TI2SEL_2                       (0x4UL<<TIM_TISEL_TI2SEL_Pos)                    /*!< 0x00000400 */
#define TIM_TISEL_TI2SEL_3                       (0x8UL<<TIM_TISEL_TI2SEL_Pos)                    /*!< 0x00000800 */
#define TIM_TISEL_TI3SEL_Pos                     (16U)
#define TIM_TISEL_TI3SEL_Msk                     (0xFUL<<TIM_TISEL_TI3SEL_Pos)                    /*!< 0x000F0000 */
#define TIM_TISEL_TI3SEL                         TIM_TISEL_TI3SEL_Msk
#define TIM_TISEL_TI3SEL_0                       (0x1UL<<TIM_TISEL_TI3SEL_Pos)                    /*!< 0x00010000 */
#define TIM_TISEL_TI3SEL_1                       (0x2UL<<TIM_TISEL_TI3SEL_Pos)                    /*!< 0x00020000 */
#define TIM_TISEL_TI3SEL_2                       (0x4UL<<TIM_TISEL_TI3SEL_Pos)                    /*!< 0x00040000 */
#define TIM_TISEL_TI3SEL_3                       (0x8UL<<TIM_TISEL_TI3SEL_Pos)                    /*!< 0x00080000 */
#define TIM_TISEL_TI4SEL_Pos                     (24U)
#define TIM_TISEL_TI4SEL_Msk                     (0xFUL<<TIM_TISEL_TI4SEL_Pos)                    /*!< 0x0F000000 */
#define TIM_TISEL_TI4SEL                         TIM_TISEL_TI4SEL_Msk
#define TIM_TISEL_TI4SEL_0                       (0x1UL<<TIM_TISEL_TI4SEL_Pos)                    /*!< 0x01000000 */
#define TIM_TISEL_TI4SEL_1                       (0x2UL<<TIM_TISEL_TI4SEL_Pos)                    /*!< 0x02000000 */
#define TIM_TISEL_TI4SEL_2                       (0x4UL<<TIM_TISEL_TI4SEL_Pos)                    /*!< 0x04000000 */
#define TIM_TISEL_TI4SEL_3                       (0x8UL<<TIM_TISEL_TI4SEL_Pos)                    /*!< 0x08000000 */

/********************************* Bit definition for TIM_AF1 register *********************************************/
#define TIM_AF1_BKINE_Pos                        (0U)
#define TIM_AF1_BKINE_Msk                        (0x1UL<<TIM_AF1_BKINE_Pos)                       /*!< 0x00000001 */
#define TIM_AF1_BKINE                            TIM_AF1_BKINE_Msk                                
#define TIM_AF1_BKCMP1E_Pos                      (1U)
#define TIM_AF1_BKCMP1E_Msk                      (0x1UL<<TIM_AF1_BKCMP1E_Pos)                     /*!< 0x00000002 */
#define TIM_AF1_BKCMP1E                          TIM_AF1_BKCMP1E_Msk                              
#define TIM_AF1_BKCMP2E_Pos                      (2U)
#define TIM_AF1_BKCMP2E_Msk                      (0x1UL<<TIM_AF1_BKCMP2E_Pos)                     /*!< 0x00000004 */
#define TIM_AF1_BKCMP2E                          TIM_AF1_BKCMP2E_Msk                              
#define TIM_AF1_BKINP_Pos                        (9U)
#define TIM_AF1_BKINP_Msk                        (0x1UL<<TIM_AF1_BKINP_Pos)                       /*!< 0x00000200 */
#define TIM_AF1_BKINP                            TIM_AF1_BKINP_Msk                                
#define TIM_AF1_BKCMP1P_Pos                      (10U)
#define TIM_AF1_BKCMP1P_Msk                      (0x1UL<<TIM_AF1_BKCMP1P_Pos)                     /*!< 0x00000400 */
#define TIM_AF1_BKCMP1P                          TIM_AF1_BKCMP1P_Msk                              
#define TIM_AF1_BKCMP2P_Pos                      (11U)
#define TIM_AF1_BKCMP2P_Msk                      (0x1UL<<TIM_AF1_BKCMP2P_Pos)                     /*!< 0x00000800 */
#define TIM_AF1_BKCMP2P                          TIM_AF1_BKCMP2P_Msk                              
#define TIM_AF1_ETRSEL_Pos                       (14U)
#define TIM_AF1_ETRSEL_Msk                       (0xFUL<<TIM_AF1_ETRSEL_Pos)                      /*!< 0x0003C000 */
#define TIM_AF1_ETRSEL                           TIM_AF1_ETRSEL_Msk
#define TIM_AF1_ETRSEL_0                         (0x1UL<<TIM_AF1_ETRSEL_Pos)                      /*!< 0x00004000 */
#define TIM_AF1_ETRSEL_1                         (0x2UL<<TIM_AF1_ETRSEL_Pos)                      /*!< 0x00008000 */
#define TIM_AF1_ETRSEL_2                         (0x4UL<<TIM_AF1_ETRSEL_Pos)                      /*!< 0x00010000 */
#define TIM_AF1_ETRSEL_3                         (0x8UL<<TIM_AF1_ETRSEL_Pos)                      /*!< 0x00020000 */
#define TIM_AF1_INTR_SEL_Pos                     (18U)
#define TIM_AF1_INTR_SEL_Msk                     (0x3UL<<TIM_AF1_INTR_SEL_Pos)                    /*!< 0x000C0000 */
#define TIM_AF1_INTR_SEL                         TIM_AF1_INTR_SEL_Msk
#define TIM_AF1_INTR_SEL_0                       (0x1UL<<TIM_AF1_INTR_SEL_Pos)                    /*!< 0x00040000 */
#define TIM_AF1_INTR_SEL_1                       (0x2UL<<TIM_AF1_INTR_SEL_Pos)                    /*!< 0x00080000 */
#define TIM_AF1_PWM_PHS_EN_Pos                   (20U)
#define TIM_AF1_PWM_PHS_EN_Msk                   (0x1UL<<TIM_AF1_PWM_PHS_EN_Pos)                  /*!< 0x00100000 */
#define TIM_AF1_PWM_PHS_EN                       TIM_AF1_PWM_PHS_EN_Msk                           

/********************************* Bit definition for TIM_AF2 register *********************************************/
#define TIM_AF2_OCRSEL_Pos                       (16U)
#define TIM_AF2_OCRSEL_Msk                       (0x7UL<<TIM_AF2_OCRSEL_Pos)                      /*!< 0x00070000 */
#define TIM_AF2_OCRSEL                           TIM_AF2_OCRSEL_Msk
#define TIM_AF2_OCRSEL_0                         (0x1UL<<TIM_AF2_OCRSEL_Pos)                      /*!< 0x00010000 */
#define TIM_AF2_OCRSEL_1                         (0x2UL<<TIM_AF2_OCRSEL_Pos)                      /*!< 0x00020000 */
#define TIM_AF2_OCRSEL_2                         (0x4UL<<TIM_AF2_OCRSEL_Pos)                      /*!< 0x00040000 */

/********************************* Bit definition for TIM_DCR register *********************************************/
#define TIM_DCR_DBA_Pos                          (0U)
#define TIM_DCR_DBA_Msk                          (0x1FUL<<TIM_DCR_DBA_Pos)                        /*!< 0x0000001F */
#define TIM_DCR_DBA                              TIM_DCR_DBA_Msk
#define TIM_DCR_DBA_0                            (0x1UL<<TIM_DCR_DBA_Pos)                         /*!< 0x00000001 */
#define TIM_DCR_DBA_1                            (0x2UL<<TIM_DCR_DBA_Pos)                         /*!< 0x00000002 */
#define TIM_DCR_DBA_2                            (0x4UL<<TIM_DCR_DBA_Pos)                         /*!< 0x00000004 */
#define TIM_DCR_DBA_3                            (0x8UL<<TIM_DCR_DBA_Pos)                         /*!< 0x00000008 */
#define TIM_DCR_DBA_4                            (0x10UL<<TIM_DCR_DBA_Pos)                        /*!< 0x00000010 */
#define TIM_DCR_DBL_Pos                          (8U)
#define TIM_DCR_DBL_Msk                          (0x1FUL<<TIM_DCR_DBL_Pos)                        /*!< 0x00001F00 */
#define TIM_DCR_DBL                              TIM_DCR_DBL_Msk
#define TIM_DCR_DBL_0                            (0x1UL<<TIM_DCR_DBL_Pos)                         /*!< 0x00000100 */
#define TIM_DCR_DBL_1                            (0x2UL<<TIM_DCR_DBL_Pos)                         /*!< 0x00000200 */
#define TIM_DCR_DBL_2                            (0x4UL<<TIM_DCR_DBL_Pos)                         /*!< 0x00000400 */
#define TIM_DCR_DBL_3                            (0x8UL<<TIM_DCR_DBL_Pos)                         /*!< 0x00000800 */
#define TIM_DCR_DBL_4                            (0x10UL<<TIM_DCR_DBL_Pos)                        /*!< 0x00001000 */

/********************************* Bit definition for TIM_DMAR register ********************************************/
#define TIM_DMAR_DMAB_Pos                        (0U)
#define TIM_DMAR_DMAB_Msk                        (0xFFFFFFFFUL<<TIM_DMAR_DMAB_Pos)                /*!< 0xFFFFFFFF */
#define TIM_DMAR_DMAB                            TIM_DMAR_DMAB_Msk

/********************************************************************************************************************/
/********************************* PWM ******************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for PWM_CR1 register **********************************************/
#define PWM_CR1_CEN_Pos                           (0U)
#define PWM_CR1_CEN_Msk                           (0x1UL<<PWM_CR1_CEN_Pos)                          /*!< 0x00000001 */
#define PWM_CR1_CEN                               PWM_CR1_CEN_Msk                                   
#define PWM_CR1_UDIS_Pos                          (1U)
#define PWM_CR1_UDIS_Msk                          (0x1UL<<PWM_CR1_UDIS_Pos)                         /*!< 0x00000002 */
#define PWM_CR1_UDIS                              PWM_CR1_UDIS_Msk                                  
#define PWM_CR1_URS_Pos                           (2U)
#define PWM_CR1_URS_Msk                           (0x1UL<<PWM_CR1_URS_Pos)                          /*!< 0x00000004 */
#define PWM_CR1_URS                               PWM_CR1_URS_Msk                                   
#define PWM_CR1_DIR_Pos                           (4U)
#define PWM_CR1_DIR_Msk                           (0x1UL<<PWM_CR1_DIR_Pos)                          /*!< 0x00000010 */
#define PWM_CR1_DIR                               PWM_CR1_DIR_Msk                                   
#define PWM_CR1_CMS_Pos                           (5U)
#define PWM_CR1_CMS_Msk                           (0x3UL<<PWM_CR1_CMS_Pos)                          /*!< 0x00000060 */
#define PWM_CR1_CMS                               PWM_CR1_CMS_Msk
#define PWM_CR1_CMS_0                             (0x1UL<<PWM_CR1_CMS_Pos)                          /*!< 0x00000020 */
#define PWM_CR1_CMS_1                             (0x2UL<<PWM_CR1_CMS_Pos)                          /*!< 0x00000040 */
#define PWM_CR1_ARPE_Pos                          (7U)
#define PWM_CR1_ARPE_Msk                          (0x1UL<<PWM_CR1_ARPE_Pos)                         /*!< 0x00000080 */
#define PWM_CR1_ARPE                              PWM_CR1_ARPE_Msk                                  
#define PWM_CR1_CKD_Pos                           (8U)
#define PWM_CR1_CKD_Msk                           (0x3UL<<PWM_CR1_CKD_Pos)                          /*!< 0x00000300 */
#define PWM_CR1_CKD                               PWM_CR1_CKD_Msk
#define PWM_CR1_CKD_0                             (0x1UL<<PWM_CR1_CKD_Pos)                          /*!< 0x00000100 */
#define PWM_CR1_CKD_1                             (0x2UL<<PWM_CR1_CKD_Pos)                          /*!< 0x00000200 */
#define PWM_CR1_INTR_SEL_Pos                      (12U)
#define PWM_CR1_INTR_SEL_Msk                      (0x3UL<<PWM_CR1_INTR_SEL_Pos)                    /*!< 0x000C0000 */
#define PWM_CR1_INTR_SEL                          PWM_CR1_INTR_SEL_Msk
#define PWM_CR1_INTR_SEL_0                        (0x1UL<<PWM_CR1_INTR_SEL_Pos)                    /*!< 0x00040000 */
#define PWM_CR1_INTR_SEL_1                        (0x2UL<<PWM_CR1_INTR_SEL_Pos)                    /*!< 0x00080000 */
#define PWM_CR1_PWM_PHS_EN_Pos                    (14U)
#define PWM_CR1_PWM_PHS_EN_Msk                    (0x1UL<<PWM_CR1_PWM_PHS_EN_Pos)                  /*!< 0x00100000 */
#define PWM_CR1_PWM_PHS_EN                        PWM_CR1_PWM_PHS_EN_Msk                           

/********************************* Bit definition for PWM_CR2 register **********************************************/
#define PWM_CR2_BKINE_Pos                         (0U)
#define PWM_CR2_BKINE_Msk                         (0x1UL<<PWM_CR2_BKINE_Pos)                        /*!< 0x00000001 */
#define PWM_CR2_BKINE                             PWM_CR2_BKINE_Msk                                 
#define PWM_CR2_BKCMP1E_Pos                       (1U)
#define PWM_CR2_BKCMP1E_Msk                       (0x1UL<<PWM_CR2_BKCMP1E_Pos)                      /*!< 0x00000002 */
#define PWM_CR2_BKCMP1E                           PWM_CR2_BKCMP1E_Msk                               
#define PWM_CR2_BKCMP2E_Pos                       (2U)
#define PWM_CR2_BKCMP2E_Msk                       (0x1UL<<PWM_CR2_BKCMP2E_Pos)                      /*!< 0x00000004 */
#define PWM_CR2_BKCMP2E                           PWM_CR2_BKCMP2E_Msk                               
#define PWM_CR2_BKINP_Pos                         (9U)
#define PWM_CR2_BKINP_Msk                         (0x1UL<<PWM_CR2_BKINP_Pos)                        /*!< 0x00000200 */
#define PWM_CR2_BKINP                             PWM_CR2_BKINP_Msk                                 
#define PWM_CR2_BKCMP1P_Pos                       (10U)
#define PWM_CR2_BKCMP1P_Msk                       (0x1UL<<PWM_CR2_BKCMP1P_Pos)                      /*!< 0x00000400 */
#define PWM_CR2_BKCMP1P                           PWM_CR2_BKCMP1P_Msk                               
#define PWM_CR2_BKCMP2P_Pos                       (11U)
#define PWM_CR2_BKCMP2P_Msk                       (0x1UL<<PWM_CR2_BKCMP2P_Pos)                      /*!< 0x00000800 */
#define PWM_CR2_BKCMP2P                           PWM_CR2_BKCMP2P_Msk                               
#define PWM_CR2_ETRSEL_Pos                        (13U)
#define PWM_CR2_ETRSEL_Msk                        (0x7UL<<PWM_CR2_ETRSEL_Pos)                       /*!< 0x0000E000 */
#define PWM_CR2_ETRSEL                            PWM_CR2_ETRSEL_Msk
#define PWM_CR2_ETRSEL_0                          (0x1UL<<PWM_CR2_ETRSEL_Pos)                       /*!< 0x00002000 */
#define PWM_CR2_ETRSEL_1                          (0x2UL<<PWM_CR2_ETRSEL_Pos)                       /*!< 0x00004000 */
#define PWM_CR2_ETRSEL_2                          (0x4UL<<PWM_CR2_ETRSEL_Pos)                       /*!< 0x00008000 */

/********************************* Bit definition for PWM_SMCR register *********************************************/
#define PWM_SMCR_ETF_Pos                          (8U)
#define PWM_SMCR_ETF_Msk                          (0xFUL<<PWM_SMCR_ETF_Pos)                         /*!< 0x00000F00 */
#define PWM_SMCR_ETF                              PWM_SMCR_ETF_Msk
#define PWM_SMCR_ETF_0                            (0x1UL<<PWM_SMCR_ETF_Pos)                         /*!< 0x00000100 */
#define PWM_SMCR_ETF_1                            (0x2UL<<PWM_SMCR_ETF_Pos)                         /*!< 0x00000200 */
#define PWM_SMCR_ETF_2                            (0x4UL<<PWM_SMCR_ETF_Pos)                         /*!< 0x00000400 */
#define PWM_SMCR_ETF_3                            (0x8UL<<PWM_SMCR_ETF_Pos)                         /*!< 0x00000800 */
#define PWM_SMCR_ETPS_Pos                         (12U)
#define PWM_SMCR_ETPS_Msk                         (0x3UL<<PWM_SMCR_ETPS_Pos)                        /*!< 0x00003000 */
#define PWM_SMCR_ETPS                             PWM_SMCR_ETPS_Msk
#define PWM_SMCR_ETPS_0                           (0x1UL<<PWM_SMCR_ETPS_Pos)                        /*!< 0x00001000 */
#define PWM_SMCR_ETPS_1                           (0x2UL<<PWM_SMCR_ETPS_Pos)                        /*!< 0x00002000 */
#define PWM_SMCR_ECE_Pos                          (14U)
#define PWM_SMCR_ECE_Msk                          (0x1UL<<PWM_SMCR_ECE_Pos)                         /*!< 0x00004000 */
#define PWM_SMCR_ECE                              PWM_SMCR_ECE_Msk                                  
#define PWM_SMCR_ETP_Pos                          (15U)
#define PWM_SMCR_ETP_Msk                          (0x1UL<<PWM_SMCR_ETP_Pos)                         /*!< 0x00008000 */
#define PWM_SMCR_ETP                              PWM_SMCR_ETP_Msk                                  

/********************************* Bit definition for PWM_DIER register *********************************************/
#define PWM_DIER_UIE_Pos                          (0U)
#define PWM_DIER_UIE_Msk                          (0x1UL<<PWM_DIER_UIE_Pos)                         /*!< 0x00000001 */
#define PWM_DIER_UIE                              PWM_DIER_UIE_Msk                                  
#define PWM_DIER_OC1IE_Pos                        (1U)
#define PWM_DIER_OC1IE_Msk                        (0x1UL<<PWM_DIER_OC1IE_Pos)                       /*!< 0x00000002 */
#define PWM_DIER_OC1IE                            PWM_DIER_OC1IE_Msk                                
#define PWM_DIER_OC2IE_Pos                        (2U)
#define PWM_DIER_OC2IE_Msk                        (0x1UL<<PWM_DIER_OC2IE_Pos)                       /*!< 0x00000004 */
#define PWM_DIER_OC2IE                            PWM_DIER_OC2IE_Msk                                
#define PWM_DIER_OC3IE_Pos                        (3U)
#define PWM_DIER_OC3IE_Msk                        (0x1UL<<PWM_DIER_OC3IE_Pos)                       /*!< 0x00000008 */
#define PWM_DIER_OC3IE                            PWM_DIER_OC3IE_Msk                                
#define PWM_DIER_OC4IE_Pos                        (4U)
#define PWM_DIER_OC4IE_Msk                        (0x1UL<<PWM_DIER_OC4IE_Pos)                       /*!< 0x00000010 */
#define PWM_DIER_OC4IE                            PWM_DIER_OC4IE_Msk                                
#define PWM_DIER_BIE_Pos                          (7U)
#define PWM_DIER_BIE_Msk                          (0x1UL<<PWM_DIER_BIE_Pos)                         /*!< 0x00000080 */
#define PWM_DIER_BIE                              PWM_DIER_BIE_Msk                                  
#define PWM_DIER_UDE_Pos                          (8U)
#define PWM_DIER_UDE_Msk                          (0x1UL<<PWM_DIER_UDE_Pos)                         /*!< 0x00000100 */
#define PWM_DIER_UDE                              PWM_DIER_UDE_Msk                                  
#define PWM_DIER_OC1DE_Pos                        (9U)
#define PWM_DIER_OC1DE_Msk                        (0x1UL<<PWM_DIER_OC1DE_Pos)                       /*!< 0x00000200 */
#define PWM_DIER_OC1DE                            PWM_DIER_OC1DE_Msk                                
#define PWM_DIER_OC2DE_Pos                        (10U)
#define PWM_DIER_OC2DE_Msk                        (0x1UL<<PWM_DIER_OC2DE_Pos)                       /*!< 0x00000400 */
#define PWM_DIER_OC2DE                            PWM_DIER_OC2DE_Msk                                
#define PWM_DIER_OC3DE_Pos                        (11U)
#define PWM_DIER_OC3DE_Msk                        (0x1UL<<PWM_DIER_OC3DE_Pos)                       /*!< 0x00000800 */
#define PWM_DIER_OC3DE                            PWM_DIER_OC3DE_Msk                                
#define PWM_DIER_OC4DE_Pos                        (12U)
#define PWM_DIER_OC4DE_Msk                        (0x1UL<<PWM_DIER_OC4DE_Pos)                       /*!< 0x00001000 */
#define PWM_DIER_OC4DE                            PWM_DIER_OC4DE_Msk                                

/********************************* Bit definition for PWM_SR register ***********************************************/
#define PWM_SR_UIF_Pos                            (0U)
#define PWM_SR_UIF_Msk                            (0x1UL<<PWM_SR_UIF_Pos)                           /*!< 0x00000001 */
#define PWM_SR_UIF                                PWM_SR_UIF_Msk                                    
#define PWM_SR_OC1IF_Pos                          (1U)
#define PWM_SR_OC1IF_Msk                          (0x1UL<<PWM_SR_OC1IF_Pos)                         /*!< 0x00000002 */
#define PWM_SR_OC1IF                              PWM_SR_OC1IF_Msk                                  
#define PWM_SR_OC2IF_Pos                          (2U)
#define PWM_SR_OC2IF_Msk                          (0x1UL<<PWM_SR_OC2IF_Pos)                         /*!< 0x00000004 */
#define PWM_SR_OC2IF                              PWM_SR_OC2IF_Msk                                  
#define PWM_SR_OC3IF_Pos                          (3U)
#define PWM_SR_OC3IF_Msk                          (0x1UL<<PWM_SR_OC3IF_Pos)                         /*!< 0x00000008 */
#define PWM_SR_OC3IF                              PWM_SR_OC3IF_Msk                                  
#define PWM_SR_OC4IF_Pos                          (4U)
#define PWM_SR_OC4IF_Msk                          (0x1UL<<PWM_SR_OC4IF_Pos)                         /*!< 0x00000010 */
#define PWM_SR_OC4IF                              PWM_SR_OC4IF_Msk                                  
#define PWM_SR_BIF_Pos                            (7U)
#define PWM_SR_BIF_Msk                            (0x1UL<<PWM_SR_BIF_Pos)                           /*!< 0x00000080 */
#define PWM_SR_BIF                                PWM_SR_BIF_Msk                                    
#define PWM_SR_CCR1OK_Pos                         (9U)
#define PWM_SR_CCR1OK_Msk                         (0x1UL<<PWM_SR_CCR1OK_Pos)                        /*!< 0x00000200 */
#define PWM_SR_CCR1OK                             PWM_SR_CCR1OK_Msk                                 
#define PWM_SR_CCR2OK_Pos                         (10U)
#define PWM_SR_CCR2OK_Msk                         (0x1UL<<PWM_SR_CCR2OK_Pos)                        /*!< 0x00000400 */
#define PWM_SR_CCR2OK                             PWM_SR_CCR2OK_Msk                                 
#define PWM_SR_CCR3OK_Pos                         (11U)
#define PWM_SR_CCR3OK_Msk                         (0x1UL<<PWM_SR_CCR3OK_Pos)                        /*!< 0x00000800 */
#define PWM_SR_CCR3OK                             PWM_SR_CCR3OK_Msk                                 
#define PWM_SR_CCR4OK_Pos                         (12U)
#define PWM_SR_CCR4OK_Msk                         (0x1UL<<PWM_SR_CCR4OK_Pos)                        /*!< 0x00001000 */
#define PWM_SR_CCR4OK                             PWM_SR_CCR4OK_Msk                                 
#define PWM_SR_CNTOK_Pos                          (13U)
#define PWM_SR_CNTOK_Msk                          (0x1UL<<PWM_SR_CNTOK_Pos)                         /*!< 0x00002000 */
#define PWM_SR_CNTOK                              PWM_SR_CNTOK_Msk                                  
#define PWM_SR_PSCOK_Pos                          (14U)
#define PWM_SR_PSCOK_Msk                          (0x1UL<<PWM_SR_PSCOK_Pos)                         /*!< 0x00004000 */
#define PWM_SR_PSCOK                              PWM_SR_PSCOK_Msk                                  
#define PWM_SR_ARROK_Pos                          (15U)
#define PWM_SR_ARROK_Msk                          (0x1UL<<PWM_SR_ARROK_Pos)                         /*!< 0x00008000 */
#define PWM_SR_ARROK                              PWM_SR_ARROK_Msk                                  

/********************************* Bit definition for PWM_EGR register **********************************************/
#define PWM_EGR_UG_Pos                            (0U)
#define PWM_EGR_UG_Msk                            (0x1UL<<PWM_EGR_UG_Pos)                           /*!< 0x00000001 */
#define PWM_EGR_UG                                PWM_EGR_UG_Msk                                    

/********************************* Bit definition for PWM_CMR register **********************************************/
#define PWM_CMR_OC1M_Pos                          (0U)
#define PWM_CMR_OC1M_Msk                          (0x3UL<<PWM_CMR_OC1M_Pos)                         /*!< 0x00000003 */
#define PWM_CMR_OC1M                              PWM_CMR_OC1M_Msk
#define PWM_CMR_OC1M_0                            (0x1UL<<PWM_CMR_OC1M_Pos)                         /*!< 0x00000001 */
#define PWM_CMR_OC1M_1                            (0x2UL<<PWM_CMR_OC1M_Pos)                         /*!< 0x00000002 */
#define PWM_CMR_OC2M_Pos                          (2U)
#define PWM_CMR_OC2M_Msk                          (0x3UL<<PWM_CMR_OC2M_Pos)                         /*!< 0x0000000C */
#define PWM_CMR_OC2M                              PWM_CMR_OC2M_Msk
#define PWM_CMR_OC2M_0                            (0x1UL<<PWM_CMR_OC2M_Pos)                         /*!< 0x00000004 */
#define PWM_CMR_OC2M_1                            (0x2UL<<PWM_CMR_OC2M_Pos)                         /*!< 0x00000008 */
#define PWM_CMR_OC3M_Pos                          (4U)
#define PWM_CMR_OC3M_Msk                          (0x3UL<<PWM_CMR_OC3M_Pos)                         /*!< 0x00000030 */
#define PWM_CMR_OC3M                              PWM_CMR_OC3M_Msk
#define PWM_CMR_OC3M_0                            (0x1UL<<PWM_CMR_OC3M_Pos)                         /*!< 0x00000010 */
#define PWM_CMR_OC3M_1                            (0x2UL<<PWM_CMR_OC3M_Pos)                         /*!< 0x00000020 */
#define PWM_CMR_OC4M_Pos                          (6U)
#define PWM_CMR_OC4M_Msk                          (0x3UL<<PWM_CMR_OC4M_Pos)                         /*!< 0x000000C0 */
#define PWM_CMR_OC4M                              PWM_CMR_OC4M_Msk
#define PWM_CMR_OC4M_0                            (0x1UL<<PWM_CMR_OC4M_Pos)                         /*!< 0x00000040 */
#define PWM_CMR_OC4M_1                            (0x2UL<<PWM_CMR_OC4M_Pos)                         /*!< 0x00000080 */
#define PWM_CMR_OC1PE_Pos                         (8U)
#define PWM_CMR_OC1PE_Msk                         (0x1UL<<PWM_CMR_OC1PE_Pos)                        /*!< 0x00000100 */
#define PWM_CMR_OC1PE                             PWM_CMR_OC1PE_Msk                                 
#define PWM_CMR_OC2PE_Pos                         (9U)
#define PWM_CMR_OC2PE_Msk                         (0x1UL<<PWM_CMR_OC2PE_Pos)                        /*!< 0x00000200 */
#define PWM_CMR_OC2PE                             PWM_CMR_OC2PE_Msk                                 
#define PWM_CMR_OC3PE_Pos                         (10U)
#define PWM_CMR_OC3PE_Msk                         (0x1UL<<PWM_CMR_OC3PE_Pos)                        /*!< 0x00000400 */
#define PWM_CMR_OC3PE                             PWM_CMR_OC3PE_Msk                                 
#define PWM_CMR_OC4PE_Pos                         (11U)
#define PWM_CMR_OC4PE_Msk                         (0x1UL<<PWM_CMR_OC4PE_Pos)                        /*!< 0x00000800 */
#define PWM_CMR_OC4PE                             PWM_CMR_OC4PE_Msk                                 

/********************************* Bit definition for PWM_CER register **********************************************/
#define PWM_CER_C1E_Pos                           (0U)
#define PWM_CER_C1E_Msk                           (0x1UL<<PWM_CER_C1E_Pos)                          /*!< 0x00000001 */
#define PWM_CER_C1E                               PWM_CER_C1E_Msk                                   
#define PWM_CER_C1P_Pos                           (1U)
#define PWM_CER_C1P_Msk                           (0x1UL<<PWM_CER_C1P_Pos)                          /*!< 0x00000002 */
#define PWM_CER_C1P                               PWM_CER_C1P_Msk                                   
#define PWM_CER_C1NE_Pos                          (2U)
#define PWM_CER_C1NE_Msk                          (0x1UL<<PWM_CER_C1NE_Pos)                         /*!< 0x00000004 */
#define PWM_CER_C1NE                              PWM_CER_C1NE_Msk                                  
#define PWM_CER_C1NP_Pos                          (3U)
#define PWM_CER_C1NP_Msk                          (0x1UL<<PWM_CER_C1NP_Pos)                         /*!< 0x00000008 */
#define PWM_CER_C1NP                              PWM_CER_C1NP_Msk                                  
#define PWM_CER_C2E_Pos                           (4U)
#define PWM_CER_C2E_Msk                           (0x1UL<<PWM_CER_C2E_Pos)                          /*!< 0x00000010 */
#define PWM_CER_C2E                               PWM_CER_C2E_Msk                                   
#define PWM_CER_C2P_Pos                           (5U)
#define PWM_CER_C2P_Msk                           (0x1UL<<PWM_CER_C2P_Pos)                          /*!< 0x00000020 */
#define PWM_CER_C2P                               PWM_CER_C2P_Msk                                   
#define PWM_CER_C2NE_Pos                          (6U)
#define PWM_CER_C2NE_Msk                          (0x1UL<<PWM_CER_C2NE_Pos)                         /*!< 0x00000040 */
#define PWM_CER_C2NE                              PWM_CER_C2NE_Msk                                  
#define PWM_CER_C2NP_Pos                          (7U)
#define PWM_CER_C2NP_Msk                          (0x1UL<<PWM_CER_C2NP_Pos)                         /*!< 0x00000080 */
#define PWM_CER_C2NP                              PWM_CER_C2NP_Msk                                  
#define PWM_CER_C3E_Pos                           (8U)
#define PWM_CER_C3E_Msk                           (0x1UL<<PWM_CER_C3E_Pos)                          /*!< 0x00000100 */
#define PWM_CER_C3E                               PWM_CER_C3E_Msk                                   
#define PWM_CER_C3P_Pos                           (9U)
#define PWM_CER_C3P_Msk                           (0x1UL<<PWM_CER_C3P_Pos)                          /*!< 0x00000200 */
#define PWM_CER_C3P                               PWM_CER_C3P_Msk                                   
#define PWM_CER_C4E_Pos                           (12U)
#define PWM_CER_C4E_Msk                           (0x1UL<<PWM_CER_C4E_Pos)                          /*!< 0x00001000 */
#define PWM_CER_C4E                               PWM_CER_C4E_Msk                                   
#define PWM_CER_C4P_Pos                           (13U)
#define PWM_CER_C4P_Msk                           (0x1UL<<PWM_CER_C4P_Pos)                          /*!< 0x00002000 */
#define PWM_CER_C4P                               PWM_CER_C4P_Msk                                   

/********************************* Bit definition for PWM_CNT register **********************************************/
#define PWM_CNT_CNT_Pos                           (0U)
#define PWM_CNT_CNT_Msk                           (0xFFFFUL<<PWM_CNT_CNT_Pos)                       /*!< 0x0000FFFF */
#define PWM_CNT_CNT                               PWM_CNT_CNT_Msk

/********************************* Bit definition for PWM_PSC register **********************************************/
#define PWM_PSC_PSC_Pos                           (0U)
#define PWM_PSC_PSC_Msk                           (0xFFFFUL<<PWM_PSC_PSC_Pos)                       /*!< 0x0000FFFF */
#define PWM_PSC_PSC                               PWM_PSC_PSC_Msk

/********************************* Bit definition for PWM_ARR register **********************************************/
#define PWM_ARR_ARR_Pos                           (0U)
#define PWM_ARR_ARR_Msk                           (0xFFFFUL<<PWM_ARR_ARR_Pos)                       /*!< 0x0000FFFF */
#define PWM_ARR_ARR                               PWM_ARR_ARR_Msk

/********************************* Bit definition for PWM_CCR1 register *********************************************/
#define PWM_CCR1_CCR1_Pos                         (0U)
#define PWM_CCR1_CCR1_Msk                         (0xFFFFUL<<PWM_CCR1_CCR1_Pos)                     /*!< 0x0000FFFF */
#define PWM_CCR1_CCR1                             PWM_CCR1_CCR1_Msk
#define PWM_CCR1_CCR1_H_Pos                       (16U)
#define PWM_CCR1_CCR1_H_Msk                       (0xFFFFUL<<PWM_CCR1_CCR1_H_Pos)                  /*!< 0xFFFF0000 */
#define PWM_CCR1_CCR1_H                           PWM_CCR1_CCR1_H_Msk

/********************************* Bit definition for PWM_CCR2 register *********************************************/
#define PWM_CCR2_CCR2_Pos                         (0U)
#define PWM_CCR2_CCR2_Msk                         (0xFFFFUL<<PWM_CCR2_CCR2_Pos)                     /*!< 0x0000FFFF */
#define PWM_CCR2_CCR2                             PWM_CCR2_CCR2_Msk
#define PWM_CCR2_CCR2_H_Pos                       (16U)
#define PWM_CCR2_CCR2_H_Msk                       (0xFFFFUL<<PWM_CCR2_CCR2_H_Pos)                  /*!< 0xFFFF0000 */
#define PWM_CCR2_CCR2_H                           PWM_CCR2_CCR2_H_Msk

/********************************* Bit definition for PWM_CCR3 register *********************************************/
#define PWM_CCR3_CCR3_Pos                         (0U)
#define PWM_CCR3_CCR3_Msk                         (0xFFFFUL<<PWM_CCR3_CCR3_Pos)                     /*!< 0x0000FFFF */
#define PWM_CCR3_CCR3                             PWM_CCR3_CCR3_Msk

/********************************* Bit definition for PWM_CCR4 register *********************************************/
#define PWM_CCR4_CCR4_Pos                         (0U)
#define PWM_CCR4_CCR4_Msk                         (0xFFFFUL<<PWM_CCR4_CCR4_Pos)                     /*!< 0x0000FFFF */
#define PWM_CCR4_CCR4                             PWM_CCR4_CCR4_Msk

/********************************* Bit definition for PWM_BDTR register *********************************************/
#define PWM_BDTR_DTG_Pos                          (0U)
#define PWM_BDTR_DTG_Msk                          (0xFFUL<<PWM_BDTR_DTG_Pos)                        /*!< 0x000000FF */
#define PWM_BDTR_DTG                              PWM_BDTR_DTG_Msk
#define PWM_BDTR_LOCK_Pos                         (8U)
#define PWM_BDTR_LOCK_Msk                         (0x3UL<<PWM_BDTR_LOCK_Pos)                        /*!< 0x00000300 */
#define PWM_BDTR_LOCK                             PWM_BDTR_LOCK_Msk
#define PWM_BDTR_LOCK_0                           (0x1UL<<PWM_BDTR_LOCK_Pos)                        /*!< 0x00000100 */
#define PWM_BDTR_LOCK_1                           (0x2UL<<PWM_BDTR_LOCK_Pos)                        /*!< 0x00000200 */
#define PWM_BDTR_BKE_Pos                          (12U)
#define PWM_BDTR_BKE_Msk                          (0x1UL<<PWM_BDTR_BKE_Pos)                         /*!< 0x00001000 */
#define PWM_BDTR_BKE                              PWM_BDTR_BKE_Msk                                  
#define PWM_BDTR_BKP_Pos                          (13U)
#define PWM_BDTR_BKP_Msk                          (0x1UL<<PWM_BDTR_BKP_Pos)                         /*!< 0x00002000 */
#define PWM_BDTR_BKP                              PWM_BDTR_BKP_Msk                                  
#define PWM_BDTR_AOE_Pos                          (14U)
#define PWM_BDTR_AOE_Msk                          (0x1UL<<PWM_BDTR_AOE_Pos)                         /*!< 0x00004000 */
#define PWM_BDTR_AOE                              PWM_BDTR_AOE_Msk                                  
#define PWM_BDTR_MOE_Pos                          (15U)
#define PWM_BDTR_MOE_Msk                          (0x1UL<<PWM_BDTR_MOE_Pos)                         /*!< 0x00008000 */
#define PWM_BDTR_MOE                              PWM_BDTR_MOE_Msk                                  

/********************************* Bit definition for PWM_DCR register **********************************************/
#define PWM_DCR_DBA_Pos                           (0U)
#define PWM_DCR_DBA_Msk                           (0x1FUL<<PWM_DCR_DBA_Pos)                         /*!< 0x0000001F */
#define PWM_DCR_DBA                               PWM_DCR_DBA_Msk
#define PWM_DCR_DBA_0                             (0x1UL<<PWM_DCR_DBA_Pos)                          /*!< 0x00000001 */
#define PWM_DCR_DBA_1                             (0x2UL<<PWM_DCR_DBA_Pos)                          /*!< 0x00000002 */
#define PWM_DCR_DBA_2                             (0x4UL<<PWM_DCR_DBA_Pos)                          /*!< 0x00000004 */
#define PWM_DCR_DBA_3                             (0x8UL<<PWM_DCR_DBA_Pos)                          /*!< 0x00000008 */
#define PWM_DCR_DBA_4                             (0x10UL<<PWM_DCR_DBA_Pos)                         /*!< 0x00000010 */
#define PWM_DCR_DBL_Pos                           (8U)
#define PWM_DCR_DBL_Msk                           (0x1FUL<<PWM_DCR_DBL_Pos)                         /*!< 0x00001F00 */
#define PWM_DCR_DBL                               PWM_DCR_DBL_Msk
#define PWM_DCR_DBL_0                             (0x1UL<<PWM_DCR_DBL_Pos)                          /*!< 0x00000100 */
#define PWM_DCR_DBL_1                             (0x2UL<<PWM_DCR_DBL_Pos)                          /*!< 0x00000200 */
#define PWM_DCR_DBL_2                             (0x4UL<<PWM_DCR_DBL_Pos)                          /*!< 0x00000400 */
#define PWM_DCR_DBL_3                             (0x8UL<<PWM_DCR_DBL_Pos)                          /*!< 0x00000800 */
#define PWM_DCR_DBL_4                             (0x10UL<<PWM_DCR_DBL_Pos)                         /*!< 0x00001000 */

/********************************* Bit definition for PWM_DMAR register *********************************************/
#define PWM_DMAR_DMAB_Pos                         (0U)
#define PWM_DMAR_DMAB_Msk                         (0xFFFFFFFFUL<<PWM_DMAR_DMAB_Pos)                 /*!< 0xFFFFFFFF */
#define PWM_DMAR_DMAB                             PWM_DMAR_DMAB_Msk

/********************************************************************************************************************/
/********************************* USART ****************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for USART_SR register *********************************************/
#define USART_SR_PE_Pos                           (0U)
#define USART_SR_PE_Msk                           (0x1UL<<USART_SR_PE_Pos)                          /*!< 0x00000001 */
#define USART_SR_PE                               USART_SR_PE_Msk                                   /*!< Parity error */
#define USART_SR_FE_Pos                           (1U)
#define USART_SR_FE_Msk                           (0x1UL<<USART_SR_FE_Pos)                          /*!< 0x00000002 */
#define USART_SR_FE                               USART_SR_FE_Msk                                   /*!< Framing error */
#define USART_SR_NE_Pos                           (2U)
#define USART_SR_NE_Msk                           (0x1UL<<USART_SR_NE_Pos)                          /*!< 0x00000004 */
#define USART_SR_NE                               USART_SR_NE_Msk                                   /*!< Noise error flag */
#define USART_SR_ORE_Pos                          (3U)
#define USART_SR_ORE_Msk                          (0x1UL<<USART_SR_ORE_Pos)                         /*!< 0x00000008 */
#define USART_SR_ORE                              USART_SR_ORE_Msk                                  /*!< overrun error */
#define USART_SR_IDLE_Pos                         (4U)
#define USART_SR_IDLE_Msk                         (0x1UL<<USART_SR_IDLE_Pos)                        /*!< 0x00000010 */
#define USART_SR_IDLE                             USART_SR_IDLE_Msk                                 /*!< idle */
#define USART_SR_RXNE_Pos                         (5U)
#define USART_SR_RXNE_Msk                         (0x1UL<<USART_SR_RXNE_Pos)                        /*!< 0x00000020 */
#define USART_SR_RXNE                             USART_SR_RXNE_Msk                                 /*!< Read data register not empty */
#define USART_SR_RXNE_RXFNF_Pos                   USART_SR_RXNE_Pos
#define USART_SR_RXNE_RXFNF_Msk                   USART_SR_RXNE_Msk
#define USART_SR_RXNE_RXFNF                       USART_SR_RXNE_Msk                                 /*!< Read data register not empty */
#define USART_SR_TC_Pos                           (6U)
#define USART_SR_TC_Msk                           (0x1UL<<USART_SR_TC_Pos)                          /*!< 0x00000040 */
#define USART_SR_TC                               USART_SR_TC_Msk                                   /*!< Transmission complete */
#define USART_SR_TXE_Pos                          (7U)
#define USART_SR_TXE_Msk                          (0x1UL<<USART_SR_TXE_Pos)                         /*!< 0x00000080 */
#define USART_SR_TXE                              USART_SR_TXE_Msk                                  /*!< Transmit data register empty */
#define USART_SR_TXE_TXFNF_Pos                    USART_SR_TXE_Pos
#define USART_SR_TXE_TXFNF_Msk                    USART_SR_TXE_Msk
#define USART_SR_TXE_TXFNF                        USART_SR_TXE_Msk                                  /*!< Transmit data register empty */
#define USART_SR_LBD_Pos                          (8U)
#define USART_SR_LBD_Msk                          (0x1UL<<USART_SR_LBD_Pos)                         /*!< 0x00000100 */
#define USART_SR_LBD                              USART_SR_LBD_Msk                                  /*!< LIN break detection flag */
#define USART_SR_CTS_Pos                          (9U)
#define USART_SR_CTS_Msk                          (0x1UL<<USART_SR_CTS_Pos)                         /*!< 0x00000200 */
#define USART_SR_CTS                              USART_SR_CTS_Msk                                  /*!< cts flag */
#define USART_SR_ABRF_Pos                         (10U)
#define USART_SR_ABRF_Msk                         (0x1UL<<USART_SR_ABRF_Pos)                        /*!< 0x00000400 */
#define USART_SR_ABRF                             USART_SR_ABRF_Msk                                 /*!< auto baud rate flag */
#define USART_SR_ABRE_Pos                         (11U)
#define USART_SR_ABRE_Msk                         (0x1UL<<USART_SR_ABRE_Pos)                        /*!< 0x00000800 */
#define USART_SR_ABRE                             USART_SR_ABRE_Msk                                 /*!< auto baud rateerror */
#define USART_SR_ABRRQ_Pos                        (12U)
#define USART_SR_ABRRQ_Msk                        (0x1UL<<USART_SR_ABRRQ_Pos)                       /*!< 0x00001000 */
#define USART_SR_ABRRQ                            USART_SR_ABRRQ_Msk                                /*!< auto baud rate req */
#define USART_SR_TXFT_Pos                         (13U)
#define USART_SR_TXFT_Msk                         (0x1UL<<USART_SR_TXFT_Pos)                        /*!< 0x00002000 */
#define USART_SR_TXFT                             USART_SR_TXFT_Msk                                 /*!< txfifo threshold flag  */
#define USART_SR_RXFT_Pos                         (14U)
#define USART_SR_RXFT_Msk                         (0x1UL<<USART_SR_RXFT_Pos)                        /*!< 0x00004000 */
#define USART_SR_RXFT                             USART_SR_RXFT_Msk                                 /*!< rxfifo threshoold flag  */
#define USART_SR_RXFF_Pos                         (15U)
#define USART_SR_RXFF_Msk                         (0x1UL<<USART_SR_RXFF_Pos)                        /*!< 0x00008000 */
#define USART_SR_RXFF                             USART_SR_RXFF_Msk                                 /*!< rxfifo full */
#define USART_SR_TXFE_Pos                         (16U)
#define USART_SR_TXFE_Msk                         (0x1UL<<USART_SR_TXFE_Pos)                        /*!< 0x00010000 */
#define USART_SR_TXFE                             USART_SR_TXFE_Msk                                 /*!< txfifo empty */
#define USART_SR_EOBF_Pos                         (18U)
#define USART_SR_EOBF_Msk                         (0x1UL<<USART_SR_EOBF_Pos)                        /*!< 0x00040000 */
#define USART_SR_EOBF                             USART_SR_EOBF_Msk                                 /*!< end of block flag */
#define USART_SR_RTOF_Pos                         (19U)
#define USART_SR_RTOF_Msk                         (0x1UL<<USART_SR_RTOF_Pos)                        /*!< 0x00080000 */
#define USART_SR_RTOF                             USART_SR_RTOF_Msk                                 /*!< rto flag */

/********************************* Bit definition for USART_DR register *********************************************/
#define USART_DR_DR_Pos                           (0U)
#define USART_DR_DR_Msk                           (0x1FFUL<<USART_DR_DR_Pos)                        /*!< 0x000001FF */
#define USART_DR_DR                               USART_DR_DR_Msk                                   /*!< DR */

/********************************* Bit definition for USART_BRR register ********************************************/
#define USART_BRR_DIV_F_Pos                       (0U)
#define USART_BRR_DIV_F_Msk                       (0xFUL<<USART_BRR_DIV_F_Pos)                      /*!< 0x0000000F */
#define USART_BRR_DIV_F                           USART_BRR_DIV_F_Msk                               /*!< DIV_Fraction */
#define USART_BRR_DIV_F_0                         (0x1UL<<USART_BRR_DIV_F_Pos)                      /*!< 0x00000001 */
#define USART_BRR_DIV_F_1                         (0x2UL<<USART_BRR_DIV_F_Pos)                      /*!< 0x00000002 */
#define USART_BRR_DIV_F_2                         (0x4UL<<USART_BRR_DIV_F_Pos)                      /*!< 0x00000004 */
#define USART_BRR_DIV_F_3                         (0x8UL<<USART_BRR_DIV_F_Pos)                      /*!< 0x00000008 */
#define USART_BRR_DIV_M_Pos                       (4U)
#define USART_BRR_DIV_M_Msk                       (0xFFFUL<<USART_BRR_DIV_M_Pos)                    /*!< 0x0000FFF0 */
#define USART_BRR_DIV_M                           USART_BRR_DIV_M_Msk                               /*!< DIV_Mantissa */

/********************************* Bit definition for USART_CR1 register ********************************************/
#define USART_CR1_SBK_Pos                         (0U)
#define USART_CR1_SBK_Msk                         (0x1UL<<USART_CR1_SBK_Pos)                        /*!< 0x00000001 */
#define USART_CR1_SBK                             USART_CR1_SBK_Msk                                 /*!< Send break */
#define USART_CR1_RWU_Pos                         (1U)
#define USART_CR1_RWU_Msk                         (0x1UL<<USART_CR1_RWU_Pos)                        /*!< 0x00000002 */
#define USART_CR1_RWU                             USART_CR1_RWU_Msk                                 /*!< Receiver wakeup */
#define USART_CR1_RE_Pos                          (2U)
#define USART_CR1_RE_Msk                          (0x1UL<<USART_CR1_RE_Pos)                         /*!< 0x00000004 */
#define USART_CR1_RE                              USART_CR1_RE_Msk                                  /*!< Receiver enable */
#define USART_CR1_TE_Pos                          (3U)
#define USART_CR1_TE_Msk                          (0x1UL<<USART_CR1_TE_Pos)                         /*!< 0x00000008 */
#define USART_CR1_TE                              USART_CR1_TE_Msk                                  /*!< Transmitter enable */
#define USART_CR1_IDLEIE_Pos                      (4U)
#define USART_CR1_IDLEIE_Msk                      (0x1UL<<USART_CR1_IDLEIE_Pos)                     /*!< 0x00000010 */
#define USART_CR1_IDLEIE                          USART_CR1_IDLEIE_Msk                              /*!< IDLE interrupt enable */
#define USART_CR1_RXNEIE_Pos                      (5U)
#define USART_CR1_RXNEIE_Msk                      (0x1UL<<USART_CR1_RXNEIE_Pos)                     /*!< 0x00000020 */
#define USART_CR1_RXNEIE                          USART_CR1_RXNEIE_Msk                              /*!< RXNE interrupt enable */
#define USART_CR1_TCIE_Pos                        (6U)
#define USART_CR1_TCIE_Msk                        (0x1UL<<USART_CR1_TCIE_Pos)                       /*!< 0x00000040 */
#define USART_CR1_TCIE                            USART_CR1_TCIE_Msk                                /*!< send complete int enable */
#define USART_CR1_TXEIE_Pos                       (7U)
#define USART_CR1_TXEIE_Msk                       (0x1UL<<USART_CR1_TXEIE_Pos)                      /*!< 0x00000080 */
#define USART_CR1_TXEIE                           USART_CR1_TXEIE_Msk                               /*!< txe  */
#define USART_CR1_PEIE_Pos                        (8U)
#define USART_CR1_PEIE_Msk                        (0x1UL<<USART_CR1_PEIE_Pos)                       /*!< 0x00000100 */
#define USART_CR1_PEIE                            USART_CR1_PEIE_Msk                                /*!< PE interrupt enable */
#define USART_CR1_PS_Pos                          (9U)
#define USART_CR1_PS_Msk                          (0x1UL<<USART_CR1_PS_Pos)                         /*!< 0x00000200 */
#define USART_CR1_PS                              USART_CR1_PS_Msk                                  /*!< Parity selection */
#define USART_CR1_PCE_Pos                         (10U)
#define USART_CR1_PCE_Msk                         (0x1UL<<USART_CR1_PCE_Pos)                        /*!< 0x00000400 */
#define USART_CR1_PCE                             USART_CR1_PCE_Msk                                 /*!< Parity control enable */
#define USART_CR1_WAKE_Pos                        (11U)
#define USART_CR1_WAKE_Msk                        (0x1UL<<USART_CR1_WAKE_Pos)                       /*!< 0x00000800 */
#define USART_CR1_WAKE                            USART_CR1_WAKE_Msk                                /*!< Wakeup method */
#define USART_CR1_M0_Pos                          (12U)
#define USART_CR1_M0_Msk                          (0x1UL<<USART_CR1_M0_Pos)                         /*!< 0x00001000 */
#define USART_CR1_M0                              USART_CR1_M0_Msk                                  /*!< word length */
#define USART_CR1_UE_Pos                          (13U)
#define USART_CR1_UE_Msk                          (0x1UL<<USART_CR1_UE_Pos)                         /*!< 0x00002000 */
#define USART_CR1_UE                              USART_CR1_UE_Msk                                  /*!< uesart enable  */
#define USART_CR1_M1_Pos                          (14U)
#define USART_CR1_M1_Msk                          (0x1UL<<USART_CR1_M1_Pos)                         /*!< 0x00004000 */
#define USART_CR1_M1                              USART_CR1_M1_Msk                                  /*!< word length */
#define USART_CR1_MSB_Pos                         (15U)
#define USART_CR1_MSB_Msk                         (0x1UL<<USART_CR1_MSB_Pos)                        /*!< 0x00008000 */
#define USART_CR1_MSB                             USART_CR1_MSB_Msk                                 /*!< msb */
#define USART_CR1_ADDM7_Pos                       (17U)
#define USART_CR1_ADDM7_Msk                       (0x1UL<<USART_CR1_ADDM7_Pos)                      /*!< 0x00020000 */
#define USART_CR1_ADDM7                           USART_CR1_ADDM7_Msk                               /*!< addm7 */
#define USART_CR1_SWAP_Pos                        (18U)
#define USART_CR1_SWAP_Msk                        (0x1UL<<USART_CR1_SWAP_Pos)                       /*!< 0x00040000 */
#define USART_CR1_SWAP                            USART_CR1_SWAP_Msk                                /*!< swap */
#define USART_CR1_TXFTCFG_Pos                     (19U)
#define USART_CR1_TXFTCFG_Msk                     (0x7UL<<USART_CR1_TXFTCFG_Pos)                    /*!< 0x00380000 */
#define USART_CR1_TXFTCFG                         USART_CR1_TXFTCFG_Msk                             /*!< txfifo threshoold cfg  */
#define USART_CR1_TXFTCFG_0                       (0x1UL<<USART_CR1_TXFTCFG_Pos)                    /*!< 0x00080000 */
#define USART_CR1_TXFTCFG_1                       (0x2UL<<USART_CR1_TXFTCFG_Pos)                    /*!< 0x00100000 */
#define USART_CR1_TXFTCFG_2                       (0x4UL<<USART_CR1_TXFTCFG_Pos)                    /*!< 0x00200000 */
#define USART_CR1_RXFTCFG_Pos                     (22U)
#define USART_CR1_RXFTCFG_Msk                     (0x7UL<<USART_CR1_RXFTCFG_Pos)                    /*!< 0x01C00000 */
#define USART_CR1_RXFTCFG                         USART_CR1_RXFTCFG_Msk                             /*!< rxfifo threshoold cfg  */
#define USART_CR1_RXFTCFG_0                       (0x1UL<<USART_CR1_RXFTCFG_Pos)                    /*!< 0x00400000 */
#define USART_CR1_RXFTCFG_1                       (0x2UL<<USART_CR1_RXFTCFG_Pos)                    /*!< 0x00800000 */
#define USART_CR1_RXFTCFG_2                       (0x4UL<<USART_CR1_RXFTCFG_Pos)                    /*!< 0x01000000 */
#define USART_CR1_RX_INV_Pos                      (25U)
#define USART_CR1_RX_INV_Msk                      (0x1UL<<USART_CR1_RX_INV_Pos)                     /*!< 0x02000000 */
#define USART_CR1_RX_INV                          USART_CR1_RX_INV_Msk                              /*!< rxinv */
#define USART_CR1_TX_INV_Pos                      (26U)
#define USART_CR1_TX_INV_Msk                      (0x1UL<<USART_CR1_TX_INV_Pos)                     /*!< 0x04000000 */
#define USART_CR1_TX_INV                          USART_CR1_TX_INV_Msk                              /*!< txinv */
#define USART_CR1_DATAINV_Pos                     (27U)
#define USART_CR1_DATAINV_Msk                     (0x1UL<<USART_CR1_DATAINV_Pos)                    /*!< 0x08000000 */
#define USART_CR1_DATAINV                         USART_CR1_DATAINV_Msk                             /*!< datainv  */
#define USART_CR1_RXFRQ_Pos                       (29U)
#define USART_CR1_RXFRQ_Msk                       (0x1UL<<USART_CR1_RXFRQ_Pos)                      /*!< 0x20000000 */
#define USART_CR1_RXFRQ                           USART_CR1_RXFRQ_Msk                               /*!< receive data flush request */
#define USART_CR1_TXFRQ_Pos                       (30U)
#define USART_CR1_TXFRQ_Msk                       (0x1UL<<USART_CR1_TXFRQ_Pos)                      /*!< 0x40000000 */
#define USART_CR1_TXFRQ                           USART_CR1_TXFRQ_Msk                               /*!< Transmit data flush request */
#define USART_CR1_FIFOEN_Pos                      (31U)
#define USART_CR1_FIFOEN_Msk                      (0x1UL<<USART_CR1_FIFOEN_Pos)                     /*!< 0x80000000 */
#define USART_CR1_FIFOEN                          USART_CR1_FIFOEN_Msk                              /*!< fifo en */

/********************************* Bit definition for USART_CR2 register ********************************************/
#define USART_CR2_LBDL_Pos                        (5U)
#define USART_CR2_LBDL_Msk                        (0x1UL<<USART_CR2_LBDL_Pos)                       /*!< 0x00000020 */
#define USART_CR2_LBDL                            USART_CR2_LBDL_Msk                                /*!< LIN break detection length */
#define USART_CR2_LBDIE_Pos                       (6U)
#define USART_CR2_LBDIE_Msk                       (0x1UL<<USART_CR2_LBDIE_Pos)                      /*!< 0x00000040 */
#define USART_CR2_LBDIE                           USART_CR2_LBDIE_Msk                               /*!< lin break enable */
#define USART_CR2_LBCL_Pos                        (8U)
#define USART_CR2_LBCL_Msk                        (0x1UL<<USART_CR2_LBCL_Pos)                       /*!< 0x00000100 */
#define USART_CR2_LBCL                            USART_CR2_LBCL_Msk                                /*!< lbcl  */
#define USART_CR2_CPHA_Pos                        (9U)
#define USART_CR2_CPHA_Msk                        (0x1UL<<USART_CR2_CPHA_Pos)                       /*!< 0x00000200 */
#define USART_CR2_CPHA                            USART_CR2_CPHA_Msk                                /*!< cpha */
#define USART_CR2_CPOL_Pos                        (10U)
#define USART_CR2_CPOL_Msk                        (0x1UL<<USART_CR2_CPOL_Pos)                       /*!< 0x00000400 */
#define USART_CR2_CPOL                            USART_CR2_CPOL_Msk                                /*!< cpol */
#define USART_CR2_CLKEN_Pos                       (11U)
#define USART_CR2_CLKEN_Msk                       (0x1UL<<USART_CR2_CLKEN_Pos)                      /*!< 0x00000800 */
#define USART_CR2_CLKEN                           USART_CR2_CLKEN_Msk                               /*!< clk en */
#define USART_CR2_STOP_Pos                        (12U)
#define USART_CR2_STOP_Msk                        (0x3UL<<USART_CR2_STOP_Pos)                       /*!< 0x00003000 */
#define USART_CR2_STOP                            USART_CR2_STOP_Msk                                /*!< stop bit */
#define USART_CR2_STOP_0                          (0x1UL<<USART_CR2_STOP_Pos)                       /*!< 0x00001000 */
#define USART_CR2_STOP_1                          (0x2UL<<USART_CR2_STOP_Pos)                       /*!< 0x00002000 */
#define USART_CR2_LINEN_Pos                       (14U)
#define USART_CR2_LINEN_Msk                       (0x1UL<<USART_CR2_LINEN_Pos)                      /*!< 0x00004000 */
#define USART_CR2_LINEN                           USART_CR2_LINEN_Msk                               /*!< lin enable */
#define USART_CR2_ADD_Pos                         (15U)
#define USART_CR2_ADD_Msk                         (0xFFUL<<USART_CR2_ADD_Pos)                       /*!< 0x007F8000 */
#define USART_CR2_ADD                             USART_CR2_ADD_Msk                                 /*!< address */
#define USART_CR2_DEM_Pos                         (23U)
#define USART_CR2_DEM_Msk                         (0x1UL<<USART_CR2_DEM_Pos)                        /*!< 0x00800000 */
#define USART_CR2_DEM                             USART_CR2_DEM_Msk                                 /*!< dem */
#define USART_CR2_DEP_Pos                         (24U)
#define USART_CR2_DEP_Msk                         (0x1UL<<USART_CR2_DEP_Pos)                        /*!< 0x01000000 */
#define USART_CR2_DEP                             USART_CR2_DEP_Msk                                 /*!< dep */
#define USART_CR2_RTOEN_Pos                       (25U)
#define USART_CR2_RTOEN_Msk                       (0x1UL<<USART_CR2_RTOEN_Pos)                      /*!< 0x02000000 */
#define USART_CR2_RTOEN                           USART_CR2_RTOEN_Msk                               /*!< Receiver timeout enable */

/********************************* Bit definition for USART_CR3 register ********************************************/
#define USART_CR3_EIE_Pos                         (0U)
#define USART_CR3_EIE_Msk                         (0x1UL<<USART_CR3_EIE_Pos)                        /*!< 0x00000001 */
#define USART_CR3_EIE                             USART_CR3_EIE_Msk                                 /*!< error int enable */
#define USART_CR3_IREN_Pos                        (1U)
#define USART_CR3_IREN_Msk                        (0x1UL<<USART_CR3_IREN_Pos)                       /*!< 0x00000002 */
#define USART_CR3_IREN                            USART_CR3_IREN_Msk                                /*!< iren enable */
#define USART_CR3_IRLP_Pos                        (2U)
#define USART_CR3_IRLP_Msk                        (0x1UL<<USART_CR3_IRLP_Pos)                       /*!< 0x00000004 */
#define USART_CR3_IRLP                            USART_CR3_IRLP_Msk                                /*!< idra lowpower */
#define USART_CR3_HDSEL_Pos                       (3U)
#define USART_CR3_HDSEL_Msk                       (0x1UL<<USART_CR3_HDSEL_Pos)                      /*!< 0x00000008 */
#define USART_CR3_HDSEL                           USART_CR3_HDSEL_Msk                               /*!< hdsel  */
#define USART_CR3_NACK_Pos                        (4U)
#define USART_CR3_NACK_Msk                        (0x1UL<<USART_CR3_NACK_Pos)                       /*!< 0x00000010 */
#define USART_CR3_NACK                            USART_CR3_NACK_Msk                                /*!< scen nack enable */
#define USART_CR3_SCEN_Pos                        (5U)
#define USART_CR3_SCEN_Msk                        (0x1UL<<USART_CR3_SCEN_Pos)                       /*!< 0x00000020 */
#define USART_CR3_SCEN                            USART_CR3_SCEN_Msk                                /*!< scen enable */
#define USART_CR3_DMAR_Pos                        (6U)
#define USART_CR3_DMAR_Msk                        (0x1UL<<USART_CR3_DMAR_Pos)                       /*!< 0x00000040 */
#define USART_CR3_DMAR                            USART_CR3_DMAR_Msk                                /*!< dma rx enable */
#define USART_CR3_DMAT_Pos                        (7U)
#define USART_CR3_DMAT_Msk                        (0x1UL<<USART_CR3_DMAT_Pos)                       /*!< 0x00000080 */
#define USART_CR3_DMAT                            USART_CR3_DMAT_Msk                                /*!< dma tx enable */
#define USART_CR3_RTSE_Pos                        (8U)
#define USART_CR3_RTSE_Msk                        (0x1UL<<USART_CR3_RTSE_Pos)                       /*!< 0x00000100 */
#define USART_CR3_RTSE                            USART_CR3_RTSE_Msk                                /*!< rts enable */
#define USART_CR3_CTSE_Pos                        (9U)
#define USART_CR3_CTSE_Msk                        (0x1UL<<USART_CR3_CTSE_Pos)                       /*!< 0x00000200 */
#define USART_CR3_CTSE                            USART_CR3_CTSE_Msk                                /*!< cts enable */
#define USART_CR3_CTSIE_Pos                       (10U)
#define USART_CR3_CTSIE_Msk                       (0x1UL<<USART_CR3_CTSIE_Pos)                      /*!< 0x00000400 */
#define USART_CR3_CTSIE                           USART_CR3_CTSIE_Msk                               /*!< cts int enable */
#define USART_CR3_OVER8_Pos                       (11U)
#define USART_CR3_OVER8_Msk                       (0x1UL<<USART_CR3_OVER8_Pos)                      /*!< 0x00000800 */
#define USART_CR3_OVER8                           USART_CR3_OVER8_Msk                               /*!< oversampling  */
#define USART_CR3_ABREN_Pos                       (12U)
#define USART_CR3_ABREN_Msk                       (0x1UL<<USART_CR3_ABREN_Pos)                      /*!< 0x00001000 */
#define USART_CR3_ABREN                           USART_CR3_ABREN_Msk                               /*!< autobaud enable */
#define USART_CR3_ABRMOD_Pos                      (13U)
#define USART_CR3_ABRMOD_Msk                      (0x3UL<<USART_CR3_ABRMOD_Pos)                     /*!< 0x00006000 */
#define USART_CR3_ABRMOD                          USART_CR3_ABRMOD_Msk                              /*!< auto baud mod */
#define USART_CR3_ABRMOD_0                        (0x1UL<<USART_CR3_ABRMOD_Pos)                     /*!< 0x00002000 */
#define USART_CR3_ABRMOD_1                        (0x2UL<<USART_CR3_ABRMOD_Pos)                     /*!< 0x00004000 */
#define USART_CR3_RXFFIE_Pos                      (15U)
#define USART_CR3_RXFFIE_Msk                      (0x1UL<<USART_CR3_RXFFIE_Pos)                     /*!< 0x00008000 */
#define USART_CR3_RXFFIE                          USART_CR3_RXFFIE_Msk                              /*!< rxff int enable */
#define USART_CR3_TXFEIE_Pos                      (16U)
#define USART_CR3_TXFEIE_Msk                      (0x1UL<<USART_CR3_TXFEIE_Pos)                     /*!< 0x00010000 */
#define USART_CR3_TXFEIE                          USART_CR3_TXFEIE_Msk                              /*!< txfe int enable */
#define USART_CR3_RXFTIE_Pos                      (17U)
#define USART_CR3_RXFTIE_Msk                      (0x1UL<<USART_CR3_RXFTIE_Pos)                     /*!< 0x00020000 */
#define USART_CR3_RXFTIE                          USART_CR3_RXFTIE_Msk                              /*!< rxft int enable */
#define USART_CR3_TXFTIE_Pos                      (18U)
#define USART_CR3_TXFTIE_Msk                      (0x1UL<<USART_CR3_TXFTIE_Pos)                     /*!< 0x00040000 */
#define USART_CR3_TXFTIE                          USART_CR3_TXFTIE_Msk                              /*!< txft int enable */
#define USART_CR3_DEDT_Pos                        (19U)
#define USART_CR3_DEDT_Msk                        (0x1FUL<<USART_CR3_DEDT_Pos)                      /*!< 0x00F80000 */
#define USART_CR3_DEDT                            USART_CR3_DEDT_Msk                                /*!< dedt int enable */
#define USART_CR3_DEDT_0                          (0x1UL<<USART_CR3_DEDT_Pos)                       /*!< 0x00080000 */
#define USART_CR3_DEDT_1                          (0x2UL<<USART_CR3_DEDT_Pos)                       /*!< 0x00100000 */
#define USART_CR3_DEDT_2                          (0x4UL<<USART_CR3_DEDT_Pos)                       /*!< 0x00200000 */
#define USART_CR3_DEDT_3                          (0x8UL<<USART_CR3_DEDT_Pos)                       /*!< 0x00400000 */
#define USART_CR3_DEDT_4                          (0x10UL<<USART_CR3_DEDT_Pos)                      /*!< 0x00800000 */
#define USART_CR3_DEAT_Pos                        (24U)
#define USART_CR3_DEAT_Msk                        (0x1FUL<<USART_CR3_DEAT_Pos)                      /*!< 0x1F000000 */
#define USART_CR3_DEAT                            USART_CR3_DEAT_Msk                                /*!< deat int enable */
#define USART_CR3_DEAT_0                          (0x1UL<<USART_CR3_DEAT_Pos)                       /*!< 0x01000000 */
#define USART_CR3_DEAT_1                          (0x2UL<<USART_CR3_DEAT_Pos)                       /*!< 0x02000000 */
#define USART_CR3_DEAT_2                          (0x4UL<<USART_CR3_DEAT_Pos)                       /*!< 0x04000000 */
#define USART_CR3_DEAT_3                          (0x8UL<<USART_CR3_DEAT_Pos)                       /*!< 0x08000000 */
#define USART_CR3_DEAT_4                          (0x10UL<<USART_CR3_DEAT_Pos)                      /*!< 0x10000000 */
#define USART_CR3_RTOIE_Pos                       (29U)
#define USART_CR3_RTOIE_Msk                       (0x1UL<<USART_CR3_RTOIE_Pos)                      /*!< 0x20000000 */
#define USART_CR3_RTOIE                           USART_CR3_RTOIE_Msk                               /*!< rto int enable */
#define USART_CR3_EOBIE_Pos                       (30U)
#define USART_CR3_EOBIE_Msk                       (0x1UL<<USART_CR3_EOBIE_Pos)                      /*!< 0x40000000 */
#define USART_CR3_EOBIE                           USART_CR3_EOBIE_Msk                               /*!< eob int enable */

/********************************* Bit definition for USART_GTPR register *******************************************/
#define USART_GTPR_PSC_Pos                        (0U)
#define USART_GTPR_PSC_Msk                        (0xFFUL<<USART_GTPR_PSC_Pos)                      /*!< 0x000000FF */
#define USART_GTPR_PSC                            USART_GTPR_PSC_Msk                                /*!< Prescaler value */
#define USART_GTPR_GT_Pos                         (8U)
#define USART_GTPR_GT_Msk                         (0xFFUL<<USART_GTPR_GT_Pos)                       /*!< 0x0000FF00 */
#define USART_GTPR_GT                             USART_GTPR_GT_Msk                                 /*!< Guard time value */

/********************************* Bit definition for USART_RTOR register *******************************************/
#define USART_RTOR_RTO_Pos                        (0U)
#define USART_RTOR_RTO_Msk                        (0xFFFFFFUL<<USART_RTOR_RTO_Pos)                  /*!< 0x00FFFFFF */
#define USART_RTOR_RTO                            USART_RTOR_RTO_Msk                                /*!< receive timeout */
#define USART_RTOR_BLEN_Pos                       (24U)
#define USART_RTOR_BLEN_Msk                       (0xFFUL<<USART_RTOR_BLEN_Pos)                     /*!< 0xFF000000 */
#define USART_RTOR_BLEN                           USART_RTOR_BLEN_Msk                               /*!< blocken length */

/********************************************************************************************************************/
/********************************* UART *****************************************************************************/
/********************************************************************************************************************/

/********************************* Bit definition for UART_DR register **********************************************/
#define UART_DR_DR_Pos                            (0U)
#define UART_DR_DR_Msk                            (0x1FFUL<<UART_DR_DR_Pos)                         /*!< 0x000001FF */
#define UART_DR_DR                                UART_DR_DR_Msk                                    /*!< Receive/send data register */

/********************************* Bit definition for UART_BRR register *********************************************/
#define UART_BRR_BRR_Pos                          (0U)
#define UART_BRR_BRR_Msk                          (0xFFFFUL<<UART_BRR_BRR_Pos)                      /*!< 0x0000FFFF */
#define UART_BRR_BRR                              UART_BRR_BRR_Msk                                  /*!< Baud rate register */

/********************************* Bit definition for UART_SR register **********************************************/
#define UART_SR_RXNE_Pos                          (0U)
#define UART_SR_RXNE_Msk                          (0x1UL<<UART_SR_RXNE_Pos)                         /*!< 0x00000001 */
#define UART_SR_RXNE                              UART_SR_RXNE_Msk                                  /*!< Receive register not empty */
#define UART_SR_ORE_Pos                           (1U)
#define UART_SR_ORE_Msk                           (0x1UL<<UART_SR_ORE_Pos)                          /*!< 0x00000002 */
#define UART_SR_ORE                               UART_SR_ORE_Msk                                   /*!< Overrun error bit */
#define UART_SR_PE_Pos                            (2U)
#define UART_SR_PE_Msk                            (0x1UL<<UART_SR_PE_Pos)                           /*!< 0x00000004 */
#define UART_SR_PE                                UART_SR_PE_Msk                                    /*!< Parity Error bit */
#define UART_SR_FE_Pos                            (3U)
#define UART_SR_FE_Msk                            (0x1UL<<UART_SR_FE_Pos)                           /*!< 0x00000008 */
#define UART_SR_FE                                UART_SR_FE_Msk                                    /*!< Framing Error bit */
#define UART_SR_BRI_Pos                           (4U)
#define UART_SR_BRI_Msk                           (0x1UL<<UART_SR_BRI_Pos)                          /*!< 0x00000010 */
#define UART_SR_BRI                               UART_SR_BRI_Msk                                   /*!< Break Interrupt bit */
#define UART_SR_TDRE_Pos                          (5U)
#define UART_SR_TDRE_Msk                          (0x1UL<<UART_SR_TDRE_Pos)                         /*!< 0x00000020 */
#define UART_SR_TDRE                              UART_SR_TDRE_Msk                                  /*!< Transmit Holding Register Empty bit */
#define UART_SR_TXE_Pos                           (6U)
#define UART_SR_TXE_Msk                           (0x1UL<<UART_SR_TXE_Pos)                          /*!< 0x00000040 */
#define UART_SR_TXE                               UART_SR_TXE_Msk                                   /*!< Transmitter Empty bit */
#define UART_SR_ADDR_RCVD_Pos                     (8U)
#define UART_SR_ADDR_RCVD_Msk                     (0x1UL<<UART_SR_ADDR_RCVD_Pos)                    /*!< 0x00000100 */
#define UART_SR_ADDR_RCVD                         UART_SR_ADDR_RCVD_Msk                             /*!< Address Received Bit */
#define UART_SR_BUSY_Pos                          (9U)
#define UART_SR_BUSY_Msk                          (0x1UL<<UART_SR_BUSY_Pos)                         /*!< 0x00000200 */
#define UART_SR_BUSY                              UART_SR_BUSY_Msk                                  /*!< UART Busy */
#define UART_SR_BUSY_ERR_Pos                      (10U)
#define UART_SR_BUSY_ERR_Msk                      (0x1UL<<UART_SR_BUSY_ERR_Pos)                     /*!< 0x00000400 */
#define UART_SR_BUSY_ERR                          UART_SR_BUSY_ERR_Msk                              /*!< Busy Detect Error */

/********************************* Bit definition for UART_CR1 register *********************************************/
#define UART_CR1_M_Pos                            (0U)
#define UART_CR1_M_Msk                            (0x3UL<<UART_CR1_M_Pos)                           /*!< 0x00000003 */
#define UART_CR1_M                                UART_CR1_M_Msk                                    /*!< Data Length Select */
#define UART_CR1_M_0                              (0x1UL<<UART_CR1_M_Pos)                           /*!< 0x00000001 */
#define UART_CR1_M_1                              (0x2UL<<UART_CR1_M_Pos)                           /*!< 0x00000002 */
#define UART_CR1_STOP_Pos                         (2U)
#define UART_CR1_STOP_Msk                         (0x1UL<<UART_CR1_STOP_Pos)                        /*!< 0x00000004 */
#define UART_CR1_STOP                             UART_CR1_STOP_Msk                                 /*!< Number of stop bits */
#define UART_CR1_PCE_Pos                          (3U)
#define UART_CR1_PCE_Msk                          (0x1UL<<UART_CR1_PCE_Pos)                         /*!< 0x00000008 */
#define UART_CR1_PCE                              UART_CR1_PCE_Msk                                  /*!< Parity Enable */
#define UART_CR1_PS_Pos                           (4U)
#define UART_CR1_PS_Msk                           (0x1UL<<UART_CR1_PS_Pos)                          /*!< 0x00000010 */
#define UART_CR1_PS                               UART_CR1_PS_Msk                                   /*!< Even Parity Select */
#define UART_CR1_SP_Pos                           (5U)
#define UART_CR1_SP_Msk                           (0x1UL<<UART_CR1_SP_Pos)                          /*!< 0x00000020 */
#define UART_CR1_SP                               UART_CR1_SP_Msk                                   /*!< Stick Parity */
#define UART_CR1_SBK_Pos                          (6U)
#define UART_CR1_SBK_Msk                          (0x1UL<<UART_CR1_SBK_Pos)                         /*!< 0x00000040 */
#define UART_CR1_SBK                              UART_CR1_SBK_Msk                                  /*!< Send Break */
#define UART_CR1_SWAP_Pos                         (8U)
#define UART_CR1_SWAP_Msk                         (0x1UL<<UART_CR1_SWAP_Pos)                        /*!< 0x00000100 */
#define UART_CR1_SWAP                             UART_CR1_SWAP_Msk                                 /*!< TX/RX pin swap */
#define UART_CR1_MSBFIRST_Pos                     (9U)
#define UART_CR1_MSBFIRST_Msk                     (0x1UL<<UART_CR1_MSBFIRST_Pos)                    /*!< 0x00000200 */
#define UART_CR1_MSBFIRST                         UART_CR1_MSBFIRST_Msk                             /*!< MSB first mode */

/********************************* Bit definition for UART_CR2 register *********************************************/
#define UART_CR2_RXNEIE_Pos                       (0U)
#define UART_CR2_RXNEIE_Msk                       (0x1UL<<UART_CR2_RXNEIE_Pos)                      /*!< 0x00000001 */
#define UART_CR2_RXNEIE                           UART_CR2_RXNEIE_Msk                               /*!< Enable Received Data Available Interrupt */
#define UART_CR2_TDREIE_Pos                       (1U)
#define UART_CR2_TDREIE_Msk                       (0x1UL<<UART_CR2_TDREIE_Pos)                      /*!< 0x00000002 */
#define UART_CR2_TDREIE                           UART_CR2_TDREIE_Msk                               /*!< Enable Transmit Holding Register Empty Interrupt */
#define UART_CR2_LSIE_Pos                         (2U)
#define UART_CR2_LSIE_Msk                         (0x1UL<<UART_CR2_LSIE_Pos)                        /*!< 0x00000004 */
#define UART_CR2_LSIE                             UART_CR2_LSIE_Msk                                 /*!< Enable Receiver Line Status Interrupt */
#define UART_CR2_BUSYERRIE_Pos                    (3U)
#define UART_CR2_BUSYERRIE_Msk                    (0x1UL<<UART_CR2_BUSYERRIE_Pos)                   /*!< 0x00000008 */
#define UART_CR2_BUSYERRIE                        UART_CR2_BUSYERRIE_Msk                            /*!< Enable Busyerr state interruption */

/********************************* Bit definition for UART_CR3 register *********************************************/
#define UART_CR3_M_E_Pos                          (0U)
#define UART_CR3_M_E_Msk                          (0x1UL<<UART_CR3_M_E_Pos)                         /*!< 0x00000001 */
#define UART_CR3_M_E                              UART_CR3_M_E_Msk                                  /*!< Extension for DLS */
#define UART_CR3_ADDR_MATCH_Pos                   (1U)
#define UART_CR3_ADDR_MATCH_Msk                   (0x1UL<<UART_CR3_ADDR_MATCH_Pos)                  /*!< 0x00000002 */
#define UART_CR3_ADDR_MATCH                       UART_CR3_ADDR_MATCH_Msk                           /*!<  Address Match Mode */
#define UART_CR3_SEND_ADDR_Pos                    (2U)
#define UART_CR3_SEND_ADDR_Msk                    (0x1UL<<UART_CR3_SEND_ADDR_Pos)                   /*!< 0x00000004 */
#define UART_CR3_SEND_ADDR                        UART_CR3_SEND_ADDR_Msk                            /*!< Send address control bit */
#define UART_CR3_TX_MODE_Pos                      (3U)
#define UART_CR3_TX_MODE_Msk                      (0x1UL<<UART_CR3_TX_MODE_Pos)                     /*!< 0x00000008 */
#define UART_CR3_TX_MODE                          UART_CR3_TX_MODE_Msk                              /*!< Transmit mode control bit */
#define UART_CR3_DMAR_Pos                         (4U)
#define UART_CR3_DMAR_Msk                         (0x1UL<<UART_CR3_DMAR_Pos)                        /*!< 0x00000010 */
#define UART_CR3_DMAR                             UART_CR3_DMAR_Msk                                 /*!< DMA receive enable */
#define UART_CR3_DMAT_Pos                         (5U)
#define UART_CR3_DMAT_Msk                         (0x1UL<<UART_CR3_DMAT_Pos)                        /*!< 0x00000020 */
#define UART_CR3_DMAT                             UART_CR3_DMAT_Msk                                 /*!< DMA transmit enable */
#define UART_CR3_DMA_SOFT_ACK_Pos                 (6U)
#define UART_CR3_DMA_SOFT_ACK_Msk                 (0x1UL<<UART_CR3_DMA_SOFT_ACK_Pos)                /*!< 0x00000040 */
#define UART_CR3_DMA_SOFT_ACK                     UART_CR3_DMA_SOFT_ACK_Msk                         /*!< DMA software ack */

/********************************* Bit definition for UART_RAR register *********************************************/
#define UART_RAR_RAR_Pos                          (0U)
#define UART_RAR_RAR_Msk                          (0xFFUL<<UART_RAR_RAR_Pos)                        /*!< 0x000000FF */
#define UART_RAR_RAR                              UART_RAR_RAR_Msk                                  /*!< Receive address matching register */

/********************************* Bit definition for UART_TAR register *********************************************/
#define UART_TAR_TAR_Pos                          (0U)
#define UART_TAR_TAR_Msk                          (0xFFUL<<UART_TAR_TAR_Pos)                        /*!< 0x000000FF */
#define UART_TAR_TAR                              UART_TAR_TAR_Msk                                  /*!< Transmit address matching register */

/********************************* Bit definition for UART_BRRF register ********************************************/
#define UART_BRRF_BRRF_Pos                        (0U)
#define UART_BRRF_BRRF_Msk                        (0xFUL<<UART_BRRF_BRRF_Pos)                       /*!< 0x0000000F */
#define UART_BRRF_BRRF                            UART_BRRF_BRRF_Msk                                /*!< Baud rate fractional register */
#define UART_BRRF_BRRF_0                          (0x1UL<<UART_BRRF_BRRF_Pos)                       /*!< 0x00000001 */
#define UART_BRRF_BRRF_1                          (0x2UL<<UART_BRRF_BRRF_Pos)                       /*!< 0x00000002 */
#define UART_BRRF_BRRF_2                          (0x4UL<<UART_BRRF_BRRF_Pos)                       /*!< 0x00000004 */
#define UART_BRRF_BRRF_3                          (0x8UL<<UART_BRRF_BRRF_Pos)                       /*!< 0x00000008 */

/********************************************************************************************************************/
/********************************* WWDG *****************************************************************************/
/********************************************************************************************************************/

/*********************  Bits Define For Peripheral WWDG  *********************/
/*!< WWDG_CR */
#define WWDG_CR_T_Pos                             (0U)
#define WWDG_CR_T_Msk                             (0x7FUL << WWDG_CR_T_Pos)                         /*!< 0x0000007F */
#define WWDG_CR_T                                 WWDG_CR_T_Msk                                     /*!< T[6:0] bits (desc T) */
#define WWDG_CR_T_0                               (0x1UL << WWDG_CR_T_Pos)                          /*!< 0x00000001 */
#define WWDG_CR_T_1                               (0x2UL << WWDG_CR_T_Pos)                          /*!< 0x00000002 */
#define WWDG_CR_T_2                               (0x4UL << WWDG_CR_T_Pos)                          /*!< 0x00000004 */
#define WWDG_CR_T_3                               (0x8UL << WWDG_CR_T_Pos)                          /*!< 0x00000008 */
#define WWDG_CR_T_4                               (0x10UL << WWDG_CR_T_Pos)                         /*!< 0x00000010 */
#define WWDG_CR_T_5                               (0x20UL << WWDG_CR_T_Pos)                         /*!< 0x00000020 */
#define WWDG_CR_T_6                               (0x40UL << WWDG_CR_T_Pos)                         /*!< 0x00000040 */

#define WWDG_CR_WDGA_Pos                          (7U)
#define WWDG_CR_WDGA_Msk                          (0x1UL << WWDG_CR_WDGA_Pos)                       /*!< 0x00000080 */
#define WWDG_CR_WDGA                              WWDG_CR_WDGA_Msk                                  /*!< desc WDGA */

/*!< WWDG_CFR */
#define WWDG_CFR_W_Pos                            (0U)
#define WWDG_CFR_W_Msk                            (0x7FUL << WWDG_CFR_W_Pos)                        /*!< 0x0000007F */
#define WWDG_CFR_W                                WWDG_CFR_W_Msk                                    /*!< W[6:0] bits (desc W) */
#define WWDG_CFR_W_0                              (0x1UL << WWDG_CFR_W_Pos)                         /*!< 0x00000001 */
#define WWDG_CFR_W_1                              (0x2UL << WWDG_CFR_W_Pos)                         /*!< 0x00000002 */
#define WWDG_CFR_W_2                              (0x4UL << WWDG_CFR_W_Pos)                         /*!< 0x00000004 */
#define WWDG_CFR_W_3                              (0x8UL << WWDG_CFR_W_Pos)                         /*!< 0x00000008 */
#define WWDG_CFR_W_4                              (0x10UL << WWDG_CFR_W_Pos)                        /*!< 0x00000010 */
#define WWDG_CFR_W_5                              (0x20UL << WWDG_CFR_W_Pos)                        /*!< 0x00000020 */
#define WWDG_CFR_W_6                              (0x40UL << WWDG_CFR_W_Pos)                        /*!< 0x00000040 */

#define WWDG_CFR_WDGTB_Pos                        (7U)
#define WWDG_CFR_WDGTB_Msk                        (0x3UL << WWDG_CFR_WDGTB_Pos)                     /*!< 0x00000180 */
#define WWDG_CFR_WDGTB                            WWDG_CFR_WDGTB_Msk                                /*!< WDGTB[8:7] bits (desc WDGTB) */
#define WWDG_CFR_WDGTB_0                          (0x1UL << WWDG_CFR_WDGTB_Pos)                     /*!< 0x00000080 */
#define WWDG_CFR_WDGTB_1                          (0x2UL << WWDG_CFR_WDGTB_Pos)                     /*!< 0x00000100 */

#define WWDG_CFR_EWI_Pos                          (9U)
#define WWDG_CFR_EWI_Msk                          (0x1UL << WWDG_CFR_EWI_Pos)                       /*!< 0x00000200 */
#define WWDG_CFR_EWI                              WWDG_CFR_EWI_Msk                                  /*!< desc EWI */

/*!< WWDG_SR */
#define WWDG_SR_EWIF_Pos                          (0U)
#define WWDG_SR_EWIF_Msk                          (0x1UL << WWDG_SR_EWIF_Pos)                       /*!< 0x00000001 */
#define WWDG_SR_EWIF                              WWDG_SR_EWIF_Msk                                  /*!< desc EWIF */

/****************************** ADC Instances *********************************/
#define IS_ADC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == ADC1)

 #define IS_ADC_COMMON_INSTANCE(INSTANCE) ((INSTANCE) == ADC_COMMON)

#define IS_ADC_MULTIMODE_MASTER_INSTANCE(INSTANCE) ((INSTANCE) == ADC1)

#define IS_ADC_DMA_CAPABILITY_INSTANCE(INSTANCE) ((INSTANCE) == ADC1)

/****************************** COMP Instances *******************************/
#define IS_COMP_ALL_INSTANCE(INSTANCE) (((INSTANCE) == COMP1) || \
                                        ((INSTANCE) == COMP2))

#define IS_COMP_COMMON_INSTANCE(INSTANCE) ((INSTANCE) == COMP12_COMMON)

/****************************** OPA Instances *******************************/
#define IS_OPA_ALL_INSTANCE(INSTANCE) (((INSTANCE) == OPA1) || \
                                       ((INSTANCE) == OPA2))

/****************************** CRC Instances *******************************/
#define IS_CRC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == CRC)

/****************************** DBGMCU Instances *******************************/
#define IS_DBGMCU_ALL_INSTANCE(INSTANCE) ((INSTANCE) == DBGMCU)

/****************************** DMA Instances *********************************/
#define IS_DMA_ALL_INSTANCE(INSTANCE) (((INSTANCE) == DMA1_Channel1) || \
                                       ((INSTANCE) == DMA1_Channel2) || \
                                       ((INSTANCE) == DMA1_Channel3) || \
                                       ((INSTANCE) == DMA1_Channel4) || \
                                       ((INSTANCE) == DMA1_Channel5) || \
                                       ((INSTANCE) == DMA1_Channel6) || \
                                       ((INSTANCE) == DMA1_Channel7) || \
                                       ((INSTANCE) == DMA1_Channel8))

/****************************** EXTI Instances ********************************/
#define IS_EXTI_ALL_INSTANCE(INSTANCE) ((INSTANCE) == EXTI)

/****************************** FLASH Instances ********************************/
#define IS_FLASH_ALL_INSTANCE(INSTANCE) ((INSTANCE) == FLASH)

/******************************* GPIO Instances *******************************/
#define IS_GPIO_ALL_INSTANCE(INSTANCE) (((INSTANCE) == GPIOA) || \
                                        ((INSTANCE) == GPIOB) || \
                                        ((INSTANCE) == GPIOC) || \
                                        ((INSTANCE) == GPIOD))

/**************************** GPIO Alternate Function Instances ***************/
#define IS_GPIO_AF_INSTANCE(INSTANCE) IS_GPIO_ALL_INSTANCE(INSTANCE)

/**************************** GPIO Lock Instances *****************************/
#define IS_GPIO_LOCK_INSTANCE(INSTANCE) IS_GPIO_ALL_INSTANCE(INSTANCE)

/******************************** I2C Instances *******************************/
#define IS_I2C_ALL_INSTANCE(INSTANCE) (((INSTANCE) == I2C1) || \
                                       ((INSTANCE) == I2C2))

/********************* I2C WAKEUP FROMSTOP Instances **************************/
#define IS_I2C_WAKEUP_FROMSTOP_INSTANCE(INSTANCE) (((INSTANCE) == I2C1) || \
                                                   ((INSTANCE) == I2C2))

/******************************* SMBUS Instances ******************************/
#define IS_SMBUS_ALL_INSTANCE         IS_I2C_ALL_INSTANCE

/****************************** PWR Instances ********************************/
#define IS_PWR_ALL_INSTANCE(INSTANCE) ((INSTANCE) == PWR)

/****************************** RTC Instances ********************************/
#define IS_RTC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == RTC)

/******************************** I2S Instances *******************************/
#define IS_I2S_ALL_INSTANCE(INSTANCE) (((INSTANCE) == SPI1) || \
                                       ((INSTANCE) == SPI2))

/****************************** IWDG Instances ********************************/
#define IS_IWDG_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == IWDG)

/****************************** LPTIM Instances ********************************/
#define IS_LPTIM_INSTANCE(INSTANCE)  ((INSTANCE) == LPTIM1)

/****************************** LPUART Instances ********************************/
#define IS_LPUART_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == LPUART1)

/****************************** LPUART Instances : Driver Enable ******** **/
#define IS_LPUART_DRIVER_ENABLE_INSTANCE(INSTANCE)  ((INSTANCE) == LPUART1)

/****************************** LPUART Instances : FIFO mode **********/
#define IS_LPUART_FIFO_INSTANCE(INSTANCE)  ((INSTANCE) == LPUART1)

/****************************** LPUART Instances : Wake-up from Stop mode *****/
#define IS_LPUART_WAKEUP_FROMSTOP_INSTANCE(INSTANCE)  ((INSTANCE) == LPUART1)

/******************************** SPI Instances *******************************/
#define IS_SPI_ALL_INSTANCE(INSTANCE) (((INSTANCE) == SPI1) || \
                                       ((INSTANCE) == SPI2))

/****************************** START TIM Instances ***************************/
/****************************** TIM Instances *********************************/
#define IS_TIM_INSTANCE(INSTANCE)\
  (((INSTANCE) == TIM1)    || \
   ((INSTANCE) == TIM2)    || \
   ((INSTANCE) == TIM3)    || \
   ((INSTANCE) == TIM4)    || \
   ((INSTANCE) == TIM6)    || \
   ((INSTANCE) == TIM7)    || \
   ((INSTANCE) == TIM15)   || \
   ((INSTANCE) == TIM16)   || \
   ((INSTANCE) == TIM17))

/****************** TIM Instances : supporting 32 bits counter ****************/

#define IS_TIM_32B_COUNTER_INSTANCE(INSTANCE) ((INSTANCE) == TIM2)

/****************** TIM Instances : supporting the break function *************/
#define IS_TIM_BREAK_INSTANCE(INSTANCE)    (((INSTANCE) == TIM1)    || \
                                            ((INSTANCE) == TIM15)   || \
                                            ((INSTANCE) == TIM16)   || \
                                            ((INSTANCE) == TIM17))

/************** TIM Instances : supporting Break source selection *************/
#define IS_TIM_BREAKSOURCE_INSTANCE(INSTANCE) (((INSTANCE) == TIM1)   || \
                                               ((INSTANCE) == TIM15)  || \
                                               ((INSTANCE) == TIM16)  || \
                                               ((INSTANCE) == TIM17))

/************* TIM Instances : at least 1 capture/compare channel *************/
#define IS_TIM_CC1_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)   || \
                                         ((INSTANCE) == TIM2)   || \
                                         ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM4)   || \
                                         ((INSTANCE) == TIM15)  || \
                                         ((INSTANCE) == TIM16)  || \
                                         ((INSTANCE) == TIM17))

/************ TIM Instances : at least 2 capture/compare channels *************/
#define IS_TIM_CC2_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)   || \
                                         ((INSTANCE) == TIM2)   || \
                                         ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM4)   || \
                                         ((INSTANCE) == TIM15))

/************ TIM Instances : at least 3 capture/compare channels *************/
#define IS_TIM_CC3_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)   || \
                                         ((INSTANCE) == TIM2)   || \
                                         ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM4))

/************ TIM Instances : at least 4 capture/compare channels *************/
#define IS_TIM_CC4_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)   || \
                                         ((INSTANCE) == TIM2)   || \
                                         ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM4))

/****************** TIM Instances : at least 5 capture/compare channels *******/
#define IS_TIM_CC5_INSTANCE(INSTANCE)   ((INSTANCE) == TIM1)

/****************** TIM Instances : at least 6 capture/compare channels *******/
#define IS_TIM_CC6_INSTANCE(INSTANCE)   ((INSTANCE) == TIM1)

/************ TIM Instances : DMA requests generation (TIMx_DIER.COMDE) *******/
#define IS_TIM_CCDMA_INSTANCE(INSTANCE)    (((INSTANCE) == TIM1)   || \
                                            ((INSTANCE) == TIM15))

/****************** TIM Instances : DMA requests generation (TIMx_DIER.UDE) ***/
#define IS_TIM_DMA_INSTANCE(INSTANCE)      (((INSTANCE) == TIM1)   || \
                                            ((INSTANCE) == TIM2)   || \
                                            ((INSTANCE) == TIM3)   || \
                                            ((INSTANCE) == TIM4)   || \
                                            ((INSTANCE) == TIM6)   || \
                                            ((INSTANCE) == TIM7)   || \
                                            ((INSTANCE) == TIM15)  || \
                                            ((INSTANCE) == TIM16)  || \
                                            ((INSTANCE) == TIM17))

/************ TIM Instances : DMA requests generation (TIMx_DIER.CCxDE) *******/
#define IS_TIM_DMA_CC_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)   || \
                                            ((INSTANCE) == TIM2)   || \
                                            ((INSTANCE) == TIM3)   || \
                                            ((INSTANCE) == TIM4)   || \
                                            ((INSTANCE) == TIM15)  || \
                                            ((INSTANCE) == TIM16)  || \
                                            ((INSTANCE) == TIM17))

/******************** TIM Instances : DMA burst feature ***********************/
#define IS_TIM_DMABURST_INSTANCE(INSTANCE) (((INSTANCE) == TIM1)   || \
                                            ((INSTANCE) == TIM2)   || \
                                            ((INSTANCE) == TIM3)   || \
                                            ((INSTANCE) == TIM4)   || \
                                            ((INSTANCE) == TIM15)  || \
                                            ((INSTANCE) == TIM16)  || \
                                            ((INSTANCE) == TIM17))

/******************* TIM Instances : output(s) available **********************/
#define IS_TIM_CCX_INSTANCE(INSTANCE, CHANNEL) \
    ((((INSTANCE) == TIM1) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4) ||          \
      ((CHANNEL) == TIM_CHANNEL_5) ||          \
      ((CHANNEL) == TIM_CHANNEL_6)))           \
     ||                                        \
     (((INSTANCE) == TIM2) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
     ||                                        \
     (((INSTANCE) == TIM3) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
     ||                                        \
     (((INSTANCE) == TIM4) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
     ||                                        \
     (((INSTANCE) == TIM15) &&                 \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2)))           \
     ||                                        \
     (((INSTANCE) == TIM16) &&                 \
     (((CHANNEL) == TIM_CHANNEL_1)))           \
     ||                                        \
     (((INSTANCE) == TIM17) &&                 \
      (((CHANNEL) == TIM_CHANNEL_1))))

/****************** TIM Instances : supporting complementary output(s) ********/
#define IS_TIM_CCXN_INSTANCE(INSTANCE, CHANNEL) \
   ((((INSTANCE) == TIM1) &&                    \
     (((CHANNEL) == TIM_CHANNEL_1) ||           \
      ((CHANNEL) == TIM_CHANNEL_2) ||           \
      ((CHANNEL) == TIM_CHANNEL_3))            \
    ||                                          \
    (((INSTANCE) == TIM15) &&                   \
     ((CHANNEL) == TIM_CHANNEL_1))              \
    ||                                          \
    (((INSTANCE) == TIM16) &&                   \
     ((CHANNEL) == TIM_CHANNEL_1))              \
    ||                                          \
    (((INSTANCE) == TIM17) &&                   \
     ((CHANNEL) == TIM_CHANNEL_1))))

/****************** TIM Instances : supporting clock division *****************/
#define IS_TIM_CLOCK_DIVISION_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)    || \
                                                    ((INSTANCE) == TIM2)    || \
                                                    ((INSTANCE) == TIM3)    || \
                                                    ((INSTANCE) == TIM4)    || \
                                                    ((INSTANCE) == TIM15)   || \
                                                    ((INSTANCE) == TIM16)   || \
                                                    ((INSTANCE) == TIM17))

/****** TIM Instances : supporting external clock mode 1 for ETRF input *******/
#define IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM4) || \
                                                        ((INSTANCE) == TIM15))

/****** TIM Instances : supporting external clock mode 2 for ETRF input *******/
#define IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM4))

/****************** TIM Instances : supporting external clock mode 1 for TIX inputs*/
#define IS_TIM_CLOCKSOURCE_TIX_INSTANCE(INSTANCE)      (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM4) || \
                                                        ((INSTANCE) == TIM15))

/****************** TIM Instances : supporting internal trigger inputs(ITRX) *******/
#define IS_TIM_CLOCKSOURCE_ITRX_INSTANCE(INSTANCE)      (((INSTANCE) == TIM1) || \
                                                         ((INSTANCE) == TIM2) || \
                                                         ((INSTANCE) == TIM3) || \
                                                         ((INSTANCE) == TIM4) || \
                                                         ((INSTANCE) == TIM15))

/****************** TIM Instances : supporting combined 3-phase PWM mode ******/
#define IS_TIM_COMBINED3PHASEPWM_INSTANCE(INSTANCE) ((INSTANCE) == TIM1)

/****************** TIM Instances : supporting commutation event generation ***/
#define IS_TIM_COMMUTATION_EVENT_INSTANCE(INSTANCE) (((INSTANCE) == TIM1)   || \
                                                     ((INSTANCE) == TIM15)  || \
                                                     ((INSTANCE) == TIM16)  || \
                                                     ((INSTANCE) == TIM17))

/****************** TIM Instances : supporting counting mode selection ********/
#define IS_TIM_COUNTER_MODE_SELECT_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM4))

/****************** TIM Instances : supporting encoder interface **************/
#define IS_TIM_ENCODER_INTERFACE_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1) || \
                                                      ((INSTANCE) == TIM2) || \
                                                      ((INSTANCE) == TIM3) || \
                                                      ((INSTANCE) == TIM4))

/****************** TIM Instances : supporting Hall sensor interface **********/
#define IS_TIM_HALL_SENSOR_INTERFACE_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1))

/**************** TIM Instances : external trigger input available ************/
#define IS_TIM_ETR_INSTANCE(INSTANCE)                  (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM4) || \
                                                        ((INSTANCE) == TIM15))

/************* TIM Instances : supporting ETR source selection ***************/
#define IS_TIM_ETRSEL_INSTANCE(INSTANCE)               (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM4) || \
                                                        ((INSTANCE) == TIM15))

/****** TIM Instances : Master mode available (TIMx_CR2.MMS available )********/
#define IS_TIM_MASTER_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)  || \
                                            ((INSTANCE) == TIM2)  || \
                                            ((INSTANCE) == TIM3)  || \
                                            ((INSTANCE) == TIM4)  || \
                                            ((INSTANCE) == TIM6)  || \
                                            ((INSTANCE) == TIM7)  || \
                                            ((INSTANCE) == TIM15))

/*********** TIM Instances : Slave mode available (TIMx_SMCR available )*******/
#define IS_TIM_SLAVE_INSTANCE(INSTANCE)    (((INSTANCE) == TIM1)  || \
                                            ((INSTANCE) == TIM2)  || \
                                            ((INSTANCE) == TIM3)  || \
                                            ((INSTANCE) == TIM4)  || \
                                            ((INSTANCE) == TIM15))

/****************** TIM Instances : supporting OCxREF clear *******************/
#define IS_TIM_OCXREF_CLEAR_INSTANCE(INSTANCE)        (((INSTANCE) == TIM1)  || \
                                                       ((INSTANCE) == TIM2)  || \
                                                       ((INSTANCE) == TIM3)  || \
                                                       ((INSTANCE) == TIM4))

/****************** TIM Instances : supporting bitfield OCCS in SMCR register *******************/
#define IS_TIM_OCCS_INSTANCE(INSTANCE)                (((INSTANCE) == TIM1)  || \
                                                       ((INSTANCE) == TIM2)  || \
                                                       ((INSTANCE) == TIM3)  || \
                                                       ((INSTANCE) == TIM4))

/****************** TIM Instances : remapping capability **********************/
#define IS_TIM_REMAP_INSTANCE(INSTANCE)    (((INSTANCE) == TIM1)  || \
                                            ((INSTANCE) == TIM2)  || \
                                            ((INSTANCE) == TIM3)  || \
                                            ((INSTANCE) == TIM4))

/****************** TIM Instances : supporting repetition counter *************/
#define IS_TIM_REPETITION_COUNTER_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1)  || \
                                                       ((INSTANCE) == TIM15) || \
                                                       ((INSTANCE) == TIM16) || \
                                                       ((INSTANCE) == TIM17))

/******************* TIM Instances : Timer input XOR function *****************/
#define IS_TIM_XOR_INSTANCE(INSTANCE)      (((INSTANCE) == TIM1)   || \
                                            ((INSTANCE) == TIM2)   || \
                                            ((INSTANCE) == TIM3)   || \
                                            ((INSTANCE) == TIM4)   || \
                                            ((INSTANCE) == TIM15))

/******************* TIM Instances : Timer input selection ********************/
#define IS_TIM_TISEL_INSTANCE(INSTANCE) (((INSTANCE) == TIM1)   || \
                                         ((INSTANCE) == TIM2)   || \
                                         ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM4)   || \
                                         ((INSTANCE) == TIM15)  || \
                                         ((INSTANCE) == TIM16)  || \
                                         ((INSTANCE) == TIM17))

/****************** TIM Instances : Advanced timer instances *******************/
#define IS_TIM_ADVANCED_INSTANCE(INSTANCE)       (((INSTANCE) == TIM1))


/****************** TIM Instances : supporting HSE/32 request instances *******************/
#define IS_TIM_HSE32_INSTANCE(INSTANCE)         (((INSTANCE) == TIM16)   || \
                                                 ((INSTANCE) == TIM17))
/****************************** END TIM Instances *****************************/


/******************** USART Instances : Synchronous mode **********************/
#define IS_USART_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/*********************** USART Instances : FIFO mode **************************/
#define IS_USART_FIFO_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/******************** USART Instances : Asynchronous mode *********************/
#define IS_SCI_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/******************** USART Instances : HWFLOW mode ***************************/
#define IS_SCI_HWFLOW_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/******************** USART Instances : Asynchronous mode *********************/
#define IS_SCI_FIFO_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/****************** USART Instances : Driver Enable detection *****************/
#define IS_SCI_DRIVER_ENABLE_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/****************** USART Instances : Auto Baud Rate detection ****************/
#define IS_SCI_AUTOBAUDRATE_DETECTION_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/******************** USART Instances : Asynchronous mode *********************/
#define IS_SCI_HALFDUPLEX_INSTANCE(INSTANCE) ((INSTANCE) == USART1)
                                              
/******************** USART Instances : Asynchronous mode *********************/
#define IS_SCI_LIN_INSTANCE(INSTANCE)        ((INSTANCE) == USART1)

/******************** UART Instances : Asynchronous mode **********************/
#define IS_UART_INSTANCE(INSTANCE) (((INSTANCE) == UART1) || \
                                    ((INSTANCE) == UART2))

/******************** USART Instances : Half-Duplex mode **********************/
#define IS_USART_HALFDUPLEX_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/******************** UART Instances : Half-Duplex mode **********************/
#define IS_UART_HALFDUPLEX_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/******************** USART Instances : LIN mode **********************/
#define IS_USART_LIN_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/******************** UART Instances : LIN mode **********************/
#define IS_UART_LIN_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/****************** UART Instances : Hardware Flow control ********************/
#define IS_UART_HWFLOW_INSTANCE(INSTANCE) ((INSTANCE) == USART1

/********************* UART Instances : Smard card mode ***********************/
#define IS_SMARTCARD_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/****************** UART Instances : Auto Baud Rate detection *****************/
#define IS_USART_AUTOBAUDRATE_DETECTION_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/*********************** UART Instances : IRDA mode ***************************/
#define IS_IRDA_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/***************** UART Instances : Multi-Processor mode **********************/
#define IS_UART_MULTIPROCESSOR_INSTANCE(INSTANCE)  ((INSTANCE) == USART1)

/***************** UART Instances : DMA mode available **********************/
#define IS_UART_DMA_INSTANCE(INSTANCE) ((INSTANCE) == USART1)

/****************** LPUART Instances : Hardware Flow control ********************/
#define IS_LPUART_HWFLOW_INSTANCE(INSTANCE) ((INSTANCE) == LPUART1)

/****************** LPUART Instances : Hardware Flow control ********************/
#define IS_LPUART_HALFDUPLEX_INSTANCE(INSTANCE) ((INSTANCE) == LPUART1)

/******************** LPUART Instance *****************************************/
#define IS_LPUART_INSTANCE(INSTANCE)    ((INSTANCE) == LPUART1)

/****************************** RTC Instances *********************************/
#define IS_RTC_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == RTC)

/**************************** WWDG Instances *****************************/
#define IS_WWDG_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == WWDG)

/****************************** PWM Instances *******************************/
#define IS_PWM_INSTANCE(INSTANCE) (((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3) || ((INSTANCE) == PWM4) ) 

/****************** PWM Instances : supporting the break function *************/
#define IS_PWM_BREAK_INSTANCE(INSTANCE)    (((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3) ) 

/************* PWM Instances : at least 1 compare channel *************/
#define IS_PWM_OC1_INSTANCE(INSTANCE)    (((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3) || ((INSTANCE) == PWM4) ) 

/************ PWM Instances : at least 2 compare channels *************/
#define IS_PWM_OC2_INSTANCE(INSTANCE)   (((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3) || ((INSTANCE) == PWM4) ) 

/************ PWM Instances : at least 3 compare channels *************/
#define IS_PWM_OC3_INSTANCE(INSTANCE)    (((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3) || ((INSTANCE) == PWM4) ) 

/************ PWM Instances : at least 4 compare channels *************/
#define IS_PWM_OC4_INSTANCE(INSTANCE)   (((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3) || ((INSTANCE) == PWM4) ) 

/************ PWM Instances : DMA requests generation (PWMx_DIER.UDE) *********/
#define IS_PWM_DMA_INSTANCE(INSTANCE)     (((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3) || ((INSTANCE) == PWM4) ) 

/************ PWM Instances : DMA requests generation (PWMx_DIER.OCxDE) *******/
#define IS_PWM_DMA_OC_INSTANCE(INSTANCE)  (((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3) || ((INSTANCE) == PWM4) ) 

/******************** PWM Instances : DMA burst feature ***********************/
#define IS_PWM_DMABURST_INSTANCE(INSTANCE)  (((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3) || ((INSTANCE) == PWM4) ) 

/******************* PWM Instances : output(s) available **********************/
#define IS_PWM_OCX_INSTANCE(INSTANCE, CHANNEL) \
    ((((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3) || ((INSTANCE) == PWM4)) &&                  \
     (((CHANNEL) == PWM_CHANNEL_1) ||          \
      ((CHANNEL) == PWM_CHANNEL_2) ||          \
      ((CHANNEL) == PWM_CHANNEL_3) ||          \
      ((CHANNEL) == PWM_CHANNEL_4)))

/****************** PWM Instances : supporting complementary output(s) ********/
#define IS_PWM_OCXN_INSTANCE(INSTANCE, CHANNEL) \
    ((((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3)) &&                   \
     (((CHANNEL) == PWM_CHANNEL_1) ||           \
      ((CHANNEL) == PWM_CHANNEL_2)))

/****************** PWM Instances : supporting clock division *****************/
#define IS_PWM_CLOCK_DIVISION_INSTANCE(INSTANCE)  (((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3) || ((INSTANCE) == PWM4) ) 

/****** PWM Instances : supporting external clock mode *******/
#define IS_PWM_CLOCKSOURCE_ETRMODE_INSTANCE(INSTANCE) (((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3) || ((INSTANCE) == PWM4) ) 

/****************** PWM Instances : supporting counting mode selection ********/
#define IS_PWM_COUNTER_MODE_SELECT_INSTANCE(INSTANCE)  (((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3) || ((INSTANCE) == PWM4) ) 

/****************** PWM Instances : remapping capability **********************/
#define IS_PWM_REMAP_INSTANCE(INSTANCE)    (((INSTANCE) == PWM1) || ((INSTANCE) == PWM2) || ((INSTANCE) == PWM3) || ((INSTANCE) == PWM4) ) 


#define RCC_HSE_MIN          4000000U
#define RCC_HSE_MAX         32000000U

#define RCC_MAX_FREQUENCY  170000000U


/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PY32F410xB_H */

