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
#include "bsp_sdram.h"
#include "log.h"

#define SDRAM_ACCESS_BASEADD   SDRAM1_ADDR
#define BUFFER_SIZE            ((uint32_t)0x1000)
/* Read/Write Buffers */
uint32_t tx_buffer[BUFFER_SIZE];
uint32_t rx_buffer[BUFFER_SIZE];
uint8_t TX_TransferCompleteFlag = 0, RX_TransferCompleteFlag = 0;
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
    NVIC_InitStructure.NVIC_IRQChannel                   = DMA_TX_IRQN;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable DMA x channel y IRQ Channel */
    NVIC_InitStructure.NVIC_IRQChannel                   = DMA_RX_IRQN;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
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
    uint32_t wr_status = 0;
    uint32_t index     = 0;
    DMA_InitType DMA_InitStructure;
    
    
    log_init();
    log_info("sdram DMA test start\r\n");
    
    /*config peripheral clocks*/
    SDRAM_RCC_Configuration();
    /*config SDRAM gpio*/
    SDRAM_GPIO_Init();
    /*config SDRAM*/
    SDRAM_DeviceInit();
    /* Enable DMA x clock */
    RCC_EnableAHBPeriphClk(DMA_CLK, ENABLE);
    /* NVIC configuration */
    NVIC_Configuration();

    /* Fill the buffer to write */
    Fill_Buffer_32(tx_buffer, BUFFER_SIZE, 0xA244250F);
    
    /* Fill the Read buffer */
    Fill_Buffer_32(rx_buffer, BUFFER_SIZE, 0xAAAAAAAA);
    
    /* DMA x channel y configuration */
    DMA_DeInit(DMA_TX_CHANNEL_USED);
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.PeriphAddr     = (uint32_t)SDRAM_ACCESS_BASEADD;
    DMA_InitStructure.MemAddr        = (uint32_t)tx_buffer;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize        = BUFFER_SIZE;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_ENABLE;
    DMA_InitStructure.MemoryInc      = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_WORD;
    DMA_InitStructure.MemDataSize    = DMA_MEM_DATA_WIDTH_WORD;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_ENABLE;
    DMA_Init(DMA_TX_CHANNEL_USED, &DMA_InitStructure);
    
    DMA_DeInit(DMA_RX_CHANNEL_USED);
    DMA_InitStructure.PeriphAddr     = (uint32_t)SDRAM_ACCESS_BASEADD;
    DMA_InitStructure.MemAddr        = (uint32_t)rx_buffer;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_Init(DMA_RX_CHANNEL_USED, &DMA_InitStructure);
    
    /* When operating in memory-to-memory mode, a reserved channel 
    request mapping number must be configured */
    DMA_RequestRemap(DMA_REMAP_RES, DMA_TX_CHANNEL_USED, ENABLE);
    DMA_RequestRemap(DMA_REMAP_RES, DMA_RX_CHANNEL_USED, ENABLE);

    /* Enable DMA x Channel y Transfer Complete interrupt */
    DMA_ConfigInt(DMA_TX_CHANNEL_USED, DMA_INT_TXC, ENABLE);
    DMA_ConfigInt(DMA_RX_CHANNEL_USED, DMA_INT_TXC, ENABLE);

    log_info("write to sdram\r\n");
    /* Enable DMA x Channel y transfer */
    DMA_EnableChannel(DMA_TX_CHANNEL_USED, ENABLE);
    /* Wait the end of transmission */
    while (TX_TransferCompleteFlag == 0)
    {
    }
    
    log_info("read back from sdram\r\n");
    /* Enable DMA x Channel y transfer */
    DMA_EnableChannel(DMA_RX_CHANNEL_USED, ENABLE);
    /* Wait the end of transmission */
    while (RX_TransferCompleteFlag == 0)
    {
    }

    /* Read back SDRAM memory and check content correctness */
    for (index = 0x00; index < BUFFER_SIZE; index++)
    {
        if (rx_buffer[index] != tx_buffer[index])
        {
            wr_status++;
        }
    }

    if (wr_status == 0)
    {
        /* OK */
        log_info("sdram test DMA pass\r\n");
    }
    else
    {
        /* fail*/
        log_info("sdram DMA test fail, wr_status = %d\r\n", wr_status);
    }

    while (1)
    {
    }
}


/**
*\*\name    Fill_Buffer_32.
*\*\fun     Fill the 32bits global buffer
*\*\param   pBuffer: pointer on the Buffer to fill
*\*\param   BufferLenght: size of the buffer to fill
*\*\param   Offset: first value to fill on the Buffer
*\*\return  none
**/
void Fill_Buffer_32(uint32_t* pBuffer, uint32_t BufferLenght, uint32_t Offset)
{
    uint32_t IndexTmp = 0;
    
    /* Put in global buffer same values */
    for (IndexTmp = 0; IndexTmp < BufferLenght; IndexTmp++)
    {
        pBuffer[IndexTmp] = IndexTmp + Offset;
    }
}

/**
*\*\name    DMA_IRQ_HANDLER.
*\*\fun     This function is DMA interrupt request handles.
*\*\param   none 
*\*\return  none 
**/
void DMA_TX_IRQ_HANDLER(void)
{
    /* Test on DMA channel Transfer Complete interrupt */
    if (DMA_GetIntStatus(DMA_TX_IT_FLAG_TC, DMA_USED))
    {
        /* Clear DMA channel Transfer Complete interrupt pending bits */
        DMA_ClrIntPendingBit(DMA_TX_IT_FLAG_TC, DMA_USED);
        /* Set DMA transfer completion flag */
        TX_TransferCompleteFlag = 1;
    }
}

/**
*\*\name    DMA_IRQ_HANDLER.
*\*\fun     This function is DMA interrupt request handles.
*\*\param   none 
*\*\return  none 
**/
void DMA_RX_IRQ_HANDLER(void)
{
    /* Test on DMA channel Transfer Complete interrupt */
    if (DMA_GetIntStatus(DMA_RX_IT_FLAG_TC, DMA_USED))
    {
        /* Clear DMA channel Transfer Complete interrupt pending bits */
        DMA_ClrIntPendingBit(DMA_RX_IT_FLAG_TC, DMA_USED);
        /* Set DMA transfer completion flag */
        RX_TransferCompleteFlag = 1;
    }
}


