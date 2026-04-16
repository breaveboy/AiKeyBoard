#include "stdio.h"
#include "stdint.h"
#include "string.h"

#define USB_REQ_GET_DESCRIPTOR       0x06  //获取描述符
#define USB_REQ_SET_ADDRESS          0x05  //设置地址
#define USB_REQ_SET_CONFIGURATION    0x09  //设置配置

#define USB_DESC_TYPE_DEVICE         0x01
#define USB_DESC_TYPE_CONFIGURATION  0x02
#define USB_DESC_TYPE_STRING         0x03
#define HID_DESC_TYPE_HID            0x21
#define HID_DESC_TYPE_REPORT         0x22


#define EP1_IN_ADDR                  0x81  //输入断点
#define EP1_OUT_ADDR                 0x01   //输出端点


#define HID_REPORT_SIZE              64

#define DEVICE_STATE_DEFAULT         0
#define DEVICE_STATE_ADDRESSED       1
#define DEVICE_STATE_CONFIGURED      2

#define HID_IDLE                     0
#define HID_BUSY                     1

#define MIN(a, b)                    ((a) < (b) ? (a) : (b))


//setup固定8字节
typedef struct 
{
     uint8_t  bmRequestType;
    uint8_t  bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
}setup;
typedef struct 
{
    uint8_t address;
    uint8_t configuration;
    uint8_t state;
    uint8_t hid_state;
}device;
//设备描述符固定18字节
const uint8_t USB_DeviceDescriptor[18] =
{
    0x12,                   // bLength = 18
    0x01,                   // bDescriptorType = Device
    0x00, 0x02,             // bcdUSB = USB 2.00

    0x00,                   // bDeviceClass = defined in interface
    0x00,                   // bDeviceSubClass
    0x00,                   // bDeviceProtocol

    0x40,                   // bMaxPacketSize0 = 64

    0x34, 0x12,             // idVendor  = 0x1234
    0x78, 0x56,             // idProduct = 0x5678

    0x00, 0x01,             // bcdDevice = 1.00

    0x01,                   // iManufacturer
    0x02,                   // iProduct
    0x03,                   // iSerialNumber

    0x01                    // bNumConfigurations
};



/* ==========================
 * 2. HID Report Descriptor
 *    Input  = 64 bytes
 *    Output = 64 bytes
 * ========================== */

const uint8_t HID_ReportDescriptor[] =
{
    0x06, 0x00, 0xFF,       // Usage Page (Vendor Defined 0xFF00)
    0x09, 0x01,             // Usage (0x01)
    0xA1, 0x01,             // Collection (Application)

    0x09, 0x02,             //   Usage (0x02)
    0x15, 0x00,             //   Logical Minimum (0)
    0x26, 0xFF, 0x00,       //   Logical Maximum (255)
    0x75, 0x08,             //   Report Size = 8 bits
    0x95, 0x40,             //   Report Count = 64
    0x81, 0x02,             //   Input

    0x09, 0x03,             //   Usage (0x03)
    0x15, 0x00,             //   Logical Minimum (0)
    0x26, 0xFF, 0x00,       //   Logical Maximum (255)
    0x75, 0x08,             //   Report Size = 8 bits
    0x95, 0x40,             //   Report Count = 64
    0x91, 0x02,             //   Output

    0xC0                    // End Collection
};

const uint8_t USB_ConfigDescriptor[] =
{
    // Configuration Descriptor
    0x09,                   // bLength
    0x02,                   // bDescriptorType = Configuration
    0x26, 0x00,             // wTotalLength = 38
    0x01,                   // bNumInterfaces = 1
    0x01,                   // bConfigurationValue = 1
    0x00,                   // iConfiguration
    0x80,                   // bmAttributes = Bus powered
    0x32,                   // bMaxPower = 100mA

    // Interface Descriptor
    0x09,                   // bLength
    0x04,                   // bDescriptorType = Interface
    0x00,                   // bInterfaceNumber = 0
    0x00,                   // bAlternateSetting
    0x02,                   // bNumEndpoints = 2
    0x03,                   // bInterfaceClass = HID
    0x00,                   // bInterfaceSubClass
    0x00,                   // bInterfaceProtocol
    0x00,                   // iInterface

    // HID Descriptor
    0x09,                   // bLength
    0x21,                   // bDescriptorType = HID
    0x11, 0x01,             // bcdHID = 1.11
    0x00,                   // bCountryCode
    0x01,                   // bNumDescriptors
    0x22,                   // bDescriptorType = Report
    sizeof(HID_ReportDescriptor), 0x00,   // wDescriptorLength

    // Endpoint Descriptor: EP1 IN
    0x07,                   // bLength
    0x05,                   // bDescriptorType = Endpoint
    0x81,                   // bEndpointAddress = EP1 IN
    0x03,                   // bmAttributes = Interrupt
    0x40, 0x00,             // wMaxPacketSize = 64
    0x01,                   // bInterval = 1ms

    // Endpoint Descriptor: EP1 OUT
    0x07,                   // bLength
    0x05,                   // bDescriptorType = Endpoint
    0x01,                   // bEndpointAddress = EP1 OUT
    0x03,                   // bmAttributes = Interrupt
    0x40, 0x00,             // wMaxPacketSize = 64
    0x01                    // bInterval = 1ms
};
