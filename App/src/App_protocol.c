#include "App_protocol.h"
#include "App_lighting.h"
#include "py32f4xx_hal.h"
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
///////////////音乐律动相关/////////
extern uint32_t g_last_music_rx_time;
extern LightMode_t g_backup_light_mode;
#define WS2812_LED_NUM 61
extern void App_set_light_config(uint8_t mode, uint8_t r, uint8_t g, uint8_t b, uint8_t br, uint8_t speed);
extern void App_get_light_config(uint8_t *mode, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *br, uint8_t *speed);
extern bool lib_ws2812_set_pixel(uint16_t led_index, uint8_t r, uint8_t g, uint8_t b);

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
                         //Payload_LightColor_t *p_color = (Payload_LightColor_t *)tx_pkt.payload;
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
                {  // <--- 新增左大括号
                    need_ack = 0; // 高频音律流直接丢弃 ACK 机制，压榨带宽以获取极致响应

                    // 1. 动效保护：备份切换音律前的键盘灯光模式
                    if (g_light_mode != LIGHT_MODE_MUSIC) {
                        g_backup_light_mode = g_light_mode;
                        g_light_mode = LIGHT_MODE_MUSIC;
                    }

                    // 2. 更新音律喂狗时间戳，防止触发超时自动退回
                    g_last_music_rx_time = HAL_GetTick();

                    uint8_t cur_pkt = g_cur_pkt.cur_pkt;       // 当前包序：0 ~ 3
                    uint8_t total_pkts = g_cur_pkt.total_pkts; // 总包数：4
                    uint8_t data_len = g_cur_pkt.data_len;     // 前三包为 54 字节，第四包为 21 字节

                    // 3. 基于 18 颗灯的索引寻址（无索引高密方案）
                    uint16_t start_led_idx = cur_pkt * 18;

                    if (start_led_idx < WS2812_LED_NUM) {
                        uint8_t led_count_in_pkt = data_len / 3; // 自动还原出该包灯数 (极限 18 颗)
                        for (uint8_t i = 0; i < led_count_in_pkt; i++) {
                            uint16_t led_idx = start_led_idx + i;
                            if (led_idx >= WS2812_LED_NUM) {
                                break;
                            }

                            // 提取流中 RGB 数据
                            uint8_t r = g_cur_pkt.payload[i * 3 + 0];
                            uint8_t g = g_cur_pkt.payload[i * 3 + 1];
                            uint8_t b = g_cur_pkt.payload[i * 3 + 2];

                            // 折算键盘当前的全局亮度比例
                            r = (uint16_t)(r * g_light_brightness) / 100;
                            g = (uint16_t)(g * g_light_brightness) / 100;
                            b = (uint16_t)(b * g_light_brightness) / 100;

                            // 写入物理驱动显存
                            lib_ws2812_set_pixel(led_idx, r, g, b);
                        }
                    }

                    // 4. 双缓冲防撕裂：仅在最后一包数据（cur_pkt == 3）解完后，才统一允许硬件刷新
                    if (cur_pkt == (total_pkts - 1)) {
                        g_led_dirty = true;
                    }
                    break;
                }  // <--- 新增右大括号
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





























