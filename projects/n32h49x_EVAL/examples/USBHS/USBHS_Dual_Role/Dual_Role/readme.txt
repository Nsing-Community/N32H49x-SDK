1、功能说明
    USB 双角色 MSC

2、使用环境

    软件开发环境：KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1

    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发


3、使用说明
    描述相关模块配置方法；例如:时钟，I/O等 
         1. SystemClock：240MHz
         2. USBClock: HSE 16MHz
         3. GPIO:  确定-KEY1（PC13）下-KEY2（PA15）上KEY3（PB4）WAKEUP（PA0）VBUS驱动引脚-PH2
         4. SPI配置：NSS--PA15、SCK--PB3、MISO--PD11、MOSI--PD12 (连接W25Q128)
         5. 串口配置：
            - 串口为USART1（TX：PA9  RX：PA10）:
            - 数据位：8
            - 停止位：1
            - 奇偶校验：无
            - 波特率： 115200 

    描述Demo的测试步骤和现象 
         1. 编译后下载程序复位运行；
         2. 打开串口调试助手，设置波特率为115200bps
         3. 根据打印使用按键KEY1,KEY2,KEY3来选择当前USB角色（主机模式或设备模式），如下所示，箭头指向当前角色选择
                    1 - Host mode
                    2 - Device mode
         4. 如果是选择设备，通过 USB 线连接 J62 USB 口，USB 挂载完成后，识别成 U 盘设备
         5. 如果选择主机，通过J62连接OTG转接线，再接上U盘，等待枚举完成，按下WKUP按键，根据打印选择读写U盘


4、注意事项
    可通过修改宏定义 USE_USB_HS_IN_FS 或 USE_USB_HS_IN_HS 切换设备为全速模式或者高速模式；
    另外需要使用16MHz、19.2MHz、20MHz、24MHz、26MHz或32MHz外部晶体。

1. Function description
    USB Dual role MSC

2. Use environment
    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 240MHz
        2. USBClock: HSE 16MHz
        3. GPIO: SEL_OK-KEY1（PC13） DOWN-KEY2(PA15) UP-KEY1(PB4) WAKEUP(PA0) VBUS driver pin(PH2).
        4. SPI：NSS--PA15、SCK--PB3、MISO--PD11、MOSI--PD12
        5. Serial port configuration:
            - Serial port: USART1 (TX: PA9 RX: PA10) :
            - Data bit: 8
            - Stop bit: 1
            - Parity check: None
            - Baud rate: 115200

    Describe the testing steps and phenomena of the Demo
    1. Compile the program and download it for reset and execution.
    2. Open the serial port debugging Assistant and set the baud rate to 115200bps.
    3. Use KEY1,KEY2,KEY3 to select the current USB role (host mode or device mode) according to the print, as shown below, the arrow points to the current role selection.
            1 - Host mode
            2 - Device mode
    4. If device mode is selected, connect it to the J62 USB port using a USB cable. After the USB is mounted, the device is identified as a USB flash drive.
    5. If host mode is selected, connect the OTG conversion cable through J62, and then connect the USB flash drive. 
       Wait for the enumeration to complete, press WKUP, then select read or write the USB flash drive according to the print
      
        
4. Attention
    The device can be switched to Full-Speed mode or High-Speed mode by modify the macro definition USE_USB_HS_IN_FS or USE_USB_HS_IN_HS;
    In addition, external crystal of 16MHz, 19.2MHz, 20MHz, 24MHz, 26MHz or 32MHz is required.