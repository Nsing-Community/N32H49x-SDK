1、功能说明
    USB MSC 设备

2、使用环境

    软件开发环境：KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1

    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发


3、使用说明
    描述相关模块配置方法；例如:时钟，I/O等 
         1. SystemClock：240MHz
         2. USBClock: HSE 16MHz
         3. SPI配置：NSS--PA15、SCK--PB3、MISO--PD11、MOSI--PD12 (连接W25Q128)

    描述Demo的测试步骤和现象 
         1. 编译后下载程序复位运行；
         2. 通过 USB 线连接 J62 USB 口，USB 挂载完成后，识别成 U 盘设备

4、注意事项
    可通过修改宏定义 USE_USB_HS_IN_FS 或 USE_USB_HS_IN_HS 切换设备为全速模式或者高速模式；
    另外需要使用16MHz、19.2MHz、20MHz、24MHz、26MHz或32MHz外部晶体。

1. Function description
    USB MSC device

2. Use environment
    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock：240MHz
        2. USBClock: HSE 16MHz
        3. SPI configuration: NSS--PA15、SCK--PB3、MISO--PD11、MOSI--PD12 (connected to W25Q128)
    
    Describe the testing steps and phenomena of the Demo

        1. Download the program after compiling and reset it to run;
        2. Connect the J62 USB port via a USB cable, and after the USB is mounted, it will be recognized as a U disk device.
        
4. Attention
     The device can be switched to Full-Speed mode or High-Speed mode by modify the macro definition USE_USB_HS_IN_FS or USE_USB_HS_IN_HS;
     In addition, external crystal of 16MHz, 19.2MHz, 20MHz, 24MHz, 26MHz or 32MHz is required.
