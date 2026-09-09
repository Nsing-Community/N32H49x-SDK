1、功能说明
    
    /* 简单描述工程功能 */
    此例程展示了JTAG接口的Remap功能。

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
            
    GPIO配置：
        PA3-LED1, PA8-LED3, PA0-KEY
    
    JTAG IO配置：
            PB4   PA15    PA14   PA13
            
    /* 描述Demo的测试步骤和现象 */
        1、编译后将程序下载到开发板并复位运行。
        2、默认状态为完全JTAG接口，PB4/PA15/PA14/PA13无方波输出。
        3、轻按按键，JTAG状态切换为无NJTRST的完全JTAG状态，PB4被释放，输出方波。
        4、再次轻按按键，JTAG状态切换为SWD状态，PB4/PA15均被释放，输出方波。
        5、再次轻按按键，JTAG接口禁用，PB4/PA15/PA14/PA13全部释放，输出方波。
        6、系统启动或JTAG状态发生变化时，串口都有相关提示信息输出。

4、注意事项
    无


1. Function description

    /* Briefly describe the project function */
    This example shows the rempa function of JTAG port.

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
            
    GPIO Configuration: 
        PA3-LED1, PA8-LED3, PA0-KEY
        
    JTAG IO Configuration: 
        PB4   PA15    PA14   PA13

     /* Describe the test steps and phenomena of Demo */
        1.  After compiling, download the program and reset, the program start running.
        2.  Default state is the complete JTAG interface, and PB4/PA15/PA14/PA13 
            have no square wave output.
        3.  Press the button, JTAG state switches to the complete JTAG state without NJTRST, 
            PB4 is released, and a square wave is output.
        4.  Press the button again, JTAG state switches to the SWD, 
            PB4/PA15 are released, and a square wave is output.
        5.  Press the button again, JTAG interface is disabled,  
            PB4/PA15/PA14/PA13 are all released, and a square wave is output.
        6.  When the system starts and the JTAG port changed, the serial port will 
            output relevant prompt information.

4. Attention
    None

