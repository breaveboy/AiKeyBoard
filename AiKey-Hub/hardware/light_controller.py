from __future__ import annotations

import logging

from .hid_connection import HidMcuConnection
from .packet_codec import McuPacketCodec
from .protocol_constants import (
    DEFAULT_MCU_PID,
    DEFAULT_MCU_VID,
    Command,
    LightParameter,
)

logger = logging.getLogger(__name__)

MUSIC_FRAME_PACKET_SIZES = (54, 54, 54, 21)
MUSIC_FRAME_RGB_LENGTH = 61 * 3


class McuLightController:
    def __init__(self, connection: HidMcuConnection | None = None):
        self.connection = connection or HidMcuConnection(DEFAULT_MCU_VID, DEFAULT_MCU_PID)

    def start(self) -> None:
        self.connection.start()

    def stop(self) -> None:
        self.connection.stop()
    
    #灯光模式切换的接口
    def set_mode(self, mode: int) -> bool:
        if not 0 <= mode <= 0xFF:
            raise ValueError(f"灯光模式超出范围: {mode}")

        payload = bytes([mode] + [0x00] * 6)
        packet = McuPacketCodec.encode(
            command=Command.LIGHT_CONFIG_WRITE,
            parameter=LightParameter.MODE_ONLY,
            payload=payload,
        )
        sent = self.connection.send(packet)
        if sent:
            logger.info("灯光模式切换指令已发送: 模式=0x%02X", mode)
        else:
            logger.warning("灯光模式切换未发送: MCU 未连接，模式=0x%02X", mode)
        return sent

    def send_music_frame(self, rgb_frame: bytes) -> bool:
        if len(rgb_frame) != MUSIC_FRAME_RGB_LENGTH:
            raise ValueError(f"Music RGB frame must be {MUSIC_FRAME_RGB_LENGTH} bytes.")

        offset = 0
        for current, size in enumerate(MUSIC_FRAME_PACKET_SIZES):
            payload = rgb_frame[offset : offset + size]
            offset += size
            packet = McuPacketCodec.encode(
                command=Command.LIGHT_MUSIC,
                parameter=0x00,
                reserved=0,
                total=len(MUSIC_FRAME_PACKET_SIZES),
                current=current,
                payload=payload,
            )
            if not self.connection.send(packet):
                return False
        return True
