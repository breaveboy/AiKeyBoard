from __future__ import annotations

import logging
import threading
import time
from enum import IntEnum
from typing import Callable, Optional

try:
    import hid  # type: ignore
except ImportError:
    hid = None

logger = logging.getLogger(__name__)


class DeviceStatus(IntEnum):
    DISCONNECTED = 0
    CONNECTING = 1
    CONNECTED = 2
    LOST = 3


class HidMcuConnection:
    def __init__(self, vid: int, pid: int):
        self.vid = vid
        self.pid = pid
        self.on_packet_received: Optional[Callable[[bytes], None]] = None
        self.on_status_changed: Optional[Callable[[DeviceStatus], None]] = None
        self._device = None
        self._status = DeviceStatus.DISCONNECTED
        self._running = False
        self._worker_thread: Optional[threading.Thread] = None
        self._write_lock = threading.Lock()

    @property
    def status(self) -> DeviceStatus:
        return self._status

    @property
    def is_connected(self) -> bool:
        return self._status == DeviceStatus.CONNECTED

    def start(self) -> None:
        if self._running:
            return
        if hid is None:
            logger.warning("hidapi 未安装，MCU HID 通讯不可用")
            return
        self._running = True
        self._worker_thread = threading.Thread(target=self._worker_loop, daemon=True)
        self._worker_thread.start()
        logger.info("MCU HID 连接线程已启动")

    def stop(self) -> None:
        self._running = False
        self._close_device()
        if self._worker_thread:
            self._worker_thread.join(timeout=1.0)

    def send(self, packet: bytes) -> bool:
        if not self.is_connected or self._device is None:
            return False

        should_close = False
        with self._write_lock:
            try:
                return self._device.write(packet) > 0
            except Exception as exc:
                logger.error("MCU HID 发送失败: %s", exc)
                self._set_status(DeviceStatus.LOST)
                should_close = True

        if should_close:
            self._close_device()
        return False

    def _worker_loop(self) -> None:
        while self._running:
            if self._device is None:
                self._try_connect()
                if self._device is None:
                    time.sleep(1.0)
                    continue

            try:
                data = self._device.read(64)
                if data and self.on_packet_received:
                    self.on_packet_received(bytes(data))
            except OSError as exc:
                logger.error("MCU HID 通讯中断: %s", exc)
                self._set_status(DeviceStatus.LOST)
                self._close_device()
            time.sleep(0.001)

    def _try_connect(self) -> None:
        if hid is None:
            return
        try:
            self._set_status(DeviceStatus.CONNECTING)
            target_path = self._find_target_path()
            if target_path is None:
                self._set_status(DeviceStatus.DISCONNECTED)
                return

            device = hid.device()
            device.open_path(target_path)
            device.set_nonblocking(True)
            self._device = device
            self._set_status(DeviceStatus.CONNECTED)
            logger.info("MCU HID 已连接: VID=%s PID=%s", hex(self.vid), hex(self.pid))
        except Exception as exc:
            logger.error("MCU HID 连接失败: %s", exc)
            self._close_device()

    def _find_target_path(self):
        for dev_info in hid.enumerate(self.vid, self.pid):
            interface = dev_info.get("interface_number", -1)
            usage_page = dev_info.get("usage_page", 0)
            if interface == 1 or usage_page == 0xFF00:
                return dev_info["path"]
        return None

    def _close_device(self) -> None:
        with self._write_lock:
            if self._device is not None:
                try:
                    self._device.close()
                except Exception as exc:
                    logger.error("关闭 MCU HID 设备失败: %s", exc)
                self._device = None
        self._set_status(DeviceStatus.DISCONNECTED)

    def _set_status(self, status: DeviceStatus) -> None:
        if self._status == status:
            return
        self._status = status
        logger.info("MCU HID 状态: %s", status.name)
        if self.on_status_changed:
            self.on_status_changed(status)
