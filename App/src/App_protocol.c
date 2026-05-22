#include "App_protocol.h"
#include "App_lighting.h"
#include "py32f4xx_hal.h"

#define PROTOCOL_RX_QUEUE_SIZE 8U

static Packet_t g_rx_queue[PROTOCOL_RX_QUEUE_SIZE];
static volatile uint8_t g_rx_head = 0;
static volatile uint8_t g_rx_tail = 0;
static volatile uint8_t g_rx_count = 0;
volatile uint32_t g_protocol_rx_drop_count = 0;
///环形队列接受数据
static bool App_protocol_pop_rx(Packet_t *pkt)
{
    bool has_pkt = false;

    __disable_irq();
    if (g_rx_count > 0U) {
        memcpy(pkt, &g_rx_queue[g_rx_tail], PROTOCOL_PKT_SIZE);
        g_rx_tail = (uint8_t)((g_rx_tail + 1U) % PROTOCOL_RX_QUEUE_SIZE);
        g_rx_count--;
        has_pkt = true;
    }
    __enable_irq();

    return has_pkt;
}
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

    uint8_t next_head = (uint8_t)((g_rx_head + 1U) % PROTOCOL_RX_QUEUE_SIZE);

    if (g_rx_count >= PROTOCOL_RX_QUEUE_SIZE) {
        g_protocol_rx_drop_count++;
        return;
    }

    memcpy(&g_rx_queue[g_rx_head], buf, PROTOCOL_PKT_SIZE);
    g_rx_head = next_head;
    g_rx_count++;
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
    Packet_t rx_pkt;

    while (App_protocol_pop_rx(&rx_pkt)) {
        Packet_t tx_pkt;
        uint8_t need_ack = 1;

        memcpy(&tx_pkt, &rx_pkt, PROTOCOL_PKT_SIZE);

        uint8_t cmd_id = rx_pkt.cmd_id;
        uint8_t cmd_param = rx_pkt.cmd_param;

        if ((cmd_id & 0x7F) >= 0x20 && (cmd_id & 0x7F) <= 0x2F) {
            switch (cmd_id) {
                case CMD_LIGHT_WRITE_CFG:
                    if (cmd_param == LPARAM_ALL_SET) {
                        Payload_LightAll_t *p_light = (Payload_LightAll_t *)tx_pkt.payload;
                        App_set_light_config(p_light->mode_idx, p_light->r, p_light->g, p_light->b, p_light->brightness, p_light->speed);
                    } else if (cmd_param == LPARAM_COLOR_ONLY) {
                    } else if (cmd_param == LPARAM_MODE_ONLY) {
                        if (rx_pkt.data_len >= 1U) {
                            uint8_t mode = rx_pkt.payload[0];

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

                case CMD_LIGHT_READ_CFG:
                    if (cmd_param == LPARAM_ALL_SET) {
                        Payload_LightAll_t *p_light = (Payload_LightAll_t *)tx_pkt.payload;
                        App_get_light_config(&p_light->mode_idx,
                                             &p_light->r, &p_light->g, &p_light->b,
                                             &p_light->brightness, &p_light->speed);
                        tx_pkt.data_len = sizeof(Payload_LightAll_t);
                    }
                    break;

                case CMD_LIGHT_MUSIC_MAIN:
                {
                    need_ack = 0;

                    if (g_light_mode != LIGHT_MODE_MUSIC) {
                        g_backup_light_mode = g_light_mode;
                        g_light_mode = LIGHT_MODE_MUSIC;
                    }

                    g_last_music_rx_time = HAL_GetTick();

                    uint8_t cur_pkt = rx_pkt.cur_pkt;
                    uint8_t total_pkts = rx_pkt.total_pkts;
                    uint8_t data_len = rx_pkt.data_len;
                    uint16_t start_led_idx = cur_pkt * 18U;

                    if (start_led_idx < WS2812_LED_NUM) {
                        uint8_t led_count_in_pkt = data_len / 3U;
                        for (uint8_t i = 0; i < led_count_in_pkt; i++) {
                            uint16_t led_idx = start_led_idx + i;
                            if (led_idx >= WS2812_LED_NUM) {
                                break;
                            }

                            uint8_t r = rx_pkt.payload[i * 3U + 0U];
                            uint8_t g = rx_pkt.payload[i * 3U + 1U];
                            uint8_t b = rx_pkt.payload[i * 3U + 2U];

                            r = (uint16_t)(r * g_light_brightness) / 100U;
                            g = (uint16_t)(g * g_light_brightness) / 100U;
                            b = (uint16_t)(b * g_light_brightness) / 100U;

                            lib_ws2812_set_pixel(led_idx, r, g, b);
                        }
                    }

                    if ((total_pkts > 0U) && (cur_pkt == (total_pkts - 1U))) {
                        g_led_dirty = true;
                    }
                    break;
                }

                default:
                    break;
            }
        }

        if (need_ack) {
            tx_pkt.crc = App_protocol_sum((uint8_t *)&tx_pkt);
            usbd_ep_start_write(PROTOCOL_PKT_ACK_EP, (uint8_t *)&tx_pkt, PROTOCOL_PKT_SIZE);
        }
    }
}
