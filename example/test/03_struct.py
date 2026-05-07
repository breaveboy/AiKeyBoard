# 任务 1：打包 (Packing) —— 发送“系统全参数配置”指令
# 你需要组装一个 64 字节 的指令包发送给 MCU，格式要求如下：
# 字节序：必须使用小端序。
# 报文头 (2 字节)：Report ID 为 0x05，指令 ID 为 0xCF。
# 配置开关 (1 字节)：一个布尔值，代表是否开启“AI 自动加速模式”。
# 去抖时间 (2 字节)：一个无符号短整型（Unsigned Short），单位为微秒。
# 触发电压 (4 字节)：一个浮点数（Float），代表磁轴触发的参考电压。
# 序列号 (12 字节)：键盘的唯一出厂字符串（如 AI-KEY-99999）。
# 预留位 (填充)：使用 struct 的填充功能，让有效数据之后的所有位置自动补 0x00。
# 校验和 (1 字节)：全包的最后一个字节（第 64 字节）必须是前面 63 个字节的累加和（取低8位）。
import struct
report_id = 0x05
cmd_id = 0xCF
switch = True
debounce_time = 500  # 微秒
trigger_voltage = 3.3  # 伏特
serial_number = b"AI-KEY-99999"
# 使用 struct 打包数据
ftm_boby='<BB?Hf12s42x'
packet = struct.pack(ftm_boby, report_id, cmd_id, switch, debounce_time, trigger_voltage, serial_number)
# 计算校验和
checksum = sum(packet) & 0xFF
full_packet = packet + bytes([checksum])
print(full_packet)
