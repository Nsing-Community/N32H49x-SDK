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
*\*\file      main.h
*\*\author    Nsing
*\*\version   v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved. 
*/
#ifndef __XSPI_FLASH__
#define __XSPI_FLASH__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h49x_xspi_v2.h"

#define XIP_REMAP_BASE_ADDR (0x90000000)

#define BUFSIZE              (256)
#define TEST_ADDR            (0x000000)
#define FLASH_WAIT_CNT       (1000U)

#define P25Q40
//#define ADDR_MUTTI_WIRE_TX

#define READ_DUAL_SPI_FORMAT  (1)
#define READ_QUAD_SPI_FORMAT  (2)
#define READ_SPI_FORMAT_MODE  (READ_QUAD_SPI_FORMAT)


#define SPIFLASH_Write_Enable          (0x06)
#define SPIFLASH_Block_Erase4KB        (0x20)
#define SPIFLASH_Block_Erase32KB       (0x52)
#define SPIFLASH_Block_EraseChip       (0x60)

#define SPIFLASH_Read_Reg1             (0x05)
#define SPIFLASH_Read_Reg2             (0x35)
#define SPIFLASH_Read_Reg3             (0x15)

#define SPIFLASH_Write_Reg1            (0x01)
#define SPIFLASH_Write_Reg2            (0x31)
#define SPIFLASH_Write_Reg3            (0x11)

#define SPIFLASH_Read_Data             (0x03)
#define SPIFLASH_Read_Data1            (0x0B)

#define SPIFLASH_Read_DUAL             (0x3B) 

#define SPIFLASH_Read_QUAD             (0x6B) 
#define SPIFLASH_Read_QUAD1            (0xEB)

#define SPIFLASH_Read_DUAL_ADDR_SINGLE (0x3B) 
#define SPIFLASH_Read_DUAL_ADDR_TWO    (0xBB) 

#define SPIFLASH_Read_QUAL_ADDR_SINGLE (0x6B) 
#define SPIFLASH_Read_QUAL_ADDR_FOUR   (0xEB) 

#define SPIFLASH_Page_Pro              (0x02)
#define SPIFLASH_QuadPage_Pro          (0x32)

//write data
#define SPIFLASH_REG2CMD_SETQE         (0x02)
#define SPIFLASH_VSRWrite_Enable       (0x50) // Volatile SR Write Enable

//FLASH WR type
#define TYPE_REG_READ                  (0x01)
#define TYPE_REG_WRITE                 (0x02)

#define sFLASH_SPI_PAGESIZE            (0x40) // 256 byte



#define TEST_WR_BYTE_LEN               (128 * 4) 
#define TEST_WR_WORD_LEN               (128) 
#define TEST_WR_CLKDIV                 (6)  // 240MHz / 6 = 40MHz
#define TEST_WR_CMDCLKDIV              (80) // 240MHz / 80 = 3MHz

#define FLASH_WriteAddress             (0x0)
#define FLASH_ReadAddress              FLASH_WriteAddress
#define FLASH_SectorToErase            FLASH_WriteAddress 

#define DMA_TX                         0x10
#define DMA_RX                         0x01

     
#define FAST_READ_DUAL_OUTPUT_WAIT_CYCLES     (XSPI_WAIT_8_CYCLES) 
#define FAST_READ_QUAD_OUTPUT_WAIT_CYCLES     (XSPI_WAIT_8_CYCLES)
#define FAST_READ_DUAL_IO_WAIT_CYCLES         (XSPI_WAIT_0_CYCLES)
#define FAST_READ_QUAD_IO_WAIT_CYCLES         (XSPI_WAIT_4_CYCLES)
#define QUAD_INPUT_PAGE_PROGRAM_WAIT_CYCLES   (XSPI_WAIT_0_CYCLES)


/************************** Pin Defined **************************/
#define XSPI_FLASH_NSS0_PIN    (GPIO_PIN_6)
#define XSPI_FLASH_NSS0_PORT   (GPIOG)
#define XSPI_FLASH_NSS0_AF     (GPIO_AF5)
#define XSPI_FLASH_NSS0_CLK    (RCC_AHB_PERIPHEN_GPIOG)

#define XSPI_FLASH_SCK_PIN     (GPIO_PIN_10)
#define XSPI_FLASH_SCK_PORT    (GPIOF)
#define XSPI_FLASH_SCK_AF      (GPIO_AF9)
#define XSPI_FLASH_SCK_CLK     (RCC_AHB_PERIPHEN_GPIOF)

#define XSPI_FLASH_D0_PIN      (GPIO_PIN_8)
#define XSPI_FLASH_D0_PORT     (GPIOF)
#define XSPI_FLASH_D0_AF       (GPIO_AF9)
#define XSPI_FLASH_D0_CLK      (RCC_AHB_PERIPHEN_GPIOF)

#define XSPI_FLASH_D1_PIN      (GPIO_PIN_9)
#define XSPI_FLASH_D1_PORT     (GPIOF)
#define XSPI_FLASH_D1_AF       (GPIO_AF9)
#define XSPI_FLASH_D1_CLK      (RCC_AHB_PERIPHEN_GPIOF)

#define XSPI_FLASH_D2_PIN      (GPIO_PIN_7)
#define XSPI_FLASH_D2_PORT     (GPIOF)
#define XSPI_FLASH_D2_AF       (GPIO_AF9)
#define XSPI_FLASH_D2_CLK      (RCC_AHB_PERIPHEN_GPIOF)

#define XSPI_FLASH_D3_PIN      (GPIO_PIN_6)
#define XSPI_FLASH_D3_PORT     (GPIOF)
#define XSPI_FLASH_D3_AF       (GPIO_AF9)
#define XSPI_FLASH_D3_CLK      (RCC_AHB_PERIPHEN_GPIOF)



void RCC_Configuration(void);
void Hardware_Configuration(void);
void GPIO_HD_WP_Configuration(void);

void XSPI_Standard_Mode_Config(uint32_t DataFrameSize, uint32_t TransferMode, uint32_t Baudr);
void XSPI_XIP_Mode_Config(uint32_t TransferMode, uint32_t FrameFormat, uint32_t TransferType, uint32_t Baudr, uint32_t WaitCycles, uint32_t XipModeBit);
void XSPI_Waie_Tx_Compelete(void);

void Flash_Register_Read(uint8_t *cmdbuf, uint8_t *rbuf, uint8_t wsize, uint32_t rsize);
void Flash_Register_Write(uint8_t *cmdbuf, uint8_t wsize);


void Flash_Write_Enable(void);
void Flash_Check_Busy(void);
void Flash_Quad_Mode_Enable(void);
void Flash_Sector_Erase(uint32_t SectorAddr);
void Flash_Chip_Erase(void);

void Flash_XIP_Read_Buffer(uint32_t* pBuffer, uint32_t ReadAddr, uint32_t NumWordToRead);
void Flash_XIP_Write_Buffer(uint32_t* pBuffer, uint32_t WriteAddr, uint32_t NumWordToWrite);

#ifdef __cplusplus
}
#endif

#endif /* __XSPI_FLASH__ */
