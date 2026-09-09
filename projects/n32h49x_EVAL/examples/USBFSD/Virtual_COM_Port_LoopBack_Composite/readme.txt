1. 功能说明
    USB模拟串口回环测试

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
         4. 虚拟串口：
            - 波特率：115200
            - 数据位：8
            - 停止位：1
            - 奇偶校验：无
            - 波特率： 115200 
         

    描述Demo的测试步骤和现象 
         1. 编译后下载程序复位运行；
         2. 通过 USB 线连接 J4 USB 口，USB 挂载完成后，在电脑设备管理中可以看到新增的串口，打开 USB 虚拟串口，
            使用串口工具发送数据，串口工具会马上收到刚刚发送的数据。

4. 注意事项
    无

1. Function description
    USB virtual serial port loop back

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
        4. Virtual serial port：
            - Baud rate: 115200
            - Data bits: 8
            - Stop position: 1
            - Parity check: none
            - Baud rate: 115200
                  
    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. Connect the J4 USB port via a USB cable. After the USB mount is complete, you can see the newly added serial port in the computer device management. 
            Open the USB virtual serial port, using the serial port tool to send data, the serial port tool will immediately receive the data just sent.
 
4. Matters needing attention
    None