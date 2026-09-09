1、功能说明

    /* 简单描述工程功能 */
        这个例程配置并演示直接对FLASH进行读写操作


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
        1.编译后下载程序复位运行；
        2.查看串口打印信息，当写入FLASH的数据与读取数据对比均相同时，打印信息为测试结束；
        3.下发0x55可以恢复选项字节默认值配置


4、注意事项


1. Function description

    /* Briefly describe the project function */
         This routine configures and demonstrates direct read and write operations to FLASH


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
         1. After compiling, download the program to reset and run;
         2. Check the printing information of the serial port. When the data written to FLASH is the same as the data read, the printing information is the end of the test;
         3. Issuing 0x55 can restore the default value configuration of option bytes


4. Attention
