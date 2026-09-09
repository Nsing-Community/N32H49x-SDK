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
#include "n32h49x_rcc.h"
#include "n32h49x_flash.h"
#include "n32h49x_usart.h"
#include <stdio.h>

#define FLASH_BOOTENABLE       ((uint32_t)0x00080000)

/** Main program. **/
int main(void)
{    
    uint32_t Value_temp;
    uint32_t FlashRemap;
    uint32_t UartCmd;
    
    /* USART Init */
    log_init();
    
    /* Show bank mode */
    if(FLASH_GetFlagSTS(FLASH_FLAG_BANKMODE) == SET)
    {
        log_info("FLASH is dual bank mode!\r\n");
    }
    else
    {
        log_info("FLASH is single bank mode!\r\n");
    }

    Value_temp = RCC->BOOTREMAP  & RCC_BOOTREMAP_REMAPSEL;
    if(Value_temp == RCC_REMAP_BFLASH)
    {
        FlashRemap = RCC_REMAP_BFLASH;
        log_info("Flash starts from the forward half, with startup address 0x08000000!\r\n");
    }
    else if(Value_temp == RCC_REMAP_AFLASH)
    {
        FlashRemap = RCC_REMAP_AFLASH;
        log_info("Flash starts from the back half, with startup address 0x08000000!\r\n");
    }
    else
    {
        log_info("No boot remap!\r\n");
        if(((*(uint32_t*)(0x1FFFE010)) & FLASH_BOOTENABLE) ==  FLASH_BOOTENABLE)
        {
            FlashRemap = RCC_REMAP_BFLASH;
            printf("System start from the forward half,with startup address 0x08000000!\r\n");
        }
        else
        {
            FlashRemap = RCC_REMAP_AFLASH;
            printf("System start from the back half,with startup address 0x08000000!\r\n");
        }
    }
    
    while (1)
    {
        /* Loop until UART1 DAT register is not empty */
        while (USART_GetFlagStatus(USART1, USART_FLAG_RXDNE) == RESET)
        {
        }

        UartCmd = USART_ReceiveData(USART1);
        
        if(UartCmd == 0x55) /* Config forward half flash as boot region */
        {
            if(FlashRemap == RCC_REMAP_BFLASH)
            {
                log_info("System is already boot form forward half flash!\r\n");
            }
            else
            {
                Value_temp = FLASH_OB2_FLASHBOOT_SET;
                UartCmd = 0xDD; /* OB need modify */
                log_info("Configure forward half flash as boot region!\r\n");
            }
        }
        else if(UartCmd == 0x66)    /* Config back half flash as boot region */
        {
            if(FlashRemap == RCC_REMAP_AFLASH)
            {
                log_info("System is already boot form back half flash!\r\n");
            }
            else
            {
                Value_temp = FLASH_OB2_FLASHBOOT_CLR;
                UartCmd = 0xDD; /* OB need modify */
                log_info("Configure back half flash as boot bank!\r\n");
            }
        }
        else if(UartCmd == 0x77)    /* Remap to forward half flash  */
        {
            if(FlashRemap == RCC_REMAP_BFLASH)
            {
                log_info("System is already remap to forward half flash!\r\n");
            }
            else
            {
                Value_temp = RCC_REMAP_BFLASH;
                UartCmd = 0xEE; /* Need remap */
                log_info("Remap forward half flash as boot bank!\r\n");
            }
        }
        else if(UartCmd == 0x88)    /* Remap to back half flash  */
        {
            if(FlashRemap == FLASH_BANK2)
            {
                log_info("System is already remap to back half flash!\r\n");
            }
            else
            {
                Value_temp = RCC_REMAP_AFLASH;
                UartCmd = 0xEE; /* Need remap */
                log_info("Remap back half flash as boot bank!\r\n");
            }
        }
        else
        {
            log_info("Invalid command!\r\n");
            UartCmd = 0xFF; /* Invalid command */
        }
        
        if(UartCmd == 0xDD) /* Modify OB */
        {
            FLASH_Unlock();
            FLASH_EraseOB();
            
            /* Configure FLASH to Single BANK mode */
            FLASH_ProgramOB_RRDC(FLASH_OB_RDP1_DISABLE,FLASH_OB_RDP2_DISABLE,FLASH_SINGLE_BANK,CCMSRAM_RST_NERASE);
            
            /* Configure FLASH BANK1 startup */
            FLASH_ProgramOB_U1U2(FLASH_OB_IWDG_SOFTWARE,FLASH_OB_STOP_NORST,FLASH_OB_STDBY_NORST,FLASH_OB_IWDG_STOP_NOFRZ,\
                                 FLASH_OB_IWDG_STDBY_NOFRZ,FLASH_OB_IWDG_SLEEP_NOFRZ,FLASH_OB2_NBOOT0_SET,FLASH_OB2_NBOOT1_SET,\
                                 FLASH_OB2_NSWBOOT0_SET,Value_temp,FLASH_OB2_DAC_SET, BOR_LEVEL_1_6V);

            log_info("System reset !\r\n");
            NVIC_SystemReset();
        }
        else if(UartCmd == 0xEE)    /* Remap */
        {
            RCC_ConfigRemapMode(Value_temp);
            RCC_EnableRemap();
        }
        else
        {
        
        }
    }
}

