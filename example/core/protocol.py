import logging
import struct
from constants import *
logger = logging.getLogger(__name__)
class Protocol:
    # 头部格式 ID, Cmd, Param, Res, Total, Cur, Len
    HEADER_FMT = '<BBBBBBB'

    @staticmethod
    def calculate_crc(data: bytes) -> int:
        """计算校验和"""
        check_sum=sum(data[:63]) & 0xFF
        return (0xFF - check_sum ) & 0xFF
    @classmethod
    def encode(cls, cmd: Cmd, param: int, res: int, total: int, cur: int, payload: bytes) -> bytes:
        """编码成协议格式"""
        data_len=len(payload)
        header =struct.pack(cls.HEADER_FMT,Report.ID,cmd,param,res,total,cur,data_len)
        # 组装完整包 (Header + Payload + Padding)
        packet=header+payload
        packet = packet.ljust(Report.SIZE - 1, b'\x00') # 填充到63字节
        # 计算校验和
        crc=cls.calculate_crc(packet)
        return packet + bytes([crc])
    
    @classmethod
    def decode(cls, data: bytes):
        """解析收到的64字节数据"""
        if len(data) != Report.SIZE:
            return None
        
        if cls.calculate_crc(data) != data[-1]:
            logger.error("CRC Checksum mismatch")
            return None
        header = struct.unpack(cls.HEADER_FMT, data[:7])
        return {
            "cmd": header[1],
            "param": header[2],
            "res": header[3],
            "total": header[4],
            "cur": header[5],
            "len": header[6],
            "payload": data[7:7+header[6]]
        }