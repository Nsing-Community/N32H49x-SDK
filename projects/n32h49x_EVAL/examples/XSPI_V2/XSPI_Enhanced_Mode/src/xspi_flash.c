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

#include "misc.h"
#include "xspi_flash.h"
#include "n32h49x_dma.h"
#include "n32h49x_gpio.h"
#include "n32h49x_rcc.h"

extern volatile uint32_t rSize;


/**
*\*\name    NVIC_Initialize.
*\*\fun     NVIC Initialize.
*\*\param   none
*\*\return  none
**/
static void NVIC_Initialize(void)
{
    NVIC_InitType NVIC_InitStruct;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStruct.NVIC_IRQChannel                   = XSPI_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\param   none
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Clock enable */
    RCC_EnableAHB1PeriphClk(XSPI_FLASH_NSS0_CLK| XSPI_FLASH_SCK_CLK | XSPI_FLASH_D0_CLK |
                            XSPI_FLASH_D1_CLK | XSPI_FLASH_D2_CLK | XSPI_FLASH_D3_CLK, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_AFIO,ENABLE);
    
    /* XSPI clock enable */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_XSPI | RCC_AHB_PERIPHEN_DMA1, ENABLE);
}


/**
*\*\name    Hardware_Configuration.
*\*\fun     Configures the different GPIO ports.
*\*\param   none
*\*\return  none
**/
void Hardware_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Clock Configuration */
    RCC_Configuration();
    
    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);
    /* Confugure NSS0 pins */   
    GPIO_InitStructure.Pin            = XSPI_FLASH_NSS0_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SR_SLOW_SLEW;
    GPIO_InitStructure.GPIO_Alternate = XSPI_FLASH_NSS0_AF;
    GPIO_InitStructure.GPIO_Current   = GPIO_DC_12mA;
    GPIO_InitPeripheral(XSPI_FLASH_NSS0_PORT, &GPIO_InitStructure);
            
    /* Confugure SCK pin  */
    GPIO_InitStructure.Pin            = XSPI_FLASH_SCK_PIN;
    GPIO_InitStructure.GPIO_Alternate = XSPI_FLASH_SCK_AF;
    GPIO_InitPeripheral(XSPI_FLASH_SCK_PORT, &GPIO_InitStructure);

    /* Confugure D0 pin  */
    GPIO_InitStructure.Pin            = XSPI_FLASH_D0_PIN;
    GPIO_InitStructure.GPIO_Alternate = XSPI_FLASH_D0_AF;
    GPIO_InitPeripheral(XSPI_FLASH_D0_PORT, &GPIO_InitStructure);
    
    /* Confugure D1 pin  */
    GPIO_InitStructure.Pin            = XSPI_FLASH_D1_PIN;
    GPIO_InitStructure.GPIO_Alternate = XSPI_FLASH_D1_AF;
    GPIO_InitPeripheral(XSPI_FLASH_D1_PORT, &GPIO_InitStructure);
    
    /* Confugure D2 pin  */
    GPIO_InitStructure.Pin            = XSPI_FLASH_D2_PIN;
    GPIO_InitStructure.GPIO_Alternate = XSPI_FLASH_D2_AF;
    GPIO_InitPeripheral(XSPI_FLASH_D2_PORT, &GPIO_InitStructure);
    
    /* Confugure D3 pin  */
    GPIO_InitStructure.Pin            = XSPI_FLASH_D3_PIN;
    GPIO_InitStructure.GPIO_Alternate = XSPI_FLASH_D3_AF;
    GPIO_InitPeripheral(XSPI_FLASH_D3_PORT, &GPIO_InitStructure);
}


/**
*\*\name    GPIO_HD_WP_Configuration.
*\*\fun     Configures Flash HD WP GPIO and set high.
*\*\param   none
*\*\return  none
**/
void GPIO_HD_WP_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);

    /* Confugure IO2 WP pin  */
    GPIO_InitStructure.Pin            = XSPI_FLASH_D2_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SR_SLOW_SLEW;
    GPIO_InitStructure.GPIO_Alternate = GPIO_NO_AF;
    GPIO_InitStructure.GPIO_Current   = GPIO_DC_12mA;
    GPIO_InitPeripheral(XSPI_FLASH_D2_PORT, &GPIO_InitStructure);
    
    /* Confugure IO3 HD pin  */
    GPIO_InitStructure.Pin            = XSPI_FLASH_D3_PIN;
    GPIO_InitPeripheral(XSPI_FLASH_D3_PORT, &GPIO_InitStructure);
    
    GPIO_WriteBits(XSPI_FLASH_D2_PORT, XSPI_FLASH_D2_PIN, Bit_SET);
    GPIO_WriteBits(XSPI_FLASH_D3_PORT, XSPI_FLASH_D3_PIN, Bit_SET);
}


/**
*\*\name    DMA_Configuration.
*\*\fun     Configures DMA.
*\*\param   PeripheralAddr
*\*\param   MemoryAddr
*\*\param   Len
*\*\param   TxRx
*\*\param   NewState
*\*\return  none
**/
void DMA_Configuration(uint32_t PeripheralAddr, uint32_t MemoryAddr, uint16_t Len, uint8_t TxRx, FunctionalState NewState)
{
    DMA_InitType  DMA_InitStructure;
    DMA_ChannelType* DMAy_Channelx;
    uint32_t DMA_Direction;
    uint32_t DMA_RemapNum = 0;

    if (TxRx == DMA_TX)/*DMA tx*/
    {
        DMAy_Channelx  = DMA1_CH1;
        DMA_Direction = DMA_DIR_PERIPH_DST;
        DMA_RemapNum = DMA_REMAP_XSPI_TX;/*DMA remap*/
    }
    else if (TxRx == DMA_RX)/*DMA rx*/
    {
        DMAy_Channelx = DMA1_CH2;
        DMA_Direction = DMA_DIR_PERIPH_SRC;
        DMA_RemapNum = DMA_REMAP_XSPI_RX;/*DMA remap*/
    }

    DMA_DeInit(DMAy_Channelx);
    DMA_StructInit(&DMA_InitStructure);
    /* config DMA channel*/
    DMA_InitStructure.PeriphAddr     = PeripheralAddr;
    DMA_InitStructure.MemAddr        = MemoryAddr;
    DMA_InitStructure.Direction      = DMA_Direction;
    DMA_InitStructure.BufSize        = Len;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.MemoryInc      = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_WORD;
    DMA_InitStructure.MemDataSize    = DMA_MEM_DATA_WIDTH_WORD;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_InitStructure.BurstCmd   = DMA_BURST_ENABLE;
    DMA_InitStructure.BurstMode     = DMA_BURST_MODE_ALMOST;    
    DMA_InitStructure.BurstLen      = DMA_BURST_LEN_8;   
    DMA_Init(DMAy_Channelx, &DMA_InitStructure);

    DMA_RequestRemap(DMA_RemapNum, DMAy_Channelx, NewState);		

    /* enable DMA channel*/
    DMA_EnableChannel(DMAy_Channelx, NewState);
}


/**
*\*\name    XSPI_Standard_Mode_Config.
*\*\fun     Configures XSPI Standard Mode.
*\*\param   DataFrameSize
*\*\          - XSPI_FRAME_SIZE_4_BIT
*\*\          - XSPI_FRAME_SIZE_5_BIT
*\*\          - XSPI_FRAME_SIZE_6_BIT
*\*\          - XSPI_FRAME_SIZE_7_BIT
*\*\          - XSPI_FRAME_SIZE_8_BIT
*\*\          - XSPI_FRAME_SIZE_9_BIT
*\*\          - XSPI_FRAME_SIZE_10_BIT
*\*\          - XSPI_FRAME_SIZE_11_BIT
*\*\          - XSPI_FRAME_SIZE_12_BIT
*\*\          - XSPI_FRAME_SIZE_13_BIT
*\*\          - XSPI_FRAME_SIZE_14_BIT
*\*\          - XSPI_FRAME_SIZE_15_BIT
*\*\          - XSPI_FRAME_SIZE_16_BIT
*\*\          - XSPI_FRAME_SIZE_17_BIT
*\*\          - XSPI_FRAME_SIZE_18_BIT
*\*\          - XSPI_FRAME_SIZE_19_BIT
*\*\          - XSPI_FRAME_SIZE_20_BIT
*\*\          - XSPI_FRAME_SIZE_21_BIT
*\*\          - XSPI_FRAME_SIZE_22_BIT
*\*\          - XSPI_FRAME_SIZE_23_BIT
*\*\          - XSPI_FRAME_SIZE_24_BIT
*\*\          - XSPI_FRAME_SIZE_25_BIT
*\*\          - XSPI_FRAME_SIZE_26_BIT
*\*\          - XSPI_FRAME_SIZE_27_BIT
*\*\          - XSPI_FRAME_SIZE_28_BIT
*\*\          - XSPI_FRAME_SIZE_29_BIT
*\*\          - XSPI_FRAME_SIZE_30_BIT
*\*\          - XSPI_FRAME_SIZE_31_BIT
*\*\          - XSPI_FRAME_SIZE_32_BIT
*\*\param   TransferMode
*\*\          - XSPI_TX_AND_RX_MODE
*\*\          - XSPI_TX_ONLY_MODE
*\*\          - XSPI_RX_ONLY_MODE
*\*\          - XSPI_EEPROM_READ_MODE
*\*\param   Baudr
*\*\          - Any even number between 2 and 65534
*\*\return  none
**/
void XSPI_Standard_Mode_Config(uint32_t DataFrameSize, uint32_t TransferMode, uint32_t Baudr)
{
    XSPI_InitType StandInitStruct;

    XSPI_Enable(XSPI, DISABLE);

    XSPI_StructBaseInit(&StandInitStruct);

    StandInitStruct.Role            = XSPI_MASTER_ROLE;
    StandInitStruct.DataFrameSize   = DataFrameSize;
    StandInitStruct.SCPH            = XSPI_SCPH_FIRST_EDGE;
    StandInitStruct.SCPOL           = XSPI_SCPOL_LOW_LEVEL;
    StandInitStruct.TransferMode    = TransferMode;
    StandInitStruct.Baudr           = Baudr; 
    StandInitStruct.NssToggle       = XSPI_NSS_TOGGLE_DISABLE;
    StandInitStruct.RxdSamplingEdge = XSPI_RXD_HCLK_RISING_SAMPLING;
    StandInitStruct.RxdSampleDelay  = Baudr / 2;
    XSPI_InitBase(XSPI, &StandInitStruct);

    XSPI_Slave_Select(XSPI, XSPI_SELECT_SLAVE_1);
}


/**
*\*\name    XSPI_Standard_Mode_Config.
*\*\fun     Configures XSPI Standard Mode.
*\*\param   DataFrameSize
*\*\          - XSPI_FRAME_SIZE_4_BIT
*\*\          - XSPI_FRAME_SIZE_5_BIT
*\*\          - XSPI_FRAME_SIZE_6_BIT
*\*\          - XSPI_FRAME_SIZE_7_BIT
*\*\          - XSPI_FRAME_SIZE_8_BIT
*\*\          - XSPI_FRAME_SIZE_9_BIT
*\*\          - XSPI_FRAME_SIZE_10_BIT
*\*\          - XSPI_FRAME_SIZE_11_BIT
*\*\          - XSPI_FRAME_SIZE_12_BIT
*\*\          - XSPI_FRAME_SIZE_13_BIT
*\*\          - XSPI_FRAME_SIZE_14_BIT
*\*\          - XSPI_FRAME_SIZE_15_BIT
*\*\          - XSPI_FRAME_SIZE_16_BIT
*\*\          - XSPI_FRAME_SIZE_17_BIT
*\*\          - XSPI_FRAME_SIZE_18_BIT
*\*\          - XSPI_FRAME_SIZE_19_BIT
*\*\          - XSPI_FRAME_SIZE_20_BIT
*\*\          - XSPI_FRAME_SIZE_21_BIT
*\*\          - XSPI_FRAME_SIZE_22_BIT
*\*\          - XSPI_FRAME_SIZE_23_BIT
*\*\          - XSPI_FRAME_SIZE_24_BIT
*\*\          - XSPI_FRAME_SIZE_25_BIT
*\*\          - XSPI_FRAME_SIZE_26_BIT
*\*\          - XSPI_FRAME_SIZE_27_BIT
*\*\          - XSPI_FRAME_SIZE_28_BIT
*\*\          - XSPI_FRAME_SIZE_29_BIT
*\*\          - XSPI_FRAME_SIZE_30_BIT
*\*\          - XSPI_FRAME_SIZE_31_BIT
*\*\          - XSPI_FRAME_SIZE_32_BIT
*\*\param   TransferMode
*\*\          - XSPI_TX_ONLY_MODE
*\*\          - XSPI_RX_ONLY_MODE
*\*\param   FrameFormat
*\*\          - XSPI_DUAL_LINE_MODE  
*\*\          - XSPI_QUAD_LINE_MODE 
*\*\          - XSPI_OCTAL_LINE_MODE 
*\*\param   TransferType
*\*\          - XSPI_INST_ADDR_SINGLE_LINE
*\*\          - XSPI_INST_SINGLE_LINE_ADDR_MULTI_LINE
*\*\          - XSPI_INST_ADDR_MULTI_LINE
*\*\param   Baudr
*\*\          - Any even number between 2 and 65534
*\*\param   WaitCycles
*\*\          - XSPI_WAIT_0_CYCLES
*\*\          - XSPI_WAIT_1_CYCLES
*\*\          - XSPI_WAIT_2_CYCLES
*\*\          - XSPI_WAIT_3_CYCLES
*\*\          - XSPI_WAIT_4_CYCLES
*\*\          - XSPI_WAIT_5_CYCLES
*\*\          - XSPI_WAIT_6_CYCLES
*\*\          - XSPI_WAIT_7_CYCLES
*\*\          - XSPI_WAIT_8_CYCLES
*\*\          - XSPI_WAIT_9_CYCLES
*\*\          - XSPI_WAIT_10_CYCLES
*\*\          - XSPI_WAIT_11_CYCLES
*\*\          - XSPI_WAIT_12_CYCLES
*\*\          - XSPI_WAIT_13_CYCLES
*\*\          - XSPI_WAIT_14_CYCLES
*\*\          - XSPI_WAIT_15_CYCLES
*\*\          - XSPI_WAIT_16_CYCLES
*\*\          - XSPI_WAIT_17_CYCLES
*\*\          - XSPI_WAIT_18_CYCLES
*\*\          - XSPI_WAIT_19_CYCLES
*\*\          - XSPI_WAIT_20_CYCLES
*\*\          - XSPI_WAIT_21_CYCLES
*\*\          - XSPI_WAIT_22_CYCLES
*\*\          - XSPI_WAIT_23_CYCLES
*\*\          - XSPI_WAIT_24_CYCLES
*\*\          - XSPI_WAIT_25_CYCLES
*\*\          - XSPI_WAIT_26_CYCLES
*\*\          - XSPI_WAIT_27_CYCLES
*\*\          - XSPI_WAIT_28_CYCLES
*\*\          - XSPI_WAIT_29_CYCLES
*\*\          - XSPI_WAIT_30_CYCLES
*\*\          - XSPI_WAIT_31_CYCLES
*\*\          - XSPI_WAIT_32_CYCLES
*\*\return  none
**/
void XSPI_Enhanced_Mode_Config(uint32_t DataFrameSize, uint32_t TransferMode, uint32_t FrameFormat, uint32_t TransferType, uint32_t Baudr, uint32_t WaitCycles)
{
    XSPI_EnhancedInitType  EnhancedInitStruct;

    XSPI_Enable(XSPI, DISABLE);

    XSPI_InitEnhancedStruct(&EnhancedInitStruct);

    EnhancedInitStruct.SCPH            = XSPI_SCPH_FIRST_EDGE;
    EnhancedInitStruct.SCPOL           = XSPI_SCPOL_LOW_LEVEL;
    EnhancedInitStruct.FrameFormat     = FrameFormat;
    EnhancedInitStruct.DataFrameSize   = DataFrameSize;
    EnhancedInitStruct.TransferMode    = TransferMode;
    EnhancedInitStruct.Baudr           = Baudr;
    EnhancedInitStruct.RxdSamplingEdge = XSPI_RXD_HCLK_RISING_SAMPLING;
    EnhancedInitStruct.RxdSampleDelay  = 3U;

    EnhancedInitStruct.TransferType    = TransferType;
    EnhancedInitStruct.AddrLen         = XSPI_ADDR_LEN_24BIT;
    EnhancedInitStruct.InstructLen     = XSPI_INST_LEN_8BIT;
    EnhancedInitStruct.WaitCycles      = WaitCycles;
    EnhancedInitStruct.ClockStrech     = XSPI_CLOCK_STRETCH_ENABLE;
    EnhancedInitStruct.DDREable        = XSPI_DDR_DISABLE;

    XSPI_InitEnhanced(XSPI, &EnhancedInitStruct);

    XSPI_Slave_Select(XSPI, XSPI_SELECT_SLAVE_1);
}


/**
*\*\name    XSPI_Waie_Tx_Compelete.
*\*\fun     Waie Tx Compelete.
*\*\param   none
*\*\return  none
**/
void XSPI_Waie_Tx_Compelete(void)
{
    while (XSPI_GetFlagStatus(XSPI, XSPI_TXFE_FLAG) != SET)
    {
    }

    while (XSPI_GetFlagStatus(XSPI, XSPI_BUSY_FLAG) != RESET)
    {
    }
}


/**
*\*\name    Flash_Register_Read.
*\*\fun     Flash Register Read.
*\*\param   cmdbuf
*\*\param   rbuf
*\*\param   wsize
*\*\param   rsize
*\*\return  none
**/
void Flash_Register_Read(uint8_t *cmdbuf, uint8_t *rbuf, uint8_t wsize, uint32_t rsize)
{
    uint32_t i = 0, rindex = 0;

    XSPI_Waie_Tx_Compelete();

    XSPI_ClearRxFIFO(XSPI);

    if (wsize > 16)
    {
        XSPI_SetTXStartFIFOThreshold(XSPI, XSPI_FIFO_THRESHOLD_LEVEL15);
    }
    else if (wsize == 0)
    {
        XSPI_SetTXStartFIFOThreshold(XSPI, XSPI_FIFO_THRESHOLD_LEVEL0);
    }
    else
    {
        XSPI_SetTXStartFIFOThreshold(XSPI, (wsize - 1));
    }

    while (i < wsize)
    {
        if (XSPI_GetFlagStatus(XSPI, XSPI_TXFNF_FLAG) != RESET)
        {
            XSPI_SendData(XSPI, cmdbuf[i++]);
        }
    }

    XSPI_Waie_Tx_Compelete();

    while (XSPI_GetFlagStatus(XSPI, XSPI_RXFNE_FLAG) == SET)
    {
        if (rindex < rsize)
        {
            rbuf[rindex++] = XSPI_ReceiveData(XSPI);
        }
        else
        {
            XSPI_ReceiveData(XSPI);
        }
    }
}


/**
*\*\name    Flash_Register_Write.
*\*\fun     Flash Register Write.
*\*\param   cmdbuf
*\*\param   wsize
*\*\return  none
**/
void Flash_Register_Write(uint8_t *cmdbuf, uint8_t wsize)
{
    uint32_t i = 0;

    XSPI_Waie_Tx_Compelete();

    XSPI_ClearRxFIFO(XSPI);

    if (wsize > 16)
    {
        XSPI_SetTXStartFIFOThreshold(XSPI, XSPI_FIFO_THRESHOLD_LEVEL15);
    }
    else if (wsize == 0)
    {
        XSPI_SetTXStartFIFOThreshold(XSPI, XSPI_FIFO_THRESHOLD_LEVEL0);
    }
    else
    {
        XSPI_SetTXStartFIFOThreshold(XSPI, (wsize - 1));
    }

    while (i < wsize)
    {
        if (XSPI_GetFlagStatus(XSPI, XSPI_TXFNF_FLAG) != RESET)
        {
            XSPI_SendData(XSPI, cmdbuf[i++]);
        }
    }

    XSPI_Waie_Tx_Compelete();
}



/**
*\*\name    XSPI_Flash_Register_Write.
*\*\fun     Flash Write Enable.
*\*\param   none
*\*\return  none
**/
void Flash_Write_Enable(void)
{
    uint8_t bufw[4] = {0xff,0xff};

    XSPI_Standard_Mode_Config(XSPI_FRAME_SIZE_8_BIT, XSPI_TX_AND_RX_MODE, TEST_WR_CMDCLKDIV);
    XSPI_Enable(XSPI, ENABLE);

#ifdef P25Q40
    bufw[0] = SPIFLASH_Write_Enable;
    Flash_Register_Write(bufw, 1);
#else
    /* Other Flash Operation */
#endif
}


/**
*\*\name    Flash_Check_Busy.
*\*\fun     Check Flash Busy Flag.
*\*\param   none
*\*\return  none
**/
void Flash_Check_Busy(void)
{
    uint8_t bufw[4] = {0};
    uint8_t bufr[4] = {0};

    XSPI_Waie_Tx_Compelete();

    XSPI_Standard_Mode_Config(XSPI_FRAME_SIZE_8_BIT, XSPI_TX_AND_RX_MODE, TEST_WR_CMDCLKDIV);
    XSPI_Enable(XSPI, ENABLE);

#ifdef P25Q40
    do/*Waiting for flash idle*/
    {
        bufw[0] = SPIFLASH_Read_Reg1;
        Flash_Register_Read(bufw, bufr, 2, 2);
    }while(((bufr[1] & 0x03) == 0x03));
#else
    /* Other Flash Operation */
#endif
}


/**
*\*\name    Flash_Quad_Mode_Enable.
*\*\fun     Flash Quad Mode Enable.
*\*\param   none
*\*\return  none
**/
void Flash_Quad_Mode_Enable(void)
{
    uint8_t bufw[4] = {0};
    uint8_t bufr[4] = {0};

    GPIO_HD_WP_Configuration();
    
    Flash_Write_Enable();

#ifdef P25Q40
    do/*set QE*/
    {
        bufw[0] = SPIFLASH_Write_Reg1;
        bufw[1] = 0x00;
        bufw[2] = SPIFLASH_REG2CMD_SETQE;
        Flash_Register_Write(bufw, 3);


        bufw[0] = SPIFLASH_Read_Reg2;
        Flash_Register_Read(bufw, bufr, 2, 2);
    } while((bufr[1] & SPIFLASH_REG2CMD_SETQE) != SPIFLASH_REG2CMD_SETQE);

    Hardware_Configuration();
#else
    /* Other Flash Operation */
#endif
}


/**
*\*\name    Flash_Sector_Erase.
*\*\fun     Flash Sector Erase.
*\*\param   none
*\*\return  none
**/
void Flash_Sector_Erase(uint32_t SectorAddr)
{
    uint8_t bufw[4] = {0xff,0xff};

#ifdef P25Q40
    Flash_Write_Enable();

    /*Erase flash*/
    bufw[0] = SPIFLASH_Block_Erase4KB;
    bufw[1] = (SectorAddr & 0xff0000) >> 16;
    bufw[2] = (SectorAddr & 0xff00) >> 8;
    bufw[3] = SectorAddr & 0xff;
    Flash_Register_Write(bufw, 4);

    Flash_Check_Busy();
#else
    /* Other Flash Operation */
#endif
}


/**
*\*\name    Flash_Chip_Erase.
*\*\fun     Flash Chip Erase.
*\*\param   none
*\*\return  none
**/
void Flash_Chip_Erase(void)
{
    uint8_t bufw[4] = {0};

#ifdef P25Q40
    Flash_Write_Enable();

    /*Erase flash*/
    bufw[0] = SPIFLASH_Block_EraseChip;
    Flash_Register_Write(bufw, 1);

    Flash_Check_Busy();
#else
    /* Other Flash Operation */
#endif
}


/**
*\*\name    Flash_Read_Buffer.
*\*\fun     Flash Rea Buffer.
*\*\param   pBuffer
*\*\param   ReadAddr
*\*\param   NumWordToRead
*\*\return  none
**/
void Flash_Read_Buffer(uint32_t* pBuffer, uint32_t ReadAddr, uint32_t NumWordToRead)
{
    uint32_t number = 0;

#ifdef P25Q40
/* Quad SPI Format Mode */
#if (READ_SPI_FORMAT_MODE == READ_QUAD_SPI_FORMAT)
#ifdef ADDR_MUTTI_WIRE_TX
    /*  Instruction will be sent in Standard SPI Mode and Address will be sent in the Quad-wire mode */
    XSPI_Enhanced_Mode_Config(XSPI_FRAME_SIZE_32_BIT, XSPI_RX_ONLY_MODE, XSPI_QUAD_LINE_MODE, XSPI_INST_SINGLE_LINE_ADDR_MULTI_LINE, TEST_WR_CLKDIV, FAST_READ_QUAD_IO_WAIT_CYCLES);
#else
    /* Instruction and Address will be sent in Standard SPI Mode */
    XSPI_Enhanced_Mode_Config(XSPI_FRAME_SIZE_32_BIT, XSPI_RX_ONLY_MODE, XSPI_QUAD_LINE_MODE, XSPI_INST_ADDR_SINGLE_LINE, TEST_WR_CLKDIV, FAST_READ_QUAD_OUTPUT_WAIT_CYCLES);
#endif
#elif (READ_SPI_FORMAT_MODE == READ_DUAL_SPI_FORMAT)
/* Dual SPI Format Mode */
#ifdef ADDR_MUTTI_WIRE_TX
    /*  Instruction will be sent in Standard SPI Mode and Address will be sent in the Dual-wire mode */
    XSPI_Enhanced_Mode_Config(XSPI_FRAME_SIZE_32_BIT, XSPI_RX_ONLY_MODE, XSPI_DUAL_LINE_MODE, XSPI_INST_SINGLE_LINE_ADDR_MULTI_LINE, TEST_WR_CLKDIV, FAST_READ_DUAL_IO_WAIT_CYCLES);
#else
    /* Instruction and Address will be sent in Standard SPI Mode */
    XSPI_Enhanced_Mode_Config(XSPI_FRAME_SIZE_32_BIT, XSPI_RX_ONLY_MODE, XSPI_DUAL_LINE_MODE, XSPI_INST_ADDR_SINGLE_LINE, TEST_WR_CLKDIV, FAST_READ_DUAL_OUTPUT_WAIT_CYCLES);
    
#endif
#endif
#else
    /* Other Flash Operation */
#endif

    XSPI_SetNumberOfDataFrame(XSPI, NumWordToRead);

    XSPI_Enable(XSPI, ENABLE);

    XSPI_Waie_Tx_Compelete();
    XSPI_ClearRxFIFO(XSPI);

    XSPI_SetTXStartFIFOThreshold(XSPI, XSPI_FIFO_THRESHOLD_LEVEL1);

#ifdef P25Q40
#if (READ_SPI_FORMAT_MODE == READ_QUAD_SPI_FORMAT)
#ifdef ADDR_MUTTI_WIRE_TX
    XSPI_SendData(XSPI, SPIFLASH_Read_QUAL_ADDR_FOUR);
    XSPI_SendData(XSPI, ReadAddr);
#else
    XSPI_SendData(XSPI, SPIFLASH_Read_QUAL_ADDR_SINGLE);
    XSPI_SendData(XSPI, ReadAddr);
#endif
#elif (READ_SPI_FORMAT_MODE == READ_DUAL_SPI_FORMAT)
#ifdef ADDR_MUTTI_WIRE_TX
    XSPI_SendData(XSPI, SPIFLASH_Read_DUAL_ADDR_TWO);
    XSPI_SendData(XSPI, ReadAddr);
#else
    XSPI_SendData(XSPI, SPIFLASH_Read_DUAL_ADDR_SINGLE);
    XSPI_SendData(XSPI, ReadAddr);
#endif
#endif
#else
    /* Other Flash Operation */
#endif

    while (number < NumWordToRead)
    {
        if (XSPI_GetFlagStatus(XSPI, XSPI_RXFNE_FLAG) == SET)
        {
            pBuffer[number++] = XSPI_ReceiveData(XSPI);
        }
    }

    while (XSPI_GetFlagStatus(XSPI, XSPI_BUSY_FLAG) != RESET)
    {
    }

    XSPI_ClearRxFIFO(XSPI);
}



/**
*\*\name    Flash_Read_Buffer_Int.
*\*\fun     Flash Rea Buffer By Interrupt.
*\*\param   pBuffer
*\*\param   ReadAddr
*\*\param   NumWordToRead
*\*\return  none
**/
void Flash_Read_Buffer_Int(uint32_t* pBuffer, uint32_t ReadAddr, uint32_t NumWordToRead)
{
    XSPI_DisbaleAllInt(XSPI);
    NVIC_Initialize();
    
    XSPI_EnableInt(XSPI, XSPI_INT_RXFFULL, ENABLE);
    
#ifdef P25Q40
/* Quad SPI Format Mode */
#if (READ_SPI_FORMAT_MODE == READ_QUAD_SPI_FORMAT)
#ifdef ADDR_MUTTI_WIRE_TX
    /*  Instruction will be sent in Standard SPI Mode and Address will be sent in the Quad-wire mode */
    XSPI_Enhanced_Mode_Config(XSPI_FRAME_SIZE_32_BIT, XSPI_RX_ONLY_MODE, XSPI_QUAD_LINE_MODE, XSPI_INST_SINGLE_LINE_ADDR_MULTI_LINE, TEST_WR_CLKDIV, FAST_READ_QUAD_IO_WAIT_CYCLES);
#else
    /* Instruction and Address will be sent in Standard SPI Mode */
    XSPI_Enhanced_Mode_Config(XSPI_FRAME_SIZE_32_BIT, XSPI_RX_ONLY_MODE, XSPI_QUAD_LINE_MODE, XSPI_INST_ADDR_SINGLE_LINE, TEST_WR_CLKDIV, FAST_READ_QUAD_OUTPUT_WAIT_CYCLES);
#endif
#elif (READ_SPI_FORMAT_MODE == READ_DUAL_SPI_FORMAT)
/* Dual SPI Format Mode */
#ifdef ADDR_MUTTI_WIRE_TX
    /*  Instruction will be sent in Standard SPI Mode and Address will be sent in the Dual-wire mode */
    XSPI_Enhanced_Mode_Config(XSPI_FRAME_SIZE_32_BIT, XSPI_RX_ONLY_MODE, XSPI_DUAL_LINE_MODE, XSPI_INST_SINGLE_LINE_ADDR_MULTI_LINE, TEST_WR_CLKDIV, FAST_READ_DUAL_IO_WAIT_CYCLES);
#else
    /* Instruction and Address will be sent in Standard SPI Mode */
    XSPI_Enhanced_Mode_Config(XSPI_FRAME_SIZE_32_BIT, XSPI_RX_ONLY_MODE, XSPI_DUAL_LINE_MODE, XSPI_INST_ADDR_SINGLE_LINE, TEST_WR_CLKDIV, FAST_READ_DUAL_OUTPUT_WAIT_CYCLES);
#endif
#endif
#else
    /* Other Flash Operation */
#endif

    XSPI_SetNumberOfDataFrame(XSPI, NumWordToRead);

    XSPI_SetTXStartFIFOThreshold(XSPI, XSPI_FIFO_THRESHOLD_LEVEL1);
    XSPI_SetRXFIFOFullThreshold(XSPI, XSPI_FIFO_THRESHOLD_LEVEL10);

    XSPI_Enable(XSPI, ENABLE);

    XSPI_Waie_Tx_Compelete();
    XSPI_ClearRxFIFO(XSPI);

    rSize = 0;

#ifdef P25Q40
#if (READ_SPI_FORMAT_MODE == READ_QUAD_SPI_FORMAT)
#ifdef ADDR_MUTTI_WIRE_TX
    XSPI_SendData(XSPI, SPIFLASH_Read_QUAL_ADDR_FOUR);
    XSPI_SendData(XSPI, ReadAddr);
#else
    XSPI_SendData(XSPI, SPIFLASH_Read_QUAL_ADDR_SINGLE);
    XSPI_SendData(XSPI, ReadAddr);
#endif
#elif (READ_SPI_FORMAT_MODE == READ_DUAL_SPI_FORMAT)
#ifdef ADDR_MUTTI_WIRE_TX
    XSPI_SendData(XSPI, SPIFLASH_Read_DUAL_ADDR_TWO);
    XSPI_SendData(XSPI, ReadAddr);
#else
    XSPI_SendData(XSPI, SPIFLASH_Read_DUAL_ADDR_SINGLE);
    XSPI_SendData(XSPI, ReadAddr);
#endif
#endif
#else
    /* Other Flash Operation */
#endif

    while (rSize < NumWordToRead)
    { 
        if (XSPI_GetINTStatus(XSPI, XSPI_INT_RXFFULL) == SET)
        {
            pBuffer[rSize] = XSPI_ReceiveData(XSPI);
            rSize++;
        }
        
        if (XSPI_GetRXFIFODataNum(XSPI) > 0)
        {
            pBuffer[rSize] = XSPI_ReceiveData(XSPI);
            rSize++;
        }
    }

    while (XSPI_GetFlagStatus(XSPI, XSPI_BUSY_FLAG) != RESET)
    {
    }

    XSPI_ClearRxFIFO(XSPI);
}


/**
*\*\name    Flash_Read_Buffer_DMA.
*\*\fun     Flash Rea Buffer By DMA.
*\*\param   pBuffer
*\*\param   ReadAddr
*\*\param   NumWordToRead
*\*\return  none
**/
void Flash_Read_Buffer_DMA(uint32_t* pBuffer, uint32_t ReadAddr, uint32_t NumWordToRead)
{
#ifdef P25Q40
/* Quad SPI Format Mode */
#if (READ_SPI_FORMAT_MODE == READ_QUAD_SPI_FORMAT)
#ifdef ADDR_MUTTI_WIRE_TX
    /*  Instruction will be sent in Standard SPI Mode and Address will be sent in the Quad-wire mode */
    XSPI_Enhanced_Mode_Config(XSPI_FRAME_SIZE_32_BIT, XSPI_RX_ONLY_MODE, XSPI_QUAD_LINE_MODE, XSPI_INST_SINGLE_LINE_ADDR_MULTI_LINE, TEST_WR_CLKDIV, FAST_READ_QUAD_IO_WAIT_CYCLES);
#else
    /* Instruction and Address will be sent in Standard SPI Mode */
    XSPI_Enhanced_Mode_Config(XSPI_FRAME_SIZE_32_BIT, XSPI_RX_ONLY_MODE, XSPI_QUAD_LINE_MODE, XSPI_INST_ADDR_SINGLE_LINE, TEST_WR_CLKDIV, FAST_READ_QUAD_OUTPUT_WAIT_CYCLES);
#endif
#elif (READ_SPI_FORMAT_MODE == READ_DUAL_SPI_FORMAT)
/* Dual SPI Format Mode */
#ifdef ADDR_MUTTI_WIRE_TX
    /*  Instruction will be sent in Standard SPI Mode and Address will be sent in the Dual-wire mode */
    XSPI_Enhanced_Mode_Config(XSPI_FRAME_SIZE_32_BIT, XSPI_RX_ONLY_MODE, XSPI_DUAL_LINE_MODE, XSPI_INST_SINGLE_LINE_ADDR_MULTI_LINE, TEST_WR_CLKDIV, FAST_READ_DUAL_IO_WAIT_CYCLES);
#else
    /* Instruction and Address will be sent in Standard SPI Mode */
    XSPI_Enhanced_Mode_Config(XSPI_FRAME_SIZE_32_BIT, XSPI_RX_ONLY_MODE, XSPI_DUAL_LINE_MODE, XSPI_INST_ADDR_SINGLE_LINE, TEST_WR_CLKDIV, FAST_READ_DUAL_OUTPUT_WAIT_CYCLES);
#endif
#endif
#else
    /* Other Flash Operation */
#endif

    XSPI_SetNumberOfDataFrame(XSPI, NumWordToRead);

    XSPI_SetDMARxFIFOThreshold(XSPI, XSPI_FIFO_THRESHOLD_LEVEL8);
    XSPI_EnableDma(XSPI, XSPI_DMA_RX, ENABLE);

    XSPI_Enable(XSPI, ENABLE);

    XSPI_Waie_Tx_Compelete();
    XSPI_ClearRxFIFO(XSPI);

    XSPI_SetTXStartFIFOThreshold(XSPI, XSPI_FIFO_THRESHOLD_LEVEL1);
    DMA_Configuration((uint32_t)&XSPI->DAT0, (uint32_t)pBuffer, NumWordToRead, DMA_RX, ENABLE);

#ifdef P25Q40
#if (READ_SPI_FORMAT_MODE == READ_QUAD_SPI_FORMAT)
#ifdef ADDR_MUTTI_WIRE_TX
    XSPI_SendData(XSPI, SPIFLASH_Read_QUAL_ADDR_FOUR);
    XSPI_SendData(XSPI, ReadAddr);
#else
    XSPI_SendData(XSPI, SPIFLASH_Read_QUAL_ADDR_SINGLE);
    XSPI_SendData(XSPI, ReadAddr);
#endif
#elif (READ_SPI_FORMAT_MODE == READ_DUAL_SPI_FORMAT)
#ifdef ADDR_MUTTI_WIRE_TX
    XSPI_SendData(XSPI, SPIFLASH_Read_DUAL_ADDR_TWO);
    XSPI_SendData(XSPI, ReadAddr);
#else
    XSPI_SendData(XSPI, SPIFLASH_Read_DUAL_ADDR_SINGLE);
    XSPI_SendData(XSPI, ReadAddr);
#endif
#endif
#else
    /* Other Flash Operation */
#endif

    /*wait RX end  */
    while(DMA_GetFlagStatus(DMA_FLAG_TC2,DMA1) == RESET)  /*wait DMA transfer complete*/
    {
    }

    DMA_ClearFlag(DMA_FLAG_TC2, DMA1);

    while (XSPI_GetFlagStatus(XSPI, XSPI_BUSY_FLAG) != RESET)
    {
    }

    XSPI_ClearRxFIFO(XSPI);

    XSPI_Enable(XSPI, DISABLE);
    DMA_Configuration((uint32_t)&XSPI->DAT0, (uint32_t)pBuffer, NumWordToRead, DMA_RX, DISABLE);
    XSPI_Enable(XSPI, ENABLE);
}


/**
*\*\name    Flash_Write_Page.
*\*\fun     Flash Write Page.
*\*\param   pBuffer
*\*\param   WriteAddr
*\*\param   NumWordToWrite
*\*\return  none
**/
void Flash_Write_Page(uint32_t* pBuffer, uint32_t WriteAddr, uint32_t NumWordToWrite)
{
    uint32_t number = 0;

    if(NumWordToWrite != 0)
    {
        Flash_Write_Enable();
        
        XSPI_Enhanced_Mode_Config(XSPI_FRAME_SIZE_32_BIT, XSPI_TX_ONLY_MODE, XSPI_QUAD_LINE_MODE, XSPI_INST_ADDR_SINGLE_LINE, TEST_WR_CLKDIV, QUAD_INPUT_PAGE_PROGRAM_WAIT_CYCLES);
        XSPI_SetNumberOfDataFrame(XSPI, NumWordToWrite);
        
        XSPI_Enable(XSPI, ENABLE);
        
        XSPI_Waie_Tx_Compelete();
        
        if (NumWordToWrite >= 16)
        {
            XSPI_SetTXStartFIFOThreshold(XSPI, XSPI_FIFO_THRESHOLD_LEVEL15);
        }
        else
        {
            XSPI_SetTXStartFIFOThreshold(XSPI, (NumWordToWrite + 1));
        }
        
#ifdef P25Q40
        XSPI_SendData(XSPI, SPIFLASH_QuadPage_Pro);
        XSPI_SendData(XSPI, WriteAddr);
#else
        /* Other Flash Operation */
#endif
        
        while (number < NumWordToWrite)
        {
            if (XSPI_GetFlagStatus(XSPI, XSPI_TXFNF_FLAG) == SET)
            {
                XSPI_SendData(XSPI, pBuffer[number++]);
            }
        }

        Flash_Check_Busy();
    }
}


/**
*\*\name    Flash_Write_Buffer.
*\*\fun     Flash Write Buffer.
*\*\param   pBuffer
*\*\param   WriteAddr
*\*\param   NumWordToWrite
*\*\return  none
**/
void Flash_Write_Buffer(uint32_t* pBuffer, uint32_t WriteAddr, uint32_t NumWordToWrite)
{
    uint32_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0, byte_size = 0;
    
    byte_size = (sFLASH_SPI_PAGESIZE*4);

    Addr        = WriteAddr % byte_size;
    count       = (byte_size - Addr)/4;
    NumOfPage   = NumWordToWrite / sFLASH_SPI_PAGESIZE;
    NumOfSingle = NumWordToWrite % sFLASH_SPI_PAGESIZE;

    if (Addr == 0) /* WriteAddr is sFLASH_PAGESIZE aligned  */
    {
        if (NumOfPage == 0) /* NumWordToWrite < sFLASH_PAGESIZE */
        {
            Flash_Write_Page(pBuffer, WriteAddr, NumWordToWrite);
        }
        else /* NumWordToWrite > sFLASH_PAGESIZE */
        {
            while (NumOfPage--)
            {
                Flash_Write_Page(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
                WriteAddr += byte_size;
                pBuffer += sFLASH_SPI_PAGESIZE;
            }
            Flash_Write_Page(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else /* WriteAddr is not sFLASH_PAGESIZE aligned  */
    {
        if (NumOfPage == 0) /* NumWordToWrite < sFLASH_PAGESIZE */
        {
            if (NumOfSingle > count) /* (NumWordToWrite + WriteAddr) > sFLASH_PAGESIZE */
            {
                temp = NumOfSingle - count;

                Flash_Write_Page(pBuffer, WriteAddr, count);
                WriteAddr += (count*4);
                pBuffer += count;

                Flash_Write_Page(pBuffer, WriteAddr, temp);
            }
            else
            {
                Flash_Write_Page(pBuffer, WriteAddr, NumWordToWrite);
            }
        }
        else /* NumWordToWrite > sFLASH_PAGESIZE */
        {
            NumWordToWrite -= count;
            NumOfPage   = NumWordToWrite / sFLASH_SPI_PAGESIZE;
            NumOfSingle = NumWordToWrite % sFLASH_SPI_PAGESIZE;

            Flash_Write_Page(pBuffer, WriteAddr, count);
            WriteAddr += (count*4);
            pBuffer += count;

            while (NumOfPage--)
            {
                Flash_Write_Page(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
                WriteAddr += byte_size;
                pBuffer += sFLASH_SPI_PAGESIZE;
            }

            Flash_Write_Page(pBuffer, WriteAddr, NumOfSingle);
        }
    }
}


/**
*\*\name    Flash_Write_Page_DMA.
*\*\fun     Flash Write Page By DMA.
*\*\param   pBuffer
*\*\param   WriteAddr
*\*\param   NumWordToWrite
*\*\return  none
**/
void Flash_Write_Page_DMA(uint32_t* pBuffer, uint32_t WriteAddr, uint32_t NumWordToWrite)
{
    if(NumWordToWrite != 0)
    {
        Flash_Write_Enable();

        XSPI_Enhanced_Mode_Config(XSPI_FRAME_SIZE_32_BIT, XSPI_TX_ONLY_MODE, XSPI_QUAD_LINE_MODE, XSPI_INST_ADDR_SINGLE_LINE, TEST_WR_CLKDIV, QUAD_INPUT_PAGE_PROGRAM_WAIT_CYCLES);
        XSPI_SetNumberOfDataFrame(XSPI, NumWordToWrite);
        
        XSPI_SetTXStartFIFOThreshold(XSPI, XSPI_FIFO_THRESHOLD_LEVEL4);
        XSPI_SetDMATxFIFOThreshold(XSPI, XSPI_FIFO_THRESHOLD_LEVEL5);
        
        XSPI_EnableDma(XSPI, XSPI_DMA_TX, ENABLE);
        
        XSPI_Enable(XSPI, ENABLE);
        
        XSPI_Waie_Tx_Compelete();
        
        DMA_Configuration((uint32_t)&XSPI->DAT0, (uint32_t)pBuffer, NumWordToWrite, DMA_TX, DISABLE);
#ifdef P25Q40
        XSPI_SendData(XSPI, SPIFLASH_QuadPage_Pro);
        XSPI_SendData(XSPI, WriteAddr);
#else
        /* Other Flash Operation */
#endif
    
        DMA_RequestRemap(DMA_REMAP_XSPI_TX, DMA1_CH1, ENABLE);	
        DMA_EnableChannel(DMA1_CH1, ENABLE);
        
        while (XSPI_GetFlagStatus(XSPI, XSPI_TXFE_FLAG) == RESET)
        {
        }
            

        /*wait TX end  */
        while(DMA_GetFlagStatus(DMA_FLAG_TC1,DMA1) == RESET)  /*wait DMA transfer complete*/
        {
        }
        
        DMA_ClearFlag(DMA_FLAG_TC1, DMA1);

        XSPI_Enable(XSPI, DISABLE);
        DMA_Configuration((uint32_t)&XSPI->DAT0, (uint32_t)pBuffer, NumWordToWrite, DMA_TX, DISABLE);
        XSPI_Enable(XSPI, ENABLE);
        
        Flash_Check_Busy();
    }
}


/**
*\*\name    Flash_Write_Buffer_DMA.
*\*\fun     Flash Write Buffer By DMA.
*\*\param   pBuffer
*\*\param   WriteAddr
*\*\param   NumWordToWrite
*\*\return  none
**/
void Flash_Write_Buffer_DMA(uint32_t* pBuffer, uint32_t WriteAddr, uint32_t NumWordToWrite)
{
    uint32_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0, byte_size = 0;
    
    byte_size = (sFLASH_SPI_PAGESIZE*4);

    Addr        = WriteAddr % byte_size;
    count       = (byte_size - Addr)/4;
    NumOfPage   = NumWordToWrite / sFLASH_SPI_PAGESIZE;
    NumOfSingle = NumWordToWrite % sFLASH_SPI_PAGESIZE;

    if (Addr == 0) /* WriteAddr is sFLASH_PAGESIZE aligned  */
    {
        if (NumOfPage == 0) /* NumWordToWrite < sFLASH_PAGESIZE */
        {
            Flash_Write_Page_DMA(pBuffer, WriteAddr, NumWordToWrite);
        }
        else /* NumWordToWrite > sFLASH_PAGESIZE */
        {
            while (NumOfPage--)
            {
                Flash_Write_Page_DMA(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
                WriteAddr += byte_size;
                pBuffer += sFLASH_SPI_PAGESIZE;
            }
            Flash_Write_Page_DMA(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else /* WriteAddr is not sFLASH_PAGESIZE aligned  */
    {
        if (NumOfPage == 0) /* NumWordToWrite < sFLASH_PAGESIZE */
        {
            if (NumOfSingle > count) /* (NumWordToWrite + WriteAddr) > sFLASH_PAGESIZE */
            {
                temp = NumOfSingle - count;

                Flash_Write_Page_DMA(pBuffer, WriteAddr, count);
                WriteAddr += (count*4);
                pBuffer += count;

                Flash_Write_Page_DMA(pBuffer, WriteAddr, temp);
            }
            else
            {
                Flash_Write_Page_DMA(pBuffer, WriteAddr, NumWordToWrite);
            }
        }
        else /* NumWordToWrite > sFLASH_PAGESIZE */
        {
            NumWordToWrite -= count;
            NumOfPage   = NumWordToWrite / sFLASH_SPI_PAGESIZE;
            NumOfSingle = NumWordToWrite % sFLASH_SPI_PAGESIZE;

            Flash_Write_Page_DMA(pBuffer, WriteAddr, count);
            WriteAddr += (count*4);
            pBuffer += count;

            while (NumOfPage--)
            {
                Flash_Write_Page_DMA(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
                WriteAddr += byte_size;
                pBuffer += sFLASH_SPI_PAGESIZE;
            }

            Flash_Write_Page_DMA(pBuffer, WriteAddr, NumOfSingle);
        }
    }
}




