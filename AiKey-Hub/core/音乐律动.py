import time
import logging
import colorsys
from connection import *
from protocol import Protocol
from logger_config import LogManager

LogManager.setup()
logger = logging.getLogger(__name__)

class PcOnlyUltimateOptimizer:
    def __init__(self):
        logger.info("初始化 [纯上位机端 - 预渲染缓存] 终极优化程序...")
        self.conn = HidConnection(vid=0x36B7, pid=0xFFFF)
        self.conn.on_status_changed = self.on_status_change
        self.is_ready = False
        
        # 预渲染配置
        self.total_leds = 61
        self.total_cached_frames = 120  # 预先生成 120 帧动画，构成一个完美的循环
        self.frame_cache = []           # 存放 120 帧预渲染二进制色彩流
        
        # 在程序启动时，一次性算完所有颜色，避免运行时产生任何计算抖动
        self.pre_render_rainbow_frames()

    def on_status_change(self, status: DevStatus):
        if status == DevStatus.CONNECTED:
            logger.info(" [OK] 通信链路已就绪。")
            self.is_ready = True
        elif status == DevStatus.LOST:
            self.is_ready = False

    def precise_delay(self, seconds: float):
        """高精度微秒级自旋锁延迟"""
        start = time.perf_counter()
        while time.perf_counter() - start < seconds:
            pass

    def pre_render_rainbow_frames(self):
        """【核心优化】预渲染生成完整的彩虹滚动动画缓存"""
        logger.info(" 正在预渲染 120 帧高精度彩虹波浪动画至内存...")
        
        for f in range(self.total_cached_frames):
            offset = f / self.total_cached_frames
            rgb_data = bytearray()
            
            for i in range(self.total_leds):
                # HSV 计算彩虹色
                hue = ((i / self.total_leds) + offset) % 1.0
                r, g, b = colorsys.hsv_to_rgb(hue, 1.0, 1.0)
                rgb_data.extend([int(r * 255), int(g * 255), int(b * 255)])
                
            self.frame_cache.append(bytes(rgb_data))
            
        logger.info(" [OK] 内存预渲染完毕。")

    def start_test(self):
        self.conn.start()
        while not self.is_ready:
            time.sleep(0.1)

        # 帧率对齐单片机 25ms 物理刷新周期
        TARGET_FRAME_TIME = 0.025  
        packet_sizes = [54, 54, 54, 21] 
        
        logger.info(" =" * 25)
        logger.info(" [启动] 正在以『极速预渲染流』向键盘无阻碍推流...")
        logger.info(" 此时 PC 端 CPU 消耗已归零，时序达到微秒级纯净对齐。")
        logger.info(" =" * 25)

        current_frame_idx = 0

        try:
            while True:
                if not self.is_ready:
                    time.sleep(0.1)
                    continue

                frame_start = time.perf_counter()

                # 1. 直接从内存中获取算好的 RGB 字节，0 耗时
                rgb_data = self.frame_cache[current_frame_idx]

                # 2. 极速发包
                start_offset = 0
                for cur_pkt in range(4):
                    size = packet_sizes[cur_pkt]
                    payload = rgb_data[start_offset : start_offset + size]
                    start_offset += size

                    packet = Protocol.encode(
                        cmd=0x22, param=0x00, res=0,
                        total=4, cur=cur_pkt, payload=payload
                    )
                    self.conn.send(packet)

                    # 分包高精度微秒级延迟 (1.2ms)，防止 USB 堵塞
                    self.precise_delay(0.0012)

                # 3. 递增动画帧
                current_frame_idx = (current_frame_idx + 1) % self.total_cached_frames

                # 4. 高精度自适应帧休眠
                elapsed = time.perf_counter() - frame_start
                sleep_time = TARGET_FRAME_TIME - elapsed
                
                if sleep_time > 0:
                    time.sleep(sleep_time)

        except KeyboardInterrupt:
            logger.info("\n已停止发送。")
        finally:
            self.conn.stop()

if __name__ == "__main__":
    tester = PcOnlyUltimateOptimizer()
    tester.start_test()