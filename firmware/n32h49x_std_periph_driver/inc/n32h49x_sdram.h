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
*\*\file n32h49x_sdram.h
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#ifndef __N32H49X_SDRAM_H__
#define __N32H49X_SDRAM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h49x.h"


/**  SDRAM Timing parameters structure definition   **/
typedef struct
{
	uint32_t RowActiveTime;                /*   Defines the minimum Self Refresh period in number of memory clock cycles.
                                                This parameter can be a value between Min_Data = 1 and Max_Data = 64  TRAS 1 */
	
	uint32_t RowCycleTime;                 /*   Defines the delay between the Refresh command and the Activate command
                                                and the delay between two consecutive Refresh commands in number of
                                                memory clock cycles.
                                                This parameter can be a value between Min_Data = 1 and Max_Data = 64  TRC 2 */
	
    uint32_t RowActToRowActDelay;          /*   Defines the delay between two active commands to different banks
                                            	in number of memory clock cycles.
                                                This parameter can be a value between Min_Data = 1 and Max_Data = 64  TRRD 3 */
	
	uint32_t PrechargeTime;                /*   Defines the delay between a Precharge Command and an other command
                                                in number of memory clock cycles.
                                                This parameter can be a value between Min_Data = 1 and Max_Data = 64 TRP 4 */
	
	uint32_t WriteRecoveryTime;            /*   Defines the Write recovery Time in number of memory clock cycles.
                                                This parameter can be a value between Min_Data = 1 and Max_Data = 64 TWR 5 */

    uint32_t RefreshCycleTime;             /*   Defines the delay between any two consecutive commands in number 
	                                            of memory clock cycles.
                                                This parameter can be a value between Min_Data = 1 and Max_Data = 64  TRFC 6 */
																							
	uint32_t RAStoCASDelay;                /*   Defines the delay between the Activate Command and a Read/Write
                                                command in number of memory clock cycles.
                                                This parameter can be a value between Min_Data = 1 and Max_Data = 16 TRCD 7 */
	
} SDRAM_TimingType;

/** Defines the number of SDRAM Devices    **/
typedef enum
{
    SDRAM_DEVICE_1            = 1,
    SDRAM_DEVICE_2                      
} SDRAM_DeviceType;

/* Address  */
#define SDRAM1_ADDR ((uint32_t)0x98000000) // 0x98000000~9BFFFFFF ->total 64M
#define SDRAM2_ADDR ((uint32_t)0x9C000000) // 0x9C000000~9FFFFFFF ->total 64M


/** Defines the Load Mode Register parameters: M2:0**/
typedef enum
{
    LOADMODE_BURSTLEN_1             = 0,
    LOADMODE_BURSTLEN_2             = 1, 
    LOADMODE_BURSTLEN_4             = 2,
    LOADMODE_BURSTLEN_8             = 3,
    LOADMODE_BURSTLEN_FULLPAGE      = 7    
} SDRAM_LoadMode_BurstLen;

/** Defines the Load Mode Register parameters: M3**/
typedef enum
{
    LOADMODE_BURSTTYP_SEQUENTIAL             = 0,
    LOADMODE_BURSTTYP_INTERLEAVED            = 1                     
} SDRAM_LoadMode_BurstType;

/** Defines the Load Mode Register parameters: M6:4**/
typedef enum
{
    LOADMODE_CASLATENCY_1             = 1,
    LOADMODE_CASLATENCY_2             = 2,
    LOADMODE_CASLATENCY_3             = 3   
} SDRAM_LoadMode_CASLatency;

/** Defines the Load Mode Register parameters: M8:7**/
typedef enum
{
    LOADMODE_STANDARD             = 0,
    LOADMODE_OTHER                = 1                     
} SDRAM_LoadMode_OPModeType;

/** Defines the Load Mode Register parameters: M9**/
typedef enum
{
    LOADMODE_WRITE_BURST             = 0,
    LOADMODE_WRITE_SINGLE            = 1                     
} SDRAM_LoadMode_WBModeType;

/** Defines the SDRAM Load Mode register content          **/
typedef union
{
    uint32_t cmd;
    struct
    {
        uint32_t BurstLen   : 3;
        uint32_t BurstType  : 1;
        uint32_t CASLatency : 3;
        uint32_t OpMode     : 2;
        uint32_t WBMode     : 1;
        uint32_t Reserved                    : 22;
    }Bits;
} SDRAM_LoadModeRegisterType;

/**  SDRAM Operation structure definition   **/
typedef struct
{
    FunctionalState ClockEnable;             /* Enables the SDRAM device clock.   */
    
    uint32_t OperationCode;                  /* Defines the operation code        */
    
    uint32_t ChipSelect;                     /* Defines SDRAM1, or SDRAM2, or All will select  */
    
    uint32_t BankAddress;                    /* Defines the bank address issued to external memory bus.  */          
     
    SDRAM_LoadModeRegisterType Address;      /* Defines the address(bank-row-column) issued to external memory bus.  */   
    
} SDRAM_OperationInitType;


/**  SDRAM Configuration structure definition   **/
typedef struct
{
    FunctionalState SdramEnable;             /* Enables the SDRAM 1 or 2 device.   */
    
    FunctionalState RefreshEnable;             /* Enables the SDRAM Refresh commands .   */
    
    FunctionalState AutoPrechargeEnable;       /* Enables the SDRAM Auto precharge.   */
    
    uint32_t        BusWidth;                  /* Defines the Bus width        */
    
    uint32_t        BurstLength;               /* Defines the SDRAM Burst length.   */
    
    uint32_t        CAS_Latency;               /* Defines the SDRAM CAS latency.   */
    
    FunctionalState PrefetchReadEnable;        /* Enables the SDRAM Prefetch read.   */
    
    FunctionalState SOM_Enable;                /* Enables the SDRAM Store On Miss(SOM) .   */
    
    FunctionalState BankInterleavEnable;       /* Enables the SDRAM Bank interleaving.   */
    
    uint32_t        AddressConfig;             /* Defines the SDRAM Address configuration.   */   
    
} SDRAM_ConfigurationInitType; 

/*** SDRAM Macro Definition Start ***/
#define SDRAM_REG_BIT_MASK                      ((uint32_t)0x00000000U)
/** SDRAM Device Enable **/
#define SDRAM_DEVICE_ENABLE                     (SDRAM_CFG_SDRAMEN)
#define SDRAM_DEVICE_DISABLE                    (~((uint32_t)SDRAM_CFG_SDRAMEN))

/** SDRAM Device Refresh Commands Enable **/
#define SDRAM_DEVICE_REFRESH_ENABLE             (SDRAM_CFG_REFRESHEN)
#define SDRAM_DEVICE_REFRESH_DISABLE            (~((uint32_t)SDRAM_CFG_REFRESHEN))

/** SDRAM Device Auto Precharge Enable **/
#define SDRAM_DEVICE_AUTOPRECHRG_ENABLE         (SDRAM_CFG_AUTOPCHEN)
#define SDRAM_DEVICE_AUTOPRECHRG_DISABLE        (~((uint32_t)SDRAM_CFG_AUTOPCHEN))

/** SDRAM Device Bus Width **/
#define SDRAM_DEVICE_BUSWID_8BITS               SDRAM_REG_BIT_MASK
#define SDRAM_DEVICE_BUSWID_16BITS              (SDRAM_CFG_BUSWID_0)
#define SDRAM_DEVICE_BUSWID_32BITS              (SDRAM_CFG_BUSWID_1)
#define SDRAM_DEVICE_BUSWID_MASK                (~((uint32_t)(SDRAM_CFG_BUSWID)))

/** SDRAM Device Burst Length **/
#define SDRAM_DEVICE_BURSTLEN_1                 SDRAM_REG_BIT_MASK
#define SDRAM_DEVICE_BURSTLEN_2                 (SDRAM_CFG_BURSTLEN_0)
#define SDRAM_DEVICE_BURSTLEN_4                 (SDRAM_CFG_BURSTLEN_0 | SDRAM_CFG_BURSTLEN_1)
#define SDRAM_DEVICE_BURSTLEN_8                 (SDRAM_CFG_BURSTLEN_0 | SDRAM_CFG_BURSTLEN_1 | SDRAM_CFG_BURSTLEN_2)
#define SDRAM_DEVICE_BURSTLEN_MASK              (~((uint32_t)(SDRAM_CFG_BURSTLEN)))

/** SDRAM Device CAS Latency **/
#define SDRAM_DEVICE_CASLTCY_0                  SDRAM_REG_BIT_MASK
#define SDRAM_DEVICE_CASLTCY_1                  (SDRAM_CFG_CASLATENCY_0)
#define SDRAM_DEVICE_CASLTCY_2                  (SDRAM_CFG_CASLATENCY_1)
#define SDRAM_DEVICE_CASLTCY_3                  (SDRAM_CFG_CASLATENCY_0 | SDRAM_CFG_CASLATENCY_1)
#define SDRAM_DEVICE_CASLTCY_MASK               (~((uint32_t)(SDRAM_CFG_CASLATENCY)))

/** SDRAM Device Prefetch Read Enable **/
#define SDRAM_DEVICE_PREFETCHREAD_ENABLE        (SDRAM_CFG_PREFCHRDEN)
#define SDRAM_DEVICE_PREFETCHREADG_DISABLE      (~((uint32_t)SDRAM_CFG_PREFCHRDEN))

/** SDRAM Device Store On Miss Enable **/
#define SDRAM_DEVICE_SOM_ENABLE                 (SDRAM_CFG_SOMEN)
#define SDRAM_DEVICE_SOM_DISABLE                (~((uint32_t)SDRAM_CFG_SOMEN))

/** SDRAM Device Bank Interleaving Enable **/
#define SDRAM_DEVICE_BANKIL_ENABLE              (SDRAM_CFG_BANKINTRLEN)
#define SDRAM_DEVICE_BANKIL_DISABLE             (~((uint32_t)SDRAM_CFG_BANKINTRLEN))

/** SDRAM Device Address Configration **/
#define SDRAM_BANK4_ROW4096_COL256       SDRAM_REG_BIT_MASK
#define SDRAM_BANK4_ROW4096_COL512       (SDRAM_CFG_ADDCFG_0)
#define SDRAM_BANK4_ROW4096_COL1024      (SDRAM_CFG_ADDCFG_1)
#define SDRAM_BANK4_ROW4096_COL2048      (SDRAM_CFG_ADDCFG_0 | SDRAM_CFG_ADDCFG_1)

#define SDRAM_BANK4_ROW8192_COL256       (SDRAM_CFG_ADDCFG_2)
#define SDRAM_BANK4_ROW8192_COL512       (SDRAM_CFG_ADDCFG_0 | SDRAM_CFG_ADDCFG_2)
#define SDRAM_BANK4_ROW8192_COL1024      (SDRAM_CFG_ADDCFG_1 | SDRAM_CFG_ADDCFG_2)
#define SDRAM_BANK4_ROW8192_COL2048      (SDRAM_CFG_ADDCFG_0 | SDRAM_CFG_ADDCFG_1 | SDRAM_CFG_ADDCFG_2)

#define SDRAM_BANK4_ROW2048_COL256       (SDRAM_CFG_ADDCFG_3)
#define SDRAM_BANK4_ROW2048_COL512       (SDRAM_CFG_ADDCFG_0 | SDRAM_CFG_ADDCFG_3)
#define SDRAM_BANK4_ROW2048_COL1024      (SDRAM_CFG_ADDCFG_1 | SDRAM_CFG_ADDCFG_3)
#define SDRAM_BANK4_ROW2048_COL2048      (SDRAM_CFG_ADDCFG_0 | SDRAM_CFG_ADDCFG_1 | SDRAM_CFG_ADDCFG_3)

#define SDRAM_DEVICE_ADDCFG_MASK                (~((uint32_t)SDRAM_CFG_ADDCFG))

/** SDRAM Operatio Setup of Clock enable **/
#define SDRAM_CLOCK_ENABLE                      (SDRAM_OS_CKEN)
#define SDRAM_CLOCK_DISABLE                     (~((uint32_t)SDRAM_OS_CKEN))

/** SDRAM Operatio Setup of Operation Code **/
#define SDRAM_OPCODE_NONE                       SDRAM_REG_BIT_MASK
#define SDRAM_OPCODE_PRECHRG                    (SDRAM_OS_OPCODE_0)
#define SDRAM_OPCODE_REFRESH                    (SDRAM_OS_OPCODE_1)
#define SDRAM_OPCODE_LOADMODE                   (SDRAM_OS_OPCODE_0 | SDRAM_OS_OPCODE_1)
#define SDRAM_OPCODE_MASK                       (~((uint32_t)(SDRAM_OS_OPCODE)))

/** SDRAM Operatio Setup of Chip Select **/
#define SDRAM_CS_ALL                            SDRAM_REG_BIT_MASK
#define SDRAM_CS_SDRAM2_ONLY                    (SDRAM_OS_CS_0)
#define SDRAM_CS_SDRAM1_ONLY                    (SDRAM_OS_CS_1)
#define SDRAM_CS_NONE                           (SDRAM_OS_CS_0 | SDRAM_OS_CS_1)
#define SDRAM_CS_MASK                           (~((uint32_t)(SDRAM_OS_CS)))

/** SDRAM Operatio Setup of Bank Address **/
#define SDRAM_BANKADD_1                         SDRAM_REG_BIT_MASK
#define SDRAM_BANKADD_2                         (SDRAM_OS_BANKADD_0)
#define SDRAM_BANKADD_3                         (SDRAM_OS_BANKADD_1)
#define SDRAM_BANKADD_4                         (SDRAM_OS_BANKADD_0 | SDRAM_OS_BANKADD_1)
#define SDRAM_BANKADD_MASK                      (~((uint32_t)(SDRAM_OS_BANKADD)))

/** SDRAM Operatio Setup of Address **/
#define SDRAM_OS_ADDRESS_MASK                   (~((uint32_t)SDRAM_OS_ADD))

/** SDRAM Write Protection **/
#define SDRAM_WP_SDRAM1_ENABLE                  (SDRAM_WP_WP1)
#define SDRAM_WP_SDRAM1_DISABLE                 (~((uint32_t)SDRAM_WP_WP1))
#define SDRAM_WP_SDRAM2_ENABLE                  (SDRAM_WP_WP2)
#define SDRAM_WP_SDRAM2_DISABLE                 (~((uint32_t)SDRAM_WP_WP2))

#define SDRAM_DELAY_MASK           (!SDRAM_WP_DLYSEL)
#define SDRAM_DELAY_NONE           (SDRAM_REG_BIT_MASK)
#define SDRAM_DELAY_0_5_PERIOD     (SDRAM_WP_DLYSEL_0)
#define SDRAM_DELAY_1_PERIOD       (SDRAM_WP_DLYSEL_1)
#define SDRAM_DELAY_1_5_PERIOD     (SDRAM_WP_DLYSEL_0|SDRAM_WP_DLYSEL_1)
#define SDRAM_DELAY_2_PERIOD       (SDRAM_WP_DLYSEL_2)
#define SDRAM_DELAY_2_5_PERIOD     (SDRAM_WP_DLYSEL_0|SDRAM_WP_DLYSEL_2)
#define SDRAM_DELAY_3_PERIOD       (SDRAM_WP_DLYSEL_1|SDRAM_WP_DLYSEL_2)
#define SDRAM_DELAY_3_5_PERIOD     (SDRAM_WP_DLYSEL_0|SDRAM_WP_DLYSEL_1|SDRAM_WP_DLYSEL_2)
#define SDRAM_DELAY_4_PERIOD       (SDRAM_WP_DLYSEL_3)

#define SDRAM_ADDR_MASK           (~SDRAM_WP_MAPSEL)
#define SDRAM1_64MB_SDRAM2_64MB   (SDRAM_REG_BIT_MASK)
#define SDRAM1_128MB_SDRAM2_NONE  (SDRAM_WP_MAPSEL)
/*** SDRAM Macro Definition End ***/

/** SDRAM Functions **/
void SDRAM_DeInit(void);
void SDRAM_TimingInit(SDRAM_TimingType *Timing);
void SDRAM_RefreshIntervalInit(uint32_t RefreshIntervalTime);
void SDRAM_SetDeviceAddress(SDRAM_DeviceType DeviceNo, uint32_t BaseAddr, uint32_t AddrMask);
void SDRAM_EnableDevice(SDRAM_DeviceType DeviceNo, FunctionalState Cmd);
void SDRAM_EnableRefreshCMD(SDRAM_DeviceType DeviceNo, FunctionalState Cmd);
void SDRAM_EnableAutoPrecharge(SDRAM_DeviceType DeviceNo, FunctionalState Cmd);
void SDRAM_EnablePrefetchRead(SDRAM_DeviceType DeviceNo, FunctionalState Cmd);
void SDRAM_EnableSOM(SDRAM_DeviceType DeviceNo, FunctionalState Cmd);
void SDRAM_EnableBankInterleave(SDRAM_DeviceType DeviceNo, FunctionalState Cmd);
void SDRAM_ConfigBusWidth(SDRAM_DeviceType DeviceNo, uint32_t BusWidth);
void SDRAM_ConfigBurstLength(SDRAM_DeviceType DeviceNo, uint32_t BurstLength);
void SDRAM_ConfigCASLatency(SDRAM_DeviceType DeviceNo, uint32_t Latency);
void SDRAM_ConfigAddress(SDRAM_DeviceType DeviceNo, uint32_t Address);
void SDRAM_EnableClock(FunctionalState Cmd);
void SDRAM_SetOperationCode(uint32_t OperationCode);
void SDRAM_SetDeviceSelect(uint32_t ChipSelect);
void SDRAM_SetBank(uint32_t BankNo);
void SDRAM_SetAddress(uint32_t Address);
void SDRAM_EnableWriteProtection(SDRAM_DeviceType DeviceNo, FunctionalState Cmd);
void SDRAM_ConfigSampleDelay(uint32_t CLK_delay);
void SDRAM_ConfigAddressRemap(uint32_t map_sel);
void SDRAM_OperationInit(SDRAM_OperationInitType SDRAM_OS);
void SDRAM_ConfigurationInit(SDRAM_DeviceType DeviceNo, SDRAM_ConfigurationInitType SDRAM_CFG);

#ifdef __cplusplus
}
#endif

#endif /*__N32H49X_SDRAM_H__ */

