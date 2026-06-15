#include "App_debug.h"

#include "App_key.h"
#include "lib_hall_sensor.h"
#include "py32f4xx_hal.h"

#include <string.h>

#if APP_DEBUG_ENABLE

/* 
 * 引入键盘核心模块的全局运行变量，
 * 通过调试模块将其统一打包暴漏给上位机，以便进行状态比对。
 */
extern volatile uint8_t g_current_row;   /* 磁轴矩阵当前扫描行 */
extern volatile uint8_t g_adc_complete;  /* 硬件 ADC 转换完成标志 */
extern volatile uint8_t g_scan_complete; /* 键盘一帧扫描完成标志 */
extern volatile uint8_t hid_state;       /* USB HID 驱动发送忙闲状态 */
extern bool report_dirty;                /* 按键脏标记，提示是否有数据待发送 */

/* 内部全局调试统计实体 */
static AppDebugInfo_t g_debug;

/**
 * @brief 调试模块初始化
 * @note 清空全局调试结构体
 */
void App_debug_init(void)
{
    memset(&g_debug, 0, sizeof(g_debug));
}

/**
 * @brief 主循环计数累加
 * @note 应放置在 main.c 的 while(1) 循环最前端，其增速反映了主循环的调度频次
 */
void App_debug_main_tick(void)
{
    g_debug.main_count++;
}

/**
 * @brief DMA 计数自增及错误抓取
 * @param error 传入 DMA 通道是否有传输错误（TEIF 标志）
 */
void App_debug_dma_tick(uint8_t error)
{
    g_debug.dma_count++;

    // 如果 DMA 产生了传输错误，记录对应的错误码
    if (error) {
        g_debug.error_code = DEBUG_ERROR_DMA;
    }
}

/**
 * @brief 完整矩阵扫描帧数累加
 * @note 当按键状态机走完所有行（如5行）并完成按键消抖/行程处理后，调用此 Tick
 */
void App_debug_frame_tick(void)
{
    g_debug.frame_count++;
}

/**
 * @brief USB 数据包成功发送计数
 * @note 仅在底层 USB IN 端点发送函数返回成功（0）时累加
 */
void App_debug_key_change_tick(void)
{
    g_debug.key_change_count++;
}

void App_debug_usb_tick(void)
{
    g_debug.usb_count++;
}

/**
 * @brief 设置系统最近一次的错误代码
 * @param error 异常错误码（如 USB 忙超时等）
 */
void App_debug_set_error(uint8_t error)
{
    g_debug.error_code = error;
}

void App_debug_capture_adc_timeout(uint8_t row)
{
    g_debug.error_code = DEBUG_ERROR_ADC_TIMEOUT;
    g_debug.adc_timeout_count++;
    g_debug.adc_timeout_tick = HAL_GetTick();
    g_debug.adc_sr = ADC1->SR;
    g_debug.adc_cr2 = ADC1->CR2;
    g_debug.dma_isr = DMA1->ISR;
    g_debug.dma_ccr = DMA1_Channel1->CCR;
    g_debug.dma_cndtr = (uint16_t)DMA1_Channel1->CNDTR;
    g_debug.adc_timeout_row = row;
    g_debug.dma_irq_flags = 0U;
    if (NVIC_GetEnableIRQ(DMA1_Channel1_IRQn) != 0U) {
        g_debug.dma_irq_flags |= 0x01U;
    }
    if (NVIC_GetPendingIRQ(DMA1_Channel1_IRQn) != 0U) {
        g_debug.dma_irq_flags |= 0x02U;
    }
}

/**
 * @brief 在回传上位机前，获取并刷新系统实时的引脚和硬件状态
 */
static void App_debug_update_state(void)
{
    uint8_t flags = 0U;

    // 1. 获取 MCU 自上电以来的运行毫秒数
    g_debug.uptime_ms = HAL_GetTick();
    
    // 2. 获取当前的扫描行
    g_debug.current_row = g_current_row;

    // 3. 收集并组装状态标志位
    if (g_adc_complete) {
        flags |= DEBUG_FLAG_ADC_COMPLETE;
    }

    if (g_scan_complete) {
        flags |= DEBUG_FLAG_SCAN_COMPLETE;
    }

    if (report_dirty) {
        flags |= DEBUG_FLAG_REPORT_DIRTY;
    }

    // hid_state 为非 0 代表 USB 驱动处于发送忙碌中（在等待 PC 端取走数据）
    if (hid_state != 0U) {
        flags |= DEBUG_FLAG_HID_BUSY;
    }

    g_debug.state_flags = flags;
}

/**
 * @brief 接收协议层分发的调试指令，读出或清空计数器
 * @param parameter 子命令参数 (0x00=读取, 0x01=清空)
 * @param payload 传入协议响应的缓存区指针
 * @param capacity 传入协议响应缓存区的最大容量
 * @return 写入缓存区的数据长度（字节）
 */
static uint8_t App_debug_read_adc_row(uint8_t parameter,
                                      uint8_t *payload,
                                      uint8_t capacity)
{
    AppDebugAdcRow_t response;
    const uint16_t *source;
    uint8_t row;

    if (capacity < sizeof(response)) {
        return 0U;
    }

    if ((parameter >= DEBUG_PARAM_ADC_FILTERED0) &&
        (parameter <= DEBUG_PARAM_ADC_FILTERED4)) {
        row = (uint8_t)(parameter - DEBUG_PARAM_ADC_FILTERED0);
        response.value_type = 1U;
        source = g_hall_adc_frame[row];
    } else if ((parameter >= DEBUG_PARAM_ADC_RAW0) &&
               (parameter <= DEBUG_PARAM_ADC_RAW4)) {
        row = (uint8_t)(parameter - DEBUG_PARAM_ADC_RAW0);
        response.value_type = 0U;
        source = g_hall_adc_raw_frame[row];
    } else {
        return 0U;
    }

    response.row = row;
    memcpy(response.adc, source, sizeof(response.adc));
    memcpy(payload, &response, sizeof(response));
    return (uint8_t)sizeof(response);
}

uint8_t App_debug_handle(uint8_t parameter,
                         uint8_t *payload,
                         uint8_t capacity)
{
    if (payload == NULL) {
        return 0U;
    }

    if (((parameter >= DEBUG_PARAM_ADC_FILTERED0) &&
         (parameter <= DEBUG_PARAM_ADC_FILTERED4)) ||
        ((parameter >= DEBUG_PARAM_ADC_RAW0) &&
         (parameter <= DEBUG_PARAM_ADC_RAW4))) {
        return App_debug_read_adc_row(parameter, payload, capacity);
    }

    // 处理读取命令
    if (parameter == DEBUG_PARAM_READ) {
        if (capacity < sizeof(g_debug)) {
            return 0U;
        }
        App_debug_update_state();                      // 先刷新一次实时状态
        memcpy(payload, &g_debug, sizeof(g_debug));    // 深拷贝到发送缓存
        return (uint8_t)sizeof(g_debug);              // 返回诊断数据的长度
    }

    // 处理清除命令
    if (parameter == DEBUG_PARAM_CLEAR) {
        App_debug_init();                              // 重置所有计数器为零
    }

    return 0U;
}

#else

/* 
 * 当编译开关 APP_DEBUG_ENABLE = 0 时，编译以下空函数。
 * 编译器会自动将其彻底优化掉，不产生任何 CPU 开销，不占用任何 Flash/RAM 空间。
 */
void App_debug_init(void) {}
void App_debug_main_tick(void) {}
void App_debug_dma_tick(uint8_t error) { (void)error; }
void App_debug_frame_tick(void) {}
void App_debug_key_change_tick(void) {}
void App_debug_usb_tick(void) {}
void App_debug_set_error(uint8_t error) { (void)error; }
void App_debug_capture_adc_timeout(uint8_t row) { (void)row; }

uint8_t App_debug_handle(uint8_t parameter,
                         uint8_t *payload,
                         uint8_t capacity)
{
    (void)parameter;
    (void)payload;
    (void)capacity;
    return 0U;
}

#endif