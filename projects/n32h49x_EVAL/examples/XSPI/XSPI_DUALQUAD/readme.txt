1、功能说明
    1、XSPI dual quad 模式擦除、读、写外部Spi_Flash设备

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
          引脚：NSS0--PD3、NSS1--PA4、CLK--PA5、IO0--PA6、IO1--PA7、IO2--PC4、IO3--PC5、IO4--PD4、IO5--PD5、IO6--PD6、IO7--PD7
          外部Spi_Flash设备：P25Q40 * 2


    5、测试步骤与现象
          a.编译后下载程序复位运行；
          b.XSPI 初始化完成后，先通过标准模式分别擦除两个Spi_Flash设备，然后读取确认数据是否为0xFF，有错误则打印报错，
            再将两个Spi_Flash设备视为一片存储区，通过双四线模式往Spi_Flash设备写256字节，然后读取确认数据是否为写入的内容，有错误则打印报错。

4、注意事项
    需连接全功能板的跳线帽J1\J47\J31



1. Function description
     1. XSPI dual quad mode erase, read, write external Spi_Flash device

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
          Pin: NSS0--PD3, NSS1--PA4, CLK--PA5, IO0--PA6, IO1--PA7, IO2--PC4, IO3--PC5, IO4--PD4, IO5--PD5, IO6--PD6, IO7--PD7
          External Spi_Flash device: P25Q40 * 2


    5、Test steps and phenomena
          a. Compile and download the program to reset and run;
          b. After the initialization of XSPI is completed, erase the two Spi_Flash devices respectively through the standard mode, then read and confirm whether the data is 0xFF, 
             if there is any error, print an error report.
             Then treat the two Spi_Flash devices as a memory area, write 256 bytes to the Spi_Flash device through the dual four-wire mode, and then read to confirm whether the data is written or not, 
             and if there is any error, then print an error message.


4. Attention
     Jumper caps J1\J47\J31 required to connect full function boards
	 