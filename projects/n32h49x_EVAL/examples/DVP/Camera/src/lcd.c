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
*\*\file lcd.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nsing Technologies Inc. All rights reserved.
**/

#if defined(N32H49X)

#include "lcd.h"
#include "stdio.h"
#include "bsp_dvp.h"

sFONT* LCD_Currentfonts   = &Font8x16;
uint16_t CurrentTextColor = BLACK;
uint16_t CurrentBackColor = WHITE;
uint16_t lcd_width = 0;
uint16_t lcd_height = 0;
uint16_t lcd_x_length = 0;
uint16_t lcd_y_length = 0;
uint16_t lcd_id = 0;
/**
*\*\name    LCD_Configuration.
*\*\fun     Configures the LCD.
*\*\return  none
**/
void LCD_Configuration(void)
{
    LCD_RCC_Configuration();
    LCD_GPIO_Configuration();
    LCD_FEMC_Configuration();
    LCD_Reset();
    printf("\n\r LCD ID : 0x%x\n\r", LCD_Get_ID());
    if((LCD_Get_ID())==0x9341)
    {
        lcd_id = 0x9341;
        lcd_width = 240;
        lcd_height = 320;
        LCD_BL_Control(IO_STATE_LOW);
        ILI9341_REG_Config();    
    }
    else if((LCD_Get_ID())==0x9806)
    {
        lcd_id = 0x9806;
        lcd_width = 480;
        lcd_height = 800;
        LCD_BL_Control(IO_STATE_HIGH);
        ILI9806G_REG_Config();       
    }
    else
    {
    
    }
}


/**
*\*\name    LCD_RCC_Configuration.
*\*\fun     Configures the lcd's clocks.
*\*\return  none
**/
void LCD_RCC_Configuration(void)
{
    /* Enable GPIOx clocks */
    RCC_EnableAHB1PeriphClk(LCD_FEMC_CS_CLK | LCD_FEMC_RS_CLK | LCD_FEMC_WR_CLK |\
                            LCD_FEMC_RD_CLK | LCD_RST_CLK | LCD_BL_CLK |\
                            LCD_FEMC_D0_CLK | LCD_FEMC_D1_CLK | LCD_FEMC_D2_CLK |\
                            LCD_FEMC_D3_CLK | LCD_FEMC_D4_CLK | LCD_FEMC_D5_CLK |\
                            LCD_FEMC_D6_CLK | LCD_FEMC_D7_CLK | LCD_FEMC_D8_CLK |\
                            LCD_FEMC_D9_CLK | LCD_FEMC_D10_CLK | LCD_FEMC_D11_CLK |\
                            LCD_FEMC_D12_CLK | LCD_FEMC_D13_CLK | LCD_FEMC_D14_CLK |\
                            LCD_FEMC_D15_CLK, ENABLE);
    /* Enable FEMC clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPHEN_FEMC,ENABLE);
    /* Enable AFIO clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPHEN_AFIO,ENABLE);
}

/**
*\*\name    LCD_GPIO_Configuration.
*\*\fun     Configures the lcd's GPIO ports.
*\*\return  none
**/
void LCD_GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    
    /* GPIOx config */
    GPIO_InitStruct(&GPIO_InitStructure);

    /* DATA pin */
    GPIO_InitStructure.Pin            = LCD_FEMC_D0_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Current   = GPIO_DC_12mA;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D0_AF;
    GPIO_InitPeripheral(LCD_FEMC_D0_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = LCD_FEMC_D1_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D1_AF;
    GPIO_InitPeripheral(LCD_FEMC_D1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = LCD_FEMC_D2_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D2_AF;
    GPIO_InitPeripheral(LCD_FEMC_D2_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = LCD_FEMC_D3_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D3_AF;
    GPIO_InitPeripheral(LCD_FEMC_D3_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = LCD_FEMC_D4_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D4_AF;
    GPIO_InitPeripheral(LCD_FEMC_D4_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = LCD_FEMC_D5_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D5_AF;
    GPIO_InitPeripheral(LCD_FEMC_D5_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = LCD_FEMC_D6_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D6_AF;
    GPIO_InitPeripheral(LCD_FEMC_D6_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = LCD_FEMC_D7_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D7_AF;
    GPIO_InitPeripheral(LCD_FEMC_D7_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = LCD_FEMC_D8_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D8_AF;
    GPIO_InitPeripheral(LCD_FEMC_D8_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = LCD_FEMC_D9_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D9_AF;
    GPIO_InitPeripheral(LCD_FEMC_D9_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = LCD_FEMC_D10_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D10_AF;
    GPIO_InitPeripheral(LCD_FEMC_D10_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = LCD_FEMC_D11_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D11_AF;
    GPIO_InitPeripheral(LCD_FEMC_D12_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = LCD_FEMC_D12_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D12_AF;
    GPIO_InitPeripheral(LCD_FEMC_D12_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = LCD_FEMC_D13_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D13_AF;
    GPIO_InitPeripheral(LCD_FEMC_D13_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = LCD_FEMC_D14_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D14_AF;
    GPIO_InitPeripheral(LCD_FEMC_D14_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = LCD_FEMC_D15_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_D15_AF;
    GPIO_InitPeripheral(LCD_FEMC_D15_PORT, &GPIO_InitStructure);
    
    /* CS pin */
    GPIO_InitStructure.Pin            = LCD_FEMC_CS_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_CS_AF;
    GPIO_InitPeripheral(LCD_FEMC_CS_PORT, &GPIO_InitStructure);

    /* RS pin */
    GPIO_InitStructure.Pin            = LCD_FEMC_RS_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_RS_AF;
    GPIO_InitPeripheral(LCD_FEMC_RS_PORT, &GPIO_InitStructure);

    /* WR pin */    
    GPIO_InitStructure.Pin            = LCD_FEMC_WR_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_WR_AF;
    GPIO_InitPeripheral(LCD_FEMC_WR_PORT, &GPIO_InitStructure);

    /* RD pin */
    GPIO_InitStructure.Pin            = LCD_FEMC_RD_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_FEMC_RD_AF;
    GPIO_InitPeripheral(LCD_FEMC_RD_PORT, &GPIO_InitStructure);

    /* RST pin */
    GPIO_InitStructure.Pin            = LCD_RST_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.GPIO_Alternate = LCD_RST_AF;
    GPIO_InitPeripheral(LCD_RST_PORT, &GPIO_InitStructure);

    /* BL pin */
    GPIO_InitStructure.Pin            = LCD_BL_PIN;
    GPIO_InitStructure.GPIO_Alternate = LCD_BL_AF;
    GPIO_InitPeripheral(LCD_BL_PORT, &GPIO_InitStructure);
}

/**
*\*\name    LCD_FEMC_Configuration.
*\*\fun     Configures FEMC.
*\*\return  none
**/
void LCD_FEMC_Configuration(void)
{
    FEMC_NorSramInitType FEMC_NorSramInitStructure;
    FEMC_NorSramTimingInitType LCDReadTiming;
    FEMC_NorSramTimingInitType LCDWriteTiming;

    /* FEMC Configuration */
    LCDReadTiming.AddrSetTime      = FEMC_NOR_SRAM_ADDR_SETUP_TIME_7HCLK;
    LCDReadTiming.AddrHoldTime     = FEMC_NOR_SRAM_ADDR_HOLD_TIME_2HCLK;
    LCDReadTiming.DataSetTime      = FEMC_NOR_SRAM_DATA_SETUP_TIME(16);
    LCDReadTiming.BusRecoveryCycle = FEMC_NOR_SRAM_BUSRECOVERY_TIME_1HCLK;
    LCDReadTiming.ClkDiv           = FEMC_NOR_SRAM_CLK_DIV_2;
    LCDReadTiming.DataHoldTime     = FEMC_NOR_SRAM_DATA_HOLD_TIME_2HCLK;
    LCDReadTiming.AccMode          = FEMC_NOR_SRAM_ACC_MODE_A;//FEMC_NOR_SRAM_ACC_MODE_A;//FEMC_NOR_SRAM_ACC_MODE_B;

    /* FEMC Configuration */
    LCDWriteTiming.AddrSetTime      = FEMC_NOR_SRAM_ADDR_SETUP_TIME_7HCLK;
    LCDWriteTiming.AddrHoldTime     = FEMC_NOR_SRAM_ADDR_HOLD_TIME_2HCLK;
    LCDWriteTiming.DataSetTime      = FEMC_NOR_SRAM_DATA_SETUP_TIME(16);
    LCDWriteTiming.BusRecoveryCycle = FEMC_NOR_SRAM_BUSRECOVERY_TIME_1HCLK;
    LCDWriteTiming.ClkDiv           = FEMC_NOR_SRAM_CLK_DIV_2;
    LCDWriteTiming.DataHoldTime     = FEMC_NOR_SRAM_DATA_HOLD_TIME_2HCLK;
    LCDWriteTiming.AccMode          = FEMC_NOR_SRAM_ACC_MODE_A;//FEMC_NOR_SRAM_ACC_MODE_A;//FEMC_NOR_SRAM_ACC_MODE_B;
    
    FEMC_NorSramInitStructure.Block            = FSMC_NORSRAM_BLOCK;
    FEMC_NorSramInitStructure.DataAddrMux      = FEMC_NOR_SRAM_MUX_DISABLE;
    FEMC_NorSramInitStructure.MemType          = FEMC_MEM_TYPE_NOR;
    FEMC_NorSramInitStructure.MemDataWidth     = FEMC_NOR_SRAM_DATA_WIDTH_16B;
    FEMC_NorSramInitStructure.BurstAccMode     = FEMC_NOR_SRAM_BURST_MODE_DISABLE;
    FEMC_NorSramInitStructure.WaitSigPolarity  = FEMC_NOR_SRAM_WAIT_SIGNAL_LOW;
    FEMC_NorSramInitStructure.WrapMode         = FEMC_NOR_SRAM_WRAP_DISABLE;
    FEMC_NorSramInitStructure.WaitSigConfig    = FEMC_NOR_SRAM_NWAIT_BEFORE_STATE;
    FEMC_NorSramInitStructure.WriteEnable      = FEMC_NOR_SRAM_WRITE_ENABLE;
    FEMC_NorSramInitStructure.WaitSigEnable    = FEMC_NOR_SRAM_NWAIT_DISABLE;
    FEMC_NorSramInitStructure.ExtModeEnable    = FEMC_NOR_SRAM_EXTENDED_ENABLE;
    FEMC_NorSramInitStructure.WriteBurstEnable = FEMC_NOR_SRAM_BURST_WRITE_DISABLE;
    FEMC_NorSramInitStructure.AsynchroWait     = FEMC_NOR_SRAM_ASYNC_NWAIT_DISABLE;
    FEMC_NorSramInitStructure.RWTimingStruct   = &LCDReadTiming;
    FEMC_NorSramInitStructure.WTimingStruct    = &LCDWriteTiming;

    FEMC_InitNorSram(&FEMC_NorSramInitStructure);
    
    /* Enable FEMC Bank1_NOR Bank */    
    FEMC_EnableNorSram(FSMC_NORSRAM_BLOCK, ENABLE);
}

/**
*\*\name    LCD_BL_Control.
*\*\fun     Enable or disable the backlight of LCD.
*\*\param   state :
*\*\          - IO_STATE_HIGH
*\*\          - IO_STATE_LOW
*\*\return  none
**/
void LCD_BL_Control(uint16_t state)
{
    if (state != IO_STATE_HIGH)
    {
        /* Enable the backlight */
        GPIO_ResetBits(LCD_BL_PORT,LCD_BL_PIN);
    }
    else
    {
        /* Disable the backlight */
        GPIO_SetBits(LCD_BL_PORT,LCD_BL_PIN);
    }
}

/**
*\*\name    LCD_Reset.
*\*\fun     Reset the LCD.
*\*\return  none
**/
void LCD_Reset(void)
{
    GPIO_ResetBits(LCD_RST_PORT,LCD_RST_PIN);

    LCD_Delay(0xFFFFF);

    GPIO_SetBits(LCD_RST_PORT,LCD_RST_PIN);

    LCD_Delay(0xFFFFF);
}

/**
*\*\name    ILI9806G_REG_Config.
*\*\fun     Config LCD registers.
*\*\return  none
**/
void ILI9806G_REG_Config(void)
{    

    /* Start Initial Sequence */
    LCD_Write_CMD(0xFF); // EXTC Command Set enable register 
    LCD_Write_Data(0xFF); 
    LCD_Write_Data(0x98); 
    LCD_Write_Data(0x06); 

    LCD_Write_CMD(0xBA); // SPI Interface Setting 
    LCD_Write_Data(0x60); 

    LCD_Write_CMD(0xBC); // GIP 1 
    LCD_Write_Data(0x01); 
    LCD_Write_Data(0x0E); 
    LCD_Write_Data(0x61); 
    LCD_Write_Data(0xFB); 
    LCD_Write_Data(0x10); 
    LCD_Write_Data(0x10); 
    LCD_Write_Data(0x0B); 
    LCD_Write_Data(0x0F); 
    LCD_Write_Data(0x2E); 
    LCD_Write_Data(0x73); 
    LCD_Write_Data(0xFF); 
    LCD_Write_Data(0xFF); 
    LCD_Write_Data(0x0E); 
    LCD_Write_Data(0x0E); 
    LCD_Write_Data(0x00); 
    LCD_Write_Data(0x03); 
    LCD_Write_Data(0x66); 
    LCD_Write_Data(0x63); 
    LCD_Write_Data(0x01); 
    LCD_Write_Data(0x00); 
    LCD_Write_Data(0x00); 

    LCD_Write_CMD(0xBD); // GIP 2 
    LCD_Write_Data(0x01); 
    LCD_Write_Data(0x23); 
    LCD_Write_Data(0x45); 
    LCD_Write_Data(0x67); 
    LCD_Write_Data(0x01); 
    LCD_Write_Data(0x23); 
    LCD_Write_Data(0x45); 
    LCD_Write_Data(0x67); 

    LCD_Write_CMD(0xBE); // GIP 3 
    LCD_Write_Data(0x00); 
    LCD_Write_Data(0x21); 
    LCD_Write_Data(0xAB); 
    LCD_Write_Data(0x60); 
    LCD_Write_Data(0x22); 
    LCD_Write_Data(0x22); 
    LCD_Write_Data(0x22); 
    LCD_Write_Data(0x22); 
    LCD_Write_Data(0x22); 

    LCD_Write_CMD(0xC7); // Vcom 
    LCD_Write_Data(0x6F); 

    LCD_Write_CMD(0xED); // EN_volt_reg 
    LCD_Write_Data(0x7F); 
    LCD_Write_Data(0x0F); 
    LCD_Write_Data(0x00); 

    LCD_Write_CMD(0xC0); // Power Control 1
    LCD_Write_Data(0x37); 
    LCD_Write_Data(0x0B); 
    LCD_Write_Data(0x0A); 

    LCD_Write_CMD(0xFC); // LVGL 
    LCD_Write_Data(0x0A); 

    LCD_Write_CMD(0xDF); // Engineering Setting 
    LCD_Write_Data(0x00); 
    LCD_Write_Data(0x00); 
    LCD_Write_Data(0x00); 
    LCD_Write_Data(0x00); 
    LCD_Write_Data(0x00); 
    LCD_Write_Data(0x20); 

    LCD_Write_CMD(0xF3); // DVDD Voltage Setting 
    LCD_Write_Data(0x74); 

    LCD_Write_CMD(0xB4); // Display Inversion Control 
    LCD_Write_Data(0x00); 
    LCD_Write_Data(0x00); 
    LCD_Write_Data(0x00); 

    LCD_Write_CMD(0xF7); // 480x800
    LCD_Write_Data(0x8A); 

    LCD_Write_CMD(0xB1); // Frame Rate 
    LCD_Write_Data(0x00); 
    LCD_Write_Data(0x12); 
    LCD_Write_Data(0x13); 

    LCD_Write_CMD(0xF2); //Panel Timing Control 
    LCD_Write_Data(0x80); 
    LCD_Write_Data(0x5B); 
    LCD_Write_Data(0x40); 
    LCD_Write_Data(0x28); 

    LCD_Write_CMD(0xC1); // Power Control 2 
    LCD_Write_Data(0x17); 
    LCD_Write_Data(0x7D); 
    LCD_Write_Data(0x7A); 
    LCD_Write_Data(0x20); 

    LCD_Write_CMD(0xE0); 
    LCD_Write_Data(0x00); //P1 
    LCD_Write_Data(0x11); //P2 
    LCD_Write_Data(0x1C); //P3 
    LCD_Write_Data(0x0E); //P4 
    LCD_Write_Data(0x0F); //P5 
    LCD_Write_Data(0x0C); //P6 
    LCD_Write_Data(0xC7); //P7 
    LCD_Write_Data(0x06); //P8 
    LCD_Write_Data(0x06); //P9 
    LCD_Write_Data(0x0A); //P10 
    LCD_Write_Data(0x10); //P11 
    LCD_Write_Data(0x12); //P12 
    LCD_Write_Data(0x0A); //P13 
    LCD_Write_Data(0x10); //P14 
    LCD_Write_Data(0x02); //P15 
    LCD_Write_Data(0x00); //P16 

    LCD_Write_CMD(0xE1); 
    LCD_Write_Data(0x00); //P1 
    LCD_Write_Data(0x12); //P2 
    LCD_Write_Data(0x18); //P3 
    LCD_Write_Data(0x0C); //P4 
    LCD_Write_Data(0x0F); //P5 
    LCD_Write_Data(0x0A); //P6 
    LCD_Write_Data(0x77); //P7 
    LCD_Write_Data(0x06); //P8 
    LCD_Write_Data(0x07); //P9 
    LCD_Write_Data(0x0A); //P10 
    LCD_Write_Data(0x0E); //P11 
    LCD_Write_Data(0x0B); //P12 
    LCD_Write_Data(0x10); //P13 
    LCD_Write_Data(0x1D); //P14 
    LCD_Write_Data(0x17); //P15 
    LCD_Write_Data(0x00); //P16 

    LCD_Write_CMD(0x35); //Tearing Effect ON 
    LCD_Write_Data(0x00); 

    LCD_Write_CMD(0x3A);
    LCD_Write_Data(0x55);


    LCD_Write_CMD(0x11); //Exit Sleep 
    DEBUG_DELAY ();
    LCD_Write_CMD(0x29); // Display On 
}


/**
*\*\name    ILI9341_REG_Config.
*\*\fun     Config LCD registers.
*\*\return  none
**/
void ILI9341_REG_Config(void)
{    
    /*  Power control B (CFh)  */
    DEBUG_DELAY();
    LCD_Write_CMD(0xCF);
    LCD_Write_Data(0x00);
    LCD_Write_Data(0x81);
    LCD_Write_Data(0x30);

    /*  Power on sequence control (EDh) */
    DEBUG_DELAY();
    LCD_Write_CMD(0xED);
    LCD_Write_Data(0x64);
    LCD_Write_Data(0x03);
    LCD_Write_Data(0x12);
    LCD_Write_Data(0x81);

    /*  Driver timing control A (E8h) */
    DEBUG_DELAY();
    LCD_Write_CMD(0xE8);
    LCD_Write_Data(0x85);
    LCD_Write_Data(0x10);
    LCD_Write_Data(0x78);

    /*  Power control A (CBh) */
    DEBUG_DELAY();
    LCD_Write_CMD(0xCB);
    LCD_Write_Data(0x39);
    LCD_Write_Data(0x2C);
    LCD_Write_Data(0x00);
    LCD_Write_Data(0x34);
    LCD_Write_Data(0x02);

    /* Pump ratio control (F7h) */
    DEBUG_DELAY();
    LCD_Write_CMD(0xF7);
    LCD_Write_Data(0x20);

    /* Driver timing control B */
    DEBUG_DELAY();
    LCD_Write_CMD(0xEA);
    LCD_Write_Data(0x00);
    LCD_Write_Data(0x00);

    /* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    DEBUG_DELAY();
    LCD_Write_CMD(0xB1);
    LCD_Write_Data(0x00);
    LCD_Write_Data(0x1B);

    /*  Display Function Control (B6h) */
    DEBUG_DELAY();
    LCD_Write_CMD(0xB6);
    LCD_Write_Data(0x0A);
    LCD_Write_Data(0xA2);

    /* Power Control 1 (C0h) */
    DEBUG_DELAY();
    LCD_Write_CMD(0xC0);
    LCD_Write_Data(0x35);

    /* Power Control 2 (C1h) */
    DEBUG_DELAY();
    LCD_Write_CMD(0xC1);
    LCD_Write_Data(0x11);

    /* VCOM Control 1 (C5h) */
    LCD_Write_CMD(0xC5);
    LCD_Write_Data(0x45);
    LCD_Write_Data(0x45);

    /*  VCOM Control 2 (C7h)  */
    LCD_Write_CMD(0xC7);
    LCD_Write_Data(0xA2);

    /* Enable 3G (F2h) */
    LCD_Write_CMD(0xF2);
    LCD_Write_Data(0x00);

    /* Gamma Set (26h) */
    LCD_Write_CMD(0x26);
    LCD_Write_Data(0x01);
    DEBUG_DELAY();

    /* Positive Gamma Correction */
    LCD_Write_CMD(0xE0); // Set Gamma
    LCD_Write_Data(0x0F);
    LCD_Write_Data(0x26);
    LCD_Write_Data(0x24);
    LCD_Write_Data(0x0B);
    LCD_Write_Data(0x0E);
    LCD_Write_Data(0x09);
    LCD_Write_Data(0x54);
    LCD_Write_Data(0xA8);
    LCD_Write_Data(0x46);
    LCD_Write_Data(0x0C);
    LCD_Write_Data(0x17);
    LCD_Write_Data(0x09);
    LCD_Write_Data(0x0F);
    LCD_Write_Data(0x07);
    LCD_Write_Data(0x00);

    /* Negative Gamma Correction (E1h) */
    LCD_Write_CMD(0XE1); // Set Gamma
    LCD_Write_Data(0x00);
    LCD_Write_Data(0x19);
    LCD_Write_Data(0x1B);
    LCD_Write_Data(0x04);
    LCD_Write_Data(0x10);
    LCD_Write_Data(0x07);
    LCD_Write_Data(0x2A);
    LCD_Write_Data(0x47);
    LCD_Write_Data(0x39);
    LCD_Write_Data(0x03);
    LCD_Write_Data(0x06);
    LCD_Write_Data(0x06);
    LCD_Write_Data(0x30);
    LCD_Write_Data(0x38);
    LCD_Write_Data(0x0F);

    /* memory access control set */
    DEBUG_DELAY();
    LCD_Write_CMD(0x36);
    LCD_Write_Data(0xC8);
    DEBUG_DELAY();

    /* column address control set */
    LCD_Write_CMD(CMD_SetCoordinateX);
    LCD_Write_Data(0x00);
    LCD_Write_Data(0x00);
    LCD_Write_Data(0x00);
    LCD_Write_Data(0xEF);

    /* page address control set */
    DEBUG_DELAY();
    LCD_Write_CMD(CMD_SetCoordinateY);
    LCD_Write_Data(0x00);
    LCD_Write_Data(0x00);
    LCD_Write_Data(0x01);
    LCD_Write_Data(0x3F);

    /*  Pixel Format Set (3Ah)  */
    DEBUG_DELAY();
    LCD_Write_CMD(0x3a);
    LCD_Write_Data(0x55);

    /* Sleep Out (11h)  */
    LCD_Write_CMD(0x11);
    // LCD_Delay ( 0xAFFf<<2 );
    DEBUG_DELAY();

    /* Display ON (29h) */
    LCD_Write_CMD(0x29);
}

/**
*\*\name    LCD_Write_CMD.
*\*\fun     Write CMD to LCD.
*\*\return  none
**/
void LCD_Write_CMD(uint16_t cmd)
{
    * ( __IO uint16_t * ) ( FSMC_ADDR_LCD_CMD ) = cmd;
}

/**
*\*\name    LCD_Write_Data.
*\*\fun     Write data to LCD.
*\*\return  none
**/
void LCD_Write_Data(uint16_t data)
{
    * ( __IO uint16_t * ) ( FSMC_ADDR_LCD_DATA ) = data;
}

/**
*\*\name    LCD_Read_Data.
*\*\fun     Read data from LCD.
*\*\return  none
**/
uint16_t LCD_Read_Data(void)
{
    return ( * ( __IO uint16_t * ) ( FSMC_ADDR_LCD_DATA ) );
}

/**
*\*\name    LCD_Get_ID.
*\*\fun     Get the ID of LCD.
*\*\return  none
**/
uint16_t LCD_Get_ID(void)
{
    uint16_t id = 0;
    LCD_Write_CMD(0xD3);
    LCD_Read_Data();
    LCD_Read_Data();
    id |= LCD_Read_Data();
    id <<= 8;
    id |= LCD_Read_Data();
    return id;
}


/**
*\*\name    LCD_Delay.
*\*\fun     LCD Delay.
*\*\return  none
**/
void LCD_Delay (__IO uint32_t nCount)
{
  for ( ;nCount != 0;nCount -- );
}

/**
*\*\name    Config LCD scan mode.
*\*\fun     ucOption specfies the scan mode.
*\*\return  none
**/
void LCD_GramScan(uint8_t ucOption)
{
    if (ucOption > 7)
        return;

    if (ucOption % 2 == 0)
    {
        lcd_x_length = lcd_width;
        lcd_y_length = lcd_height;
    }
    else
    {
        lcd_x_length = lcd_height;
        lcd_y_length = lcd_width;
    }

    LCD_Write_CMD(0x36);
    if(lcd_id==0x9341)
    {
        LCD_Write_Data(0x08 | (ucOption << 5));
    }
    else if(lcd_id==0x9806)
    {
        LCD_Write_Data(0x00 | (ucOption << 5));
    }
    else
    {
    
    }
    LCD_Write_CMD(CMD_SetCoordinateX);
    LCD_Write_Data(0x00);
    LCD_Write_Data(0x00);
    LCD_Write_Data(((lcd_x_length - 1) >> 8) & 0xFF);
    LCD_Write_Data((lcd_x_length - 1) & 0xFF);

    LCD_Write_CMD(CMD_SetCoordinateY);
    LCD_Write_Data(0x00);
    LCD_Write_Data(0x00);
    LCD_Write_Data(((lcd_y_length - 1) >> 8) & 0xFF);
    LCD_Write_Data((lcd_y_length - 1) & 0xFF);

    /* write gram start */
    LCD_Write_CMD(CMD_SetPixel);
}

/**
*\*\name    LCD_OpenWindow.
*\*\fun     Set a window.
*\*\param   usX :
*\*\          - Specfies the start position in x axis
*\*\param   usY :
*\*\          - Specfies the start position in y axis
*\*\param   usWidth :
*\*\          - Specfies the size of window in x axis
*\*\param   usHeight :
*\*\          - Specfies the size of window in y axis
*\*\return  none
**/
void LCD_OpenWindow(uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight)
{
    LCD_Write_CMD(CMD_SetCoordinateX);
    LCD_Write_Data(usX >> 8);
    LCD_Write_Data(usX & 0xff);
    LCD_Write_Data((usX + usWidth - 1) >> 8);
    LCD_Write_Data((usX + usWidth - 1) & 0xff);

    LCD_Write_CMD(CMD_SetCoordinateY);
    LCD_Write_Data(usY >> 8);
    LCD_Write_Data(usY & 0xff);
    LCD_Write_Data((usY + usHeight - 1) >> 8);
    LCD_Write_Data((usY + usHeight - 1) & 0xff);
}

/**
*\*\name    LCD_SetCursor.
*\*\fun     Set the cursor position.
*\*\param   usX :
*\*\          - Specfies the start position in x axis
*\*\param   usY :
*\*\          - Specfies the start position in y axis
*\*\return  none
**/
static void LCD_SetCursor(uint16_t usX, uint16_t usY)
{
    LCD_OpenWindow(usX, usY, 1, 1);
}

/**
*\*\name    LCD_FillColor.
*\*\fun     Fill a area by some color.
*\*\param   ulAmout_Point :
*\*\          - Secfies the total pixels for the area.
*\*\param   usColor :
*\*\          - Specfies the color to be used.
*\*\return  none
**/
static __INLINE void LCD_FillColor(uint32_t ulAmout_Point, uint16_t usColor)
{
    uint32_t i = 0;

    /* memory write */
    LCD_Write_CMD(CMD_SetPixel);

    for (i = 0; i < ulAmout_Point; i++)
        LCD_Write_Data(usColor);
}

/**
*\*\name    LCD_Clear.
*\*\fun     Fill a window by default back color.
*\*\param   usX :
*\*\          - Specfies the start position in x axis
*\*\param   usY :
*\*\          - Specfies the start position in y axis
*\*\param   usWidth :
*\*\          - Specfies the size of window in x axis
*\*\param   usHeight :
*\*\          - Specfies the size of window in y axis
*\*\return  none
**/
void LCD_Clear(uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight)
{
    LCD_OpenWindow(usX, usY, usWidth, usHeight);

    LCD_FillColor(usWidth * usHeight, CurrentBackColor);
}

/**
*\*\name    LCD_SetPointPixel.
*\*\fun     Fill a pixel by default text color.
*\*\param   usX :
*\*\          - Specfies the start position in x axis
*\*\param   usY :
*\*\          - Specfies the start position in y axis
*\*\return  none
**/
void LCD_SetPointPixel(uint16_t usX, uint16_t usY)
{
    if ((usX < lcd_x_length) && (usY < lcd_y_length))
    {
        LCD_SetCursor(usX, usY);

        LCD_FillColor(1, CurrentTextColor);
    }
}

/**
*\*\name    LCD_Read_PixelData.
*\*\fun     Get the color data for current pixel.
*\*\return  Color data in RGB565 format.
**/
static uint16_t LCD_Read_PixelData(void)
{
    uint16_t usR = 0, usG = 0, usB = 0;

    LCD_Write_CMD(0x2E);

    usR = LCD_Read_Data(); /*FIRST READ OUT DUMMY DATA*/

    usR = LCD_Read_Data(); /*READ OUT RED DATA  */
    usB = LCD_Read_Data(); /*READ OUT BLUE DATA*/
    usG = LCD_Read_Data(); /*READ OUT GREEN DATA*/

    return (((usR >> 11) << 11) | ((usG >> 10) << 5) | (usB >> 11));
}

/**
*\*\name    LCD_GetPointPixel.
*\*\fun     Get the color data for a pixel.
*\*\param   usX :
*\*\          - Specfies the start position in x axis
*\*\param   usY :
*\*\          - Specfies the start position in y axis
*\*\return  Color data in RGB565 format.
**/
uint16_t LCD_GetPointPixel(uint16_t usX, uint16_t usY)
{
    uint16_t usPixelData;

    LCD_SetCursor(usX, usY);

    usPixelData = LCD_Read_PixelData();

    return usPixelData;
}

/**
*\*\name    LCD_DrawLine.
*\*\fun     Draw a line between two point, used current text color.
*\*\param   usX1 :
*\*\          - Specfies the position in x axis for first point.
*\*\param   usY1 :
*\*\          - Specfies the position in y axis for first point.
*\*\param   usX2 :
*\*\          - Specfies the position in x axis for second point.
*\*\param   usY2 :
*\*\          - Specfies the position in y axis for second point.
*\*\return  none
**/
void LCD_DrawLine(uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2)
{
    uint16_t us;
    uint16_t usX_Current, usY_Current;

    int32_t lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance;
    int32_t lIncrease_X, lIncrease_Y;

    lDelta_X = usX2 - usX1;
    lDelta_Y = usY2 - usY1;

    usX_Current = usX1;
    usY_Current = usY1;

    if (lDelta_X > 0)
        lIncrease_X = 1;

    else if (lDelta_X == 0)
        lIncrease_X = 0;
    else
    {
        lIncrease_X = -1;
        lDelta_X    = -lDelta_X;
    }

    if (lDelta_Y > 0)
        lIncrease_Y = 1;

    else if (lDelta_Y == 0)
        lIncrease_Y = 0;
    else
    {
        lIncrease_Y = -1;
        lDelta_Y    = -lDelta_Y;
    }

    if (lDelta_X > lDelta_Y)
        lDistance = lDelta_X;
    else
        lDistance = lDelta_Y;

    for (us = 0; us <= lDistance + 1; us++)
    {
        LCD_SetPointPixel(usX_Current, usY_Current);

        lError_X += lDelta_X;
        lError_Y += lDelta_Y;

        if (lError_X > lDistance)
        {
            lError_X -= lDistance;
            usX_Current += lIncrease_X;
        }

        if (lError_Y > lDistance)
        {
            lError_Y -= lDistance;
            usY_Current += lIncrease_Y;
        }
    }
}

/**
*\*\name    LCD_DrawRectangle.
*\*\fun     Draw a rectangle,and fill it with text color optionally.
*\*\param   usX_Start :
*\*\          - Specfies the start position in x axis.
*\*\param   usY_Start :
*\*\          - Specfies the start position in y axis.
*\*\param   usWidth :
*\*\          - Specfies the size in x axis.
*\*\param   usHeight :
*\*\          - Specfies the size in y axis.
*\*\param   ucFilled :
*\*\          - Specifies the fill option.
*\*\return  none
**/
void LCD_DrawRectangle(uint16_t usX_Start,
                           uint16_t usY_Start,
                           uint16_t usWidth,
                           uint16_t usHeight,
                           uint8_t ucFilled)
{
    if (ucFilled)
    {
        LCD_OpenWindow(usX_Start, usY_Start, usWidth, usHeight);
        LCD_FillColor(usWidth * usHeight, CurrentTextColor);
    }
    else
    {
        LCD_DrawLine(usX_Start, usY_Start, usX_Start + usWidth - 1, usY_Start);
        LCD_DrawLine(usX_Start, usY_Start + usHeight - 1, usX_Start + usWidth - 1, usY_Start + usHeight - 1);
        LCD_DrawLine(usX_Start, usY_Start, usX_Start, usY_Start + usHeight - 1);
        LCD_DrawLine(usX_Start + usWidth - 1, usY_Start, usX_Start + usWidth - 1, usY_Start + usHeight - 1);
    }
}

/**
*\*\name    LCD_DrawCircle.
*\*\fun     Draw a circle,and fill it with text color optionally.
*\*\param   usX_Center :
*\*\          - Specfies the center position in x axis.
*\*\param   usY_Center :
*\*\          - Specfies the center position in y axis.
*\*\param   usRadius :
*\*\          - Specfies the radius of circle.
*\*\param   ucFilled :
*\*\          - Specifies the fill option.
*\*\return  none
**/
void LCD_DrawCircle(uint16_t usX_Center, uint16_t usY_Center, uint16_t usRadius, uint8_t ucFilled)
{
    int16_t sCurrentX, sCurrentY;
    int16_t sError;

    sCurrentX = 0;
    sCurrentY = usRadius;

    sError = 3 - (usRadius << 1);

    while (sCurrentX <= sCurrentY)
    {
        int16_t sCountY;

        if (ucFilled)
            for (sCountY = sCurrentX; sCountY <= sCurrentY; sCountY++)
            {
                LCD_SetPointPixel(usX_Center + sCurrentX, usY_Center + sCountY);
                LCD_SetPointPixel(usX_Center - sCurrentX, usY_Center + sCountY);
                LCD_SetPointPixel(usX_Center - sCountY, usY_Center + sCurrentX);
                LCD_SetPointPixel(usX_Center - sCountY, usY_Center - sCurrentX);
                LCD_SetPointPixel(usX_Center - sCurrentX, usY_Center - sCountY);
                LCD_SetPointPixel(usX_Center + sCurrentX, usY_Center - sCountY);
                LCD_SetPointPixel(usX_Center + sCountY, usY_Center - sCurrentX);
                LCD_SetPointPixel(usX_Center + sCountY, usY_Center + sCurrentX);
            }

        else
        {
            LCD_SetPointPixel(usX_Center + sCurrentX, usY_Center + sCurrentY);
            LCD_SetPointPixel(usX_Center - sCurrentX, usY_Center + sCurrentY);
            LCD_SetPointPixel(usX_Center - sCurrentY, usY_Center + sCurrentX);
            LCD_SetPointPixel(usX_Center - sCurrentY, usY_Center - sCurrentX);
            LCD_SetPointPixel(usX_Center - sCurrentX, usY_Center - sCurrentY);
            LCD_SetPointPixel(usX_Center + sCurrentX, usY_Center - sCurrentY);
            LCD_SetPointPixel(usX_Center + sCurrentY, usY_Center - sCurrentX);
            LCD_SetPointPixel(usX_Center + sCurrentY, usY_Center + sCurrentX);
        }

        sCurrentX++;

        if (sError < 0)
            sError += 4 * sCurrentX + 6;

        else
        {
            sError += 10 + 4 * (sCurrentX - sCurrentY);
            sCurrentY--;
        }
    }
}

/**
*\*\name    LCD_DispChar_EN.
*\*\fun     Display a ascii char by current font.
*\*\param   usX :
*\*\          - Specfies the start position in x axis.
*\*\param   usY :
*\*\          - Specfies the start position in y axis.
*\*\param   cChar :
*\*\          - Specfies the char to be display.
*\*\return  none
**/
void LCD_DispChar_EN(uint16_t usX, uint16_t usY, const char cChar)
{
    uint8_t byteCount, bitCount, fontLength;
    uint16_t ucRelativePositon;
    uint8_t* Pfont;

    ucRelativePositon = cChar - ' ';

    fontLength = (LCD_Currentfonts->Width * LCD_Currentfonts->Height) / 8;

    Pfont = (uint8_t*)&LCD_Currentfonts->table[ucRelativePositon * fontLength];

    LCD_OpenWindow(usX, usY, LCD_Currentfonts->Width, LCD_Currentfonts->Height);

    LCD_Write_CMD(CMD_SetPixel);

    for (byteCount = 0; byteCount < fontLength; byteCount++)
    {
        for (bitCount = 0; bitCount < 8; bitCount++)
        {
            if (Pfont[byteCount] & (0x80 >> bitCount))
                LCD_Write_Data(CurrentTextColor);
            else
                LCD_Write_Data(CurrentBackColor);
        }
    }
}

/**
*\*\name    LCD_DispString_EN.
*\*\fun     Display a horizontal ascii string by current font ,start from some positon.
*\*\param   usX :
*\*\          - Specfies the start position in x axis.
*\*\param   usY :
*\*\          - Specfies the start position in y axis.
*\*\param   pStr :
*\*\          - Specfies the string to be display.
*\*\return  none
**/
void LCD_DispString_EN(uint16_t usX, uint16_t usY, char* pStr)
{
    while (*pStr != '\0')
    {
        if ((usX - LCD_DispWindow_X_Star + LCD_Currentfonts->Width) > lcd_x_length)
        {
            usX = LCD_DispWindow_X_Star;
            usY += LCD_Currentfonts->Height;
        }

        if ((usY - LCD_DispWindow_Y_Star + LCD_Currentfonts->Height) > lcd_y_length)
        {
            usX = LCD_DispWindow_X_Star;
            usY = LCD_DispWindow_Y_Star;
        }

        LCD_DispChar_EN(usX, usY, *pStr);

        pStr++;

        usX += LCD_Currentfonts->Width;
    }
}

/**
*\*\name    LCD_DispString_EN_YDir.
*\*\fun     Display a vertical ascii string by current font ,start from some positon.
*\*\param   usX :
*\*\          - Specfies the start position in x axis.
*\*\param   usY :
*\*\          - Specfies the start position in y axis.
*\*\param   pStr :
*\*\          - Specfies the string to be display.
*\*\return  none
**/
void LCD_DispString_EN_YDir(uint16_t usX, uint16_t usY, char* pStr)
{
    while (*pStr != '\0')
    {
        if ((usY - LCD_DispWindow_Y_Star + LCD_Currentfonts->Height) > lcd_y_length)
        {
            usY = LCD_DispWindow_Y_Star;
            usX += LCD_Currentfonts->Width;
        }

        if ((usX - LCD_DispWindow_X_Star + LCD_Currentfonts->Width) > lcd_x_length)
        {
            usX = LCD_DispWindow_X_Star;
            usY = LCD_DispWindow_Y_Star;
        }

        LCD_DispChar_EN(usX, usY, *pStr);

        pStr++;

        usY += LCD_Currentfonts->Height;
    }
}

/**
*\*\name    LCD_SetFont.
*\*\fun     Config the font to be used in Lcd display.
*\*\param   fonts :
*\*\          - Specfies the new font.
*\*\return  none
**/
void LCD_SetFont(sFONT* fonts)
{
    LCD_Currentfonts = fonts;
}

/**
*\*\name    LCD_GetFont.
*\*\fun     Get current font used.
*\*\return  Current font
**/
sFONT* LCD_GetFont(void)
{
    return LCD_Currentfonts;
}

/**
*\*\name    LCD_SetColors.
*\*\fun     Config the colors used for text and background.
*\*\param   TextColor :
*\*\          - Specifies the new text color.
*\*\param   BackColor :
*\*\          - Specifies the new background color.
*\*\return  none
**/
void LCD_SetColors(uint16_t TextColor, uint16_t BackColor)
{
    CurrentTextColor = TextColor;
    CurrentBackColor = BackColor;
}

/**
*\*\name    LCD_GetColors.
*\*\fun     Get current colors used for text and background.
*\*\param   TextColor :
*\*\          - Specifies the new text color.
*\*\param   BackColor :
*\*\          - Specifies the new background color.
*\*\return  none
**/
void LCD_GetColors(uint16_t* TextColor, uint16_t* BackColor)
{
    *TextColor = CurrentTextColor;
    *BackColor = CurrentBackColor;
}

/**
*\*\name    LCD_SetTextColor.
*\*\fun     Config the colors used for text .
*\*\param   Color :
*\*\          - Specifies the new text color.
*\*\return  none
**/
void LCD_SetTextColor(uint16_t Color)
{
    CurrentTextColor = Color;
}

/**
*\*\name    LCD_SetBackColor.
*\*\fun     Config the colors used for background.
*\*\param   Color :
*\*\          - Specifies the new background color.
*\*\return  none
**/
void LCD_SetBackColor(uint16_t Color)
{
    CurrentBackColor = Color;
}

/**
*\*\name    LCD_ClearLine.
*\*\fun     Fill a line by background color.
*\*\param   Line :
*\*\          - Specifies the start posion in y axis.
*\*\return  none
**/
void LCD_ClearLine(uint16_t Line)
{
    LCD_Clear(0, Line, lcd_x_length, ((sFONT*)LCD_GetFont())->Height);
}

/**
*\*\name    lcd_draw_rgb565.
*\*\fun     Show a colorful image on LCD.
*\*\param   image :
*\*\          - Specfies the pointer of image data structure RGB565 format used (16bit/pixel).
*\*\return  none
**/
void lcd_draw_rgb565(const image_t* image)
{
    const color_t* pcolor = (const color_t*)(image->img_data);
    const color_t* pend   = pcolor + image->width * image->height;
    while (pcolor != pend)
    {
        LCD_Write_Data(*pcolor++);
    }
}

/**
*\*\name    lcd_draw_image.
*\*\fun     Show a image on LCD.
*\*\param   x :
*\*\          - Specfies the start position in x axis.
*\*\param   y :
*\*\          - Specfies the start position in y axis.
*\*\param   image :
*\*\          - Specfies the pointer of image data structure.
*\*\return  none
**/
void lcd_draw_image(uint16_t x, uint16_t y, const image_t* image)
{
    LCD_OpenWindow(x, y, image->width, image->height);

    LCD_Write_CMD(CMD_SetPixel);

    lcd_draw_rgb565(image);

}

/**
*\*\name    lcd_ov5640.
*\*\fun     OV5640 output is displayed on the LCD..
*\*\param   x :
*\*\          - Specfies the start position in x axis
*\*\param   y :
*\*\          - Specfies the start position in y axis
*\*\param   width :
*\*\          - Specfies the size of window in x axis
*\*\param   height :
*\*\          - Specfies the size of window in y axis
*\*\return  none
**/
void lcd_ov5640(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    LCD_OpenWindow(x, y, width, height);

    LCD_Write_CMD(CMD_SetPixel);

    color_t* str_color;
    str_color = (color_t*)LCD_IMAGE_ADDRESS;
    color_t* end_color   = str_color + width * height;
    while (str_color != end_color)
    {
        LCD_Write_Data(*str_color++);
    }

}


#endif
