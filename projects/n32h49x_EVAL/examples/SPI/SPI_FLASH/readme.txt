1、功能说明

    1、SPI 读、写、擦除 W25Q128

2、使用环境

    软件开发环境：
        IDE工具：KEIL MDK-ARM 5.34
	       IAR EWARM 8.50.1
    
    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发

3、使用说明

    1、时钟源：HSI+PLL
    2、系统时钟频率：240MHz
    3、SPI配置：
			SPI3配置：NSS--PA15、SCK--PB3、MISO--PD11、MOSI--PD12
    4、USART配置：
			TX--PA9,115200,8bit data,1bit stop

    5、测试步骤与现象
    1、编译后下载程序复位运行；
    2、通过串口工具查看结果。

4、注意事项
	需要连接跳线帽J20

1. Function description

    1、SPI Read, Write, Erase W25Q128

2. Use environment

    Software development environment:
        IDE tool: KEIL MDK-ARM 5.34
	       IAR EWARM 8.50.1
    
    Hardware development environment:
        Developed based on the evaluation board N32H497ZGL7_EVB V1.0

3. Instructions for use

    1, clock source: HSI + PLL
    2、System clock frequency:240MHz
    3、SPI configuration:
			SPI3 configuration: NSS--PA15、SCK--PB3、MISO--PD11、MOSI--PD12
    4、USART configuration:
			TX--PA9,115200,8bit data,1bit stop

    5, test steps and phenomena
    1, compiled and downloaded the program reset run;
    2, through the serial port tool to view the results.

4. Attention
	Jumpers J20 must be connected.