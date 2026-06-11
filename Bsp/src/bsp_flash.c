#include "bsp_flash.h"

#include <stdbool.h>
#include <string.h>

#if BSP_FLASH_PAGE_SIZE != FLASH_PAGE_SIZE
#error "Flash page size does not match the PY32 device header"
#endif

#if BSP_FLASH_SECTOR_SIZE != FLASH_SECTOR_SIZE
#error "Flash sector size does not match the PY32 device header"
#endif

typedef struct {
    uint32_t address;
    uint32_t size;
} bsp_flash_partition_t;

static bool bsp_flash_get_partition(bsp_flash_region_t region,
                                    bsp_flash_partition_t *partition)
{
    if (partition == NULL) {
        return false;
    }

    switch (region) {
        case BSP_FLASH_REGION_APP:
            partition->address = BSP_FLASH_APP_ADDRESS;
            partition->size = BSP_FLASH_APP_SIZE;
            return true;

        case BSP_FLASH_REGION_DOWNLOAD:
            partition->address = BSP_FLASH_DOWNLOAD_ADDRESS;
            partition->size = BSP_FLASH_DOWNLOAD_SIZE;
            return true;

        case BSP_FLASH_REGION_INFO:
            partition->address = BSP_FLASH_INFO_ADDRESS;
            partition->size = BSP_FLASH_INFO_SIZE;
            return true;

        default:
            return false;
    }
}

static bool bsp_flash_range_valid(const bsp_flash_partition_t *partition,
                                  uint32_t offset,
                                  size_t length)
{
    if ((partition == NULL) || (length == 0U) ||
        (length > partition->size) || (offset >= partition->size)) {
        return false;
    }

    return length <= (partition->size - offset);
}

static bool bsp_flash_is_blank(uint32_t address, size_t length)
{
    const volatile uint8_t *flash = (const volatile uint8_t *)address;
    size_t index;

    for (index = 0U; index < length; ++index) {
        if (flash[index] != 0xFFU) {
            return false;
        }
    }

    return true;
}

static bool bsp_flash_verify(uint32_t address,
                             const uint8_t *data,
                             size_t length)
{
    const volatile uint8_t *flash = (const volatile uint8_t *)address;
    size_t index;

    for (index = 0U; index < length; ++index) {
        if (flash[index] != data[index]) {
            return false;
        }
    }

    return true;
}

bsp_flash_status_t bsp_flash_erase(bsp_flash_region_t region,
                                   uint32_t offset,
                                   size_t length)
{
    bsp_flash_partition_t partition;
    FLASH_EraseInitTypeDef erase = {0};
    uint32_t erase_error = 0xFFFFFFFFUL;
    uint32_t address;
    HAL_StatusTypeDef hal_status;

    if (!bsp_flash_get_partition(region, &partition) ||
        !bsp_flash_range_valid(&partition, offset, length)) {
        return BSP_FLASH_ERROR_ARGUMENT;
    }

    if (((offset % BSP_FLASH_SECTOR_SIZE) != 0U) ||
        ((length % BSP_FLASH_SECTOR_SIZE) != 0U)) {
        return BSP_FLASH_ERROR_ALIGNMENT;
    }

    address = partition.address + offset;
    erase.TypeErase = FLASH_TYPEERASE_SECTORERASE;
    erase.SectorAddress = address;
    erase.NbSectors = (uint32_t)(length / BSP_FLASH_SECTOR_SIZE);

    if (HAL_FLASH_Unlock() != HAL_OK) {
        return BSP_FLASH_ERROR_ERASE;
    }

    hal_status = HAL_FLASH_Erase(&erase, &erase_error);
    (void)HAL_FLASH_Lock();

    if ((hal_status != HAL_OK) || (erase_error != 0xFFFFFFFFUL)) {
        return BSP_FLASH_ERROR_ERASE;
    }

    if (!bsp_flash_is_blank(address, length)) {
        return BSP_FLASH_ERROR_VERIFY;
    }

    return BSP_FLASH_OK;
}

bsp_flash_status_t bsp_flash_write(bsp_flash_region_t region,
                                   uint32_t offset,
                                   const void *data,
                                   size_t length)
{
    bsp_flash_partition_t partition;
    const uint8_t *source = (const uint8_t *)data;
    uint32_t page[BSP_FLASH_PAGE_SIZE / sizeof(uint32_t)];
    uint32_t address;
    size_t remaining = length;
    bsp_flash_status_t status = BSP_FLASH_OK;

    if ((data == NULL) ||
        !bsp_flash_get_partition(region, &partition) ||
        !bsp_flash_range_valid(&partition, offset, length)) {
        return BSP_FLASH_ERROR_ARGUMENT;
    }

    if ((offset % BSP_FLASH_PAGE_SIZE) != 0U) {
        return BSP_FLASH_ERROR_ALIGNMENT;
    }

    address = partition.address + offset;

    if (HAL_FLASH_Unlock() != HAL_OK) {
        return BSP_FLASH_ERROR_WRITE;
    }

    while (remaining > 0U) {
        size_t page_data_size = remaining;

        if (page_data_size > BSP_FLASH_PAGE_SIZE) {
            page_data_size = BSP_FLASH_PAGE_SIZE;
        }

        if (!bsp_flash_is_blank(address, BSP_FLASH_PAGE_SIZE)) {
            status = BSP_FLASH_ERROR_NOT_ERASED;
            break;
        }

        memset(page, 0xFF, sizeof(page));
        memcpy(page, source, page_data_size);

        if (HAL_FLASH_PageProgram(address, page) != HAL_OK) {
            status = BSP_FLASH_ERROR_WRITE;
            break;
        }

        if (!bsp_flash_verify(address, (const uint8_t *)page, sizeof(page))) {
            status = BSP_FLASH_ERROR_VERIFY;
            break;
        }

        address += BSP_FLASH_PAGE_SIZE;
        source += page_data_size;
        remaining -= page_data_size;
    }

    (void)HAL_FLASH_Lock();
    return status;
}

bsp_flash_status_t bsp_flash_read(bsp_flash_region_t region,
                                  uint32_t offset,
                                  void *data,
                                  size_t length)
{
    bsp_flash_partition_t partition;

    if ((data == NULL) ||
        !bsp_flash_get_partition(region, &partition) ||
        !bsp_flash_range_valid(&partition, offset, length)) {
        return BSP_FLASH_ERROR_ARGUMENT;
    }

    memcpy(data, (const void *)(partition.address + offset), length);
    return BSP_FLASH_OK;
}
