1、功能说明
    
    /* 简单描述工程功能 */
    此例程展示了通过SDIO主机接口与TF卡之间数据读写功能。
             
2、使用环境

    软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发
        
3、使用说明
    
    /* 描述相关模块配置方法；例如:时钟，I/O等 */
    系统时钟配置：
        SystemClock：240MHz
            
    打印串口配置：
        USART：TX - PA9，RX - PA10，波特率115200
        
    DMA通道配置：
        DMA1通道1：SDIO读写
    
    SDIO 配置：
        端口: PB4  - SDIO_DAT0
              PB0  - SDIO_DAT1
              PC10 - SDIO_DAT2
              PC11 - SDIO_DAT3
              PC12 - SDIO_CLK 
              PD2  - SDIO_CMD 
        时钟源：120MHz（SDIOCLK = HCLK/2）
        分频系数：298（初始化）、4（数据传输），SDIO_CLK = SDIOCLK/(2 + 分频系数)
        SDIO_CLK上升沿有效，禁用硬件流控，总线位宽4bit
    
    GPIO配置：
        PA0-按键

    /* 描述Demo的测试步骤和现象 */
        1、测试前请先安装好TF卡。
        2、编译后将程序下载到开发板并复位运行。
        3、轻按按键,对TF卡进行一次读写擦测试。
        4、通过串口输出相关提示信息。

4、注意事项
    必须外接TF卡座。

1. Function description
    
    /* Briefly describe the project function */
    This example shows the data read and write function between SDIO host interface and TF card.

2. Use environment

    Software development environment: 
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

     Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0

3. Instructions for use   

    /* Describe related module configuration methods; for example: clock, I/O, etc. */
    System Clock Configuration:
        SystemClock：240MHz
            
    Print Serial Port Configuration:
        USART：TX - PA9，RX - PA10, baud rate 115200

    DMA Configuration:
        DMA1 channel1: SDIO read or write
        
    SDIO Configuration:
        Ports: PB4  - SDIO_DAT0
               PB0  - SDIO_DAT1
               PC10 - SDIO_DAT2
               PC11 - SDIO_DAT3
               PC12 - SDIO_CLK 
               PD2  - SDIO_CMD 
        clock source：120MHz (SDIOCLK = HCLK/2)
        clock divider factor：298(initialization) and 4(data transfer), SDIO_CLK = SDIOCLK/(2 + factor)
        SDIO_CLK rising edge, hardware flow control disabled, 4bits bus

    GPIO Configuration:
        PA0-KEY

    /* Describe the test steps and phenomena of the Demo */
        1. Please install the TF card before the test.
        2. After compiling, download the program and reset.
        3. Press the button, the read/erase/write test for TF card start.
        4. The serial port will output relevant prompt information.
        
4. Attention
    An extenel TF card slot must be connected.