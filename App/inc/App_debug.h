#ifndef __APP_DEBUG_H__
#define __APP_DEBUG_H__
#include "py32f4xx_hal.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>


#define APP_DEBUG_ENABLE 1

/* Custom HID 调试主命令 */

#define CMD_SYS_DEBUG 0xF3
#define DEBUG_PARAM_READ  0x00  /* 子命令：读取当前系统诊断数据 */
#define DEBUG_PARAM_CLEAR        0x01  /* 清除运行计数器 */
#define DEBUG_PARAM_ADC_FILTERED0 0x10  /* 0x10~0x14：读取第0~4行滤波ADC */
#define DEBUG_PARAM_ADC_FILTERED4 0x14
#define DEBUG_PARAM_ADC_RAW0      0x20  /* 0x20~0x24：读取第0~4行原始ADC */
#define DEBUG_PARAM_ADC_RAW4      0x24


/* 
 * 返回给上位机的诊断数据结构体（共56字节）
 * 采用 1 字节对齐，确保数据在 USB 传输中无空洞、无平台差异 
 */
#pragma pack(push, 1)
typedef struct{
    uint32_t uptime_ms;       /* MCU 系统运行时间（毫秒），通过读取 HAL_GetTick() 获取 */
    uint32_t main_count;      /* 主循环执行次数，用于判断大循环是否发生卡死/死循环 */
    uint32_t dma_count;       /* DMA 传输完成中断次数，用于确认 ADC 采样硬件是否在正常运转 */
    uint32_t frame_count;     /* 完成一轮（如 5 行磁轴）完整矩阵扫描的次数，用于监控按键扫描状态机 */
    uint32_t key_change_count; /* 按键状态变化次数 */
    uint32_t usb_count;       /* 0x81键盘报告提交成功次数 */

    uint8_t current_row;      /* 实时监控：当前正在扫描的矩阵行号（可检查行选切换是否卡死在某一行） */
    uint8_t state_flags;      /* 实时监控：系统当前状态标志位集合（ADC状态、扫描状态、USB忙闲等） */
    uint8_t error_code;       /* 故障追溯：记录最近一次发生的系统错误码（如 DMA 错误、USB 超时等） */
    uint8_t reserved;         /* 字节对齐预留 */

    uint32_t adc_timeout_count;
    uint32_t adc_timeout_tick;
    uint32_t adc_sr;
    uint32_t adc_cr2;
    uint32_t dma_isr;
    uint32_t dma_ccr;
    uint16_t dma_cndtr;
    uint8_t adc_timeout_row;
    uint8_t dma_irq_flags;
}AppDebugInfo_t;
typedef char AppDebugInfoSizeCheck[(sizeof(AppDebugInfo_t) <= 56U) ? 1 : -1];
typedef struct{
    uint8_t row;
    uint8_t value_type;      /* 0=原始ADC，1=滤波ADC */
    uint16_t adc[14];
} AppDebugAdcRow_t;
#pragma pack(pop)
 
/* 状态位定义（对应 state_flags） */
#define DEBUG_FLAG_ADC_COMPLETE  (1U << 0) /* 硬件 ADC 采样已完成（1：完成，0：未完成） */
#define DEBUG_FLAG_SCAN_COMPLETE (1U << 1) /* 键盘一帧扫描完成标志（1：扫描完成） */
#define DEBUG_FLAG_REPORT_DIRTY  (1U << 2) /* 按键值发生改变，等待发送 USB 报告（脏标记） */
#define DEBUG_FLAG_HID_BUSY      (1U << 3) /* USB 端点当前处于繁忙状态（正在发送上一个数据包） */
/* 错误类型定义（对应 error_code） */
#define DEBUG_ERROR_NONE       0U  /* 无任何错误 */
#define DEBUG_ERROR_DMA        1U  /* DMA 传输或硬件总线发生错误 */
#define DEBUG_ERROR_USB_SEND   2U  /* USB 底层驱动发送接口调用失败 */
#define DEBUG_ERROR_USB_BUSY   3U  /* USB 物理线路可能断线，导致端点长时间忙碌超时 */
#define DEBUG_ERROR_ADC_TIMEOUT 4U /* ADC/DMA scan completion timeout */
 
 
 /* 供其他模块调用的 API 接口 */
void App_debug_init(void);                  /* 调试模块初始化，清空所有数据 */
void App_debug_main_tick(void);             /* 主循环计数自增 */
void App_debug_dma_tick(uint8_t error);     /* DMA 传输计数自增，并传入硬件错误状态 */
void App_debug_frame_tick(void);            /* 完整扫描帧计数自增 */
void App_debug_key_change_tick(void);       /* 按键状态变化计数自增 */
void App_debug_usb_tick(void);              /* USB 成功发送计数自增 */
void App_debug_set_error(uint8_t error);    /* 发生异常时，手动记录错误码 */
void App_debug_capture_adc_timeout(uint8_t row);

 
/* 将当前的诊断信息打包写入发送载荷，返回实际打包的数据长度 */
uint8_t App_debug_handle(uint8_t parameter,
                         uint8_t *payload,
                         uint8_t capacity);
 

#endif