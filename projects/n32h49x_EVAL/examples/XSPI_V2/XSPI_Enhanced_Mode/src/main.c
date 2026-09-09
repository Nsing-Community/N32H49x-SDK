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
*\*\file      main.c
*\*\author    Nsing
*\*\version   v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved. 
**/
#include "main.h"
#include "xspi_flash.h"
#include "log.h"
#include "delay.h"

uint32_t XSPI_Wbuffer[BUFSIZE]={0};
uint32_t XSPI_Rbuffer[BUFSIZE]={0};
volatile uint32_t rSize = 0;


void Delay(__IO uint32_t nCount)
{
    for(; nCount != 0; nCount--);
}

/**
*\*\name    main.
*\*\fun     main function.
*\*\param   none
*\*\return  none 
**/
int main(void)
{   
    uint16_t i = 0x00;
    /*SystemInit() function has been called by startup file startup_n32h4xx.s*/
    
    log_init();
    
    /* Clocks Configuration */
    RCC_Configuration();
    
    /* Configure the GPIO ports */
    Hardware_Configuration();
    
    for(i = 0; i < BUFSIZE; i++)
    {
        XSPI_Wbuffer[i] = 0x5A5A5A5A;
    }

#if (READ_SPI_FORMAT_MODE == READ_QUAD_SPI_FORMAT)
#ifdef ADDR_MUTTI_WIRE_TX
    log_info("\nSpi_flash write and read demo start - quad mode - address quad IO output\r\n");
#else
    log_info("\nSpi_flash write and read demo start - quad mode - address single IO output\r\n");
#endif
#elif (READ_SPI_FORMAT_MODE == READ_DUAL_SPI_FORMAT)
/* Dual SPI Format Mode */
#ifdef ADDR_MUTTI_WIRE_TX
    log_info("\nSpi_flash write and read demo start - dual mode - address dual IO output\r\n");
#else
    log_info("\nSpi_flash write and read demo start - dual mode - address single IO output\r\n");
#endif
#endif
    
    Flash_Quad_Mode_Enable();
    
    Flash_Sector_Erase(FLASH_SectorToErase);
    Flash_Read_Buffer(XSPI_Rbuffer, FLASH_ReadAddress, BUFSIZE);
    for (i = 0; i < BUFSIZE; i++)
    {
        if (XSPI_Rbuffer[i] != 0xFFFFFFFF)
        {
             log_info("\n Read data error afer earase sector\r\n");
            break;
        }
    }
    
    log_info("\n Write/Read data Start\r\n");
    Flash_Write_Buffer(XSPI_Wbuffer, FLASH_ReadAddress, BUFSIZE);
    Flash_Read_Buffer(XSPI_Rbuffer, FLASH_ReadAddress, BUFSIZE);
    for (i = 0; i < BUFSIZE; i++)
    {
        if (XSPI_Rbuffer[i] != XSPI_Wbuffer[i])
        {
            log_info("\n Write data and Read data error\r\n");
            break;
        }
        XSPI_Rbuffer[i] = 0;
    }
    if (i == BUFSIZE)
        log_info("\n Write data and Read data succeed\r\n");
    
    log_info("\n Interrupt Read data Start\r\n");
    Flash_Read_Buffer_Int(XSPI_Rbuffer, FLASH_ReadAddress, BUFSIZE);
    for (i = 0; i < BUFSIZE; i++)
    {
        if (XSPI_Rbuffer[i] != XSPI_Wbuffer[i])
        {
            log_info("\n Write data and interrupt-Read data error\r\n");
            break;
        }
        XSPI_Rbuffer[i] = 0;
    }
    if (i == BUFSIZE)
        log_info("\n Interrupt-Read data succeed\r\n");
    
    Flash_Chip_Erase();
    Flash_Read_Buffer(XSPI_Rbuffer, FLASH_ReadAddress, BUFSIZE);
    for (i = 0; i < BUFSIZE; i++)
    {
        if (XSPI_Rbuffer[i] != 0xFFFFFFFF)
        {
             log_info("\n Read data error afer earase chip\r\n");
            break;
        }
        XSPI_Rbuffer[i] = 0;
    }
    

    log_info("\n DMA Write data and DMA Read data Start\r\n");
    Flash_Write_Buffer_DMA(XSPI_Wbuffer, FLASH_ReadAddress, BUFSIZE);

    for(i = 0; i < BUFSIZE; i++)
    {
        XSPI_Rbuffer[i] = 0;
    }
    Flash_Read_Buffer_DMA(XSPI_Rbuffer, FLASH_ReadAddress, BUFSIZE);

    for (i = 0; i < BUFSIZE; i++)
    {
        if (XSPI_Rbuffer[i] != XSPI_Wbuffer[i])
        {
            log_info("\n DMA Write data and DMA Read data Error\r\n");
            break;
        }
    }
    if (i == BUFSIZE)
        log_info("\n DMA Write data and DMA Read data succeed\r\n");

    while (1)
    {      
     
    }
}



