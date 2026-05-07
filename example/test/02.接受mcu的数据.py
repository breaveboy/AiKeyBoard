import hid        
VID =0x36B7
PID =0xFFFF
REPORT_ID = 0x05

# 路径查找
target_path = None 
for dev in hid.enumerate(VID, PID):
   if dev.get("interface_number", -1) == 1 or dev.get("usage_page", 0) == 0xFF00:
       target_path = dev["path"]
       break
if target_path is None:
   print("没有找到自定义 HID 设备。请确认设备管理器里能看到 MI_01。")
   exit()

# 创建设备对象并用path打开
dev = hid.device()
dev.open_path(target_path)
print("已打开设备：", target_path)
# 发送数据包
def send_data_packet():
    data = [0x00] * 64
    data[0] =  REPORT_ID  # report_id
    data[1] =  0x20       # cmd_id (CMD_LIGHT_WRITE_CFG)
    data[2] =  0x00       # cmd_param (LPARAM_ALL_SET 综合设置)
    data[3] =  0x00       # reserved
    data[4] =  0x01       # total_pkts
    data[5] =  0x00       # cur_pkt
    data[6] =  0x07       # data_len (Payload_LightAll_t 的大小)
    data[7]  = 0x04      # payload[0]: mode_idx (1=呼吸)
    data[8]  = 0x00      # payload[1]: color_idx
    data[9]  = 0xFF      # payload[2]: R
    data[10] = 0x00      # payload[3]: G
    data[11] = 0x00      # payload[4]: B
    data[12] = 0x64     # payload[5]: brightness (100)
    data[13] = 0x0A     # payload[6]: speed (5
    # 计算 CRC
    total_sum = sum(data[0:63]) & 0xFF
    data[63] = (0xFF - total_sum) & 0xFF  # 将 CRC 值写入最后一个字节
    return data

packet = send_data_packet()
dev.write(packet)
print("数据已成功发送到自定义接口！")
dev.close()