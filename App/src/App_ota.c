#include "App_ota.h"

#include "bsp_flash.h"
#include "py32f4xx_hal.h"

#include <stddef.h>
#include <string.h>

#define APP_OTA_REBOOT_DELAY_MS  200U
#define APP_OTA_CRC_BUFFER_SIZE  128U

typedef struct {
    OtaState_t state; //ota的状态机
    uint32_t image_size; //固件大小
    uint32_t expected_crc32; //上位机提供的固件CRC32
    uint32_t image_version;  
    uint32_t received_size; //接受的固件大小
    uint32_t erase_size;    //擦除的大小
    uint8_t version_text[OTA_VERSION_TEXT_SIZE];  //固件信息
    uint8_t page_buffer[BSP_FLASH_PAGE_SIZE];  //暂存尚未写入 Flash 的固件数据
    uint16_t page_length;   //当前缓存的数据长度
    bool reboot_pending;
    uint32_t reboot_request_tick;
} AppOtaContext_t;

static AppOtaContext_t g_ota;

///////crc校验///////
static uint32_t App_ota_crc32_update(uint32_t crc,const uint8_t *data,size_t length){
    size_t index;
    uint8_t bit;

    for (index = 0U; index < length; ++index) {
        crc ^= data[index];

        for (bit = 0U; bit < 8U; ++bit) {
            if ((crc & 1U) != 0U) {
                crc = (crc >> 1U) ^ 0xEDB88320UL;
            } else {
                crc >>= 1U;
            }
        }
    }

    return crc;
}
///////info区域的校验//////
static uint32_t App_ota_crc32_memory(const void *data, size_t length){
    uint32_t crc = 0xFFFFFFFFUL;

    crc = App_ota_crc32_update(crc, (const uint8_t *)data, length);
    return crc ^ 0xFFFFFFFFUL;
}
//////固件区域的校验//////
static bool App_ota_crc32_download(uint32_t length, uint32_t *result){
    uint8_t buffer[APP_OTA_CRC_BUFFER_SIZE];
    uint32_t offset = 0U;
    uint32_t crc = 0xFFFFFFFFUL;

    if ((result == NULL) || (length == 0U) ||
        (length > BSP_FLASH_DOWNLOAD_SIZE)) {
        return false;
    }

    while (offset < length) {
        size_t block_size = length - offset;

        if (block_size > sizeof(buffer)) {
            block_size = sizeof(buffer);
        }

        if (bsp_flash_read(BSP_FLASH_REGION_DOWNLOAD,
                           offset,
                           buffer,
                           block_size) != BSP_FLASH_OK) {
            return false;
        }

        crc = App_ota_crc32_update(crc, buffer, block_size);
        offset += (uint32_t)block_size;
    }

    *result = crc ^ 0xFFFFFFFFUL;
    return true;
}

//////ota的重置//////////
static void App_ota_reset_context(void){
    memset(&g_ota, 0, sizeof(g_ota));
    g_ota.state = OTA_STATE_IDLE;
}



/////向上对齐///////////
static uint32_t App_ota_align_up(uint32_t value, uint32_t alignment){
    return (value + alignment - 1U) & ~(alignment - 1U);
}
////////回复上位机////////
static void App_ota_fill_response(Payload_OtaResponse_t *response)
{
    response->protocol_version = OTA_PROTOCOL_VERSION;
    response->state = (uint8_t)g_ota.state;
    response->reserved = 0U;
    response->max_image_size = BSP_FLASH_DOWNLOAD_SIZE;
    response->received_size = g_ota.received_size;
    response->image_crc32 = g_ota.expected_crc32;
    response->image_version = g_ota.image_version;
}
/////////检测info是否是无效的信息
static bool App_ota_validate_info(const AppOtaImageInfo_t *info){
    uint32_t crc;

    if ((info == NULL) ||
        (info->magic != APP_OTA_INFO_MAGIC) ||
        (info->format_version != APP_OTA_INFO_FORMAT_VERSION) ||
        (info->image_state != APP_OTA_IMAGE_READY) ||
        (info->image_size == 0U) ||
        (info->image_size > BSP_FLASH_DOWNLOAD_SIZE)) {
        return false;
    }

    crc = App_ota_crc32_memory(info,offsetof(AppOtaImageInfo_t, metadata_crc32));

    return crc == info->metadata_crc32;
}


//读取info中的信息
bool App_ota_read_image_info(AppOtaImageInfo_t *info)
{
    if (info == NULL) {
        return false;
    }

    if (bsp_flash_read(BSP_FLASH_REGION_INFO,
                       0U,
                       info,
                       sizeof(*info)) != BSP_FLASH_OK) {
        return false;
    }

    return App_ota_validate_info(info);
}
/////清除info区域的信息
static bool App_ota_clear_image_info(void)
{
    return bsp_flash_erase(BSP_FLASH_REGION_INFO,0U, BSP_FLASH_SECTOR_SIZE) == BSP_FLASH_OK;
}
/////写入info区域的信息
static bool App_ota_write_image_info(void)
{
    AppOtaImageInfo_t info; 

    memset(&info, 0, sizeof(info));
    info.magic = APP_OTA_INFO_MAGIC;
    info.format_version = APP_OTA_INFO_FORMAT_VERSION;
    info.image_state = APP_OTA_IMAGE_READY;
    info.image_size = g_ota.image_size;
    info.image_crc32 = g_ota.expected_crc32;
    info.image_version = g_ota.image_version;
    memcpy(info.version_text, g_ota.version_text, sizeof(info.version_text));
    info.metadata_crc32 = App_ota_crc32_memory(&info,offsetof(AppOtaImageInfo_t, metadata_crc32));

    if (!App_ota_clear_image_info()) {
        return false;
    }
    return bsp_flash_write(BSP_FLASH_REGION_INFO, 0U, &info,sizeof(info)) == BSP_FLASH_OK;
}
//////ota进行初始化/////////////
void App_ota_init(void){
    AppOtaImageInfo_t info;

    App_ota_reset_context();

    /*
     * READY记录表示下载区已有完整镜像。
     * 上电后保留该状态，便于上位机QUERY获得真实状态。
     */
    if (App_ota_read_image_info(&info)) {
        g_ota.state = OTA_STATE_READY;
        g_ota.image_size = info.image_size;
        g_ota.expected_crc32 = info.image_crc32;
        g_ota.image_version = info.image_version;
        g_ota.received_size = info.image_size;
        memcpy(g_ota.version_text,info.version_text,sizeof(g_ota.version_text));
    }
}

static OtaStatus_t App_ota_begin(const uint8_t *payload){
    Payload_OtaBegin_t begin;
    uint32_t erase_size;

    if (g_ota.state == OTA_STATE_VERIFYING) {
        return OTA_STATUS_BUSY;
    }
    //数据包复制到begin包中
    memcpy(&begin, payload, sizeof(begin));

    if ((begin.image_size == 0U) ||
        (begin.image_size > BSP_FLASH_DOWNLOAD_SIZE)) {
        return OTA_STATUS_INVALID_IMAGE;
    }
    //计算擦除大小
    erase_size = App_ota_align_up(begin.image_size,
                                  BSP_FLASH_SECTOR_SIZE);

    /*
     * 先清除旧READY记录，再擦除下载区。
     * 任何中途断电都不会让Bootloader误认为新镜像有效。
     */
    if (!App_ota_clear_image_info()) {
        App_ota_reset_context();
        g_ota.state = OTA_STATE_ERROR;
        return OTA_STATUS_FLASH_ERROR;
    }

    if (bsp_flash_erase(BSP_FLASH_REGION_DOWNLOAD,0U, erase_size) != BSP_FLASH_OK) {
        App_ota_reset_context();
        g_ota.state = OTA_STATE_ERROR;
        return OTA_STATUS_FLASH_ERROR;
    }

    App_ota_reset_context();
    g_ota.state = OTA_STATE_RECEIVING;
    g_ota.image_size = begin.image_size;
    g_ota.expected_crc32 = begin.image_crc32;
    g_ota.image_version = begin.image_version;
    g_ota.erase_size = erase_size;
    memcpy(g_ota.version_text, begin.version_text, sizeof(g_ota.version_text));
    return OTA_STATUS_OK;
}
//////把ram的page_buffer放入flash下载区 
static OtaStatus_t App_ota_flush_page(void)
{
    uint32_t page_offset;

    if (g_ota.page_length == 0U) {
        return OTA_STATUS_OK;
    }

    page_offset = g_ota.received_size - g_ota.page_length;

    if (bsp_flash_write(BSP_FLASH_REGION_DOWNLOAD,page_offset,g_ota.page_buffer,g_ota.page_length) != BSP_FLASH_OK) {
        g_ota.state = OTA_STATE_ERROR;
        return OTA_STATUS_FLASH_ERROR;
    }

    memset(g_ota.page_buffer, 0xFF, sizeof(g_ota.page_buffer));
    g_ota.page_length = 0U;
    return OTA_STATUS_OK;
}




static OtaStatus_t App_ota_data(const uint8_t *payload, uint8_t payload_length){
    uint32_t packet_offset;  //分包偏移值
    const uint8_t *packet_data; //分包数据位置的指针
    uint8_t data_length;     //分包的实际数据大小值

    if (g_ota.state != OTA_STATE_RECEIVING) {
        return OTA_STATUS_INVALID_STATE;
    }

    memcpy(&packet_offset, payload, sizeof(packet_offset));  //获取偏移值
    packet_data = payload + sizeof(packet_offset);    //数据包指针
    data_length = (uint8_t)(payload_length - sizeof(packet_offset)); //数据大小

    if (packet_offset != g_ota.received_size) {
        return OTA_STATUS_OFFSET_MISMATCH;
    }

    if ((uint32_t)data_length >(g_ota.image_size - g_ota.received_size)) {
        return OTA_STATUS_INVALID_IMAGE;
    }

    while (data_length > 0U) {
        uint16_t free_space =(uint16_t)(BSP_FLASH_PAGE_SIZE - g_ota.page_length);  //256的页里面的剩余空间
        uint16_t copy_length = data_length;  

        if (copy_length > free_space) {
            copy_length = free_space;
        }

        memcpy(&g_ota.page_buffer[g_ota.page_length], packet_data, copy_length);   //将数据复制到page_buffer缓冲区中

        g_ota.page_length += copy_length;   //page_length是使用的大小
        g_ota.received_size += copy_length; //管整个固件已经收了多少
        packet_data += copy_length;   //当前包还没处理的数据位置
        data_length = (uint8_t)(data_length - copy_length);

        if (g_ota.page_length == BSP_FLASH_PAGE_SIZE) {
            OtaStatus_t status = App_ota_flush_page();

            if (status != OTA_STATUS_OK) {
                return status;
            }
        }
    }

    return OTA_STATUS_OK;
}

static OtaStatus_t App_ota_end(const uint8_t *payload)
{
    Payload_OtaEnd_t end;
    uint32_t actual_crc32;
    OtaStatus_t status;

    if (g_ota.state != OTA_STATE_RECEIVING) {
        return OTA_STATUS_INVALID_STATE;
    }

    memcpy(&end, payload, sizeof(end));

    if ((end.image_size != g_ota.image_size) ||
        (end.image_crc32 != g_ota.expected_crc32) ||
        (g_ota.received_size != g_ota.image_size)) {
        return OTA_STATUS_INVALID_IMAGE;
    }

    status = App_ota_flush_page();
    if (status != OTA_STATUS_OK) {
        return status;
    }

    g_ota.state = OTA_STATE_VERIFYING;

    if (!App_ota_crc32_download(g_ota.image_size, &actual_crc32)) {
        g_ota.state = OTA_STATE_ERROR;
        return OTA_STATUS_FLASH_ERROR;
    }

    if (actual_crc32 != g_ota.expected_crc32) {
        g_ota.state = OTA_STATE_ERROR;
        return OTA_STATUS_CRC_ERROR;
    }

    if (!App_ota_write_image_info()) {
        g_ota.state = OTA_STATE_ERROR;
        return OTA_STATUS_FLASH_ERROR;
    }

    g_ota.state = OTA_STATE_READY;
    return OTA_STATUS_OK;
}

static OtaStatus_t App_ota_abort(void)
{
    if (!App_ota_clear_image_info()) {
        g_ota.state = OTA_STATE_ERROR;
        return OTA_STATUS_FLASH_ERROR;
    }

    App_ota_reset_context();
    return OTA_STATUS_OK;
}

static OtaStatus_t App_ota_request_reboot(void)
{
    if (g_ota.state != OTA_STATE_READY) {
        return OTA_STATUS_INVALID_STATE;
    }

    g_ota.reboot_pending = true;
    g_ota.reboot_request_tick = HAL_GetTick();
    return OTA_STATUS_OK;
}

OtaStatus_t App_ota_handle(OtaCmdParam_t command,
                           const uint8_t *payload,
                           uint8_t payload_length,
                           Payload_OtaResponse_t *response)
{
    OtaStatus_t status;

    if (response == NULL) {
        return OTA_STATUS_INTERNAL_ERROR;
    }

    switch (command) {
        case OTA_PARAM_QUERY:
            if (payload_length != 0U) {
                status = OTA_STATUS_INVALID_LENGTH;
                break;
            }
            status = OTA_STATUS_OK;
            break;

        case OTA_PARAM_BEGIN:
            if ((payload == NULL) ||
                (payload_length != sizeof(Payload_OtaBegin_t))) {
                status = OTA_STATUS_INVALID_LENGTH;
                break;
            }
            status = App_ota_begin(payload);
            break;

        case OTA_PARAM_DATA:
            if ((payload == NULL) ||
                (payload_length <= sizeof(uint32_t)) ||
                (payload_length > sizeof(Payload_OtaData_t))) {
                status = OTA_STATUS_INVALID_LENGTH;
                break;
            }
            status = App_ota_data(payload, payload_length);
            break;

        case OTA_PARAM_END:
            if ((payload == NULL) ||
                (payload_length != sizeof(Payload_OtaEnd_t))) {
                status = OTA_STATUS_INVALID_LENGTH;
                break;
            }
            status = App_ota_end(payload);
            break;

        case OTA_PARAM_ABORT:
            if (payload_length != 0U) {
                status = OTA_STATUS_INVALID_LENGTH;
                break;
            }
            status = App_ota_abort();
            break;

        case OTA_PARAM_REBOOT:
            if (payload_length != 0U) {
                status = OTA_STATUS_INVALID_LENGTH;
                break;
            }
            status = App_ota_request_reboot();
            break;

        default:
            status = OTA_STATUS_INVALID_COMMAND;
            break;
    }

    App_ota_fill_response(response);
    response->status = (uint8_t)status;
    return status;
}

void App_ota_task(void)
{
    if (!g_ota.reboot_pending) {
        return;
    }

    if ((HAL_GetTick() - g_ota.reboot_request_tick) <
        APP_OTA_REBOOT_DELAY_MS) {
        return;
    }

    g_ota.reboot_pending = false;
    __disable_irq();
    NVIC_SystemReset();
}
