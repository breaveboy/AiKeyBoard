from __future__ import annotations

import logging
import struct

from .protocol_constants import Report

logger = logging.getLogger(__name__)


class McuPacketCodec:
    HEADER_FMT = "<BBBBBBB"

    @staticmethod
    def calculate_crc(data: bytes) -> int:
        check_sum = sum(data[: Report.SIZE - 1]) & 0xFF
        return (0xFF - check_sum) & 0xFF

    @classmethod
    def encode(
        cls,
        command: int,
        parameter: int,
        payload: bytes,
        *,
        reserved: int = 0,
        total: int = 1,
        current: int = 1,
    ) -> bytes:
        header = struct.pack(
            cls.HEADER_FMT,
            Report.ID,
            command,
            parameter,
            reserved,
            total,
            current,
            len(payload),
        )
        packet = (header + payload).ljust(Report.SIZE - 1, b"\x00")
        return packet + bytes([cls.calculate_crc(packet)])

    @classmethod
    def decode(cls, data: bytes) -> dict[str, int | bytes] | None:
        if len(data) != Report.SIZE:
            return None
        if cls.calculate_crc(data) != data[-1]:
            logger.error("MCU packet CRC mismatch")
            return None

        report_id, command, parameter, reserved, total, current, data_len = struct.unpack(
            cls.HEADER_FMT,
            data[:7],
        )
        return {
            "report_id": report_id,
            "command": command,
            "parameter": parameter,
            "reserved": reserved,
            "total": total,
            "current": current,
            "length": data_len,
            "payload": data[7 : 7 + data_len],
        }
