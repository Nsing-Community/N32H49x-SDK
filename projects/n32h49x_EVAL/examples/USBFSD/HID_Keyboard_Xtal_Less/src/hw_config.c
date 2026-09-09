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
*\*\file hw_config.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#include "hw_config.h"
#include "usbfsd_lib.h"
#include "usbfsd_desc.h"
#include "usbfsd_pwr.h"
#include "n32h49x_rcc.h"
#include "n32h49x_gpio.h"
#include "n32h49x_exti.h"
#include "misc.h"
#include "delay.h"


/**
*\*\name    Cfg_KeyInterrupt.
*\*\fun     Configures the gpio->exti line interrupt.
*\*\param   none
*\*\return  none 
**/
void Cfg_KeyInterrupt(void)
{
    GPIO_InitType GPIO_InitStructure;
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;

    KEY_INPUT_CLK_ENABLE;
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_AFIO, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);

    GPIO_InitStructure.Pin       = KEY_INPUT_PIN;
    GPIO_InitStructure.GPIO_Pull = KEY_INPUT_PULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(KEY_INPUT_PORT, &GPIO_InitStructure);

    /*Configure key EXTI Line to key input Pin*/
    GPIO_ConfigEXTILine(KEY_INPUT_EXTI_SOURCE, KEY_INPUT_PORT_SOURCE, KEY_INPUT_PIN_SOURCE);

    /*Configure key EXTI line*/
    EXTI_InitStructure.EXTI_Line    = KEY_INPUT_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    /*Set key input interrupt priority*/
    NVIC_InitStructure.NVIC_IRQChannel                   = KEY_INPUT_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}



/**
*\*\name    USBFS_IO_Configure.
*\*\fun     Configures usb fs device gpio.
*\*\param   none
*\*\return  none 
**/
void USBFS_IO_Configure(void)
{
    GPIO_InitType GPIO_InitStructure;  
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA, ENABLE);
    
    GPIO_InitStruct(&GPIO_InitStructure);
  
    GPIO_InitStructure.Pin              = GPIO_PIN_11;
    GPIO_InitStructure.GPIO_Mode        = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate   = GPIO_AF10;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin              = GPIO_PIN_12;
    GPIO_InitStructure.GPIO_Mode        = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate   = GPIO_AF10;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}
 
/**
*\*\name    Set_System.
*\*\fun     Configures Main system clocks & power.
*\*\param   none
*\*\return  none 
**/
void Set_System(void)
{
#ifdef USE_USBFSD_XTALLESS
    /* Set USB clock UCDR */
    Set_USBClock_Xtalless();
#endif /* USE_USBFSD_XTALLESS */
}

/**
*\*\name    Set_USBClock.
*\*\fun     Configures USB Clock input (48MHz).
*\*\param   sysclk: system clock.
*\*\          - SYSCLK_VALUE_48MHz
*\*\          - SYSCLK_VALUE_72MHz
*\*\          - SYSCLK_VALUE_96MHz
*\*\          - SYSCLK_VALUE_144MHz
*\*\          - SYSCLK_VALUE_192MHz
*\*\          - SYSCLK_VALUE_240MHz
*\*\return  ErrorStatus 
*\*\          - SUCCESS
*\*\          - ERROR
**/
ErrorStatus Set_USBClock(uint32_t sysclk)
{
    ErrorStatus status = SUCCESS;

    switch(sysclk)
    {
    case SYSCLK_VALUE_48MHz: 
        RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV1);
        RCC->CFG3 &= ~RCC_CFG3_USBFSTM;
        break;

    case SYSCLK_VALUE_96MHz: 
        RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV2);
        RCC->CFG3 &= ~RCC_CFG3_USBFSTM;
        break;
    
    case SYSCLK_VALUE_144MHz: 
        RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV3);
        RCC->CFG3 |= RCC_CFG3_USBFSTM;
        break;

    case SYSCLK_VALUE_192MHz: 
        RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV4);
        RCC->CFG3 |= RCC_CFG3_USBFSTM;
        break;
    
    case SYSCLK_VALUE_240MHz: 
        RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV5);
        RCC->CFG3 |= RCC_CFG3_USBFSTM;
        break;

    default:
        status = ERROR;
        break;
    }

    return status;
}


/**
*\*\name    USB_ActiveRemoteWakeup.
*\*\fun     Active remote wakeup host.
*\*\param   none
*\*\return  none 
**/
void USB_ActiveRemoteWakeup(void)
{
    uint16_t wCNTR;
    
    /* CTRL_LP_MODE = 0 */
    wCNTR = _GetCNTR();
    wCNTR &= (~CTRL_LP_MODE);
    _SetCNTR(wCNTR);

    /* reset FSUSP bit */ 
    _SetCNTR(IMR_MSK);
    
    /*Pull up DP*/
    _EnPortPullup();
    
    /* active Remote wakeup signaling */
    wCNTR = _GetCNTR();
    wCNTR |= CTRL_RESUM;
    _SetCNTR(wCNTR);
    
    systick_delay_ms(10);

    wCNTR = _GetCNTR();
    wCNTR &= (~CTRL_RESUM);
    _SetCNTR(wCNTR);
}


/**
*\*\name    Enter_LowPowerMode.
*\*\fun     Power-off system clocks and power while entering suspend mode.
*\*\param   none
*\*\return  none 
**/
void Enter_LowPowerMode(void)
{
    /* Set the device state to suspend */
    bDeviceState = SUSPENDED;
}

/**
*\*\name    Leave_LowPowerMode.
*\*\fun     Restores system clocks and power while exiting suspend mode.
*\*\param   none
*\*\return  none 
**/
void Leave_LowPowerMode(void)
{
    USB_DeviceMess* pInfo = &Device_Info;

    /* Set the device state to the correct state */
    if (pInfo->CurrentConfiguration != 0)
    {
        /* Device configured */
        bDeviceState = CONFIGURED;
    }
    else
    {
        bDeviceState = ATTACHED;
    }
}

/**
*\*\name    USB_Interrupts_Config.
*\*\fun     Configures the USB interrupts.
*\*\param   none
*\*\return  none 
**/
void USB_Interrupts_Config(void)
{
    NVIC_InitType NVIC_InitStructure;
    EXTI_InitType EXTI_InitStructure;

    /* 2 bit for pre-emption priority, 2 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Enable the USB interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = USB_FS_LP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the USB Wake-up interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = USB_FS_WKUP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure the EXTI line 18 connected internally to the USB IP */
    EXTI_ClrITPendBit(EXTI_LINE18);
    EXTI_InitStructure.EXTI_Line = EXTI_LINE18; 
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);
}

/**
*\*\name    USB_Config.
*\*\fun     Configures USB Clock input (48MHz).
*\*\param   sysclk: system clock.
*\*\          - SYSCLK_VALUE_48MHz
*\*\          - SYSCLK_VALUE_72MHz
*\*\          - SYSCLK_VALUE_96MHz
*\*\          - SYSCLK_VALUE_144MHz
*\*\          - SYSCLK_VALUE_192MHz
*\*\          - SYSCLK_VALUE_240MHz
*\*\return  ErrorStatus 
*\*\          - SUCCESS
*\*\          - ERROR
**/
ErrorStatus USB_Config(uint32_t sysclk)
{
    ErrorStatus status = SUCCESS;
    
#ifndef USE_USBFSD_XTALLESS
    RCC_ConfigUSBFSClk(RCC_USBFS_CLKSRC_PLLPRES);

    if(Set_USBClock(sysclk) == SUCCESS)
    {
        /* Enable USBFS clock */
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_USBFS, ENABLE);
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
#else 
    /* Enable UCRD clock */
    RCC_ConfigUSBFSClk(RCC_USBFS_CLKSRC_UCDR);
    /* Enable USBFS clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_USBFS, ENABLE);
    if(sysclk >= SYSCLK_VALUE_120MHz)
    {
        RCC->CFG3 |= RCC_CFG3_USBFSTM;
    }
    else
    {
        RCC->CFG3 &= ~RCC_CFG3_USBFSTM;
    }
     
#endif /* USE_USBFSD_XTALLESS */

    return status;
}

#ifdef USE_USBFSD_XTALLESS

/**
*\*\name    Set_USBClock_Xtalless.
*\*\fun     Configures USB Xtal less clock.
*\*\param   none
*\*\return  none
**/
void Set_USBClock_Xtalless(void)
{
    uint32_t time;
    
    /* Enable LDO for OSC UCDR */	
    _EnOsc300Ldo();
    time = 0x400;
    while(time--);
    /* Enable iBias for OSC UCDR */	
    _EnOsc300Ibias();
    time = 0x400;
    while(time--);
    /* Enable Core for OSC UCDR */	
    _EnOsc300Core();
    time = 0x400;
    while(time--);
    
    /* Enable UDCR */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_UCDR, ENABLE);
    time = 0x400;
    while(time--);
}

#endif /* USE_USBFSD_XTALLESS */
