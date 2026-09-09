1、功能说明
    1、XSPI dual quad XIP模式读、写外部Spi_Flash设备

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
          时钟：系统时钟6分频；
          引脚：NSS0--PG6(CS)、CLK--PF10(SCLK)、IO0--PF8(SI)、IO1--PF9(SO)、IO2--PF7(WP)、IO3--PF6(HOLD)
          外部Spi_Flash设备：P25Q40


    5、测试步骤与现象
          a.编译后下载程序复位运行；
          b.XSPI 初始化完成后，先通过标准模式分别擦除Spi_Flash设备，然后XIP模式读取确认数据是否为0xFF，有错误则打印报错，
            再将Spi_Flash设备视为一片存储区，通过双四线XIP模式往Spi_Flash设备写256字节，然后XIP模式读取确认数据是否为写入的内容，有错误则打印报错。

4、注意事项
    需连接全功能板的跳线帽J47



1. Function description
     1. XSPI dual quad XIP mode read, write external Spi_Flash device

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
          External Spi_Flash device: P25Q40


    5、Test steps and phenomena
          a. Compile and download the program to reset and run;
          b. After the initialization of XSPI is completed, erase the Spi_Flash devices through the standard mode, then XIP mode read and confirm whether the data is 0xFF, 
             if there is any error, print an error report.
             Then treat the Spi_Flash devices as a memory area, write 256 bytes to the Spi_Flash device through the dual four-wire XIP mode, and then XIP mode read to confirm whether the data is written or not, 
             and if there is any error, then print an error message.


4. Attention
     Jumper caps J47 required to connect full function boards
