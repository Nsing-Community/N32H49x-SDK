1、功能说明

    /* 简单描述工程功能 */
    此例程演示了DSMU的基本用法，采用直接写数据寄存器的方式模拟输入信号数据，通过DSMU滤波后，可明显减小信号抖动。

    
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
        输入通道0:CPU直接写入
        滤波器0：Sinc2滤波，16倍滤波器过采样率，积分器旁路
   
    /* 描述Demo的测试步骤和现象 */
        1、编译后烧录到开发板，复位MCU。
        2、通过串口输出运行信息

4、注意事项
    无
    
    
1. Function description
    
    /* Briefly describe the project function */
    This example shows how to use the DSMU module. 
    Signal data is input by directly writing register, and the signal jitter can be reduced.
    
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
        Input channel 0: CPU write
        Filter0: Sinc2 type,filter oversampling ratio is 16,Integrator bypass 

    /* Describe the test steps and phenomena of the Demo */
         1. Compile the programme, and download to the evaluation board, then reset MCU.
         2. The running informations are output through the serial port.

4. Attention
     None