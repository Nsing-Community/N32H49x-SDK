1、功能说明

    /* 简单描述工程功能 */
    PVD配置电压产生对应的中断。

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
        
    /* 描述Demo的测试步骤和现象 */
        在KEIL下编译后烧录到评估板，把电压调到PVD设置电压附近，此时程序会进PVD_IRQHandler()中断，并打印相关信息。


4、注意事项
    无

1. Function description
    
    /* Briefly describe the project function */
    The PVD configuration voltage generates a corresponding interrupt.

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

    /* Describe the test steps and phenomena of the Demo */
        After compiling under KEIL and burning to the evaluation board, adjust the voltage to near the PVD setting voltage, 
        at this time the program will go into the PVD_IRQHandler() interrupt and print the relevant information..

4. Attention
    None

