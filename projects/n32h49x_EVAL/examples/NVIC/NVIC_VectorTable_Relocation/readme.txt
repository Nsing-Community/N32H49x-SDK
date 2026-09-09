1、功能说明

    /* 简单描述工程功能 */
        这个例程配置并演示NVIC中断向量表重定位


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
    
        EXIT：PA15为浮空输入模式，外部中断线 - EXIT_LINE4，开启外部中断，优先级为0

    /* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.一开始向量表位于FLASH，当按键按下后向量表重定位至SRAM，并打印相关信息，程序运行正常；


4、注意事项



1. Function description
    /* A brief description of the engineering function */
    This routine configures and demonstrates NVIC interrupt directional table relocation

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
        EXIT: PA15 is floating input mode, external interrupt line -exit_line4, external interrupt is enabled, and the priority is 0
        
    TIM: Pre-dividing frequency coefficient - (SystemClock/1200-1), period - (1200-1), start timer interrupt
    /* Describes the test steps and symptoms of Demo */
    1. Reset and run the downloaded program after compilation;
    2. At the beginning, the directional table is located in FLASH. When the button is pressed, 
       the backward table is repositioned to SRAM and relevant information is printed, and the program runs normally;


4. Attention
    None
