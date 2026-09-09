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
*\*\file usbfsd_endp.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#include "hw_config.h"
#include "usbfsd_lib.h"
#include "usbfsd_istr.h"

uint8_t Receive_Buffer[2];
extern __IO uint8_t PrevXferComplete;
extern u8* Ep1DataPtr;
extern u8 key_buffer[8];

/**
*\*\name    EP1_OUT_Callback.
*\*\fun     EP1 OUT Callback Routine.
*\*\param   none
*\*\return  none 
**/
void EP1_OUT_Callback(void)
{
Bit_OperateType Led_State;

    /* Read received data (2 bytes) */  
    USB_SilRead(EP1_OUT, Receive_Buffer);

    if (Receive_Buffer[1] == 0)
    {
        Led_State = Bit_RESET;
    }
    else 
    {
        Led_State = Bit_SET;
    }

    switch (Receive_Buffer[0])
    {
    case 1: /* Led 1 */
        if (Led_State != Bit_RESET)
        {
        LED_On(LED1_PORT, LED1_PIN);
        }
        else
        {
        LED_Off(LED1_PORT, LED1_PIN);
        }
        break;
    case 2: /* Led 2 */
        if (Led_State != Bit_RESET)
        {
        LED_On(LED2_PORT, LED2_PIN);
        }
        else
        {
        LED_Off(LED2_PORT, LED2_PIN);
        }
        break;
    case 3: /* Led 3 */
        if (Led_State != Bit_RESET)
        {
            LED_On(LED3_PORT, LED3_PIN);
        }
        else
        {
            LED_Off(LED3_PORT, LED3_PIN);
        }
        break;
    default:
        LED_Off(LED1_PORT, LED1_PIN);
        LED_Off(LED2_PORT, LED2_PIN);
        LED_Off(LED3_PORT, LED3_PIN);
        break;
    }

    /* Enable the receive of data on EP1 */
    SetEPRxStatus(ENDP1, EP_RX_VALID);
}

/**
*\*\name    EP1_IN_Callback.
*\*\fun     EP1 IN Callback Routine.
*\*\param   none
*\*\return  none 
**/
void EP1_IN_Callback(void)
{
    PrevXferComplete = 1;
}

