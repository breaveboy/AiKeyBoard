#ifndef __APP_PROTOCOL_H__
#define __APP_PROTOCOL_H__


#include<stdint.h>
#include<string.h>


//协议的基础定义
#define PROTOCOL_REPORT_ID   0x09  //包的报告头
#define PROTOCOL_PKT_SIZE    64    //包的大小
#define PROTOCOL_PKT_ACK_EP  0x82  //in端点
#define PROTOCOL_TIMEOUT_MS   50  //超时判断

////////////////////////命令id划分////////////////////////////
#define CMD_WRITE_CONFIG 0x04
#define CMD_READ_CONFIG  0x84
#define CMD_MUSIC_DATA   0x08
#define CMD_BUBLE_BOTIFY 0xFE //冒泡主动上报



//定义命令的结构体
//64-8=56个数据有效区
#pragma pack(1)
typedef struct{
	uint8_t report_id;     //报告id   byte0
	uint8_t cmd_id;       //命令参数
	uint8_t cmd_param;    //命令参数
	uint8_t reserved;     //预留字节
  uint8_t total_pkts;    //总包数
  uint8_t cur_pkt;       //当前包数
	uint8_t data_len;      //有效数据长度
	uint8_t payload[56];    //数据区
	uint8_t crc;             //前面字段的校验和
}Packet_t;
#pragma pack()



//////////////////定义函数接口
uint8_t App_protocol_sum(uint8_t *buf);
void App_protocol_task(void);
void App_protocol_on_rx(uint8_t *buf, uint32_t len); 

#endif
