1、功能说明

    /* 简单描述工程功能 */
    此例程展示了GPIO的基本配置方法。

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
            
    GPIO配置：
        PA3-LED1, PB3-LED2, PA8-LED3

    /* 描述Demo的测试步骤和现象 */
        1、编译后将程序下载到开发板并复位运行。
        2、可观察到2个LED同步闪烁4次后，3个LED依次循环点亮。

4、注意事项
    无
    
1. Function description

    /* Briefly describe the project function */
    This example shows the basic configuration of GPIO.

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
            
    GPIO Configuration: 
        PA3-LED1, PB3-LED2, PA8-LED3
        
    /* Describe the test steps and phenomena of the Demo */
        1. After compiling, download the program and reset, the program start running.
        2. First two LEDs blink 4 times, then the three LEDs turn on one by one and repeat.

4. Attention
    None

