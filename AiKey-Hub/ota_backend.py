"""
AiKeyBoard OTA 升级后端。

通过 Custom HID 与键盘通信，实现固件升级流程：
    1. 选择 .bin 固件文件
    2. 连接键盘（VID=0x36b7, PID=0xffff）
    3. 发送 BEGIN → DATA × N → END → REBOOT
    4. 实时更新 UI 进度

依赖：
    pip install hid
"""

import logging
import re
import struct
import threading
import time
import zlib
from pathlib import Path
from urllib.parse import unquote, urlparse

from PySide6.QtCore import QObject, Property, Signal, Slot

logger = logging.getLogger(__name__)

# ======================================================================
#  协议常量（与 App_protocol.h / App_ota.h 对齐）
# ======================================================================

USB_VID = 0x36B7
USB_PID = 0xFFFF

REPORT_ID = 0x05
PACKET_SIZE = 64
PAYLOAD_SIZE = 56
CRC_INDEX = 63

CMD_SYS_OTA = 0xF2

OTA_PARAM_QUERY = 0x00
OTA_PARAM_BEGIN = 0x01
OTA_PARAM_DATA = 0x02
OTA_PARAM_END = 0x03
OTA_PARAM_ABORT = 0x04
OTA_PARAM_REBOOT = 0x05

OTA_STATE_IDLE = 0x00
OTA_STATE_RECEIVING = 0x01
OTA_STATE_VERIFYING = 0x02
OTA_STATE_READY = 0x03
OTA_STATE_ERROR = 0x04

OTA_STATUS_OK = 0x00
OTA_STATUS_BUSY = 0x08

OTA_PROTOCOL_VERSION = 1
OTA_DATA_MAX_SIZE = 52  # 56 字节 payload - 4 字节 offset

# ======================================================================
#  工具函数
# ======================================================================


def _calc_checksum(data: bytes) -> int:
    """8-bit 累加反码校验，与 App_protocol_sum 一致。"""
    return (0xFF - sum(data[:CRC_INDEX])) & 0xFF


def _guess_version_from_filename(path: str) -> tuple[int, str]:
    """
    从文件名猜测版本号。
    返回 (numeric_version, version_text)。
    如 "firmware_v1.2.3.bin" → ((1<<24)|(2<<16)|(3<<8), "1.2.3")
    """
    stem = Path(path).stem
    match = re.search(r"v?(\d+)\.(\d+)\.(\d+)", stem)
    if match:
        major, minor, patch = int(match[1]), int(match[2]), int(match[3])
        numeric = (major << 24) | (minor << 16) | (patch << 8)
        text = f"{major}.{minor}.{patch}"
    else:
        numeric = 0x00010000
        text = "1.0.0"
    return numeric, text


# ======================================================================
#  OtaBackend — QML 可访问的后端
# ======================================================================


class OtaBackend(QObject):
    """暴露给 QML 的 OTA 升级后端。"""

    # ---- QML 属性通知信号 ----
    deviceStateChanged = Signal()
    firmwareFileChanged = Signal()
    progressChanged = Signal()
    statusTextChanged = Signal()
    currentVersionChanged = Signal()
    availableVersionChanged = Signal()
    busyChanged = Signal()

    def __init__(self, parent=None):
        super().__init__(parent)
        self._hid_device = None
        self._lock = threading.Lock()

        # QML 绑定属性
        self._device_state = "未连接"
        self._firmware_file = ""
        self._progress = 0.0
        self._status_text = "等待选择固件文件"
        self._current_version = "--"
        self._available_version = "--"
        self._busy = False

        # 内部状态
        self._firmware_data: bytes | None = None
        self._firmware_crc32: int = 0
        self._image_version: int = 0
        self._version_text: str = ""

    # ==================================================================
    #  QML 属性
    # ==================================================================

    @Property(str, notify=deviceStateChanged)
    def deviceState(self) -> str:
        return self._device_state

    @deviceState.setter
    def deviceState(self, val: str) -> None:
        if self._device_state != val:
            self._device_state = val
            self.deviceStateChanged.emit()

    @Property(str, notify=firmwareFileChanged)
    def firmwareFile(self) -> str:
        return self._firmware_file

    @firmwareFile.setter
    def firmwareFile(self, val: str) -> None:
        if self._firmware_file != val:
            self._firmware_file = val
            self.firmwareFileChanged.emit()

    @Property(float, notify=progressChanged)
    def progress(self) -> float:
        return self._progress

    @progress.setter
    def progress(self, val: float) -> None:
        val = max(0.0, min(1.0, val))
        if abs(self._progress - val) > 0.001:
            self._progress = val
            self.progressChanged.emit()

    @Property(str, notify=statusTextChanged)
    def statusText(self) -> str:
        return self._status_text

    @statusText.setter
    def statusText(self, val: str) -> None:
        if self._status_text != val:
            self._status_text = val
            self.statusTextChanged.emit()

    @Property(str, notify=currentVersionChanged)
    def currentVersion(self) -> str:
        return self._current_version

    @currentVersion.setter
    def currentVersion(self, val: str) -> None:
        if self._current_version != val:
            self._current_version = val
            self.currentVersionChanged.emit()

    @Property(str, notify=availableVersionChanged)
    def availableVersion(self) -> str:
        return self._available_version

    @availableVersion.setter
    def availableVersion(self, val: str) -> None:
        if self._available_version != val:
            self._available_version = val
            self.availableVersionChanged.emit()

    @Property(bool, notify=busyChanged)
    def busy(self) -> bool:
        return self._busy

    @busy.setter
    def busy(self, val: bool) -> None:
        if self._busy != val:
            self._busy = val
            self.busyChanged.emit()

    # ==================================================================
    #  QML 可调用槽函数
    # ==================================================================

    @Slot(str)
    def selectFile(self, file_path: str) -> None:
        """用户选择固件文件后 QML FileDialog 回调。"""
        logger.info("selectFile called: %s", file_path)

        # QML FileDialog 返回 "file:///C:/path" 格式，转为本地路径
        if file_path.startswith("file://"):
            file_path = unquote(urlparse(file_path).path)
            if len(file_path) > 2 and file_path[2] == ":":
                file_path = file_path.lstrip("/")
        path = Path(file_path)
        if not path.exists() or path.suffix.lower() != ".bin":
            logger.warning("文件无效: %s (exists=%s)", file_path, path.exists())
            self.statusText = "请选择有效的 .bin 文件"
            return

        self.firmwareFile = str(path)
        data = path.read_bytes()
        if len(data) == 0:
            logger.warning("固件文件为空")
            self.statusText = "固件文件为空"
            return

        self._firmware_data = data
        self._firmware_crc32 = zlib.crc32(data) & 0xFFFFFFFF
        self._image_version, self._version_text = _guess_version_from_filename(
            file_path
        )
        logger.info("固件已加载: %s, %d bytes, CRC=0x%08X, version=%s",
                     path.name, len(data), self._firmware_crc32, self._version_text)
        self.availableVersion = self._version_text
        self.statusText = f"已选择: {path.name}  ({len(data)} bytes)"

    @Slot()
    def startUpgrade(self) -> None:
        """开始升级（在后台线程执行）。"""
        logger.info("startUpgrade called — busy=%s, firmware=%s",
                     self._busy, self._firmware_data is not None)
        if self._busy:
            self.statusText = "正在升级中，请勿重复操作"
            return
        if self._firmware_data is None:
            self.statusText = "请先选择固件文件"
            return

        self.busy = True
        self.progress = 0.0
        self.statusText = "正在连接设备…"
        threading.Thread(target=self._do_upgrade, daemon=True).start()
        logger.info("升级线程已启动")

    @Slot()
    def checkUpdate(self) -> None:
        """查询设备当前状态（后台线程）。"""
        if self._busy:
            logger.info("checkUpdate skipped — busy")
            return
        self.busy = True
        self.statusText = "正在查询设备…"
        threading.Thread(target=self._do_query, daemon=True).start()
        logger.info("查询线程已启动")

    @Slot()
    def closeConnection(self) -> None:
        """切离 OTA 页面时释放 Custom HID。"""
        if not self._busy:
            self._close()

    # ==================================================================
    #  HID 通信
    # ==================================================================

    def _ensure_connected(self) -> bool:
        """确保 HID 设备已连接，尝试打开。"""
        if self._hid_device is not None:
            logger.debug("HID 设备已存在，复用")
            return True
        try:
            import hid
            logger.info("hid 模块已加载")
        except ImportError:
            logger.error("缺少 hid 模块")
            self.statusText = "缺少 hid 模块，请运行: pip install hid"
            return False

        try:
            logger.info("正在枚举 HID 设备 VID=0x%04X PID=0x%04X ...", USB_VID, USB_PID)
            target_path = None
            for dev_info in hid.enumerate(USB_VID, USB_PID):
                # 打印所有字段，确认实际字段名
                logger.info("  HID 设备详情: %s", dev_info)
                usage_page = dev_info.get("usage_page", 0)
                interface = dev_info.get("interface_number", -1)
                path = dev_info.get("path", b"")
                logger.info("  枚举: path=%s interface=%d usage_page=0x%04X",
                            path, interface, usage_page)
                if interface == 1 or usage_page == 0xFF00:
                    target_path = path
                    logger.info("✅ 找到自定义 HID 接口: %s", target_path)
                    break

            if target_path is None:
                raise RuntimeError("未找到自定义 HID 接口 (usage_page=0xFF00)，"
                                   "请确认键盘已连接且固件支持")

            dev = hid.device()
            dev.open_path(target_path)
            dev.set_nonblocking(0)
            self._hid_device = dev
            self.deviceState = "已连接"
            logger.info("HID 设备连接成功")
            return True
        except Exception as e:
            self._hid_device = None
            self.deviceState = "未连接"
            self.statusText = f"连接设备失败: {e}"
            logger.error("HID 连接失败: %s", e)
            return False

    def _close(self) -> None:
        if self._hid_device is not None:
            try:
                self._hid_device.close()
            except Exception:
                pass
            self._hid_device = None
            self.deviceState = "未连接"

    def _send_packet(self, cmd_id: int, cmd_param: int, payload: bytes = b"") -> bool:
        """构造并发送 64 字节 HID 包。返回 True 表示发送成功。"""
        pkt = bytearray(PACKET_SIZE)
        pkt[0] = REPORT_ID
        pkt[1] = cmd_id
        pkt[2] = cmd_param
        pkt[3] = 0  # reserved
        pkt[4] = 0  # total_pkts（DATA 命令不使用分包）
        pkt[5] = 0  # cur_pkt
        data_len = min(len(payload), PAYLOAD_SIZE)
        pkt[6] = data_len
        pkt[7 : 7 + data_len] = payload[:data_len]
        pkt[CRC_INDEX] = _calc_checksum(pkt)

        try:
            with self._lock:
                written = self._hid_device.write(bytes(pkt))
            logger.debug("发送: cmd_id=0x%02X param=0x%02X data_len=%d written=%d",
                          cmd_id, cmd_param, data_len, written)
            if written < 0:
                raise RuntimeError(f"write 返回 {written}")
            return True
        except Exception as e:
            self.statusText = f"发送失败: {e}"
            logger.error("发送失败: %s", e)
            self._close()
            return False

    def _receive_response(self, timeout_ms: int = 1000) -> dict | None:
        """读取应答包，解析为字段字典。超时返回 None。"""
        try:
            with self._lock:
                raw = bytes(self._hid_device.read(PACKET_SIZE, timeout_ms))
        except Exception as e:
            self.statusText = f"接收失败: {e}"
            logger.error("接收失败: %s", e)
            self._close()
            return None

        if len(raw) < PACKET_SIZE:
            logger.warning("接收数据不完整: %d bytes", len(raw))
            return None

        # 校验 checksum
        if _calc_checksum(raw) != raw[CRC_INDEX]:
            logger.warning("CRC 校验失败")
            return None

        # 对于 OTA 命令，payload 中是 Payload_OtaResponse_t
        resp_bytes = raw[7 : 7 + raw[6]]  # payload + data_len
        if len(resp_bytes) < 20:
            logger.warning("响应数据不足: %d bytes", len(resp_bytes))
            return None

        (
            protocol_version,
            state,
            status,
            reserved,
            max_image_size,
            received_size,
            image_crc32,
            image_version,
        ) = struct.unpack_from("<BBBB IIII", resp_bytes, 0)

        logger.debug("收到响应: state=%d status=%d received=%d ver=0x%08X",
                      state, status, received_size, image_version)

        return {
            "protocol_version": protocol_version,
            "state": state,
            "status": status,
            "max_image_size": max_image_size,
            "received_size": received_size,
            "image_crc32": image_crc32,
            "image_version": image_version,
        }

    # ==================================================================
    #  OTA 协议实现
    # ==================================================================

    def _do_query(self) -> None:
        """查询设备 OTA 状态。"""
        logger.info("===== _do_query 开始 =====")
        try:
            if not self._ensure_connected():
                logger.warning("_do_query: 设备未连接")
                return

            logger.info("发送 QUERY 命令...")
            if not self._send_packet(CMD_SYS_OTA, OTA_PARAM_QUERY):
                logger.warning("_do_query: 发送 QUERY 失败")
                return

            logger.info("等待 QUERY 响应...")
            resp = self._receive_response()
            if resp is None:
                self.statusText = "查询超时，请检查设备连接"
                logger.warning("_do_query: 无响应")
                return

            logger.info("QUERY 响应: state=%s status=%s received=%s",
                         resp["state"], resp["status"], resp["received_size"])

            if resp["status"] != OTA_STATUS_OK:
                self.statusText = f"查询失败 (status={resp['status']})"
                return

            state_names = {
                OTA_STATE_IDLE: "空闲",
                OTA_STATE_RECEIVING: "接收中",
                OTA_STATE_VERIFYING: "校验中",
                OTA_STATE_READY: "可重启升级",
                OTA_STATE_ERROR: "错误",
            }
            state_name = state_names.get(resp["state"], f"未知({resp['state']})")
            self.deviceState = f"已连接 · {state_name}"

            if resp["image_version"] != 0:
                self.currentVersion = f"v{resp['image_version'] >> 24}.{(resp['image_version'] >> 16) & 0xFF}.{(resp['image_version'] >> 8) & 0xFF}"
                logger.info("设备当前固件版本: %s", self._current_version)

            self.statusText = "设备查询完成"
            logger.info("===== _do_query 完成 =====")
        finally:
            self.busy = False

    def _do_upgrade(self) -> None:
        """完整的 OTA 升级流程。"""
        logger.info("===== _do_upgrade 开始 =====")
        try:
            if not self._ensure_connected():
                logger.warning("_do_upgrade: 设备未连接")
                return

            data = self._firmware_data
            total_size = len(data)
            crc32_val = self._firmware_crc32
            logger.info("准备升级: size=%d CRC=0x%08X ver=%s",
                         total_size, crc32_val, self._version_text)

            # ---- 1. BEGIN ----
            self.statusText = "正在发送固件信息…"
            begin_payload = struct.pack(
                "<III 16s",
                total_size,
                crc32_val,
                self._image_version,
                self._version_text.encode("ascii", errors="replace").ljust(
                    16, b"\x00"
                )[:16],
            )
            logger.info("发送 BEGIN...")
            if not self._send_packet(CMD_SYS_OTA, OTA_PARAM_BEGIN, begin_payload):
                logger.warning("BEGIN 发送失败")
                return

            resp = self._receive_response(timeout_ms=2000)
            if resp is None:
                self.statusText = "BEGIN 超时"
                logger.warning("BEGIN 无响应")
                return
            if resp["status"] != OTA_STATUS_OK:
                self.statusText = f"BEGIN 失败 (status={resp['status']})"
                logger.warning("BEGIN 失败: status=%d", resp["status"])
                return
            logger.info("BEGIN 成功: state=%d received=%d", resp["state"], resp["received_size"])

            # ---- 2. DATA × N ----
            offset = 0
            chunk_size = OTA_DATA_MAX_SIZE
            chunk_index = 0

            while offset < total_size:
                chunk = data[offset : offset + chunk_size]
                data_payload = struct.pack("<I", offset) + chunk
                if not self._send_packet(
                    CMD_SYS_OTA, OTA_PARAM_DATA, data_payload
                ):
                    logger.warning("DATA 发送失败: offset=%d", offset)
                    return

                resp = self._receive_response()
                if resp is None:
                    self.statusText = f"DATA 超时 (offset={offset})"
                    logger.warning("DATA 无响应: offset=%d", offset)
                    return
                if resp["status"] == OTA_STATUS_BUSY:
                    logger.debug("设备忙，重试 offset=%d", offset)
                    time.sleep(0.01)
                    continue
                if resp["status"] != OTA_STATUS_OK:
                    self.statusText = (
                        f"DATA 失败 (offset={offset}, status={resp['status']})"
                    )
                    logger.warning("DATA 失败: offset=%d status=%d", offset, resp["status"])
                    return

                offset += len(chunk)
                chunk_index += 1
                self.progress = 0.1 + 0.85 * (offset / total_size)
                if chunk_index % 50 == 0:
                    logger.info("进度: %d/%d (%.1f%%)", offset, total_size, 100 * offset / total_size)
                self.statusText = f"正在发送… {offset}/{total_size} bytes"

            logger.info("固件数据发送完成, 共 %d 包", chunk_index)

            # ---- 3. END ----
            self.statusText = "正在校验固件…"
            end_payload = struct.pack("<II", total_size, crc32_val)
            logger.info("发送 END...")
            if not self._send_packet(CMD_SYS_OTA, OTA_PARAM_END, end_payload):
                return

            resp = self._receive_response(timeout_ms=5000)
            if resp is None:
                self.statusText = "END 超时"
                logger.warning("END 无响应")
                return
            if resp["status"] != OTA_STATUS_OK:
                self.statusText = f"校验失败 (status={resp['status']})"
                logger.warning("END 失败: status=%d", resp["status"])
                return

            self.progress = 1.0
            self.statusText = "固件校验通过，准备重启…"
            logger.info("固件校验通过!")

            # ---- 4. REBOOT ----
            logger.info("发送 REBOOT...")
            if not self._send_packet(CMD_SYS_OTA, OTA_PARAM_REBOOT):
                return

            resp = self._receive_response()
            if resp and resp["status"] == OTA_STATUS_OK:
                self.statusText = "升级成功！键盘即将重启…"
                self.deviceState = "未连接"
                logger.info("升级成功！")
            else:
                self.statusText = "重启命令已发送"
                logger.warning("重启响应: status=%s", resp["status"] if resp else "None")

        except Exception as e:
            self.statusText = f"升级异常: {e}"
            logger.exception("升级异常")
        finally:
            self.busy = False
            self._close()
            logger.info("===== _do_upgrade 结束 =====")
