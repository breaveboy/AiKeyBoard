from __future__ import annotations

import logging
import struct
import threading
from enum import IntEnum
from pathlib import Path
from typing import Callable

from .hid_connection import HidMcuConnection
from .packet_codec import McuPacketCodec

logger = logging.getLogger(__name__)


class OtaParameter(IntEnum):
    """OTA 子命令（与 App_protocol.h OtaCmdParam_t 对齐）。"""
    QUERY = 0x00
    BEGIN = 0x01
    DATA = 0x02
    END = 0x03
    ABORT = 0x04
    REBOOT = 0x05
