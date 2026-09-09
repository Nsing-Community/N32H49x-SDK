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
#include "n32h49x_rcc.h"
#include "n32h49x_gpio.h"
#include "log.h"

#define MAX_JTAG_STS    (4)
uint32_t jtag_sts[MAX_JTAG_STS]={GPIO_RMP_SWJ_JTAG,GPIO_RMP_SWJ_JTAG_NO_NJTRST,GPIO_RMP_SWJ_SWD,GPIO_RMP_SWJ_DISABLE};
char *sts[] = {"JTAG","JTAG without TRST","SWD","Disabled"};

#define KEY_DEBOUCING   (50000)
uint32_t KeyDelay = 0;

uint32_t IODelay = 0;

static void JTAG_switch(uint32_t sts_cnt);

/**
 *\*\name   main.
 *\*\fun    Main program.
 *\*\param  none
 *\*\return none
 */
int main(void)
{
    static uint32_t sts_cnt = 0;

    log_init();
    Delay(SystemCoreClock/4);
    printf("\r\n IO remaping demo!\r\n");
    printf("JTAG current status is %s\r\n",sts[sts_cnt]);

    /* AFIO clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_AFIO,ENABLE);

    /* LED port init */
    LED_Init(LED1_PORT,LED1_PIN,LED1_CLOCK);
    LED_Init(LED3_PORT,LED3_PIN,LED3_CLOCK);
    
    /*JTAG IO init*/
    JTAG_IO_Init();
    
    /* KEY port init */
    Key_Init(KEY_PORT, KEY_PIN, KEY_CLOCK);
    
    /* LED turn on one by one and repeat */
    while (1)
    {
        if( KEY_READ() != 0) /* Key pressed */
        {
            KeyDelay++;
        }
        else if(KeyDelay > KEY_DEBOUCING)   /* Key released */
        {
            if(sts_cnt >= (MAX_JTAG_STS-1))
            {
                sts_cnt = 0;
            }
            else
            {
                sts_cnt++;
            }
            
            
            JTAG_switch(sts_cnt);   /* Change JTAG status by remapping */
            KeyDelay = 0;
        }
        else if(KeyDelay)
        {
            KeyDelay = 0;
        }
        else
        {
        
        }

        /*Toggle JTAG IO port*/
        if(IODelay < (SystemCoreClock/100))
        {
            IODelay++;
        }
        else
        {
            IODelay = 0;
            GPIO_TogglePin(GPIOA,GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
            GPIO_TogglePin(GPIOB,GPIO_PIN_3|GPIO_PIN_4);
        }
        
    }
}

/**
 *\*\name   LED_Init.
 *\*\fun    Initialize a GPIO as LED port.
 *\*\param  GPIOx
 *\*\         - GPIOA
 *\*\         - GPIOB
 *\*\         - GPIOC
 *\*\         - GPIOD
 *\*\         - GPIOE
 *\*\         - GPIOF
 *\*\         - GPIOG
 *\*\         - GPIOH
 *\*\param  Pin
 *\*\         - GPIO_PIN_0
 *\*\         - GPIO_PIN_1
 *\*\         - GPIO_PIN_2
 *\*\         - GPIO_PIN_3
 *\*\         - GPIO_PIN_4
 *\*\         - GPIO_PIN_5
 *\*\         - GPIO_PIN_6
 *\*\         - GPIO_PIN_7
 *\*\         - GPIO_PIN_8
 *\*\         - GPIO_PIN_9
 *\*\         - GPIO_PIN_10
 *\*\         - GPIO_PIN_11
 *\*\         - GPIO_PIN_12
 *\*\         - GPIO_PIN_13
 *\*\         - GPIO_PIN_14
 *\*\         - GPIO_PIN_15
 *\*\         - GPIO_PIN_ALL
 *\*\param  clock
 *\*\         - RCC_AHB_PERIPHEN_GPIOA
 *\*\         - RCC_AHB_PERIPHEN_GPIOB
 *\*\         - RCC_AHB_PERIPHEN_GPIOC
 *\*\         - RCC_AHB_PERIPHEN_GPIOD
 *\*\         - RCC_AHB_PERIPHEN_GPIOE
 *\*\         - RCC_AHB_PERIPHEN_GPIOF
 *\*\         - RCC_AHB_PERIPHEN_GPIOG
 *\*\         - RCC_AHB_PERIPHEN_GPIOH
 *\*\return none
 */
void LED_Init(GPIO_Module* GPIOx,uint16_t Pin, uint32_t clock)
{
    GPIO_InitType InitStruct;
    
    /* Enable GPIO clock */
    RCC_EnableAHB1PeriphClk(clock,ENABLE);
    
    /* Init GPIO as output push-pull mode */
    InitStruct.Pin            = Pin;
    InitStruct.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    InitStruct.GPIO_Mode      = GPIO_MODE_OUTPUT_PP;
    InitStruct.GPIO_Alternate = GPIO_AF0;
    InitStruct.GPIO_Pull      = GPIO_NO_PULL;
    InitStruct.GPIO_Current   = GPIO_DS_8mA;
    
    GPIO_InitPeripheral(GPIOx, &InitStruct);
}

/**
 *\*\name   LED_On.
 *\*\fun    Turn on LED by set GPIO pin.
 *\*\param  none
 *\*\return none
 */
void LED_On(GPIO_Module* GPIOx,uint16_t Pin)
{
    GPIO_SetBits(GPIOx,Pin);
}

/**
 *\*\name   LED_Off.
 *\*\fun    Turn off LED by reset GPIO pin.
 *\*\param  none
 *\*\return none
 */
void LED_Off(GPIO_Module* GPIOx,uint16_t Pin)
{
    GPIO_ResetBits(GPIOx,Pin);
}

/**
 *\*\name   LED_Blink.
 *\*\fun    Blink LED by toggle GPIO pin.
 *\*\param  none
 *\*\return none
 */
void LED_Blink(GPIO_Module* GPIOx,uint16_t Pin)
{
    GPIO_TogglePin(GPIOx,Pin);
}

/**
 *\*\name   Key_Init.
 *\*\fun    Initialize a GPIO as key port.
 *\*\param  GPIOx
 *\*\         - GPIOA
 *\*\         - GPIOB
 *\*\         - GPIOC
 *\*\         - GPIOD
 *\*\         - GPIOE
 *\*\         - GPIOF
 *\*\         - GPIOG
 *\*\         - GPIOH
 *\*\param  Pin
 *\*\         - GPIO_PIN_0
 *\*\         - GPIO_PIN_1
 *\*\         - GPIO_PIN_2
 *\*\         - GPIO_PIN_3
 *\*\         - GPIO_PIN_4
 *\*\         - GPIO_PIN_5
 *\*\         - GPIO_PIN_6
 *\*\         - GPIO_PIN_7
 *\*\         - GPIO_PIN_8
 *\*\         - GPIO_PIN_9
 *\*\         - GPIO_PIN_10
 *\*\         - GPIO_PIN_11
 *\*\         - GPIO_PIN_12
 *\*\         - GPIO_PIN_13
 *\*\         - GPIO_PIN_14
 *\*\         - GPIO_PIN_15
 *\*\         - GPIO_PIN_ALL
 *\*\param  clock
 *\*\         - RCC_AHB_PERIPHEN_GPIOA
 *\*\         - RCC_AHB_PERIPHEN_GPIOB
 *\*\         - RCC_AHB_PERIPHEN_GPIOC
 *\*\         - RCC_AHB_PERIPHEN_GPIOD
 *\*\         - RCC_AHB_PERIPHEN_GPIOE
 *\*\         - RCC_AHB_PERIPHEN_GPIOF
 *\*\         - RCC_AHB_PERIPHEN_GPIOG
 *\*\         - RCC_AHB_PERIPHEN_GPIOH
 *\*\return none
 */
void Key_Init(GPIO_Module* GPIOx,uint16_t Pin, uint32_t clock)
{
    GPIO_InitType InitStruct;
    
    /* Enable GPIO clock */
    RCC_EnableAHB1PeriphClk(clock,ENABLE);
    
    /* Init GPIO as input push-down mode */
    InitStruct.Pin            = Pin;
    InitStruct.GPIO_Slew_Rate = GPIO_SLEW_RATE_SLOW;
    InitStruct.GPIO_Mode      = GPIO_MODE_INPUT;
    InitStruct.GPIO_Alternate = GPIO_AF0;
    InitStruct.GPIO_Pull      = GPIO_PULL_DOWN;
    InitStruct.GPIO_Current   = GPIO_DS_8mA;
    
    GPIO_InitPeripheral(GPIOx, &InitStruct);
}

/**
 *\*\name   Key_Init.
 *\*\fun    Initialize all JTAG port as GPIO push-pull mode.
 *\*\param  none
 *\*\return none
 */
void JTAG_IO_Init(void)
{
    GPIO_InitType InitStruct;
    
    /* Enable GPIO clock */
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA | RCC_AHB_PERIPHEN_GPIOB,ENABLE);
    
    /* Init JTMS-SWDIO, JTCK-SWCLK, JTDI as push-pull mode */
    InitStruct.Pin            = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    InitStruct.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    InitStruct.GPIO_Mode      = GPIO_MODE_OUTPUT_PP;
    InitStruct.GPIO_Alternate = GPIO_NO_AF;
    InitStruct.GPIO_Pull      = GPIO_NO_PULL;
    InitStruct.GPIO_Current   = GPIO_DS_2mA;
    GPIO_InitPeripheral(GPIOA, &InitStruct);
    
    /* Init NJTRST as push-pull mode */
    InitStruct.Pin            = GPIO_PIN_3|GPIO_PIN_4;
    GPIO_InitPeripheral(GPIOB, &InitStruct);
}

/**
 *\*\name   Delay.
 *\*\fun    Delay a short time.
 *\*\param  none
 *\*\return none
 */
static void JTAG_switch(uint32_t sts_cnt)
{
    if(sts_cnt >= MAX_JTAG_STS)
        return;
   
    LED_Off(LED1_PORT, LED1_PIN);
    LED_Off(LED3_PORT, LED3_PIN);

    GPIO_ConfigPinRemap(0,0,jtag_sts[sts_cnt]);
    printf("JTAG status changed to %s\r\n",sts[sts_cnt]);

    if(sts_cnt & 0x1)
    {
        LED_On(LED1_PORT, LED1_PIN);
    }

    if(sts_cnt > 1)
    {
        LED_On(LED3_PORT, LED3_PIN);
    }
}

/**
 *\*\name   Delay.
 *\*\fun    Delay a short time.
 *\*\param  none
 *\*\return none
 */
void Delay(uint32_t delay)
{
    uint32_t i;
    
    for(i=0;i<delay;i++);
}

