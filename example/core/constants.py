from enum import IntEnum

class Report(IntEnum):
    ID=0x05  #report_id是0x05
    SIZE=64  #包的大小是64字节
    PAYLOAD_SIZE=56  #有效载荷的大小是56字节

class Cmd(IntEnum):
    # 系统类 (0x01-0x0F)
    SYS_CFG_W = 0x03
    SYS_CFG_R = 0x83
    # 按键类 (0x10-0x1F)
    KEY_MAP_W = 0x10
    KEY_RT_W  = 0x19
    # 灯光类 (0x20-0x2F)
    LIGHT_CFG_W = 0x20
    LIGHT_CFG_R = 0xA0
    LIGHT_MUSIC = 0x22
    # 冒泡
    BUBBLE_RPT = 0xFE

class Param:
    """参数分组"""
    class Light(IntEnum):
        ALL_SET = 0x00
        MODE_ONLY = 0x01
        BRIGHT_ONLY = 0x03

    class Bubble(IntEnum):
        BATTERY = 0x02
        AI_KEY_TRIG = 0x04
        
class AiAction(IntEnum):
    TRIGGER = 0x01
    CONFIRM = 0x02
    CANCEL  = 0x03