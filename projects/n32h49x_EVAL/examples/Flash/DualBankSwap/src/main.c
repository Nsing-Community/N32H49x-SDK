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
#include "delay.h"
#include "bsp_eval.h"
#include <stdio.h>

#define FLASH_BOOT_BANK1        ((uint32_t)FLASH_OB2_FLASHBOOT_SET << REG_BIT16_OFFSET)
#define FLASH_BOOT_BANK2        ((uint32_t)FLASH_OB2_FLASHBOOT_CLR << REG_BIT16_OFFSET)
#define FLASH_BOOT_BANK_MASK    (FLASH_BOOT_BANK1)

static void SetModeMark(uint32_t mark);
static void ClrModeMark(void);
static uint32_t GetModeMark(void);
    
/** Main program. **/
int main(void)
{    
    uint32_t Value_temp;
    uint32_t RemapBankNum;
    uint32_t WorkBankNum;
    uint32_t UartCmd;
    uint32_t LoopCnt;
    uint32_t tMark;
    
    /* USART Init */
    log_init();
    
    /* When performing Flash programming operations(write or erase), HSI must be enable*/
    RCC_EnableHsi(ENABLE);
    RCC_WaitHsiStable();
    
    /* User LED Init */
    Hardware_Board_Led_Init();
    
    /* Check current Bank mode, must be in dual Bank mode */
    if(FLASH_GetFlagSTS(FLASH_FLAG_BANKMODE) == SET)
    {
        log_info("\r\nFLASH is dual Bank mode!\r\n");
    }
    else
    {
        log_info("\r\nFLASH is single Bank mode!\r\n");
        log_info("This demo can not be used!\r\n");
        while(1)
        {
            /* Dual Bank swap demo is only used for dual Bank mode */
        }
    }
    
    /* Get current number of boot Bank from option byte */
    if((OBT->USER2_USER & FLASH_BOOT_BANK_MASK) ==  FLASH_BOOT_BANK1)
    {
        WorkBankNum = FLASH_BANK1;
    }
    else
    {
        WorkBankNum = FLASH_BANK2;
    }
    
    /* Get current number of remap Bank from RCC */
    Value_temp = RCC->BOOTREMAP  & RCC_BOOTREMAP_REMAPSEL;
    if(Value_temp == RCC_REMAP_AFLASH)
    {
        RemapBankNum = FLASH_BANK2;
    }
    else
    {
        RemapBankNum = FLASH_BANK1;
    }
    
    /* Get mode mark */
    tMark = GetModeMark();
    
    /* Check current word mode, and config the option byte if nessarry */
    if(RETRY_MARK == tMark)  /* Retry mode */
    {
        log_info("MCU boot from Bank%d,with startup address 0x08000000!\r\n",WorkBankNum);
        log_info("MCU work in Bank%d by Retry mode\r\n",RemapBankNum);
        WorkBankNum = RemapBankNum;
    }
    else if(RELOAD_MARK == tMark) /* Reload mode */
    {
        log_info("MCU boot from Bank%d,with startup address 0x08000000!\r\n",((RemapBankNum == FLASH_BANK1) ? 2 : 1) );
        log_info("MCU work in Bank%d by Reload mode\r\n",RemapBankNum);
        WorkBankNum = RemapBankNum;
        
        if(FLASH_BANK1 == RemapBankNum)
        {
            /* Relaod from Bank2 to Bank1, option byte is already config before remap */
        }
        else if(ConfigBootBank(RemapBankNum) == FLASH_EOP)   /* Relaod from Bank1 to Bank2, option byte must be config after remap */
        {
            log_info("Config Bank2 as boot Bank after remap!\r\n");
        }
        else
        {
            log_info("Boot Bank config fail!\r\n");
        }
    }
    else if(BACKUP_MARK == tMark)
    {
        log_info("MCU boot from Bank%d,with startup address 0x08000000!\r\n",WorkBankNum);
        log_info("MCU work in Bank%d by backup mode\r\n",WorkBankNum);
    }
    else
    {
        log_info("MCU boot from Bank%d,with startup address 0x08000000!\r\n",WorkBankNum);
        log_info("MCU work in Bank%d by normal mode\r\n",WorkBankNum);
    }
    
    /* System start, clear the mark of work mode */
    ClrModeMark();
    
    /* Wait for command */
    LoopCnt = LED_BLINK_DELAY;
    while (1)
    {
        while(1)
        {
            /* If UART1 DAT register is not empty */
            if(USART_GetFlagStatus(USART1, USART_FLAG_RXDNE) != RESET)
            {
                break;
            }
            
            if(LoopCnt >= LED_BLINK_DELAY)
            {
                LoopCnt = 0;
                
                if(FLASH_BANK2 == WorkBankNum)  /*Work in Bank2, LED3 blink*/
                {
                    BANK2_LED_BLINK;
                }
                else                        /*Work in Bank1, LED1 blink*/
                {
                    BANK1_LED_BLINK;
                }
            }
            else
            {
                LoopCnt++;
            }
        }
        
        /* Get the cmd code */
        UartCmd = USART_ReceiveData(USART1);
        
        if(UartCmd == 0x55U) /* Retry */
        {
            if(FLASH_BANK2 == WorkBankNum)
            {
                Value_temp = RCC_REMAP_BFLASH;
                log_info("Remap to Bank1!\r\n");
            }
            else
            {
                Value_temp = RCC_REMAP_AFLASH;
                log_info("Remap to Bank2!\r\n");
            }
            
            /* Set the mark of work mode */
            SetModeMark(RETRY_MARK);
            
            /* Turn on all LED before remap */
            ALL_BANK_LED_ON;
            systick_delay_ms(5);
            
            /* Config remap bank and remap */
            RCC_ConfigRemapMode(Value_temp);
            RCC_EnableRemap();
        }
        else if(UartCmd == 0x66U)    /* Backup */
        {
            if(FLASH_BANK2 == WorkBankNum)
            {
                Value_temp = FLASH_BANK1;
            }
            else
            {
                Value_temp = FLASH_BANK2;
            }
            
            if(ConfigBootBank(Value_temp) == FLASH_EOP)
            {
                /* Set the mark of work mode */
                SetModeMark(BACKUP_MARK);
                
                log_info("Reset MCU by NVIC,reboot to Bank%d!\r\n",Value_temp);
                systick_delay_ms(5);
                
                /* Reset MCU */
                NVIC_SystemReset();
            }
        }
        else if(UartCmd == 0x77U)    /* Reload  */
        {
            if(FLASH_BANK2 == WorkBankNum)
            {
                /* Relaod from Bank2 to Bank1, must config boot bank before remap */
                if(ConfigBootBank(FLASH_BANK1) == FLASH_EOP)
                {
                    Value_temp = RCC_REMAP_BFLASH;
                    log_info("Config Bank1 as boot Bank before remap!\r\n");
                }
                else
                {
                    Value_temp = 0xFFFFFFFFU;
                }
            }
            else
            {
                Value_temp = RCC_REMAP_AFLASH;
            }
            
            if(0xFFFFFFFFU == Value_temp)
            {
                /* Option byte config fail, do nothing*/
            }
            else
            {
                /* Set the mark of work mode */
                SetModeMark(RELOAD_MARK);
                
                /* Turn on all LED before remap */
                 ALL_BANK_LED_ON;
                
                log_info("Remap to Bank%d!\r\n",Value_temp);
                systick_delay_ms(5);
                
                /* Config remap bank and remap */
                RCC_ConfigRemapMode(Value_temp);
                RCC_EnableRemap();
            }
        }
        else
        {
            log_info("Invalid command!\r\n");
            UartCmd = 0xFF; /* Invalid command */
        }
    }
}


FLASH_STS ConfigBootBank(uint32_t BankNum)
{
    uint32_t *pBuf;
    FLASH_STS ConfigSts;
    
    /* Get current value of option byte, store in BKP SRAM */
    pBuf = (uint32_t *)OB_BUF_ADDRESS;
    pBuf[0] = OBT->RDP2_RDP1;
    pBuf[1] = OBT->CCMSRAM_RST_DBANK;
    pBuf[2] = OBT->USER2_USER;
    pBuf[3] = OBT->WRP1_WRP0;
    pBuf[4] = OBT->WRP3_WRP2;
    pBuf[5] = OBT->DATA1_DATA0;
    pBuf[6] = OBT->DATA3_DATA2;
    pBuf[7] = OBT->SRAM3_SRAM2_ECC;
    
    /* Config the Bank number for boot */
    pBuf[2] &= (~FLASH_BOOT_BANK_MASK);
    if(FLASH_BANK2 == BankNum)
    {
        pBuf[2] |= (FLASH_BOOT_BANK2 | 0xFF00FF00U);
    }
    else
    {
        pBuf[2] |= (FLASH_BOOT_BANK1 | 0xFF00FF00U);
    }
    
    /* Reload IWDG */
    IWDG_ReloadKey();
    
    /* Freeze IWDG */
    IWDG_Freeze_Enable(ENABLE);
    
    /* Disable interrupt */
    __set_PRIMASK(1);
    
    /* Unlock Flash */
    FLASH_Unlock();
    
    /* Erase */
    ConfigSts = FLASH_EraseOB();
    
    /* Erase success, write the new value of option byte */
    if(FLASH_EOP == ConfigSts)
    {
        /* Unlock option byte */
        Option_Bytes_Unlock();
        
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        
        /* Enables the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        
        /* Option byte must be programming in the unit of double-word */
        /* Programming the 1st double word at 0x1FFF_E000 */
        OBT->RDP2_RDP1          = pBuf[0];
        OBT->CCMSRAM_RST_DBANK  = pBuf[1];
        
        /* Wait for the programming operation to complete */
        ConfigSts = FLASH_WaitForLastOpt(ProgramTimeout);
        
        /* Disable the Option Bytes Programming operation */
        FLASH->CTRL &= CTRL_Reset_OPTPG;
    }
    
    if(FLASH_EOP == ConfigSts)
    {
        /* Enables the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        
        /* Programming the 2nd double word at 0x1FFF_E010 */
        OBT->USER2_USER         = pBuf[2];
        OBT->RESERVED1[0]       = 0xFFFFFFFFU;
        
        /* Wait for the programming operation to complete */
        ConfigSts = FLASH_WaitForLastOpt(ProgramTimeout);
        
        /* Disable the Option Bytes Programming operation */
        FLASH->CTRL &= CTRL_Reset_OPTPG;
    }
    
    if(FLASH_EOP == ConfigSts)
    {
        /* Enables the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        
        /* Programming the 3rd double word at 0x1FFF_E020 */
        OBT->WRP1_WRP0          = pBuf[3];
        OBT->WRP3_WRP2          = pBuf[4];
        
        /* Wait for the programming operation to complete */
        ConfigSts = FLASH_WaitForLastOpt(ProgramTimeout);
        
        /* Disable the Option Bytes Programming operation */
        FLASH->CTRL &= CTRL_Reset_OPTPG;
    }
    
    if(FLASH_EOP == ConfigSts)
    {
        /* Enables the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        
        /* Programming the 4th double word at 0x1FFF_E030 */
        OBT->DATA1_DATA0        = pBuf[5];
        OBT->DATA3_DATA2        = pBuf[6];
        
        /* Wait for the programming operation to complete */
        ConfigSts = FLASH_WaitForLastOpt(ProgramTimeout);
        
        /* Disable the Option Bytes Programming operation */
        FLASH->CTRL &= CTRL_Reset_OPTPG;
    }
    
    if(FLASH_EOP == ConfigSts)
    {
        /* Enables the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        
        /* Programming the 5th double word at 0x1FFF_E040 */
        OBT->SRAM3_SRAM2_ECC    = pBuf[7];
        OBT->RESERVED4          = 0xFFFFFFFFU;
        
        /* Wait for the programming operation to complete */
        ConfigSts = FLASH_WaitForLastOpt(ProgramTimeout);
        
        /* Disable the Option Bytes Programming operation */
        FLASH->CTRL &= CTRL_Reset_OPTPG;
    }
    
    /* Lock option byte */
    Option_Bytes_Lock();
    
    /* Lock Flash */
    FLASH_Lock();
    
    /* Enable interrupt */
    __set_PRIMASK(0);
    
    /* Unfreeze IWDG */
    IWDG_Freeze_Enable(DISABLE);
    
    /* Reload IWDG */
    IWDG_ReloadKey();
    
    return ConfigSts;
}

static void SetModeMark(uint32_t mark)
{
    uint32_t *pMark;

    pMark = (uint32_t *)MODE_MARK_ADDR;
    
    pMark[0]    = mark;
    pMark[1]    = (~mark);
}

static void ClrModeMark(void)
{
    uint32_t *pMark;

    pMark = (uint32_t *)MODE_MARK_ADDR;
    
    pMark[0]    = 0x55555555U;
    pMark[1]    = 0xAAAAAAAAU;
}

static uint32_t GetModeMark(void)
{
    uint32_t *pMark;
    uint32_t tMode;

    pMark = (uint32_t *)MODE_MARK_ADDR;
    
    tMode = pMark[0];
    if(tMode != (~pMark[1]) )
    {
        tMode = 0xFFFFFFFFU;
    }
    
    return tMode;
}


