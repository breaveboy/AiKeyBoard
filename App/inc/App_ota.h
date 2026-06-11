#ifndef __APP_OTA_H__
#define __APP_OTA_H__

#include <stdbool.h>
#include <stdint.h>

#include "App_protocol.h"
#include "bsp_flash.h"

/* Info区中用于Bootloader识别有效升级镜像的固定标记。 */
#define APP_OTA_INFO_MAGIC          (0x4F544131UL) /* "OTA1" */
#define APP_OTA_INFO_FORMAT_VERSION (0x0001U)

typedef enum {
    APP_OTA_IMAGE_EMPTY = 0U,
    APP_OTA_IMAGE_READY = 1U
} AppOtaImageState_t;

/*
 * 持久化升级信息。
 * 只有下载区固件完成CRC校验后才写入Info区。
 */
#pragma pack(push, 1)
typedef struct {
    uint32_t magic;
    uint16_t format_version;
    uint16_t image_state;
    uint32_t image_size;
    uint32_t image_crc32;
    uint32_t image_version;
    uint8_t version_text[OTA_VERSION_TEXT_SIZE];
    uint32_t metadata_crc32;
} AppOtaImageInfo_t;
#pragma pack(pop)



/* 上电时初始化RAM状态，并读取Info区中已有的升级信息。 */
void App_ota_init(void);

/*
 * OTA业务入口，由App_protocol.c在主循环上下文中调用。
 * 此函数负责状态机、下载区Flash操作和完整镜像校验。
 */
OtaStatus_t App_ota_handle(OtaCmdParam_t command,
                           const uint8_t *payload,
                           uint8_t payload_length,
                           Payload_OtaResponse_t *response);

/*
 * 在主循环中持续调用。
 * REBOOT命令成功应答后，会延迟复位，避免ACK尚未发完就断开USB。
 */
void App_ota_task(void);

/* 读取并验证Info区中的升级镜像信息，供Bootloader后续复用。 */
bool App_ota_read_image_info(AppOtaImageInfo_t *info);

#endif
