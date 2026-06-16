#ifndef __BSP_FLASH_H__
#define __BSP_FLASH_H__

#include <stddef.h>
#include <stdint.h>

#include "py32f4xx_hal.h"

/*
 * PY32F403xC, 256 KiB internal Flash layout:
 *
 * Bootloader : 0x08000000 - 0x08007FFF,  32 KiB
 * APP        : 0x08008000 - 0x08021FFF, 104 KiB
 * Download   : 0x08022000 - 0x0803BFFF, 104 KiB
 * OTA info   : 0x0803C000 - 0x0803FFFF,  16 KiB
 */
#define BSP_FLASH_APP_ADDRESS       (0x08008000UL)
#define BSP_FLASH_APP_SIZE          (0x0001A000UL)
#define BSP_FLASH_DOWNLOAD_ADDRESS  (0x08022000UL)
#define BSP_FLASH_DOWNLOAD_SIZE     (0x0001A000UL)
#define BSP_FLASH_INFO_ADDRESS      (0x0803C000UL)
#define BSP_FLASH_INFO_SIZE         (0x00004000UL)

#define BSP_FLASH_PAGE_SIZE         (0x00000100UL)   //页的大小256
#define BSP_FLASH_SECTOR_SIZE       (0x00000800UL)   //扇区的大小2kb

typedef enum {
    BSP_FLASH_REGION_APP = 0,
    BSP_FLASH_REGION_DOWNLOAD,
    BSP_FLASH_REGION_INFO
} bsp_flash_region_t;

typedef enum {
    BSP_FLASH_OK = 0,     //成功
    BSP_FLASH_ERROR_ARGUMENT, 
    BSP_FLASH_ERROR_ALIGNMENT,
    BSP_FLASH_ERROR_NOT_ERASED,
    BSP_FLASH_ERROR_ERASE,
    BSP_FLASH_ERROR_WRITE,
    BSP_FLASH_ERROR_VERIFY
} bsp_flash_status_t;

/*
 * offset and length are relative to the selected region.
 * Erase offset and length must be aligned to 2 KiB sectors.
 * Write offset must be aligned to a 256-byte page.
 */
bsp_flash_status_t bsp_flash_erase(bsp_flash_region_t region,
                                   uint32_t offset,
                                   size_t length);

bsp_flash_status_t bsp_flash_write(bsp_flash_region_t region,
                                   uint32_t offset,
                                   const void *data,
                                   size_t length);

bsp_flash_status_t bsp_flash_read(bsp_flash_region_t region,
                                  uint32_t offset,
                                  void *data,
                                  size_t length);

#endif
