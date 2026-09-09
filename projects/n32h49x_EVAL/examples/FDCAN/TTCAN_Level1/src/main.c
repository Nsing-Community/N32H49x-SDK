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
#include "n32h49x_fdcan.h"
#include "log.h"
#include "misc.h"

#define MSG_RAM_SIZE            (0x300) /* Message ram size,must not be greater than 4480 */
uint32_t FDCAN_ram[MSG_RAM_SIZE];  /* Used for FDCAN message ram, shared by all FDCAN modules */

#define TEST_BUF_SIZE           (32)
#define TEST_FRAME_NUMBER       (2)
#define TEST_FRAME_DATA_SIZE    (TEST_BUF_SIZE/TEST_FRAME_NUMBER)


FDCAN_TxHeaderType TxHeader;
uint8_t TxData[TEST_BUF_SIZE] = {   0x01, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78,
                                    0x89, 0x9A, 0xAB, 0xBC, 0xCD, 0xDE, 0xEF, 0xF0,
                                    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 
                                    0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF  };

FDCAN_RxHeaderType RxHeader;
uint8_t RxBuf[TEST_FRAME_DATA_SIZE];
uint32_t TxFlag = 0;

FDCAN_MsgRamType Node1_msg,Node2_msg;


/**
 *\*\name   main.
 *\*\fun    Main program.
 *\*\param  none
 *\*\return none
 */
int main(void)
{
    uint32_t index;
    uint32_t value_cnt = 0;
    FDCAN_RxHeaderType RxHeader0;    
    FDCAN_RxHeaderType RxHeader1;
    FDCAN_TT_Status TTStatus0;
    uint8_t  RxData0[8] = {0};            
    uint8_t  RxData1[8] = {0};
    
    log_init();

    log_info("\r\n TTCAN Level1 polling demo!\r\n");

    FDCAN_clock_src_config();

    Node1_port_config();
    Node2_port_config();

    Node2_Config();
    Node1_Config();
    
    for(index=0;index<4;index++)
    {       
        if(index<2)
        {
            TxHeader.ID = 0x1AAAA754+index;                            
        }
        else
        {
            TxHeader.ID = 0x1AAAA754+0x00000030+index;                            
        }                    
        FDCAN_AddMsgToTxBuffer(NODE1, &TxHeader, &TxData[index], FDCAN_TX_BUFFER1<<index);
    }
    FDCAN_EnableTxBufferRequest(NODE1, 0x0000001E);

    while (1)
    {
        if((NODE1->TXBTO & 0x0000001A) == 0x0000001A)
        {
            FDCAN_EnableTxBufferRequest(NODE1, 0x0000001A);
        }
        
        
        FDCAN_TT_GetStatus(NODE2,&TTStatus0);
        if(TTStatus0.ErrorLevel != 0)
        {
            if(TTStatus0.ErrorLevel == 3)
            {
                printf("Severity 3- Serious Error(filter 0).\r\n");
                while(1);
            }
            else
            {
                printf("Severity 1/2- Serious Error(filter 0).\r\n");
            }
        }
        
        if(FDCAN_TT_GetFlag(NODE2,FDCAN_TT_FLAG_SCHEDULING_ERROR_1 | FDCAN_TT_FLAG_SCHEDULING_ERROR_2 | FDCAN_TT_FLAG_ERROR_LEVEL_CHANGE))
        {
            printf("Schedule type error(filter 0).\r\n");
            FDCAN_TT_ClearFlag(NODE2,FDCAN_TT_FLAG_SCHEDULING_ERROR_1 | FDCAN_TT_FLAG_SCHEDULING_ERROR_2 | FDCAN_TT_FLAG_ERROR_LEVEL_CHANGE);
        }
        if((FDCAN_GetRxFifoFillLevel(NODE2, FDCAN_RX_FIFO0)!=0))
        {
            FDCAN_GetRxMsg(NODE2, FDCAN_RX_FIFO0, &RxHeader0, RxData0);    
            if(RxHeader0.ID!=0x1AAAA754)
            {
                printf("Id type error(filter 0).\r\n");    
                while(1);                                    
            }
            
            if(RxHeader0.IdType!=FDCAN_EXTENDED_ID)
            {
                printf("Id type error(filter 0).\r\n");    
                while(1);                                    
            }
            
            if(RxHeader0.RxFrameType!=FDCAN_DATA_FRAME)
            {
                printf("Frame type error(filter 0).\r\n");            
                while(1);                                        
            }                
            
            if(RxHeader0.DataLength !=FDCAN_DLC_BYTES_8)
            {
                printf("Data length code error(filter 0).\r\n");        
                while(1);                                        
            }    
                                
            if(RxHeader0.FDFormat !=FDCAN_FD_CAN)
            {
                printf("Frame format error(filter 0).\r\n");    
                while(1);                                                
            }
            
            if(RxHeader0.BitRateSwitch !=FDCAN_BRS_ON)
            {
                printf("Bit rate switch error(filter 0).\r\n");    
                while(1);                                                
            }    
            
            if(RxHeader0.FilterIndex !=0)
            {
                printf("Filter index error(filter 0).\r\n");    
                while(1);                                        
            }                                
                            
            for(index=0;index<8;index++)
            {
                if(TxData[index]!=RxData0[index])
                {
                    printf("Data receiving error(filter 0).\r\n");        
                    while(1);                                                
                }        
                RxData0[index]=0;
            }      
        }
        
        
        if((FDCAN_GetRxFifoFillLevel(NODE2, FDCAN_RX_FIFO1)!=0))
        {
            FDCAN_GetRxMsg(NODE2, FDCAN_RX_FIFO1, &RxHeader1, RxData1);    
            if(RxHeader1.IdType!=FDCAN_EXTENDED_ID)
            {
                printf("Id type error(filter 1).\r\n");        
                while(1);                                        
            }
            
            if(RxHeader1.RxFrameType!=FDCAN_DATA_FRAME)
            {
                printf("Frame type error(filter 1).\r\n");    
                while(1);                                        
            }        
            
            if(RxHeader1.DataLength !=FDCAN_DLC_BYTES_8)
            {
                printf("Data length code error(filter 1).\r\n");    
                while(1);                                        
            }    
                    
            if(RxHeader1.FDFormat !=FDCAN_FD_CAN)
            {
                printf("Frame format error(filter 1).\r\n");    
                while(1);                                                
            }    
            
            if(RxHeader1.BitRateSwitch !=FDCAN_BRS_ON)
            {
                printf("Bit rate switch error(filter 1).\r\n");    
                while(1);                                                
            }                        
        
            if(RxHeader1.FilterIndex !=1)
            {
                printf("Filter index error(filter 1).\r\n");        
                while(1);                                        
            }                                
                            
            for(index=0;index<8;index++)
            {
                if(TxData[index+1]!=RxData1[index])
                {
                    printf("Data receiving error(filter 1).\r\n");    
                    while(1);                                                
                }        
                RxData1[index]=0;
            }                  
        }
        
        value_cnt++;
        if(value_cnt > 0x100000)
        {
            value_cnt = 0;
            printf("TTCAN Level1 Runing OK.\r\n");
        }
    }
}


/**
 *\*\name   FDCAN_clock_src_config.
 *\*\fun    Config the clock source of all FDCAN module.
 *\*\param  none
 *\*\return none
 *\*\note   FDCAN clock source should be set to one of the following values: 20M,40M,80M.
 */
void FDCAN_clock_src_config(void)
{
    /* Config  PLL prescaler for FDCAN */
    RCC_ConfigFDCANPllClk(RCC_FDCAN_PLLSRC_DIV12);

    /* Select PLL as FDCAN clock source */
    RCC_ConfigFDCANClksrc(RCC_FDCAN_CLKSRC_PLL);
}

/**
 *\*\name   Node1_port_config.
 *\*\fun    Config the GPIO used for FDCAN node 1.
 *\*\param  none
 *\*\return none
 */
void Node1_port_config(void)
{
    GPIO_InitType InitStruct;

    RCC_EnableAHB1PeriphClk(NODE1_TX_PORT_CLK|NODE1_RX_PORT_CLK,ENABLE);

    InitStruct.Pin            = NODE1_TX_PIN;
    InitStruct.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    InitStruct.GPIO_Mode      = GPIO_MODE_AF_PP;
    InitStruct.GPIO_Alternate = NODE1_TX_PIN_AF;
    InitStruct.GPIO_Pull      = GPIO_NO_PULL;
    InitStruct.GPIO_Current   = GPIO_DS_8mA;
    GPIO_InitPeripheral(NODE1_TX_PORT,&InitStruct);

    InitStruct.Pin            = NODE1_RX_PIN;
    InitStruct.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    InitStruct.GPIO_Mode      = GPIO_MODE_INPUT;
    InitStruct.GPIO_Alternate = NODE1_RX_PIN_AF;
    InitStruct.GPIO_Pull      = GPIO_PULL_UP;
    InitStruct.GPIO_Current   = GPIO_DS_8mA;
    GPIO_InitPeripheral(NODE1_RX_PORT,&InitStruct);
}

/**
 *\*\name   Node2_port_config.
 *\*\fun    Config the GPIO used for FDCAN node 2.
 *\*\param  none
 *\*\return none
 */
void Node2_port_config(void)
{
    GPIO_InitType InitStruct;

    RCC_EnableAHB1PeriphClk(NODE2_TX_PORT_CLK|NODE2_RX_PORT_CLK,ENABLE);

    InitStruct.Pin            = NODE2_TX_PIN;
    InitStruct.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    InitStruct.GPIO_Mode      = GPIO_MODE_AF_PP;
    InitStruct.GPIO_Alternate = NODE2_TX_PIN_AF;
    InitStruct.GPIO_Pull      = GPIO_NO_PULL;
    InitStruct.GPIO_Current   = GPIO_DS_8mA;
    GPIO_InitPeripheral(NODE2_TX_PORT,&InitStruct);

    InitStruct.Pin            = NODE2_RX_PIN;
    InitStruct.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    InitStruct.GPIO_Mode      = GPIO_MODE_INPUT;
    InitStruct.GPIO_Alternate = NODE2_RX_PIN_AF;
    InitStruct.GPIO_Pull      = GPIO_PULL_UP;
    InitStruct.GPIO_Current   = GPIO_DS_8mA;
    GPIO_InitPeripheral(NODE2_RX_PORT,&InitStruct);
}

/**
 *\*\name   Node1_Config.
 *\*\fun    Config FDCAN node 1.
 *\*\param  none
 *\*\return none
 */
void Node1_Config(void)
{
    FDCAN_InitType InitParam;
    FDCAN_FilterType FilterParam;
    FDCAN_TT_InitType pTTParams;
    FDCAN_TriggerType sTriggerConfig;
    
    /* Enable NODE1 clock */
    RCC_EnableAPB1PeriphClk(NODE1_PERIPH,ENABLE);

    /* Reset NODE1 register */
    RCC_EnableAPB1PeriphReset(NODE1_PERIPH);

    /** FDCAN config parameter **/
    InitParam.FrameFormat           = FDCAN_FRAME_FD_BRS;          /* Frame format */
    InitParam.Mode                  = FDCAN_MODE_NORMAL; /* Work mode */
    InitParam.Prescaler             = 1;    /* Nominal timing  */
    InitParam.SyncJumpWidth         = 8;
    InitParam.TimeSeg1              = 31;
    InitParam.TimeSeg2              = 8;
    InitParam.DataPrescaler         = 1;    /* Data timing  */
    InitParam.DataSyncJumpWidth     = 4;
    InitParam.DataTimeSeg1          = 15;
    InitParam.DataTimeSeg2          = 4;
    InitParam.MsgRamStrAddr         = (uint32_t)FDCAN_ram;   /* Msg ram start address, shared by all FDCAN modules */
    InitParam.MsgRamOffset          = 0;    /* Current NODE1 msg ram start offset  */
    InitParam.pMsgInfo              = &Node1_msg;
    InitParam.StdFilterSize         = 0;    /* Standard filter list */
    InitParam.ExtFilterSize         = 1;    /* Extended filter list */
    InitParam.RxFifo0Size           = 0;    /* Rx FIFO 0*/
    InitParam.RxFifo0DataSize       = FDCAN_DATA_BYTES_8;
    InitParam.RxFifo1Size           = 0;    /* Rx FIFO 1*/
    InitParam.RxFifo1DataSize       = FDCAN_DATA_BYTES_8;
    InitParam.RxBufferSize          = 0;    /* Dedicate Rx buffer */
    InitParam.RxBufferDataSize      = FDCAN_DATA_BYTES_8;
    InitParam.TxBufferSize          = 5;    /* Tx buffer*/
    InitParam.TxBufferDataSize      = FDCAN_DATA_BYTES_8;
    InitParam.TxFifoQueueSize       = 0;    /* Tx FIFO */
    InitParam.TxFifoQueueMode       = FDCAN_TX_FIFO_MODE;
    InitParam.TxEventSize           = 0;    /* Tx event fifo */
    InitParam.AutoRetransmission    = DISABLE;   /* Enable auto retransmission */
    InitParam.TransmitPause         = ENABLE;    /* Disable transmit pause*/
    InitParam.ProtocolException     = DISABLE;   /* Enable Protocol Exception Handling */

    /* Init NODE1 */
    FDCAN_Init(NODE1,&InitParam);
    
    /* Configure standard ID reception filter to Rx buffer 0 */
    FilterParam.IdType          = FDCAN_EXTENDED_ID;
    FilterParam.FilterIndex     = 0;
    FilterParam.FilterType      = FDCAN_FILTER_MASK;
    FilterParam.FilterConfig    = FDCAN_FILTER_TO_RXFIFO0;
    FilterParam.FilterID1       = 0x0AAAAAAA;
    FilterParam.FilterID2       = 0x00000000;
    FDCAN_ConfigFilter(NODE1,&FilterParam);
    
    FDCAN_ConfigGlobalFilter(   NODE1,
                                FDCAN_REJECT_STD,
                                FDCAN_REJECT_EXT,
                                FDCAN_REJECT_STD_REMOTE,
                                FDCAN_REJECT_EXT_REMOTE);
                                
    FDCAN_ConfigTSPrescaler(NODE1,FDCAN_TIMESTAMP_PRESC_16);
    FDCAN_Config_TS(NODE1,FDCAN_TIMESTAMP_INTERNAL);
    
    pTTParams.OperationMode = FDCAN_TT_COMMUNICATION_LEVEL1;
    pTTParams.GapEnable = FDCAN_STRICTLY_TT_OPERATION;
    pTTParams.TimeMaster = FDCAN_TT_POTENTIAL_MASTER;
    pTTParams.SyncDevLimit = 3;
    pTTParams.InitRefTrigOffset = 127;
    pTTParams.ExternalClkSync = FDCAN_TT_EXT_CLK_SYNC_ENABLE;
    pTTParams.AppWdgLimit = 0;
    pTTParams.GlobalTimeFilter = FDCAN_TT_GLOB_TIME_FILT_ENABLE;
    pTTParams.ClockCalibration = FDCAN_TT_AUTO_CLK_CALIB_ENABLE;
    pTTParams.EvtTrigPolarity = FDCAN_TT_EVT_TRIG_POL_RISING;
    pTTParams.BasicCycles = FDCAN_TT_CYCLES_PER_MATRIX_8;
    pTTParams.CycleStartSync = FDCAN_TT_NO_SYNC_PULSE;
    pTTParams.TxEnableWindow = 8;
    pTTParams.ExpTxTrigSize = 10;
    pTTParams.TURNumerator = 0x13880;     //500K:2us  FDCAN_CLK:20MHz;  1/20*40 = 2us
    pTTParams.TURDenominator = 0x7D0;
    pTTParams.TrigMemorySize = 7;
    pTTParams.StopWatchTrigSel = FDCAN_TT_STOP_WATCH_TRIGGER_0;
    pTTParams.EventTrigSel = FDCAN_TT_EVENT_TRIGGER_0;
    FDCAN_TT_Init(NODE1,&pTTParams);
    
    /* Check message ram size */
    if(Node1_msg.EndAddress > ((uint32_t)FDCAN_ram + (MSG_RAM_SIZE*4U)))
    {
        log_info("\r\n NODE1 init error:message ram is too small!\r\n");
        while(1);
    }
    
    FDCAN_TT_ConfigRefMsg(NODE1,FDCAN_EXTENDED_ID,0x15555758,FDCAN_TT_REF_MSG_NO_PAYLOAD);
    
    sTriggerConfig.TriggerIndex = 0;
    sTriggerConfig.TimeMark = 5000;
    sTriggerConfig.RepeatFactor = FDCAN_TT_REPEAT_EVERY_4TH_CYCLE;
    sTriggerConfig.StartCycle = 0;
    sTriggerConfig.TmEventInt = FDCAN_TT_TM_NO_INTERNAL_EVENT;
    sTriggerConfig.TmEventExt = FDCAN_TT_TM_NO_EXTERNAL_EVENT;
    sTriggerConfig.TriggerType = FDCAN_TT_TX_TRIGGER_SINGLE;
    sTriggerConfig.FilterType = FDCAN_EXTENDED_ID;
    sTriggerConfig.TxBufferIndex = FDCAN_TX_BUFFER1;
    sTriggerConfig.FilterIndex = 0;
    FDCAN_TT_ConfigTrigger(NODE1,&sTriggerConfig);
    
    sTriggerConfig.TriggerIndex = 1;
    sTriggerConfig.TimeMark = 10000;
    sTriggerConfig.RepeatFactor = FDCAN_TT_REPEAT_EVERY_2ND_CYCLE;
    sTriggerConfig.StartCycle = 1;
    sTriggerConfig.TmEventInt = FDCAN_TT_TM_NO_INTERNAL_EVENT;
    sTriggerConfig.TmEventExt = FDCAN_TT_TM_NO_EXTERNAL_EVENT;
    sTriggerConfig.TriggerType = FDCAN_TT_TX_TRIGGER_CONTINUOUS;
    sTriggerConfig.FilterType = FDCAN_EXTENDED_ID;
    sTriggerConfig.TxBufferIndex = FDCAN_TX_BUFFER2;
    sTriggerConfig.FilterIndex = 0;
    FDCAN_TT_ConfigTrigger(NODE1,&sTriggerConfig);
    
    sTriggerConfig.TriggerIndex = 2;
    sTriggerConfig.TimeMark = 20000;
    sTriggerConfig.RepeatFactor = FDCAN_TT_REPEAT_EVERY_4TH_CYCLE;
    sTriggerConfig.StartCycle = 2;
    sTriggerConfig.TmEventInt = FDCAN_TT_TM_NO_INTERNAL_EVENT;
    sTriggerConfig.TmEventExt = FDCAN_TT_TM_NO_EXTERNAL_EVENT;
    sTriggerConfig.TriggerType = FDCAN_TT_TX_TRIGGER_MERGED;
    sTriggerConfig.FilterType = FDCAN_EXTENDED_ID;
    sTriggerConfig.TxBufferIndex = FDCAN_TX_BUFFER3;
    sTriggerConfig.FilterIndex = 0;
    FDCAN_TT_ConfigTrigger(NODE1,&sTriggerConfig);
    
    sTriggerConfig.TriggerIndex = 3;
    sTriggerConfig.TimeMark = 20200;
    sTriggerConfig.RepeatFactor = FDCAN_TT_REPEAT_EVERY_4TH_CYCLE;
    sTriggerConfig.StartCycle = 2;
    sTriggerConfig.TmEventInt = FDCAN_TT_TM_NO_INTERNAL_EVENT;
    sTriggerConfig.TmEventExt = FDCAN_TT_TM_NO_EXTERNAL_EVENT;
    sTriggerConfig.TriggerType = FDCAN_TT_TX_TRIGGER_ARBITRATION;
    sTriggerConfig.FilterType = FDCAN_EXTENDED_ID;
    sTriggerConfig.TxBufferIndex = FDCAN_TX_BUFFER4;
    sTriggerConfig.FilterIndex = 0;
    FDCAN_TT_ConfigTrigger(NODE1,&sTriggerConfig);
    
    sTriggerConfig.TriggerIndex = 4;
    sTriggerConfig.TimeMark = 50000;
    sTriggerConfig.RepeatFactor = FDCAN_TT_REPEAT_EVERY_CYCLE;
    sTriggerConfig.StartCycle = 0;
    sTriggerConfig.TmEventInt = FDCAN_TT_TM_NO_INTERNAL_EVENT;
    sTriggerConfig.TmEventExt = FDCAN_TT_TM_NO_EXTERNAL_EVENT;
    sTriggerConfig.TriggerType = FDCAN_TT_TX_REF_TRIGGER;
    sTriggerConfig.FilterType = FDCAN_EXTENDED_ID;
    sTriggerConfig.TxBufferIndex = FDCAN_TX_BUFFER0;
    sTriggerConfig.FilterIndex = 0;
    FDCAN_TT_ConfigTrigger(NODE1,&sTriggerConfig);
    
    sTriggerConfig.TriggerIndex = 5;
    sTriggerConfig.TimeMark = 60000;
    sTriggerConfig.RepeatFactor = FDCAN_TT_REPEAT_EVERY_CYCLE;
    sTriggerConfig.StartCycle = 0;
    sTriggerConfig.TmEventInt = FDCAN_TT_TM_NO_INTERNAL_EVENT;
    sTriggerConfig.TmEventExt = FDCAN_TT_TM_NO_EXTERNAL_EVENT;
    sTriggerConfig.TriggerType = FDCAN_TT_WATCH_TRIGGER;
    sTriggerConfig.FilterType = FDCAN_EXTENDED_ID;
    sTriggerConfig.TxBufferIndex = 0;
    sTriggerConfig.FilterIndex = 0;
    FDCAN_TT_ConfigTrigger(NODE1,&sTriggerConfig);
    
    sTriggerConfig.TriggerIndex = 6;
    sTriggerConfig.TimeMark = 65000;
    sTriggerConfig.RepeatFactor = FDCAN_TT_REPEAT_EVERY_CYCLE;
    sTriggerConfig.StartCycle = 0;
    sTriggerConfig.TmEventInt = FDCAN_TT_TM_NO_INTERNAL_EVENT;
    sTriggerConfig.TmEventExt = FDCAN_TT_TM_NO_EXTERNAL_EVENT;
    sTriggerConfig.TriggerType = FDCAN_TT_END_OF_LIST;
    sTriggerConfig.FilterType = FDCAN_EXTENDED_ID;
    sTriggerConfig.TxBufferIndex = 0;
    sTriggerConfig.FilterIndex = 0;
    FDCAN_TT_ConfigTrigger(NODE1,&sTriggerConfig);
                            
    /* Start the FDCAN module */
    FDCAN_Start(NODE1);
    
    TxHeader.ID             = 0x1AAAA754;
    TxHeader.IdType         = FDCAN_EXTENDED_ID;
    TxHeader.TxFrameType    = FDCAN_DATA_FRAME;
    TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
    TxHeader.ErrorState     = FDCAN_ESI_ACTIVE;
    TxHeader.BitRateSwitch  = FDCAN_BRS_ON;
    TxHeader.FDFormat       = FDCAN_FD_CAN;
    TxHeader.TxEventFifo    = FDCAN_NO_TX_EVENTS;
    TxHeader.MsgMarker      = 0x7711;
}

/**
 *\*\name   Node2_Config.
 *\*\fun    Config FDCAN node 2.
 *\*\param  none
 *\*\return none
 */
void Node2_Config(void)
{
    FDCAN_InitType InitParam;
    FDCAN_FilterType FilterParam;
    FDCAN_TT_InitType pTTParams;
    FDCAN_TriggerType sTriggerConfig;
    
    /* Enable NODE2 clock */
    RCC_EnableAPB1PeriphClk(NODE2_PERIPH,ENABLE);

    /* Reset NODE2 register */
    RCC_EnableAPB1PeriphReset(NODE2_PERIPH);

    /** FDCAN config parameter **/
    InitParam.FrameFormat           = FDCAN_FRAME_FD_BRS;          /* Frame format */
    InitParam.Mode                  = FDCAN_MODE_NORMAL; /* Work mode */
    InitParam.Prescaler             = 1;    /* Nominal timing  */
    InitParam.SyncJumpWidth         = 8;
    InitParam.TimeSeg1              = 31;
    InitParam.TimeSeg2              = 8;
    InitParam.DataPrescaler         = 1;    /* Data timing  */
    InitParam.DataSyncJumpWidth     = 4;
    InitParam.DataTimeSeg1          = 15;
    InitParam.DataTimeSeg2          = 4;
    InitParam.MsgRamStrAddr         = (uint32_t)FDCAN_ram;   /* Msg ram start address, shared by all FDCAN modules */
    InitParam.MsgRamOffset          = 0x100;    /* Current NODE2 msg ram start offset  */
    InitParam.pMsgInfo              = &Node2_msg;
    InitParam.StdFilterSize         = 0;    /* Standard filter list */
    InitParam.ExtFilterSize         = 2;    /* Extended filter list */
    InitParam.RxFifo0Size           = 2;    /* Rx FIFO 0*/
    InitParam.RxFifo0DataSize       = FDCAN_DATA_BYTES_8;
    InitParam.RxFifo1Size           = 2;    /* Rx FIFO 1*/
    InitParam.RxFifo1DataSize       = FDCAN_DATA_BYTES_8;
    InitParam.RxBufferSize          = 0;    /* Dedicate Rx buffer */
    InitParam.RxBufferDataSize      = FDCAN_DATA_BYTES_8;
    InitParam.TxBufferSize          = 0;    /* Tx buffer*/
    InitParam.TxBufferDataSize      = FDCAN_DATA_BYTES_8;
    InitParam.TxFifoQueueSize       = 0;    /* Tx FIFO */
    InitParam.TxFifoQueueMode       = FDCAN_TX_FIFO_MODE;
    InitParam.TxEventSize           = 0;    /* Tx event fifo */
    InitParam.AutoRetransmission    = DISABLE;   /* Enable auto retransmission */
    InitParam.TransmitPause         = ENABLE;    /* Disable transmit pause*/
    InitParam.ProtocolException     = DISABLE;   /* Enable Protocol Exception Handling */

    /* Init NODE2 */
    FDCAN_Init(NODE2,&InitParam);
    
    /* Configure standard ID reception filter to Rxfifo 1 */
    FilterParam.IdType          = FDCAN_EXTENDED_ID;
    FilterParam.FilterIndex     = 0;
    FilterParam.FilterType      = FDCAN_FILTER_MASK;
    FilterParam.FilterConfig    = FDCAN_FILTER_TO_RXFIFO0;
    FilterParam.FilterID1       = 0x1AAAA754;
    FilterParam.FilterID2       = 0x1FFFFFFF;
    FDCAN_ConfigFilter(NODE2,&FilterParam);
    
    FilterParam.IdType          = FDCAN_EXTENDED_ID;
    FilterParam.FilterIndex     = 1;
    FilterParam.FilterType      = FDCAN_FILTER_MASK;
    FilterParam.FilterConfig    = FDCAN_FILTER_TO_RXFIFO1;
    FilterParam.FilterID1       = 0x1AAAA755;
    FilterParam.FilterID2       = 0x1FFFFFFF;
    FDCAN_ConfigFilter(NODE2,&FilterParam);
  
    FDCAN_ConfigGlobalFilter(   NODE2,
                                FDCAN_REJECT_STD,
                                FDCAN_REJECT_EXT,
                                FDCAN_REJECT_STD_REMOTE,
                                FDCAN_REJECT_EXT_REMOTE);
                                
    FDCAN_ConfigTSPrescaler(NODE2,FDCAN_TIMESTAMP_PRESC_16);
    FDCAN_Config_TS(NODE2,FDCAN_TIMESTAMP_INTERNAL);
    
    pTTParams.OperationMode = FDCAN_TT_COMMUNICATION_LEVEL1;
    pTTParams.GapEnable = FDCAN_STRICTLY_TT_OPERATION;
    pTTParams.TimeMaster = FDCAN_TT_SLAVE;
    pTTParams.SyncDevLimit = 3;
    pTTParams.InitRefTrigOffset = 127;
    pTTParams.ExternalClkSync = FDCAN_TT_EXT_CLK_SYNC_ENABLE;
    pTTParams.AppWdgLimit = 0;
    pTTParams.GlobalTimeFilter = FDCAN_TT_GLOB_TIME_FILT_ENABLE;
    pTTParams.ClockCalibration = FDCAN_TT_AUTO_CLK_CALIB_ENABLE;
    pTTParams.EvtTrigPolarity = FDCAN_TT_EVT_TRIG_POL_RISING;
    pTTParams.BasicCycles = FDCAN_TT_CYCLES_PER_MATRIX_8;
    pTTParams.CycleStartSync = FDCAN_TT_NO_SYNC_PULSE;
    pTTParams.TxEnableWindow = 8;
    pTTParams.ExpTxTrigSize = 0;
    pTTParams.TURNumerator = 0x13880;     //500K:2us  FDCAN_CLK:20MHz;  1/20*40 = 2us
    pTTParams.TURDenominator = 0x7D0;
    pTTParams.TrigMemorySize = 3;
    pTTParams.StopWatchTrigSel = FDCAN_TT_STOP_WATCH_TRIGGER_0;
    pTTParams.EventTrigSel = FDCAN_TT_EVENT_TRIGGER_0;
    FDCAN_TT_Init(NODE2,&pTTParams);
    
    /* Check message ram size */
    if(Node2_msg.EndAddress > ((uint32_t)FDCAN_ram + (MSG_RAM_SIZE*4U)))
    {
        log_info("\r\n NODE2 init error:message ram is too small!\r\n");
        while(1);
    }
    
    FDCAN_TT_ConfigRefMsg(NODE2,FDCAN_EXTENDED_ID,0x15555758,FDCAN_TT_REF_MSG_NO_PAYLOAD);
    
    sTriggerConfig.TriggerIndex = 0;
    sTriggerConfig.TimeMark = 6000;
    sTriggerConfig.RepeatFactor = FDCAN_TT_REPEAT_EVERY_4TH_CYCLE;
    sTriggerConfig.StartCycle = 0;
    sTriggerConfig.TmEventInt = FDCAN_TT_TM_NO_INTERNAL_EVENT;
    sTriggerConfig.TmEventExt = FDCAN_TT_TM_NO_EXTERNAL_EVENT;
    sTriggerConfig.TriggerType = FDCAN_TT_RX_TRIGGER;
    sTriggerConfig.FilterType = FDCAN_EXTENDED_ID;
    sTriggerConfig.TxBufferIndex = FDCAN_TX_BUFFER0;
    sTriggerConfig.FilterIndex = 0;
    FDCAN_TT_ConfigTrigger(NODE2,&sTriggerConfig);
    
    sTriggerConfig.TriggerIndex = 1;
    sTriggerConfig.TimeMark = 11000;
    sTriggerConfig.RepeatFactor = FDCAN_TT_REPEAT_EVERY_2ND_CYCLE;
    sTriggerConfig.StartCycle = 1;
    sTriggerConfig.TmEventInt = FDCAN_TT_TM_NO_INTERNAL_EVENT;
    sTriggerConfig.TmEventExt = FDCAN_TT_TM_NO_EXTERNAL_EVENT;
    sTriggerConfig.TriggerType = FDCAN_TT_RX_TRIGGER;
    sTriggerConfig.FilterType = FDCAN_EXTENDED_ID;
    sTriggerConfig.TxBufferIndex = FDCAN_TX_BUFFER0;
    sTriggerConfig.FilterIndex = 1;
    FDCAN_TT_ConfigTrigger(NODE2,&sTriggerConfig);
    
    sTriggerConfig.TriggerIndex = 2;
    sTriggerConfig.TimeMark = 60000;
    sTriggerConfig.RepeatFactor = FDCAN_TT_REPEAT_EVERY_CYCLE;
    sTriggerConfig.StartCycle = 0;
    sTriggerConfig.TmEventInt = FDCAN_TT_TM_NO_INTERNAL_EVENT;
    sTriggerConfig.TmEventExt = FDCAN_TT_TM_NO_EXTERNAL_EVENT;
    sTriggerConfig.TriggerType = FDCAN_TT_WATCH_TRIGGER;
    sTriggerConfig.FilterType = FDCAN_EXTENDED_ID;
    sTriggerConfig.TxBufferIndex = FDCAN_TX_BUFFER0;
    sTriggerConfig.FilterIndex = 1;
    FDCAN_TT_ConfigTrigger(NODE2,&sTriggerConfig);
    
    /* Start the FDCAN module */
    FDCAN_Start(NODE2);
}
