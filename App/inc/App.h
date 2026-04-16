#ifndef __APP_H__
#define __APP_H__

void App_init(void);

void App_adkey_scan_task(void);
void App_logic_handler_task(void);
void App_usb_process_task(void);
void App_usb_test_task(void);

#endif
