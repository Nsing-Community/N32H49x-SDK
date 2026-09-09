1、功能说明

    此例程提供了一种DMA MemtoMem模式用法，用于在FLASH与RAM之间传输数据。

2、使用环境

    软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发


3、使用说明

    1、时钟源：HSE+PLL
    2、时钟频率：240MHz
    3、DMA通道：DMA1_CH1
    4、USART：TX - PA9，RX - PA10，波特率115200
    5、测试步骤与现象
        a，编译下载代码复位运行
        b，DMA传输完成，串口打印"DMA Flash to RAM passed"，表示传输无误

4、注意事项
    无


1. Function description

    This routine provides a DMA MemtoMem mode usage for transferring data between FLASH and RAM.

2. Use environment

    Software development environment: 
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0


3. Instructions for use

    1. Clock source: HSI+PLL
    2. Clock frequency: 240MHz
    3. DMA channel: DMA1_CH1
    4. USART: TX - PA9，RX - PA10, baud rate 115200
    5. Test steps and phenomena
        a, Compile and download the code reset run
        b, DMA transfer completed. The serial port prints“DMA Flash to RAM passed” indicating the transfer was successful

4. Attention
    None


