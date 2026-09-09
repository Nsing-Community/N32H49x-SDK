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
#include "n32h49x_usart.h"
#include <stdio.h>

/**
*\*\name    main.
*\*\fun     main program.
*\*\param   none
*\*\return  none 
**/
int main(void)
{
    FLASH_STS state_value;
    uint32_t UartCmd;
    
    /* USART Init */
    log_init();
    
    log_info("\nOption Byte configure Test start!\r\n");
    /* Unlocks the FLASH Program Erase Controller */
    FLASH_Unlock();
    /* Unlocks the Option Byte Program Erase Controller */
    Option_Bytes_Unlock();
    /*  Erase Option Byte page */
    state_value = FLASH_EraseOB();
    
    if(state_value == FLASH_EOP)
    {
        /*  Start Option Byte program */
        
        /* Disable read protection L1、L2，config Dual Bank Mode, CCM reset does not erase*/
        state_value = FLASH_ProgramOB_RRDC(FLASH_OB_RDP1_DISABLE,FLASH_OB_RDP2_DISABLE,FLASH_DUAL_BANK,\
                                           CCMSRAM_RST_NERASE);

        if(state_value == FLASH_EOP)
        {
            /* Configure option bytes RDP2, user2 and user3 */
            state_value = FLASH_ProgramOB_U1U2(FLASH_OB_IWDG_SOFTWARE,FLASH_OB_STOP_NORST,FLASH_OB_STDBY_NORST,\
                                                FLASH_OB_IWDG_STOP_NOFRZ,FLASH_OB_IWDG_STDBY_NOFRZ,FLASH_OB_IWDG_SLEEP_NOFRZ,\
                                                FLASH_OB2_NBOOT0_SET,FLASH_OB2_NBOOT1_SET,FLASH_OB2_NSWBOOT0_SET,\
                                                FLASH_OB2_FLASHBOOT_SET,FLASH_OB2_DAC_SET,BOR_LEVEL_1_6V);
        }
        else
        {
            /* no process*/
        }
        
        if(state_value == FLASH_EOP)
        {
            /* Enable writing protection Single Bank: page 32 to 33, Dual Banke: page 64  to 67 */
            state_value = FLASH_EnWriteProtection(FLASH_WRP_NUM16);
        }
        else
        {
            /* no process*/
        }
        
        if(state_value == FLASH_EOP)
        {
            /* Configure option byte datax */
            state_value = FLASH_ProgramOB_Data(0x55,0x66,0x77,0xAA);
        }
        else
        {
            /* no process*/
        }
        
        if(state_value == FLASH_EOP)
        {
            /* Configure option byte CCMSRAM reset without erasing */
            state_value = FLASH_ProgramOB_SRAMECC(SRAM2_ECC_ENABLE,SRAM3_ECC_ENABLE);
        }
        else
        {
            /* no process*/
        }
        if(state_value == FLASH_EOP)
        {
            log_info("Option Byte configure OK!\r\n");
        }
        else
        {
            log_info("Option Byte configure failed!\r\n");
        }
    }
    else
    {
        log_info("Option Byte erase failed!\r\n");
    }
    
    /* Locks the FLASH Program Erase Controller */
    FLASH_Lock();
    /* Locks the Option Byte Program Erase Controller */
    Option_Bytes_Lock();

    while (1)
    {
        /* Loop until UART1 DAT register is not empty */
        while (USART_GetFlagStatus(USART1, USART_FLAG_RXDNE) == RESET)
        {
        }

        UartCmd = USART_ReceiveData(USART1);
        if(UartCmd == 0x55)
        {
            /* Unlocks the FLASH Program Erase Controller */
            FLASH_Unlock();
            /* Unlocks the Option Byte Program Erase Controller */
            Option_Bytes_Unlock();
            /*  Erase Option Byte page */
            state_value = FLASH_EraseOB();
            if(state_value == FLASH_EOP)
            {
                /* Disable read protection L1、L2，config Dual Bank Mode, CCM reset does not erase*/
                state_value = FLASH_ProgramOB_RRDC(FLASH_OB_RDP1_DISABLE,FLASH_OB_RDP2_DISABLE,FLASH_DUAL_BANK,\
                                                   CCMSRAM_RST_NERASE);
                
                if(state_value == FLASH_EOP)
                {
                    log_info("Option byte configured to default value successfully!\r\n");
                }
                else
                {
                    log_info("Option byte configured to default value failed!\r\n");
                }
            }
            else
            {
                log_info("Option byte configured to default value failed!\r\n");
            }
            
            /* Locks the FLASH Program Erase Controller */
            FLASH_Lock();
            /* Locks the Option Byte Program Erase Controller */
            Option_Bytes_Lock();
        }
    }
}

