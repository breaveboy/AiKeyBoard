from __future__ import annotations

from enum import IntEnum


class Report(IntEnum):
    ID = 0x05
    SIZE = 64


class Command(IntEnum):
    LIGHT_CONFIG_WRITE = 0x20
    LIGHT_MUSIC = 0x22
    LIGHT_CONFIG_READ = 0xA0
    AI_ACTION = 0xFE


class LightParameter(IntEnum):
    ALL_SETTINGS = 0x00
    MODE_ONLY = 0x01
    BRIGHTNESS_ONLY = 0x03


class AiParameter(IntEnum):
    ACTION = 0x04

# 01唤醒 02运行 03替换
class AiAction(IntEnum):
    WAKE = 0x01
    RUN = 0x02
    REPLACE = 0x03

# 默认的MCU vid和pid
DEFAULT_MCU_VID = 0x36B7
DEFAULT_MCU_PID = 0xFFFF
