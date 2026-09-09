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
*\*\file main.h
*\*\author Nsing 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#ifndef I2C_MASTER_H_
#define I2C_MASTER_H_

#include "stdint.h"

#define I2C_MASTER_ADDR   0x30
#define I2C_SLAVE_ADDR    0x10
#define TEST_BUFFER_SIZE  100
#define I2CT_FLAG_TIMEOUT ((uint32_t)0x8000)
#define I2CT_LONG_TIMEOUT ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))


#define I2Cx I2C1
#define I2Cx_RCC            RCC_APB1_PERIPHEN_I2C1

#define I2Cx_SCL_PIN        GPIO_PIN_6
#define I2Cx_SDA_PIN        GPIO_PIN_7
#define I2Cx_SCL_GPIO       GPIOB
#define I2Cx_SDA_GPIO       GPIOB
#define I2Cx_SCL_AF         GPIO_AF2
#define I2Cx_SDA_AF         GPIO_AF2

#define I2Cx_clk_en         RCC_AHB_PERIPHEN_GPIOB

#define I2Cx_EV_IRQn  			I2C1_EV_IRQn
#define I2Cx_ER_IRQn  			I2C1_ER_IRQn
#define I2Cx_EV_IRQHandler  I2C1_EV_IRQHandler
#define I2Cx_ER_IRQHandler  I2C1_ER_IRQHandler

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} Status;

typedef enum
{
    C_READY = 0,
    C_START_BIT,
    C_STOP_BIT
}CommCtrl_t;

typedef enum
{
    MASTER_OK = 0,
    MASTER_BUSY,
    MASTER_MODE,
    MASTER_TXMODE,
    MASTER_RXMODE,
    MASTER_SENDING,
    MASTER_SENDED,
    MASTER_RECVD,
    MASTER_BYTEF,
    MASTER_BUSERR,
    MASTER_UNKNOW,
    SLAVE_OK = 20,
    SLAVE_BUSY,
    SLAVE_MODE,
    SLAVE_BUSERR,
    SLAVE_UNKNOW,

}ErrCode_t;

// Prototype statements for functions
int i2c_master_init(void);
void I2CMaster_Transmit(uint16_t I2CMaster_ByteCountTx, uint8_t *I2CMaster_TxArray, uint16_t I2CMaster_ByteCountRx, uint8_t *I2CMaster_RxArray);
void I2CMaster_Wait(void);
uint8_t I2CMaster_NotReady(void);

#endif /*I2C_MASTER_H_*/
