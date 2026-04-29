import hid
import time

VID = 0x36B7
PID = 0xFFFF

REPORT_ID = 0x05

def print_devices():
    print("查找 HID 设备：")
    devices = hid.enumerate(VID, PID)

    for index, dev in enumerate(devices):
        print(f"\n[{index}]")
        print("path             :", dev["path"])
        print("vendor_id        :", hex(dev["vendor_id"]))
        print("product_id       :", hex(dev["product_id"]))
        print("product_string   :", dev.get("product_string"))
        print("manufacturer     :", dev.get("manufacturer_string"))
        print("usage_page       :", hex(dev.get("usage_page", 0)))
        print("usage            :", hex(dev.get("usage", 0)))
        print("interface_number :", dev.get("interface_number"))

    return devices


def find_custom_hid_path():
    devices = hid.enumerate(VID, PID)

    for dev in devices:
        usage_page = dev.get("usage_page", 0)
        interface_number = dev.get("interface_number", -1)

        # 优先找自定义 HID
        # 你的自定义 HID 是 Interface 1，也就是 MI_01
        if interface_number == 1:
            return dev["path"]

        # 有些系统 interface_number 可能拿不到，可以根据 usage_page 找
        if usage_page == 0xFF00:
            return dev["path"]

    return None


def build_packet(pkt_type=0x10, cmd=0x01, seq=0x01, payload=None):
    if payload is None:
        payload = []

    if len(payload) > 56:
        raise ValueError("payload 最大 56 字节")

    buf = [0x00] * 64

    buf[0] = REPORT_ID   # Report ID = 0x05
    buf[1] = 0xA5        # 包头
    buf[2] = 0x01        # 协议版本
    buf[3] = pkt_type    # Type，例如 0x10 灯光
    buf[4] = cmd         # Cmd
    buf[5] = seq         # Seq
    buf[6] = len(payload)

    for i, value in enumerate(payload):
        buf[7 + i] = value & 0xFF

    return buf



print_devices()

path = find_custom_hid_path()
if path is None:
    print("\n没有找到自定义 HID 接口。")
    print("请确认设备管理器里能看到 MI_01，或者 usage_page = 0xff00。")
  
print("\n打开自定义 HID：", path)

dev = hid.device()
dev.open_path(path)



# 测试包：05 A5 01 10 01 01 03 11 22 33 ...







while True:
    packet = build_packet(pkt_type=0x10, cmd=0x01, seq=0x01, payload=[255,0,0])
    dev.write(packet)
    time.sleep(1)
    packet = build_packet(pkt_type=0x10, cmd=0x01, seq=0x01, payload=[0,255,0])
    dev.write(packet)
    time.sleep(1)
    packet = build_packet(pkt_type=0x10, cmd=0x01, seq=0x01, payload=[0,0,255])
    dev.write(packet)
   







  