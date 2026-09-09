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
#include <string.h>
#include "log.h"
#include "main.h"


DMA_InitType DMA_InitStructure;

const uint32_t SRC_Const_Buffer[] = {
    0x72aa0305, 0x839916bf, 0x913782c5, 0x7e3bd953, 0x4174430c, 0x40d59981, 0xbccff537, 0xd22bca1a,
    0xda039c07, 0xff38219a, 0x17f16c33, 0x0056b9cf, 0x4e75ab0a, 0x0751b137, 0xbb051ec9, 0xcac01e06,
    0x5de647ba, 0xf2bd2108, 0x60a32be0, 0xbf80a68f, 0x299b4a55, 0xd37b1965, 0x84a3ca5b, 0x0f08f335,
    0x21c4084b, 0x738688ca, 0xe7971a03, 0xadcd6bfc, 0xd4bb55ae, 0x0ea4ed88, 0x131711a3, 0x4e92f42f,
};
uint32_t DST_Buffer[BUFFER_SIZE];

__IO uint8_t TransferCompleteFlag = 0;


/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\param   none
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable peripheral clocks */
    /* Enable DMA x clock */
    RCC_EnableAHBPeriphClk(DMA_CLK, ENABLE);
}

/**
*\*\name    NVIC_Configuration.
*\*\fun     Configure the nested vectored interrupt controller.
*\*\param   none 
*\*\return  none 
**/
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* Enable DMA x channel y IRQ Channel */
    NVIC_InitStructure.NVIC_IRQChannel                   = DMA_IRQN;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    log_init();
    log_info("DMA Burst transfer demo go...\n");
    
    /* System clocks configuration */
    RCC_Configuration();

    /* NVIC configuration */
    NVIC_Configuration();
    
    /* Clear destination buffer */
    memset(DST_Buffer, 0, sizeof(DST_Buffer));
    
    /* DMA x channel y configuration */
    DMA_DeInit(DMA_CHANNEL_USED);
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.PeriphAddr     = (uint32_t)SRC_Const_Buffer;
    DMA_InitStructure.MemAddr        = (uint32_t)DST_Buffer;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = BUFFER_SIZE;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_ENABLE;
    DMA_InitStructure.MemoryInc      = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_WORD;
    DMA_InitStructure.MemDataSize    = DMA_MEM_DATA_WIDTH_WORD;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_ENABLE;
    /* DMA BURST enable */
    DMA_InitStructure.BurstCmd   = DMA_BURST_ENABLE;
    /* BURST mode is almost */
    DMA_InitStructure.BurstMode     = DMA_BURST_MODE_ALMOST;
    /* BURST length */
    DMA_InitStructure.BurstLen      = DMA_BURST_LEN_8;
    DMA_Init(DMA_CHANNEL_USED, &DMA_InitStructure);
    
    /* When operating in memory-to-memory mode, a reserved channel 
    request mapping number must be configured */
    DMA_RequestRemap(DMA_REMAP_RES, DMA_CHANNEL_USED, ENABLE);

    /* Enable DMA x Channel y Transfer Complete interrupt */
    DMA_ConfigInt(DMA_CHANNEL_USED, DMA_IT_FLAG_TC, ENABLE);

    /* Enable DMA x Channel y transfer */
    DMA_EnableChannel(DMA_CHANNEL_USED, ENABLE);

    /* Wait the end of transmission */
    while (TransferCompleteFlag == 0)
    {
    }
    
    /* Check if the transmitted and received data are equal */
    if (memcmp(SRC_Const_Buffer, DST_Buffer, BUFFER_SIZE) == 0)
    {
        log_info("DMA Burst transfer passed\n");
    }
    else
    {
        log_error("DMA Burst transfer failed\n");
    }
    
    while (1)
    {
    }
}

/**
*\*\name    DMA_IRQ_HANDLER.
*\*\fun     This function is DMA interrupt request handles. 
*\*\param   none 
*\*\return  none 
**/
void DMA_IRQ_HANDLER(void)
{
    /* Test on DMA channel Transfer Complete interrupt */
    if (DMA_GetIntStatus(DMA_IT_FLAG_TC, DMA_USED))
    {
        /* Clear DMA channel Transfer Complete interrupt pending bits */
        DMA_ClrIntPendingBit(DMA_IT_FLAG_TC, DMA_USED);
        /* Set DMA transfer completion flag */
        TransferCompleteFlag = 1;
    }
}

