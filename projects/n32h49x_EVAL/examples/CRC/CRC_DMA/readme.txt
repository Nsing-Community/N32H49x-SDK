1、功能说明
    此例程展示了通过DMA传输数据计算CRC值。 
    其中有16bit校验、LRC校验与32bit校验。

2、使用环境
    软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发

3、使用说明

    系统配置
        1、时钟源：HSI+PLL
        2、系统时钟频率：
           240MHz
        3、打印：PA9 - baud rate 115200

    使用方法：
        1、在KEIL下编译后烧录到开发板，通电
        2、通过串口输出运行信息

4、注意事项
    无
    
1. Function description
    1. This routine demonstrates the calculation of CRC value via DMA transfer of data.  
     There are 16bit checksum, LRC checksum and 32bit checksum.

2. Use environment
    Software development environment: 
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0


3. Instructions for use

    System Configuration:
        1. Clock source: HSI+PLL
        2. System Clock frequency: 
            240MHz
        3. printf: PA9 - baud rate 115200

     Instructions:
        1. Compile under KEIL and burn to the development board, then power on
         2. Output running information through serial port

4. Attention
    None

