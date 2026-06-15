from __future__ import annotations

import logging
import struct
import threading
import time
from datetime import datetime
from pathlib import Path

from PySide6.QtCore import QObject, Property, Signal, Slot

from hardware.packet_codec import McuPacketCodec
from hardware.protocol_constants import DEFAULT_MCU_PID, DEFAULT_MCU_VID

logger = logging.getLogger(__name__)

CMD_SYS_DEBUG = 0xF3
DEBUG_PARAM_READ = 0x00
DEBUG_PARAM_CLEAR = 0x01
DEBUG_PARAM_ADC_FILTERED0 = 0x10
DEBUG_PARAM_ADC_RAW0 = 0x20
DEBUG_PAYLOAD_FORMAT = "<IIIIII4B"
DEBUG_PAYLOAD_SIZE = struct.calcsize(DEBUG_PAYLOAD_FORMAT)
ADC_PAYLOAD_FORMAT = "<BB14H"
ADC_PAYLOAD_SIZE = struct.calcsize(ADC_PAYLOAD_FORMAT)


class DebugBackend(QObject):
    connectionChanged = Signal()
    summaryChanged = Signal()
    logTextChanged = Signal()
    logFileChanged = Signal()
    adcFileChanged = Signal()
    displayPausedChanged = Signal()
    adcChanged = Signal()
    adcStatusChanged = Signal()
    adcDisplayPausedChanged = Signal()
    activeChanged = Signal()

    _sampleReady = Signal(object)
    _adcReady = Signal(object)
    _connectionReady = Signal(str)
    _logReady = Signal(str)

    def __init__(self, parent=None):
        super().__init__(parent)
        self._active = False
        self._connection = "未连接"
        self._summary = {
            "uptime": "--",
            "main": "0",
            "dma": "0",
            "frame": "0",
            "key": "0",
            "usb": "0",
            "row": "--",
            "flags": "--",
            "error": "无",
        }
        self._log_lines: list[str] = []
        self._display_paused = False
        log_dir = Path(__file__).resolve().with_name("logs")
        log_dir.mkdir(parents=True, exist_ok=True)
        self._log_file = log_dir / (
            "keyboard_debug_" + datetime.now().strftime("%Y%m%d_%H%M%S") + ".log"
        )
        self._adc_file = log_dir / (
            "keyboard_adc_" + datetime.now().strftime("%Y%m%d_%H%M%S") + ".csv"
        )
        self._log_lock = threading.Lock()
        self._adc_file_lock = threading.Lock()
        self._worker: threading.Thread | None = None
        self._stop_event = threading.Event()
        self._device = None
        self._device_lock = threading.Lock()
        self._last_sample: dict[str, int] | None = None
        self._adc_filtered = [0] * 70
        self._adc_raw = [0] * 70
        self._adc_latest_filtered = [0] * 70
        self._adc_latest_raw = [0] * 70
        self._adc_updated_row = -1
        self._adc_filtered_rows = 0
        self._adc_raw_rows = 0
        self._adc_display_paused = False
        self._adc_status = "等待ADC数据"
        self._next_adc_retry = 0.0

        self._sampleReady.connect(self._apply_sample)
        self._adcReady.connect(self._apply_adc)
        self._connectionReady.connect(self._set_connection)
        self._logReady.connect(self._append_log)

    @Property(bool, notify=activeChanged)
    def active(self) -> bool:
        return self._active

    @Property(str, notify=connectionChanged)
    def connection(self) -> str:
        return self._connection

    @Property(str, notify=summaryChanged)
    def uptime(self) -> str:
        return self._summary["uptime"]

    @Property(str, notify=summaryChanged)
    def mainCount(self) -> str:
        return self._summary["main"]

    @Property(str, notify=summaryChanged)
    def dmaCount(self) -> str:
        return self._summary["dma"]

    @Property(str, notify=summaryChanged)
    def frameCount(self) -> str:
        return self._summary["frame"]

    @Property(str, notify=summaryChanged)
    def keyChangeCount(self) -> str:
        return self._summary["key"]

    @Property(str, notify=summaryChanged)
    def usbCount(self) -> str:
        return self._summary["usb"]

    @Property(str, notify=summaryChanged)
    def currentRow(self) -> str:
        return self._summary["row"]

    @Property(str, notify=summaryChanged)
    def stateFlags(self) -> str:
        return self._summary["flags"]

    @Property(str, notify=summaryChanged)
    def errorText(self) -> str:
        return self._summary["error"]

    @Property(str, notify=logTextChanged)
    def logText(self) -> str:
        return "\n".join(self._log_lines)

    @Property(str, notify=logFileChanged)
    def logFile(self) -> str:
        return str(self._log_file)

    @Property(str, notify=adcFileChanged)
    def adcFile(self) -> str:
        return str(self._adc_file)

    @Property(bool, notify=displayPausedChanged)
    def displayPaused(self) -> bool:
        return self._display_paused

    @Property("QVariantList", notify=adcChanged)
    def adcFiltered(self):
        return self._adc_filtered

    @Property("QVariantList", notify=adcChanged)
    def adcRaw(self):
        return self._adc_raw

    @Property(int, notify=adcChanged)
    def adcUpdatedRow(self) -> int:
        return self._adc_updated_row

    @Property(bool, notify=adcDisplayPausedChanged)
    def adcDisplayPaused(self) -> bool:
        return self._adc_display_paused

    @Property(bool, notify=adcChanged)
    def adcFrameReady(self) -> bool:
        return self._adc_filtered_rows == 0x1F and self._adc_raw_rows == 0x1F

    @Property(str, notify=adcStatusChanged)
    def adcStatus(self) -> str:
        return self._adc_status

    @Slot(bool)
    def setActive(self, active: bool) -> None:
        if active == self._active:
            return
        self._active = active
        self.activeChanged.emit()
        if active:
            self._start()
        else:
            self.stop()

    @Slot()
    def refresh(self) -> None:
        if not self._active:
            self.setActive(True)

    @Slot()
    def clearCounters(self) -> None:
        if self._send_command(DEBUG_PARAM_CLEAR):
            self._append_log("已发送清除计数命令")
        else:
            self._append_log("清除计数失败：设备未连接")

    @Slot()
    def clearLog(self) -> None:
        self._log_lines.clear()
        self.logTextChanged.emit()

    @Slot()
    def toggleDisplayPause(self) -> None:
        self._display_paused = not self._display_paused
        self.displayPausedChanged.emit()
        if not self._display_paused:
            self.logTextChanged.emit()

    @Slot()
    def recordAdcSnapshot(self) -> None:
        self._append_log("ADC滤波矩阵:")
        for row in range(5):
            values = self._adc_latest_filtered[row * 14 : (row + 1) * 14]
            self._append_log(f"FILTERED R{row}: " + " ".join(map(str, values)))
        self._append_log("ADC原始矩阵:")
        for row in range(5):
            values = self._adc_latest_raw[row * 14 : (row + 1) * 14]
            self._append_log(f"RAW R{row}: " + " ".join(map(str, values)))

    @Slot()
    def toggleAdcDisplayPause(self) -> None:
        self._adc_display_paused = not self._adc_display_paused
        self.adcDisplayPausedChanged.emit()
        if not self._adc_display_paused:
            self._adc_filtered[:] = self._adc_latest_filtered
            self._adc_raw[:] = self._adc_latest_raw
            self.adcChanged.emit()

    @Slot()
    def stop(self) -> None:
        self._stop_event.set()
        self._close_device()
        worker = self._worker
        if worker and worker is not threading.current_thread():
            worker.join(timeout=1.0)
        self._worker = None
        if self._active:
            self._active = False
            self.activeChanged.emit()
        self._set_connection("已停止")

    def _start(self) -> None:
        if self._worker and self._worker.is_alive():
            return
        self._stop_event.clear()
        self._worker = threading.Thread(target=self._poll_loop, daemon=True)
        self._worker.start()

    def _poll_loop(self) -> None:
        self._logReady.emit("诊断监控已启动")
        next_status_poll = 0.0
        next_adc_poll = 0.0
        while not self._stop_event.is_set():
            if self._device is None and not self._open_device():
                self._stop_event.wait(1.0)
                continue

            now = time.monotonic()
            if now >= next_status_poll:
                if not self._send_command(DEBUG_PARAM_READ):
                    self._mark_disconnected("发送诊断查询失败")
                    continue

                response = self._read_response(400)
                if response is None:
                    self._mark_disconnected("诊断响应超时")
                    continue

                sample = self._decode_response(response)
                if sample is not None:
                    self._sampleReady.emit(sample)
                next_status_poll = now + 0.5

            if now >= next_adc_poll and now >= self._next_adc_retry:
                adc_ok = True
                for row in range(5):
                    if self._poll_adc_row(DEBUG_PARAM_ADC_FILTERED0 + row) != "ok":
                        adc_ok = False
                        break
                    if self._poll_adc_row(DEBUG_PARAM_ADC_RAW0 + row) != "ok":
                        adc_ok = False
                        break

                if adc_ok:
                    self._set_adc_status("ADC数据正常")
                    self._write_adc_frame()
                    next_adc_poll = time.monotonic() + 0.2
                else:
                    self._set_adc_status("MCU未返回ADC数据，请重新编译并烧录最新固件")
                    self._next_adc_retry = time.monotonic() + 5.0
            self._stop_event.wait(0.01)

    def _poll_adc_row(self, parameter: int) -> str:
        if not self._send_command(parameter):
            return "failed"
        response = self._read_response(400)
        if response is None:
            return "failed"
        adc = self._decode_adc_response(response, parameter)
        if adc is None:
            return "unsupported"
        self._adcReady.emit(adc)
        return "ok"

    def _open_device(self) -> bool:
        try:
            import hid

            target_path = None
            for info in hid.enumerate(DEFAULT_MCU_VID, DEFAULT_MCU_PID):
                if info.get("interface_number", -1) == 1 or info.get("usage_page", 0) == 0xFF00:
                    target_path = info.get("path")
                    break
            if target_path is None:
                self._connectionReady.emit("未找到设备")
                return False

            device = hid.device()
            device.open_path(target_path)
            device.set_nonblocking(0)
            with self._device_lock:
                self._device = device
            self._connectionReady.emit("已连接")
            self._logReady.emit("Custom HID 已连接")
            return True
        except Exception as exc:
            logger.warning("Debug HID connection failed: %s", exc)
            self._connectionReady.emit("连接失败")
            return False

    def _send_command(self, parameter: int) -> bool:
        packet = McuPacketCodec.encode(CMD_SYS_DEBUG, parameter, b"")
        with self._device_lock:
            if self._device is None:
                return False
            try:
                return self._device.write(packet) > 0
            except Exception as exc:
                logger.warning("Debug HID write failed: %s", exc)
                return False

    def _read_response(self, timeout_ms: int) -> bytes | None:
        with self._device_lock:
            if self._device is None:
                return None
            try:
                data = bytes(self._device.read(64, timeout_ms))
            except Exception as exc:
                logger.warning("Debug HID read failed: %s", exc)
                return None
        return data if len(data) == 64 else None

    def _decode_response(self, data: bytes) -> dict[str, int] | None:
        packet = McuPacketCodec.decode(data)
        if packet is None:
            self._logReady.emit("收到校验失败的数据包")
            return None
        if packet["command"] != CMD_SYS_DEBUG or packet["parameter"] != DEBUG_PARAM_READ:
            return None

        payload = packet["payload"]
        if len(payload) != DEBUG_PAYLOAD_SIZE:
            self._logReady.emit(f"诊断数据长度异常：{len(payload)}，期望 {DEBUG_PAYLOAD_SIZE}")
            return None

        names = ("uptime", "main", "dma", "frame", "key", "usb",
                 "row", "flags", "error", "reserved")
        return dict(zip(names, struct.unpack(DEBUG_PAYLOAD_FORMAT, payload)))

    def _decode_adc_response(self, data: bytes, parameter: int):
        packet = McuPacketCodec.decode(data)
        if packet is None:
            return None
        if packet["command"] != CMD_SYS_DEBUG or packet["parameter"] != parameter:
            return None
        payload = packet["payload"]
        if len(payload) != ADC_PAYLOAD_SIZE:
            return None
        row, value_type, *values = struct.unpack(ADC_PAYLOAD_FORMAT, payload)
        if row >= 5 or value_type not in (0, 1):
            return None
        return {
            "row": row,
            "value_type": value_type,
            "values": values,
        }

    @Slot(object)
    def _apply_sample(self, sample: dict[str, int]) -> None:
        flags = self._format_flags(sample["flags"])
        error = self._format_error(sample["error"])
        self._summary = {
            "uptime": self._format_uptime(sample["uptime"]),
            "main": str(sample["main"]),
            "dma": str(sample["dma"]),
            "frame": str(sample["frame"]),
            "key": str(sample["key"]),
            "usb": str(sample["usb"]),
            "row": str(sample["row"]),
            "flags": flags,
            "error": error,
        }
        self.summaryChanged.emit()

        conclusion = self._diagnose(self._last_sample, sample)
        self._last_sample = sample
        self._append_log(
            f"row={sample['row']} main={sample['main']} dma={sample['dma']} "
            f"frame={sample['frame']} key={sample['key']} usb={sample['usb']} "
            f"flags={flags} error={error}{conclusion}"
        )

    @Slot(object)
    def _apply_adc(self, sample) -> None:
        row = sample["row"]
        start = row * 14
        if sample["value_type"] == 1:
            self._adc_latest_filtered[start : start + 14] = sample["values"]
            self._adc_filtered_rows |= 1 << row
            if not self._adc_display_paused:
                self._adc_filtered[start : start + 14] = sample["values"]
        else:
            self._adc_latest_raw[start : start + 14] = sample["values"]
            self._adc_raw_rows |= 1 << row
            if not self._adc_display_paused:
                self._adc_raw[start : start + 14] = sample["values"]
        self._adc_updated_row = row
        if not self._adc_display_paused:
            self.adcChanged.emit()

    @staticmethod
    def _diagnose(previous, current) -> str:
        if previous is None:
            return ""
        if current["main"] == previous["main"]:
            return " | 异常：主循环未推进"
        if current["dma"] == previous["dma"]:
            return " | 异常：ADC/DMA未推进"
        if current["frame"] == previous["frame"]:
            return " | 异常：整帧扫描未完成"
        if current["error"] != 0:
            return " | 异常：MCU已记录错误"
        return " | 正常"

    @Slot(str)
    def _set_connection(self, value: str) -> None:
        if value != self._connection:
            self._connection = value
            self.connectionChanged.emit()

    def _set_adc_status(self, value: str) -> None:
        if value != self._adc_status:
            self._adc_status = value
            self.adcStatusChanged.emit()

    @Slot(str)
    def _append_log(self, message: str) -> None:
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
        line = f"{timestamp}  {message}"
        self._log_lines.append(line)
        if len(self._log_lines) > 300:
            del self._log_lines[:-300]
        if not self._display_paused:
            self.logTextChanged.emit()
        self._write_log_file(line)

    def _write_log_file(self, line: str) -> None:
        try:
            with self._log_lock:
                with self._log_file.open("a", encoding="utf-8", newline="\n") as stream:
                    stream.write(line + "\n")
        except OSError as exc:
            logger.error("Failed to save diagnostic log: %s", exc)

    def _write_adc_frame(self) -> None:
        try:
            new_file = not self._adc_file.exists()
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
            with self._adc_file_lock:
                with self._adc_file.open("a", encoding="utf-8", newline="\n") as stream:
                    if new_file:
                        columns = ",".join(f"C{column}" for column in range(14))
                        stream.write(f"time,type,row,{columns}\n")
                    for row in range(5):
                        start = row * 14
                        filtered = self._adc_latest_filtered[start : start + 14]
                        raw = self._adc_latest_raw[start : start + 14]
                        stream.write(
                            f"{timestamp},filtered,{row},"
                            + ",".join(map(str, filtered))
                            + "\n"
                        )
                        stream.write(
                            f"{timestamp},raw,{row},"
                            + ",".join(map(str, raw))
                            + "\n"
                        )
        except OSError as exc:
            logger.error("Failed to save ADC data: %s", exc)

    def _mark_disconnected(self, reason: str) -> None:
        self._logReady.emit(reason)
        self._connectionReady.emit("连接中断")
        self._close_device()
        self._stop_event.wait(1.0)

    def _close_device(self) -> None:
        with self._device_lock:
            device = self._device
            self._device = None
        if device is not None:
            try:
                device.close()
            except Exception:
                pass

    @staticmethod
    def _format_uptime(milliseconds: int) -> str:
        seconds = milliseconds // 1000
        hours, seconds = divmod(seconds, 3600)
        minutes, seconds = divmod(seconds, 60)
        return f"{hours:02d}:{minutes:02d}:{seconds:02d}"

    @staticmethod
    def _format_flags(flags: int) -> str:
        names = []
        if flags & 0x01:
            names.append("ADC完成")
        if flags & 0x02:
            names.append("帧完成")
        if flags & 0x04:
            names.append("待上报")
        if flags & 0x08:
            names.append("HID忙")
        return " / ".join(names) if names else "运行中"

    @staticmethod
    def _format_error(error: int) -> str:
        return {
            0: "无",
            1: "DMA错误",
            2: "USB发送失败",
            3: "USB忙超时",
        }.get(error, f"未知错误({error})")
