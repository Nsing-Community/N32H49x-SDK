/**
*     Copyright (c) 2025, Nsing Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nsing Technologies Inc. (Hereinafter 
* referred to as Nsing). This software, and the product of Nsing described herein 
* (Hereinafter referred to as the Product) are owned by Nsing under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     Nsing does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     Nsing reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact Nsing and obtain 
* the latest version of this software before placing orders.

*     Although Nsing has attempted to provide accurate and reliable information, Nsing assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall Nsing be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     Nsing Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify Nsing and hold Nsing 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by Nsing, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     Nsing products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
*\*\file main.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#include "main.h"
#include "log.h"
#include "n32h49x_flash.h"
#include <stdio.h>
/** Run_In_CCM **/

/* CCM SRAM SBus address range for N32MC47x/DP47x (64KB) */
#define CCM_SRAM_BASE   ((uint32_t)0x20070000U)
#define CCM_SRAM_SIZE   ((uint32_t)0x00010000U)   /* 64KB */
#define CCM_SRAM_END    ((uint32_t)0x2007FFFFU)

/* IAR EWARM: section pragma for CCM_CODE (referenced by _Pragma("location=...")) */
#if defined(__ICCARM__)
#pragma section="CCM_CODE"
#endif

/* Backup buffer in regular SRAM. Used to mirror the CCM_CODE bytes before
   CCM_SRAM_Init() wipes CCM, then write them back after re-enabling ECC.
   This avoids having to locate the FLASH load address (which is fragile in
   IAR). 1KB is comfortably larger than the three small CCM functions. */
#define CCM_BACKUP_WORDS    256U
static uint32_t ccm_backup[CCM_BACKUP_WORDS];

/* Cross-compiler section attribute: marks a function to be stored in FLASH
   and executed from CCM SRAM.
   Keil MDK  : requires scatter file ER_CCM region (Run_In_CCM.sct)
   IAR EWARM : _Pragma("location=\"CCM_CODE\""); ICF places CCM_CODE in CCM_region */
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
#define __CCM_FUNC  __attribute__((section("ccmram")))
#elif defined(__ICCARM__)
#define __CCM_FUNC  _Pragma("location=\"CCM_CODE\"")
#elif defined(__GNUC__)
#define __CCM_FUNC  __attribute__((section(".ccmram")))
#else
#define __CCM_FUNC
#endif

/* Three-level nested CCM functions: all stored in FLASH, executed from CCM SRAM.
   Call chain: CCM_WeightedSumOfSquares -> CCM_SumOfSquares -> CCM_Square */

/* Level 3 (leaf): returns x squared */
__CCM_FUNC static uint32_t CCM_Square(uint32_t x)
{
    return x * x;
}

/* Level 2: returns sum of squares from 1 to n; calls CCM_Square */
__CCM_FUNC static uint32_t CCM_SumOfSquares(uint32_t n)
{
    uint32_t i;
    uint32_t result = 0U;

    for (i = 1U; i <= n; i++)
    {
        result += CCM_Square(i);
    }
    return result;
}

/* Level 1 (top): returns sum of i*SumOfSquares(i) for i=1..n; calls CCM_SumOfSquares */
__CCM_FUNC static uint32_t CCM_WeightedSumOfSquares(uint32_t n)
{
    uint32_t i;
    uint32_t result = 0U;

    for (i = 1U; i <= n; i++)
    {
        result += i * CCM_SumOfSquares(i);
    }
    return result;
}

/**
*\*\name    CCM_SRAM_Init.
*\*\fun     Initialize CCM SRAM via RCC one-key initialization.
*\*\        Writes INIDAT to all words in the CCM SRAM range, setting ECC bits.
*\*\        Note: In production, call this from SystemInit() before startup copy.
*\*\param   none
*\*\return  none
**/
static void CCM_SRAM_Init(void)
{
    /* Hardware requirement: write one word of init value to start address
       before configuring the RCC range registers */
    *(__IO uint32_t *)CCM_SRAM_BASE = 0x00000000U;

    /* Step 1: Configure initialization range
       End address must differ from start address */
    RCC->SRAMCFG3 = (uint32_t)CCM_SRAM_BASE;
    RCC->SRAMCFG4 = (uint32_t)(CCM_SRAM_BASE + CCM_SRAM_SIZE - 4U);

    /* Step 2: Configure initialization value */
    RCC->SRAMCFG2 = 0x00000000U;

    /* Step 3: Start one-key initialization */
    RCC->SRAMCFG1 |= RCC_SRAMCFG1_SRINIEN;

    /* Step 4: Wait for initialization complete */
    while (!(RCC->SRAMCFG1 & RCC_SRAMCFG1_SRINIF))
    {
    }

    /* Clear initialization enable */
    RCC->SRAMCFG1 &= ~RCC_SRAMCFG1_SRINIEN;
    
    /* Enable CCM mode */
    CCM_ModeSet(ENABLE);
}

/**
*\*\name    CCM_SRAM_SaveCode.
*\*\fun     Mirror the current CCM SRAM contents (already populated by the
*\*\        startup code) into a regular-SRAM backup buffer. Must be called
*\*\        BEFORE CCM_SRAM_Init() so the function bytes can be restored
*\*\        afterwards. ECC must be disabled first to allow reading any
*\*\        uninitialized CCM cells without triggering an ECC fault.
*\*\param   none
*\*\return  none
**/
static void CCM_SRAM_SaveCode(void)
{
    volatile uint32_t *src = (volatile uint32_t *)CCM_SRAM_BASE;
    uint32_t i;

    for (i = 0U; i < CCM_BACKUP_WORDS; i++)
    {
        ccm_backup[i] = src[i];
    }
}

/**
*\*\name    CCM_SRAM_RestoreCode.
*\*\fun     Write the backed-up bytes back to CCM SRAM. Called AFTER
*\*\        CCM_SRAM_Init() + ECC re-enable so the restored words carry
*\*\        valid ECC bits. Functions become callable again from CCM.
*\*\param   none
*\*\return  none
**/
static void CCM_SRAM_RestoreCode(void)
{
    volatile uint32_t *dst = (volatile uint32_t *)CCM_SRAM_BASE;
    uint32_t i;

    for (i = 0U; i < CCM_BACKUP_WORDS; i++)
    {
        dst[i] = ccm_backup[i];
    }
}

/** Main program. **/
int main(void)
{
    uint32_t addr_square;
    uint32_t addr_sum;
    uint32_t addr_weighted;
    uint32_t result;

    /* USART Init */
    log_init();

    printf("Run_In_CCM Test Start\r\n");

    /* Step 1: Save the CCM functions BEFORE wiping CCM.
       The startup code has already placed them at CCM_SRAM_BASE; we just
       mirror those bytes into a regular-SRAM backup buffer. */
    CCM_SRAM_SaveCode();
    printf("CCM Function Code Saved\r\n");

    /* Step 2: Initialize CCM SRAM via RCC one-key initialization
       Fills all 32KB of CCM SRAM with 0x00000000, setting correct ECC bits.
       This overwrites the CCM function code copied by the startup code */
    CCM_SRAM_Init();
    printf("CCM SRAM Initialized\r\n");
    
    /* Step 3: Write the backed-up bytes back to CCM SRAM so the three
       CCM functions become callable again. The writes happen with ECC
       enabled so the restored words carry valid ECC bits. */
    CCM_SRAM_RestoreCode();
    printf("CCM Function Code Restored\r\n");

    /* Step 4: Verify all three functions execute from CCM SRAM */
    addr_square   = (uint32_t)CCM_Square              & ~1U;
    addr_sum      = (uint32_t)CCM_SumOfSquares         & ~1U;
    addr_weighted = (uint32_t)CCM_WeightedSumOfSquares & ~1U;

    printf("CCM_Square Address              : 0x%08X\r\n", (unsigned int)addr_square);
    printf("CCM_SumOfSquares Address        : 0x%08X\r\n", (unsigned int)addr_sum);
    printf("CCM_WeightedSumOfSquares Address: 0x%08X\r\n", (unsigned int)addr_weighted);
    printf("CCM SRAM Range: 0x%08X ~ 0x%08X\r\n",
           (unsigned int)CCM_SRAM_BASE, (unsigned int)CCM_SRAM_END);

    if ((addr_square   >= CCM_SRAM_BASE) && (addr_square   <= CCM_SRAM_END) &&
        (addr_sum      >= CCM_SRAM_BASE) && (addr_sum      <= CCM_SRAM_END) &&
        (addr_weighted >= CCM_SRAM_BASE) && (addr_weighted <= CCM_SRAM_END))
    {
        printf("All Functions In CCM SRAM [PASS]\r\n");
    }
    else
    {
        printf("Function NOT In CCM SRAM [FAIL]\r\n");
        while (1)
        {
        }
    }

    /* Step 5: Execute the three-level nested CCM call chain and verify the result
       CCM_WeightedSumOfSquares calls CCM_SumOfSquares, which calls CCM_Square
       Expected: sum(i * sum(j^2, j=1..i), i=1..5)
                 = 1*1 + 2*5 + 3*14 + 4*30 + 5*55
                 = 1 + 10 + 42 + 120 + 275 = 448 */
    result = CCM_WeightedSumOfSquares(5U);
    printf("CCM_WeightedSumOfSquares(5) = %u (Expected: 448)\r\n", (unsigned int)result);

    if (result == 448U)
    {
        printf("Run_In_CCM Test Passed\r\n");
    }
    else
    {
        printf("Run_In_CCM Test Failed\r\n");
    }

    printf("Run_In_CCM Test End\r\n");

    while (1)
    {
    }
}

