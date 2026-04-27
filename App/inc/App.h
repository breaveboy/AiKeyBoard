#ifndef __APP_H__
#define __APP_H__
#include "usbd_core.h"
#include "usbd_hid.h"
void App_init(void);

void App_adkey_scan_task(void);
void App_lighting_process_task(void);
void App_display_task(void);
void App_logic_handler_task(void);
void App_usb_process_task(void);

void App_usb_test_task(void);
void App_ws2812_breath_task(void);
void App_ws2812_rainbow_task(void);
#endif
