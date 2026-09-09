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
#include "misc.h"
#include "log.h"
#include "n32h49x_dsmu.h"
#include "n32h49x_rcc.h"

/* Filter paramter */
#define FILTER_ORDER            (DSMU_FILTER_SINC2_ORDER)
#define FILTER_OVERSAMPLE       (16)    //must be 2^x
#define INTEGRATOR_OVERSAMPLE   (1)    //must be 2^x

/* Signal data input: BASE_DATA+DataOffset */
#define BASE_DATA           (0x0E00U)
#define MAX_DATA_OFFSET     (2000)
#define INPUT_BUF_SIZE      (sizeof(DataOffset)/2)
uint32_t InputNum;  /* Input signal data count */

/* The absolute value of each DataOffset must be less than MAX_DATA_OFFSET */
int16_t DataOffset[] = {
    10, -10, 100, -1000, 500, -500, 300, -300,
    50, -80, 200, -300, 400, -600, 200, -500,
    40, -90, 400, -600, 200, -600, 500, -500,
    80, -20, 1000, -300, 700, -200, 2000, -300,
    70, -30, 300, -500, 500, -500, 300, -600,
    20, -80, 1000, -100, 200, -200, 500, -300,
    90, -20, 300, -200, 400, -100, 600, -200,
    30, -60, 200, -400, 600, -600, 700, -2000,
};

/* Data output after filter */
#define OUTPUT_BUF_SIZE     (16)
int32_t DataOut[OUTPUT_BUF_SIZE];
uint32_t OutputBufSize = OUTPUT_BUF_SIZE;
uint32_t flag_data; /* Output data buf full */

/* Test time define */
#define TEST_CYCLE              (64)
uint32_t TestCycle;

/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    uint32_t err = 0;
    uint32_t i;
    uint32_t temp;
    uint32_t InputPosErr,InputNegErr;
    uint32_t OutputPosErr,OutputNegErr;
    
    /* Log configuration */
    log_init();
    printf("\r\n DSMU data filter demo! \r\n");
    
    /* Config DSMU  clock */
    RCC_ConfigDSMUFilterClk(RCC_DSMU_FLT_DIV2);
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_DSMU, ENABLE);
    
    /* Config DSMU channel and filter*/
    if(DSMU_Configuration() != SUCCESS)
    {
        while(1);
    }

    /* Get the jitter of input data */
    InputPosErr = 0;
    InputNegErr = 0;
    for(i=0;i<INPUT_BUF_SIZE;i++)
    {
        if(DataOffset[i] < 0)
        {
            temp = (uint32_t)(0-DataOffset[i]);
            if(temp > InputNegErr)
            {
                InputNegErr = temp;
            }
        }
        else
        {
            temp = DataOffset[i];
            if(temp > InputPosErr)
            {
                InputPosErr = temp;
            }
        }
    }
   
    InputNum = 0;
    TestCycle = 0;
    flag_data = 0;
    OutputNegErr = 0;
    OutputPosErr = 0;
    i = 0;

    while(1)
    {
        /* Input data by writting register */
        DSMU_ChannelWriteData(DSMU_Channel0,(uint32_t)(BASE_DATA+DataOffset[InputNum%INPUT_BUF_SIZE]));
        InputNum++;

        /* If output data buffer is full or not */
        if(flag_data == 0)
        {
            continue;
        }
        else
        {
            flag_data = 0;
        }
        
        /* Get the jitter of output data when buffer is full */
        for(i=0;i<16;i++)
        {
            if(DataOut[i] < BASE_DATA)
            {
                temp = BASE_DATA -((uint32_t)DataOut[i]);
                if(temp > OutputNegErr)
                {
                    OutputNegErr = temp;
                }
            }
            else
            {
                temp = ((uint32_t)DataOut[i]) - BASE_DATA;
                if(temp > OutputPosErr)
                {
                    OutputPosErr = temp;
                }
            }
        }
        
        if(TestCycle > TEST_CYCLE)
        {
            break;
        }
    }

    printf("\r\n Input data:%d +%d/-%d\r\n",BASE_DATA,InputPosErr,InputNegErr);
    printf(" Maximum input data jitter:%d\r\n",(InputPosErr>InputNegErr)?InputPosErr:InputNegErr);
    
    printf("\r\n After filter,output data:%d +%d/-%d\r\n",BASE_DATA,OutputPosErr,OutputNegErr);
    printf(" Maximum output data jitter:%d\r\n",(OutputPosErr>OutputNegErr)?OutputPosErr:OutputNegErr);
    
    if(OutputPosErr >= InputPosErr)
    {
        err |= 1U;
    }
    
    if(OutputNegErr >= InputNegErr)
    {
        err |= 2U;
    }
    
    if(err)
    {
        printf(" DSMU test fail:%d! \r\n",err);
    }
    else
    {
        printf(" DSMU data filter test OK! \r\n");
    }
    
    while (1)
    {
    }
}


/**
*\*\name    DSMU_Configuration.
*\*\param   none
*\*\return  none
**/
static ErrorStatus DSMU_Configuration(void)
{
    DSMU_Channel_InitType ChCfg;
    DSMU_Filter_InitType FilterCfg;
    NVIC_InitType NVIC_Cfg;
    uint32_t temp;
    
    /* Get total oversample rate and check input data */
    if(FILTER_ORDER == DSMU_FILTER_FASTSINC_ORDER)
    {
        temp = 2*POSITION_VAL(FILTER_OVERSAMPLE)+1;
    }
    else
    {
        temp = (FILTER_ORDER >> REG_BIT29_OFFSET)*POSITION_VAL(FILTER_OVERSAMPLE);
    }
    
    temp += POSITION_VAL(INTEGRATOR_OVERSAMPLE);
    if(BASE_DATA > ((0x7FFFFFFF - MAX_DATA_OFFSET) >> temp))    /* After oversampling by filter and integrator,input data must be in the range (-2^31)~(2^31-1) */
    {
        printf("DSMU Configuration error: data overflow after integrator\r\n");
        return ERROR;
    }
    
    if(BASE_DATA > (0x7FFFFFFF - MAX_DATA_OFFSET) )/* Finally ountput data must be in the range (-2^23)~(2^23-1) */
    {
        printf("DSMU Configuration error: input data overflow\r\n");
        return ERROR;
    }
    
    /*** Channel configuration ***/
    /* Clock output parameter */
    ChCfg.OutputClock.Activation    = DISABLE;
    ChCfg.OutputClock.Selection     = DSMU_CHANNEL_OUTPUT_CLOCK_SYSTEM;
    ChCfg.OutputClock.Divider       = 1;

    /* Input channel parameter */
    ChCfg.Input.Multiplexer = DSMU_CHANNEL_INTERNAL_REGISTER;
    ChCfg.Input.DataPacking = DSMU_CHANNEL_STANDARD_MODE;
    ChCfg.Input.Pins        = DSMU_CHANNEL_SAME_CHANNEL_PINS;

    /* Serial input parameter */
    ChCfg.SerialInterface.Type      = DSMU_CHANNEL_SPI_RISING;
    ChCfg.SerialInterface.SpiClock  = DSMU_CHANNEL_SPI_CLOCK_EXTERNAL;

    /* Analog watchdog parameter */
    ChCfg.Awd.FilterOrder   = DSMU_AWD_FASTSINC_ORDER;
    ChCfg.Awd.Oversampling  = 1;

    /* Bit shift and offset parameter */
    ChCfg.Offset = 0;
    ChCfg.RightBitShift = temp;
    
    /* Config current channel */
    DSMU_ChannelInit(DSMU_Channel0,&ChCfg);

    /*** Filter configuration ***/
    /* Regular channel parameter */
    FilterCfg.RegularParam.DmaMode = DISABLE;
    FilterCfg.RegularParam.FastMode = DISABLE;   //ENABLE
    FilterCfg.RegularParam.Trigger = DSMU_FILTER_SW_TRIGGER;

    /* Injected channel parameter */
    FilterCfg.InjectedParam.ScanMode = DISABLE;
    FilterCfg.InjectedParam.DmaMode = DISABLE;
    FilterCfg.InjectedParam.Trigger = DSMU_FILTER_SW_TRIGGER;
    FilterCfg.InjectedParam.ExtTrigger = DSMU_FILTER_EXT_TRIG_ATIM1_TRGO;

    /* Filter function parameter */
    FilterCfg.FilterParam.SincOrder = FILTER_ORDER;
    FilterCfg.FilterParam.Oversampling = FILTER_OVERSAMPLE;
    FilterCfg.FilterParam.IntOversampling = INTEGRATOR_OVERSAMPLE;

    /* Config current filter */
    DSMU_FilterInit(DSMU_Filter0, &FilterCfg );

    /* Enable regular channel in continuous mode */
    DSMU_FilterConfigRegChannel(DSMU_Filter0,DSMU_CHANNEL_SELECT_0,DSMU_CONTINUOUS_CONV_ON);
    
    /* Enable regular conversion end interrupt  */
    DSMU_ConfigInt(DSMU_Filter0,DSMU_INT_REGULAR_END, ENABLE);

    /* NVIC configuration */
    NVIC_Cfg.NVIC_IRQChannel = DSMU_FLT0_IRQn;
    NVIC_Cfg.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_Cfg.NVIC_IRQChannelSubPriority = 0;
    NVIC_Cfg.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_Cfg);
    
    /* Start regular conversion*/
    DSMU_RegConvStart(DSMU_Filter0, DSMU_FILTER_SW_TRIGGER);
    
    return SUCCESS;
}



