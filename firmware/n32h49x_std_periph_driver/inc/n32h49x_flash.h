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
*\*\file n32h49x_flash.h
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#ifndef __N32H49X_FLASH_H__
#define __N32H49X_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h49x.h"

/** FLASH Status **/
typedef enum
{
    FLASH_EOP = 1,
    FLASH_BUSY,
    FLASH_ERR_PG,
    FLASH_ERR_WRP,
    FLASH_ERR_PV,
    FLASH_ERR_EV,
    FLASH_ERR_RPADD,
    FLASH_ERR_RDP2,
    FLASH_ERR_ADD,
    FLASH_TIMEOUT
} FLASH_STS;


/** Flash_Latency **/
#define FLASH_LATENCY_0     ((uint32_t)FLASH_AC_LATENCY_0) /* FLASH Zero Latency cycle */
#define FLASH_LATENCY_1     ((uint32_t)FLASH_AC_LATENCY_1) /* FLASH One Latency cycle */
#define FLASH_LATENCY_2     ((uint32_t)FLASH_AC_LATENCY_2) /* FLASH Two Latency cycle */
#define FLASH_LATENCY_3     ((uint32_t)FLASH_AC_LATENCY_3) /* FLASH Three Latency cycle */
#define FLASH_LATENCY_4     ((uint32_t)FLASH_AC_LATENCY_4) /* FLASH Four Latency cycle */
#define FLASH_LATENCY_MASK  ((uint32_t)FLASH_AC_LATENCY)

/** Flash Access Control Register bits **/
#define FLASH_PRFTBS_MSK                  ((uint32_t)FLASH_AC_PRFTBFSTS)
/** Prefetch_Buffer_Enable_Disable **/
#define FLASH_PrefetchBuf_EN              ((uint32_t)FLASH_AC_PRFTBFEN)            /* FLASH Prefetch Buffer Enable */
#define FLASH_PrefetchBuf_DIS             ((uint32_t)0x00000000U)         		   /* FLASH Prefetch Buffer Disable */
#define FLASH_PrefetchBuf_MSK             (~((uint32_t)FLASH_AC_PRFTBFEN))         /* FLASH Prefetch Buffer mask */

/* FLASH BANK Type */
#define FLASH_BANK1                ((uint32_t)0x00000001U)
#define FLASH_BANK2                ((uint32_t)0x00000002U)

/** iCache_Enable_Disable **/
#define AC_ICAHEN_MSK                ((uint32_t)(~FLASH_AC_ICAHEN1))
#define FLASH_iCache_EN              ((uint32_t)FLASH_AC_ICAHEN1) /* FLASH iCache Enable */
#define FLASH_iCache_DIS             ((uint32_t)0x00000000U) /* FLASH iCache Disable */
#define FLASH_DCache_EN              ((uint32_t)FLASH_AC_DCAHEN) /* FLASH DCache Enable */
#define FLASH_DCache_DIS             ((uint32_t)0x00000000U) /* FLASH DCache Disable */


/** FLASH Keys **/
#define FLASH_KEY1   ((uint32_t)0x45670123U)
#define FLASH_KEY2   ((uint32_t)0xCDEF89ABU)

/** CCM Keys **/
#define CCM_KEY1   ((uint32_t)0xCAU)
#define CCM_KEY2   ((uint32_t)0x53U)

/** Flash Control Register bits **/
#define CTRL_Set_LOCK           ((uint32_t)FLASH_CTRL_LOCK)
#define FLASH_CTRL_SET_OPTWE    ((uint32_t)FLASH_CTRL_OPTWE)

#define CTRL_Set_PG             ((uint32_t)FLASH_CTRL_PG)
#define CTRL_Reset_PG           (~((uint32_t)FLASH_CTRL_PG))
#define CTRL_Set_PER            ((uint32_t)FLASH_CTRL_PER)
#define CTRL_Reset_PER          (~((uint32_t)FLASH_CTRL_PER))
#define CTRL_Set_MER1           ((uint32_t)FLASH_CTRL_MER1)
#define CTRL_Reset_MER1         (~((uint32_t)FLASH_CTRL_MER1))
#define CTRL_Set_OPTPG          ((uint32_t)FLASH_CTRL_OPTPG)
#define CTRL_Reset_OPTPG        (~((uint32_t)FLASH_CTRL_OPTPG))
#define CTRL_Set_OPTER          ((uint32_t)FLASH_CTRL_OPTER)
#define CTRL_Reset_OPTER        (~((uint32_t)FLASH_CTRL_OPTER))
#define CTRL_Set_START          ((uint32_t)FLASH_CTRL_START)
#define CTRL_Set_MER2           ((uint32_t)FLASH_CTRL_MER2)
#define CTRL_Reset_MER2         (~((uint32_t)FLASH_CTRL_MER2))


/** Delay definition **/
#define EraseTimeout      ((uint32_t)0x00200000U)
#define ProgramTimeout    ((uint32_t)0x00002000U)
#define RowProgramTimeout ((uint32_t)0x00010000U)

#define FLASH_WORD_LENGTH   ((uint32_t)0x00000007U)

/** Option_Bytes_RDPx **/
#define FLASH_OB_RDP1_ENABLE            ((uint8_t)0x00U) /* Enable RDP1 */
#define FLASH_OB_RDP1_DISABLE           ((uint8_t)0xA5U) /* DISABLE RDP1 */

#define FLASH_OB_RDP2_ENABLE            ((uint8_t)0xCCU) /* Enable RDP2 */
#define FLASH_OB_RDP2_DISABLE           ((uint8_t)0x00U) /* Disable RDP2 */

/** CCMSRAM_RST **/
#define CCMSRAM_RST_NERASE              ((uint8_t)0x00U) /* CCMSRAM reset not erase */
#define CCMSRAM_RST_ERASE               ((uint8_t)0xABU) /* CCMSRAM reset erase */

/** DBANK **/
#define FLASH_SINGLE_BANK               ((uint8_t)0x5AU) /* Single Bank Mode */
#define FLASH_DUAL_BANK                 ((uint8_t)0x00U) /* Dual Bank Mode */

/** Option_Bytes_IWatchdog **/
#define FLASH_OB_IWDG_SOFTWARE          ((uint16_t)0x0001U) /* Software IWDG selected */
#define FLASH_OB_IWDG_HARDWARE          ((uint16_t)0x0000U) /* Hardware IWDG selected */

/** Option_Bytes_nRST_STOP **/
#define FLASH_OB_STOP_NORST             ((uint16_t)0x0002U) /* No reset generated when entering in STOP */
#define FLASH_OB_STOP_RST               ((uint16_t)0x0000U) /* Reset generated when entering in STOP */

/** Option_Bytes_nRST_STDBY **/
#define FLASH_OB_STDBY_NORST            ((uint16_t)0x0004U) /* No reset generated when entering in standby */
#define FLASH_OB_STDBY_RST              ((uint16_t)0x0000U) /* Reset generated when entering in standby */

/** Option_Bytes_IWatchdog_STOP **/
#define FLASH_OB_IWDG_STOP_FRZ          ((uint16_t)0x0000U) /* IWDG freeze in stop */
#define FLASH_OB_IWDG_STOP_NOFRZ        ((uint16_t)0x0008U) /* Default no freeze */

/** Option_Bytes_IWatchdog_STDBY **/
#define FLASH_OB_IWDG_STDBY_FRZ         ((uint16_t)0x0000U) /* IWDG freeze in standby */
#define FLASH_OB_IWDG_STDBY_NOFRZ       ((uint16_t)0x0020U) /* Default no freeze */

/** Option_Bytes_IWatchdog_SLEEP **/
#define FLASH_OB_IWDG_SLEEP_FRZ         ((uint16_t)0x0000U) /* IWDG freeze in sleep */
#define FLASH_OB_IWDG_SLEEP_NOFRZ       ((uint16_t)0x0040U) /* Default no freeze */

/** USER2 **/
#define FLASH_OB2_NBOOT0_SET                ((uint8_t)0x01U) /* Set nBOOT0 */
#define FLASH_OB2_NBOOT0_CLR                ((uint8_t)0x00U) /* Clear nBOOT0 */

#define FLASH_OB2_NBOOT1_SET                ((uint8_t)0x02U) /* Set nBOOT1 */
#define FLASH_OB2_NBOOT1_CLR                ((uint8_t)0x00U) /* Clear nBOOT1 */

#define FLASH_OB2_NSWBOOT0_SET              ((uint8_t)0x04U) /* Set nSWBOOT0 */
#define FLASH_OB2_NSWBOOT0_CLR              ((uint8_t)0x00U) /* Clear nSWBOOT0 */

#define FLASH_OB2_FLASHBOOT_SET             ((uint8_t)0x08U) /* Main flash forward section boot */
#define FLASH_OB2_FLASHBOOT_CLR             ((uint8_t)0x00U) /* Main flash back part boot */

#define FLASH_OB2_DAC_SET                   ((uint8_t)0x10U) /* System reset, DAC voltage value maintained */
#define FLASH_OB2_DAC_CLR                   ((uint8_t)0x00U) /* System reset, DAC voltage value not maintained */

#define BOR_LEVEL_1_6V                      ((uint8_t)0x00U) /* Reset level threshold 1.6V (Up 1.66V / Down 1.62V) */
#define BOR_LEVEL_2_0V                      ((uint8_t)0x01U) /* Reset level threshold 2.0V (Up 2.1V / Down 2.0V) */
#define BOR_LEVEL_2_2V                      ((uint8_t)0x02U) /* Reset level threshold 2.2V (Up 2.3V / Down 2.2V) */
#define BOR_LEVEL_2_5V                      ((uint8_t)0x03U) /* Reset level threshold 2.5V (Up 2.6V / Down 2.5V) */
#define BOR_LEVEL_2_8V                      ((uint8_t)0x04U) /* Reset level threshold 2.8V (Up 2.9V / Down 2.8V) */

/*data0 and data1*/
#define FLASH_OB_DATA0_MASK             (FLASH_OB_DATA0_MSK)
#define FLASH_OB_DATA1_MASK             (FLASH_OB_DATA1_MSK)
#define FLASH_OB_DATA0_OFFSET           (REG_BIT12_OFFSET)
#define FLASH_OB_DATA1_OFFSET           (REG_BIT20_OFFSET)

/** Option Bytes MASK **/
#define FLASH_OB_MASK                       ((uint32_t)0xFFFFFFFFU)

/** FLASH Mask **/
#define FLASH_RDPRTL1_MSK                   ((uint32_t)FLASH_OB_RDPRT1)
#define FLASH_RDPRTL2_MSK                   ((uint32_t)FLASH_OB_RDPRT2)

/** SRAM_ECC_ENABLE **/
#define SRAM2_ECC_ENABLE              ((uint8_t)0x01U) /* SRAM2 ECC ENABLE  */
#define SRAM2_ECC_DISABLE             ((uint8_t)0x00U) /* SRAM2 ECC DISABLE */
#define SRAM3_ECC_ENABLE              ((uint8_t)0x01U) /* SRAM3 ECC ENABLE  */
#define SRAM3_ECC_DISABLE             ((uint8_t)0x00U) /* SRAM3 ECC DISABLE */


/* FLASH_WRP */
#define FLASH_WRP_NUM0    ((uint32_t)FLASH_WRP_WRPT_0)  /*  Single Bank: page 0 to 1  , Dual Banke: page 0   to 3   */
#define FLASH_WRP_NUM1    ((uint32_t)FLASH_WRP_WRPT_1)  /*  Single Bank: page 2 to 3  , Dual Banke: page 4   to 7   */
#define FLASH_WRP_NUM2    ((uint32_t)FLASH_WRP_WRPT_2)  /*  Single Bank: page 4 to 5  , Dual Banke: page 8   to 11  */
#define FLASH_WRP_NUM3    ((uint32_t)FLASH_WRP_WRPT_3)  /*  Single Bank: page 6 to 7  , Dual Banke: page 12  to 15  */
#define FLASH_WRP_NUM4    ((uint32_t)FLASH_WRP_WRPT_4)  /*  Single Bank: page 8 to 9  , Dual Banke: page 16  to 19  */
#define FLASH_WRP_NUM5    ((uint32_t)FLASH_WRP_WRPT_5)  /*  Single Bank: page 10 to 11, Dual Banke: page 20  to 23  */
#define FLASH_WRP_NUM6    ((uint32_t)FLASH_WRP_WRPT_6)  /*  Single Bank: page 12 to 13, Dual Banke: page 24  to 27  */
#define FLASH_WRP_NUM7    ((uint32_t)FLASH_WRP_WRPT_7)  /*  Single Bank: page 14 to 15, Dual Banke: page 28  to 31  */
#define FLASH_WRP_NUM8    ((uint32_t)FLASH_WRP_WRPT_8)  /*  Single Bank: page 16 to 17, Dual Banke: page 32  to 35  */
#define FLASH_WRP_NUM9    ((uint32_t)FLASH_WRP_WRPT_9)  /*  Single Bank: page 18 to 19, Dual Banke: page 36  to 39  */
#define FLASH_WRP_NUM10   ((uint32_t)FLASH_WRP_WRPT_10) /*  Single Bank: page 20 to 21, Dual Banke: page 40  to 43  */
#define FLASH_WRP_NUM11   ((uint32_t)FLASH_WRP_WRPT_11) /*  Single Bank: page 22 to 23, Dual Banke: page 44  to 47  */
#define FLASH_WRP_NUM12   ((uint32_t)FLASH_WRP_WRPT_12) /*  Single Bank: page 24 to 25, Dual Banke: page 48  to 51  */
#define FLASH_WRP_NUM13   ((uint32_t)FLASH_WRP_WRPT_13) /*  Single Bank: page 26 to 27, Dual Banke: page 52  to 55  */
#define FLASH_WRP_NUM14   ((uint32_t)FLASH_WRP_WRPT_14) /*  Single Bank: page 28 to 29, Dual Banke: page 56  to 59  */
#define FLASH_WRP_NUM15   ((uint32_t)FLASH_WRP_WRPT_15) /*  Single Bank: page 30 to 31, Dual Banke: page 60  to 63  */
#define FLASH_WRP_NUM16   ((uint32_t)FLASH_WRP_WRPT_16) /*  Single Bank: page 32 to 33, Dual Banke: page 64  to 67  */
#define FLASH_WRP_NUM17   ((uint32_t)FLASH_WRP_WRPT_17) /*  Single Bank: page 34 to 35, Dual Banke: page 68  to 71  */
#define FLASH_WRP_NUM18   ((uint32_t)FLASH_WRP_WRPT_18) /*  Single Bank: page 36 to 37, Dual Banke: page 72  to 75  */
#define FLASH_WRP_NUM19   ((uint32_t)FLASH_WRP_WRPT_19) /*  Single Bank: page 38 to 39, Dual Banke: page 76  to 79  */
#define FLASH_WRP_NUM20   ((uint32_t)FLASH_WRP_WRPT_20) /*  Single Bank: page 40 to 41, Dual Banke: page 80  to 83  */
#define FLASH_WRP_NUM21   ((uint32_t)FLASH_WRP_WRPT_21) /*  Single Bank: page 42 to 43, Dual Banke: page 84  to 87  */
#define FLASH_WRP_NUM22   ((uint32_t)FLASH_WRP_WRPT_22) /*  Single Bank: page 44 to 45, Dual Banke: page 88  to 91  */
#define FLASH_WRP_NUM23   ((uint32_t)FLASH_WRP_WRPT_23) /*  Single Bank: page 46 to 47, Dual Banke: page 92  to 95  */
#define FLASH_WRP_NUM24   ((uint32_t)FLASH_WRP_WRPT_24) /*  Single Bank: page 48 to 49, Dual Banke: page 96  to 99  */
#define FLASH_WRP_NUM25   ((uint32_t)FLASH_WRP_WRPT_25) /*  Single Bank: page 50 to 51, Dual Banke: page 100 to 103 */
#define FLASH_WRP_NUM26   ((uint32_t)FLASH_WRP_WRPT_26) /*  Single Bank: page 52 to 53, Dual Banke: page 104 to 107 */
#define FLASH_WRP_NUM27   ((uint32_t)FLASH_WRP_WRPT_27) /*  Single Bank: page 54 to 55, Dual Banke: page 108 to 111 */
#define FLASH_WRP_NUM28   ((uint32_t)FLASH_WRP_WRPT_28) /*  Single Bank: page 56 to 57, Dual Banke: page 112 to 115 */
#define FLASH_WRP_NUM29   ((uint32_t)FLASH_WRP_WRPT_29) /*  Single Bank: page 58 to 59, Dual Banke: page 116 to 119 */
#define FLASH_WRP_NUM30   ((uint32_t)FLASH_WRP_WRPT_30) /*  Single Bank: page 60 to 61, Dual Banke: page 120 to 123 */
#define FLASH_WRP_NUM31   ((uint32_t)FLASH_WRP_WRPT_31) /*  Single Bank: page 62 to 63, Dual Banke: page 124 to 127 */
#define FLASH_WRP_AllPages      ((uint32_t)FLASH_WRP_WRPT) /* Write protection of all Pages */

#define FLASH_WRP0_MSK           (FLASH_OB_BYTE1)
#define FLASH_WRP1_MSK           (FLASH_OB_BYTE3 >> REG_BIT8_OFFSET)
#define FLASH_WRP2_MSK           (FLASH_OB_BYTE1 << REG_BIT16_OFFSET)
#define FLASH_WRP3_MSK           (FLASH_OB_BYTE3 << REG_BIT8_OFFSET)

/** FLASH_Interrupts **/
#define FLASH_INT_EOP      ((uint32_t)FLASH_CTRL_EOPITE)      /* End of FLASH Operation Interrupt source */
#define FLASH_INT_ERR      ((uint32_t)FLASH_CTRL_ERRITE)      /* PGERR WRPERR ERROR interrupt source */
#define FLASH_INT_FERR     ((uint32_t)FLASH_CTRL_FERRITE)     /* EVERR PVERR ERROR interrupt source */
#define FLASH_INT_ECC1     ((uint32_t)FLASH_CTRL_EC1ERRITE)   /* 1 bit ECC error interrupt source */
#define FLASH_INT_JS       ((uint32_t)FLASH_CTRL_JSERRITE)    /* jtag seal error interrupt source */
#define FLASH_INT_ECC2     ((uint32_t)FLASH_CTRL_EC2ERRITE)   /* 2 bit ECC error interrupt source */
#define FLASH_INT_DECC     ((uint32_t)FLASH_CTRL_DECCERRITE)  /* XSPI/FEMC decryption misconfiguration interrupt source */
#define FLASH_INT_RPADD    ((uint32_t)FLASH_CTRL_RPADDERRITE) /* Row programmer address error interrupt source */
#define FLASH_INT_BANKEX   ((uint32_t)FLASH_CTRL_BANKEXERRITE) /* BANK exchange error interrupt Enable */

/** FLASH_Flags **/
#define FLASH_FLAG_EOP          ((uint32_t)FLASH_STS_EOP)       /* FLASH End of Operation flag */
#define FLASH_FLAG_BUSY         ((uint32_t)FLASH_STS_BUSY)      /* FLASH Busy flag */
#define FLASH_FLAG_PGERR        ((uint32_t)FLASH_STS_PGERR)     /* FLASH Program error flag */
#define FLASH_FLAG_WRPERR       ((uint32_t)FLASH_STS_WRPERR)    /* FLASH Write protected error flag */
#define FLASH_FLAG_PVERR        ((uint32_t)FLASH_STS_PVERR)     /* FLASH Program Verify ERROR flag after program */
#define FLASH_FLAG_EVERR        ((uint32_t)FLASH_STS_EVERR)     /* FLASH Erase Verify ERROR flag after page erase */
#define FLASH_FLAG_ECC1ERR      ((uint32_t)FLASH_STS_ECC1ERR)   /* FLASH 1 bit ECC error flag */
#define FLASH_FLAG_RDKEYERR     ((uint32_t)FLASH_STS_RDKEYERR)  /* read key error flag */
#define FLASH_FLAG_RDXKEYERR    ((uint32_t)FLASH_STS_RDXKEYERR) /* xKEY match error flag */
#define FLASH_FLAG_NRDXKEYEN    ((uint32_t)FLASH_STS_NRDXKEYEN) /* Not allowed to read RTPD_KEY enable flag */
#define FLASH_FLAG_JSERR        ((uint32_t)FLASH_STS_JSERR)     /* JTAG/SRAM access JTAG_SEAL error flag */
#define FLASH_FLAG_RTPKEYERR    ((uint32_t)FLASH_STS_RTPKEYERR) /* read RTPD_KEY error flag */
#define FLASH_FLAG_ECC2ERR      ((uint32_t)FLASH_STS_ECC2ERR)   /* FLASH 2 bit ECC error flag */
#define FLASH_FLAG_DECCRDF      ((uint32_t)FLASH_STS_DECCRDF)   /* XSPI/FEMC Decryption Configuration Completion Flag */
#define FLASH_FLAG_DECCERR      ((uint32_t)FLASH_STS_DECCERR)   /* XSPI/FEMC Decryption Configuration sequences error Flag */
#define FLASH_FLAG_FWORDF       ((uint32_t)FLASH_STS_FWORDF)    /* first word write completion flag */
#define FLASH_FLAG_RPADDERR     ((uint32_t)FLASH_STS_RPADDERR)  /* row programmmer address error */
#define FLASH_FLAG_BANKEXERR    ((uint32_t)FLASH_STS_BANKEXERR) /* BANK exchange error */
#define FLASH_FLAG_BANKMODE     ((uint32_t)FLASH_STS_BANKMODE)  /* BANK mode */
#define FLASH_FLAG_OBERR        ((uint32_t)FLASH_OB_OBERR)      /* FLASH Option Byte error flag */

#define FLASH_STS_CLRFLAG   (FLASH_FLAG_PGERR | FLASH_FLAG_PVERR |\
                             FLASH_FLAG_WRPERR | FLASH_FLAG_EOP |\
                             FLASH_FLAG_EVERR | FLASH_FLAG_RPADDERR)

/** Option_Bytes_RDPx **/
#define FLASH_ROW_MASK                  ((uint32_t)FLASH_ROWP_RPADD_MASK)  /* row programmer address Mask */
#define FLASH_ROW_RPNUM_MASK            ((uint32_t)~FLASH_ROWP_RPNUM_MASK)  /* row programmer number Mask */
#define FLASH_ROW_ENABLE                ((uint32_t)FLASH_ROWP_RPEN)        /* Enable Row programmer */
#define FLASH_ROW_DISABLE               ((uint32_t)(~FLASH_ROWP_RPEN))     /* Disable Row programmer */
#define FLASH_ROW_SYSTEMMEMORY          ((uint32_t)FLASH_ROWP_RPAREA)        /* Row programmer in system memory */
#define FLASH_ROW_MAINFLASH             ((uint32_t)(~FLASH_ROWP_RPAREA))     /* Row programmer in main flash */

/** CCM **/
#define CCM_ERASE_ENABLE                ((uint32_t)CCM_ERASE_EN)
#define CCM_ERASE_STSMSK                ((uint32_t)CCM_ERASE_BUSY)
#define CCM_MODE_ENABLE                 ((uint32_t)CCM_MODE_EN)
#define XSPI_FEMC_DES_ENABLE            ((uint32_t)XSPI_FEMC_DEN_EN)

#define JTAG_SEAL_ENABLE                ((uint8_t)0x5AU) /* Enable JTAG_SEAL */
#define JTAG_SEAL_DISABLE               ((uint8_t)0x00U) /* DISABLE JTAG_SEAL */

/** Partition Jump **/
#define BOOT_PRATITIONJUMP_ENABLE       ((uint32_t)FLASH_PJCTRL_BOOTEN)
#define USER1_PRATITIONJUMP_ENABLE      ((uint32_t)FLASH_PJCTRL_U1EN)
#define USER2_PRATITIONJUMP_ENABLE      ((uint32_t)FLASH_PJCTRL_U2EN)
#define USER3_PRATITIONJUMP_ENABLE      ((uint32_t)FLASH_PJCTRL_U3EN)





/** FLASH_Exported_Functions **/

void FLASH_SetLatency(uint32_t FLASH_Latency);
uint8_t FLASH_GetLatency(void);
void FLASH_PrefetchBufSet(uint32_t FLASH_PrefetchBuf);
void FLASH_iCacheRST(uint32_t Bank);
void FLASH_iCacheCmd(uint32_t Bank, uint32_t FLASH_iCache);
void FLASH_DCacheRST(void);
void FLASH_DCacheCmd(uint32_t FLASH_DCache);
void FLASH_Unlock(void);
void FLASH_Lock(void);
FlagStatus Flash_GetLockStatus(void);
void Option_Bytes_Unlock(void);
void Option_Bytes_Lock(void);
FlagStatus OB_GetLockStatus(void);
FLASH_STS FLASH_EraseOnePage(uint32_t Page_Address);
FLASH_STS FLASH_MassErase(void);
FLASH_STS FLASH_BankErase(uint32_t Bank);
FLASH_STS FLASH_ProgramdoubleWord(uint32_t address, uint32_t data0,uint32_t data1);
void FLASH_RowProgramSet(FunctionalState Cmd);
void FLASH_RowProgramAreaSet(FunctionalState Cmd);
FLASH_STS FLASH_RowProgram(uint32_t address, uint32_t row_num, uint32_t *data);
FLASH_STS FLASH_EraseOB(void);
FLASH_STS FLASH_ProgramOB_RRDC(uint32_t option_byte_rpd1, uint32_t option_byte_rpd2, \
                               uint32_t option_byte_DBANK,uint32_t option_byte_CCMSRAM);
FLASH_STS FLASH_ProgramOB_U1U2(uint32_t option_byte_iwdg, uint32_t option_byte_stop,\
    uint32_t option_byte_stdby, uint32_t option_byte_iwdg_stop, uint32_t option_byte_iwdg_stdby,\
    uint32_t option_byte_iwdg_sleep,uint32_t option_byte2_nBOOT0, uint32_t option_byte2_nBOOT1,\
    uint32_t option_byte2_nSWBOOT0, uint32_t option_byte2_FlashBoot,uint32_t option_byte2_DAC,\
    uint32_t option_byte2_BOR);
FLASH_STS FLASH_EnWriteProtection(uint32_t FLASH_Pages);
FLASH_STS FLASH_ProgramOB_Data(uint32_t option_byte_data0, uint32_t option_byte_data1,\
                               uint32_t option_byte_data2, uint32_t option_byte_data3);
FLASH_STS FLASH_ProgramOB_SRAMECC(uint32_t option_byte_SRAM2,uint32_t option_byte_SRAM3);
FLASH_STS FLASH_ReadOutProtectionL1(FunctionalState Cmd);
FLASH_STS FLASH_ReadOutProtectionL2_ENABLE(void);
uint32_t FLASH_GetUserOB(void);
FlagStatus FLASH_GetUser2(uint32_t option_byte_bit);
uint32_t FLASH_GetOptionBytes_Data0(void);
uint32_t FLASH_GetOptionBytes_Data1(void);
uint32_t FLASH_GetWriteProtectionSTS(void);
FlagStatus FLASH_GetReadOutProtectionSTS(void);
FlagStatus FLASH_GetReadOutProtectionL2STS(void);
FlagStatus FLASH_GetPrefetchBufSTS(void);
void FLASH_INTConfig(uint32_t FLASH_INT, FunctionalState Cmd);
FlagStatus FLASH_GetFlagSTS(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_STS FLASH_GetSTS(void);
FLASH_STS FLASH_WaitForLastOpt(uint32_t Timeout);
void CCM_EnWriteProtection(uint32_t CCM_Pages);
uint32_t CCM_GetWriteProtectionSTS(void);
void CCM_Earse_Unlock(void);
void CCM_EarseEN(void);
FlagStatus CCM_EarseSTS(void);
void CCM_ModeSet(FunctionalState Cmd);
void XSPI_DESRangeSet(uint32_t start_add,uint32_t end_add);
void FEMC_DESRangeSet(uint32_t start_add,uint32_t end_add);
void RTP_DESKeySet(uint32_t* DES_key);
uint32_t GetRTP_DESKeyWnum(void);
void Jtag_SealSet(FunctionalState Cmd);
void XSPI_FEMC_DESSet(FunctionalState Cmd);
uint32_t Get_XFUID(void);
uint32_t Get_CCMUID(void);

#ifdef __cplusplus
}
#endif

#endif /* __N32H49X_FLASH_H__ */

