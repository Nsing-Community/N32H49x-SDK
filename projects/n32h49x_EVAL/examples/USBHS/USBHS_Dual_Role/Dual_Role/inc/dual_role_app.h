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
*\*\file dual_role_app.h
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nsing Technologies Inc. All rights reserved.
**/
#ifndef __USR_DEMO_H__
#define __USR_DEMO_H__


/* Includes ------------------------------------------------------------------*/
#include "usbhs_conf.h"
#include <stdio.h>
#include "n32h49x.h"

typedef enum
{
    BUTTON_NULL = 1u,
    BUTTON_RIGHT,
    BUTTON_LEFT,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_SEL,
}Button_TypeDef;


typedef enum 
{
    DRD_IDLE   = 0,
    DRD_WAIT,  
    DRD_DEVICE,
    DRD_HOST,
}DRD_State;

typedef enum 
{
    DRD_HOST_IDLE   = 0,
    DRD_HOST_WAIT,  
}DRD_HOST_State;

typedef enum 
{
    DRD_DEVICE_IDLE   = 0,
    DRD_DEVICE_WAIT,    
}DRD_DEVICE_State;

typedef struct _DemoStateMachine
{
  __IO DRD_State            state;
  __IO DRD_HOST_State       Host_state;
  __IO DRD_DEVICE_State     Device_state;
  __IO uint8_t              select;
  __IO uint8_t              lock;
  
}DRD_StateMachine;

extern DRD_StateMachine drd;

#define DRD_LOCK()                       drd.lock = 1;
#define DRD_UNLOCK()                     drd.lock = 0;
#define DRD_IS_LOCKED()                  (drd.lock == 1)


extern uint8_t USBFS_EnumDone;

void DRD_Init (void);
void DRD_Process (void);
void DRD_HandleDisconnect (void);
void DRD_ProbeKey (Button_TypeDef state);
#endif /* __USR_DEMO_H__ */
