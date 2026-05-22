import time
import numpy as np
import sounddevice as sd
from connection import *
from protocol import Protocol

# 1. 初始化键盘连接 (VID/PID)
conn = HidConnection(vid=0x36B7, pid=0xFFFF)
is_ready = False

def on_status_change(status):
    global is_ready
    if status == DevStatus.CONNECTED:
        print(" [OK] 键盘已连接！")
        is_ready = True
    elif status == DevStatus.LOST:
        is_ready = False

conn.on_status_changed = on_status_change
conn.start()

# 2. 定位您的 WASAPI 声卡设备
# 基于刚才的列表分析，12 号设备是您板载声卡 WASAPI 的 Speakers，延迟极低
DEVICE_ID = 12 
SAMPLE_RATE = 48000
BLOCK_SIZE = 1024

print(" 正在等待键盘连接...")
while not is_ready:
    time.sleep(0.1)

print("\n" + "=" * 55)
print(" [开始极简音律验证] 请在电脑上放歌！")
print(" 键盘所有灯珠将化身为单个『音量呼吸灯』，随音乐鼓点同明同暗。")
print(" 按 Ctrl + C 退出测试。")
print("=" * 55 + "\n")

# 高精度 1.2ms 微秒延迟函数
def precise_delay(sec):
    start = time.perf_counter()
    while time.perf_counter() - start < sec:
        pass

# 3. 音频捕获回调函数
def audio_callback(indata, frames, time_info, status):
    if not is_ready:
        return

    # 均方根（RMS）算法：计算当前双声道缓冲区的音频能量
    rms = np.sqrt(np.mean(indata ** 2))
    
    # 乘以增益系数 3.0，并限幅在 0.0 ~ 1.0 之间
    energy = min(max(rms * 3.0, 0.0), 1.0)
    
    # 转换为物理亮度值 (0 ~ 255)
    brightness = int(energy * 255)

    # 打印控制台能量条
    bar = "#" * int(energy * 30)
    print(f"\r实时音量能量: [{bar:<30}] 亮度值: {brightness:<3}", end="")

    # 填充 61 颗灯珠的颜色 (使用干净的冰蓝色: R=0, G=亮度*0.6, B=亮度)
    g = int(brightness * 0.6)
    b = brightness
    rgb_frame = bytes([0, g, b] * 61) # 61颗灯同色

    # 18+18+18+7 分 4 包推流
    packet_sizes = [54, 54, 54, 21]
    offset = 0
    for cur_pkt in range(4):
        size = packet_sizes[cur_pkt]
        payload = rgb_frame[offset : offset + size]
        offset += size

        packet = Protocol.encode(
            cmd=0x22, param=0x00, res=0,
            total=4, cur=cur_pkt, payload=payload
        )
        conn.send(packet)
        precise_delay(0.0012) # 分包 1.2ms 避堵延迟

try:
    # 【核心修正】：配置 Windows WASAPI 专属的环回监听模式（loopback）
    wasapi_loopback_settings = sd.WasapiSettings(loopback=True)

    # 开启 WASAPI 音频监听 (设备ID=12, 通道数必须设为 2)
    with sd.InputStream(device=DEVICE_ID, 
                         channels=2, # 12号设备输出为立体声，环回输入必须强制设为双声道 2
                         samplerate=SAMPLE_RATE, 
                         blocksize=BLOCK_SIZE, 
                         callback=audio_callback,
                         extra_settings=wasapi_loopback_settings): # 注入环回配置
        while True:
            time.sleep(1.0)
            
except KeyboardInterrupt:
    print("\n [测试结束]")
finally:
    conn.stop()