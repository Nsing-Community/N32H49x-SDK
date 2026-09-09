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
*\*\file n32h49x_i2c.h
*\*\author Nsing 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/
#ifndef __n32h49x_I2C_H__
#define __n32h49x_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h49x.h"

/**  n32h49x_StdPeriph_Driver **/

/** I2C Init structure definition **/

typedef struct
{
    uint32_t ClkSpeed; /* Specifies the clock frequency.
                                  This parameter must be set to a value lower than 400kHz */

    uint32_t BusMode; /* Specifies the I2C mode.
                            This parameter can be a value of @ref I2C_BusMode */

    uint32_t FmDutyCycle; /* Specifies the I2C fast mode duty cycle.
                                 This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode */

    uint16_t OwnAddr1; /* Specifies the first device own address.
                                   This parameter can be a 7-bit or 10-bit address. */

    uint32_t AckEnable; /* Enables or disables the acknowledgement.
                           This parameter can be a value of @ref I2C_acknowledgement */

    uint16_t AddrMode; /* Specifies if 7-bit or 10-bit address is acknowledged.
                                           This parameter can be a value of @ref I2C_acknowledged_address */
} I2C_InitType;


/** I2C Private Defines **/
#define  I2C_REG_BIT_MASK          ((uint32_t)0x00000000)
#define  I2C_CTRL_BIT_MASK         ((uint32_t)0x00000000)
/** I2C SPE mask **/
#define CTRL1_SPEN_SET   (I2C_CTRL1_EN)
#define CTRL1_SPEN_RESET (~I2C_CTRL1_EN)

/** I2C START mask **/
#define CTRL1_START_SET   (I2C_CTRL1_STARTGEN)
#define CTRL1_START_RESET (~I2C_CTRL1_STARTGEN)

/** I2C STOP mask **/
#define CTRL1_STOP_SET   (I2C_CTRL1_STOPGEN)
#define CTRL1_STOP_RESET (~I2C_CTRL1_STOPGEN)

/** I2C ACK mask **/
#define CTRL1_ACK_SET   (I2C_CTRL1_ACKEN)
#define CTRL1_ACK_RESET (~I2C_CTRL1_ACKEN)

/** I2C ENGC mask **/
#define CTRL1_GCEN_SET   (I2C_CTRL1_GCEN)
#define CTRL1_GCEN_RESET (~I2C_CTRL1_GCEN)

/** I2C SWRST mask **/
#define CTRL1_SWRESET_SET   (I2C_CTRL1_SWRST)
#define CTRL1_SWRESET_RESET (~I2C_CTRL1_SWRST)

/** I2C PEC mask **/
#define CTRL1_PEC_SET   (I2C_CTRL1_PEC)
#define CTRL1_PEC_RESET (~I2C_CTRL1_PEC)

/** I2C ENPEC mask **/
#define CTRL1_PECEN_SET   (I2C_CTRL1_PECEN)
#define CTRL1_PECEN_RESET (~I2C_CTRL1_PECEN)

/** I2C ENARP mask **/
#define CTRL1_ARPEN_SET   (I2C_CTRL1_ARPEN)
#define CTRL1_ARPEN_RESET (~I2C_CTRL1_ARPEN)

/** I2C NOSTRETCH mask **/
#define CTRL1_NOEXTEND_SET   (I2C_CTRL1_NOEXTEND)
#define CTRL1_NOEXTEND_RESET (~I2C_CTRL1_NOEXTEND)

/** I2C FIFOEN mask **/
#define CTRL1_FIFOEN_SET     (I2C_CTRL1_FIFOEN)
#define CTRL1_FIFOEN_RESET   (~I2C_CTRL1_FIFOEN)

/** I2C FIFOCLR mask **/
#define CTRL1_FIFOCLR_SET      (I2C_CTRL1_FIFOCLR)
#define CTRL1_FIFOCLR_RESET    (~I2C_CTRL1_FIFOCLR)

/** I2C registers Masks **/
#define I2C_CTRL1_CLR_MASK     (~(I2C_CTRL1_SMBMODE | I2C_CTRL1_SMBTYPE | I2C_CTRL1_ACKEN))

/* I2C CLR TX FIFO Threshold Mask */
#define CTRL1_TXFT_Mask              (~I2C_CTRL1_THRFIFOHE)
/* I2C CLR RX FIFO Threshold Mask */
#define CTRL1_RXFT_Mask              (~I2C_CTRL1_THRFIFOHF)

/** I2C DMAEN mask **/
#define CTRL2_DMAEN_SET   (I2C_CTRL2_DMAEN)
#define CTRL2_DMAEN_RESET (~I2C_CTRL2_DMAEN)

/** I2C LAST mask **/
#define CTRL2_DMALAST_SET   (I2C_CTRL2_DMALAST)
#define CTRL2_DMALAST_RESET (~I2C_CTRL2_DMALAST)

/** I2C FREQ mask **/
#define CTRL2_CLKFREQ_RESET (~I2C_CTRL2_CLKFREQ)

/** I2C ADD0 mask **/
#define OADDR1_ADDR0_SET   (I2C_OADDR1_ADDR0)
#define OADDR1_ADDR0_RESET (~I2C_OADDR1_ADDR0)

/** I2C ENDUAL mask **/
#define OADDR2_DUALEN_SET   (I2C_OADDR2_DUALEN)
#define OADDR2_DUALEN_RESET (~I2C_OADDR2_DUALEN)

/** I2C ADD2 mask **/
#define OADDR2_ADDR2_SET    (I2C_OADDR2_ADDR2)
#define OADDR2_ADDR2_RESET (~I2C_OADDR2_ADDR2)

/** I2C F/S mask **/
#define CLKCTRL_FSMODE_SET (I2C_CLKCTRL_FSMODE)

/** I2C CHCFG mask **/
#define CLKCTRL_CLKCTRL_SET (I2C_CLKCTRL_CLKCTRL)

/** I2C DMA_FIFO_EN mask **/
#define CTRL2_DMAFIFOEN_SET   (I2C_CTRL2_DMAFIFOEN)
#define CTRL2_DMAFIFOEN_RESET (~I2C_CTRL2_DMAFIFOEN)


/* I2C GFLTRCTRL mask */
#define I2C_SDADFW_MASK  (~I2C_GFLTRCTRL_SDADFW)
#define I2C_SCLDFW_MASK  (~I2C_GFLTRCTRL_SCLDFW)
#define I2C_SDAAFW_MASK  (~I2C_GFLTRCTRL_SDAAFW)
#define I2C_SCLAFW_MASK  (~I2C_GFLTRCTRL_SCLAFW)

/** I2C Analog filter mask **/
#define SCL_AFE_SET     (I2C_GFLTRCTRL_SCLAFENN)
#define SCL_AFE_RESET   (~I2C_GFLTRCTRL_SCLAFENN)

#define SDA_AFE_SET     (I2C_GFLTRCTRL_SDAAFENN)
#define SDA_AFE_RESET   (~I2C_GFLTRCTRL_SDAAFENN)

/** I2C FLAG mask **/
#define FLAG_MASK                   ((uint32_t)0x03FFFFFFU)
#define I2C_FLAG_MASK               ((uint32_t)0x00FFFFFFU)

/* I2C BYTE_NUM_EN mask */
#define I2C_BYTENUMEN_SET        (I2C_BYTENUM_BYTENUMEN)
#define I2C_BYTENUMEN_RESET      (~I2C_BYTENUM_BYTENUMEN)

/* I2C BYTE_NUM byte number mask */
#define I2C_BYTENUM_MASK         (~I2C_BYTENUM_BYTENUM)

/* I2C master sended status after finishing receiving data bytes */
#define I2C_BYTENUM_LAST_STOP    (~I2C_BYTENUM_BYTEFSEL)
#define I2C_BYTENUM_LAST_START   (I2C_BYTENUM_BYTEFSEL)

/** I2C_BusMode **/
#define I2C_BUSMODE_I2C        (I2C_CTRL_BIT_MASK)
#define I2C_BUSMODE_SMBDEVICE  (I2C_CTRL1_SMBMODE)
#define I2C_BUSMODE_SMBHOST    (I2C_CTRL1_SMBMODE | I2C_CTRL1_SMBTYPE)

/** I2C_duty_cycle_in_fast_mode **/
#define I2C_FMDUTYCYCLE_16_9         (I2C_CLKCTRL_DUTY)  /* I2C fast mode Tlow/Thigh = 16/9 */
#define I2C_FMDUTYCYCLE_2            (~I2C_CLKCTRL_DUTY) /* I2C fast mode Tlow/Thigh = 2 */

/** I2C_acknowledgement **/
#define I2C_ACKEN                (I2C_CTRL1_ACKEN)
#define I2C_ACKDIS               (I2C_CTRL_BIT_MASK)

/** I2C_transfer_direction **/
#define I2C_DIRECTION_SEND           ((uint8_t)0x00)
#define I2C_DIRECTION_RECV           ((uint8_t)0x01)

/** I2C_acknowledged_address **/
#define I2C_ADDR_MODE_7BIT         (((uint16_t)0x4000) | I2C_REG_BIT_MASK) 
#define I2C_ADDR_MODE_10BIT        (((uint16_t)0x4000) | I2C_OADDR1_ADDRMODE) 

/** I2C_registers **/
#define I2C_REG_CTRL1                   ((uint8_t)0x00U)
#define I2C_REG_CTRL2                   ((uint8_t)0x04U)
#define I2C_REG_OADDR1                  ((uint8_t)0x08U)
#define I2C_REG_OADDR2                  ((uint8_t)0x0CU)
#define I2C_REG_DAT                     ((uint8_t)0x10U)
#define I2C_REG_STS1                    ((uint8_t)0x14U)
#define I2C_REG_STS2                    ((uint8_t)0x18U)
#define I2C_REG_CLKCTRL                 ((uint8_t)0x1CU)
#define I2C_REG_TMRISE                  ((uint8_t)0x20U)
#define I2C_REG_BYTENUM                 ((uint8_t)0x24U)
#define I2C_REG_GFLTRCTRL               ((uint8_t)0x28U)
#define I2C_REG_FIFODAT                 ((uint8_t)0x2CU)

/** I2C_SMBus_alert_pin_level **/
#define I2C_SMBALERT_LOW        (I2C_CTRL1_ALERT)
#define I2C_SMBALERT_HIGH       (~I2C_CTRL1_ALERT)

/** I2C_PEC_position **/
#define I2C_PEC_POS_NEXT         (I2C_CTRL1_ACKPOS)
#define I2C_PEC_POS_CURRENT      (~I2C_CTRL1_ACKPOS)

/** I2C_NCAK_position **/
#define I2C_NACK_POS_NEXT         (I2C_CTRL1_ACKPOS)
#define I2C_NACK_POS_CURRENT      (~I2C_CTRL1_ACKPOS)

/** I2C Analogue Filter Width **/
#define I2C_ANALOG_FILTER_WIDTH_5NS    (I2C_REG_BIT_MASK)
#define I2C_ANALOG_FILTER_WIDTH_15NS   (I2C_GFLTRCTRL_SDAAFW_0)
#define I2C_ANALOG_FILTER_WIDTH_25NS   (I2C_GFLTRCTRL_SDAAFW_1)
#define I2C_ANALOG_FILTER_WIDTH_35NS   (I2C_GFLTRCTRL_SDAAFW_0|I2C_GFLTRCTRL_SDAAFW_1)

/* I2C timeout detection function enable */
#define I2C_LTOSEL_MASK              (~I2C_CTRL1_LTC)
#define I2C_TIMEOUT_LOWLIMIT_25MS    (I2C_CTRL_BIT_MASK)
#define I2C_TIMEOUT_LOWLIMIT_100MS   (I2C_CTRL1_LTC_0)
#define I2C_TIMEOUT_LOWLIMIT_1S      (I2C_CTRL1_LTC_1)
#define I2C_TIMEOUT_LOWLIMIT_4S      (I2C_CTRL1_LTC_0|I2C_CTRL1_LTC_1)

#define I2C_HTOSEL_MASK               (~I2C_CTRL1_HTC)
#define I2C_TIMEOUT_HIGHLIMIT_256US   (I2C_CTRL_BIT_MASK)
#define I2C_TIMEOUT_HIGHLIMIT_512US   (I2C_CTRL1_HTC_0)
#define I2C_TIMEOUT_HIGHLIMIT_1MS     (I2C_CTRL1_HTC_1)
#define I2C_TIMEOUT_HIGHLIMIT_128US   (I2C_CTRL1_HTC_0|I2C_CTRL1_HTC_1)

#define I2C_TIMEOUT_LOW           (I2C_CTRL2_TOLEN)
#define I2C_TIMEOUT_HIGH          (I2C_CTRL2_TOHEN)

#define I2C_TIMEOUT_FLAG_SCLLOW    (I2C_STS1_SCLLTO)
#define I2C_TIMEOUT_FLAG_SCLHIGH   (I2C_STS1_SCLHTO)
#define I2C_TIMEOUT_FLAG_SDALOW    (I2C_STS1_SDALTO)

/** I2C_interrupts_definition **/
#define I2C_INT_BUF               (I2C_CTRL2_BUFINTEN) /* buffer interrupt enable */
#define I2C_INT_EVENT             (I2C_CTRL2_EVTINTEN) /* event interrupt enable */
#define I2C_INT_ERR               (I2C_CTRL2_ERRINTEN) /* error full interrupt enable */
#define I2C_INT_FIFOFEN          (I2C_CTRL2_FIFOFINTEN ) /* FIFO full interrupt enable */
#define I2C_INT_FIFOEEN          (I2C_CTRL2_FIFOEINTEN ) /* FIFO empty interrupt enable */
#define I2C_INT_FIFOHFEN         (I2C_CTRL2_FIFOHFINTEN) /* FIFO half full interrupt enable */
#define I2C_INT_FIFOHEEN         (I2C_CTRL2_FIFOHEINTEN) /* FIFOHE half empty interrupt enable */
#define I2C_INT_FIFOUREN         (I2C_CTRL2_FIFOURINTEN) /* FIFO under-run interrupt enable */
#define I2C_INT_FIFOOREN         (I2C_CTRL2_FIFOORINTEN) /* FIFO over-run interrupt enable */
#define I2C_INT_DMAETOERREN      (I2C_CTRL2_DMAETOEIEN ) /* DMA ETO error interrupt enable */
#define I2C_INT_SDALTOEN         (I2C_CTRL2_SDATOLIEN) /* SDA low timeout interrupt enable */
#define I2C_INT_SCLHTOEN         (I2C_CTRL2_SCLTOHIEN) /* SCL high timeout interrupt enable */
#define I2C_INT_SCLLTOEN         (I2C_CTRL2_SCLTOLIEN) /* SCL low timeout interrupt enable */

/** I2C_interrupts_flag_definition **/
#define I2C_INT_STARTBF                  (I2C_STS1_STARTBF) /* Start Bit (Master mode) */
#define I2C_INT_ADDRF                    (I2C_STS1_ADDRF) /* Address sent (master mode)/matched (slave mode) */
#define I2C_INT_BSF                      (I2C_STS1_BSF) /* Byte Transfer Finished */
#define I2C_INT_STOPF                    (I2C_STS1_STOPF) /* Stop detection (Slave mode) */
#define I2C_INT_RXDATNE                  (I2C_STS1_RXDATNE) /* Data Register not Empty (receivers) */
#define I2C_INT_TXDATE                   (I2C_STS1_TXDATE) /* Data Register Empty (transmitters) */
#define I2C_INT_ADDR10F                  (I2C_STS1_ADDR10F) /* 10-bit header sent (Master mode) */
#define I2C_INT_ACKFAIL                  (I2C_STS1_ACKFAIL) /* Acknowledge Failure */
#define I2C_INT_ARLOST                   (I2C_STS1_ARLOST) /* Arbitration Lost (master mode) */
#define I2C_INT_BUSERR                   (I2C_STS1_BUSERR) /* Bus Error */
#define I2C_INT_OVERRUN                  (I2C_STS1_OVERRUN) /* Overrun/Underrun */
#define I2C_INT_PECERR                   (I2C_STS1_PECERR) /* PEC Error in reception */
#define I2C_INT_SMBALERT                 (I2C_STS1_SMBALERT) /* SMBus Alert */
#define I2C_INT_FIFOF                     (I2C_STS1_FIFOF) /* FIFO full */
#define I2C_INT_FIFOE                     (I2C_STS1_FIFOE) /* FIFO empty */
#define I2C_INT_FIFOHF                    (I2C_STS1_FIFOHF) /* FIFO half full */
#define I2C_INT_FIFOHE                    (I2C_STS1_FIFOHE) /* FIFO half empty */
#define I2C_INT_FIFOUR                    (I2C_STS1_FIFOUR) /* Read data when FIFO is empty,FIFO under-run */
#define I2C_INT_FIFOOR                    (I2C_STS1_FIFOOR) /* Write data when FIFO is full,FIFO over-run */
#define I2C_INT_DMAETOERR                 (I2C_STS1_DMAETOERR) /* Prove that the DMA transmission is complete but no ETO signal is given */
#define I2C_INT_SDALTO                    (I2C_STS1_SDALTO) /* SDA timeout low error */
#define I2C_INT_SCLHTO                    (I2C_STS1_SCLHTO) /* SCL timeout high error */
#define I2C_INT_SCLLTO                    (I2C_STS1_SCLLTO) /* SCL timeout low error */

/** I2C_flags_definition **/

/** STS2 register flags **/
#define I2C_FLAG_DUALFLAG  (((uint32_t)I2C_STS2_DUALFLAG)<<REG_BIT16_OFFSET)
#define I2C_FLAG_SMBHADDR  (((uint32_t)I2C_STS2_SMBHADDR)<<REG_BIT16_OFFSET)
#define I2C_FLAG_SMBDADDR  (((uint32_t)I2C_STS2_SMBDADDR)<<REG_BIT16_OFFSET)
#define I2C_FLAG_GCALLADDR (((uint32_t)I2C_STS2_GCALLADDR)<<REG_BIT16_OFFSET)
#define I2C_FLAG_TRF       (((uint32_t)I2C_STS2_TRF)<<REG_BIT16_OFFSET)
#define I2C_FLAG_BUSY      (((uint32_t)I2C_STS2_BUSY)<<REG_BIT16_OFFSET)
#define I2C_FLAG_MSMODE    (((uint32_t)I2C_STS2_MSMODE)<<REG_BIT16_OFFSET)

/** STS1 register flags **/
#define I2C_FLAG_SCLLTO        (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_SCLLTO))
#define I2C_FLAG_SCLHTO        (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_SCLHTO))
#define I2C_FLAG_SDALTO       (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_SDALTO))
#define I2C_FLAG_DMAETOERR    (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_DMAETOERR))
#define I2C_FLAG_FIFOOR        (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_FIFOOR))
#define I2C_FLAG_FIFOUR        (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_FIFOUR))
#define I2C_FLAG_FIFOHE        (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_FIFOHE))
#define I2C_FLAG_FIFOHF        (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_FIFOHF))
#define I2C_FLAG_FIFOE        (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_FIFOE))
#define I2C_FLAG_FIFOF        (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_FIFOF))
#define I2C_FLAG_SMBALERT     (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_SMBALERT))
#define I2C_FLAG_PECERR       (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_PECERR))
#define I2C_FLAG_OVERRUN      (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_OVERRUN))
#define I2C_FLAG_ACKFAIL      (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_ACKFAIL))
#define I2C_FLAG_ARLOST       (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_ARLOST))
#define I2C_FLAG_BUSERR       (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_BUSERR))
#define I2C_FLAG_TXDATE       (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_TXDATE))
#define I2C_FLAG_RXDATNE      (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_RXDATNE))
#define I2C_FLAG_STOPF        (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_STOPF))
#define I2C_FLAG_ADDR10F      (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_ADDR10F))
#define I2C_FLAG_BSF          (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_BSF))
#define I2C_FLAG_ADDRF        (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_ADDRF))
#define I2C_FLAG_STARTBF      (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_STARTBF))

/***  I2C_Events ***/

/** I2C Master Events (Events grouped in order of communication) **/
/**
*\*\brief  Communication start
*\*\       After sending the START condition (I2C_GenerateStart() function) the master
*\*\       has to wait for this event. It means that the Start condition has been correctly
*\*\       released on the I2C bus (the bus is free, no other devices is communicating).
**/

/* Master mode */
#define I2C_ROLE_MASTER ((uint32_t)0x00020000U) /* MSMODE */
/* --EV5 */
#define I2C_EVT_MASTER_MODE_FLAG ((uint32_t)0x00030001U) /* BUSY, MSMODE and STARTBF flag */
/* --EV5_FIFO */
#define  I2C_EVENT_MASTER_FIFO_MODE_SELECT                 ((uint32_t)0x03000001)  /* BUSY, MSL and SB flag */
/**
*\*\brief  Address Acknowledge
*\*\       After checking on EV5 (start condition correctly released on the bus), the
*\*\       master sends the address of the slave(s) with which it will communicate
*\*\       (I2C_SendAddr7bit() function, it also determines the direction of the communication:
*\*\       Master transmitter or Receiver). Then the master has to wait that a slave acknowledges
*\*\       his address. If an acknowledge is sent on the bus, one of the following events will
*\*\       be set:
*\*\       1) In case of Master Receiver (7-bit addressing): the I2C_EVT_MASTER_RXMODE_FLAG
*\*\       event is set.
*\*\       2) In case of Master Transmitter (7-bit addressing): the I2C_EVT_MASTER_TXMODE_FLAG
*\*\       is set
*\*\       3) In case of 10-Bit addressing mode, the master (just after generating the START
*\*\       and checking on EV5) has to send the header of 10-bit addressing mode (I2C_SendData()
*\*\       function). Then master should wait on EV9. It means that the 10-bit addressing
*\*\       header has been correctly sent on the bus. Then master should send the second part of
*\*\       the 10-bit address (LSB) using the function I2C_SendAddr7bit(). Then master
*\*\       should wait for event EV6.
**/

/* --EV6 */
#define I2C_EVT_MASTER_TXMODE_FLAG ((uint32_t)0x00070022U) /* BUSY, MSMODE, ADDRF, TXDATE and TRF flags */
#define I2C_EVT_MASTER_RXMODE_FLAG ((uint32_t)0x00030002U) /* BUSY, MSMODE and ADDRF flags */
/* --EV9 */
#define I2C_EVT_MASTER_MODE_ADDRESS10_FLAG ((uint32_t)0x00030040U) /* BUSY, MSMODE and ADD10RF flags */

/* --EV6_FIFO */
#define  I2C_EVENT_MASTER_FIFO_TRANSMITTER_MODE_SELECTED   ((uint32_t)0x07000002U)  /* BUSY, MSL, ADDR, and TRA flags */
#define  I2C_EVENT_MASTER_FIFO_RECEIVER_MODE_SELECTED      ((uint32_t)0x03000002U)  /* BUSY, MSL and ADDR flags */
/* --EV9_FIFO */
#define  I2C_EVENT_MASTER_FIFO_MODE_ADDRESS10              ((uint32_t)0x03000040U)  /* BUSY, MSL and ADD10 flags */


/**
*\*\brief Communication events
*\*\      If a communication is established (START condition generated and slave address
*\*\      acknowledged) then the master has to check on one of the following events for
*\*\      communication procedures:
*\*\      1) Master Receiver mode: The master has to wait on the event EV7 then to read
*\*\      the data received from the slave (I2C_RecvData() function).
*\*\      2) Master Transmitter mode: The master has to send data (I2C_SendData()
*\*\      function) then to wait on event EV8 or EV8_2.
*\*\      These two events are similar:
*\*\      - EV8 means that the data has been written in the data register and is
*\*\      being shifted out.
*\*\      - EV8_2 means that the data has been physically shifted out and output
*\*\      on the bus.
*\*\      In most cases, using EV8 is sufficient for the application.
*\*\      Using EV8_2 leads to a slower communication but ensure more reliable test.
*\*\      EV8_2 is also more suitable than EV8 for testing on the last data transmission
*\*\      (before Stop condition generation).
*\*\note  In case the  user software does not guarantee that this event EV7 is
*\*\      managed before the current byte end of transfer, then user may check on EV7
*\*\      and BSF flag at the same time (ie. (I2C_EVT_MASTER_DATA_RECVD_FLAG | I2C_FLAG_BSF)).
*\*\      In this case the communication may be slower.
**/

/* Master RECEIVER mode -----------------------------*/
/* --EV7 */
#define I2C_EVT_MASTER_DATA_RECVD_FLAG ((uint32_t)0x00030010U) /* BUSY, MSMODE and RXDATNE flags */
/* EV7x shifter register full */
#define I2C_EVT_MASTER_SFT_DATA_RECVD_FLAG ((uint32_t)0x00030014U) /* BUSY, MSMODE, BSF and RXDATNE flags */
/* Master TRANSMITTER mode --------------------------*/
/* --EV8 */
#define I2C_EVT_MASTER_DATA_SENDING ((uint32_t)0x00070020U) /* TRF, BUSY, MSMODE, TXDATE flags */
/* --EV8_2 */
#define I2C_EVT_MASTER_DATA_SENDED ((uint32_t)0x00070024U) /* TRF, BUSY, MSMODE, TXDATE and BSF flags */


/* Master FIFO TRANSMITTER mode --------------------------*/
/* --EV10_FIFO */
#define  I2C_EVENT_MASTER_FIFO_TRANSMITTING                  ((uint32_t)0x07080000U)  /* TRA, BUSY, MSL, FIFOHE flags */
/* --EV10_FIFO_1 */
#define  I2C_EVENT_MASTER_FIFO_TRANSMITTED                 ((uint32_t)0x000A0004U)  /* FIFOHE, FIFOE, BSF flags */

/* Master FIFO RECEIVER mode -----------------------------*/
/* --EV4_FIFO  */
#define  I2C_EVENT_MASTER_FIFO_STOP_DETECTED                ((uint32_t)0x00000008U)  /* STOPF flag */
/* --EV11_FIFO */
#define  I2C_EVENT_MASTER_FIFO_RECEIVING                    ((uint32_t)0x03040000U)  /* BUSY, MSL and FIFOHF flags */
/* --EV12_FIFO */
#define  I2C_EVENT_MASTER_FIFO_RECEIVED                     ((uint32_t)0x00020000U)  /* FIFOE flags */


/** I2C Slave Events (Events grouped in order of communication)***/

/**
*\*\brief  Communication start events
*\*\       Wait on one of these events at the start of the communication. It means that
*\*\       the I2C peripheral detected a Start condition on the bus (generated by master
*\*\       device) followed by the peripheral address. The peripheral generates an ACK
*\*\       condition on the bus (if the acknowledge feature is enabled through function
*\*\       I2C_ConfigAck()) and the events listed above are set :
*\*\       1) In normal case (only one address managed by the slave), when the address
*\*\       sent by the master matches the own address of the peripheral (configured by
*\*\       OwnAddr1 field) the I2C_EVENT_SLAVE_XXX_ADDRESS_MATCHED event is set
*\*\       (where XXX could be TRANSMITTER or RECEIVER).
*\*\       2) In case the address sent by the master matches the second address of the
*\*\       peripheral (configured by the function I2C_ConfigOwnAddr2() and enabled
*\*\       by the function I2C_EnableDualAddr()) the events I2C_EVENT_SLAVE_XXX_SECONDADDRESS_MATCHED
*\*\       (where XXX could be TRANSMITTER or RECEIVER) are set.
*\*\       3) In case the address sent by the master is General Call (address 0x00) and
*\*\       if the General Call is enabled for the peripheral (using function I2C_EnableGeneralCall())
*\*\       the following event is set I2C_EVT_SLAVE_GCALLADDR_MATCHED.
**/

/* --EV1  (all the events below are variants of EV1) */
/* 1) Case of One Single Address managed by the slave */
#define I2C_EVT_SLAVE_RECV_ADDR_MATCHED                     ((uint32_t)0x00010002U) /* BUSY and ADDRF flags */
#define I2C_EVT_SLAVE_FIFO_RECV_ADDR_MATCHED       ((uint32_t)0x00010002U) /* BUSY and ADDR flags */
#define I2C_EVT_SLAVE_SEND_ADDR_MATCHED                  ((uint32_t)0x00050022U) /* TRF, BUSY, TXDATE and ADDRF flags */

/* 2) Case of Dual address managed by the slave */
#define I2C_EVT_SLAVE_RECV_ADDR2_MATCHED                     ((uint32_t)0x00210000U) /* DUALF and BUSY flags */
#define I2C_EVT_SLAVE_SEND_ADDR2_MATCHED                     ((uint32_t)0x00250020U) /* DUALF, TRF, BUSY and TXDATE flags */

/* 3) Case of General Call enabled for the slave */
#define I2C_EVT_SLAVE_GCALLADDR_MATCHED                        ((uint32_t)0x00110000U) /* GENCALL and BUSY flags */

/* --EV1_FIFO*/
/* 1) Case of One Single Address managed by the slave fifo mode */
#define  I2C_EVENT_SLAVE_FIFO_RECEIVER_ADDRESS_MATCHED                     ((uint32_t)0x01000002U) /* BUSY and ADDR flags */
#define  I2C_EVENT_SLAVE_FIFO_TRANSMITTER_ADDRESS_MATCHED               ((uint32_t)0x05000002U) /* TRA, BUSY, and ADDR flags */


/* 2) Case of Dual address managed by the slave fifo mode*/
#define  I2C_EVENT_SLAVE_FIFO_RECEIVER_SECONDADDRESS_MATCHED            ((uint32_t)0x21000000U)  /* DUALF and BUSY flags */
#define  I2C_EVENT_SLAVE_FIFO_TRANSMITTER_SECONDADDRESS_MATCHED         ((uint32_t)0x25000000U)  /* DUALF, TRA, BUSY and flags */

/* 3) Case of General Call enabled for the slave fifo mode*/
#define  I2C_EVENT_SLAVE_FIFO_GENERALCALLADDRESS_MATCHED                ((uint32_t)0x11000000U)  /* GENCALL and BUSY flags */

/**
*\*\brief  Communication events
*\*\       Wait on one of these events when EV1 has already been checked and:
*\*\       - Slave RECEIVER mode:
*\*\       - EV2: When the application is expecting a data byte to be received.
*\*\       - EV4: When the application is expecting the end of the communication: master
*\*\       sends a stop condition and data transmission is stopped.
*\*\       - Slave Transmitter mode:
*\*\       - EV3: When a byte has been transmitted by the slave and the application is expecting
*\*\       the end of the byte transmission. The two events I2C_EVT_SLAVE_DATA_SENDED and
*\*\       I2C_EVT_SLAVE_DATA_SENDING are similar. The second one can optionally be
*\*\       used when the user software doesn't guarantee the EV3 is managed before the
*\*\       current byte end of transfer.
*\*\       - EV3_2: When the master sends a NACK in order to tell slave that data transmission
*\*\       shall end (before sending the STOP condition). In this case slave has to stop sending
*\*\       data bytes and expect a Stop condition on the bus.
*\*\note   In case the  user software does not guarantee that the event EV2 is
*\*\       managed before the current byte end of transfer, then user may check on EV2
*\*\       and BSF flag at the same time (ie. (I2C_EVT_SLAVE_DATA_RECVD | I2C_FLAG_BSF)).
*\*\       In this case the communication may be slower.
**/

/* Slave RECEIVER mode --------------------------*/
/* --EV2 */
#define I2C_EVT_SLAVE_DATA_RECVD ((uint32_t)0x00010010U) /* BUSY and RXDATNE flags */
/* --EV2x */
#define I2C_EVT_SLAVE_DATA_RECVD_NOBUSY ((uint32_t)0x00000010U) /* no BUSY and RXDATNE flags */
/* --EV4  */
#define I2C_EVT_SLAVE_STOP_RECVD ((uint32_t)0x00000008U) /* STOPF flag */

/* Slave TRANSMITTER mode -----------------------*/
/* --EV3 */
#define I2C_EVT_SLAVE_DATA_SENDED  ((uint32_t)0x00050024U) /* TRF, BUSY, TXDATE and BSF flags */
#define I2C_EVT_SLAVE_DATA_SENDING ((uint32_t)0x00050020U) /* TRF, BUSY and TXDATE flags */
/* --EV3_2 */
#define I2C_EVT_SLAVE_ACK_MISS ((uint32_t)0x00000100U) /* AF flag */

/* Slave FIFO RECEIVER mode --------------------------*/
/* --EV4_FIFO  */
#define  I2C_EVENT_SLAVE_FIFO_STOP_DETECTED                ((uint32_t)0x00000008U)  /* STOPF flag */
/* --EV11_FIFO */
#define  I2C_EVENT_SLAVE_FIFO_RECEIVING                    ((uint32_t)0x01040000U)  /* BUSY and FIFOHF flags */
/* --EV12_FIFO */
#define  I2C_EVENT_SLAVE_FIFO_RECEIVED                     ((uint32_t)0x00020000U)  /* FIFOE flags */

/* Slave FIFO TRANSMITTER mode --------------------------*/
/* --EV10_FIFO */
#define  I2C_EVENT_SLAVE_FIFO_TRANSMITTING                  ((uint32_t)0x05080000U)  /* TRA, BUSY and FIFOHE flags */
/* --EV3_2_FIFO */
#define  I2C_EVENT_SLAVE_FIFO_ACK_FAILURE                  ((uint32_t)0x000A0100U)  /* FIFOHE, FIFOE and AF flag */


/** I2C_Exported_Macros **/

/** I2C_Exported_Functions **/

void I2C_DeInit(I2C_Module* I2Cx);
void I2C_Init(I2C_Module* I2Cx,I2C_InitType* I2C_InitStruct);
void I2C_InitStruct(I2C_InitType* I2C_InitStruct);
void I2C_Enable(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_GenerateStart(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_GenerateStop(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ConfigAck(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_SendAddr7bit(I2C_Module* I2Cx, uint8_t Address, uint8_t I2C_Direction);
void I2C_ConfigOwnAddr2(I2C_Module* I2Cx, uint8_t Address);
void I2C_EnableDualAddr(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableGeneralCall(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ConfigInt(I2C_Module* I2Cx, uint32_t I2C_IT, FunctionalState Cmd);
void I2C_SendData(I2C_Module* I2Cx, uint8_t Data);
uint8_t I2C_RecvData(I2C_Module* I2Cx);
void I2C_EnableDMA(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableDmaLastSend(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableSoftwareReset(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ConfigNackLocation(I2C_Module* I2Cx, uint32_t I2C_NACKPosition);
void I2C_ConfigPecLocation(I2C_Module* I2Cx, uint32_t I2C_PECPosition);
void I2C_ConfigSmbusAlert(I2C_Module* I2Cx, uint32_t I2C_SMBusAlert);
void I2C_SendPEC(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ComputePec(I2C_Module* I2Cx, FunctionalState Cmd);
uint8_t I2C_GetPec(I2C_Module* I2Cx);
void I2C_EnableArp(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableExtendClk(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ConfigFastModeDutyCycle(I2C_Module* I2Cx, uint32_t DutyCycle);
void I2C_SetSDADigitalFilterWidth(I2C_Module* I2Cx, uint32_t width);
void I2C_SetSCLDigitalFilterWidth(I2C_Module* I2Cx, uint32_t width);
void I2C_SetSDAAnalogFilterWidth(I2C_Module* I2Cx, uint32_t width);
void I2C_EnableSDAAnalogFilter(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_SetSCLAnalogFilterWidth(I2C_Module* I2Cx, uint32_t width);
void I2C_EnableSCLAnalogFilter(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ClrFlag(I2C_Module* I2Cx, uint32_t I2C_FLAG);
void I2C_ClrIntPendingBit(I2C_Module* I2Cx, uint32_t I2C_IT);
void I2C_ClrFIFO(I2C_Module* I2Cx);
void I2C_EnableFIFO(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableDMAFIFO(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_SetTxFifoThreshold( I2C_Module* I2Cx, uint8_t TxFifoThreshold);
void I2C_SetRxFifoThreshold( I2C_Module* I2Cx, uint8_t RxFifoThreshold);
void I2C_EnableByteNum(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_SetMasterReceivedDataBytesNum(I2C_Module* I2Cx, uint16_t Number_Of_bytes);
void I2C_SetByteNumLastStartStop(I2C_Module* I2Cx, uint32_t LastStatus);
void I2C_SendFIFOData(I2C_Module* I2Cx, uint8_t Data);
uint8_t I2C_RecvFIFOData(I2C_Module* I2Cx);
void I2C_SetTimeoutLowLimit(I2C_Module* I2Cx, uint32_t limit);
void I2C_SetTimeoutHighLimit(I2C_Module* I2Cx, uint32_t limit);
void I2C_EnableTimeoutDetect(I2C_Module* I2Cx, uint32_t timeout_type, FunctionalState Cmd);
uint32_t I2C_GetRegister(I2C_Module* I2Cx, uint8_t I2C_Register);
INTStatus I2C_GetIntStatus(I2C_Module* I2Cx, uint32_t I2C_IT);
ErrorStatus I2C_CheckFifoEvent(I2C_Module* I2Cx, uint32_t I2C_FIFO_EVENT);

/** 1) Basic state monitoring **/
ErrorStatus I2C_CheckEvent(I2C_Module* I2Cx, uint32_t I2C_EVENT);
/** 2) Advanced state monitoring **/
uint32_t I2C_GetLastEvent(I2C_Module* I2Cx);
/** 3) Flag-based state monitoring **/
FlagStatus I2C_GetFlag(I2C_Module* I2Cx, uint32_t I2C_FLAG);

#ifdef __cplusplus
}
#endif

#endif /*__n32h49x_I2C_H */

