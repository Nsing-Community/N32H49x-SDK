1、功能说明
    USB Keyboard设备

2、使用环境

    软件开发环境：KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1

    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发


3、使用说明
    描述相关模块配置方法；例如:时钟，I/O等 
         1. SystemClock：240MHz
         2. USBClock: HSE 16MHz
         3. GPIO：WKUP(PA0 )KEY1(PC13) KEY2(PA15) KEY3(PB4)键盘输入
            键盘灯控制：D1(PA3),D2(PB3)键盘输出
            
    描述Demo的测试步骤和现象 
         1. 编译后下载程序复位运行；
         2. 通过 USB 线连接 J62 USB 口，电脑识别出键盘设备
         3. 按下WKUP,KEY1,KEY2,KEY3按键，USB 输入 "a","b","c","d"
         4. 用另外一个键盘开关Capslock和Numlock，可以看到D1和D2对应键盘灯亮灭

4、注意事项
    可通过修改宏定义 USE_USB_HS_IN_FS 或 USE_USB_HS_IN_HS 切换设备为全速模式或者高速模式；
    另外需要使用16MHz、19.2MHz、20MHz、24MHz、26MHz或32MHz外部晶体。

1. Function description
    USB Keyboard device

2. Use environment
    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc.
        1. SystemClock: 240MHz
        2. USBClock: HSE 16MHz
        3. GPIO: WKUP(PA0 )KEY1(PC13) KEY2(PA15) KEY3(PB4) keyboard input
           Keyboard light control: D1(PA3),D2(PB3) keyboard output
    
    Describe the testing steps and phenomena of the Demo

        1. Download the program after compiling and reset it to run;
        2. Connect the J62 USB port via a USB cable, and the computer recognizes the mouse device; 
        3. Press WKUP,KEY1,KEY2,KEY3, and USB inputs "a", "b", "c", "d".
        4. Using another keyboard to toggle Capslock and Numlock, D1 and D2 output corresponding ON and OFF.
        
4. Attention
    The device can be switched to Full-Speed mode or High-Speed mode by modify the macro definition USE_USB_HS_IN_FS or USE_USB_HS_IN_HS;
    In addition, external crystal of 16MHz, 19.2MHz, 20MHz, 24MHz, 26MHz or 32MHz is required.