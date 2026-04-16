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
 * Project:      Flash Programming Functions for Puya PY32F403xx Flash
 * --------------------------------------------------------------------------- */

/* History:
 *  Version 1.0.0
 *    Initial release
 */

#include "FlashOS.h" /* FlashOS Structures */

typedef volatile unsigned char vu8;
typedef unsigned char u8;
typedef volatile unsigned short vu16;
typedef unsigned short u16;
typedef volatile unsigned long vu32;
typedef unsigned long u32;

/******************  FLASH Keys  **********************************************/

#define HW32_REG(ADDRESS) (*((volatile unsigned int *)(ADDRESS)))

#define HW16_REG(ADDRESS) (*((volatile unsigned short int *)(ADDRESS)))

#define HW8_REG(ADDRESS) (*((volatile unsigned char *)(ADDRESS)))

#define M32(ADDRESS) HW32_REG(ADDRESS)

#define M16(ADDRESS) HW16_REG(ADDRESS)

#define M8(ADDRESS) HW8_REG(ADDRESS)

#define SET_BIT(REG, BIT) ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT) ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT) ((REG) & (BIT))
#define CLEAR_REG(REG) ((REG) = (0x0))
#define WRITE_REG(REG, VAL) ((REG) = (VAL))
#define READ_REG(REG) ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK) WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

int ErasePage(unsigned long adr);

/**
 * @brief FMC Registers
 */
typedef struct
{
    vu32 ACR; /*!<  FLASH_ACR Register,                          Address offset: 0x00  */
    vu32 RESERVED1;
    vu32 KEYR;    /*!<  FLASH_KEYR Register,                         Address offset: 0x08  */
    vu32 OPTKEYR; /*!<  FLASH_OPTKEYR Register,                      Address offset: 0x0C  */
    vu32 SR;      /*!<  FLASH_SR Register,                           Address offset: 0x10  */
    vu32 CR;      /*!<  FLASH_CR Register,                           Address offset: 0x14  */
    vu32 RESERVED2[2];
    vu32 OPTR1;   /*!<  FLASH_OPTR1 Register,                        Address offset: 0x20  */
    vu32 OPTR2;   /*!<  FLASH_OPTR2 Register,                        Address offset: 0x24  */
    vu32 WRPR0;   /*!<  FLASH_WRPR0 Register,                        Address offset: 0x28  */
    vu32 PCROPR0; /*!<  FLASH_PCROPR0 Register,                      Address offset: 0x2C  */
    vu32 SECR0;   /*!<  FLASH_SECR0 Register,                        Address offset: 0x30  */
    vu32 WRPR1;   /*!<  FLASH_WRPR1 Register,                        Address offset: 0x34  */
    vu32 PCROPR1; /*!<  FLASH_PCROPR1 Register,                      Address offset: 0x38  */
    vu32 SECR1;   /*!<  FLASH_SECR1 Register,                        Address offset: 0x3C  */
    vu32 RESERVED3[8];
    vu32 OPTBFB; /*!<  FLASH_OPTBFB Register,                       Address offset: 0x60  */
    vu32 RESERVED4[39];
    vu32 TS0;    /*!<  FLASH_TS0 Register,                          Address offset: 0x100  */
    vu32 TS1;    /*!<  FLASH_TS1 Register,                          Address offset: 0x104  */
    vu32 TS2P;   /*!<  FLASH_TS2P Register,                         Address offset: 0x108  */
    vu32 TPS3;   /*!<  FLASH_TPS3 Register,                         Address offset: 0x10C  */
    vu32 TS3;    /*!<  FLASH_TS3 Register,                          Address offset: 0x110  */
    vu32 ERSTPE; /*!<  FLASH_ERSTPE Register,                       Address offset: 0x114  */
    vu32 PRGTPE; /*!<  FLASH_PRGTPE Register,                       Address offset: 0x118  */
    vu32 PRETPE; /*!<  FLASH_PRETPE Register,                       Address offset: 0x11C  */
} FLASH_TypeDef;

/**
 * @brief IWDG Registers
 */
typedef struct
{
    vu32 KR;  /*!< IWDG KR Register,                   Address offset: 0x0  */
    vu32 PR;  /*!< IWDG PR Register,                   Address offset: 0x4  */
    vu32 RLR; /*!< IWDG RLR Register,                  Address offset: 0x8  */
    vu32 SR;  /*!< IWDG SR Register,                   Address offset: 0xC  */
} IWDG_TypeDef;

/**
 * @brief RCC Registers
 */
typedef struct
{
    vu32 CR;   /*!< RCC CR Register,                    Address offset: 0x00  */
    vu32 CFGR; /*!< RCC CFGR Register,                  Address offset: 0x04  */
    vu32 CIR;  /*!< RCC CIR Register,                   Address offset: 0x08  */
    vu32 RESERVED1[7];
    vu32 AHBRSTR; /*!< RCC AHBRSTR Register,               Address offset: 0x28  */
    vu32 RESERVED2[3];
    vu32 APB1RSTR1; /*!< RCC APB1RSTR1 Register,             Address offset: 0x38  */
    vu32 APB1RSTR2; /*!< RCC APB1RSTR2 Register,             Address offset: 0x3C  */
    vu32 APB2RSTR;  /*!< RCC APB2RSTR Register,              Address offset: 0x40  */
    vu32 RESERVED3;
    vu32 AHBENR; /*!< RCC AHBENR Register,                Address offset: 0x48  */
    vu32 RESERVED4[3];
    vu32 APB1ENR1; /*!< RCC APB1ENR1 Register,              Address offset: 0x58  */
    vu32 APB1ENR2; /*!< RCC APB1ENR2 Register,              Address offset: 0x5C  */
    vu32 APB2ENR;  /*!< RCC APB2ENR Register,               Address offset: 0x60  */
    vu32 RESERVED5;
    vu32 CCIPR; /*!< RCC CCIPR Register,                 Address offset: 0x68  */
    vu32 RESERVED6;
    vu32 BDCR;  /*!< RCC BDCR Register,                  Address offset: 0x70  */
    vu32 CSR;   /*!< RCC CSR Register,                   Address offset: 0x74  */
    vu32 CFGR1; /*!< RCC CFGR1 Register,                 Address offset: 0x78  */
    vu32 CFGR2; /*!< RCC CFGR2 Register,                 Address offset: 0x7C  */
    vu32 CFGR3; /*!< RCC CFGR3 Register,                 Address offset: 0x80  */
} RCC_TypeDef;

/**
 * @brief WWDG Registers
 */
typedef struct
{
    vu32 CR;  /*!< WWDR CR Register,                   Address offset: 0x0  */
    vu32 CFR; /*!< WWDG CFR Register,                  Address offset: 0x4  */
    vu32 SR;  /*!< WWDG SR Register,                   Address offset: 0x8  */
} WWDG_TypeDef;

/*!< Peripheral memory map */
#define FLASH_BASE (0x08000000UL) /*!< FLASH base address */
#define FLASH_END (0x0803FFFFUL)  /*!< FLASH end address */
#define FLASH_SIZE (FLASH_END - FLASH_BASE + 1)
#define FLASH_PAGE_SIZE (0x0000080UL) /*!< FLASH Page Size, 128 Bytes */
#define FLASH_PAGE_NB (FLASH_SIZE / FLASH_PAGE_SIZE)
#define FLASH_SECTOR_SIZE (0x00001000UL) /*!< FLASH Sector Size, 4096(4k) Bytes */
#define FLASH_SECTOR_NB (FLASH_SIZE / FLASH_SECTOR_SIZE)
#define SRAM1_BASE (0x20000000UL) /*!< SRAM1(up to 48 KB) base address */
#define OB_BASE (0x1FFF1B00UL)    /*!< Flash Option Bytes base address */
#define UID_BASE (0x1FFF1A00UL)   /*!< Unique device ID register base address */
#define OTP_BASE (0x1FFF1700UL)

#define FLAHS_SIZE_ADDR (0x1FFF1F60)
#define FLASH_BANK_SIZE ((((M32(FLAHS_SIZE_ADDR) & 0x3) + 1) * 8 * 8 * 1024) / 2)
#define FLASH_BANK_NB (FLASH_SIZE / FLASH_BANK_SIZE)

/* Legacy defines */
#define SRAM_BASE SRAM1_BASE

#define WWDG_BASE (0x40002C00UL)
#define IWDG_BASE (0x40003000UL)
#define RCC_BASE (0x40021000UL)
#define FLASH_R_BASE (0x40022000UL) /*!< Flash registers base address */

#define OB ((OB_TypeDef *)OB_BASE)
#define IWDG ((IWDG_TypeDef *)IWDG_BASE)
#define RCC ((RCC_TypeDef *)RCC_BASE)
#define WWDG ((WWDG_TypeDef *)WWDG_BASE)
#define FLASH ((FLASH_TypeDef *)FLASH_R_BASE)

/********************************* Bit definition for FLASH_ACR register ********************************************/
#define FLASH_ACR_LATENCY_Pos (0U)
#define FLASH_ACR_LATENCY_Msk (0xFUL << FLASH_ACR_LATENCY_Pos) /*!< 0x0000000F */
#define FLASH_ACR_LATENCY FLASH_ACR_LATENCY_Msk                /*!< Latency */
#define FLASH_ACR_LATENCY_0 (0x1UL << FLASH_ACR_LATENCY_Pos)   /*!< 0x00000001 */
#define FLASH_ACR_LATENCY_1 (0x2UL << FLASH_ACR_LATENCY_Pos)   /*!< 0x00000002 */
#define FLASH_ACR_LATENCY_2 (0x4UL << FLASH_ACR_LATENCY_Pos)   /*!< 0x00000004 */
#define FLASH_ACR_LATENCY_3 (0x8UL << FLASH_ACR_LATENCY_Pos)   /*!< 0x00000008 */

/********************************* Bit definition for FLASH_KEYR register *******************************************/
#define FLASH_KEYR_KEY_Pos (0U)
#define FLASH_KEYR_KEY_Msk (0xFFFFFFFFUL << FLASH_KEYR_KEY_Pos) /*!< 0xFFFFFFFF */
#define FLASH_KEYR_KEY FLASH_KEYR_KEY_Msk                       /*!< Flash CR key */

/********************************* Bit definition for FLASH_OPTKEYR register ****************************************/
#define FLASH_OPTKEYR_OPTKEY_Pos (0U)
#define FLASH_OPTKEYR_OPTKEY_Msk (0xFFFFFFFFUL << FLASH_OPTKEYR_OPTKEY_Pos) /*!< 0xFFFFFFFF */
#define FLASH_OPTKEYR_OPTKEY FLASH_OPTKEYR_OPTKEY_Msk                       /*!< Flash Option key */

/********************************* Bit definition for FLASH_SR register *********************************************/
#define FLASH_SR_EOP_Pos (0U)
#define FLASH_SR_EOP_Msk (0x1UL << FLASH_SR_EOP_Pos) /*!< 0x00000001 */
#define FLASH_SR_EOP FLASH_SR_EOP_Msk                /*!< End of operation */
#define FLASH_SR_BSY0_Pos (16U)
#define FLASH_SR_BSY0_Msk (0x1UL << FLASH_SR_BSY0_Pos) /*!< 0x00010000 */
#define FLASH_SR_BSY0 FLASH_SR_BSY0_Msk                /*!< Bank0 Busy */
#define FLASH_SR_BSY1_Pos (17U)
#define FLASH_SR_BSY1_Msk (0x1UL << FLASH_SR_BSY1_Pos) /*!< 0x00020000 */
#define FLASH_SR_BSY1 FLASH_SR_BSY1_Msk                /*!< Bank1 Busy */

/********************************* Bit definition for FLASH_CR register *********************************************/
#define FLASH_CR_PG_Pos (0U)
#define FLASH_CR_PG_Msk (0x1UL << FLASH_CR_PG_Pos) /*!< 0x00000001 */
#define FLASH_CR_PG FLASH_CR_PG_Msk                /*!< Page Program */
#define FLASH_CR_PER_Pos (1U)
#define FLASH_CR_PER_Msk (0x1UL << FLASH_CR_PER_Pos) /*!< 0x00000002 */
#define FLASH_CR_PER FLASH_CR_PER_Msk                /*!< Page Erase */
#define FLASH_CR_MER0_Pos (2U)
#define FLASH_CR_MER0_Msk (0x1UL << FLASH_CR_MER0_Pos) /*!< 0x00000004 */
#define FLASH_CR_MER0 FLASH_CR_MER0_Msk                /*!< Bank 0 Mass Erase */
#define FLASH_CR_MER1_Pos (3U)
#define FLASH_CR_MER1_Msk (0x1UL << FLASH_CR_MER1_Pos) /*!< 0x00000008 */
#define FLASH_CR_MER1 FLASH_CR_MER1_Msk                /*!< Bank 1 Mass Erase */
#define FLASH_CR_SER_Pos (11U)
#define FLASH_CR_SER_Msk (0x1UL << FLASH_CR_SER_Pos) /*!< 0x00000800 */
#define FLASH_CR_SER FLASH_CR_SER_Msk                /*!< Sector Erase */
#define FLASH_CR_OPTSTRT_Pos (17U)
#define FLASH_CR_OPTSTRT_Msk (0x1UL << FLASH_CR_OPTSTRT_Pos) /*!< 0x00020000 */
#define FLASH_CR_OPTSTRT FLASH_CR_OPTSTRT_Msk                /*!< Option bytes Programming Start */
#define FLASH_CR_PGSTRT_Pos (19U)
#define FLASH_CR_PGSTRT_Msk (0x1UL << FLASH_CR_PGSTRT_Pos) /*!< 0x00080000 */
#define FLASH_CR_PGSTRT FLASH_CR_PGSTRT_Msk                /*!< Programming Start */
#define FLASH_CR_EOPIE_Pos (24U)
#define FLASH_CR_EOPIE_Msk (0x1UL << FLASH_CR_EOPIE_Pos) /*!< 0x01000000 */
#define FLASH_CR_EOPIE FLASH_CR_EOPIE_Msk                /*!< End of operation interrupt enable */
#define FLASH_CR_ERRIE_Pos (25U)
#define FLASH_CR_ERRIE_Msk (0x1UL << FLASH_CR_ERRIE_Pos) /*!< 0x02000000 */
#define FLASH_CR_ERRIE FLASH_CR_ERRIE_Msk                /*!< Error interrupt enable */
#define FLASH_CR_OPTLOCK_Pos (30U)
#define FLASH_CR_OPTLOCK_Msk (0x1UL << FLASH_CR_OPTLOCK_Pos) /*!< 0x40000000 */
#define FLASH_CR_OPTLOCK FLASH_CR_OPTLOCK_Msk                /*!< Option Lock */
#define FLASH_CR_LOCK_Pos (31U)
#define FLASH_CR_LOCK_Msk (0x1UL << FLASH_CR_LOCK_Pos) /*!< 0x80000000 */
#define FLASH_CR_LOCK FLASH_CR_LOCK_Msk                /*!< Lock */

#define FLASH_OPTR1_BFB_Pos (11U)
#define FLASH_OPTR1_BFB_Msk (0x1UL << FLASH_OPTR1_BFB_Pos) /*!< 0x00000800 */
#define FLASH_OPTR1_BFB FLASH_OPTR1_BFB_Msk
#define FLASH_OPTR1_IWDG_SW_Pos (12U)
#define FLASH_OPTR1_IWDG_SW_Msk (0x1UL << FLASH_OPTR1_IWDG_SW_Pos) /*!< 0x00001000 */
#define FLASH_OPTR1_IWDG_SW FLASH_OPTR1_IWDG_SW_Msk                /*!< IWDG Software Enable */
#define FLASH_OPTR1_WWDG_SW_Pos (15U)
#define FLASH_OPTR1_WWDG_SW_Msk (0x1UL << FLASH_OPTR1_WWDG_SW_Pos) /*!< 0x00008000 */
#define FLASH_OPTR1_WWDG_SW FLASH_OPTR1_WWDG_SW_Msk

/********************************* Bit definition for FLASH_KEY register ********************************************/
#define FLASH_KEY1_Pos (0U)
#define FLASH_KEY1_Msk (0x45670123UL << FLASH_KEY1_Pos) /*!< 0x45670123 */
#define FLASH_KEY1 FLASH_KEY1_Msk                       /*!< Flash program erase key1 */
#define FLASH_KEY2_Pos (0U)
#define FLASH_KEY2_Msk (0xCDEF89ABUL << FLASH_KEY2_Pos) /*!< 0xCDEF89AB */
#define FLASH_KEY2 FLASH_KEY2_Msk                       /*!< Flash program erase key2: \
used with FLASH_PEKEY1 to unlock the write access to the FPEC. */

#define FLASH_OPTKEY1_Pos (0U)
#define FLASH_OPTKEY1_Msk (0x08192A3BUL << FLASH_OPTKEY1_Pos) /*!< 0x08192A3B */
#define FLASH_OPTKEY1 FLASH_OPTKEY1_Msk                       /*!< Flash option key1 */
#define FLASH_OPTKEY2_Pos (0U)
#define FLASH_OPTKEY2_Msk (0x4C5D6E7FUL << FLASH_OPTKEY2_Pos) /*!< 0x4C5D6E7F */
#define FLASH_OPTKEY2 FLASH_OPTKEY2_Msk                       /*!< Flash option key2: \
used with FLASH_OPTKEY1 to unlock the write access to the option byte block */

/*!< WWDG_CR */
#define WWDG_CR_T_Pos (0U)
#define WWDG_CR_T_Msk (0x7FUL << WWDG_CR_T_Pos) /*!< 0x0000007F */
#define WWDG_CR_T WWDG_CR_T_Msk                 /*!< T[6:0] bits (desc T) */

/*!< WWDG_CFR */
#define WWDG_CFR_W_Pos (0U)
#define WWDG_CFR_W_Msk (0x7FUL << WWDG_CFR_W_Pos) /*!< 0x0000007F */
#define WWDG_CFR_W WWDG_CFR_W_Msk                 /*!< W[6:0] bits (desc W) */

#define WWDG_CFR_WDGTB_Pos (7U)
#define WWDG_CFR_WDGTB_Msk (0x3UL << WWDG_CFR_WDGTB_Pos) /*!< 0x00000180 */
#define WWDG_CFR_WDGTB WWDG_CFR_WDGTB_Msk                /*!< WDGTB[8:7] bits (desc WDGTB) */
#define WWDG_CFR_WDGTB_0 (0x1UL << WWDG_CFR_WDGTB_Pos)   /*!< 0x00000080 */
#define WWDG_CFR_WDGTB_1 (0x2UL << WWDG_CFR_WDGTB_Pos)   /*!< 0x00000100 */

/*
 *  Initialize Flash Programming Functions
 *    Parameter:      adr:  Device Base Address
 *                    clk:  Clock Frequency (Hz)
 *                    fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

int Init(unsigned long adr, unsigned long clk, unsigned long fnc)
{
    FLASH->KEYR = FLASH_KEY1; /* Unlock Flash */
    FLASH->KEYR = FLASH_KEY2;

#ifdef FLASH_OB
    FLASH->OPTKEYR = FLASH_OPTKEY1; /* Unlock Option Bytes */
    FLASH->OPTKEYR = FLASH_OPTKEY2;
#endif

    FLASH->ACR &= ~FLASH_ACR_LATENCY; /* Zero Wait State, no Prefetch */
    FLASH->SR |= FLASH_SR_EOP;        /* Reset FLASH_EOP */
    while ((FLASH->SR & FLASH_SR_BSY0) || (FLASH->SR & FLASH_SR_BSY1))
        ; /* Check FLASH_SR_BSY */

    if ((FLASH->OPTR1 & FLASH_OPTR1_IWDG_SW) == 0x00) /* Test if IWDG is running (IWDG in HW mode) */
    {
        /* Set IWDG time out to ~32.768 second */
        IWDG->KR = 0xAAAA; /* Reload IWDG */
        IWDG->KR = 0x5555; /* Enable write access to IWDG_PR and IWDG_RLR */
        IWDG->PR = 0x06;   /* Set prescaler to 256 */
        IWDG->RLR = 0xFFF; /* Set reload value to 4095 */
    }

    if (FLASH_OPTR1_WWDG_SW != READ_BIT(FLASH->OPTR1, FLASH_OPTR1_WWDG_SW)) /* Test if WWDG is running (WWDG in HW mode) */
    {
        /* Set WWDG time out to maximum */
        SET_BIT(WWDG->CFR, WWDG_CFR_WDGTB); /* Set prescaler to maximum */
        SET_BIT(WWDG->CR, WWDG_CR_T);       /* Reload WWDG */
    }
    return (0);
}

/*
 *  De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

int UnInit(unsigned long fnc)
{
    FLASH->CR |= FLASH_CR_LOCK_Msk; /* Lock Flash */

#ifdef FLASH_OB
    FLASH->CR |= FLASH_CR_OPTLOCK; /* Lock Option Bytes */
#endif

    return (0);
}

/*
 *  Erase complete Flash Memory
 *    Return Value:   0 - OK,  1 - Failed
 */

#ifdef FLASH_MEM
int EraseChip(void)
{
#ifdef FLASH_OTP
    ErasePage(OTP_BASE);
#else
    FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */

    if (READ_BIT(FLASH->OPTR1, FLASH_OPTR1_BFB) != FLASH_OPTR1_BFB)
    {
        FLASH->CR |= FLASH_CR_MER0; /* Mass BANK0 Erase Enabled */
        FLASH->CR |= FLASH_CR_EOPIE;
        M32(FLASH_BASE) = 0xFF; /*BANK0*/
        __asm("DSB");
        while (FLASH->SR & (FLASH_SR_BSY0 | FLASH_SR_BSY1))
        {
            WWDG->CR |= WWDG_CR_T; /* Reload WWDG */
            IWDG->KR = 0xAAAAU;    /* Reload IWDG */
        }

        if (FLASH_SR_EOP != (FLASH->SR & FLASH_SR_EOP)) /* Check for FLASH_SR_EOP */
        {
            FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */
            return (1);                /* Failed */
        }
        FLASH->SR |= FLASH_SR_EOP;     /* Reset FLASH_EOP */
        FLASH->CR &= ~(FLASH_CR_MER0); /* Mass BANK0 Erase Disabled */
        FLASH->CR &= ~FLASH_CR_EOPIE;  /* Reset FLASH_EOPIE */

        FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */

        FLASH->CR |= FLASH_CR_MER1; /* Mass BANK1 Erase Enabled */
        FLASH->CR |= FLASH_CR_EOPIE;
        M32(FLASH_BASE + FLASH_BANK_SIZE) = 0xFF; /*BANK1*/
    }
    else
    {
        FLASH->CR |= FLASH_CR_MER1; /* Mass BANK1 Erase Enabled */
        FLASH->CR |= FLASH_CR_EOPIE;
        M32(FLASH_BASE + FLASH_BANK_SIZE) = 0xFF; /*BANK1*/
        __asm("DSB");
        while (FLASH->SR & (FLASH_SR_BSY0 | FLASH_SR_BSY1))
        {
            WWDG->CR |= WWDG_CR_T; /* Reload WWDG */
            IWDG->KR = 0xAAAAU;    /* Reload IWDG */
        }

        if (FLASH_SR_EOP != (FLASH->SR & FLASH_SR_EOP)) /* Check for FLASH_SR_EOP */
        {
            FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */
            return (1);                /* Failed */
        }

        FLASH->CR &= ~(FLASH_CR_MER0); /* Mass BANK0 Erase Disabled */
        FLASH->CR &= ~FLASH_CR_EOPIE;  /* Reset FLASH_EOPIE */

        FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */

        FLASH->CR |= FLASH_CR_MER0; /* Mass BANK0 Erase Enabled */
        FLASH->CR |= FLASH_CR_EOPIE;
        M32(FLASH_BASE) = 0xFF; /*BANK0*/
    }
    __asm("DSB");
    while (FLASH->SR & (FLASH_SR_BSY0 | FLASH_SR_BSY1))
    {
        WWDG->CR |= WWDG_CR_T; /* Reload WWDG */
        IWDG->KR = 0xAAAAU;    /* Reload IWDG */
    }
    if (FLASH_SR_EOP != (FLASH->SR & FLASH_SR_EOP)) /* Check for FLASH_SR_EOP */
    {
        FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */
        return (1);                /* Failed */
    }

    FLASH->SR |= FLASH_SR_EOP;                     /* Reset FLASH_EOP */
    FLASH->CR &= ~(FLASH_CR_MER0 | FLASH_CR_MER1); /* Mass Erase Disabled */
    FLASH->CR &= ~FLASH_CR_EOPIE;                  /* Reset FLASH_EOPIE */
#endif          /* FLASH_OTP */
    return (0); /* Done */
}
#endif /* FLASH_MEM */

/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */

#ifdef FLASH_MEM
int EraseSector(unsigned long adr)
{
#ifdef FLASH_OTP
    return ErasePage(OTP_BASE); /* Done */
#else
    FLASH->SR |= FLASH_SR_EOP; /* Clear FLASH_EOP */

    FLASH->CR |= FLASH_CR_SER; /* Sector Erase Enabled */
    FLASH->CR |= FLASH_CR_EOPIE;

    M32(adr) = 0xFFFFFFFF; /* Sector Address */

    __asm("DSB");

    while (FLASH->SR & (FLASH_SR_BSY0 | FLASH_SR_BSY1))
    {
        WWDG->CR |= WWDG_CR_T; /* Reload WWDG */
        IWDG->KR = 0xAAAAU;    /* Reload IWDG */
    }

    if (FLASH_SR_EOP != (FLASH->SR & FLASH_SR_EOP)) /* Check for FLASH_SR_EOP */
    {
        FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */
        return (1);                /* Failed */
    }
    FLASH->SR |= FLASH_SR_EOP;    /* Reset FLASH_EOP */
    FLASH->CR &= ~FLASH_CR_SER;   /* Sector Erase Disabled */
    FLASH->CR &= ~FLASH_CR_EOPIE; /* Reset FLASH_EOPIE */

#endif
    return (0); /* Done */
}
#endif

#ifdef FLASH_OB
int EraseSector(unsigned long adr)
{
    /* erase sector is not needed for
       - Flash Option bytes
    */
    return (0);
}
#endif

/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */

#ifdef FLASH_MEM
int ProgramPage(unsigned long adr, unsigned long sz, unsigned char *buf)
{
    sz = (sz + (FLASH_PAGE_SIZE - 1)) & ~(FLASH_PAGE_SIZE - 1); /* Adjust size for 32 Words */

    FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */

    while (sz)
    {
        FLASH->CR |= FLASH_CR_PG; /* Programming Enabled */
        FLASH->CR |= FLASH_CR_EOPIE;

        for (u32 i = 0; i < FLASH_PAGE_SIZE / 4; i++)
        {

            M32(adr + i * 4) = M32(buf + i * 4); /* Program the first word of the Double Word */
            if (i == (FLASH_PAGE_SIZE / 4 - 2))
            {
                FLASH->CR |= FLASH_CR_PGSTRT;
            }
        }
        __asm("DSB");

        while (FLASH->SR & (FLASH_SR_BSY0 | FLASH_SR_BSY1))
        {
            WWDG->CR = WWDG_CR_T;
            IWDG->KR = 0xAAAA; /* Reload IWDG */
        }

        if (FLASH_SR_EOP != (FLASH->SR & FLASH_SR_EOP)) /* Check for FLASH_SR_EOP */
        {
            FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */
            return (1);                /* Failed */
        }
        FLASH->SR |= FLASH_SR_EOP;    /* Reset FLASH_EOP */
        FLASH->CR &= ~FLASH_CR_PG;    /* Programming Disabled */
        FLASH->CR &= ~FLASH_CR_EOPIE; /* Reset FLASH_EOPIE */

        adr += FLASH_PAGE_SIZE; /* Go to next Page */
        buf += FLASH_PAGE_SIZE;
        sz -= FLASH_PAGE_SIZE;
    }
    return (0); /* Done */
}
#endif /* FLASH_MEM */

#ifdef FLASH_OB
int ProgramPage(unsigned long adr, unsigned long sz, unsigned char *buf)
{
    u32 optr1, optr2, optr3, wrpr0, secer0, wrpr1, pcrop0sr, pcrop0er, secer1, pcrop1sr, pcrop1er, optbfbr;

    if (adr != 0x1FFF1B00)
        return 1;

    optr1 = M16(buf + 0x00);
    optr2 = M16(buf + 0x04);
    optr3 = M16(buf + 0x08);
    wrpr0 = M16(buf + 0x10);
    pcrop0sr = M16(buf + 0x14);
    pcrop0er = M16(buf + 0x18);
    secer0 = M16(buf + 0x20);
    wrpr1 = M16(buf + 0x24);
    pcrop1sr = M16(buf + 0x28);
    pcrop1er = M16(buf + 0x2C);
    secer1 = M16(buf + 0x34);
    optbfbr = M16(buf + 0x100);

    FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */

    FLASH->OPTR1 = ((optr1 & 0x0000FFFF) | ((optr2 & 0x0000FFFF) << 16));
    FLASH->OPTR2 = (optr3 & 0x0000FFFF);
    FLASH->WRPR0 = (wrpr0 & 0x0000FFFF);
    FLASH->PCROPR0 = ((pcrop0sr & 0x0000FFFF) | ((pcrop0er & 0x0000FFFF) << 16));
    FLASH->SECR0 = (secer0 & 0x0000FFFF);
    FLASH->PCROPR1 = ((pcrop1sr & 0x0000FFFF) | ((pcrop1er & 0x0000FFFF) << 16));
    FLASH->SECR1 = (secer1 & 0x0000FFFF);
    FLASH->WRPR1 = (wrpr1 & 0x0000FFFF);

    FLASH->OPTBFB = (optbfbr & 0x0000FFFF);

    FLASH->CR |= FLASH_CR_OPTSTRT;
    FLASH->CR |= FLASH_CR_EOPIE;

    M32(0x1FFF1B00) = 0xFFFFFFFF; /*PGM option1*/
    __asm("DSB");
    M32(0x1FFF1C00) = 0xFFFFFFFF; /*PGM option2 OPTBFB*/
    __asm("DSB");

    while (FLASH->SR & (FLASH_SR_BSY0 | FLASH_SR_BSY1))
    {
        WWDG->CR |= WWDG_CR_T;
        IWDG->KR = 0xAAAAU;
    }

    if (FLASH_SR_EOP != (FLASH->SR & FLASH_SR_EOP)) /* Check for FLASH_SR_EOP */
    {
        FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */
        return (1);                /* Failed */
    }
    FLASH->SR |= FLASH_SR_EOP;      /* Reset FLASH_EOP */
    FLASH->CR &= ~FLASH_CR_OPTSTRT; /* Programming Disabled */
    FLASH->CR &= ~FLASH_CR_EOPIE;   /* Reset FLASH_EOPIE */

    return (0); /* Done */
}
#endif /* FLASH_OB */

#ifdef FLASH_MEM
int ErasePage(unsigned long adr)
{
    FLASH->SR |= FLASH_SR_EOP; /* Clear FLASH_EOP */

    FLASH->CR |= FLASH_CR_PER; /* PAGE Erase Enabled */
    FLASH->CR |= FLASH_CR_EOPIE;
    M32(adr) = 0xFF; /* PAGE Address */
    __asm("DSB");

    while (FLASH->SR & (FLASH_SR_BSY0 | FLASH_SR_BSY1))
    {
        WWDG->CR |= WWDG_CR_T;
        IWDG->KR = 0xAAAAU;
    }

    if (FLASH_SR_EOP != (FLASH->SR & FLASH_SR_EOP)) /* Check for FLASH_SR_EOP */
    {
        FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */
        return (1);                /* Failed */
    }
    FLASH->SR |= FLASH_SR_EOP;    /* Reset FLASH_EOP */
    FLASH->CR &= ~FLASH_CR_PER;   /* page Erase Disabled */
    FLASH->CR &= ~FLASH_CR_EOPIE; /* Reset FLASH_EOPIE */

    return (0); /* Done */
}
#endif /* FLASH_MEM */
