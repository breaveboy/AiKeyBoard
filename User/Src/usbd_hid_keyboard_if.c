#include "usbd_core.h"
#include "usbd_hid.h"
#include <stdio.h>
#include <string.h>
#include "lib_ws2812.h"
/* ================= USB 基本信息 ================= */

#define USBD_VID           0x36b7
#define USBD_PID           0xffff
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

/* ================= 标准键盘 HID：保持和 App.c 兼容 ================= */

#define HID_INT_EP          0x81
#define HID_INT_EP_SIZE     8
#define HID_INT_EP_INTERVAL 10

/* ================= 自定义 HID ================= */

#define HID_CUSTOM_OUT_EP      0x02    /* PC -> MCU */
#define HID_CUSTOM_IN_EP       0x82    /* MCU -> PC */
#define HID_CUSTOM_EP_SIZE     64
#define HID_CUSTOM_INTERVAL    1
#define CUSTOM_REPORT_ID       0x05

/*
 * 配置描述符长度：
 * Config Descriptor: 9
 * Keyboard Interface: 9
 * Keyboard HID Descriptor: 9
 * Keyboard IN Endpoint: 7
 * Custom Interface: 9
 * Custom HID Descriptor: 9
 * Custom OUT Endpoint: 7
 * Custom IN Endpoint: 7
 *
 * 总计 = 66
 */
#define USB_HID_CONFIG_DESC_SIZ       66
#define HID_KEYBOARD_REPORT_DESC_SIZE 64
#define HID_CUSTOM_REPORT_DESC_SIZE   36

#define HID_STATE_IDLE 0
#define HID_STATE_BUSY 1

/* 键盘 IN 端点状态，App.c 里面会用到 */
volatile uint8_t hid_state = HID_STATE_IDLE;

/* 自定义 HID IN 端点状态 */
static volatile uint8_t custom_hid_state = HID_STATE_IDLE;

/* ================= USB 描述符 ================= */

static const uint8_t hid_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(
        USB_2_0,
        0x00,
        0x00,
        0x00,
        USBD_VID,
        USBD_PID,
        0x0002,
        0x01
    ),

    /*
     * bNumInterfaces = 0x02
     * Interface 0 = 标准键盘 HID
     * Interface 1 = 自定义 HID
     */
    USB_CONFIG_DESCRIPTOR_INIT(
        USB_HID_CONFIG_DESC_SIZ,
        0x02,
        0x01,
        USB_CONFIG_BUS_POWERED,
        USBD_MAX_POWER
    ),

    /**************** Interface 0: Standard Keyboard HID ****************/
    0x09,                          /* bLength */
    USB_DESCRIPTOR_TYPE_INTERFACE, /* bDescriptorType */
    0x00,                          /* bInterfaceNumber = 0 */
    0x00,                          /* bAlternateSetting */
    0x01,                          /* bNumEndpoints = 1 */
    0x03,                          /* bInterfaceClass = HID */
    0x00,                          /* bInterfaceSubClass = no boot */
    0x01,                          /* bInterfaceProtocol = keyboard */
    0x00,                          /* iInterface */

    /**************** Keyboard HID Descriptor ****************/
    0x09,                          /* bLength */
    HID_DESCRIPTOR_TYPE_HID,       /* bDescriptorType */
    0x11, 0x01,                    /* bcdHID = 1.11 */
    0x00,                          /* bCountryCode */
    0x01,                          /* bNumDescriptors */
    0x22,                          /* bDescriptorType = Report */
    HID_KEYBOARD_REPORT_DESC_SIZE,
    0x00,

    /**************** Keyboard IN Endpoint ****************/
    0x07,                          /* bLength */
    USB_DESCRIPTOR_TYPE_ENDPOINT,  /* bDescriptorType */
    HID_INT_EP,                    /* bEndpointAddress = 0x81 */
    0x03,                          /* bmAttributes = Interrupt */
    HID_INT_EP_SIZE,               /* wMaxPacketSize = 8 */
    0x00,
    HID_INT_EP_INTERVAL,           /* bInterval */

    /**************** Interface 1: Custom HID ****************/
    0x09,                          /* bLength */
    USB_DESCRIPTOR_TYPE_INTERFACE, /* bDescriptorType */
    0x01,                          /* bInterfaceNumber = 1 */
    0x00,                          /* bAlternateSetting */
    0x02,                          /* bNumEndpoints = 2 */
    0x03,                          /* bInterfaceClass = HID */
    0x00,                          /* bInterfaceSubClass = none */
    0x00,                          /* bInterfaceProtocol = none */
    0x00,                          /* iInterface */

    /**************** Custom HID Descriptor ****************/
    0x09,                          /* bLength */
    HID_DESCRIPTOR_TYPE_HID,       /* bDescriptorType */
    0x11, 0x01,                    /* bcdHID = 1.11 */
    0x00,                          /* bCountryCode */
    0x01,                          /* bNumDescriptors */
    0x22,                          /* bDescriptorType = Report */
    HID_CUSTOM_REPORT_DESC_SIZE,
    0x00,

    /**************** Custom HID OUT Endpoint: PC -> MCU ****************/
    0x07,                          /* bLength */
    USB_DESCRIPTOR_TYPE_ENDPOINT,  /* bDescriptorType */
    HID_CUSTOM_OUT_EP,             /* bEndpointAddress = 0x02 */
    0x03,                          /* bmAttributes = Interrupt */
    HID_CUSTOM_EP_SIZE,            /* wMaxPacketSize = 64 */
    0x00,
    HID_CUSTOM_INTERVAL,           /* bInterval */

    /**************** Custom HID IN Endpoint: MCU -> PC ****************/
    0x07,                          /* bLength */
    USB_DESCRIPTOR_TYPE_ENDPOINT,  /* bDescriptorType */
    HID_CUSTOM_IN_EP,              /* bEndpointAddress = 0x82 */
    0x03,                          /* bmAttributes = Interrupt */
    HID_CUSTOM_EP_SIZE,            /* wMaxPacketSize = 64 */
    0x00,
    HID_CUSTOM_INTERVAL,           /* bInterval */

    /**************** String Descriptor 0: LANGID ****************/
    USB_LANGID_INIT(USBD_LANGID_STRING),

    /**************** String Descriptor 1: Manufacturer = WSK ****************/
    0x08,
    USB_DESCRIPTOR_TYPE_STRING,
    'W', 0x00,
    'S', 0x00,
    'K', 0x00,

    /**************** String Descriptor 2: Product = HID AI KEYBOARD ****************/
    0x20,
    USB_DESCRIPTOR_TYPE_STRING,
    'H', 0x00,
    'I', 0x00,
    'D', 0x00,
    ' ', 0x00,
    'A', 0x00,
    'I', 0x00,
    ' ', 0x00,
    'K', 0x00,
    'E', 0x00,
    'Y', 0x00,
    'B', 0x00,
    'O', 0x00,
    'A', 0x00,
    'R', 0x00,
    'D', 0x00,

    /**************** String Descriptor 3: Serial Number = 20260422 ****************/
    0x12,
    USB_DESCRIPTOR_TYPE_STRING,
    '2', 0x00,
    '0', 0x00,
    '2', 0x00,
    '6', 0x00,
    '0', 0x00,
    '4', 0x00,
    '2', 0x00,
    '2', 0x00,

#ifdef CONFIG_USB_HS
    /**************** Device Qualifier Descriptor ****************/
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x01,
    0x00,
#endif

    0x00
};

/* ================= 标准键盘 Report Descriptor ================= */

static const uint8_t hid_keyboard_report_desc[HID_KEYBOARD_REPORT_DESC_SIZE] = {
    0x05, 0x01,        /* USAGE_PAGE (Generic Desktop) */
    0x09, 0x06,        /* USAGE (Keyboard) */
    0xA1, 0x01,        /* COLLECTION (Application) */

    0x05, 0x07,        /* USAGE_PAGE (Keyboard) */
    0x19, 0xE0,        /* USAGE_MINIMUM (Keyboard LeftControl) */
    0x29, 0xE7,        /* USAGE_MAXIMUM (Keyboard Right GUI) */
    0x15, 0x00,        /* LOGICAL_MINIMUM (0) */
    0x25, 0x01,        /* LOGICAL_MAXIMUM (1) */
    0x75, 0x01,        /* REPORT_SIZE (1) */
    0x95, 0x08,        /* REPORT_COUNT (8) */
    0x81, 0x02,        /* INPUT (Data,Var,Abs) */

    0x95, 0x01,        /* REPORT_COUNT (1) */
    0x75, 0x08,        /* REPORT_SIZE (8) */
    0x81, 0x03,        /* INPUT (Cnst,Var,Abs) */

    0x05, 0x08,        /* USAGE_PAGE (LEDs) */
    0x19, 0x01,        /* USAGE_MINIMUM (Num Lock) */
    0x29, 0x05,        /* USAGE_MAXIMUM (Kana) */
    0x95, 0x05,        /* REPORT_COUNT (5) */
    0x75, 0x01,        /* REPORT_SIZE (1) */
    0x91, 0x02,        /* OUTPUT (Data,Var,Abs) */

    0x95, 0x01,        /* REPORT_COUNT (1) */
    0x75, 0x03,        /* REPORT_SIZE (3) */
    0x91, 0x03,        /* OUTPUT (Cnst,Var,Abs) */

    0x95, 0x06,        /* REPORT_COUNT (6) */
    0x75, 0x08,        /* REPORT_SIZE (8) */
    0x15, 0x00,        /* LOGICAL_MINIMUM (0) */
    0x26, 0xFF, 0x00,  /* LOGICAL_MAXIMUM (255) */
    0x05, 0x07,        /* USAGE_PAGE (Keyboard) */
    0x19, 0x00,        /* USAGE_MINIMUM (Reserved) */
    0x29, 0x64,        /* USAGE_MAXIMUM (Keyboard Application) */
    0x81, 0x00,        /* INPUT (Data,Ary,Abs) */

    0xC0               /* END_COLLECTION */
};

/* ================= 自定义 HID Report Descriptor =================
 *
 * 使用 Report ID = 0x05
 *
 * PC -> MCU:
 *   64 字节，其中 Byte0 = Report ID，Byte1~Byte63 = 自定义数据
 *
 * MCU -> PC:
 *   64 字节，其中 Byte0 = Report ID，Byte1~Byte63 = 自定义数据
 */
static const uint8_t hid_custom_report_desc[HID_CUSTOM_REPORT_DESC_SIZE] = {
    0x06, 0x00, 0xFF,       /* Usage Page: Vendor Defined 0xFF00 */
    0x09, 0x01,             /* Usage */
    0xA1, 0x01,             /* Collection Application */

    0x85, CUSTOM_REPORT_ID, /* Report ID = 0x05 */

    /* OUT Report: PC -> MCU, 63 bytes payload */
    0x09, 0x01,             /* Usage */
    0x15, 0x00,             /* Logical Min 0 */
    0x26, 0xFF, 0x00,       /* Logical Max 255 */
    0x75, 0x08,             /* Report Size = 8 bit */
    0x95, 0x3F,             /* Report Count = 63 bytes */
    0x91, 0x02,             /* Output Data,Var,Abs */

    /* IN Report: MCU -> PC, 63 bytes payload */
    0x09, 0x02,             /* Usage */
    0x15, 0x00,             /* Logical Min 0 */
    0x26, 0xFF, 0x00,       /* Logical Max 255 */
    0x75, 0x08,             /* Report Size = 8 bit */
    0x95, 0x3F,             /* Report Count = 63 bytes */
    0x81, 0x02,             /* Input Data,Var,Abs */

    0xC0                    /* End Collection */
};

/* ================= HID Descriptor ================= */

static const uint8_t keyboard_hid_desc[9] = {
    0x09,
    HID_DESCRIPTOR_TYPE_HID,
    0x11, 0x01,
    0x00,
    0x01,
    0x22,
    HID_KEYBOARD_REPORT_DESC_SIZE,
    0x00,
};

static const uint8_t custom_hid_desc[9] = {
    0x09,
    HID_DESCRIPTOR_TYPE_HID,
    0x11, 0x01,
    0x00,
    0x01,
    0x22,
    HID_CUSTOM_REPORT_DESC_SIZE,
    0x00,
};








static uint8_t custom_hid_rx_buf[HID_CUSTOM_EP_SIZE];
static volatile uint32_t custom_hid_rx_len = 0;
static volatile uint8_t custom_hid_rx_flag = 0;
/* ================= Interface 和 Endpoint ================= */

struct usbd_interface intf0;
struct usbd_interface intf1;

static void usbd_hid_int_callback(uint8_t ep, uint32_t nbytes);
static void usbd_custom_hid_out_callback(uint8_t ep, uint32_t nbytes);
static struct usbd_endpoint hid_in_ep = {
    .ep_cb = usbd_hid_int_callback,
    .ep_addr = HID_INT_EP
};

static struct usbd_endpoint hid_custom_out_ep = {
    .ep_cb = usbd_custom_hid_out_callback,
    .ep_addr = HID_CUSTOM_OUT_EP
};

static struct usbd_endpoint hid_custom_in_ep = {
    .ep_cb = usbd_hid_int_callback,
    .ep_addr = HID_CUSTOM_IN_EP
};

/* ================= USB 回调函数 ================= */

void usbd_configure_done_callback(void)
{
   usbd_ep_start_read(HID_CUSTOM_OUT_EP,
                       custom_hid_rx_buf,
                       HID_CUSTOM_EP_SIZE);
}

/*
 * IN 端点发送完成回调。
 * HID_INT_EP = 0x81：标准键盘 IN 发送完成。
 * HID_CUSTOM_IN_EP = 0x82：自定义 HID IN 发送完成。
 */
static void usbd_hid_int_callback(uint8_t ep, uint32_t nbytes)
{
    if (ep == HID_INT_EP) {
        hid_state = HID_STATE_IDLE;
    } else if (ep == HID_CUSTOM_IN_EP) {
        custom_hid_state = HID_STATE_IDLE;
    }
}


#define PKT_SOF          0xA5
#define PKT_VERSION      0x01

#define PKT_TYPE_LIGHT   0x10

#define LIGHT_CMD_SET_MODE   0x01
#define LIGHT_CMD_NEXT_MODE  0x02
#define LIGHT_CMD_SET_COLOR  0x03
#define LIGHT_CMD_OFF        0x04
static void usbd_custom_hid_out_callback(uint8_t ep, uint32_t nbytes)
{
    if (ep != HID_CUSTOM_OUT_EP) {
        return;
    }

   if (nbytes >= 10) {
        uint8_t report_id = custom_hid_rx_buf[0];
        uint8_t sof       = custom_hid_rx_buf[1];
        uint8_t version   = custom_hid_rx_buf[2];
        uint8_t type      = custom_hid_rx_buf[3];
        uint8_t cmd       = custom_hid_rx_buf[4];
        uint8_t plen      = custom_hid_rx_buf[6];

        if (report_id == CUSTOM_REPORT_ID ) {

          

        
            uint8_t r = custom_hid_rx_buf[7];
            uint8_t g = custom_hid_rx_buf[8];
            uint8_t b = custom_hid_rx_buf[9];

            
             
        
            }
    }


   
		
   
    /*
     * 必须重新启动下一次 OUT 接收。
     * 否则只能收第一包。
     */
    usbd_ep_start_read(HID_CUSTOM_OUT_EP,
                       custom_hid_rx_buf,
                       HID_CUSTOM_EP_SIZE);
}















/*
 * PC 通过 HID Set_Report 发送数据时，CherryUSB 会调用这个函数。
 *
 * intf == 0：标准键盘 HID
 * intf == 1：自定义 HID
 */
uint32_t usbd_hid_set_report(uint8_t req,
                             uint8_t intf,
                             uint8_t report_id,
                             uint8_t report_type,
                             uint8_t *data,
                             uint32_t len)
{
    if (data == NULL || len == 0) {
        return 0;
    }

    /*
     * 这里只处理 Interface 1，也就是自定义 HID。
     * Interface 0 是标准键盘，不在这里处理灯光协议。
     */
    if (intf != 1) {
        return 0;
    }

   
     
    lib_ws2812_set_pixel(0,255,255,255);
	  lib_ws2812_update();

    return 0;
}

/* ================= USB 初始化 ================= */

void hid_keyboard_init(void)
{
    usbd_desc_register(hid_descriptor);

    /*
     * Interface 0：标准键盘 HID
     */
    usbd_add_interface(usbd_hid_init_intf(
        &intf0,
        keyboard_hid_desc,
        hid_keyboard_report_desc,
        HID_KEYBOARD_REPORT_DESC_SIZE
    ));
    usbd_add_endpoint(&hid_in_ep);

    /*
     * Interface 1：自定义 HID
     *
     * 关键点：
     * 必须注册 intf1、0x02 OUT、0x82 IN。
     * 你原来的代码只注册了 intf0 和 hid_in_ep，所以自定义 HID 不会生效。
     */
    usbd_add_interface(usbd_hid_init_intf(
        &intf1,
        custom_hid_desc,
        hid_custom_report_desc,
        HID_CUSTOM_REPORT_DESC_SIZE
    ));
    usbd_add_endpoint(&hid_custom_out_ep);
    usbd_add_endpoint(&hid_custom_in_ep);

    usbd_initialize();
}








/* ================= HID Idle ================= */

uint8_t idle_speed;

void usbh_hid_set_idle(uint8_t intf, uint8_t report_id, uint8_t duration)
{
    idle_speed = duration;
}

uint8_t usbh_hid_get_idle(uint8_t intf, uint8_t report_id)
{
    return idle_speed;
}