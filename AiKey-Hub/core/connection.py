import hid
import threading
import time
import logging
from enum import IntEnum
from typing import Optional, Callable

logger = logging.getLogger(__name__)

class DevStatus(IntEnum):
    DISCONNECTED = 0  # 断开连接
    CONNECTING = 1    # 正在尝试连接
    CONNECTED = 2     # 已连接
    LOST = 3          # 连接丢失（异常断开）

# 协议层专注于数据的打包和解析
class HidConnection:
    """
    工业级 HID 连接管理器
    特点：路径精准锁定 (MI_01)、自动重连、读写分离、线程安全
    """
    def __init__(self, vid: int, pid: int):
        self.vid = vid
        self.pid = pid
        
        self._device: Optional[hid.device] = None
        self._status: DevStatus = DevStatus.DISCONNECTED

        # 回调函数
        self.on_packet_received: Optional[Callable[[bytes], None]] = None
        self.on_status_changed: Optional[Callable[[DevStatus], None]] = None

        self._is_running = False
        self._write_lock = threading.Lock()  
        self._worker_thread: Optional[threading.Thread] = None

    def start(self):
        if self._is_running: return
        self._is_running = True
        self._worker_thread = threading.Thread(target=self._worker_loop, daemon=True)
        self._worker_thread.start()
        logger.info("连接管理器线程已启动")

    def stop(self):
        self._is_running = False
        self._close_device()
        if self._worker_thread:
            self._worker_thread.join(timeout=1.0)

    @property
    def is_connected(self) -> bool:
        return self._status == DevStatus.CONNECTED

    def _set_status(self, status: DevStatus):
        if self._status != status:
            self._status = status
            logger.info(f"设备状态变更: {self._status.name}")
            if self.on_status_changed:
                self.on_status_changed(self._status)

    def _close_device(self):
        with self._write_lock:
            if self._device:
                try:
                    self._device.close()
                except Exception as e:
                    logger.error(f"关闭设备时报错: {e}")
                finally:
                    self._device = None
        self._set_status(DevStatus.DISCONNECTED)

    def _worker_loop(self):
        while self._is_running:
            if not self._device:
                self._try_connect()
                if not self._device:
                    time.sleep(1.0) # 没连上，每秒尝试一次
                    continue

            try:
                # 读取 64 字节数据
                data = self._device.read(64)
                if data:
                    if self.on_packet_received:
                        self.on_packet_received(bytes(data))
            except OSError as e:
                logger.error(f"通信中断 (拔出?): {e}")
                self._set_status(DevStatus.LOST)
                self._close_device()
            
            time.sleep(0.001) # 1ms 高频采样

    def _try_connect(self):
        """
        完善后的路径查找连接逻辑
        """
        try:
            self._set_status(DevStatus.CONNECTING)
            target_path = None

            # 1. 枚举所有匹配 VID/PID 的 HID 设备接口
            devices = hid.enumerate(self.vid, self.pid)
            
            for dev_info in devices:
                # 精准匹配策略：
                # MI_01 通常是 interface_number=1
                # 或者是 Vendor Defined 的 Usage Page (0xFF00)
                interface = dev_info.get("interface_number", -1)
                usage_page = dev_info.get("usage_page", 0)

                if interface == 1 or usage_page == 0xFF00:
                    target_path = dev_info["path"]
                    break

            # 2. 如果找到了路径，通过 open_path 打开
            if target_path:
                new_dev = hid.device()
                new_dev.open_path(target_path)
                new_dev.set_nonblocking(True)
                
                self._device = new_dev
                self._set_status(DevStatus.CONNECTED)
                logger.info("HID 接口 (MI_01) 连接成功！")
                logger.debug(f"详细路径: {target_path}") # 这条信息只会在 logs 文件里出现
            else:
                # 没找到匹配的自定义接口
                self._set_status(DevStatus.DISCONNECTED)

        except Exception as e:
            logger.error(f"路径连接尝试失败: {e}")
            self._close_device()

    def send(self, packet: bytes) -> bool:
        """
        完善后的发送函数：线程安全且支持断开检查
        :param packet: 完整的 64 字节包（含 ReportID 和 CRC）
        """
        if not self.is_connected or not self._device:
            return False

        with self._write_lock:
            try:
                # hidapi 发送时，第一个字节必须是 Report ID (0x05)
                # 你的 Protocol.encode 已经处理好了
                sent_len = self._device.write(packet)
                return sent_len > 0
            except Exception as e:
                logger.error(f"发送失败: {e}")
                self._close_device()
                return False