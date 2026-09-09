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
*\*\file n32h49x_sdram.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#include "n32h49x_sdram.h"
#include "n32h49x_rcc.h"

/**
*\*\name    SDRAM_DeInit.
*\*\fun     Deinitializes the SDRAM module to their default reset values.
*\*\param   none
*\*\return  none
**/
void SDRAM_DeInit(void)
{
    /* SDRAM soft reset */
    RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_SDRAM);
}

/**
*\*\name    SDRAM_TimingInit.
*\*\fun     SDRAM Timing Registers Configuration.
*\*\param   Timing: The parameter range is as follows
*\*\            - RowActiveTime       : from 1 to 64
*\*\            - RowCycleTime        : from 1 to 64
*\*\            - RowActToRowActDelay : from 1 to 64
*\*\            - PrechargeTime       : from 1 to 64
*\*\            - WriteRecoveryTime   : from 1 to 64
*\*\            - RefreshCycleTime    : from 1 to 64
*\*\            - RAStoCASDelay       : from 1 to 16
*\*\return  none
**/
void SDRAM_TimingInit(SDRAM_TimingType *Timing)
{
    SDRAM->RAT    = Timing->RowActiveTime;
    SDRAM->RCT    = Timing->RowCycleTime;
    SDRAM->RRDLY  = Timing->RowActToRowActDelay;
    SDRAM->PT     = Timing->PrechargeTime;
    SDRAM->WRT    = Timing->WriteRecoveryTime;
    SDRAM->RFCT   = Timing->RefreshCycleTime;
    SDRAM->RCDLY  = Timing->RAStoCASDelay;
}

/**
*\*\name    SDRAM_RefreshIntervalInit.
*\*\fun     Configure the refresh interval parameter.
*\*\param   The input parameters must be the following values:
*\*\          - RefreshIntervalTime: from 1 to 16777216
*\*\return  none
**/
void SDRAM_RefreshIntervalInit(uint32_t RefreshIntervalTime)
{
    SDRAM->RI = RefreshIntervalTime;
}

/**
*\*\name    SDRAM_SetAddress.
*\*\fun     SDRAM set Base Address and mask address.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - BaseAddr
*\*\               - 0xC0000000    Default value for SDRAM1
*\*\               - 0xD0000000    Default value for SDRAM2
*\*\          - AddrMask
*\*\               - (0xFFFFFFFF-(SDRAM SIZE-1))
*\*\return  none
**/
void SDRAM_SetDeviceAddress(SDRAM_DeviceType DeviceNo, uint32_t BaseAddr, uint32_t AddrMask)
{
    if(DeviceNo == SDRAM_DEVICE_1)
    {
        SDRAM->BADD1    = BaseAddr;
        SDRAM->ADDMASK1 = AddrMask;
    }
    else
    {
        SDRAM->BADD2    = BaseAddr;
        SDRAM->ADDMASK2 = AddrMask;
    }
}

/**
*\*\name    SDRAM_EnableDevice.
*\*\fun     SDRAM Device enable.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableDevice(SDRAM_DeviceType DeviceNo, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SDRAM Device*/
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 |= SDRAM_DEVICE_ENABLE;
        }
        else
        {
            SDRAM->CFG2 |= SDRAM_DEVICE_ENABLE;
        }
    }
    else
    {
        /* Disable the selected SDRAM Device */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 &= SDRAM_DEVICE_DISABLE;
        }
        else
        {
            SDRAM->CFG2 &= SDRAM_DEVICE_DISABLE;
        }
    }
}

/**
*\*\name    SDRAM_EnableRefreshCMD.
*\*\fun     SDRAM Refresh enable of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableRefreshCMD(SDRAM_DeviceType DeviceNo, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SDRAM Refresh */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 |= SDRAM_DEVICE_REFRESH_ENABLE;
        }
        else
        {
            SDRAM->CFG2 |= SDRAM_DEVICE_REFRESH_ENABLE;
        }
    }
    else
    {
        /* Disable the selected SDRAM Refresh */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 &= SDRAM_DEVICE_REFRESH_DISABLE;
        }
        else
        {
            SDRAM->CFG2 &= SDRAM_DEVICE_REFRESH_DISABLE;
        }
    }
}

/**
*\*\name    SDRAM_EnableAutoPrecharge.
*\*\fun     SDRAM Auto Precharge enable of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableAutoPrecharge(SDRAM_DeviceType DeviceNo, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SDRAM Auto Precharge */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 |= SDRAM_DEVICE_AUTOPRECHRG_ENABLE;
        }
        else
        {
            SDRAM->CFG2 |= SDRAM_DEVICE_AUTOPRECHRG_ENABLE;
        }
    }
    else
    {
        /* Disable the selected SDRAM Auto Precharge */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 &= SDRAM_DEVICE_AUTOPRECHRG_DISABLE;
        }
        else
        {
            SDRAM->CFG2 &= SDRAM_DEVICE_AUTOPRECHRG_DISABLE;
        }
    }
}

/**
*\*\name    SDRAM_EnablePrefetchRead.
*\*\fun     SDRAM Prefetch Read enable of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnablePrefetchRead(SDRAM_DeviceType DeviceNo, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SDRAM Prefetch Read */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 |= SDRAM_DEVICE_PREFETCHREAD_ENABLE;
        }
        else
        {
            SDRAM->CFG2 |= SDRAM_DEVICE_PREFETCHREAD_ENABLE;
        }
    }
    else
    {
        /* Disable the selected SDRAM Prefetch Read */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 &= SDRAM_DEVICE_PREFETCHREADG_DISABLE;
        }
        else
        {
            SDRAM->CFG2 &= SDRAM_DEVICE_PREFETCHREADG_DISABLE;
        }
    }
}

/**
*\*\name    SDRAM_EnableSOM.
*\*\fun     SDRAM Store On Miss(SOM) enable of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableSOM(SDRAM_DeviceType DeviceNo, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SDRAM Store On Miss(SOM) */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 |= SDRAM_DEVICE_SOM_ENABLE;
        }
        else
        {
            SDRAM->CFG2 |= SDRAM_DEVICE_SOM_ENABLE;
        }
    }
    else
    {
        /* Disable the selected SDRAM Store On Miss(SOM) */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 &= SDRAM_DEVICE_SOM_DISABLE;
        }
        else
        {
            SDRAM->CFG2 &= SDRAM_DEVICE_SOM_DISABLE;
        }
    }
}

/**
*\*\name    SDRAM_EnableBankInterleave.
*\*\fun     SDRAM BankInterleave enable of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableBankInterleave(SDRAM_DeviceType DeviceNo, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SDRAM BankInter leave */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 |= SDRAM_DEVICE_BANKIL_ENABLE;
        }
        else
        {
            SDRAM->CFG2 |= SDRAM_DEVICE_BANKIL_ENABLE;
        }
    }
    else
    {
        /* Disable the selected SDRAM Bank Interleave */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->CFG1 &= SDRAM_DEVICE_BANKIL_DISABLE;
        }
        else
        {
            SDRAM->CFG2 &= SDRAM_DEVICE_BANKIL_DISABLE;
        }
    }
}

/**
*\*\name    SDRAM_ConfigBusWidth.
*\*\fun     Configures the SDRAM Bus Width of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - BusWidth:
*\*\               - SDRAM_DEVICE_BUSWID_8BITS
*\*\               - SDRAM_DEVICE_BUSWID_16BITS
*\*\               - SDRAM_DEVICE_BUSWID_32BITS
*\*\return  none
**/
void SDRAM_ConfigBusWidth(SDRAM_DeviceType DeviceNo, uint32_t BusWidth)
{
    uint32_t reg_value;

    /* Configures the selected SDRAM Bus Width */
    if(DeviceNo == SDRAM_DEVICE_1)
    {
        reg_value = SDRAM->CFG1;
        reg_value &= SDRAM_DEVICE_BUSWID_MASK;
        reg_value |= BusWidth;
        SDRAM->CFG1 = reg_value;
    }
    else
    {
        reg_value = SDRAM->CFG2;
        reg_value &= SDRAM_DEVICE_BUSWID_MASK;
        reg_value |= BusWidth;
        SDRAM->CFG2 = reg_value;
    }
}

/**
*\*\name    SDRAM_ConfigBurstLength.
*\*\fun     Configures the SDRAM Burst Length of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - BurstLength:
*\*\               - SDRAM_DEVICE_BURSTLEN_1
*\*\               - SDRAM_DEVICE_BURSTLEN_2
*\*\               - SDRAM_DEVICE_BURSTLEN_4
*\*\               - SDRAM_DEVICE_BURSTLEN_8
*\*\return  none
**/
void SDRAM_ConfigBurstLength(SDRAM_DeviceType DeviceNo, uint32_t BurstLength)
{
    uint32_t reg_value;

    /* Configures the selected SDRAM Burst Length */
    if(DeviceNo == SDRAM_DEVICE_1)
    {
        reg_value = SDRAM->CFG1;
        reg_value &= SDRAM_DEVICE_BURSTLEN_MASK;
        reg_value |= BurstLength;
        SDRAM->CFG1 = reg_value;
    }
    else
    {
        reg_value = SDRAM->CFG2;
        reg_value &= SDRAM_DEVICE_BURSTLEN_MASK;
        reg_value |= BurstLength;
        SDRAM->CFG2 = reg_value;
    }
}

/**
*\*\name    SDRAM_ConfigCASLatency.
*\*\fun     Configures the SDRAM CAS Latency of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - CASLatency:
*\*\               - SDRAM_DEVICE_CASLTCY_0
*\*\               - SDRAM_DEVICE_CASLTCY_1
*\*\               - SDRAM_DEVICE_CASLTCY_2
*\*\               - SDRAM_DEVICE_CASLTCY_3
*\*\return  none
**/
void SDRAM_ConfigCASLatency(SDRAM_DeviceType DeviceNo, uint32_t Latency)
{
    uint32_t reg_value;

    /* Configures the selected SDRAM CAS Latency */
    if(DeviceNo == SDRAM_DEVICE_1)
    {
        reg_value = SDRAM->CFG1;
        reg_value &= SDRAM_DEVICE_CASLTCY_MASK;
        reg_value |= Latency;
        SDRAM->CFG1 = reg_value;
    }
    else
    {
        reg_value = SDRAM->CFG2;
        reg_value &= SDRAM_DEVICE_CASLTCY_MASK;
        reg_value |= Latency;
        SDRAM->CFG2 = reg_value;
    }
}

/**
*\*\name    SDRAM_ConfigAddress.
*\*\fun     Configures the SDRAM Address of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Address:
*\*\               - SDRAM_BANK4_ROW4096_COL256
*\*\               - SDRAM_BANK4_ROW4096_COL512
*\*\               - SDRAM_BANK4_ROW4096_COL1024
*\*\               - SDRAM_BANK4_ROW4096_COL2048
*\*\               - SDRAM_BANK4_ROW8192_COL256
*\*\               - SDRAM_BANK4_ROW8192_COL512
*\*\               - SDRAM_BANK4_ROW8192_COL1024
*\*\               - SDRAM_BANK4_ROW8192_COL2048
*\*\               - SDRAM_BANK4_ROW2048_COL256
*\*\               - SDRAM_BANK4_ROW2048_COL512
*\*\               - SDRAM_BANK4_ROW2048_COL1024
*\*\               - SDRAM_BANK4_ROW2048_COL2048
*\*\return  none
**/
void SDRAM_ConfigAddress(SDRAM_DeviceType DeviceNo, uint32_t Address)
{
    uint32_t reg_value;

    /* Configures the selected SDRAM Address */
    if(DeviceNo == SDRAM_DEVICE_1)
    {
        reg_value = SDRAM->CFG1;
        reg_value &= SDRAM_DEVICE_ADDCFG_MASK;
        reg_value |= Address;
        SDRAM->CFG1 = reg_value;
    }
    else
    {
        reg_value = SDRAM->CFG2;
        reg_value &= SDRAM_DEVICE_ADDCFG_MASK;
        reg_value |= Address;
        SDRAM->CFG2 = reg_value;
    }
}

/**
*\*\name    SDRAM_EnableClock.
*\*\fun     SDRAM Clock enable.
*\*\param   The input parameters must be the following values:
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableClock(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the SDRAM Clock */
        SDRAM->OS |= SDRAM_CLOCK_ENABLE;
    }
    else
    {
        /* Disable the SDRAM Clock */
        SDRAM->OS &= SDRAM_CLOCK_DISABLE;
    }
}

/**
*\*\name    SDRAM_SetOperationCode.
*\*\fun     Set the SDRAM Operation Code.
*\*\param   The input parameters must be the following values:
*\*\          - OperationCode:
*\*\               - SDRAM_OPCODE_NONE
*\*\               - SDRAM_OPCODE_PRECHRG
*\*\               - SDRAM_OPCODE_REFRESH
*\*\               - SDRAM_OPCODE_LOADMODE
*\*\return  none
**/
void SDRAM_SetOperationCode(uint32_t OperationCode)
{
    uint32_t reg_value;

    reg_value = SDRAM->OS;
    /* Clear the SDRAM Operation Code */
    reg_value &= SDRAM_OPCODE_MASK;
    /* Set the SDRAM Operation Code */
    reg_value |= OperationCode;
    SDRAM->OS = reg_value;
}

/**
*\*\name    SDRAM_SetDeviceSelect.
*\*\fun     Set the SDRAM Device.
*\*\param   The input parameters must be the following values:
*\*\          - ChipSelect:
*\*\               - SDRAM_CS_ALL
*\*\               - SDRAM_CS_SDRAM2_ONLY
*\*\               - SDRAM_CS_SDRAM1_ONLY
*\*\               - SDRAM_CS_NONE
*\*\return  none
**/
void SDRAM_SetDeviceSelect(uint32_t ChipSelect)
{
    uint32_t reg_value;

    reg_value = SDRAM->OS;
    /* Clear the SDRAM Device */
    reg_value &= SDRAM_CS_MASK;
    /* Set the SDRAM Device */
    reg_value |= ChipSelect;
    SDRAM->OS = reg_value;
}

/**
*\*\name    SDRAM_SetBank.
*\*\fun     Set the SDRAM Bank.
*\*\param   The input parameters must be the following values:
*\*\          - BankNo:
*\*\               - SDRAM_BANKADD_1
*\*\               - SDRAM_BANKADD_2
*\*\               - SDRAM_BANKADD_3
*\*\               - SDRAM_BANKADD_4
*\*\return  none
**/
void SDRAM_SetBank(uint32_t BankNo)
{
    uint32_t reg_value;

    reg_value = SDRAM->OS;
    /* Clear the SDRAM Bank */
    reg_value &= SDRAM_BANKADD_MASK;
    /* Set the SDRAM Bank */
    reg_value |= BankNo;
    SDRAM->OS = reg_value;
}

/**
*\*\name    SDRAM_SetAddress.
*\*\fun     Set the SDRAM Bank.
*\*\param   The input parameters must be the following values:
*\*\          - Address:
*\*\return  none
**/
void SDRAM_SetAddress(uint32_t Address)
{
    uint32_t reg_value;

    reg_value = SDRAM->OS;
    /* Clear the SDRAM Address */
    reg_value &= SDRAM_OS_ADDRESS_MASK;
    /* Set the SDRAM Address */
    reg_value |= (Address & SDRAM_OS_ADD);
    SDRAM->OS = reg_value;
}

/**
*\*\name    SDRAM_EnableWriteProtection.
*\*\fun     Write protection enable of the selected device.
*\*\param   The input parameters must be the following values:
*\*\          - DeviceNo:
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - Cmd:
*\*\               - ENABLE
*\*\               - DISABLE
*\*\return  none
**/
void SDRAM_EnableWriteProtection(SDRAM_DeviceType DeviceNo, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the Write protection of selected SDRAM Device*/
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->WP |= SDRAM_WP_SDRAM1_ENABLE;
        }
        else
        {
            SDRAM->WP |= SDRAM_WP_SDRAM2_ENABLE;
        }
    }
    else
    {
        /* Disable the Write protection of selected SDRAM Device */
        if(DeviceNo == SDRAM_DEVICE_1)
        {
            SDRAM->WP &= SDRAM_WP_SDRAM1_DISABLE;
        }
        else
        {
            SDRAM->WP &= SDRAM_WP_SDRAM2_DISABLE;
        }
    }
}

/**
*\*\name   SDRAM_ConfigSampleDelay .
*\*\fun    Increase SDRAM sample clock latency.
*\*\param  CLK_delay
*\*\       - SDRAM_DELAY_NONE          Delay bypass
*\*\       - SDRAM_DELAY_0_5_PERIOD    Delay 0.5 sdram_clk period
*\*\       - SDRAM_DELAY_1_PERIOD      Delay 1 sdram_clk period
*\*\       - SDRAM_DELAY_1_5_PERIOD    Delay 1.5 sdram_clk period
*\*\       - SDRAM_DELAY_2_PERIOD      Delay 2 sdram_clk period
*\*\       - SDRAM_DELAY_2_5_PERIOD    Delay 2.5 sdram_clk period
*\*\       - SDRAM_DELAY_3_PERIOD      Delay 3 sdram_clk period
*\*\       - SDRAM_DELAY_3_5_PERIOD    Delay 3.5 sdram_clk period
*\*\       - SDRAM_DELAY_4_PERIOD      Delay 4 sdram_clk period
*\*\return none.
**/
void SDRAM_ConfigSampleDelay(uint32_t CLK_delay)
{
    uint32_t reg_value;

    reg_value = SDRAM->WP;
    /* Clear DLYSEL  bits */
    reg_value &=  SDRAM_DELAY_MASK;
    /* Set the DLYSEL  bits */
    reg_value |=  CLK_delay;
    /* Store the new value */
    SDRAM->WP = reg_value;
}


/**
*\*\name    SDRAM_ConfigAddressRemap.
*\*\fun     Config SDRAM1 and SDRAM2 address range.
*\*\param  map_sel
*\*\       - SDRAM1_64MB_SDRAM2_64MB     SDRAM1 range is 0x98000000~0x9BFFFFFF; SDRAM2 range is 0x9C000000~0x9FFFFFFF
*\*\       - SDRAM1_128MB_SDRAM2_NONE    SDRAM1 range is 0x98000000~0x9FFFFFFF; SDRAM2 is unavailable
*\*\return  none
**/
void SDRAM_ConfigAddressRemap(uint32_t map_sel)
{
    uint32_t reg_value;

    reg_value = SDRAM->WP;
    /* Clear MAPSEL  bits */
    reg_value &=  SDRAM_ADDR_MASK;
    /* Set the MAPSEL  bits */
    reg_value |=  map_sel;
    /* Store the new value */
    SDRAM->WP = reg_value;
}

/**
*\*\name    SDRAM_OperationInit.
*\*\fun     Initialization SDRAM using Precharge all banks, auto-refresh and load mode register
*\*\param   The input parameters must be the following values: 
*\*\          - SDRAM_OS: 
*\*\               - ClockEnable:
*\*\                   - ENABLE
*\*\                   - DISABLE 
*\*\               - OperationCode:
*\*\                   - NO_OPERATION
*\*\                   - PRECHARGE_ALL_DEVICE    
*\*\                   - REFRESH(when ClockEnable = ENABLE is auto refresh; when  ClockEnable = DISABLE is self refresh)                
*\*\                   - LOAD_MODE_REGISTER   
*\*\               - ChipSelect:
*\*\                   - SDRAM_CS_ALL
*\*\                   - SDRAM_CS_SDRAM2_ONLY
*\*\                   - SDRAM_CS_SDRAM1_ONLY
*\*\                   - SDRAM_CS_NONE 
*\*\               - BankAddress:
*\*\               - Address: load mode register parameters
*\*\                   - BurstLen : 3;
*\*\                   - BurstType : 1;
*\*\                   - CASLatency : 3;
*\*\                   - OpMode : 2;
*\*\                   - WBMode : 1;
*\*\return  none
**/
void SDRAM_OperationInit(SDRAM_OperationInitType SDRAM_OS)
{  
    /* Set the clock enable */
    SDRAM_EnableClock(SDRAM_OS.ClockEnable);
    
    /*Set the OP_CODE */
    SDRAM_SetOperationCode(SDRAM_OS.OperationCode);
    
    //SDRAM->OS |= 0x0C000000;//reserve 26\27
    
    /*Set the sdram cs */
    SDRAM_SetDeviceSelect(SDRAM_OS.ChipSelect);
    
    /*Set Bank address */
    SDRAM_SetBank(SDRAM_OS.BankAddress);
    
    /*Set address */
    SDRAM_SetAddress(SDRAM_OS.Address.cmd);

    /*A dummy access to activate previous SDRAM_OS configuration, read/write data is dont care*/
    (void)(SDRAM->OR);
}

/**
*\*\name    SDRAM_ConfigurationInit.
*\*\fun     Configure SDRAM1 or 2 bus width, burst length, latency, and other information
*\*\param   The input parameters must be the following values: 
*\*\          - DeviceNo: 
*\*\               - SDRAM_DEVICE_1
*\*\               - SDRAM_DEVICE_2
*\*\          - SDRAM_CFG: 
*\*\               - SdramEnable:
*\*\                   - ENABLE
*\*\                   - DISABLE 
*\*\               - RefreshEnable:
*\*\                   - ENABLE
*\*\                   - DISABLE 
*\*\               - AutoPrechargeEnable:
*\*\                   - ENABLE
*\*\                   - DISABLE 
*\*\               - PrefetchReadEnable:
*\*\                   - ENABLE
*\*\                   - DISABLE 
*\*\               - SOM_Enable:
*\*\                   - ENABLE
*\*\                   - DISABLE 
*\*\               - BankInterleavEnable:
*\*\                   - ENABLE
*\*\                   - DISABLE 
*\*\               - BusWidth:
*\*\                   - SDRAM_DEVICE_BUSWID_8BITS
*\*\                   - SDRAM_DEVICE_BUSWID_16BITS
*\*\                   - SDRAM_DEVICE_BUSWID_32BITS
*\*\               - BurstLength:
*\*\                   - SDRAM_DEVICE_BURSTLEN_1
*\*\                   - SDRAM_DEVICE_BURSTLEN_2
*\*\                   - SDRAM_DEVICE_BURSTLEN_4
*\*\                   - SDRAM_DEVICE_BURSTLEN_8
*\*\               - CAS_Latency: 
*\*\                   - SDRAM_DEVICE_CASLTCY_0
*\*\                   - SDRAM_DEVICE_CASLTCY_1
*\*\                   - SDRAM_DEVICE_CASLTCY_2
*\*\                   - SDRAM_DEVICE_CASLTCY_3
*\*\               - AddressConfig:
*\*\                   - SDRAM_BANK4_ROW4096_COL256 
*\*\                   - SDRAM_BANK4_ROW4096_COL512 
*\*\                   - SDRAM_BANK4_ROW4096_COL1024
*\*\                   - SDRAM_BANK4_ROW4096_COL2048
*\*\                   - SDRAM_BANK4_ROW8192_COL256 
*\*\                   - SDRAM_BANK4_ROW8192_COL512 
*\*\                   - SDRAM_BANK4_ROW8192_COL1024
*\*\                   - SDRAM_BANK4_ROW8192_COL2048
*\*\                   - SDRAM_BANK4_ROW2048_COL256 
*\*\                   - SDRAM_BANK4_ROW2048_COL512 
*\*\                   - SDRAM_BANK4_ROW2048_COL1024
*\*\                   - SDRAM_BANK4_ROW2048_COL2048
*\*\return  none
**/
void SDRAM_ConfigurationInit(SDRAM_DeviceType DeviceNo, SDRAM_ConfigurationInitType SDRAM_CFG)
{
    /* Set the clock enable */
    SDRAM_EnableDevice(DeviceNo, SDRAM_CFG.SdramEnable);

    SDRAM_EnableRefreshCMD(DeviceNo, SDRAM_CFG.RefreshEnable);
    
    SDRAM_EnableAutoPrecharge(DeviceNo, SDRAM_CFG.AutoPrechargeEnable);
    
    SDRAM_EnablePrefetchRead(DeviceNo, SDRAM_CFG.PrefetchReadEnable);
    
    SDRAM_EnableSOM(DeviceNo, SDRAM_CFG.SOM_Enable);
    
    SDRAM_EnableBankInterleave(DeviceNo, SDRAM_CFG.BankInterleavEnable);
    
    SDRAM_ConfigBusWidth(DeviceNo, SDRAM_CFG.BusWidth);
    
    SDRAM_ConfigBurstLength(DeviceNo, SDRAM_CFG.BurstLength);
    
    SDRAM_ConfigCASLatency(DeviceNo, SDRAM_CFG.CAS_Latency);
    
    SDRAM_ConfigAddress(DeviceNo, SDRAM_CFG.AddressConfig);
    
}


