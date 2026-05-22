import time
import logging
import colorsys
from connection import *
from protocol import Protocol
from logger_config import LogManager

LogManager.setup()  # 初始化工业级日志系统
logger = logging.getLogger(__name__)

class MusicOnlyTester:
    def __init__(self):
        logger.info("初始化专属音乐律动测试程序 (VID=0x36B7, PID=0xFFFF)...")
        # 1. 绑定键盘连接
        self.conn = HidConnection(vid=0x36B7, pid=0xFFFF)
        self.conn.on_status_changed = self.on_status_change
        self.is_ready = False

    def on_status_change(self, status: DevStatus):
        if status == DevStatus.CONNECTED:
            logger.info(" [OK] 键盘通信链路已成功就绪！")
            self.is_ready = True
        elif status == DevStatus.LOST:
            logger.warning(" [ERR] 键盘连接中断！")
            self.is_ready = False

    def get_rainbow_rgb(self, led_idx: int, total_leds: int, offset: float):
        """利用 HSV 色彩空间计算彩虹过渡色"""
        hue = ((led_idx / total_leds) + offset) % 1.0
        r, g, b = colorsys.hsv_to_rgb(hue, 1.0, 1.0)
        return int(r * 255), int(g * 255), int(b * 255)

    def start_test(self):
        self.conn.start()
        logger.info(" 正在等待键盘握手连接...")
        
        # 等待链路建立
        while not self.is_ready:
            time.sleep(0.1)

        logger.info(" =" * 25)
        logger.info(" [开始测试] 正在向键盘推送 30 FPS 高频音律数据流...")
        logger.info(" 此时您的键盘应当呈现『丝滑移动的彩虹波浪』。")
        logger.info(" [退出测试] 随时在控制台按 Ctrl + C 停止发送。")
        logger.info(" 停止后，请观察键盘是否在 2 秒后自动恢复之前的板载灯效。")
        logger.info(" =" * 25)

        total_leds = 61
        offset = 0.0
        packet_sizes = [54, 54, 54, 21] # 18+18+18+7 对齐方案字节大小

        try:
            while True:
                if not self.is_ready:
                    time.sleep(0.5)
                    continue

                # 1. 构建当前帧的 183 字节 RGB 原始色彩流
                rgb_data = bytearray()
                for i in range(total_leds):
                    r, g, b = self.get_rainbow_rgb(i, total_leds, offset)
                    rgb_data.extend([r, g, b])

                # 2. 将数据切片，打包成 4 个分包连续下发
                start_offset = 0
                for cur_pkt in range(4):
                    size = packet_sizes[cur_pkt]
                    payload = bytes(rgb_data[start_offset : start_offset + size])
                    start_offset += size

                    # 构建自定义音律 0x22 协议
                    packet = Protocol.encode(
                        cmd=0x22,        # 音乐律动主命令 CMD_LIGHT_MUSIC_MAIN
                        param=0x00,      # 参数 0x00
                        res=0, 
                        total=4,         # total_pkts = 4
                        cur=cur_pkt,     # cur_pkt = 0, 1, 2, 3
                        payload=payload
                    )
                    self.conn.send(packet)

                # 3. 产生色彩位移偏移量，实现动态波浪
                offset += 0.015
                if offset >= 1.0:
                    offset = 0.0

                # 4. 控制刷新率为 30 FPS (约 33 毫秒更新一帧)
                time.sleep(0.033)

        except KeyboardInterrupt:
            logger.info("\n 检测到 Ctrl+C 终止命令，已停止音律数据发送。")
            logger.info(" [正在测试看门狗] 请静静观察键盘是否在 2 秒内恢复它原有的默认灯光...")
        finally:
            self.conn.stop()
            logger.info(" 测试程序已彻底安全退出。")

if __name__ == "__main__":
    tester = MusicOnlyTester()
    tester.start_test()