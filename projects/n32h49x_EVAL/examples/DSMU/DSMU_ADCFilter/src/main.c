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
#include "n32h49x_adc.h"
#include "n32h49x_gpio.h"

/* Filter paramter */
#define FILTER_ORDER            (DSMU_FILTER_SINC2_ORDER)
#define FILTER_OVERSAMPLE       (16)    //must be 2^x
#define INTEGRATOR_OVERSAMPLE   (4)     //must be 2^x

/* DSMU output data size */
#define FILTER_DATA_LENGTH      (32)

/* ADC data samples need for DSMU filter.
   If FILTER_ORDER == DSMU_FILTER_SINC2_ORDER, and DSMU_FLTxCTRL1.FAST == 0,
   samples must be at lease ((2+INTEGRATOR_OVERSAMPLE-1)*FILTER_OVERSAMPLE+2)*FILTER_DATA_LENGTH-1.
*/
#define ADC_DATA_LENGTH         (((2+INTEGRATOR_OVERSAMPLE-1)*FILTER_OVERSAMPLE+2)*FILTER_DATA_LENGTH)

/* Original ADC data */
uint16_t ADC_Data[ADC_DATA_LENGTH] = {0};
uint32_t ADC_DataCnt = 0;

/* Data after DMSU  filter */
uint16_t DataOut[FILTER_DATA_LENGTH] = {0};
uint32_t DataOutCnt = 0;

uint32_t OutputBufSize = FILTER_DATA_LENGTH;

uint32_t flag_data = 0; /* Output data buf full */


/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    uint16_t min,max;
    
    /* RCC configuration */
    RCC_Configuration();
    
    /* Log configuration */
    log_init();
    printf("\r\nDSMU ADC data filter test start! \r\n");
    
    /* Config DSMU channel and filter*/
    if(DSMU_Configuration() != SUCCESS)
    {
        while(1);
    }

    /* ADC port configuration */
    ADC_GPIO_Configuration();
    
    /* ADC configuration */
    ADC2_Initial();
    
    /* ADC start conversion */
    ADC_EnableSoftwareStartConv(ADC2, ENABLE);
    
    while(1)
    {
        /* If DSMU output data buffer is full, break loop */
        if(flag_data)
        {
            break;
        }
        
        /* Get an ADC data, and start conversion again */
        if(ADC_GetFlagStatus(ADC2, ADC_FLAG_ENDC) == SET)
        {
            ADC_ClearFlag(ADC2, ADC_FLAG_ENDC);
            ADC_ClearFlag(ADC2, ADC_FLAG_STR);
            
            ADC_Data[ADC_DataCnt] = ADC_GetDat(ADC2);
            ADC_DataCnt++;
            if(ADC_DataCnt >= ADC_DATA_LENGTH)
            {
                break;
            }
            
            ADC_EnableSoftwareStartConv(ADC2, ENABLE);
        }
    }
    
    /* Stop ADC Regular channel conversion */
    ADC_StopRegularConv(ADC2);
    
    /* Get original ADC data range */
    GetDataRange(ADC_Data,ADC_DataCnt,&max,&min);
    printf("\r\n %d ADC samples(12bit) needed before filte,range: %d -- %d\r\n",ADC_DataCnt,min,max);
    printf("\tMaximum difference of ADC sample: %d\r\n",max-min);
    
    /* Get filter data range */
    GetDataRange(DataOut,DataOutCnt,&max,&min);
    printf("\r\n Get %d data(%dbit) after filte,range: %d -- %d\r\n",DataOutCnt,12+POSITION_VAL(INTEGRATOR_OVERSAMPLE),min,max);
    printf("\tMaximum difference of filter data: %d\r\n",max-min);
    
    /* Test done */
    printf("\r\n ADC data filter by DSMU test finish! \r\n");
    
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
    
    /* Reset DSMU */
    DSMU_DeInit();
    
    /* Get total oversample rate and check input data */
    if(FILTER_ORDER == DSMU_FILTER_FASTSINC_ORDER)
    {
        temp = 2*POSITION_VAL(FILTER_OVERSAMPLE)+1;
    }
    else
    {
        temp = (FILTER_ORDER >> REG_BIT29_OFFSET)*POSITION_VAL(FILTER_OVERSAMPLE);
    }
    
    /*** Channel configuration ***/
    /* Clock output parameter */
    ChCfg.OutputClock.Activation    = DISABLE;
    ChCfg.OutputClock.Selection     = DSMU_CHANNEL_OUTPUT_CLOCK_SYSTEM;
    ChCfg.OutputClock.Divider       = 1;

    /* Input channel parameter */
    ChCfg.Input.Multiplexer = DSMU_CHANNEL_ADC_OUTPUT;
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
    DSMU_ChannelInit(DSMU_Channel1,&ChCfg);

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
    DSMU_FilterConfigRegChannel(DSMU_Filter0,DSMU_CHANNEL_SELECT_1,DSMU_CONTINUOUS_CONV_ON);
    
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

/**
*\*\name    ADC_GPIO_Configuration.
*\*\fun     Configures the GPIO ports used for ADC.
*\*\return  none
**/
void ADC_GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    
    /* Configure PA6 as analog input -----------------------*/
    GPIO_InitStructure.Pin            = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_ANALOG;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Current   = GPIO_DC_8mA;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    GPIO_InitStructure.GPIO_Alternate = GPIO_NO_AF;
    GPIO_InitPeripheral(GPIOH, &GPIO_InitStructure );
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configures peripheral clocks.
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Config DSMU clock */
    RCC_ConfigDSMUFilterClk(RCC_DSMU_FLT_DIV1);
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPHEN_DSMU, ENABLE);
    
    /* Config ADC clock */
    RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI,RCC_ADC1MCLK_DIV8);
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_ADC2,ENABLE);
    RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_ADC2);
    ADC_ConfigClk(ADC_CTRL3_CKMOD_AHB, RCC_ADCHCLK_DIV16);
    
    /* Enable GPIOH clock */
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOH, ENABLE);
    
    /* Enable AFIO clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_AFIO, ENABLE);
}

/**
*\*\name    ADC2_Initial.
*\*\fun     ADC_Initial program.
*\*\param   none
*\*\return  none
**/
void ADC2_Initial(void)
{
    ADC_InitType ADC_InitStructure;
    
    /* Reset ADC */
    ADC_DeInit(ADC2);
    
    /* ADCx configuration ------------------------------------------------------*/
    ADC_InitStructure.WorkMode         = ADC_WORKMODE_INDEPENDENT;
    ADC_InitStructure.MultiChEn        = DISABLE;
    ADC_InitStructure.ContinueConvEn   = DISABLE;
    ADC_InitStructure.ExtTrigSelect    = ADC_EXT_TRIG_REG_CONV_SOFTWARE;
    ADC_InitStructure.DatAlign         = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber        = 1;
    ADC_InitStructure.Resolution       = ADC_DATA_RES_12BIT;
    ADC_Init(ADC2, &ADC_InitStructure);

    /* Enable ADCx */
    ADC_Enable(ADC2, ENABLE);
    /*Check ADC Ready*/
    while(ADC_GetFlagStatus(ADC2,ADC_FLAG_RDY) == RESET)
        ;
    /* Start ADCx calibration */
    ADC_CalibrationOperation(ADC2, ADC_CALIBRATION_SINGLE_MODE);
    /* Check the end of ADCx calibration */
    while (ADC_GetCalibrationStatus(ADC2, ADC_CALIBRATION_SINGLE_MODE))
        ;
    
    /* ADC channel configuration */
    ADC_ConfigRegularChannel(ADC2, ADC2_Channel_17_PH3, 1, ADC_SAMP_TIME_CYCLES_28_5);
    ADC_SetAdcDSMUChannel(ADC2, ADC2_Channel_17_PH3,ENABLE);
    ADC_EnableAdcDSMU(ADC2, ENABLE);
}

/**
*\*\name    GetDataRange.
*\*\fun     Get the maximum value minimum value of some data.
*\*\param   Buf: Pointer of data buffer
*\*\param   Len: Data length
*\*\param   pMax: Pointer of maximum data
*\*\param   pMin: Pointer of minimum data
*\*\return  none
**/
void GetDataRange(uint16_t *Buf, uint32_t Len, uint16_t *pMax, uint16_t *pMin)
{
    uint32_t k;
    uint16_t min = 0xFFFFU;
    uint16_t max = 0x0000U;
    
    for(k=0; k<Len; k++)
    {
        if(Buf[k] > max)
        {
            max = Buf[k];
        }
        
        if(Buf[k] < min)
        {
            min = Buf[k];
        }
    }
    
    *pMin = min;
    *pMax = max;
}

