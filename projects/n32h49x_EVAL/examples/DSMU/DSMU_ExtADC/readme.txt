1、功能说明
    
    /* 简单描述工程功能 */
    此例程演示了DSMU如何对外接ADC串行数据进行数据处理。

    
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
        
    DSMU配置：
        时钟输出：PD3-CKOUT，20MHz
        输入通道4：
            外部ADC(NSI1306M25)：PD7-DATIN4
            SPI接口，下降沿采样
        滤波器0：Sinc3滤波，32倍滤波器过采样率，积分器旁路
        
    DMA配置:
        DMA1通道1: 从DSMU读取滤波结果

    /* 描述Demo的测试步骤和现象 */
        1、编译后烧录到开发板，复位MCU。
        2、通过串口输出运行信息

4、注意事项
    1、通过DSMU滤波会大幅降低最终数据的采样率。
    2、全功能板上J26 GND/VIN+必须通过跳线连接其他GND。
    
    
1. Function description

    /* Briefly describe the project function */
    This example shows how the DSMU processes the external ADCk serial data.
    
2. Development environment

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
        
    DSMU Configuration: 
        Clock output: PD3-CKOUT, 20MHz
        Input channel 4:
            External ADC(NSI1306M25): PD7-DATIN4
            SPI interface, sampling at falling edge
        Filter0: Sinc3,filter oversampling ratio is 32, Integrator bypass
        
    DMA Configuration: 
        DMA1 channel1: Read result of DSMU

    /* Describe the test steps and phenomena of the Demo */
         1. Compile the programme, and download to the evaluation board, then reset MCU.
         2. The running informations are output through the serial port.

4. Attention
    1. Filtering through DSMU will significantly reduce the sampling rate of the final data.
    2. On the board N32H497ZGL7_EVB, the GND and VIM+ signal of J26 must be connected to other GND.