import hid
import time

VID = 0x36B7
PID = 0xFFFF
REPORT_ID = 0x05

def print_devices():
    print("查找 HID 设备：")
    devices = hid.enumerate(VID, PID)
    for index, dev in enumerate(devices):
        print(f"\n[{index}] path: {dev['path']} | interface: {dev.get('interface_number')}")
    return devices

def find_custom_hid_path():
    devices = hid.enumerate(VID, PID)
    for dev in devices:
        if dev.get("interface_number", -1) == 1 or dev.get("usage_page", 0) == 0xFF00:
            return dev["path"]
    return None

def calculate_crc(buffer_64):
    total_sum = sum(buffer_64[0:63]) & 0xFF
    return (0xFF - total_sum) & 0xFF

def build_light_packet(mode, r, g, b, brightness=100, speed=5):
    buf = [0x00] * 64

    buf[0] = REPORT_ID   # report_id = 0x05
    buf[1] = 0x20        # cmd_id    = 0x20 (CMD_LIGHT_WRITE_CFG)
    buf[2] = 0x00        # cmd_param = 0x00 (LPARAM_ALL_SET 综合设置)
    buf[3] = 0x00        # reserved  = 0x00
    buf[4] = 0x01        # total_pkts= 1
    buf[5] = 0x00        # cur_pkt   = 0
    buf[6] = 0x07        # data_len  = 7 (Payload_LightAll_t 的大小)

    buf[7]  = mode       # payload[0]: mode_idx (4=静态, 1=呼吸, 2=彩虹等)
    buf[8]  = 0x00       # payload[1]: color_idx (这里不使用预设颜色)
    buf[9]  = r          # payload[2]: R
    buf[10] = g          # payload[3]: G
    buf[11] = b          # payload[4]: B
    buf[12] = brightness # payload[5]: brightness (0-100)
    buf[13] = speed      # payload[6]: speed (延时，值越小越快，建议1-10)

    buf[63] = calculate_crc(buf)

    return buf

# =============== 主程序运行 ===============
print_devices()

path = find_custom_hid_path()
if path is None:
    print("\n没有找到自定义 HID 接口。请确认设备管理器里能看到 MI_01。")
    exit()
  
print("\n打开自定义 HID：", path)
dev = hid.device()
dev.open_path(path)
# 设置为非阻塞模式，方便读取 ACK
dev.set_nonblocking(1) 

def send_to_mcu(packet_64):
    send_buf = packet_64
    dev.write(send_buf)

print("\n开始循环发送灯光测试...\n")

# 注释掉单次测试
packet = build_light_packet(mode=4, r=0, g=255, b=0, brightness=100, speed=9)
send_to_mcu(packet)
time.sleep(2)

