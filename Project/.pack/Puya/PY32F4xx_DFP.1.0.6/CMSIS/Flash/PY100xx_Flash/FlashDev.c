/* -----------------------------------------------------------------------------
 * Copyright (c) 2014 - 2019 ARM Ltd.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software. Permission is granted to anyone to use this
 * software for any purpose, including commercial applications, and to alter
 * it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *
 * $Date:        2021-7-1
 * $Revision:    V1.0.0
 *
 * Project:      Flash Device Description for Puya PY32F403xx Flash
 * --------------------------------------------------------------------------- */

/* History:
 *  Version 1.0.0
 *    Initial release
 */
#include "FlashOS.h" // FlashOS Structures

#ifdef FLASH_MEM

#ifdef PY100xx_16
struct FlashDevice const FlashDevice = {
    FLASH_DRV_VERS,         // Driver Version, do not modify!
    "Cortex-M4 16kB Flash", // Device Name (16kB)
    ONCHIP,                 // Device Type
    0x08000000,             // Device Start Address
    0x00004000,             // Device Size in Bytes (16kB)
    0x100,                  // Programming Page Size
    0,                      // Reserved, must be 0
    0xFF,                   // Initial Content of Erased Memory
    600,                    // Program Page Timeout 600 mSec
    6000,                   // Erase Sector Timeout 6000 mSec

    // Specify Size and Address of Sectors
    0x800, 0x000000, // Sector Size  2kB (8 sectors)
    SECTOR_END};
#endif // PY100xx_16

#ifdef PY100xx_32
struct FlashDevice const FlashDevice = {
    FLASH_DRV_VERS,         // Driver Version, do not modify!
    "Cortex-M4 32kB Flash", // Device Name (32kB)
    ONCHIP,                 // Device Type
    0x08000000,             // Device Start Address
    0x00008000,             // Device Size in Bytes (32kB)
    0x100,                  // Programming Page Size
    0,                      // Reserved, must be 0
    0xFF,                   // Initial Content of Erased Memory
    600,                    // Program Page Timeout 600 mSec
    6000,                   // Erase Sector Timeout 6000 mSec

    // Specify Size and Address of Sectors
    0x800, 0x000000, // Sector Size  2kB (16 sectors)
    SECTOR_END};
#endif // PY100xx_32

#ifdef PY100xx_64
struct FlashDevice const FlashDevice = {
    FLASH_DRV_VERS,         // Driver Version, do not modify!
    "Cortex-M4 64kB Flash", // Device Name (64kB)
    ONCHIP,                 // Device Type
    0x08000000,             // Device Start Address
    0x00010000,             // Device Size in Bytes (64kB)
    0x100,                  // Programming Page Size
    0,                      // Reserved, must be 0
    0xFF,                   // Initial Content of Erased Memory
    600,                    // Program Page Timeout 600 mSec
    6000,                   // Erase Sector Timeout 6000 mSec

    // Specify Size and Address of Sectors
    0x800, 0x000000, // Sector Size  2kB (32 sectors)
    SECTOR_END};
#endif // PY100xx_64

#ifdef PY100xx_128
struct FlashDevice const FlashDevice = {
    FLASH_DRV_VERS,          // Driver Version, do not modify!
    "Cortex-M4 128kB Flash", // Device Name (128kB)
    ONCHIP,                  // Device Type
    0x08000000,              // Device Start Address
    0x00020000,              // Device Size in Bytes (128kB)
    0x100,                   // Programming Page Size
    0,                       // Reserved, must be 0
    0xFF,                    // Initial Content of Erased Memory
    600,                     // Program Page Timeout 600 mSec
    6000,                    // Erase Sector Timeout 6000 mSec

    // Specify Size and Address of Sectors
    0x800, 0x000000, // Sector Size  2kB (64 sectors)
    SECTOR_END};
#endif // PY100xx_128

#ifdef PY100xx_256
struct FlashDevice const FlashDevice = {
    FLASH_DRV_VERS,          // Driver Version, do not modify!
    "Cortex-M4 256kB Flash", // Device Name (256kB)
    ONCHIP,                  // Device Type
    0x08000000,              // Device Start Address
    0x00040000,              // Device Size in Bytes (256kB)
    0x100,                   // Programming Page Size
    0,                       // Reserved, must be 0
    0xFF,                    // Initial Content of Erased Memory
    600,                     // Program Page Timeout 600 mSec
    6000,                    // Erase Sector Timeout 6000 mSec

    // Specify Size and Address of Sectors
    0x800, 0x000000, // Sector Size  2kB (128 sectors)
    SECTOR_END};
#endif // PY100xx_256

#ifdef PY100xx_384
struct FlashDevice const FlashDevice = {
    FLASH_DRV_VERS,          // Driver Version, do not modify!
    "Cortex-M4 384kB Flash", // Device Name (384kB)
    ONCHIP,                  // Device Type
    0x08000000,              // Device Start Address
    0x00060000,              // Device Size in Bytes (384kB)
    0x100,                   // Programming Page Size
    0,                       // Reserved, must be 0
    0xFF,                    // Initial Content of Erased Memory
    600,                     // Program Page Timeout 600 mSec
    6000,                    // Erase Sector Timeout 6000 mSec

    // Specify Size and Address of Sectors
    0x800, 0x000000, // Sector Size  2kB (192 sectors)
    SECTOR_END};
#endif // PY100xx_384

#endif // FLASH_MEM

#ifdef FLASH_OB
struct FlashDevice const FlashDevice = {
    FLASH_DRV_VERS,            // Driver Version, do not modify!
    "Cortex-M4 Flash Options", // Device Name
    ONCHIP,                    // Device Type
    0x1FFF5000,                // Device Start Address
    0x00000010,                // Device Size in Bytes (16)
    0x10,                      // Programming Page Size
    0,                         // Reserved, must be 0
    0xFF,                      // Initial Content of Erased Memory
    3000,                      // Program Page Timeout 3 Sec
    3000,                      // Erase Sector Timeout 3 Sec

    // Specify Size and Address of Sectors
    0x00010, 0x000000, // Sector Size  16B (1 sectors)
    SECTOR_END};
#endif // FLASH_OB
