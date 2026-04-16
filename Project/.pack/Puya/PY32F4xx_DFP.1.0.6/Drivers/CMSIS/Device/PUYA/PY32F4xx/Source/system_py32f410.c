/**
  ******************************************************************************
  * @file    system_py32f410.c
  * @author  MCU Application Team
  * @brief   CMSIS Cortex-M4 Device Peripheral Access Layer System Source File
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

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup py32f410_system
  * @{
  */  
  
/** @addtogroup py32f410_System_Private_Includes
  * @{
  */

#include "py32f4xx.h"

#if !defined  (HSE_VALUE) 
  #define HSE_VALUE    ((uint32_t)24000000) /*!< Default value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE    ((uint32_t)8000000) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

/**
  * @}
  */

/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x00 /*!< Vector Table base offset field. 
                                   This value must be a multiple of 0x200. */
/******************************************************************************/


/** @addtogroup PY32F410_System_Private_Variables
  * @{
  */
  /* This variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetHCLKFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency 
         Note: If you use this function to configure the system clock; then there
               is no need to call the 2 first functions listed above, since SystemCoreClock
               variable is updated automatically.
  */
uint32_t SystemCoreClock = HSI_VALUE;
const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APBPrescTable[8]  = {0, 0, 0, 0, 1, 2, 3, 4};
/**
  * @}
  */

/** @addtogroup PY32F410_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system
  *         Initialize the FPU setting, vector table location and External memory 
  *         configuration.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
  RCC->AHBENR |= RCC_AHBENR_IOPDEN;
  while(1)
  {
    if (((FLASH->OPTR2 & FLASH_OPTR2_NRST_MODE) == FLASH_OPTR2_NRST_MODE_1) || 
        (((FLASH->OPTR2 & FLASH_OPTR2_NRST_MODE) != FLASH_OPTR2_NRST_MODE_1) && ((GPIOD->IDR & GPIO_PIN_11) != RESET)))
    {
      /* Set the HSI clock to 8MHz by default */
      RCC->CR = (RCC->CR & 0xF3FF800F) | (((*(uint32_t *)(0x1FFF1200)) & 0x7FF) << 4);
      break;
    } 
  }
  RCC->AHBENR &= ~RCC_AHBENR_IOPDEN;
  
  /* Configure the Vector Table location add offset address ------------------*/
#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH */
#endif
}

/**
   * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *           
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.         
  *     
  * @note   - The system frequency computed by this function is not the real 
  *           frequency in the chip. It is calculated based on the predefined 
  *           constant and the selected clock source:
  *             
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(*)
  *                                              
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(**)
  *                          
  *           - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(**) 
  *             or HSI_VALUE(*) multiplied/divided by the PLL factors.
  *         
  *         (*) HSI_VALUE is a constant defined in py32f410_hal_conf.h file (default value
  *             16 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.   
  *    
  *         (**) HSE_VALUE is a constant defined in py32f410_hal_conf.h file (its value
  *              depends on the application requirements), user has to ensure that HSE_VALUE
  *              is same as the real frequency of the crystal used. Otherwise, this function
  *              may have wrong result.
  *                
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.
  *     
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
  uint32_t tmpreg = 0U,tmppllreg=0, pllclk = 0U, pllmul = 0U, hsiIndex = 0U;
  uint32_t tmp = 0;
  const uint32_t hsiValue[4] = {8000000, 16000000, 24000000, 48000000};
  
  tmpreg = RCC->CFGR;
  tmppllreg = RCC->CFGR3;
  /* Get SYSCLK source -------------------------------------------------------*/
  switch (tmpreg & RCC_CFGR_SWS)
  {
    case 0x00:  /* HSI used as system clock source */
    {
      hsiIndex = (RCC->CR & RCC_CR_HSIFS) >> RCC_CR_HSIFS_Pos;
      SystemCoreClock = (uint32_t)hsiValue[hsiIndex];
      break;
    }
    
    case 0x04:  /* HSE used as system clock */
    {
      SystemCoreClock = HSE_VALUE;
      break;
    }
    
    case 0x08:  /* PLL used as system clock */
    {
      pllmul = (READ_BIT(RCC->CFGR3, RCC_CFGR3_PLLMUL) >> RCC_CFGR3_PLLMUL_Pos) + 2U;
      if ((tmppllreg & RCC_CFGR3_PLLSRC) == RCC_PLLSOURCE_HSE)
      {
        /* HSE used as PLL clock source : PLLCLK = HSE * PLLMUL */
        pllclk = (uint32_t)(HSE_VALUE * pllmul);
      }
      else
      {
        hsiIndex = (RCC->CR & RCC_CR_HSIFS) >> RCC_CR_HSIFS_Pos;
        /* HSI used as PLL clock source : PLLCLK = HSI * PLLMUL */
        pllclk = (uint32_t)(hsiValue[hsiIndex] * pllmul);
      }
      SystemCoreClock = pllclk;
      break;
    }
    
    default:
    {
      break;
    } 
  }
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos)];
  SystemCoreClock >>= tmp;
}

/**
  * @}
  */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
