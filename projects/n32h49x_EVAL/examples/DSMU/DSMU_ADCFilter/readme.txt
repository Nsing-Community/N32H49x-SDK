1、功能说明
    
    /* 简单描述工程功能 */
    此例程演示了DSMU如何对MCU内置ADC采样数据进行滤波和过采样。
    
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

    ADC配置：
        ADC2,通道17-PH3
        
    DSMU配置：
        输入通道1:内部ADC2
        滤波器0：Sinc2滤波，16倍滤波器过采样率，4倍积分器过采样率

    /* 描述Demo的测试步骤和现象 */
        1、连接跳线J18。
        2、编译后烧录到开发板，复位MCU。
        3、通过串口输出运行信息。

4、注意事项
    1、通过DSMU滤波会大幅降低最终数据的采样率。
    2、DSMU仅支持对1个ADC规则通道进行数据滤波。
    
    
1. Function description

    /* Briefly describe the project function */
    This example shows how to filter and oversample the internal ADC data by DSMU.

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
            
    ADC Configuration: 
        ADC2, channel17-PH3
        
    DSMU Configuration: 
        Input channel 1: ADC2
        Filter0: Sinc2 type,filter oversampling ratio is 16,Integrator oversampling ratio is 4 

    /* Describe the test steps and phenomena of the Demo */
        1. Connected jumper J18.
        2. Compile the programme, and download to the evaluation board, then reset MCU.
        3. The running informations are output through the serial port.

4. Attention
    1. Filtering through DSMU will significantly reduce the sampling rate of the final data.
    2. DSMU only supports data filtering for 1 regular channel of ADC.