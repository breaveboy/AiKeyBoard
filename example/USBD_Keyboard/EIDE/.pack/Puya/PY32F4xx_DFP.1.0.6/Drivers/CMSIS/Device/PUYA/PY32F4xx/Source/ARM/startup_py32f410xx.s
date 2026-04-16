;****************************************************************************** 
;* @file    startup_py32f410xx.s
;* @author  MCU Application Team
;* @brief   PY32F410xx devices vector table for MDK-ARM toolchain.
;*          This module performs:
;*          - Set the initial SP
;*          - Set the initial PC == Reset_Handler
;*          - Set the vector table entries with the exceptions ISR address
;*          - Branches to __main in the C library (which eventually
;*            calls main()).
;*          After Reset the CortexM4 processor is in Thread mode,
;*          priority is Privileged, and the Stack is set to Main.
;****************************************************************************** 
;* @attention
;*
;* <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
;* All rights reserved.</center></h2>
;*
;* This software component is licensed by Puya under BSD 3-Clause license,
;* the "License"; You may not use this file except in compliance with the
;* License. You may obtain a copy of the License at:
;*                        opensource.org/licenses/BSD-3-Clause
;*
;******************************************************************************
;* @attention
;*
;* <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
;* All rights reserved.</center></h2>
;*
;* This software component is licensed by ST under BSD 3-Clause license,
;* the "License"; You may not use this file except in compliance with the
;* License. You may obtain a copy of the License at:
;*                        opensource.org/licenses/BSD-3-Clause
;*
;****************************************************************************** 
;* <<< Use Configuration Wizard in Context Menu >>>

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp               ; Top of Stack
                DCD     Reset_Handler              ; Reset Handler
                DCD     NMI_Handler                ; NMI Handler
                DCD     HardFault_Handler          ; Hard Fault Handler
                DCD     MemManage_Handler          ; MPU Fault Handler
                DCD     BusFault_Handler           ; Bus Fault Handler
                DCD     UsageFault_Handler         ; Usage Fault Handler
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     SVC_Handler                ; SVCall Handler
                DCD     DebugMon_Handler           ; Debug Monitor Handler
                DCD     0                          ; Reserved
                DCD     PendSV_Handler             ; PendSV Handler
                DCD     SysTick_Handler            ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler               ; Window Watchdog
                DCD     PVD_IRQHandler                ; PVD through EXTI Line detect
                DCD     TAMPER_IRQHandler             ; Tamper
                DCD     RTC_IRQHandler                ; RTC
                DCD     FLASH_IRQHandler              ; Flash
                DCD     RCC_IRQHandler                ; RCC
                DCD     EXTI0_IRQHandler              ; EXTI Line 0
                DCD     EXTI1_IRQHandler              ; EXTI Line 1
                DCD     EXTI2_IRQHandler              ; EXTI Line 2
                DCD     EXTI3_IRQHandler              ; EXTI Line 3
                DCD     EXTI4_IRQHandler              ; EXTI Line 4
                DCD     EXTI9_5_IRQHandler            ; EXTI Line[9:5]
                DCD     EXTI15_10_IRQHandler          ; EXTI Line[15:10]
                DCD     DMA1_Channel1_IRQHandler      ; DMA1 Channel 1
                DCD     DMA1_Channel2_IRQHandler      ; DMA1 Channel 2
                DCD     DMA1_Channel3_IRQHandler      ; DMA1 Channel 3
                DCD     DMA1_Channel4_IRQHandler      ; DMA1 Channel 4
                DCD     DMA1_Channel5_IRQHandler      ; DMA1 Channel 5
                DCD     DMA1_Channel6_IRQHandler      ; DMA1 Channel 6
                DCD     DMA1_Channel7_IRQHandler      ; DMA1 Channel 7
                DCD     DMA1_Channel8_IRQHandler      ; DMA1 Channel 8
                DCD     ADC_IRQHandler                ; ADC
                DCD     TIM1_BRK_IRQHandler           ; TIM1 Break
                DCD     TIM1_UP_IRQHandler            ; TIM1 Update
                DCD     TIM1_TRG_COM_IRQHandler       ; TIM1 Trigger and Commutation
                DCD     TIM1_CC_IRQHandler            ; TIM1 Capture Compare
                DCD     TIM2_IRQHandler               ; TIM2
                DCD     TIM3_IRQHandler               ; TIM3
                DCD     TIM4_IRQHandler               ; TIM4
                DCD     TIM6_IRQHandler               ; TIM6
                DCD     TIM7_IRQHandler               ; TIM7
                DCD     TIM15_IRQHandler              ; TIM15
                DCD     TIM16_IRQHandler              ; TIM16
                DCD     TIM17_IRQHandler              ; TIM17
                DCD     PWM1_IRQHandler               ; PWM1
                DCD     PWM2_IRQHandler               ; PWM2
                DCD     PWM3_IRQHandler               ; PWM3
                DCD     PWM4_IRQHandler               ; PWM4
                DCD     LPTIM_IRQHandler              ; LPTIM
                DCD     SPI1_IRQHandler               ; SPI1
                DCD     SPI2_IRQHandler               ; SPI2
                DCD     USART_IRQHandler              ; USART
                DCD     UART1_IRQHandler              ; UART1
                DCD     UART2_IRQHandler              ; UART2
                DCD     LPUART_IRQHandler             ; LPUART
                DCD     RTC_Alarm_IRQHandler          ; RTC Alarm through EXTI Line
                DCD     I2C1_EV_IRQHandler            ; I2C1 Event
                DCD     I2C1_ER_IRQHandler            ; I2C1 Error
                DCD     I2C2_EV_IRQHandler            ; I2C2 Event
                DCD     I2C2_ER_IRQHandler            ; I2C2 Error
                DCD     COMP1_IRQHandler              ; COMP1
                DCD     COMP2_IRQHandler              ; COMP2
                DCD     OPA2_IRQHandler               ; OPA2

__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler          [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler          [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler           [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler           [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler             [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler            [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler               [WEAK]
                EXPORT  PVD_IRQHandler                [WEAK]
                EXPORT  TAMPER_IRQHandler             [WEAK]
                EXPORT  RTC_IRQHandler                [WEAK]
                EXPORT  FLASH_IRQHandler              [WEAK]
                EXPORT  RCC_IRQHandler                [WEAK]
                EXPORT  EXTI0_IRQHandler              [WEAK]
                EXPORT  EXTI1_IRQHandler              [WEAK]
                EXPORT  EXTI2_IRQHandler              [WEAK]
                EXPORT  EXTI3_IRQHandler              [WEAK]
                EXPORT  EXTI4_IRQHandler              [WEAK]
                EXPORT  EXTI9_5_IRQHandler            [WEAK]
                EXPORT  EXTI15_10_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler      [WEAK]
                EXPORT  DMA1_Channel8_IRQHandler      [WEAK]
                EXPORT  ADC_IRQHandler                [WEAK]
                EXPORT  TIM1_BRK_IRQHandler           [WEAK]
                EXPORT  TIM1_UP_IRQHandler            [WEAK]
                EXPORT  TIM1_TRG_COM_IRQHandler       [WEAK]
                EXPORT  TIM1_CC_IRQHandler            [WEAK]
                EXPORT  TIM2_IRQHandler               [WEAK]
                EXPORT  TIM3_IRQHandler               [WEAK]
                EXPORT  TIM4_IRQHandler               [WEAK]
                EXPORT  TIM6_IRQHandler               [WEAK]
                EXPORT  TIM7_IRQHandler               [WEAK]
                EXPORT  TIM15_IRQHandler              [WEAK]
                EXPORT  TIM16_IRQHandler              [WEAK]
                EXPORT  TIM17_IRQHandler              [WEAK]
                EXPORT  PWM1_IRQHandler               [WEAK]
                EXPORT  PWM2_IRQHandler               [WEAK]
                EXPORT  PWM3_IRQHandler               [WEAK]
                EXPORT  PWM4_IRQHandler               [WEAK]
                EXPORT  LPTIM_IRQHandler              [WEAK]
                EXPORT  SPI1_IRQHandler               [WEAK]
                EXPORT  SPI2_IRQHandler               [WEAK]
                EXPORT  USART_IRQHandler              [WEAK]
                EXPORT  UART1_IRQHandler              [WEAK]
                EXPORT  UART2_IRQHandler              [WEAK]
                EXPORT  LPUART_IRQHandler             [WEAK]
                EXPORT  RTC_Alarm_IRQHandler          [WEAK]
                EXPORT  I2C1_EV_IRQHandler            [WEAK]
                EXPORT  I2C1_ER_IRQHandler            [WEAK]
                EXPORT  I2C2_EV_IRQHandler            [WEAK]
                EXPORT  I2C2_ER_IRQHandler            [WEAK]
                EXPORT  COMP1_IRQHandler              [WEAK]
                EXPORT  COMP2_IRQHandler              [WEAK]
                EXPORT  OPA2_IRQHandler               [WEAK]
                  
WWDG_IRQHandler
PVD_IRQHandler
TAMPER_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
RCC_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
EXTI9_5_IRQHandler
EXTI15_10_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
DMA1_Channel8_IRQHandler
ADC_IRQHandler
TIM1_BRK_IRQHandler
TIM1_UP_IRQHandler
TIM1_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_IRQHandler
TIM4_IRQHandler
TIM6_IRQHandler
TIM7_IRQHandler
TIM15_IRQHandler
TIM16_IRQHandler
TIM17_IRQHandler
PWM1_IRQHandler
PWM2_IRQHandler
PWM3_IRQHandler
PWM4_IRQHandler
LPTIM_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
LPUART_IRQHandler
RTC_Alarm_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
COMP1_IRQHandler
COMP2_IRQHandler
OPA2_IRQHandler

                B       .
                ENDP

                ALIGN

; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
                    
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF

                END

;************************ (C) COPYRIGHT Puya *****END OF FILE*******************
