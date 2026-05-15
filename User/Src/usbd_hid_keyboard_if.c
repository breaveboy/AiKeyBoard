#include "usbd_core.h"
#include "usbd_hid.h"
#include <stdio.h>
#include <string.h>
#include "App_protocol.h"
#include "App_key.h"
/* ================= USB 基本信息 ================= */

#define USBD_VID           0x36b7
#define USBD_PID           0xffff
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

/* ================= 标准键盘 HID：保持和 App.c 兼容 ================= */

#define HID_INT_EP          0x81
#define HID_INT_EP_SIZE     8
#define HID_INT_EP_INTERVAL 5

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
volatile uint8_t custom_hid_state = HID_STATE_IDLE;

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

// IN 端点发送完成回调：0x81 对应键盘，0x82 对应自定义 HID。
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

// 配置完成后启动自定义 HID OUT 接收，并让键盘 report 重新同步一次。
void usbd_configure_done_callback(void)
{
    hid_state = HID_STATE_IDLE;
    custom_hid_state = HID_STATE_IDLE;
    report_dirty = true;

    usbd_ep_start_read(HID_CUSTOM_OUT_EP,
                       custom_hid_rx_buf,
                       HID_CUSTOM_EP_SIZE);
}

/*
 * IN 端点发送完成回调。
 * HID_INT_EP = 0x81：标准键盘 IN 发送完成。
 * HID_CUSTOM_IN_EP = 0x82：自定义 HID IN 发送完成。
 */
// USB 总线事件通知：恢复/重新配置时复位 HID 状态，防止键盘 IN 端点卡住。
static void usbd_hid_event_notify(uint8_t event, void *arg)
{
    (void)arg;

    switch (event) {
    case USBD_EVENT_RESET:
    case USBD_EVENT_CONFIGURED:
    case USBD_EVENT_RESUME:
        hid_state = HID_STATE_IDLE;
        custom_hid_state = HID_STATE_IDLE;
        report_dirty = true;
        usbd_ep_start_read(HID_CUSTOM_OUT_EP, custom_hid_rx_buf, HID_CUSTOM_EP_SIZE);
        break;
    case USBD_EVENT_SUSPEND:
        hid_state = HID_STATE_IDLE;
        custom_hid_state = HID_STATE_IDLE;
        break;
    default:
        break;
    }
}
// IN 端点发送完成回调：0x81 对应键盘，0x82 对应自定义 HID。
static void usbd_hid_int_callback(uint8_t ep, uint32_t nbytes)
{
    if (ep == HID_INT_EP) {
        hid_state = HID_STATE_IDLE;
    } else if (ep == HID_CUSTOM_IN_EP) {
        custom_hid_state = HID_STATE_IDLE;
    }
}












//发送完成的回调函数
static void usbd_custom_hid_out_callback(uint8_t ep, uint32_t nbytes)
{
    if(ep!=HID_CUSTOM_OUT_EP){
		   return;
		}
    //pc端的数据在这个回调函数中接受
    App_protocol_on_rx(custom_hid_rx_buf,nbytes);


    /*
     * 必须重新启动下一次 OUT 接收。
     * 否则只能收第一包。
     */
    usbd_ep_start_read(HID_CUSTOM_OUT_EP,
                       custom_hid_rx_buf,
                       HID_CUSTOM_EP_SIZE);
}


//大小锁的全局变量
volatile bool g_caps_lock_active =false;

/**
 * CherryUSB HID 类请求回调函数
 * 当电脑发出 SET_REPORT 指令（比如切换大小写灯）时，库会自动调用这个函数
0x00 (二进制 0000 0000)：所有灯全灭。
0x01 (二进制 0000 0001)：Num Lock（小键盘锁）开启。
0x02 (二进制 0000 0010)：Caps Lock（大小写锁）开启。
0x03 (二进制 0000 0011)：Num Lock 和 Caps Lock 同时开启（1+2=3）。
 */
void usbh_hid_set_report(uint8_t intf, uint8_t report_id, uint8_t report_type, uint8_t *report, uint8_t report_len)
{
    // 调试打印：看看收到的原始数据
     printf("[USB] HID Set Report. Intf: %d, Data: 0x%02x\n", intf, report[0]);

    // Interface 0 通常是标准键盘接口
    if (intf == 0) {
        /*
         * 标准键盘 LED 报告字节位定义:
         * bit 0: Num Lock
         * bit 1: Caps Lock  <-- 我们要找的就是它
         * bit 2: Scroll Lock
         */
        if (report[0] & 0x02) {
            g_caps_lock_active = true;

        } else {
            g_caps_lock_active = false;

        }
    }

    // 如果你有 Interface 1 的自定义协议，也可以在这里继续写 if (intf == 1) ...
}
/* ================= USB 初始化 ================= */

void hid_keyboard_init(void)
{
    usbd_desc_register(hid_descriptor);

    /*
     * Interface 0：标准键盘 HID
     */
    usbd_add_interface(usbd_hid_init_intf(&intf0,keyboard_hid_desc, hid_keyboard_report_desc,HID_KEYBOARD_REPORT_DESC_SIZE ));
    // 标准键盘接口也接收 USB reset/resume 事件，用于恢复 0x81 状态。
    intf0.notify_handler = usbd_hid_event_notify;
    usbd_add_endpoint(&hid_in_ep);

    /*
     * Interface 1：自定义 HID
     *
     * 关键点：
     * 必须注册 intf1、0x02 OUT、0x82 IN。
     */

    usbd_add_interface(usbd_hid_init_intf(&intf1,custom_hid_desc,hid_custom_report_desc,HID_CUSTOM_REPORT_DESC_SIZE));
    // 自定义 HID 接口恢复后重新准备 OUT 接收。
    intf1.notify_handler = usbd_hid_event_notify;
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
