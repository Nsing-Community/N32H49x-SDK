1、功能说明
    USB Mouse设备

2、使用环境

    软件开发环境：KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1

    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发


3、使用说明
    描述相关模块配置方法；例如:时钟，I/O等 
         1. SystemClock：240MHz
         2. USBClock: HSE 16MHz
         3. GPIO：上WKUP（PA0）、下KEY1（PC13）、左KEY2（PA15）、右KEY3（PB4）。

    描述Demo的测试步骤和现象 
         1. 编译后下载程序复位运行；
         2. 通过 USB 线连接 J3 USB 口，电脑识别出键盘设备
         3. 按下按键WKUP、KEY1、KEY2、KEY3，鼠标会上下左右移动。

4、注意事项
    可通过修改宏定义 USE_USB_HS_IN_FS 或 USE_USB_HS_IN_HS 切换设备为全速模式或者高速模式；
    另外需要使用16MHz、19.2MHz、20MHz、24MHz、26MHz或32MHz外部晶体。

1. Function description
    USB Mouse device

2. Use environment
    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 240MHz
        2. USBClock: HSE 16MHz
        3. GPIO: up WKUP (PA0), down KEY1 (PC13), left KEY2 (PA15), right KEY3 (PB4)
    
    Describe the testing steps and phenomena of the Demo

        1. Download the program after compiling and reset it to run;
        2. Connect the J3 USB port via a USB cable, and the computer recognizes the mouse device; 
        3. When press WKUP KEY1 KEY2 KEY3, the mouse will move up, down, left and right.
        
4. Attention
    The device can be switched to Full-Speed mode or High-Speed mode by modify the macro definition USE_USB_HS_IN_FS or USE_USB_HS_IN_HS;
    In addition, external crystal of 16MHz, 19.2MHz, 20MHz, 24MHz, 26MHz or 32MHz is required.