1. 功能说明
    USB 使用外部SPI FLASH W25Q128 模拟 U 盘

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
         4. SPI配置：NSS--PA15、SCK--PB3、MISO--PD11、MOSI--PD12 (连接W25Q128)

    描述Demo的测试步骤和现象 
         1. 编译后下载程序复位运行；
         2. 通过 USB 线连接J4 USB 口，USB 挂载完成后，识别成 U 盘设备

4. 注意事项
    首次挂载 U 盘需要格式化，格式化完成后即可当成 U 盘使用。在N32H49XZEL7_EVB V1.1开发板上，J20用跳线帽连接

1. Function description
    USB uses external SPI FLASH W25Q128 to simulate a U disk

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
        4. SPI configuration: NSS--PA15、SCK--PB3、MISO--PD11、MOSI--PD12 (connected to W25Q128)
                  
    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. Connect the USB port through the J4 USB cable, and after the USB is mounted, it will be recognized as a U disk device.
 
4. Matters needing attention
    The first mount U disk needs to be formatted, and it can be used as a U disk after formatting. On N32H49XZEL7_EVB V1.1 board, J20 Connected with jumper cap