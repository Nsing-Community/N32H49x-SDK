1. 功能说明
    USB  Joystick Mouse 设备

2. 使用环境

    软件开发环境：KEIL MDK-ARM V5.34
                  IAR EWARM 8.50.1

    硬件开发环境：
        N32H49X系列：
        基于全功能板N32H497ZGL7_EVB V1.0开发

3. 使用说明
    描述相关模块配置方法；例如:时钟，I/O等 
         1. SystemClock：240MHz
         2. HSE: 16MHz
		 3. USBClock: 48MHz
         4. GPIO：上WKUP（PA0）、下KEY1（PC13）、左KEY2（PA15）、右KEY3（PB4）

    描述Demo的测试步骤和现象 
         1. 编译后下载程序复位运行；
         2. 通过 USB 线连接 J4 USB 口，按下 WKUP、KEY1、KEY2、KEY3 鼠标会上下左右移动。

4. 注意事项
    无

1. Function description
    USB Joystick Mouse device

2. Use environment

    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1

    Hardware development environment:
        N32H49X series:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 240MHz
        2. HSE: 16MHz
		3. USBClock: 48MHz
        4. GPIO: up WKUP (PA0), down KEY1 (PC13), left KEY2 (PA15), right KEY3 (PB4)
                  
    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. Connect the J4 USB port through a USB cable, press WKUP KEY1 KEY2 KEY3, the mouse will move up, down, left and right.
 
4. Matters needing attention
    none.