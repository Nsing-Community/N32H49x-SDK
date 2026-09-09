1、功能说明

    1、XSPI Quad SPI 模式下使用DMA擦除、读、写外部Spi_Flash设备

2、使用环境

    软件开发环境：
        IDE工具：KEIL MDK-ARM 5.34
                 IAR EWARM 8.50.1
    
    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发
        

3、使用说明
    
    1、时钟源：HSI+PLL
    2、系统时钟频率：
        240MHz
    3、打印：PA9 - baud rate 115200
    4、XSPI配置：
          时钟：系统时钟6分频
          引脚：NSS0--PG6(CS)、CLK--PF10(SCLK)、IO0--PF8(SI)、IO1--PF9(SO)、IO2--PF7(WP)、IO3--PF6(HOLD)
          外部Spi_Flash设备：W25Q128或P25Q40


    5、测试步骤与现象
          a.编译后下载程序复位运行；
          b.XSPI和DMA 初始化完成后，先往Spi_Flash设备写256字节，然后读取确认数据是否为写入的内容，有错误则打印报错，
             再全片擦除Spi_Flash设备，然后读取确认数据是否为0xFF，有错误则打印报错。

4、注意事项
    需连接全功能板的跳线帽J47



1. Function description

     1. XSPI Quad SPI Mode Using DMA to Erase, Read, and Write External Spi_Flash Device

2. Use environment

     Software development environment:
         IDE tool: KEIL MDK-ARM 5.34
	           IAR EWARM 8.50.1
    
     Hardware development environment:
        Based on full-function board N32H497ZGL7_EVB V1.0 development

3. Instructions for use
    
    1、clock source: HSI + PLL
    2、System clock frequency:
        240MHz
    3、Printing: PA9 - baud rate 115200
    4、XSPI Configuration:
          Clock: System clock 6 divisions;
          Pin: NSS0--PG6(CS)、CLK--PF10(SCLK)、IO0--PF8(SI)、IO1--PF9(SO)、IO2--PF7(WP)、IO3--PF6(HOLD)
          External Spi_Flash device: W25Q128 or P25Q40


    5、Test steps and phenomena
          a. Compile and download the program to reset and run;
          b. After the initialization of XSPI and DMA is completed, first write 256 bytes to the Spi_Flash device, then read to confirm whether the data is what is written, and if there is an error, print an error report.
             Then erase the Spi_Flash device, and then read to confirm whether the data is 0xFF, and if there is an error, print the error report.

4. Attention
     Jumper caps J47 required to connect full function boards
	 