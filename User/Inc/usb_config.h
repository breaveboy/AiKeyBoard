/*
 * Copyright (c) 2026
 * Minimal USB HID keyboard demo for PY32F403 + CherryUSB.
 */
#ifndef CHERRYUSB_CONFIG_H
#define CHERRYUSB_CONFIG_H

/* ================ USB common Configuration ================ */

#define CONFIG_USB_PRINTF(...) //printf(__VA_ARGS__)

#define usb_malloc(size) malloc(size)
#define usb_free(ptr)    free(ptr)

#ifndef CONFIG_USB_DBG_LEVEL
#define CONFIG_USB_DBG_LEVEL USB_DBG_ERROR
#endif

#define CONFIG_USB_PRINTF_COLOR_ENABLE

#ifndef CONFIG_USB_ALIGN_SIZE
#define CONFIG_USB_ALIGN_SIZE 4
#endif

#define USB_NOCACHE_RAM_SECTION __attribute__((section(".noncacheable")))

/* ================= USB Device Stack Configuration ================ */
#define CONFIG_USBDEV_REQUEST_BUFFER_LEN 256

#ifndef CONFIG_USBDEV_MSC_BLOCK_SIZE
#define CONFIG_USBDEV_MSC_BLOCK_SIZE 512
#endif

#ifndef CONFIG_USBDEV_MSC_MANUFACTURER_STRING
#define CONFIG_USBDEV_MSC_MANUFACTURER_STRING ""
#endif

#ifndef CONFIG_USBDEV_MSC_PRODUCT_STRING
#define CONFIG_USBDEV_MSC_PRODUCT_STRING ""
#endif

#ifndef CONFIG_USBDEV_MSC_VERSION_STRING
#define CONFIG_USBDEV_MSC_VERSION_STRING "0.01"
#endif

#ifndef CONFIG_USBDEV_AUDIO_VERSION
#define CONFIG_USBDEV_AUDIO_VERSION 0x0100
#endif

#ifndef CONFIG_USBDEV_AUDIO_MAX_CHANNEL
#define CONFIG_USBDEV_AUDIO_MAX_CHANNEL 8
#endif

#include "py32f4xx_hal.h"

#define __HAL_USB_SOFT_RESET()     do { \
                                     __HAL_RCC_USB_CLK_DISABLE(); \
                                     HAL_Delay(10); \
                                     __HAL_RCC_USB_CLK_ENABLE();  \
                                   } while (0U)

#define USBD_IRQn       USB_IRQn
#define USBD_IRQHandler USBD_IRQHandler

void hid_keyboard_init(void);
uint8_t hid_keyboard_is_configured(void);
int hid_keyboard_send_report(const uint8_t report[8]);
int hid_keyboard_send_key(uint8_t keycode);
void hid_keyboard_test(void);

#endif
