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
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_user.h"
#include "usbd_mouse_core.h"
#include "n32h49x_rcc.h"
#include "n32h49x_gpio.h"
#include "usbhs_bsp.h"


#ifdef USB_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ )      /* !< IAR Compiler */
#pragma data_alignment=4
#endif
#endif
__ALIGN_BEGIN USB_CORE_MODULE USB_dev __ALIGN_END;

typedef enum
{
    BUTTON_NULL = 1u,
    BUTTON_RIGHT,
    BUTTON_LEFT,
    BUTTON_UP,
    BUTTON_DOWN,
}Button_TypeDef;

#define CURSOR_STEP     10u

/**
*\*\name    Key_ReadIOPin_continuous.
*\*\fun     Key status read function.
*\*\param   none.
*\*\return  button id.
*\*\
**/
Button_TypeDef Key_ReadIOPin_continuous(void)
{
    Button_TypeDef enKey = BUTTON_NULL;

#ifdef BUTTON_WKUP_EVB
    if (KEY_Press_Status_Read(UP_BUTTON_AND_WUKP) == SET)
    {
        enKey = BUTTON_UP;
    }
#ifdef BUTTON_KEY1_EVB
    else if (KEY_Press_Status_Read(DOWN_BUTTON_AND_1) == SET)
    {
        enKey = BUTTON_DOWN;
    }
#endif /* BUTTON_KEY1_EVB */ 
#ifdef BUTTON_KEY2_EVB
    else if (KEY_Press_Status_Read(LEFT_BUTTON_AND_2) == SET)
    {
        enKey = BUTTON_LEFT;
    }   
#endif /* BUTTON_KEY2_EVB */ 
#ifdef BUTTON_KEY3_EVB
    else if (KEY_Press_Status_Read(RIGHT_BUTTON_AND_3) == SET)
    {
        enKey = BUTTON_RIGHT;
    }
#endif /* BUTTON_KEY3_EVB */ 
    else
    {
        enKey = BUTTON_NULL;
    }    
#else
    
#ifdef BUTTON_KEY1_EVB
    if (KEY_Press_Status_Read(DOWN_BUTTON_AND_1) == SET)
    {
        enKey = BUTTON_DOWN;
    }
#ifdef BUTTON_KEY2_EVB
    else if (KEY_Press_Status_Read(LEFT_BUTTON_AND_2) == SET)
    {
        enKey = BUTTON_LEFT;
    }   
#endif /* BUTTON_KEY2_EVB */ 
#ifdef BUTTON_KEY3_EVB
    else if (KEY_Press_Status_Read(RIGHT_BUTTON_AND_3) == SET)
    {
        enKey = BUTTON_RIGHT;
    }
#endif /* BUTTON_KEY3_EVB */ 
    else
    {
        enKey = BUTTON_NULL;
    }  
#else

#ifdef BUTTON_KEY2_EVB
    if (KEY_Press_Status_Read(LEFT_BUTTON_AND_2) == SET)
    {
        enKey = BUTTON_LEFT;
    }
#ifdef BUTTON_KEY3_EVB
    else if (KEY_Press_Status_Read(RIGHT_BUTTON_AND_3) == SET)
    {
        enKey = BUTTON_RIGHT;
    }
#endif /* BUTTON_KEY3_EVB */ 
    else
    {
        enKey = BUTTON_NULL;
    }  
#else

#ifdef BUTTON_KEY3_EVB
    if (KEY_Press_Status_Read(RIGHT_BUTTON_AND_3) == SET)
    {
        enKey = BUTTON_RIGHT;
    }
    else
#endif /* BUTTON_KEY3_EVB */
    {
        enKey = BUTTON_NULL;
    }
#endif /* BUTTON_KEY2_EVB */     
#endif /* BUTTON_KEY1_EVB */     
#endif /* BUTTON_WKUP_EVB */     

    return enKey;
}

/**
*\*\name    get_mouse_pos.
*\*\fun     get the position of the mouse.
*\*\param   none.
*\*\return  Pointer to report buffer.
*\*\
**/
uint8_t* get_mouse_pos(void)
{
    int8_t  x = (int8_t)0, y = (int8_t)0;
    static uint8_t HID_Buffer [4];

    switch (Key_ReadIOPin_continuous())
    {
        case BUTTON_UP:
            y -= (int8_t)CURSOR_STEP;
            break;
        case BUTTON_DOWN:
            y += (int8_t)CURSOR_STEP;
            break;
        case BUTTON_LEFT:
            x -= (int8_t)CURSOR_STEP;
            break;
        case BUTTON_RIGHT:
            x += (int8_t)CURSOR_STEP;
            break;
        default:
            break;
    }
    HID_Buffer[0] = (uint8_t)0;
    HID_Buffer[1] = (uint8_t)x;
    HID_Buffer[2] = (uint8_t)y;
    HID_Buffer[3] = (uint8_t)0;

    return HID_Buffer;
}


/**
*\*\name    USBHS_ConfigCLK.
*\*\fun     Configure USBHS clock.
*\*\param   none.
*\*\return  none.
*\*\
**/
static void USBHS_ConfigCLK(void)
{
    /* Select the corresponding bandwidth and frequency*/
    RCC_ConfigUSBHSBandwidth(RCC_USBHS_BW_16M);
    
    /* Select USBHS clock source frequency */
    RCC_ConfigUSBHSFrequency(RCC_USBHS_FREQ_16_OR_32M);

    /* Select HSE as USBHS clock */
    RCC_ConfigUSBHSClk(RCC_USBHS_CLKSRC_HSE);

    /* Reset the USBHS phy clock*/
    RCC_EnableAHBPeriphReset(RCC_AHBPRST_USBHSPHYRST); 
    
    /* Enables the USBHS peripheral clock*/
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_USBHS, ENABLE);

    /* Set USBHS timing tune */
    RCC->USBHSCTRL2 = (RCC->USBHSCTRL2 & (~(0xF << 4)))  | (0xB << 4);  //TX vref TUNE
    RCC->USBHSCTRL1 = (RCC->USBHSCTRL1 & (~(0x7 << 12))) | (0x5 << 12); //TX Rise TUNE
    RCC->USBHSCTRL2 = (RCC->USBHSCTRL2 & (~(0x3 << 12))) | (0x0 << 14); //TX Res TUNE
    RCC->USBHSCTRL2 = (RCC->USBHSCTRL2 & (~(0x3 << 16))) | (0x1 << 16); //TX preempamp TUNE

    USB_BSP_mDelay(20);

    /* Reset the usBHs phy clock */
    RCC_EnableAHBPeriphReset(RCC_AHBPRST_USBHSPHYRST);
}


/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none.
*\*\return  none.
*\*\
**/
int main(void)
{
    Hardware_Board_Key_Init();
    USBHS_ConfigCLK();

    USBD_Init(&USB_dev, &USBD_desc, &USBD_MOUSE_cb, &USER_cb);

    while (1)
    {
    }
}
