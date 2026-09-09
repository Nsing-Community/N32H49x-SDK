1、功能说明

    /* 简单描述工程功能 */
        这个例程配置并演示NVIC优先级设置


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    
    硬件开发环境：    
        基于全功能板N32H497ZGL7_EVB V1.0开发


3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
    系统时钟配置：
        SystemClock：240MHz
            
    打印串口配置：
        USART：TX - PA9，RX - PA10，波特率115200
    
        EXIT：PA15为浮空输入模式，外部中断线 - EXIT_LINE4，开启外部中断
    
    SysTick：中断优先级设置为0

    /* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.正常情况下打印SysTick中断信息，当按键外部中断和SysTick中断同时触发时，修改SysTick中断优先级为2，并打印相关信息，程序运行正常；


4、注意事项



1. Function description
    /* A brief description of the engineering function */
    TThis routine configures and demonstrates NVIC priority Settings

2. Use environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0
        

3. Instructions for use

    /* Describe related module configuration methods; for example: clock, I/O, etc. */
    System Clock Configuration:
        SystemClock：240MHz
            
    Print Serial Port Configuration:
        USART：TX - PA9，RX - PA10, baud rate 115200               
        EXIT: PA15 is in floating input mode, and external interrupt line -exit_line4 is used to enable external interrupt
        
    TIM: Pre-dividing frequency coefficient - (SystemClock/1200-1), period - (1200-1), start timer interrupt
    /* Describes the test steps and symptoms of Demo */
    1. Reset and run the downloaded program after compilation;
    2. In normal cases, SysTick interrupt information is displayed. If both the external interrupt and SysTick interrupt are triggered at the same time, 
       change the SysTick interrupt priority to 2 and print related information.

4. Attention
    None
