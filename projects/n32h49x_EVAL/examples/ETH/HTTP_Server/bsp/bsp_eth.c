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
*\*\file bsp_eth.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/ 

#include "bsp_eth.h"


/* Local MAC address */
uint8_t aMACAddr[6];

/* ETH DMA TX RX descriptor physical address */
ETH_DMADescType aDMARxDscrTab[ETH_RX_DESC_NUMBER];
ETH_DMADescType aDMATxDscrTab[ETH_TX_DESC_NUMBER];

/* ETH receive buffer physical address */
uint8_t aRxBuffer[ETH_RX_DESC_NUMBER][ETH_RX_BUFFER_SIZE];

/* Global ETH information structure variable */
ETH_InfoType sEthInfo;

/* Global ETH initialize structure variable */
ETH_InitType sETH_InitParam;

/* Global ETH TX packet structure variable */
ETH_TxPacketType sTxPacket;

/* ETH RMII */
ETH_PinType ETHRMIIPins[] = 
{
    /* ETH_RMII_CRS_DV */
    {GPIOA, GPIO_PIN_7,  GPIO_AF11, GPIO_MODE_INPUT, GPIO_DC_2mA},
    /* ETH_RMII_TXD0 */
    {GPIOG, GPIO_PIN_13, GPIO_AF2,  GPIO_MODE_AF_PP, GPIO_DC_2mA},
    /* ETH_RMII_TXD1 */
    {GPIOG, GPIO_PIN_14, GPIO_AF2,  GPIO_MODE_AF_PP, GPIO_DC_2mA},
    /* ETH_RMII_TXEN */
    {GPIOG, GPIO_PIN_11, GPIO_AF2,  GPIO_MODE_AF_PP, GPIO_DC_2mA},
    /* ETH_RMII_RXD0 */
    {GPIOC, GPIO_PIN_4,  GPIO_AF10, GPIO_MODE_INPUT, GPIO_DC_2mA},
    /* ETH_RMII_RXD1 */
    {GPIOC, GPIO_PIN_5,  GPIO_AF10, GPIO_MODE_INPUT, GPIO_DC_2mA},
    /* ETH_RMII_REFCLK */
    {GPIOA, GPIO_PIN_1,  GPIO_AF7,  GPIO_MODE_INPUT, GPIO_DC_2mA},
    /* ETH_MDC */
    {GPIOC, GPIO_PIN_1,  GPIO_AF11, GPIO_MODE_AF_PP, GPIO_DC_2mA},
    /* ETH_MDIO */
    {GPIOA, GPIO_PIN_2,  GPIO_AF1,  GPIO_MODE_AF_PP, GPIO_DC_2mA}
};

/* ETH MII */
ETH_PinType ETHMIIPins[] = 
{
    /* ETH_MII_RX_CLK */
    {GPIOA, GPIO_PIN_1,  GPIO_AF1,  GPIO_MODE_INPUT, GPIO_DC_2mA},
    /* ETH_MII_RX_DV */
    {GPIOA, GPIO_PIN_7,  GPIO_AF10, GPIO_MODE_INPUT, GPIO_DC_2mA},
    /* ETH_MII_RX_ERR */
    {GPIOB, GPIO_PIN_10, GPIO_AF13, GPIO_MODE_INPUT, GPIO_DC_2mA},
    /* ETH_MII_RXD0 */
    {GPIOC, GPIO_PIN_4,  GPIO_AF11, GPIO_MODE_INPUT, GPIO_DC_2mA},
    /* ETH_MII_RXD1 */
    {GPIOC, GPIO_PIN_5,  GPIO_AF11, GPIO_MODE_INPUT, GPIO_DC_2mA},
    /* ETH_MII_RXD2 */
    {GPIOB, GPIO_PIN_0,  GPIO_AF1,  GPIO_MODE_INPUT, GPIO_DC_2mA},
    /* ETH_MII_RXD3 */
    {GPIOB, GPIO_PIN_1,  GPIO_AF1,  GPIO_MODE_INPUT, GPIO_DC_2mA},
    /* ETH_MII_TX_CLK */
    {GPIOC, GPIO_PIN_3,  GPIO_AF11, GPIO_MODE_INPUT, GPIO_DC_2mA},
    /* ETH_MII_TX_EN */
    {GPIOG, GPIO_PIN_11, GPIO_AF1,  GPIO_MODE_AF_PP, GPIO_DC_2mA},
    /* ETH_MII_TXD0 */
    {GPIOG, GPIO_PIN_13, GPIO_AF1,  GPIO_MODE_AF_PP, GPIO_DC_2mA},
    /* ETH_MII_TXD1 */
    {GPIOG, GPIO_PIN_14, GPIO_AF1,  GPIO_MODE_AF_PP, GPIO_DC_2mA},
    /* ETH_MII_TXD2 */
    {GPIOC, GPIO_PIN_2,  GPIO_AF11, GPIO_MODE_AF_PP, GPIO_DC_2mA},
    /* ETH_MII_TXD3 */
    {GPIOE, GPIO_PIN_2,  GPIO_AF8,  GPIO_MODE_AF_PP, GPIO_DC_2mA},
    /* ETH_MII_COL */
    {GPIOA, GPIO_PIN_3,  GPIO_AF1,  GPIO_MODE_INPUT, GPIO_DC_2mA},
    /* ETH_MII_CRS */
    {GPIOA, GPIO_PIN_0,  GPIO_AF1,  GPIO_MODE_INPUT, GPIO_DC_2mA},
    /* ETH_MDC */
    {GPIOC, GPIO_PIN_1,  GPIO_AF11, GPIO_MODE_AF_PP, GPIO_DC_2mA},
    /* ETH_MDIO */
    {GPIOA, GPIO_PIN_2,  GPIO_AF1,  GPIO_MODE_AF_PP, GPIO_DC_2mA}
};



/** ETH_BSP Private Defines **/


/** ETH_BSP Driving Functions Declaration **/

/**
*\*\name    ETH_BSP_GPIOInit.
*\*\fun     Initialization the GPIOs used by the ETH module.
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\return  none
**/
void ETH_BSP_GPIOInit(ETH_InfoType* pInfo)
{
    uint32_t      index = 0;
    GPIO_InitType GPIO_InitStructure;

    /* Initialize the pins */
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Slew_Rate     = GPIO_SLEW_RATE_FAST;
    if (pInfo->MediaInterface == ETH_RMII_MODE)
    {
        /* Using ETH with RMII hardware interface */
        for (index = 0; index < sizeof(ETHRMIIPins) / sizeof(ETH_PinType); index++)
        {
            GPIO_InitStructure.Pin            = ETHRMIIPins[index].Pin;
            GPIO_InitStructure.GPIO_Mode      = ETHRMIIPins[index].Mode;
            GPIO_InitStructure.GPIO_Current   = ETHRMIIPins[index].Current;
            GPIO_InitStructure.GPIO_Alternate = ETHRMIIPins[index].Alternate;
            GPIO_InitPeripheral(ETHRMIIPins[index].GPIOx, &GPIO_InitStructure);
        }
    }
    else if (pInfo->MediaInterface == ETH_MII_MODE)
    {
        /* Using ETH with MII hardware interface */
        for (index = 0; index < sizeof(ETHMIIPins) / sizeof(ETH_PinType); index++)
        {
            GPIO_InitStructure.Pin            = ETHMIIPins[index].Pin;
            GPIO_InitStructure.GPIO_Mode      = ETHMIIPins[index].Mode;
            GPIO_InitStructure.GPIO_Current   = ETHMIIPins[index].Current;
            GPIO_InitStructure.GPIO_Alternate = ETHMIIPins[index].Alternate;
            GPIO_InitPeripheral(ETHMIIPins[index].GPIOx, &GPIO_InitStructure);
        }
    }
    else
    {
        /* The interface mode doesn't match the hardware development board, and does nothing */
    }

    /* Check whether to enable PPS output */
    if (pInfo->PPSOutCmd != DISABLE)
    {
        /* ETH_PPS_OUT: PB5(AF13)/PB6(AF13)/PG8(AF1), Alternate Function Push Pull Mode */
        GPIO_InitStructure.Pin            = GPIO_PIN_5;
        GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = GPIO_AF13;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    }
}

/**
*\*\name    ETH_BSP_NVICInit.
*\*\fun     Initialization Configuration NVIC.
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\return  none
**/
void ETH_BSP_NVICInit(ETH_InfoType* pInfo)
{
    NVIC_InitType NVIC_InitStructure;
    EXTI_InitType EXTI_InitStructure;
    
    /* Configures the priority group */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    /* Configures the ETH global interrupt NVIC */
    NVIC_InitStructure.NVIC_IRQChannel                   = ETH_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PRE_PRIORITY_5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = NVIC_SUB_PRIORITY_0;
    NVIC_Init(&NVIC_InitStructure);

    /* Check whether to enable PMT */
    if (pInfo->PMTCmd != DISABLE)
    {
        /* Configures the PMT connected to EXTI Line n */
        EXTI_InitStruct(&EXTI_InitStructure);
        EXTI_InitStructure.EXTI_Line                     = EXTI_LINE24;
        EXTI_InitStructure.EXTI_LineCmd                  = ENABLE;
        EXTI_InitStructure.EXTI_Mode                     = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger                  = EXTI_Trigger_Rising;
        EXTI_InitPeripheral(&EXTI_InitStructure);
        /* Configures the ETH_WKUP_IRQn NVIC */
        NVIC_InitStructure.NVIC_IRQChannel               = ETH_WKUP_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority    = NVIC_SUB_PRIORITY_1;
        NVIC_Init(&NVIC_InitStructure);
    }
}

/**
*\*\name    ETH_BSP_ClockCmd.
*\*\fun     Enables or disables the ETH, GPIO, AFIO, etc. clocks.
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_BSP_ClockCmd(FunctionalStatus Cmd)
{
    /* Enable or disable GPIOx Clock */
    RCC_EnableAHB1PeriphClk((RCC_AHB_PERIPHEN_GPIOA | RCC_AHB_PERIPHEN_GPIOB
                           | RCC_AHB_PERIPHEN_GPIOC | RCC_AHB_PERIPHEN_GPIOD
                           | RCC_AHB_PERIPHEN_GPIOE | RCC_AHB_PERIPHEN_GPIOF
                           | RCC_AHB_PERIPHEN_GPIOG | RCC_AHB_PERIPHEN_GPIOH),
                             Cmd);

    /* Enable or disable AFIO Clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_AFIO, Cmd);

    /* Enable or disable ETH Clock */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_ETH, Cmd);
}

/**
*\*\name    ETH_BSP_GetPhyLinkStatus.
*\*\fun     Get PHY link status.
*\*\param   phyAddr:
*\*\          - PHY port address.
*\*\param   phyReg:
*\*\          - PHY register address.
*\*\return  Acquired PHY link state value containing speed core duplex mode
**/
uint16_t ETH_BSP_GetPhyLinkStatus(uint16_t phyAddr, uint16_t phyReg)
{
    uint16_t retVlaue;
    uint32_t regVlaue;
    
    /* Read the PHY register */
    if (!(ETH_ReadPHYRegister(ETH, (uint32_t)phyAddr, (uint32_t)phyReg, &regVlaue)))
    {
        /* Read ERROR */
        retVlaue = 0U;
    }
    else
    {
        /* Get link status */
        retVlaue = ((regVlaue & PHY_SPEEDDUPLEX_MASK) == PHY_FULLDUPLEX10M_STS)? ETH_LINK_10FULL :
                   ((regVlaue & PHY_SPEEDDUPLEX_MASK) == PHY_HALFDUPLEX10M_STS)? ETH_LINK_10HALF :
                   ((regVlaue & PHY_SPEEDDUPLEX_MASK) == PHY_FULLDUPLEX100M_STS)? ETH_LINK_100FULL :
                   ((regVlaue & PHY_SPEEDDUPLEX_MASK) == PHY_HALFDUPLEX100M_STS)? ETH_LINK_100HALF :
                   0U;
    }
    
    return retVlaue;
}

/**
*\*\name    ETH_BSP_Init.
*\*\fun     ETH initialization function, called in the low_level_init() function.
*\*\param   none
*\*\return  SUCCESS or ERROR.
**/
ErrorStatus ETH_BSP_Init(void)
{
    uint32_t TempIndex;
    
    /* Set the local MAC address */
    aMACAddr[0] = MAC_ADDR0;
    aMACAddr[1] = MAC_ADDR1;
    aMACAddr[2] = MAC_ADDR2;
    aMACAddr[3] = MAC_ADDR3;
    aMACAddr[4] = MAC_ADDR4;
    aMACAddr[5] = MAC_ADDR5;

    /* Clear the sEthInfo structure variable */
    memset(&sEthInfo, 0, sizeof(ETH_InfoType));
    /* Set ETH operation-related information via sEthInfo */
    sEthInfo.AutoNegCmd     = (FunctionalStatus)ETH_AUTONEG_CMD;
    sEthInfo.MDCClockMode   = ETH_MDCCLK_NORMAL;
    sEthInfo.MediaInterface = ETH_SEL_MEDIAIF;
    sEthInfo.pMACAddr       = &aMACAddr[0];
    sEthInfo.PMTCmd         = (FunctionalStatus)ETH_PMT_CMD;
    sEthInfo.PPSOutCmd      = (FunctionalStatus)ETH_PPSOUT_CMD;
    sEthInfo.pRxDesc        = aDMARxDscrTab;
    sEthInfo.pTxDesc        = aDMATxDscrTab;
    sEthInfo.RxBuffLen      = ETH_RX_BUFFER_SIZE;
    sEthInfo.PHYInfo.phyAddr       = PHY_ADDR;
    sEthInfo.PHYInfo.bcRegAddr     = PHY_BCR;
    sEthInfo.PHYInfo.bsRegAddr     = PHY_BSR;
    sEthInfo.PHYInfo.sdRegAddr     = PHY_SDSR;
    sEthInfo.PHYInfo.phyReset      = PHY_RESET;
    sEthInfo.PHYInfo.phyAutoNeg    = PHY_AUTONEGOTIATION;
    sEthInfo.PHYInfo.phyAutoNegOK  = PHY_AUTONEGO_COMPLETE;
    sEthInfo.PHYInfo.phyLinkOK     = PHY_LINKED_STATUS;
    sEthInfo.PHYInfo.phyDuplexMask = PHY_DUPLEX_MASK;
    sEthInfo.PHYInfo.phySpeedMask  = PHY_SPEED_MASK;
    sEthInfo.PHYInfo.phyGetLinkStatus = ETH_BSP_GetPhyLinkStatus;

    /* Enable related clocks */
    ETH_BSP_ClockCmd(ENABLE);
    /* Configuring GPIOs */
    ETH_BSP_GPIOInit(&sEthInfo);
    /* Configuring NVIC */
    ETH_BSP_NVICInit(&sEthInfo);

    /* DeInitializes the ETH peripheral */
    ETH_DeInit(ETH);
    /* Set ETH initialization parameters by default */
    ETH_StructInit(&sETH_InitParam);
    /* Modify ETH initialization parameters */
#if (ETH_AUTONEG_CMD == 0U)
    sETH_InitParam.Duplex               = ETH_SEL_DUPLEX;
    sETH_InitParam.SpeedSelect          = ETH_SEL_SPEED;
#endif
    sETH_InitParam.AutoPadCRCStrip      = (uint32_t)(ENABLE << 20);
    sETH_InitParam.CRCStripTypePacket   = (uint32_t)(ENABLE << 21);
    sETH_InitParam.ChecksumOffload      = (uint32_t)(ENABLE << 27);
    sETH_InitParam.GiantPacketSizeLimit = (0x618U);

    sETH_InitParam.ProgramWatchdog    = (uint32_t)(ENABLE << 8);
    sETH_InitParam.TxQueueOperateMode = ETH_TXQUEUE_OPERATE_THRESHOLD_64;
    sETH_InitParam.RxQueueOperateMode = ETH_RXQUEUE_OPERATE_THRESHOLD_64;

    sETH_InitParam.BurstMode         = ETH_BURST_MODE_FIXED;
    sETH_InitParam.AddrAlignedBeats  = (uint32_t)(ENABLE << 12);
    sETH_InitParam.DescriptorSkipLen = ETH_DESC_SKIP_LEN_64BIT;
    sETH_InitParam.TxBurstLength     = ETH_TX_PROGRAM_BURST_LEN_32;
    sETH_InitParam.RxBurstLength     = ETH_RX_PROGRAM_BURST_LEN_32;
    
#if (ETH_AUTONEG_CMD == 0U)
    sEthInfo.PHYInfo.phyAutoNeg = (~PHY_AUTONEGOTIATION);
    if ((sETH_InitParam.Duplex == ETH_FULL_DUPLEX_MODE)
            && (sETH_InitParam.SpeedSelect == ETH_SPEED_100M))
    {
        /* Set the full-duplex mode at 100 Mb/s to PHY */
        sEthInfo.PHYInfo.phyMode = PHY_FULLDUPLEX_100M;
    }
    else if ((sETH_InitParam.Duplex == ETH_FULL_DUPLEX_MODE)
            && (sETH_InitParam.SpeedSelect == ETH_SPEED_10M))
    {
        /* Set the full-duplex mode at 10 Mb/s to PHY */
        sEthInfo.PHYInfo.phyMode = PHY_FULLDUPLEX_10M;
    }
    else if ((sETH_InitParam.Duplex == ETH_HALF_DUPLEX_MODE)
            && (sETH_InitParam.SpeedSelect == ETH_SPEED_100M))
    {
        /* Set the half-duplex mode at 100 Mb/s to PHY */
        sEthInfo.PHYInfo.phyMode = PHY_HALFDUPLEX_100M;
    }
    else if ((sETH_InitParam.Duplex == ETH_HALF_DUPLEX_MODE)
            && (sETH_InitParam.SpeedSelect == ETH_SPEED_10M))
    {
        /* Set the half-duplex mode at 10 Mb/s to PHY */
        sEthInfo.PHYInfo.phyMode = PHY_HALFDUPLEX_10M;
    }
    else
    {
        /* Auto-Negotiation is enabled when speed is set to 1000Base-T */
        return ERROR;
    }
#endif

    /* Checks whether initializing the ETH was successful */
    if (ETH_Init(ETH, &sEthInfo, &sETH_InitParam) != ETH_SUCCESS)
    {
        /* ETH initialization failed */
        return ERROR;
    }

    /* Assign memory for each RX descriptor */
    for (TempIndex = 0; TempIndex < ETH_RX_DESC_NUMBER; TempIndex++)
    {
        /* Checks whether the assign of memory was successful */
        if (ETH_RxDescAssignMemory(&sEthInfo, TempIndex, aRxBuffer[TempIndex], NULL) != ETH_SUCCESS)
        {
            /* Assign memory failed for descriptor */
            return ERROR;
        }
    }

    /* Clear the sTxPacket structure variable */
    memset(&sTxPacket, 0, sizeof(ETH_TxPacketType));
    /* Set TxPacket-related config via sTxPacket */
    sTxPacket.Attributes   = (ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD);
    sTxPacket.CRCPadCtrl   = ETH_CRC_PAD_INSERT;
    sTxPacket.ChecksumCtrl = ETH_CHECKSUM_INSERT_IPHDR_PAYLOAD_PHDR_CALC;

    return SUCCESS;
}

/**
*\*\name    ETH_BSP_DeInit.
*\*\fun     ETH DeInitializes function.
*\*\param   none
*\*\return  none.
**/
void ETH_BSP_DeInit(void)
{
    /* Clear the sEthInfo structure variable */
    memset(&sEthInfo, 0, sizeof(ETH_InfoType));
    /* Clear the sETH_InitParam structure variable */
    memset(&sETH_InitParam, 0, sizeof(ETH_InitType));
    /* Clear the sTxPacket structure variable */
    memset(&sTxPacket, 0, sizeof(ETH_TxPacketType));
    /* DISABLE related clocks */
    ETH_BSP_ClockCmd(DISABLE);
}


