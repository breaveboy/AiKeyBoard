#include "App_protocol.h"

//定义全局变量
static Packet_t g_cur_pkt;
static volatile uint8_t g_new_recv_pkt;

//计算crc的校验和
uint8_t App_protocol_sum(uint8_t *buf){
	uint8_t sum=0;
	for(uint8_t i=0;i<63;i++){
		//计算和
		sum+=buf[i];
	}
  sum=(uint8_t)(0xFF - (uint8_t)(sum & 0xFF));
	return sum;
}



/**
 * [接收回调函数]
 * 流程：接收数据 -> 校验CRC -> 立即回传应答(IN数据) -> 标记解析
 */
// 外部 USB 发送函数接口
extern uint8_t usbd_ep_start_write(uint8_t ep, uint8_t *data, uint32_t len);
void App_protocol_on_rx(uint8_t *buf, uint32_t len){
	//判断头是否正常
	if(buf[0]!=PROTOCOL_REPORT_ID||len!=PROTOCOL_PKT_SIZE){
		return;
	}
  //2.进行crc校验
	if(App_protocol_sum(buf)!=buf[64]){
	  return;
	}
  // 立即返回 IN 数据 (停-等机制的核心)
	// 返回 IN 数据：结构与 OUT 完全一致
	// 必须在设备应答后，PC 才会发起下一帧
  usbd_ep_start_write(PROTOCOL_PKT_ACK_EP,buf,PROTOCOL_PKT_SIZE);
  ///标记给task进行业务处理
	if(!g_new_recv_pkt){
		memcpy(&g_cur_pkt,buf,PROTOCOL_PKT_SIZE);
		g_new_recv_pkt=1;
	}

}           

// 3. 业务处理分发任务 (在 Task_exec 中运行)

void App_protocol_task(void){
    



}





























