import time
import logging
from connection import *
from protocol import Protocol
from constants import *
from logger_config import LogManager
LogManager.setup()  # 初始化工业级日志系统
logger = logging.getLogger(__name__)
class KeyBoardApp:
    def __init__(self, vid: int, pid: int):

        logger.info(f"初始化应用 vid={hex(vid)}, pid={hex(pid)}")

        # 1. 初始化搬运工 (使用你脚本里的 VID 和 PID)
        self.conn = HidConnection(vid=0x36B7, pid=0xFFFF)
        # 2. 绑定回调函数（传声筒）
        self.conn.on_packet_received = self.on_receive_data
        self.conn.on_status_changed = self.on_status_change
        
        self.is_ready = False  # 设备准备就绪标志

    
    def on_status_change(self, status: DevStatus):
        """当连接状态改变时触发"""
        if status == DevStatus.CONNECTED:
    
            logger.info(" 键盘连接成功！通信链路已就绪。")
            self.is_ready = True
        elif status == DevStatus.LOST:
            logger.warning(" 硬件链路中断，请检查 USB 连接线")
            self.is_ready = False
    def on_receive_data(self, data):
        """当收到键盘主动发回的消息时触发"""
        # 使用协议官解析收到的 64 字节
        packet = Protocol.decode(data)
        if packet:
            logger.info(f" 收到键盘回传: 指令={hex(packet['cmd'])}, 数据={packet['payload'].hex(' ')}")
    def send_breathing_red(self):
        """
        发送红色呼吸灯指令 (对应你脚本里的逻辑)
        """
        if not self.is_ready:
            logger.warning(" 设备未连接，无法发送")
            return

        # --- 业务逻辑：对应你脚本里的 payload 部分 ---
        # 模式0x04 (呼吸), 颜色0, R=255, G=0, B=0, 亮度100, 速度10
        payload = bytes([0x04, 0x00, 0xFF, 0xff, 0xFF, 0x64, 0x0A])
        
        # --- 协议打包：对应你脚本里复杂的 data[0]=... 和计算 CRC 的部分 ---
        # 自动帮你填 ReportID(0x05), CMD(0x20), 填充 0, 计算 CRC
        packet = Protocol.encode(
            cmd=Cmd.LIGHT_CFG_W,       # 0x20
            param=Param.Light.ALL_SET, # 0x00
            res=0, total=1, cur=1, 
            payload=payload
        )
        
        # --- 发送数据 ---
        if self.conn.send(packet):
            logger.info(" 灯光包已成功发送！")

    def run(self):
        # 开启后台搬运工线程
        self.conn.start()
        
        logger.info(" 正在搜索键盘接口 (MI_01)...")
        
        try:
            while True:
                # 简单的控制台交互
                cmd = input("\n请输入指令 [1:发灯光, 0:退出]: ")
                if cmd == '1':
                    self.send_breathing_red()
                elif cmd == '0':
                    break
        except KeyboardInterrupt:
            pass
        finally:
            self.conn.stop()
            logger.info(" 程序结束")

if __name__ == "__main__":
    app = KeyBoardApp(vid=0x36B7, pid=0xFFFF)
    app.run()