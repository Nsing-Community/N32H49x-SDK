    1. 功能说明
    USB 无晶体模式 HID 键盘设备

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
         4. GPIO：KEY1(PC13),KEY2(PA15),KEY3(PB4)键盘输入
            键盘灯控制：D1(PA3),D2(PB3)键盘输出

    描述Demo的测试步骤和现象 
         1. 编译后下载程序复位运行；
         2. 通过 USB 线连接 J4 USB 口，电脑识别出键盘设备，按下KEY1,KEY2,KEY3按键，USB 输入 "a","b","c"，
            用另外一个键盘开关Capslock和Numlock，可以看到D1和D2对应键盘灯亮灭

4. 注意事项
    无

1. Function description
    USB xtal less mode HID keyboard device

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
        4. GPIO: KEY1(PC13),KEY2(PA15),KEY3(PB4) keyboard input 
           Keyboard light control: D1(PA3),D2(PB3) keyboard output
    
    Describe the testing steps and phenomena of the Demo

        1. Download the program after compiling and reset it to run;
        2. Connect the J4 USB port via a USB cable, and the computer recognizes the keyboard device. Press KEY1,KEY2,KEY3, and USB inputs "a", "b", and "c".
           Using another keyboard to toggle Capslock and Numlock, D1 and D2 output corresponding ON and OFF.
 
4. Matters needing attention
    None.