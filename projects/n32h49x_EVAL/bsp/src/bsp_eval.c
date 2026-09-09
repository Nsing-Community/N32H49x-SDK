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
*\*\file usbhs_bsp.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#include "delay.h"
#include "bsp_eval.h"

static Key_Info_t Key_Info[BUTTON_NUM] =
{
#ifdef BUTTON_WKUP_EVB
    {BUTTON_WKUP_PORT, BUTTON_WKUP_PIN, BUTTON_WKUP_STATE},
#endif /* BUTTON_WKUP_EVB */ 

#ifdef BUTTON_KEY1_EVB
    {BUTTON_KEY1_PORT, BUTTON_KEY1_PIN, BUTTON_KEY1_STATE},
#endif /* BUTTON_KEY1_EVB */ 

#ifdef BUTTON_KEY2_EVB
    {BUTTON_KEY2_PORT, BUTTON_KEY2_PIN, BUTTON_KEY2_STATE},
#endif /* BUTTON_KEY2_EVB */ 

#ifdef BUTTON_KEY3_EVB
    {BUTTON_KEY3_PORT, BUTTON_KEY3_PIN, BUTTON_KEY3_STATE},
#endif /* BUTTON_KEY3_EVB */ 
    
#ifdef BUTTON_KEY4_EVB
    {BUTTON_KEY4_PORT, BUTTON_KEY4_PIN, BUTTON_KEY4_STATE},
#endif /* BUTTON_KEY4_EVB */ 
    
#ifdef BUTTON_KEY5_EVB
    {BUTTON_KEY5_PORT, BUTTON_KEY5_PIN, BUTTON_KEY5_STATE},
#endif /* BUTTON_KEY5_EVB */ 
};

/**
*\*\name   Hardware_Board_Led_Init.
*\*\fun    Development board led initialization.
*\*\param  none
*\*\return none
*/
void Hardware_Board_Led_Init(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;

#ifdef LED1_EVB
    LED1_CLOCK_ENABLE;

    GPIO_InitStructure.Pin = LED1_PIN;
    GPIO_InitPeripheral(LED1_PORT, &GPIO_InitStructure);
#endif /* LED1_EVB */

#ifdef LED2_EVB
    LED2_CLOCK_ENABLE;

    GPIO_InitStructure.Pin = LED2_PIN;
    GPIO_InitPeripheral(LED2_PORT, &GPIO_InitStructure);
#endif /* LED2_EVB */

#ifdef LED3_EVB
    LED3_CLOCK_ENABLE;

    GPIO_InitStructure.Pin = LED3_PIN;
    GPIO_InitPeripheral(LED3_PORT, &GPIO_InitStructure);
#endif /* LED3_EVB */
}

/**
*\*\name   LED_On.
*\*\fun    Turn on LED by set GPIO pin.
*\*\param  GPIOx
*\*\param  Pin
*\*\return none
*/
void LED_On(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_SetBits(GPIOx, Pin);
}

/**
*\*\name   LED_Off.
*\*\fun    Turn off LED by reset GPIO pin.
**\*\param  GPIOx
*\*\param  Pin
*\*\return none
*/
void LED_Off(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_ResetBits(GPIOx, Pin);
}

/**
*\*\name   LED_Blink.
*\*\fun    Blink LED by toggle GPIO pin.
*\*\param  GPIOx
*\*\param  Pin
*\*\return none
*/
void LED_Blink(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_TogglePin(GPIOx, Pin);
}


/**
*\*\name   Hardware_Board_Key_Init.
*\*\fun    Development board button initialization.
*\*\param  none
*\*\return none
*/
void Hardware_Board_Key_Init(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;

#ifdef BUTTON_WKUP_EVB
    BUTTON_WKUP_CLK_ENABLE;

    GPIO_InitStructure.Pin       = BUTTON_WKUP_PIN;
    GPIO_InitStructure.GPIO_Pull = BUTTON_WKUP_PULL;
    GPIO_InitPeripheral(BUTTON_WKUP_PORT, &GPIO_InitStructure);
#endif /* BUTTON_WKUP_EVB */

#ifdef BUTTON_KEY1_EVB
    BUTTON_KEY1_CLK_ENABLE;

    GPIO_InitStructure.Pin       = BUTTON_KEY1_PIN;
    GPIO_InitStructure.GPIO_Pull = BUTTON_KEY1_PULL;
    GPIO_InitPeripheral(BUTTON_KEY1_PORT, &GPIO_InitStructure);
#endif /* BUTTON_KEY1_EVB */

#ifdef BUTTON_KEY2_EVB
    BUTTON_KEY2_CLK_ENABLE;

    GPIO_InitStructure.Pin       = BUTTON_KEY2_PIN;
    GPIO_InitStructure.GPIO_Pull = BUTTON_KEY2_PULL;
    GPIO_InitPeripheral(BUTTON_KEY2_PORT, &GPIO_InitStructure);
#endif /* BUTTON_KEY2_EVB */

#ifdef BUTTON_KEY3_EVB
    BUTTON_KEY3_CLK_ENABLE;

    GPIO_InitStructure.Pin       = BUTTON_KEY3_PIN;
    GPIO_InitStructure.GPIO_Pull = BUTTON_KEY3_PULL;
    GPIO_InitPeripheral(BUTTON_KEY3_PORT, &GPIO_InitStructure);
#endif /* BUTTON_KEY3_EVB */
}


/**
*\*\name   KEY_Press_Status_Scan.
*\*\fun    Get key pressed or not status.
*\*\param  Key_Name
*\*\return none
*/
FlagStatus KEY_Press_Status_Get(Key_Name_t Key_Name)
{
    FlagStatus status = RESET;

    if (GPIO_ReadInputDataBit(Key_Info[Key_Name].GPIOx, Key_Info[Key_Name].Pin) == Key_Info[Key_Name].State)
    {
        systick_delay_ms(20); 
        
        if (GPIO_ReadInputDataBit(Key_Info[Key_Name].GPIOx, Key_Info[Key_Name].Pin) == Key_Info[Key_Name].State)
        {
            while (GPIO_ReadInputDataBit(Key_Info[Key_Name].GPIOx, Key_Info[Key_Name].Pin) == Key_Info[Key_Name].State)
            {
            }
            
            systick_delay_ms(20); 
            
            status = SET;
        }
    }
    
    return status;
}

/**
*\*\name   KEY_Press_Status_Read.
*\*\fun    Get key pressed or not status.
*\*\param  Key_Name
*\*\return none
*/
FlagStatus KEY_Press_Status_Read(Key_Name_t Key_Name)
{
    return ((GPIO_ReadInputDataBit(Key_Info[Key_Name].GPIOx, Key_Info[Key_Name].Pin) == Key_Info[Key_Name].State) ? SET : RESET);
}


/**
*\*\name   Get_Ken_Info_Array.
*\*\fun    Get key infor array.
*\*\param  Key_Name
*\*\return none
*/
Key_Info_t *Get_Ken_Info_Array(void)
{
    return Key_Info;
}
