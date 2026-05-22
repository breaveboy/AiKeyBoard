import sounddevice as sd
import numpy as np

# ================= 配置参数 =================
SAMPLERATE = 44100  
BLOCKSIZE = 2048    
CHANNELS = 1

BASS_RANGE = (20, 250)
MID_RANGE = (250, 4000)
HIGH_RANGE = (4000, 10000)

SMOOTHING = 0.75  # 稍微提高平滑度，律动更丝滑
prev_bass, prev_mid, prev_high = 0, 0, 0

def get_freq_index(freq, samplerate, blocksize):
    return int(freq * blocksize / samplerate)

# 计算各频段在 FFT 结果中的区间索引
bass_low, bass_high = [get_freq_index(f, SAMPLERATE, BLOCKSIZE) for f in BASS_RANGE]
mid_low, mid_high = [get_freq_index(f, SAMPLERATE, BLOCKSIZE) for f in MID_RANGE]
high_low, high_high = [get_freq_index(f, SAMPLERATE, BLOCKSIZE) for f in HIGH_RANGE]

# 先清一次屏，并隐藏光标（可选）
print("\033[2J\033[?25l", end="") 

def audio_callback(indata, frames, time, status):
    global prev_bass, prev_mid, prev_high
    
    if status:
        pass  # 忽略一些微小的状态警告以保持画面整洁
        
    # 汉宁窗 + FFT
    windowed_data = indata.flatten() * np.hanning(len(indata))
    fft_data = np.abs(np.fft.rfft(windowed_data))
    
    # 提取能量
    bass_energy = np.mean(fft_data[bass_low:bass_high]) if bass_high > bass_low else 0
    mid_energy = np.mean(fft_data[mid_low:mid_high]) if mid_high > mid_low else 0
    high_energy = np.mean(fft_data[high_low:high_high]) if high_high > high_low else 0
    
    # 动态映射
    bass_val = int(bass_energy * 300)
    mid_val = int(mid_energy * 1000)
    high_val = int(high_energy * 2500)
    
    # 平滑滤波
    bass_val = int(prev_bass * SMOOTHING + bass_val * (1 - SMOOTHING))
    mid_val = int(prev_mid * SMOOTHING + mid_val * (1 - SMOOTHING))
    high_val = int(prev_high * SMOOTHING + high_val * (1 - SMOOTHING))
    
    prev_bass, prev_mid, prev_high = bass_val, mid_val, high_val
    
    # 构建律动条
    b_bar = "■" * min(bass_val, 30)
    m_bar = "■" * min(mid_val, 30)
    h_bar = "■" * min(high_val, 30)
    
    # ================= 核心修改：无闪烁刷新 =================
    # \033[H 将光标移动到控制台左上角 (0, 0) 位置，直接覆写，不闪烁
    print("\033[H", end="") 
    print("====== 实时音乐律动频谱分析 ======")
    # {b_bar:<30} 确保即使长度变短，后面也会用空格填满，清除上一次残留的方块
    print(f"低音 (Bass/鼓点):   |{b_bar:<30}| ({bass_val:<4})")
    print(f"中音 (Mid/人声):    |{m_bar:<30}| ({mid_val:<4})")
    print(f"高音 (High/乐器):   |{h_bar:<30}| ({high_val:<4})")
    print("==================================")
    print("提示：播放音乐并让麦克风听到声音。按 Ctrl+C 退出。")

# 启动音频流
try:
    with sd.InputStream(channels=CHANNELS,
                        samplerate=SAMPLERATE,
                        blocksize=BLOCKSIZE,
                        callback=audio_callback):
        while True:
            sd.sleep(100)
except KeyboardInterrupt:
    # 恢复光标显示
    print("\033[?25h\n律动已停止。")