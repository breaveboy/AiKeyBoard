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

#include "FlashOS.h"   /* FlashOS Structures */

typedef volatile unsigned char vu8;
typedef unsigned char u8;
typedef volatile unsigned short vu16;
typedef unsigned short u16;
typedef volatile unsigned long vu32;
typedef unsigned long u32;

#define HW32_REG(ADDRESS)     ( * ((volatile unsigned           int * )(ADDRESS)))

#define HW16_REG(ADDRESS)     ( * ((volatile unsigned short     int * )(ADDRESS)))

#define HW8_REG(ADDRESS)      ( * ((volatile unsigned          char * )(ADDRESS)))

#define M32(ADDRESS)          HW32_REG(ADDRESS)

#define M16(ADDRESS)          HW16_REG(ADDRESS)

#define M8(ADDRESS)           HW8_REG(ADDRESS)

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))


/*!< Peripheral memory map */
#define FLASH_BASE            (0x08000000UL)                         /*!< FLASH base address */
#define FLASH_END             (0x0805FFFFUL)                         /*!< FLASH end address */
#define FLASH_SIZE            (FLASH_END - FLASH_BASE + 1)
#define FLASH_PAGE_SIZE       (0x00000100UL)                         /*!< FLASH Page Size, 256 Bytes */
#define FLASH_PAGE_NB         (FLASH_SIZE / FLASH_PAGE_SIZE)
#define FLASH_SECTOR_SIZE     (0x00000800UL)                         /*!< FLASH Sector Size, 2048 Bytes */
#define FLASH_SECTOR_NB       (FLASH_SIZE / FLASH_SECTOR_SIZE)
#define FLASH_BLOCK_SIZE      (0x00008000UL)                         /*!< FLASH Block  Size, 32768 Bytes */
#define FLASH_BLOCK_NB        (FLASH_SIZE / FLASH_BLOCK_SIZE)
#define SRAM_BASE             (0x20000000UL)                         /*!< SRAM base address */
#define SRAM_END              (0x2000FFFFUL)                         /*!< SRAM end address */
#define OB_BASE               (0x1FFF5000UL)                         /*!< Flash Option Bytes base address */
#define UID_BASE              (0x1FFF5800UL)                         /*!< Unique device ID register base address */

#define IWDG_BASE             (0x40003000UL)
#define WWDG_BASE             (0x40002C00UL)
#define RCC_BASE              (0x40021000UL)
#define FLASH_R_BASE          (0x40022000UL)                            /*!< Flash registers base address */


#define RCC             ((RCC_TypeDef*) RCC_BASE)
#define IWDG            ((IWDG_TypeDef *) IWDG_BASE)
#define WWDG            ((WWDG_TypeDef *) WWDG_BASE)
#define FLASH           ((FLASH_TypeDef*) FLASH_R_BASE)

/**
* @brief RCC Registers
*/
typedef struct
{
    vu32 CR;          /*!< RCC clock control register,                Address offset: 0x00 */
    vu32 CFGR;        /*!< RCC clock configuration register,          Address offset: 0x04 */
    vu32 CIR;         /*!< RCC clock interrupt register,              Address offset: 0x08 */
    vu32 APB2RSTR;    /*!< RCC APB2 peripheral reset register,        Address offset: 0x0C */
    vu32 APB1RSTR;    /*!< RCC APB1 peripheral reset register,        Address offset: 0x10 */
    vu32 AHB1ENR;     /*!< RCC AHB1 peripheral clock register,        Address offset: 0x14 */
    vu32 APB2ENR;     /*!< RCC APB2 peripheral clock enable register, Address offset: 0x18 */
    vu32 APB1ENR;     /*!< RCC APB1 peripheral clock enable register, Address offset: 0x1C */
    vu32 BDCR;        /*!< RCC Backup domain control register,        Address offset: 0x20 */
    vu32 CSR;         /*!< RCC clock control & status register,       Address offset: 0x24 */
    vu32 CFGR1;       /*!< RCC clock configuration register 1,        Address offset: 0x28 */
    vu32 AHB1RSTR;    /*!< RCC AHB1 peripheral reset register,        Address offset: 0x2C */
    vu32 AHB2RSTR;    /*!< RCC AHB2 peripheral reset register,        Address offset: 0x30 */
    vu32 AHB2ENR;     /*!< RCC AHB2 peripheral clock register,        Address offset: 0x34 */
    vu32 CFGR2;       /*!< RCC desc CFGR2,                            Address offset: 0x38 */
} RCC_TypeDef;


/**
* @brief FLASH Registers
*/
typedef struct
{
    vu32 ACR;         /*!< FLASH desc ACR,     Address offset: 0x00 */
    u8 RESERVED1[4];      /*!< Reserved, Address offset: 0x04 */
    vu32 KEYR;        /*!< FLASH desc KEYR,    Address offset: 0x08 */
    vu32 OPTKEYR;     /*!< FLASH desc OPTKEYR, Address offset: 0x0C */
    vu32 SR;          /*!< FLASH desc SR,      Address offset: 0x10 */
    vu32 CR;          /*!< FLASH desc CR,      Address offset: 0x14 */
    u8 RESERVED5[8];      /*!< Reserved, Address offset: 0x18 - 0x1F */
    vu32 OPTR;        /*!< FLASH desc OPTR,    Address offset: 0x20 */
    u8 RESERVED7[8];      /*!< Reserved, Address offset: 0x24 - 0x28 */
    vu32 WRPR;        /*!< FLASH desc WRPR,    Address offset: 0x2C */
} FLASH_TypeDef;

/**
* @brief IWDG Registers
*/
typedef struct
{
    vu32 KR;          /*!< IWDG desc KR,  Address offset: 0x00 */
    vu32 PR;          /*!< IWDG desc PR,  Address offset: 0x04 */
    vu32 RLR;         /*!< IWDG desc RLR, Address offset: 0x08 */
    vu32 SR;          /*!< IWDG desc SR,  Address offset: 0x0C */
} IWDG_TypeDef;

/**
* @brief WWDG Registers
*/
typedef struct
{
    vu32 CR;          /*!< WWDG desc CR,  Address offset: 0x00 */
    vu32 CFR;         /*!< WWDG desc CFR, Address offset: 0x04 */
    vu32 SR;          /*!< WWDG desc SR,  Address offset: 0x08 */
} WWDG_TypeDef;

/*!< FLASH_KEYR */
#define FLASH_KEYR_KEY_Pos                        (0U)
#define FLASH_KEYR_KEY_Msk                        (0xFFFFFFFFUL << FLASH_KEYR_KEY_Pos)              /*!< 0xFFFFFFFF */
#define FLASH_KEYR_KEY                            FLASH_KEYR_KEY_Msk                                /*!< KEY[31:0] bits (desc KEY) */

/*!< FLASH_OPTKEYR */
#define FLASH_OPTKEYR_OPTKEY_Pos                  (0U)
#define FLASH_OPTKEYR_OPTKEY_Msk                  (0xFFFFFFFFUL << FLASH_OPTKEYR_OPTKEY_Pos)        /*!< 0xFFFFFFFF */
#define FLASH_OPTKEYR_OPTKEY                      FLASH_OPTKEYR_OPTKEY_Msk                          /*!< OPTKEY[31:0] bits (desc OPTKEY) */

/*!< FLASH_ACR */
#define FLASH_ACR_LATENCY_Pos                     (0U)
#define FLASH_ACR_LATENCY_Msk                     (0xFUL << FLASH_ACR_LATENCY_Pos)                  /*!< 0x0000000F */
#define FLASH_ACR_LATENCY                         FLASH_ACR_LATENCY_Msk                             /*!< LATENCY[3:0] bits (desc LATENCY) */

/*!< FLASH_SR */
#define FLASH_SR_EOP_Pos                          (0U)
#define FLASH_SR_EOP_Msk                          (0x1UL << FLASH_SR_EOP_Pos)                       /*!< 0x00000001 */
#define FLASH_SR_EOP                              FLASH_SR_EOP_Msk                                  /*!< desc EOP */
#define FLASH_SR_WRPERR_Pos                       (4U)
#define FLASH_SR_WRPERR_Msk                       (0x1UL << FLASH_SR_WRPERR_Pos)                    /*!< 0x00000010 */
#define FLASH_SR_WRPERR                           FLASH_SR_WRPERR_Msk                               /*!< desc WRPERR */
#define FLASH_SR_OPTVERR_Pos                      (15U)
#define FLASH_SR_OPTVERR_Msk                      (0x1UL << FLASH_SR_OPTVERR_Pos)                   /*!< 0x00008000 */
#define FLASH_SR_OPTVERR                          FLASH_SR_OPTVERR_Msk                              /*!< desc OPTVERR */
#define FLASH_SR_BSY_Pos                          (16U)
#define FLASH_SR_BSY_Msk                          (0x1UL << FLASH_SR_BSY_Pos)                       /*!< 0x00010000 */
#define FLASH_SR_BSY                              FLASH_SR_BSY_Msk                                  /*!< desc BSY */

/*!< FLASH_CR */
#define FLASH_CR_PG_Pos                           (0U)
#define FLASH_CR_PG_Msk                           (0x1UL << FLASH_CR_PG_Pos)                        /*!< 0x00000001 */
#define FLASH_CR_PG                               FLASH_CR_PG_Msk                                   /*!< desc PG */
#define FLASH_CR_PER_Pos                          (1U)
#define FLASH_CR_PER_Msk                          (0x1UL << FLASH_CR_PER_Pos)                       /*!< 0x00000002 */
#define FLASH_CR_PER                              FLASH_CR_PER_Msk                                  /*!< desc PER */
#define FLASH_CR_MER_Pos                          (2U)
#define FLASH_CR_MER_Msk                          (0x1UL << FLASH_CR_MER_Pos)                       /*!< 0x00000004 */
#define FLASH_CR_MER                              FLASH_CR_MER_Msk                                  /*!< desc MER */
#define FLASH_CR_SER_Pos                          (11U)
#define FLASH_CR_SER_Msk                          (0x1UL << FLASH_CR_SER_Pos)                       /*!< 0x00000800 */
#define FLASH_CR_SER                              FLASH_CR_SER_Msk                                  /*!< desc SER */
#define FLASH_CR_BER_Pos                          (12U)
#define FLASH_CR_BER_Msk                          (0x1UL << FLASH_CR_BER_Pos)                       /*!< 0x00001000 */
#define FLASH_CR_BER                              FLASH_CR_BER_Msk                                  /*!< desc BER */
#define FLASH_CR_OPTSTRT_Pos                      (17U)
#define FLASH_CR_OPTSTRT_Msk                      (0x1UL << FLASH_CR_OPTSTRT_Pos)                   /*!< 0x00020000 */
#define FLASH_CR_OPTSTRT                          FLASH_CR_OPTSTRT_Msk                              /*!< desc OPTSTRT */
#define FLASH_CR_PGSTRT_Pos                       (19U)
#define FLASH_CR_PGSTRT_Msk                       (0x1UL << FLASH_CR_PGSTRT_Pos)                    /*!< 0x00080000 */
#define FLASH_CR_PGSTRT                           FLASH_CR_PGSTRT_Msk                               /*!< desc PGSTRT */
#define FLASH_CR_EOPIE_Pos                        (24U)
#define FLASH_CR_EOPIE_Msk                        (0x1UL << FLASH_CR_EOPIE_Pos)                     /*!< 0x01000000 */
#define FLASH_CR_EOPIE                            FLASH_CR_EOPIE_Msk                                /*!< desc EOPIE */
#define FLASH_CR_ERRIE_Pos                        (25U)
#define FLASH_CR_ERRIE_Msk                        (0x1UL << FLASH_CR_ERRIE_Pos)                     /*!< 0x02000000 */
#define FLASH_CR_ERRIE                            FLASH_CR_ERRIE_Msk                                /*!< desc ERRIE */
#define FLASH_CR_OBL_LAUNCH_Pos                   (27U)
#define FLASH_CR_OBL_LAUNCH_Msk                   (0x1UL << FLASH_CR_OBL_LAUNCH_Pos)                /*!< 0x08000000 */
#define FLASH_CR_OBL_LAUNCH                       FLASH_CR_OBL_LAUNCH_Msk                           /*!< desc OBL_LAUNCH */
#define FLASH_CR_OPTLOCK_Pos                      (30U)
#define FLASH_CR_OPTLOCK_Msk                      (0x1UL << FLASH_CR_OPTLOCK_Pos)                   /*!< 0x40000000 */
#define FLASH_CR_OPTLOCK                          FLASH_CR_OPTLOCK_Msk                              /*!< desc OPTLOCK */
#define FLASH_CR_LOCK_Pos                         (31U)
#define FLASH_CR_LOCK_Msk                         (0x1UL << FLASH_CR_LOCK_Pos)                      /*!< 0x80000000 */
#define FLASH_CR_LOCK                             FLASH_CR_LOCK_Msk                                 /*!< desc LOCK */

#define FLASH_OPTR_IWDG_SW_Pos                    (12U)
#define FLASH_OPTR_IWDG_SW_Msk                    (0x1UL << FLASH_OPTR_IWDG_SW_Pos)                 /*!< 0x00001000 */
#define FLASH_OPTR_IWDG_SW                        FLASH_OPTR_IWDG_SW_Msk                            /*!< desc IWDG_SW */

/******************  FLASH Keys  **********************************************/
#define FLASH_KEY1_Pos                            (0U)
#define FLASH_KEY1_Msk                            (0x45670123UL << FLASH_KEY1_Pos)                  /*!< 0x45670123 */
#define FLASH_KEY1                                FLASH_KEY1_Msk                                    /*!< Flash program erase key1 */
#define FLASH_KEY2_Pos                            (0U)
#define FLASH_KEY2_Msk                            (0xCDEF89ABUL << FLASH_KEY2_Pos)                  /*!< 0xCDEF89AB */
#define FLASH_KEY2                                FLASH_KEY2_Msk                                    /*!< Flash program erase key2: used with FLASH_PEKEY1
to unlock the write access to the FPEC. */

#define FLASH_OPTKEY1_Pos                         (0U)
#define FLASH_OPTKEY1_Msk                         (0x08192A3BUL << FLASH_OPTKEY1_Pos)               /*!< 0x08192A3B */
#define FLASH_OPTKEY1                             FLASH_OPTKEY1_Msk                                 /*!< Flash option key1 */
#define FLASH_OPTKEY2_Pos                         (0U)
#define FLASH_OPTKEY2_Msk                         (0x4C5D6E7FUL << FLASH_OPTKEY2_Pos)               /*!< 0x4C5D6E7F */
#define FLASH_OPTKEY2                             FLASH_OPTKEY2_Msk                                 /*!< Flash option key2: used with FLASH_OPTKEY1 to
unlock the write access to the option byte block */

#define WWDG_CR_T                                 WWDG_CR_T_Msk                                     /*!< T[6:0] bits (desc T) */
#define WWDG_CFR_W                                WWDG_CFR_W_Msk                                    /*!< W[6:0] bits (desc W) */

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

    FLASH->ACR &= ~FLASH_ACR_LATENCY;   /* Zero Wait State, no Prefetch */
    FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */

    while (FLASH->SR & FLASH_SR_BSY);

    if ((FLASH->OPTR & FLASH_OPTR_IWDG_SW) == 0x00) /* Test if IWDG is running (IWDG in HW mode) */
    {
        /* Set IWDG time out to ~32.768 second */
        IWDG->KR = 0xAAAA;                              /* Reload IWDG */
        IWDG->KR = 0x5555; /* Enable write access to IWDG_PR and IWDG_RLR */
        IWDG->PR = 0x06;   /* Set prescaler to 256 */
        IWDG->RLR = 0xFFF; /* Set reload value to 4095 */
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
    FLASH->CR |= FLASH_CR_LOCK; /* Lock Flash */

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
    FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */

    FLASH->CR |= FLASH_CR_MER; /* Mass Erase Enabled */
    FLASH->CR |= FLASH_CR_EOPIE;
    M32(0x08000000) = 0xFF;
    __asm("DSB");

    while (FLASH->SR & FLASH_SR_BSY)
    {
        IWDG->KR = 0xAAAA; /* Reload IWDG */
    }

    if (FLASH_SR_EOP != (FLASH->SR & FLASH_SR_EOP)) /* Check for FLASH_SR_EOP */
    {
        FLASH->SR |= FLASH_SR_EOP;
        return (1); /* Failed */
    }

    FLASH->CR &= ~FLASH_CR_MER;   /* Mass Erase Disabled */
    FLASH->CR &= ~FLASH_CR_EOPIE; /* Reset FLASH_EOPIE */

    return (0); /* Done */
}
#endif

#ifdef FLASH_OB
int EraseChip(void)
{

    /* erase chip is not needed for
       - Flash Option bytes
       - Flash One Time Programmable bytes
    */
    return (0); // Done */
}
#endif

/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */

#ifdef FLASH_MEM
int EraseSector(unsigned long adr)
{

    FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */

    FLASH->CR |= FLASH_CR_SER; /* Sector Erase Enabled */
    FLASH->CR |= FLASH_CR_EOPIE;
    M32(adr) = 0xFF; /* Sector Address */
    __asm("DSB");

    while (FLASH->SR & FLASH_SR_BSY)
    {
        IWDG->KR = 0xAAAA; /* Reload IWDG */
    }


    if (FLASH_SR_EOP != (FLASH->SR & FLASH_SR_EOP)) /* Check for FLASH_SR_EOP */
    {
        FLASH->SR |= FLASH_SR_EOP;
        return (1); /* Failed */
    }

    FLASH->CR &= ~FLASH_CR_SER;   /* Sector Erase Disabled */
    FLASH->CR &= ~FLASH_CR_EOPIE; /* Reset FLASH_EOPIE */

    return (0); /* Done */
}
#endif

#ifdef FLASH_OB
int EraseSector(unsigned long adr)
{
    /* erase sector is not needed for
       - Flash Option bytes
       - Flash One Time Programmable bytes
    */
    return (0); /* Done */
}
#endif


#ifdef FLASH_MEM
int ErasePage(unsigned long adr)
{

    FLASH->SR |= FLASH_SR_EOP; /* Clear FLASH_EOP */

    FLASH->CR |= FLASH_CR_PER; /* PAGE Erase Enabled */
    FLASH->CR |= FLASH_CR_EOPIE;
    M32(adr) = 0xFF; /* PAGE Address */
    __asm("DSB");

    while (FLASH->SR & FLASH_SR_BSY)
    {
        IWDG->KR = 0xAAAA; /* Reload IWDG */
    }

    if (FLASH_SR_EOP != (FLASH->SR & FLASH_SR_EOP))       /* Check for FLASH_SR_EOP */
    {
        FLASH->SR |= FLASH_SR_EOP;                        /* Reset FLASH_EOP */
        return (1);                                       /* Failed */
    }

    FLASH->CR &= ~FLASH_CR_PER;   /* page Erase Disabled */
    FLASH->CR &= ~FLASH_CR_EOPIE; /* Reset FLASH_EOPIE */

    return (0); /* Done */
}
#endif /* FLASH_MEM */

/*
 *  Blank Check Checks if Memory is Blank
 *    Parameter:      adr:  Block Start Address
 *                    sz:   Block Size (in bytes)
 *                    pat:  Block Pattern
 *    Return Value:   0 - OK,  1 - Failed
 */

int BlankCheck(unsigned long adr, unsigned long sz, unsigned char pat)
{
    return (1); /* Always Force Erase */
}

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

        for (u8 i = 0; i < FLASH_PAGE_SIZE / 4; i++)
        {

            M32(adr + i * 4) = *((u32 *)(buf + i * 4)); /* Program the first word of the Double Word */
            if (i == (FLASH_PAGE_SIZE / 4 - 2))
            {
                FLASH->CR |= FLASH_CR_PGSTRT;
            }
        }
        __asm("DSB");

        while (FLASH->SR & FLASH_SR_BSY)
        {
            IWDG->KR = 0xAAAA; /* Reload IWDG */
        }

        if (FLASH_SR_EOP != (FLASH->SR & FLASH_SR_EOP))       /* Check for FLASH_SR_EOP */
        {
            FLASH->SR |= FLASH_SR_EOP;                        /* Reset FLASH_EOP */
            return (1);                                       /* Failed */
        }

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

    u32 optr;
    u32 wrpr;

    optr = *((u32 *)(buf + 0x00));
    wrpr = *((u32 *)(buf + 0x0C));

    FLASH->SR |= FLASH_SR_EOP; /* Reset FLASH_EOP */

    FLASH->OPTR = (optr & 0x0000FFFF); /* Write OPTR values */
    FLASH->WRPR = (wrpr & 0x0000FFFF); /* Write WRPR values */

    FLASH->CR |= FLASH_CR_OPTSTRT;
    FLASH->CR |= FLASH_CR_EOPIE;

    __asm("DSB");

    while (FLASH->SR & FLASH_SR_BSY)
    {
        IWDG->KR = 0xAAAA; /* Reload IWDG */
    }

    if (FLASH_SR_EOP != (FLASH->SR & FLASH_SR_EOP))       /* Check for FLASH_SR_EOP */
    {
        FLASH->SR |= FLASH_SR_EOP;                        /* Reset FLASH_EOP */
        return (1);                                       /* Failed */
    }

    FLASH->CR &= ~FLASH_CR_OPTSTRT; /* Programming Disabled */
    FLASH->CR &= ~FLASH_CR_EOPIE;   /* Reset FLASH_EOPIE */

    return (0); /* Done */
}
#endif /*  FLASH_OB */

/*
 *  Verify Flash Contents
 *    Parameter:      adr:  Start Address
 *                    sz:   Size (in bytes)
 *                    buf:  Data
 *    Return Value:   (adr+sz) - OK, Failed Address
 */

#ifdef FLASH_OB
unsigned long Verify(unsigned long adr, unsigned long sz, unsigned char *buf)
{
    u32 optr;
    u32 wrpr;

    optr = *((u32 *)(buf + 0x00));
    wrpr = *((u32 *)(buf + 0x0C));

    if (M32(adr + 0x00) != optr)
    {
        return (adr + 0x00);
    }

    if (M32(adr + 0x0C) != wrpr)
    {
        return (adr + 0x0C);
    }

    return (adr + sz);
}
#endif /* FLASH_OB */


