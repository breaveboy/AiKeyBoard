#ifndef __APP_H__
#define __APP_H__
#include "usbd_core.h"
#include "usbd_hid.h"


















void App_init(void);
void App_adkey_scan_task(void);
void App_lighting_process_task(void);
void App_display_task(void);

void App_usb_process_task(void);

/**
 * @brief 任务3：灯光业务逻辑处理 (建议 10ms)
 * 处理内部功能键请求（如切换灯效模式、开关灯等）
 */
void App_led_logic_task(void);

/**
 * @brief 任务4：灯光动画演算 (建议 20ms - 30ms)
 * 根据当前模式（彩虹、呼吸等）计算每个 LED 的 RGB 颜色数值
 */
void App_led_animation_task(void);

/**
 * @brief 任务5：物理显示刷新 (建议 30ms)
 * 调用硬件驱动接口（SPI/DMA）将颜色数据推送到 WS2812 灯珠
 */
void App_led_display_task(void);

extern void App_protocol_task(void);

#endif
