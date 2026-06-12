#include "App_protocol.h"

#include "App_lighting.h"
#include "App_ota.h"
#include "py32f4xx_hal.h"
#include "App_debug.h"
#include <stdbool.h>
#include <string.h>

#define PROTOCOL_RX_QUEUE_SIZE  8U
#define PROTOCOL_TX_QUEUE_SIZE  8U
#define PROTOCOL_HID_IDLE       0U
#define PROTOCOL_HID_BUSY       1U
#define PROTOCOL_CRC_INDEX      (PROTOCOL_PKT_SIZE - 1U)

#define WS2812_LED_NUM          61U
#define MUSIC_LEDS_PER_PACKET   18U
#define MUSIC_BYTES_PER_LED     3U

/* USB回调只负责校验和入队，业务处理全部放在主循环任务中。 */
static Packet_t g_rx_queue[PROTOCOL_RX_QUEUE_SIZE];
static volatile uint8_t g_rx_head;
static volatile uint8_t g_rx_tail;
static volatile uint8_t g_rx_count;

/*
 * USB驱动在IN传输完成前会继续使用发送缓冲区。
 * 因此应答包必须使用静态存储，不能直接发送栈变量。
 */
static Packet_t g_tx_queue[PROTOCOL_TX_QUEUE_SIZE];
static volatile uint8_t g_tx_head;
static volatile uint8_t g_tx_tail;
static volatile uint8_t g_tx_count;
static bool g_tx_inflight;

/* 运行统计，可在调试器中观察通信质量。 */
volatile uint32_t g_protocol_rx_drop_count;
volatile uint32_t g_protocol_rx_invalid_count;
volatile uint32_t g_protocol_tx_error_count;
volatile uint32_t g_protocol_tx_drop_count;

extern volatile uint8_t custom_hid_state;
extern int usbd_ep_start_write(const uint8_t ep,
                               const uint8_t *data,
                               uint32_t len);

extern uint32_t g_last_music_rx_time;
extern LightMode_t g_backup_light_mode;
extern void App_set_light_config(uint8_t mode,
                                 uint8_t r,
                                 uint8_t g,
                                 uint8_t b,
                                 uint8_t brightness,
                                 uint8_t speed);
extern void App_get_light_config(uint8_t *mode,
                                 uint8_t *r,
                                 uint8_t *g,
                                 uint8_t *b,
                                 uint8_t *brightness,
                                 uint8_t *speed);
extern bool lib_ws2812_set_pixel(uint16_t led_index,
                                 uint8_t r,
                                 uint8_t g,
                                 uint8_t b);

/* 保存并恢复进入临界区之前的中断状态。 */
static uint32_t App_protocol_enter_critical(void)
{
    uint32_t primask = __get_PRIMASK();

    __disable_irq();
    return primask;
}

static void App_protocol_exit_critical(uint32_t primask)
{
    if (primask == 0U) {
        __enable_irq();
    }
}

static bool App_protocol_pop_rx(Packet_t *packet)
{
    uint32_t primask;
    bool available = false;

    if (packet == NULL) {
        return false;
    }

    primask = App_protocol_enter_critical();

    if (g_rx_count > 0U) {
        memcpy(packet, &g_rx_queue[g_rx_tail], sizeof(*packet));
        g_rx_tail = (uint8_t)((g_rx_tail + 1U) % PROTOCOL_RX_QUEUE_SIZE);
        --g_rx_count;
        available = true;
    }

    App_protocol_exit_critical(primask);
    return available;
}

/*
 * 所有0x82端点数据统一进入此队列，包括命令应答和主动冒泡上报。
 * 返回false表示队列已满，调用方可选择稍后重试。
 */
bool App_protocol_send_packet(const Packet_t *packet)
{
    Packet_t queued_packet;
    uint32_t primask;

    if ((packet == NULL) ||
        (packet->data_len > PROTOCOL_PAYLOAD_SIZE)) {
        return false;
    }

    memcpy(&queued_packet, packet, sizeof(queued_packet));
    queued_packet.report_id = PROTOCOL_REPORT_ID;
    queued_packet.crc = App_protocol_sum((uint8_t *)&queued_packet);

    primask = App_protocol_enter_critical();

    if (g_tx_count >= PROTOCOL_TX_QUEUE_SIZE) {
        ++g_protocol_tx_drop_count;
        App_protocol_exit_critical(primask);
        return false;
    }

    memcpy(&g_tx_queue[g_tx_head], &queued_packet, sizeof(queued_packet));
    g_tx_head = (uint8_t)((g_tx_head + 1U) % PROTOCOL_TX_QUEUE_SIZE);
    ++g_tx_count;

    App_protocol_exit_critical(primask);
    return true;
}

/*
 * 校验范围为Byte0到Byte62，Byte63保存校验值。
 * 保持现有协议的8位累加反码算法。
 */
uint8_t App_protocol_sum(uint8_t *buffer)
{
    uint8_t sum = 0U;
    uint32_t index;

    if (buffer == NULL) {
        return 0U;
    }

    for (index = 0U; index < PROTOCOL_CRC_INDEX; ++index) {
        sum = (uint8_t)(sum + buffer[index]);
    }

    return (uint8_t)(0xFFU - sum);
}

/*
 * 自定义HID OUT接收回调调用此函数。
 * 中断上下文中禁止执行Flash、灯光业务和USB IN发送。
 */
void App_protocol_on_rx(uint8_t *buffer, uint32_t length)
{
    uint32_t primask;

    if ((buffer == NULL) || (length != PROTOCOL_PKT_SIZE)) {
        ++g_protocol_rx_invalid_count;
        return;
    }

    if ((buffer[0] != PROTOCOL_REPORT_ID) ||
        (buffer[6] > PROTOCOL_PAYLOAD_SIZE) ||
        (App_protocol_sum(buffer) != buffer[PROTOCOL_CRC_INDEX])) {
        ++g_protocol_rx_invalid_count;
        return;
    }

    primask = App_protocol_enter_critical();

    if (g_rx_count >= PROTOCOL_RX_QUEUE_SIZE) {
        ++g_protocol_rx_drop_count;
        App_protocol_exit_critical(primask);
        return;
    }

    memcpy(&g_rx_queue[g_rx_head], buffer, sizeof(Packet_t));
    g_rx_head = (uint8_t)((g_rx_head + 1U) % PROTOCOL_RX_QUEUE_SIZE);
    ++g_rx_count;

    App_protocol_exit_critical(primask);
}

/* 检查不同OTA命令要求的payload长度。 */
static OtaStatus_t App_protocol_validate_ota(const Packet_t *packet)
{
    switch ((OtaCmdParam_t)packet->cmd_param) {
        case OTA_PARAM_QUERY:
        case OTA_PARAM_ABORT:
        case OTA_PARAM_REBOOT:
            return (packet->data_len == 0U)
                       ? OTA_STATUS_OK
                       : OTA_STATUS_INVALID_LENGTH;

        case OTA_PARAM_BEGIN:
            return (packet->data_len == sizeof(Payload_OtaBegin_t))
                       ? OTA_STATUS_OK
                       : OTA_STATUS_INVALID_LENGTH;

        case OTA_PARAM_DATA:
            /* 4字节offset后面必须携带1到52字节固件数据。 */
            return ((packet->data_len > sizeof(uint32_t)) &&
                    (packet->data_len <= sizeof(Payload_OtaData_t)))
                       ? OTA_STATUS_OK
                       : OTA_STATUS_INVALID_LENGTH;

        case OTA_PARAM_END:
            return (packet->data_len == sizeof(Payload_OtaEnd_t))
                       ? OTA_STATUS_OK
                       : OTA_STATUS_INVALID_LENGTH;

        default:
            return OTA_STATUS_INVALID_COMMAND;
    }
}

/* 校验OTA包并调用独立的App_ota业务层。 */
static void App_protocol_handle_ota(const Packet_t *request,
                                    Packet_t *response_packet)
{
    Payload_OtaResponse_t response;
    OtaStatus_t status;

    memset(&response, 0, sizeof(response));
    response.protocol_version = OTA_PROTOCOL_VERSION;
    response.state = OTA_STATE_IDLE;

    status = App_protocol_validate_ota(request);
    if (status == OTA_STATUS_OK) {
        status = App_ota_handle((OtaCmdParam_t)request->cmd_param,
                                request->payload,
                                request->data_len,
                                &response);
    }

    response.protocol_version = OTA_PROTOCOL_VERSION;
    response.status = (uint8_t)status;

    memset(response_packet->payload, 0, sizeof(response_packet->payload));
    memcpy(response_packet->payload, &response, sizeof(response));
    response_packet->data_len = (uint8_t)sizeof(response);
}

static void App_protocol_handle_light(const Packet_t *request,
                                      Packet_t *response,
                                      bool *need_ack)
{
    uint8_t command = request->cmd_id;
    uint8_t parameter = request->cmd_param;

    switch (command) {
        case CMD_LIGHT_WRITE_CFG:
            if ((parameter == LPARAM_ALL_SET) &&
                (request->data_len == sizeof(Payload_LightAll_t))) {
                Payload_LightAll_t light;

                memcpy(&light, request->payload, sizeof(light));
                if ((light.mode_idx < LIGHT_MODE_MAX) &&
                    (light.brightness <= 100U)) {
                    App_set_light_config(light.mode_idx,
                                         light.r,
                                         light.g,
                                         light.b,
                                         light.brightness,
                                         light.speed);
                }
            } else if ((parameter == LPARAM_MODE_ONLY) &&
                       (request->data_len == 1U)) {
                uint8_t mode = request->payload[0];

                if (mode < LIGHT_MODE_MAX) {
                    App_set_light_config(mode,
                                         g_light_r,
                                         g_light_g,
                                         g_light_b,
                                         g_light_brightness,
                                         g_light_speed);
                }
            }
            break;

        case CMD_LIGHT_READ_CFG:
            if (parameter == LPARAM_ALL_SET) {
                Payload_LightAll_t light = {0};

                App_get_light_config(&light.mode_idx,
                                     &light.r,
                                     &light.g,
                                     &light.b,
                                     &light.brightness,
                                     &light.speed);
                memset(response->payload, 0, sizeof(response->payload));
                memcpy(response->payload, &light, sizeof(light));
                response->data_len = (uint8_t)sizeof(light);
            }
            break;

        case CMD_LIGHT_MUSIC_MAIN:
        {
            uint16_t start_led;
            uint8_t led_count;
            uint8_t index;

            *need_ack = false;

            if (g_light_mode != LIGHT_MODE_MUSIC) {
                g_backup_light_mode = g_light_mode;
                g_light_mode = LIGHT_MODE_MUSIC;
            }

            g_last_music_rx_time = HAL_GetTick();
            start_led = (uint16_t)request->cur_pkt * MUSIC_LEDS_PER_PACKET;
            led_count = request->data_len / MUSIC_BYTES_PER_LED;

            for (index = 0U; index < led_count; ++index) {
                uint16_t led_index = start_led + index;
                uint8_t r;
                uint8_t g;
                uint8_t b;

                if (led_index >= WS2812_LED_NUM) {
                    break;
                }

                r = request->payload[index * MUSIC_BYTES_PER_LED];
                g = request->payload[index * MUSIC_BYTES_PER_LED + 1U];
                b = request->payload[index * MUSIC_BYTES_PER_LED + 2U];

                r = (uint8_t)(((uint16_t)r * g_light_brightness) / 100U);
                g = (uint8_t)(((uint16_t)g * g_light_brightness) / 100U);
                b = (uint8_t)(((uint16_t)b * g_light_brightness) / 100U);

                (void)lib_ws2812_set_pixel(led_index, r, g, b);
            }

            if ((request->total_pkts > 0U) &&
                (request->cur_pkt == (request->total_pkts - 1U))) {
                g_led_dirty = true;
            }
            break;
        }

        default:
            break;
    }
}

static void App_protocol_dispatch(const Packet_t *request,
                                  Packet_t *response,
                                  bool *need_ack)
{
    memcpy(response, request, sizeof(*response));
    
    if (request->cmd_id == CMD_SYS_DEBUG) {
        memset(response->payload, 0, sizeof(response->payload));

        response->data_len = App_debug_handle(
            request->cmd_param,
            response->payload,
            sizeof(response->payload));

        return;
    }

    
    
    
    
    
    
    if (request->cmd_id == CMD_SYS_OTA) {
        App_protocol_handle_ota(request, response);
        return;
    }

    if (((request->cmd_id & 0x7FU) >= 0x20U) &&
        ((request->cmd_id & 0x7FU) <= 0x2FU)) {
        App_protocol_handle_light(request, response, need_ack);
    }
}

/*
 * 尝试发送一个待发送应答。
 * 发送失败时保留g_tx_pending，下一次任务调度继续重试。
 */
static void App_protocol_try_send(void)
{
    int result;
    uint32_t primask;

    /*
     * IN完成回调会把custom_hid_state恢复为IDLE。
     * 此时才从队列移除已完成包，确保驱动使用期间缓冲区有效。
     */
    if (g_tx_inflight && (custom_hid_state == PROTOCOL_HID_IDLE)) {
        primask = App_protocol_enter_critical();
        if (g_tx_count > 0U) {
            g_tx_tail = (uint8_t)((g_tx_tail + 1U) % PROTOCOL_TX_QUEUE_SIZE);
            --g_tx_count;
        }
        g_tx_inflight = false;
        App_protocol_exit_critical(primask);
    }

    if (g_tx_inflight ||
        (g_tx_count == 0U) ||
        (custom_hid_state != PROTOCOL_HID_IDLE)) {
        return;
    }

    /*
     * 先置忙再调用驱动，避免同一调度窗口内其他任务重复提交0x82。
     * IN完成回调负责将custom_hid_state恢复为IDLE。
     */
    custom_hid_state = PROTOCOL_HID_BUSY;
    result = usbd_ep_start_write(PROTOCOL_PKT_ACK_EP,
                                 (const uint8_t *)&g_tx_queue[g_tx_tail],
                                 sizeof(Packet_t));

    if (result == 0) {
        g_tx_inflight = true;
    } else {
        custom_hid_state = PROTOCOL_HID_IDLE;
        ++g_protocol_tx_error_count;
    }
}

/*
 * 主循环持续调用。
 * 同一时刻最多允许一个应答在0x82端点传输，为OTA提供ACK流控。
 */
void App_protocol_task(void)
{
    Packet_t request;
    Packet_t response;
    bool need_ack;

    App_protocol_try_send();

    if (g_tx_count >= PROTOCOL_TX_QUEUE_SIZE) {
        return;
    }

    while (App_protocol_pop_rx(&request)) {
        need_ack = true;
        App_protocol_dispatch(&request, &response, &need_ack);

        if (!need_ack) {
            continue;
        }

        if (!App_protocol_send_packet(&response)) {
            ++g_protocol_tx_error_count;
            return;
        }

        App_protocol_try_send();

        if (g_tx_count >= PROTOCOL_TX_QUEUE_SIZE) {
            return;
        }
    }
}
