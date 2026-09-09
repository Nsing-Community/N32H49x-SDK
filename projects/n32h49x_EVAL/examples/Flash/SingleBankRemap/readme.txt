1、功能说明

    /* 简单描述工程功能 */
    这个例程配置并演示单Bank模式下FLASH启动地址的重映射操作。


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
    1. 配置FLASH为单Bank模式。
    2. 编译后下载程序复位运行；
    3. 查看串口打印信息，刚上电时FLASH从前半部分启动，启动地址是0x8000000；
    4. 通过串口下发0x66指令，系统复位，MCU改为从后半部分启动，后半部分中未存储代码，故没有打印；
    5. 重新下载本例程并复位运行程序，FLASH从后半部分启动，启动地址是0x8000000；
    6. 通过串口下发0x77指令，FLASH重映射到前半部分启动，启动地址是0x8000000；
    7. 通过串口下发0x88指令，FLASH重映射到后半部分启动，启动地址是0x8000000；
    8. 通过串口下发0x55指令，系统复位，MCU改为从前半部分启动，启动地址是0x8000000；

4、注意事项
    1. FLASH启动的地址一直是0x8000000，但是代码实际存储位置会发生切换。
    2. FLASH默认是双BANK模式，需要更改为单BANK模式后再测试此demo，不然发生BANK模式切换时需要重新下载代码。


1. Function description

    /* Briefly describe the project function */
    This routine configures and demonstrates Changing the FLASH remap mode in single bank.


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
    1. Set MCU as single bank mode.
    2. After compilation, download the program and reset it to run;
    3. Check the serial port printing information. When first powered on, system is starting from forward half, the boot address is 0x8000000;
    4. Send the 0x66 instruction through the serial port, system reset and switch to start from back half. There is no code stored in back half, so it is not printed;
    5. Download this routine again and reset the running program. system is starting from back half, and the boot address is 0x8000000;
    6. Issue the 0x77 command through the serial port, system is remap to forward half, and the boot address is 0x8000000;
    7. Issue the 0x88 command through the serial port, system is remap to back half with the boot address of 0x8000000;
    8. Send the 0x55 command through the serial port,  system reset and switch to start from forward half with the boot address of 0x8000000;

4. Attention
    1. The FLASH boot address has always been 0x8000000, but the actual storage location of the code has changed.
    2. FLASH defaults to dual BANK mode. You need to change it to single BANK mode before testing this demo, otherwise you will need to download the code again when the BANK mode switch occurs.
