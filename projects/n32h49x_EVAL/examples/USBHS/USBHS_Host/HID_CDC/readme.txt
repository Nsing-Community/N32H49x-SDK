1、功能说明
    USB 主机 HID mouse & HID keyboard & CDC

2、使用环境

    软件开发环境：KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1

    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发


3、使用说明
    描述相关模块配置方法；例如:时钟，I/O等 
    1. SystemClock：240MHz
    2. USBClock: HSE 16MHz
    3. GPIO: 确定-KEY1（PC13）下-KEY2（PA15）上KEY3（PB4）WAKEUP（PA0）VBUS驱动引脚-PH2
    4. 串口配置：
            - 串口为USART1（TX：PA9  RX：PA10）:
            - 数据位：8
            - 停止位：1
            - 奇偶校验：无
            - 波特率： 115200 

    描述Demo的测试步骤和现象 
    1. 编译后下载程序复位运行；
    2. 打开串口调试助手，设置波特率为115200bps
    3. 连接OTG转接线，再接上鼠标或键盘，等待枚举完成
    4. 枚举完成后，按下WKUP按键，开始鼠标或键盘或CDC设备数据通信 
    5. 串口调试助手界面打印相应鼠标坐标或键盘键值信息或
       根据打印信息按KEY2, KEY3 选择发送或接收串口数据或串口配置，KEY1按键确认选项

4、注意事项
    可通过修改宏定义 USE_USB_HS_IN_FS 或 USE_USB_HS_IN_HS 切换设备为全速模式或者高速模式；
    需要使用16MHz、19.2MHz、20MHz、24MHz、26MHz或32MHz外部晶体。

1. Function description
    USB host HID mouse & HID keyboard & CDC

2. Use environment
    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
    1. SystemClock: 240MHz
    2. USBClock: HSE 16MHz
    3. GPIO: SEL_OK-KEY1（PC13） DOWN-KEY2(PA15) UP-KEY1(PB4) WAKEUP(PA0) VBUS driver pin(PH2)
    4. Serial port configuration:
            - Serial port: USART1 (TX: PA9 RX: PA10) :
            - Data bit: 8
            - Stop bit: 1
            - Parity check: None
            - Baud rate: 115200
    
    Describe the testing steps and phenomena of the Demo
    1. Compile the program and download it for reset and execution.
    2. Open the serial port debugging Assistant and set the baud rate to 115200bps.
    3. Connect the OTG adapter, followed by the mouse or keyboard, and wait for enumeration to complete.
    4. After enumeration is complete, press the WKUP button to start mouse or keyboard or CDC device data communication.
    5. The serial port Debugging Assistant interface will display the corresponding mouse coordinates or keyboard key value information or
       based on the printed information, pressing KEY2, KEY3 can select send or receive data or configurate USART, and pressing the KEY1 confirms the selection.
    
4. Attention
    The device can be switched to Full-Speed mode or High-Speed mode by modify the macro definition USE_USB_HS_IN_FS or USE_USB_HS_IN_HS;
    External crystal of 16MHz, 19.2MHz, 20MHz, 24MHz, 26MHz or 32MHz is required.