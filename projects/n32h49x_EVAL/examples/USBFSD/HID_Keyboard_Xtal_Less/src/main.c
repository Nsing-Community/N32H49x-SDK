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
#include "n32h49x.h"
#include "hw_config.h"
#include "usbfsd_lib.h"
#include "usbfsd_pwr.h"
#include "n32h49x_flash.h"
#include "n32h49x_gpio.h"
#include "n32h49x_rcc.h"

__IO uint8_t PrevXferComplete = 1;
uint8_t key_buffer[8] = {0};
u8* Ep1DataPtr = 0;

bool USB_SET_CONFIGED_FLAG = false;

extern __IO uint8_t bIntPackSOF;

uint8_t LastIntPackSOF = 0;

uint8_t remotewakeup_flag = 0;

/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none.
*\*\return  none.
*\*\
**/
int main(void)
{
    uint32_t system_clock;
    uint16_t i;

    Hardware_Board_Led_Init();
    Hardware_Board_Key_Init();
    Cfg_KeyInterrupt();
    Set_System();
    USBFS_IO_Configure();
    USB_Interrupts_Config();                   

#ifndef USE_USBFSD_XTALLESS
#if defined (N32H49X)
    system_clock = SYSCLK_VALUE_240MHz;
#endif
#else
    system_clock = SystemCoreClock;
#endif /* USE_USBFSD_XTALLESS */
    
    if(USB_Config(system_clock) == SUCCESS)
    {
        USB_Init();

        while (bDeviceState != CONFIGURED)
        {
        }
        while (1)
        {
            if (bDeviceState == SUSPENDED)
            {
                LastIntPackSOF = bIntPackSOF;
            
                for (i = 0; i < 0xffff; i++);
                
                if (LastIntPackSOF != bIntPackSOF)
                {
                    bDeviceState = CONFIGURED;
                }
            }
            
            if (bDeviceState == CONFIGURED)
            {
                if (remotewakeup_flag == 0)
                {
                    if (PrevXferComplete)
                    {
#ifdef BUTTON_KEY1_EVB
                        if (KEY_Press_Status_Read(DOWN_BUTTON_AND_1) == SET)
                        {
                            key_buffer[2] = 0x04;
                        }
#ifdef BUTTON_KEY2_EVB
                        else if (KEY_Press_Status_Read(LEFT_BUTTON_AND_2) == SET)
                        {
                            key_buffer[2] = 0x05;
                        }   
#endif /* BUTTON_KEY2_EVB */ 
#ifdef BUTTON_KEY3_EVB
                        else if (KEY_Press_Status_Read(RIGHT_BUTTON_AND_3) == SET)
                        {
                            key_buffer[2] = 0x06;
                        }
#endif /* BUTTON_KEY3_EVB */ 
                        else
                        {
                            key_buffer[2] = 0;
                        }  
#else

#ifdef BUTTON_KEY2_EVB
                        if (KEY_Press_Status_Read(LEFT_BUTTON_AND_2) == SET)
                        {
                            key_buffer[2] = 0x05;
                        }
#ifdef BUTTON_KEY3_EVB
                        else if (KEY_Press_Status_Read(RIGHT_BUTTON_AND_3) == SET)
                        {
                            key_buffer[2] = 0x06;
                        }
#endif /* BUTTON_KEY3_EVB */ 
                        else
                        {
                            key_buffer[2] = 0;
                        }  
#else

#ifdef BUTTON_KEY3_EVB
                        if (KEY_Press_Status_Read(RIGHT_BUTTON_AND_3) == SET)
                        {
                            key_buffer[2] = 0x06;
                        }
                        else
#endif /* BUTTON_KEY3_EVB */
                        {
                            key_buffer[2] = 0;
                        }
#endif /* BUTTON_KEY2_EVB */     
#endif /* BUTTON_KEY1_EVB */  
                        
                        if (key_buffer[2] != 0)
                        {
                            PrevXferComplete = 0;
                            Ep1DataPtr       = key_buffer;
                            USB_SilWrite(EP1_IN, Ep1DataPtr, 8);
                            _SetEPTxStatus(ENDP1, EP_TX_VALID);
                            
                            while(!PrevXferComplete);
                            
#if defined(BUTTON_KEY1_EVB) && defined(BUTTON_KEY2_EVB) && defined(BUTTON_KEY3_EVB)
                            while((KEY_Press_Status_Read(DOWN_BUTTON_AND_1) == SET) && 
                                  (KEY_Press_Status_Read(LEFT_BUTTON_AND_2) == SET) &&
                                  (KEY_Press_Status_Read(RIGHT_BUTTON_AND_3) == SET));
#elif defined(BUTTON_KEY2_EVB) && defined(BUTTON_KEY3_EVB)
                            while((KEY_Press_Status_Read(LEFT_BUTTON_AND_2) == SET) &&
                                  (KEY_Press_Status_Read(RIGHT_BUTTON_AND_3) == SET));
#elif defined(BUTTON_KEY3_EVB)  
                            while((KEY_Press_Status_Read(RIGHT_BUTTON_AND_3) == SET));
#endif                             
                            
                            key_buffer[2] = 0x00;
                            Ep1DataPtr       = key_buffer;
                            USB_SilWrite(EP1_IN, Ep1DataPtr, 8);
                            _SetEPTxStatus(ENDP1, EP_TX_VALID);
                        }
                    }
                }
                else
                {
                    remotewakeup_flag = 0;

                    key_buffer[2] = 0x05;
                    if (key_buffer[2] != 0)
                    {
                        PrevXferComplete = 0;
                        Ep1DataPtr       = key_buffer;
                        USB_SilWrite(EP1_IN, Ep1DataPtr, 8);
                        _SetEPTxStatus(ENDP1, EP_TX_VALID);
                    }
                    
                    while(!PrevXferComplete);
                    
                    key_buffer[2] = 0x00;
                    Ep1DataPtr = key_buffer;
                    USB_SilWrite(EP1_IN, Ep1DataPtr, 8);
                    _SetEPTxStatus(ENDP1, EP_TX_VALID);
                    
                    while(!PrevXferComplete);
                }
            }
        }
    }
    while(1)
    {
    }
}
