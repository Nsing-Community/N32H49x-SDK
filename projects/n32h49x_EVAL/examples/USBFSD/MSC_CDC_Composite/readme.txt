1. 功能说明
    USB MSC + CDC 组合设备

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
         4. SPI配置：NSS--PA15、SCK--PB3、MISO--PD11、MOSI--PD12(连接W25Q128)
         5. GPIO：USART1（TX--PA9，RX--PA10）波特率 115200
         6. 虚拟串口：
            - 波特率：115200
            - 数据位：8
            - 停止位：1
            - 奇偶校验：无
            - 波特率： 115200 

    描述Demo的测试步骤和现象 
         1. 编译后下载程序复位运行；
         2. 通过 USB 线连接 J4 USB 口，电脑识别出串口和U盘设备;
         3. 在电脑设备管理中可以看到新增的串口，将 USART1 接到串口工具上，打开 USB 虚拟串口，
            USB 虚拟串口发送数据，用串口工具接收数据，然后用串口工具发送数据， USB 虚拟串口接收数据。

4. 注意事项
    首次挂载 U 盘需要格式化，格式化完成后即可当成 U 盘使用。在N32H49XZEL7_EVB V1.1开发板上，J20用跳线帽连接

1. Function description
    USB MSC + CDC composite device

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
        4. SPI configuration: NSS--PA15、SCK--PB3、MISO--PD11、MOSI--PD12
        5. GPIO: USART1 (TX--PA9, RX--PA10) baud rate 115200
        6. Virtual serial port：
            - Baud rate: 115200
            - Data bits: 8
            - Stop position: 1
            - Parity check: none
            - Baud rate: 115200
    
    Describe the testing steps and phenomena of the Demo

        1. Download the program after compiling and reset it to run;
        2. Connect the J4 USB port via a USB cable, and the computer recognizes the HID device and U disk.
        3. The new serial port can be seen in the computer device management, connect USART1 to the serial port tool, open the USB virtual serial port;
           The USB virtual serial port sends data, the serial port tool receives data, and the serial port tool sends data, and the USB virtual serial port receives data.
 
4. Matters needing attention
    The first mount U disk needs to be formatted, and it can be used as a U disk after formatting. On N32H49XZEL7_EVB V1.1 board, J20 Connected with jumper cap