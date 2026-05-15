#include "App_protocol.h"
#include "App_lighting.h"
//定义全局变量
static Packet_t g_cur_pkt;  //暂存接受的数据包
static volatile uint8_t g_new_recv_pkt;  //新数据包的标志位

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
// CherryUSB 发送接口，声明需与 usb_dc.h 中的原型保持一致。
extern int usbd_ep_start_write(const uint8_t ep, const uint8_t *data, uint32_t len);
void App_protocol_on_rx(uint8_t *buf, uint32_t len){
	//判断头是否正常
	if(buf[0]!=PROTOCOL_REPORT_ID||len!=PROTOCOL_PKT_SIZE){
		return;
	}
  //2.进行crc校验
	if(App_protocol_sum(buf)!=buf[63]){
	  return;
	}
    
   ///标记给task进行业务处理
	if(!g_new_recv_pkt){
		memcpy(&g_cur_pkt,buf,PROTOCOL_PKT_SIZE);
		g_new_recv_pkt=1;
	}

}           
extern void App_set_light_config(uint8_t mode, uint8_t r, uint8_t g, uint8_t b, uint8_t br, uint8_t speed);
extern void App_get_light_config(uint8_t *mode, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *br, uint8_t *speed);
// 3. 业务处理分发任务
void App_protocol_task(void){
    if(g_new_recv_pkt){
        static Packet_t tx_pkt;
        uint8_t need_ack=1;   //默认是需要回传应答
        
       
        //默认复制接受到的数据包
        memcpy(&tx_pkt,&g_cur_pkt,PROTOCOL_PKT_SIZE);
       
        //清除接受的标志位,USB后台继续接收下一包
        g_new_recv_pkt=0;
        
        
        /* =================== 灯光控制协议处理 =================== */
        uint8_t cmd_id    =g_cur_pkt.cmd_id;
        uint8_t cmd_param =g_cur_pkt.cmd_param;
        
        
        //下发/写入的指令
        if((cmd_id&0x7F)>=0x20&&(cmd_id&0x7F)<=0x2F){
            switch(cmd_id){
                case CMD_LIGHT_WRITE_CFG: //0x20  写灯光模式
                    if(cmd_param==LPARAM_ALL_SET){ //综合设置
                        //提取payload的数据
                        Payload_LightAll_t *p_light=(Payload_LightAll_t*)tx_pkt.payload;
                        
                        //传递给灯光控制层  全部设置 模式id+rgb+亮度+速度
                        App_set_light_config(p_light->mode_idx,p_light->r,p_light->g,p_light->b,p_light->brightness,p_light->speed);
                    }else if(cmd_param==LPARAM_COLOR_ONLY){
                         Payload_LightColor_t *p_color = (Payload_LightColor_t *)tx_pkt.payload;
                         //传递给灯光控制层
                    }else if(cmd_param==LPARAM_MODE_ONLY){
                        if (g_cur_pkt.data_len >= 1) {
                            uint8_t mode = g_cur_pkt.payload[0];

                            if (mode < LIGHT_MODE_MAX) {
                                App_set_light_config(
                                    mode,
                                    g_light_r,
                                    g_light_g,
                                    g_light_b,
                                    g_light_brightness,
                                    g_light_speed
                                );
                            }
                        }
      
                    }
                    break;
                  // -------- [读] 电脑读取灯光配置 --------
                case CMD_LIGHT_READ_CFG: // 0xA0
                    if (cmd_param == LPARAM_ALL_SET) {
                        Payload_LightAll_t *p_light = (Payload_LightAll_t *)tx_pkt.payload;
                        // 获取当前灯光状态，填入到 payload 返回给电脑
                        App_get_light_config(&p_light->mode_idx, 
                                             &p_light->r, &p_light->g, &p_light->b, 
                                             &p_light->brightness, &p_light->speed);
                        tx_pkt.data_len = sizeof(Payload_LightAll_t);
                    }
                    break;

                // -------- [写] 音乐律动高频推流 --------
                case CMD_LIGHT_MUSIC_MAIN: // 0x22
                   
                    need_ack = 0; 
                    break;

                default:
                    break;
            
            
            
            
            }

        
        }

         // 将应答包回传给 PC
        if(need_ack){
            // 重新计算并更新发送包的 CRC
            tx_pkt.crc = App_protocol_sum((uint8_t *)&tx_pkt);
            // 通过 USB 自定义 IN 端点 (0x82) 发送
            usbd_ep_start_write(PROTOCOL_PKT_ACK_EP, (uint8_t *)&tx_pkt, PROTOCOL_PKT_SIZE);
        }
        
        
    
    }



}





























