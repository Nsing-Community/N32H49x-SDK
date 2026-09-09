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
*\*\file hw_config.h
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#ifndef __HW_CONFIG_H__
#define __HW_CONFIG_H__

#include "bsp_eval.h"
#include "n32h49x.h"
#include "usbfsd_type.h"
#include "n32h49x_gpio.h"

/* Exported define -----------------------------------------------------------*/
#define SYSCLK_VALUE_48MHz            ((uint32_t)48000000)
#define SYSCLK_VALUE_72MHz            ((uint32_t)72000000)
#define SYSCLK_VALUE_96MHz            ((uint32_t)96000000)
#define SYSCLK_VALUE_108MHz           ((uint32_t)108000000)
#define SYSCLK_VALUE_120MHz           ((uint32_t)120000000)
#define SYSCLK_VALUE_144MHz           ((uint32_t)144000000)
#define SYSCLK_VALUE_192MHz           ((uint32_t)192000000)
#define SYSCLK_VALUE_240MHz           ((uint32_t)240000000)

#ifdef USE_USBFSD_XTALLESS
#define OSC300_CTRL         ((__IO unsigned*)(0x4001000C))
#define _DisOsc300Ldo()    (*OSC300_CTRL = (*OSC300_CTRL) & (~0x40000000));
#define _EnOsc300Ldo()     (*OSC300_CTRL = (*OSC300_CTRL) | 0x40000000);
#define _DisOsc300Ibias()  (*OSC300_CTRL = (*OSC300_CTRL) & (~0x20000000));
#define _EnOsc300Ibias()   (*OSC300_CTRL = (*OSC300_CTRL) | 0x20000000);
#define _DisOsc300Core()   (*OSC300_CTRL = (*OSC300_CTRL) & (~0x10000000));
#define _EnOsc300Core()    (*OSC300_CTRL = (*OSC300_CTRL) | 0x10000000);

#endif /* USE_USBFSD_XTALLESS */




#define KEY_INPUT_CLK_ENABLE    BUTTON_WKUP_CLK_ENABLE
#define KEY_INPUT_PORT          BUTTON_WKUP_PORT
#define KEY_INPUT_PIN           BUTTON_WKUP_PIN
#define KEY_INPUT_PULL          BUTTON_WKUP_PULL
#define KEY_INPUT_STATE         BUTTON_WKUP_STATE
#define KEY_INPUT_EXTI_LINE     BUTTON_WKUP_EXTI_LINE
#define KEY_INPUT_PORT_SOURCE   BUTTON_WKUP_PORT_SOURCE
#define KEY_INPUT_PIN_SOURCE    BUTTON_WKUP_PIN_SOURCE
#define KEY_INPUT_EXTI_SOURCE   BUTTON_WKUP_EXTI_SOURCE
#define KEY_INPUT_IRQn          BUTTON_WKUP_IRQn


#define open_capslock_led()     GPIO_SetBits(LED1_PORT, LED1_PIN);
#define close_capslock_led()    GPIO_ResetBits(LED1_PORT, LED1_PIN);

#define open_numlock_led()      GPIO_SetBits(LED2_PORT, LED2_PIN);
#define close_numlock_led()     GPIO_ResetBits(LED2_PORT, LED2_PIN);


//#define USB_LOW_PWR_MGMT_SUPPORT


void Set_System(void);
ErrorStatus Set_USBClock(uint32_t sysclk);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void TimingDelay_Decrement(void);
void Cfg_KeyInterrupt(void);
void USBFS_IO_Configure(void);
ErrorStatus USB_Config(uint32_t sysclk);
void USB_ActiveRemoteWakeup(void);

#ifdef USE_USBFSD_XTALLESS
void Set_USBClock_Xtalless(void);
#endif /* USE_USBFSD_XTALLESS */

#endif /*__HW_CONFIG_H__*/

