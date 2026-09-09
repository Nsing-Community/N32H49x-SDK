1、功能说明

    /* 简单描述工程功能 */
        这个例程配置并演示了FPU的浮点运算单元


2、使用环境

    软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1
    
    硬件开发环境：    
        基于全功能板N32H497ZGL7_EVB V1.0开发


3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
        SystemClock：240MHz
        USART：TX - PA9，波特率115200

    /* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.使用Julia套装测试FPU，查看打印的信息，并比较打开或关闭FPU单元的计算时间。


4、注意事项
    通过“Options for Target"的Target界面“Flaoting Point Hardware”选择打开或关闭FPU功能

1. Function description
    /* A brief description of the engineering function */
    This routine configures and demonstrates the FPU floating point arithmetic unit
2. Use environment

    Software development environment: 
        KEIL MDK-ARM V5.34.0.0
        IAR EWARM 8.50.1
    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0

3. Instructions for use
    
    /* Describe the related module configuration method; For example: clock, I/O, etc. */
        SystemClock: 240MHZ
        USART: TX-PA9, baud rate 115200
    /* Describes the test steps and symptoms of Demo */
    1. Reset and run the downloaded program after compilation;
    2. Use the Julia set to test the FPU, view the printed information, and compare the calculation time of opening or closing the FPU unit.
4. Attention
    Select whether to turn on or off the FPU function through the "Flaoting Point Hardware" option on the Target interface of "Options for Target"