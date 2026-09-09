1、功能说明

    /* 简单描述工程功能 */
    STANDBY模式的进入和退出。

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
        WAKEUP按键-PA0

    /* 描述Demo的测试步骤和现象 */
        在KEIL下编译后烧录到评估板，串接电流表，上电后一段时间进入STANDBY模式，电流明显变小。按下WAKEUP按键，退出STANDBY模式，电流变大。
        如果开启打印输出，可以看到串口输出“Entry STANDBY mode”，唤醒后输出“--- Reset for STANDBY ---”，说明STANDBY唤醒后从0地址开始执行。


4、注意事项
    在评估功耗的时候，要注意去掉打印

1. Function description
    
    /* Briefly describe the project function */
    Enter and exit STANDBY mode.

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
        WAKEUP button-PA0

    /* Describe the test steps and phenomena of the Demo */
        Compiled under KEIL and burned to the evaluation board, connected an ammeter in series, powered up and went into STANDBY mode for a while and 
        the current became significantly lower. Press the WAKEUP button to exit STANDBY mode, and the current is back.
        If you turn on the printout, you can see that the serial port outputs "Enter STANDBY mode" and "---- Reset for STANDBY ----" after waking up, 
        which means that STANDBY wakes up and starts executing from address 0.

4. Attention
    When evaluating power consumption, pay attention to removing the printf

