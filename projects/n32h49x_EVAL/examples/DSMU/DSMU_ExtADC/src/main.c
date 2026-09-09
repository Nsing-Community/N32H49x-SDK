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
#include "n32h49x_dma.h"

/* Filter paramter for AD7402 15bit output:
    Data bits=3*log2(32)=15bits,
    and addtional 1 sign bit    */
#define FILTER_ORDER            (DSMU_FILTER_SINC3_ORDER)
#define FILTER_OVERSAMPLE       (32)    //must be 2^x
#define INTEGRATOR_OVERSAMPLE   (1)     //must be 2^x

/* Data offset define to get 16-bit sign data */
#define FILTER_DATA_OFFSET      (0)

/* DSMU output data size */
#define FILTER_DATA_LENGTH      (128)

/* Data after DMSU  filter */
int32_t DataOut[FILTER_DATA_LENGTH] = {0};
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
    uint32_t i;
    uint32_t temp;
    
    /* RCC configuration */
    RCC_Configuration();
    
    /* NVIC configuration for DMA */
    DMA_NVIC_Config();
    
    /* Log configuration */
    log_init();
    printf("\r\nDSMU External Sigma-Delta ADC data filter test start! \r\n");
    
    /* DMA configuration */
    DSMU_DMA_Read_Config(DataOut,FILTER_DATA_LENGTH);
    
    /* DSMU port configuration */
    DSMU_GPIO_Configuration();
    
    /* Config DSMU channel and filter*/
    if(DSMU_Configuration() != SUCCESS)
    {
        while(1);
    }

    /* Wait until DSMU output data buffer is full */
    while(0 == flag_data)
    {
        
    }

    /* Show result */
    printf("\r\nFilter data:\r\n");
    for(i = 0; i < FILTER_DATA_LENGTH; i++) 
    {
        /* Data from DMA is register value, need convertion */
        temp = (uint32_t)DataOut[i] & DSMU_FLTXRDAT_RDAT;
        printf("%6d  ",(int)temp/256);
        if(((i+1)%8) == 0)
        {
            printf("\r\n");
        }
    }
    
    /* Test done */
    printf("\r\n External Sigma-Delta ADC data filter by DSMU test finish! \r\n");
    
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
    
    /* Reset DSMU */
    DSMU_DeInit();
    
    /*** Channel configuration ***/
    /* Clock output parameter */
    ChCfg.OutputClock.Activation    = ENABLE;
    ChCfg.OutputClock.Selection     = DSMU_CHANNEL_OUTPUT_CLOCK_SYSTEM;
    ChCfg.OutputClock.Divider       = 12;

    /* Input channel parameter */
    ChCfg.Input.Multiplexer = DSMU_CHANNEL_EXTERNAL_INPUTS;
    ChCfg.Input.DataPacking = DSMU_CHANNEL_STANDARD_MODE;
    ChCfg.Input.Pins        = DSMU_CHANNEL_SAME_CHANNEL_PINS;

    /* Serial input parameter */
    ChCfg.SerialInterface.Type      = DSMU_CHANNEL_SPI_FALLING;
    ChCfg.SerialInterface.SpiClock  = DSMU_CHANNEL_SPI_CLOCK_INTERNAL;

    /* Analog watchdog parameter */
    ChCfg.Awd.FilterOrder   = DSMU_AWD_FASTSINC_ORDER;
    ChCfg.Awd.Oversampling  = 1;

    /* Bit shift and offset parameter */
    ChCfg.Offset = 0;
    ChCfg.RightBitShift = FILTER_DATA_OFFSET;
    
    /* Config current channel */
    DSMU_ChannelInit(DSMU_Channel4,&ChCfg);

    /*** Filter configuration ***/
    /* Regular channel parameter */
    FilterCfg.RegularParam.DmaMode = ENABLE;
    FilterCfg.RegularParam.FastMode = DISABLE;
    FilterCfg.RegularParam.Trigger = DSMU_FILTER_SW_TRIGGER;

    /* Injected channel parameter */
    FilterCfg.InjectedParam.ScanMode = DISABLE;
    FilterCfg.InjectedParam.DmaMode = DISABLE;
    FilterCfg.InjectedParam.Trigger = DSMU_FILTER_SW_TRIGGER;
    FilterCfg.InjectedParam.ExtTrigger = DSMU_FILTER_EXT_TRIG_NONE;

    /* Filter function parameter */
    FilterCfg.FilterParam.SincOrder = FILTER_ORDER;
    FilterCfg.FilterParam.Oversampling = FILTER_OVERSAMPLE;
    FilterCfg.FilterParam.IntOversampling = INTEGRATOR_OVERSAMPLE;

    /* Config current filter */
    DSMU_FilterInit(DSMU_Filter0, &FilterCfg );

    /* Enable regular channel in continuous mode */
    DSMU_FilterConfigRegChannel(DSMU_Filter0,DSMU_CHANNEL_SELECT_4,DSMU_CONTINUOUS_CONV_ON);
    
    /* Start regular conversion*/
    DSMU_RegConvStart(DSMU_Filter0, DSMU_FILTER_SW_TRIGGER);

    return SUCCESS;
}

/**
*\*\name    DSMU_GPIO_Configuration.
*\*\fun     Configures the GPIO ports used for DSMU.
*\*\return  none
**/
void DSMU_GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    
    /* Configure PD3 as alternate output fuction DSMU_CKOUT */
    GPIO_InitStructure.Pin            = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Current   = GPIO_DC_2mA;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_SLOW;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF_DSMU_CKOUT_PD3;
    GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure );
    
    /* Configure PD7 as input mode with alternate fuction DSMU_DATIN4 */
    GPIO_InitStructure.Pin            = GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF_DSMU_DATIN4_PD7;
    GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure );
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
    
    /* Enable DMA1, DMAMUX1 clock */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_DMA1, ENABLE);
    
    /* Enable GPIOD clock */
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOD, ENABLE);
    
    /* Enable AFIO clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_AFIO, ENABLE);
}

/**
*\*\name    DMA_NVIC_Config.
*\*\fun     NVIC configuration for DMA.
*\*\param   none
*\*\return  none
**/
void DMA_NVIC_Config(void)
{
    NVIC_InitType NVIC_Cfg;
    
    /* NVIC config for DMA1 channel1 */
    NVIC_Cfg.NVIC_IRQChannel                   = DMA1_Channel1_IRQn;
    NVIC_Cfg.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_Cfg.NVIC_IRQChannelSubPriority        = 0x01;
    NVIC_Cfg.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_Cfg);
}

/**
*\*\name    DSMU_DMA_Read_Config.
*\*\fun     DMA configuration for DSMU read.
*\*\param   DstAddr :
*\*\          - Destination Addresses.
*\*\param   DataLen :
*\*\          - Length of data.
*\*\return  none
**/
void DSMU_DMA_Read_Config(int32_t *DstAddr, uint32_t DataLen)
{
    DMA_InitType DMA_Cfg;
    
    /* Reset DMA1 channel 1*/
    DMA_DeInit(DMA1_CH1);
    /* Selcect DMA request as DSMU filter 0 */
    DMA_RequestRemap(DMA_REMAP_DSMU_FILT0,DMA1_CH1,ENABLE);
    
    /* Config channel 0 */
    DMA_Cfg.PeriphAddr     = (uint32_t)(&(DSMU_Filter0->FLTRDATA));
    DMA_Cfg.MemAddr        = (uint32_t)DstAddr;
    DMA_Cfg.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_Cfg.BufSize        = DataLen;
    DMA_Cfg.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_Cfg.MemoryInc      = DMA_MEM_INC_ENABLE;
    DMA_Cfg.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_WORD;
    DMA_Cfg.MemDataSize    = DMA_MEM_DATA_WIDTH_WORD;
    DMA_Cfg.CircularMode   = DMA_MODE_NORMAL;
    DMA_Cfg.Priority       = DMA_PRIORITY_HIGH;
    DMA_Cfg.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Cfg.BurstCmd   = DMA_BURST_DISABLE;
    DMA_Cfg.BurstMode     = DMA_BURST_MODE_ALMOST;
    DMA_Cfg.BurstLen      = DMA_BURST_LEN_SINGLE;
    DMA_Init(DMA1_CH1, &DMA_Cfg);

    DMA_ConfigInt(DMA1_CH1,DMA_INT_TXC,ENABLE);
    DMA_EnableChannel(DMA1_CH1, ENABLE);
}



