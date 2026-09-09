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
 */
#include "main.h"
#include "delay.h"
#include "log.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void DAC_Configuratoin(void);
ErrorStatus Start_UserTrimming(uint8_t *NewTrimValue);

uint8_t  Trim_Value = 0;
ErrorStatus status = ERROR;
/**
*\*\name    main.
*\*\fun     main program.
*\*\return  none
**/
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();
    
    log_init();
    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /*Start User Trimming ------------------------------------------------------*/
    status = Start_UserTrimming(&Trim_Value);
    
    if(status == SUCCESS)
    {
       log_info("User trimming passed, the triming value = 0x%x\r\n",Trim_Value);
    }
    else
    {
       log_info("User trimming failed,the triming invalid\r\n");
    }
    while (1)
    {
    }
}

/**
*\*\name    DAC_Configuratoin.
*\*\fun     Configures the DAC1 module.
*\*\return  none
**/
void DAC_Configuratoin(void)
{
   
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable GPIOA, GPIOB, GPIOC clocks */
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA | RCC_AHB_PERIPHEN_GPIOB | RCC_AHB_PERIPHEN_GPIOC, ENABLE);
    
    /* Enable DAC1 DAC2 clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_DAC12 ,ENABLE);
    /* Config DAC12 prescaler factor,DAC_CLK = 1M*/ 
    DAC_ConfigClkPrescaler(DAC12,120);

    DAC_SetHighFrequencyMode(DAC12,DAC_HIGH_FREQ_MODE_BELOW_160M);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the different GPIO ports.
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    // DAC1_OUT 
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin        = GPIO_PIN_4 ;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_ANALOG;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/**
*\*\name    Start_UserTrimming.
*\*\fun     start user trimming process for DAC1.
*\*\param   NewTrimValue :
*\*\          - the result value after user trimming.
*\*\return   ErrorStatus :
*\*\          - ERROR
*\*\          - SUCCESS
**/
ErrorStatus Start_UserTrimming(uint8_t *NewTrimValue)
{
    uint8_t index  =0;
    DAC_InitType DAC_InitStructure;

    DAC_StructInit(&DAC_InitStructure);
    /* DAC1 Configuration */
    DAC_InitStructure.DAC_Trigger                       = DAC_Trigger_Software;
    DAC_InitStructure.DAC_WaveGeneration                = DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_OutputBuffer                  = ENABLE;
    DAC_InitStructure.DAC_ConnectOnChipPeripheral       = DISABLE;
    DAC_InitStructure.DAC_ConnectExternalPin            = ENABLE;
    DAC_InitStructure.DAC_TriggerEnable                 = ENABLE;
    DAC_Init(DAC1, &DAC_InitStructure);
    /* Enable DAC1 Calibration  */
    DAC_CaliEnable(DAC1,ENABLE) ;
    /* Enable DAC1  */
    DAC_Enable(DAC1, ENABLE);

    for(index = 0;index<32;index++)
    {
        DAC_SetUserTrimming(DAC1,index) ;
        systick_delay_us(100);
        if(DAC_GetFlagSts(DAC1,DAC_FLAG_CALCOMPLETE) != RESET)
        {
             *NewTrimValue = index;
             return SUCCESS;
        }
    }
     return ERROR;
}
