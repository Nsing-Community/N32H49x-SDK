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
*\*\file bsp_sdram.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#include "n32h49x_sdram.h"
#include "n32h49x_gpio.h"
#include "n32h49x_rcc.h"
#include "log.h"
#include "delay.h"
#include "bsp_sdram.h"

/**
*\*\name    SDRAM_RCC_Configuration.
*\*\fun     Configures the peripheral clocks.
*\*\param   none
*\*\return  none
**/
void SDRAM_RCC_Configuration(void)
{
    /* Enable GPIO clock*/
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA|RCC_AHB_PERIPHEN_GPIOB|RCC_AHB_PERIPHEN_GPIOC|RCC_AHB_PERIPHEN_GPIOD, ENABLE);;
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOE|RCC_AHB_PERIPHEN_GPIOF|RCC_AHB_PERIPHEN_GPIOG|RCC_AHB_PERIPHEN_GPIOH, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_AFIO, ENABLE);
    
    /* hclk = 240M, sdram_clk = 80M */
    RCC_ConfigSDRAMClk(RCC_SDRAM_HCLK_DIV3);
    /* Enable SDRAM clock*/
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_SDRAM, ENABLE);
    /* Enable SDRAM clock delay*/
    SDRAM_ConfigSampleDelay(SDRAM_DELAY_0_5_PERIOD);
}

/**
*\*\name    SDRAM_GPIO_Init.
*\*\fun     SDRAM gpio initialized.
*\*\param   none
*\*\return  none 
**/
void SDRAM_GPIO_Init(void)
{
    GPIO_InitType GPIO_InitStructure;
    
    /*-- GPIO Configuration -----------------------*/
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    GPIO_InitStructure.GPIO_Current      = GPIO_DC_2mA;
    GPIO_InitStructure.GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    
    /* ADD pin configuration */
    GPIO_InitStructure.Pin            = SDRAM_A0_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_A0_AF;
    GPIO_InitPeripheral(SDRAM_A0_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_A1_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_A1_AF;
    GPIO_InitPeripheral(SDRAM_A1_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_A2_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_A2_AF;
    GPIO_InitPeripheral(SDRAM_A2_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_A3_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_A3_AF;
    GPIO_InitPeripheral(SDRAM_A3_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_A4_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_A4_AF;
    GPIO_InitPeripheral(SDRAM_A4_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_A5_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_A5_AF;
    GPIO_InitPeripheral(SDRAM_A5_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_A6_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_A6_AF;
    GPIO_InitPeripheral(SDRAM_A6_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_A7_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_A7_AF;
    GPIO_InitPeripheral(SDRAM_A7_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_A8_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_A8_AF;
    GPIO_InitPeripheral(SDRAM_A8_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_A9_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_A9_AF;
    GPIO_InitPeripheral(SDRAM_A9_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_A10_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_A10_AF;
    GPIO_InitPeripheral(SDRAM_A10_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_A11_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_A11_AF;
    GPIO_InitPeripheral(SDRAM_A11_PORT, &GPIO_InitStructure);

//    GPIO_InitStructure.Pin            = SDRAM_A12_PIN;
//    GPIO_InitStructure.GPIO_Alternate = SDRAM_A12_AF;
//    GPIO_InitPeripheral(SDRAM_A12_PORT, &GPIO_InitStructure);

    /*  DATA pin configuration  */
    GPIO_InitStructure.Pin            = SDRAM_D0_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D0_AF;
    GPIO_InitPeripheral(SDRAM_D0_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_D1_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D1_AF;
    GPIO_InitPeripheral(SDRAM_D1_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_D2_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D2_AF;
    GPIO_InitPeripheral(SDRAM_D2_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_D3_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D3_AF;
    GPIO_InitPeripheral(SDRAM_D3_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_D4_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D4_AF;
    GPIO_InitPeripheral(SDRAM_D4_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_D5_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D5_AF;
    GPIO_InitPeripheral(SDRAM_D5_PORT, &GPIO_InitStructure);
    
    
    GPIO_InitStructure.Pin            = SDRAM_D6_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D6_AF;
    GPIO_InitPeripheral(SDRAM_D6_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_D7_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D7_AF;
    GPIO_InitPeripheral(SDRAM_D7_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_D8_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D8_AF;
    GPIO_InitPeripheral(SDRAM_D8_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_D9_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D9_AF;
    GPIO_InitPeripheral(SDRAM_D9_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_D10_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D10_AF;
    GPIO_InitPeripheral(SDRAM_D10_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_D11_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D11_AF;
    GPIO_InitPeripheral(SDRAM_D11_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_D12_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D12_AF;
    GPIO_InitPeripheral(SDRAM_D12_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_D13_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D13_AF;
    GPIO_InitPeripheral(SDRAM_D13_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_D14_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D14_AF;
    GPIO_InitPeripheral(SDRAM_D14_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_D15_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_D15_AF;
    GPIO_InitPeripheral(SDRAM_D15_PORT, &GPIO_InitStructure);

    /* BA signal pin configuration */
    GPIO_InitStructure.Pin            = SDRAM_BA0_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_BA0_AF;
    GPIO_InitPeripheral(SDRAM_BA0_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_BA1_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_BA1_AF;
    GPIO_InitPeripheral(SDRAM_BA1_PORT, &GPIO_InitStructure);


    /* NCE signal pin configuration */
    GPIO_InitStructure.Pin            = SDRAM_NCE0_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_NCE0_AF;
    GPIO_InitPeripheral(SDRAM_NCE0_PORT, &GPIO_InitStructure);
  
    /* NWE pin configuration */
    GPIO_InitStructure.Pin            = SDRAM_NWE_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_NWE_AF;
    GPIO_InitPeripheral(SDRAM_NWE_PORT, &GPIO_InitStructure);
    
    /* NRAS pin configuration */
    GPIO_InitStructure.Pin            = SDRAM_NRAS_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_NRAS_AF;
    GPIO_InitPeripheral(SDRAM_NRAS_PORT, &GPIO_InitStructure);
    
    /* NCAS pin configuration */
    GPIO_InitStructure.Pin            = SDRAM_NCAS_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_NCAS_AF;
    GPIO_InitPeripheral(SDRAM_NCAS_PORT, &GPIO_InitStructure);

    /* DQM signal pin configuration */
    GPIO_InitStructure.Pin            = SDRAM_DQM0_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_DQM0_AF;
    GPIO_InitPeripheral(SDRAM_DQM0_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = SDRAM_DQM1_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_DQM1_AF;
    GPIO_InitPeripheral(SDRAM_DQM1_PORT, &GPIO_InitStructure);

    /* CKE signal pin configuration*/
    GPIO_InitStructure.Pin            = SDRAM_CKE0_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_CKE0_AF;
    GPIO_InitPeripheral(SDRAM_CKE0_PORT, &GPIO_InitStructure);
    
    /* CLK pin configuration*/
    GPIO_InitStructure.Pin            = SDRAM_CLK_PIN;
    GPIO_InitStructure.GPIO_Alternate = SDRAM_CLK_AF;
    GPIO_InitPeripheral(SDRAM_CLK_PORT, &GPIO_InitStructure);
}    

/**
*\*\name    SDRAM_DeviceInit.
*\*\fun     initialize the one or twe SDRAM device.    
*\*\param   none
*\*\return  none 
**/
void SDRAM_DeviceInit()
{
    SDRAM_TimingType SDRAM_Timing;
    SDRAM_OperationInitType SDRAM_Operation;
    SDRAM_ConfigurationInitType SDRAM_Configuration;
   
     /* Set SDRAM address: BaseAddr = 0x98000000, AddrMask = 0xFFFFFFFF-(SDRAMSIZI-1)*/
    SDRAM_SetDeviceAddress(SDRAM_DEVICE_1, 0x98000000, 0xFF800000);//AddrMask=0xFFFFFFFF-(8Mbyte-1)
    /* Set SDRAM Refresh Interval=(Refresh Period / Number of Rows / Mem clock Period)*/
    SDRAM_RefreshIntervalInit(0x4A0);//64000000ns/4096rows/(1/80M=12.5)ns =0x4E2,whichever is smaller

    /* Set SDRAM Timing registers*/
    /* Needs to be consistent with SDRAM device characteristics */
    SDRAM_Timing.RowActiveTime       = 0x7;
    SDRAM_Timing.RowCycleTime        = 0x9;
    SDRAM_Timing.RowActToRowActDelay = 0x3;
    SDRAM_Timing.PrechargeTime       = 0x4;
    SDRAM_Timing.WriteRecoveryTime   = 0x3;
    SDRAM_Timing.RefreshCycleTime    = 0x9;
    SDRAM_Timing.RAStoCASDelay       = 0x4;
    SDRAM_TimingInit(&SDRAM_Timing);
    
     /* Set SDRAM configuration registers*/
    SDRAM_Configuration.SdramEnable         = ENABLE;
    SDRAM_Configuration.RefreshEnable       = ENABLE;
    SDRAM_Configuration.AutoPrechargeEnable = DISABLE;
    SDRAM_Configuration.PrefetchReadEnable  = DISABLE;
    SDRAM_Configuration.SOM_Enable          = ENABLE;
    SDRAM_Configuration.BankInterleavEnable = DISABLE;
    /* Needs to be consistent with SDRAM device characteristics */
    SDRAM_Configuration.BusWidth            = SDRAM_DEVICE_BUSWID_16BITS;
    /* Needs to be consistent with SDRAM_Operation.Address.Bits.BurstLen */
    SDRAM_Configuration.BurstLength         = SDRAM_DEVICE_BURSTLEN_4;
    /* Needs to be consistent with SDRAM_Operation.Address.Bits.CASLatency */
    SDRAM_Configuration.CAS_Latency         = SDRAM_DEVICE_CASLTCY_3;
    /* Needs to be consistent with SDRAM device characteristics */
    SDRAM_Configuration.AddressConfig       = SDRAM_BANK4_ROW4096_COL256;
    SDRAM_ConfigurationInit(SDRAM_DEVICE_1, SDRAM_Configuration);

    /* Precharge all banks, auto-refresh, load mode register */
    /* Precharge all banks */
    SDRAM_Operation.ClockEnable   = ENABLE;
    SDRAM_Operation.OperationCode = SDRAM_OPCODE_PRECHRG;
    SDRAM_Operation.ChipSelect    = SDRAM_CS_SDRAMx;
    SDRAM_Operation.BankAddress   = SDRAM_BANKADD_1;
    SDRAM_Operation.Address.cmd   = 0x00;
    SDRAM_OperationInit(SDRAM_Operation);
    
    /* auto-refresh */
    for(uint8_t i = 0; i < 2; i++)
    {
        SDRAM_Operation.ClockEnable   = ENABLE;
        SDRAM_Operation.OperationCode = SDRAM_OPCODE_REFRESH;
        SDRAM_Operation.ChipSelect    = SDRAM_CS_SDRAMx;
        SDRAM_Operation.BankAddress   = SDRAM_BANKADD_1;
        SDRAM_Operation.Address.cmd   = 0x00;
        SDRAM_OperationInit(SDRAM_Operation);
    }
    
    /* load mode register */
    SDRAM_Operation.ClockEnable   = ENABLE;
    SDRAM_Operation.OperationCode = SDRAM_OPCODE_LOADMODE;
    SDRAM_Operation.ChipSelect    = SDRAM_CS_SDRAMx;     
    SDRAM_Operation.BankAddress   = SDRAM_BANKADD_1;
    SDRAM_Operation.Address.Bits.BurstLen = LOADMODE_BURSTLEN_4;
    SDRAM_Operation.Address.Bits.BurstType = LOADMODE_BURSTTYP_SEQUENTIAL;
    SDRAM_Operation.Address.Bits.CASLatency = LOADMODE_CASLATENCY_3;
    SDRAM_Operation.Address.Bits.OpMode = LOADMODE_STANDARD; 
    SDRAM_Operation.Address.Bits.WBMode = LOADMODE_WRITE_BURST;
    SDRAM_OperationInit(SDRAM_Operation);
    
    /* wait at least 300us*/
    systick_delay_us(500);
}



