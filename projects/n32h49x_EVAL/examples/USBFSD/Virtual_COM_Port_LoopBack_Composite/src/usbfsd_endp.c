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

/* Includes ------------------------------------------------------------------*/
#include "usbfsd_lib.h"
#include "usbfsd_desc.h"
#include "usbfsd_mem.h"
#include "hw_config.h"
#include "usbfsd_istr.h"
#include "usbfsd_pwr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Interval between sending IN packets in frame number (1 frame = 1ms) */
#define VCOMPORT_IN_FRAME_INTERVAL             5

extern __IO uint32_t packet_sent;
extern __IO uint32_t packet_receive;
extern __IO uint8_t Receive_Buffer[CDC_DEVICE_NUM][64];
__IO uint16_t Receive_length[CDC_DEVICE_NUM];


static void EP_IN_Callback(uint8_t bEpNum)
{
	packet_sent |= (1 << (bEpNum - 1));
}

static void EP_OUT_Callback(uint8_t bEpNum, uint16_t wPMABufAddr)
{
    packet_receive |= (1 << (bEpNum - 1));
	
	Receive_length[bEpNum - 1] = USB_GetEpRxCnt(bEpNum);
	
    USB_CopyPMAToUserBuf((unsigned char*)Receive_Buffer[bEpNum - 1], wPMABufAddr, Receive_length[bEpNum - 1]);
}

/**
*\*\name    EP1_IN_Callback.
*\*\fun     EP1 IN Callback Routine.
*\*\param   none
*\*\return  none 
**/
void EP1_IN_Callback (void)
{
	EP_IN_Callback(ENDP1);
}

/**
*\*\name    EP1_OUT_Callback.
*\*\fun     EP1 OUT Callback Routine.
*\*\param   none
*\*\return  none 
**/
void EP1_OUT_Callback(void)
{
	EP_OUT_Callback(ENDP1, ENDP1_RXADDR);
}

/**
*\*\name    EP2_IN_Callback.
*\*\fun     EP2 IN Callback Routine.
*\*\param   none
*\*\return  none 
**/
void EP2_IN_Callback (void)
{
	EP_IN_Callback(ENDP2);
}

/**
*\*\name    EP2_OUT_Callback.
*\*\fun     EP2 OUT Callback Routine.
*\*\param   none
*\*\return  none 
**/
void EP2_OUT_Callback(void)
{
    EP_OUT_Callback(ENDP2, ENDP2_RXADDR);
}

/**
*\*\name    EP3_IN_Callback.
*\*\fun     EP3 IN Callback Routine.
*\*\param   none
*\*\return  none 
**/
void EP3_IN_Callback (void)
{
	EP_IN_Callback(ENDP3);
}

/**
*\*\name    EP3_OUT_Callback.
*\*\fun     EP3 OUT Callback Routine.
*\*\param   none
*\*\return  none 
**/
void EP3_OUT_Callback(void)
{
    EP_OUT_Callback(ENDP3, ENDP3_RXADDR);
}

