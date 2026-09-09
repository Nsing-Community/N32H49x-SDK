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
*\*\file bsp_sdram.h
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#ifndef __BSP_SDRAM_H__
#define __BSP_SDRAM_H__

#include "n32h49x.h"
#include "n32h49x_sdram.h"

#define SDRAM_M12L64164A 0 /* 8Mbyte-4096row-256col-16bit */

#define SDRAM_DEVICE  SDRAM_M12L64164A// choose one

#define SDRAM_CS_SDRAMx SDRAM_CS_SDRAM1_ONLY

/* ADD pin */
#define SDRAM_A0_PORT       GPIOF
#define SDRAM_A0_PIN        GPIO_PIN_0
#define SDRAM_A0_AF         GPIO_AF11

#define SDRAM_A1_PORT       GPIOF
#define SDRAM_A1_PIN        GPIO_PIN_1
#define SDRAM_A1_AF         GPIO_AF11

#define SDRAM_A2_PORT       GPIOF
#define SDRAM_A2_PIN        GPIO_PIN_2
#define SDRAM_A2_AF         GPIO_AF11

#define SDRAM_A3_PORT       GPIOF
#define SDRAM_A3_PIN        GPIO_PIN_3
#define SDRAM_A3_AF         GPIO_AF11

#define SDRAM_A4_PORT       GPIOF
#define SDRAM_A4_PIN        GPIO_PIN_4
#define SDRAM_A4_AF         GPIO_AF11

#define SDRAM_A5_PORT       GPIOF
#define SDRAM_A5_PIN        GPIO_PIN_5
#define SDRAM_A5_AF         GPIO_AF11

#define SDRAM_A6_PORT       GPIOF
#define SDRAM_A6_PIN        GPIO_PIN_12
#define SDRAM_A6_AF         GPIO_AF11

#define SDRAM_A7_PORT       GPIOF
#define SDRAM_A7_PIN        GPIO_PIN_13
#define SDRAM_A7_AF         GPIO_AF11

#define SDRAM_A8_PORT       GPIOF
#define SDRAM_A8_PIN        GPIO_PIN_14
#define SDRAM_A8_AF         GPIO_AF11

#define SDRAM_A9_PORT       GPIOF
#define SDRAM_A9_PIN        GPIO_PIN_15
#define SDRAM_A9_AF         GPIO_AF11

#define SDRAM_A10_PORT      GPIOG
#define SDRAM_A10_PIN       GPIO_PIN_0
#define SDRAM_A10_AF        GPIO_AF11

#define SDRAM_A11_PORT      GPIOG
#define SDRAM_A11_PIN       GPIO_PIN_1
#define SDRAM_A11_AF        GPIO_AF11

// #define SDRAM_A12_PORT        	   GPIOG
// #define SDRAM_A12_PIN              GPIO_PIN_2
// #define SDRAM_A12_AF			   GPIO_AF0

/* DATA pin */
#define SDRAM_D0_PORT        	   GPIOD
#define SDRAM_D0_PIN               GPIO_PIN_14
#define SDRAM_D0_AF			       GPIO_AF7

#define SDRAM_D1_PORT        	   GPIOD
#define SDRAM_D1_PIN               GPIO_PIN_15
#define SDRAM_D1_AF			       GPIO_AF8

#define SDRAM_D2_PORT        	   GPIOD
#define SDRAM_D2_PIN               GPIO_PIN_0
#define SDRAM_D2_AF			       GPIO_AF7

#define SDRAM_D3_PORT        	   GPIOD
#define SDRAM_D3_PIN               GPIO_PIN_1
#define SDRAM_D3_AF			       GPIO_AF8

#define SDRAM_D4_PORT        	   GPIOE
#define SDRAM_D4_PIN               GPIO_PIN_7
#define SDRAM_D4_AF			       GPIO_AF3

#define SDRAM_D5_PORT        	   GPIOE
#define SDRAM_D5_PIN               GPIO_PIN_8
#define SDRAM_D5_AF			       GPIO_AF6

#define SDRAM_D6_PORT        	   GPIOE
#define SDRAM_D6_PIN               GPIO_PIN_9
#define SDRAM_D6_AF			       GPIO_AF6

#define SDRAM_D7_PORT        	   GPIOE
#define SDRAM_D7_PIN               GPIO_PIN_10
#define SDRAM_D7_AF			       GPIO_AF11

#define SDRAM_D8_PORT        	   GPIOE
#define SDRAM_D8_PIN               GPIO_PIN_11
#define SDRAM_D8_AF			       GPIO_AF11

#define SDRAM_D9_PORT        	   GPIOE
#define SDRAM_D9_PIN               GPIO_PIN_12
#define SDRAM_D9_AF			       GPIO_AF11

#define SDRAM_D10_PORT        	   GPIOE
#define SDRAM_D10_PIN              GPIO_PIN_13
#define SDRAM_D10_AF			   GPIO_AF11

#define SDRAM_D11_PORT        	   GPIOE
#define SDRAM_D11_PIN              GPIO_PIN_14
#define SDRAM_D11_AF			   GPIO_AF11

#define SDRAM_D12_PORT        	   GPIOE
#define SDRAM_D12_PIN              GPIO_PIN_15
#define SDRAM_D12_AF			   GPIO_AF11

#define SDRAM_D13_PORT        	   GPIOD
#define SDRAM_D13_PIN              GPIO_PIN_8
#define SDRAM_D13_AF		       GPIO_AF6

#define SDRAM_D14_PORT        	   GPIOD
#define SDRAM_D14_PIN              GPIO_PIN_9
#define SDRAM_D14_AF	           GPIO_AF7

#define SDRAM_D15_PORT        	   GPIOD
#define SDRAM_D15_PIN              GPIO_PIN_10
#define SDRAM_D15_AF		       GPIO_AF7

/* BA signal pin */
#define SDRAM_BA0_PORT      GPIOG
#define SDRAM_BA0_PIN       GPIO_PIN_4
#define SDRAM_BA0_AF        GPIO_AF11

#define SDRAM_BA1_PORT      GPIOG
#define SDRAM_BA1_PIN       GPIO_PIN_5
#define SDRAM_BA1_AF        GPIO_AF11

/* NWE pin */
#define SDRAM_NWE_PORT      GPIOC
#define SDRAM_NWE_PIN       GPIO_PIN_0
#define SDRAM_NWE_AF        GPIO_AF13

/* NRAS pin */
#define SDRAM_NRAS_PORT        	   GPIOF
#define SDRAM_NRAS_PIN             GPIO_PIN_11
#define SDRAM_NRAS_AF			   GPIO_AF9

/* NCAS pin */
#define SDRAM_NCAS_PORT     GPIOG
#define SDRAM_NCAS_PIN      GPIO_PIN_15
#define SDRAM_NCAS_AF       GPIO_AF10

/* DQM signal pin */
#define SDRAM_DQM0_PORT        	   GPIOE
#define SDRAM_DQM0_PIN             GPIO_PIN_0
#define SDRAM_DQM0_AF			   GPIO_AF5

#define SDRAM_DQM1_PORT        	   GPIOE
#define SDRAM_DQM1_PIN             GPIO_PIN_1
#define SDRAM_DQM1_AF			   GPIO_AF5

/* NCE0 signal pin */
#define SDRAM_NCE0_PORT     GPIOC //SDRAM1
#define SDRAM_NCE0_PIN      GPIO_PIN_2
#define SDRAM_NCE0_AF       GPIO_AF14

/* CKE0 signal pin */
#define SDRAM_CKE0_PORT     GPIOC //SDRAM1
#define SDRAM_CKE0_PIN      GPIO_PIN_3
#define SDRAM_CKE0_AF       GPIO_AF14

/* CLK pin */
#define SDRAM_CLK_PORT        	   GPIOG
#define SDRAM_CLK_PIN              GPIO_PIN_10
#define SDRAM_CLK_AF			   GPIO_AF12

void SDRAM_RCC_Configuration(void);
void SDRAM_GPIO_Init(void);
void SDRAM_DeviceInit(void);




#endif //__BSP_SDRAM_H__
