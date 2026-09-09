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
*\*\file usbhs_evb.h
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#ifndef __USBHS_EVB_H__
#define __USBHS_EVB_H__

#include "n32h49x.h"
#include "n32h49x_rcc.h"
#include "n32h49x_gpio.h"

/*N32H497 Hardware Eval Defination*/
#define N32H497ZGL7_STB_V1_0  (1U)
#define N32H497ZGL7_EVB_V1_0  (2U)

/* Demo board selected */
#ifndef DEMO_BOARD
    #define  DEMO_BOARD   (N32H497ZGL7_EVB_V1_0)
#endif

#if (DEMO_BOARD == N32H497ZGL7_STB_V1_0)
    #define LED1_EVB
    #define LED1_PORT                      GPIOA
    #define LED1_PIN                       GPIO_PIN_3
    #define LED1_CLOCK                     RCC_AHB_PERIPHEN_GPIOA
    #define LED1_CLOCK_ENABLE              RCC_EnableAHB1PeriphClk(LED1_CLOCK, ENABLE)

    #define LED2_EVB
    #define LED2_PORT                      GPIOA
    #define LED2_PIN                       GPIO_PIN_8
    #define LED2_CLOCK                     RCC_AHB_PERIPHEN_GPIOA
    #define LED2_CLOCK_ENABLE              RCC_EnableAHB1PeriphClk(LED2_CLOCK, ENABLE)

    #define LED3_EVB
    #define LED3_PORT                      GPIOB
    #define LED3_PIN                       GPIO_PIN_4
    #define LED3_CLOCK                     RCC_AHB_PERIPHEN_GPIOB
    #define LED3_CLOCK_ENABLE              RCC_EnableAHB1PeriphClk(LED3_CLOCK, ENABLE)

    #define BUTTON_WKUP_EVB
    #define BUTTON_WKUP_CLK                RCC_AHB_PERIPHEN_GPIOA
    #define BUTTON_WKUP_CLK_ENABLE         RCC_EnableAHB1PeriphClk(BUTTON_WKUP_CLK, ENABLE)
    #define BUTTON_WKUP_PORT               GPIOA
    #define BUTTON_WKUP_PIN                GPIO_PIN_2
    #define BUTTON_WKUP_PULL               GPIO_PULL_DOWN
    #define BUTTON_WKUP_STATE              Bit_SET
    #define BUTTON_WKUP_EXTI_LINE          EXTI_LINE0
    #define BUTTON_WKUP_PORT_SOURCE        GPIOA_PORT_SOURCE
    #define BUTTON_WKUP_PIN_SOURCE         GPIO_PIN_SOURCE2
    #define BUTTON_WKUP_EXTI_SOURCE        EXTI_LINE_SOURCE0
    #define BUTTON_WKUP_IRQn               EXTI0_IRQn

    #define BUTTON_KEY1_EVB
    #define BUTTON_KEY1_CLK                RCC_AHB_PERIPHEN_GPIOA
    #define BUTTON_KEY1_CLK_ENABLE         RCC_EnableAHB1PeriphClk(BUTTON_KEY1_CLK, ENABLE)
    #define BUTTON_KEY1_PORT               GPIOA
    #define BUTTON_KEY1_PIN                GPIO_PIN_4
    #define BUTTON_KEY1_PULL               GPIO_PULL_UP
    #define BUTTON_KEY1_STATE              Bit_RESET

    #define BUTTON_KEY2_EVB
    #define BUTTON_KEY2_CLK                RCC_AHB_PERIPHEN_GPIOA
    #define BUTTON_KEY2_CLK_ENABLE         RCC_EnableAHB1PeriphClk(BUTTON_KEY2_CLK, ENABLE)
    #define BUTTON_KEY2_PORT               GPIOA
    #define BUTTON_KEY2_PIN                GPIO_PIN_5
    #define BUTTON_KEY2_PULL               GPIO_PULL_UP
    #define BUTTON_KEY2_STATE              Bit_RESET

    #define BUTTON_KEY3_EVB
    #define BUTTON_KEY3_CLK                RCC_AHB_PERIPHEN_GPIOA
    #define BUTTON_KEY3_CLK_ENABLE         RCC_EnableAHB1PeriphClk(BUTTON_KEY3_CLK, ENABLE)
    #define BUTTON_KEY3_PORT               GPIOA
    #define BUTTON_KEY3_PIN                GPIO_PIN_6
    #define BUTTON_KEY3_PULL               GPIO_PULL_UP
    #define BUTTON_KEY3_STATE              Bit_RESET

    #define USB_HOST_EVB
    #define USB_VBUS_DRIVER_PORT           GPIOB
    #define USB_VBUS_DRIVER_PIN            GPIO_PIN_3
    #define USB_VBUS_DRIVER_CLK            RCC_AHB_PERIPHEN_GPIOB
    #define USB_VBUS_DRIVER_CLK_ENABLE     RCC_EnableAHB1PeriphClk(USB_VBUS_DRIVER_CLK, ENABLE)
#elif (DEMO_BOARD == N32H497ZGL7_EVB_V1_0)
    #define LED1_EVB
    #define LED1_PORT                      GPIOA
    #define LED1_PIN                       GPIO_PIN_3
    #define LED1_CLOCK                     RCC_AHB_PERIPHEN_GPIOA
    #define LED1_CLOCK_ENABLE              RCC_EnableAHB1PeriphClk(LED1_CLOCK, ENABLE)

    #define LED2_EVB
    #define LED2_PORT                      GPIOB
    #define LED2_PIN                       GPIO_PIN_3
    #define LED2_CLOCK                     RCC_AHB_PERIPHEN_GPIOB
    #define LED2_CLOCK_ENABLE              RCC_EnableAHB1PeriphClk(LED2_CLOCK, ENABLE)

    #define LED3_EVB
    #define LED3_PORT                      GPIOA
    #define LED3_PIN                       GPIO_PIN_8
    #define LED3_CLOCK                     RCC_AHB_PERIPHEN_GPIOA
    #define LED3_CLOCK_ENABLE              RCC_EnableAHB1PeriphClk(LED3_CLOCK, ENABLE)

    #define BUTTON_WKUP_EVB
    #define BUTTON_WKUP_CLK                RCC_AHB_PERIPHEN_GPIOA
    #define BUTTON_WKUP_CLK_ENABLE         RCC_EnableAHB1PeriphClk(BUTTON_WKUP_CLK, ENABLE)
    #define BUTTON_WKUP_PORT               GPIOA
    #define BUTTON_WKUP_PIN                GPIO_PIN_0
    #define BUTTON_WKUP_PULL               GPIO_PULL_DOWN
    #define BUTTON_WKUP_STATE              Bit_SET
    #define BUTTON_WKUP_EXTI_LINE          EXTI_LINE0
    #define BUTTON_WKUP_PORT_SOURCE        GPIOA_PORT_SOURCE
    #define BUTTON_WKUP_PIN_SOURCE         GPIO_PIN_SOURCE0
    #define BUTTON_WKUP_EXTI_SOURCE        EXTI_LINE_SOURCE0
    #define BUTTON_WKUP_IRQn               EXTI0_IRQn
    

    #define BUTTON_KEY1_EVB
    #define BUTTON_KEY1_CLK                (RCC_AHB_PERIPHEN_GPIOC | RCC_AHB_PERIPHEN_GPIOF)
    #define BUTTON_KEY1_CLK_ENABLE         RCC_EnableAHB1PeriphClk(BUTTON_KEY1_CLK, ENABLE)
    #define BUTTON_KEY1_PORT               GPIOC
    #define BUTTON_KEY1_PIN                GPIO_PIN_13
    #define BUTTON_KEY1_PULL               GPIO_PULL_UP
    #define BUTTON_KEY1_STATE              Bit_RESET

    #define BUTTON_KEY2_EVB
    #define BUTTON_KEY2_CLK                RCC_AHB_PERIPHEN_GPIOA
    #define BUTTON_KEY2_CLK_ENABLE         RCC_EnableAHB1PeriphClk(BUTTON_KEY2_CLK, ENABLE)
    #define BUTTON_KEY2_PORT               GPIOA
    #define BUTTON_KEY2_PIN                GPIO_PIN_15
    #define BUTTON_KEY2_PULL               GPIO_PULL_UP
    #define BUTTON_KEY2_STATE              Bit_RESET

    #define BUTTON_KEY3_EVB
    #define BUTTON_KEY3_CLK                RCC_AHB_PERIPHEN_GPIOB
    #define BUTTON_KEY3_CLK_ENABLE         RCC_EnableAHB1PeriphClk(BUTTON_KEY3_CLK, ENABLE)
    #define BUTTON_KEY3_PORT               GPIOB
    #define BUTTON_KEY3_PIN                GPIO_PIN_4
    #define BUTTON_KEY3_PULL               GPIO_PULL_UP
    #define BUTTON_KEY3_STATE              Bit_RESET

    #define USB_HOST_EVB
    #define USB_VBUS_DRIVER_PORT           GPIOH
    #define USB_VBUS_DRIVER_PIN            GPIO_PIN_2
    #define USB_VBUS_DRIVER_CLK            RCC_AHB_PERIPHEN_GPIOH
    #define USB_VBUS_DRIVER_CLK_ENABLE     RCC_EnableAHB1PeriphClk(USB_VBUS_DRIVER_CLK, ENABLE)
#endif /* (HARDWARE_EVB == N32H785XIB7_STB_V11) */

typedef enum
{
#ifdef BUTTON_WKUP_EVB
    UP_BUTTON_AND_WUKP = 0U,
#endif /* BUTTON_WKUP_EVB */   

#ifdef BUTTON_KEY1_EVB
    DOWN_BUTTON_AND_1,
#endif /* BUTTON_KEY1_EVB */   

#ifdef BUTTON_KEY2_EVB
    LEFT_BUTTON_AND_2,
#endif /* BUTTON_KEY2_EVB */ 

#ifdef BUTTON_KEY3_EVB
    RIGHT_BUTTON_AND_3,
#endif /* BUTTON_KEY3_EVB */ 
    
#ifdef BUTTON_KEY4_EVB
    LEFT_BUTTON_AND_4,
#endif /* BUTTON_KEY4_EVB */ 
    
#ifdef BUTTON_KEY5_EVB
    RIGHT_BUTTON_AND_5,
#endif /* BUTTON_KEY5_EVB */ 

    BUTTON_NUM,
} Key_Name_t;

typedef struct 
{
    GPIO_Module*    GPIOx;
    uint16_t        Pin;
    Bit_OperateType State;
} Key_Info_t;



void Hardware_Board_Led_Init(void);
void LED_On(GPIO_Module* GPIOx, uint16_t Pin);
void LED_Off(GPIO_Module* GPIOx, uint16_t Pin);
void LED_Blink(GPIO_Module* GPIOx, uint16_t Pin);

void Hardware_Board_Key_Init(void);
FlagStatus KEY_Press_Status_Get(Key_Name_t Key_Name);
FlagStatus KEY_Press_Status_Read(Key_Name_t Key_Name);
Key_Info_t *Get_Ken_Info_Array(void);

#endif /* __USBHS_EVB_H__ */

