1、功能说明

    /* 简单描述工程功能 */
    这个例程配置并演示双bank切换方法。


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
    1. 配置MCU为双Bank模式。
    2. 编译后下载程序复位运行；
    3. 查看串口打印信息，刚上电时FLASH从BANK1启动，启动地址是0x8000000；
    4. 通过串口下发0x66指令，系统复位，MCU改为从BANK2启动，BANK2中未存储代码，故没有打印;
    5. 重新下载本例程并复位运行程序，FLASH从BANK2启动，启动地址仍然是0x8000000；
    6. 通过串口下发0x55指令，MCU通过Retry方式进行双bank切换（重映射）；
    7. 通过串口下发0x66指令，MCU通过Backup方式进行双bank切换（修改选项字节）；
    8. 通过串口下发0x77指令，MCU通过Reload方式进行双bank切换（重映射与修改选项字节组合使用）。
    9. MCU工作在Bank1时，LED1闪烁；MCU工作在Bank2时，LED2闪烁。
    10. 如果有发生重映射（Retry或Reload），LED1闪烁时，LED2常亮；LED2闪烁时，LED1常亮。

4、注意事项
    FLASH启动的地址一直是0x8000000，但是代码实际存储位置会发生切换。


1. Function description

    /* Briefly describe the project function */
    This routine configures and demonstrates the dual-bank switching method.


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
    1. Set MCU as dual bank mode.
    2. After compilation, download the program and reset it to run;
    3. Check the serial port printing information. When first powered on, system is starting from BANK1, the boot address is 0x8000000;
    4. Send the 0x66 instruction through the serial port, system reset and switch to start from BANK2. There is no code stored in BANK2, so it is not printed;
    5. Download this routine again and reset the running program. system is starting from BANK2, and the boot address is still 0x8000000;
    6. Send the 0x55 command through the serial port, the MCU performs a dual-bank switch (remapping) via Retry mode;
    7. Send the 0x66 command through the serial port, the MCU performs a dual-bank switch (modifying option bytes) via Backup mode;
    8. Send the 0x55 command through the serial port, the MCU performs a dual-bank switch (combination of remapping and option byte modification) via Reload mode;
    9. When the MCU is operating in Bank 1, LED1 blinks; when the MCU is operating in Bank 2, LED2 blinks.
    10.If a remapping (Retry or Reload) occurs, when LED1 blinks, LED2 remains on; when LED2 blinks, LED1 remains on.

4. Attention
    The FLASH boot address has always been 0x8000000, but the actual storage location of the code has changed.
