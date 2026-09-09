1、功能说明

    1、SPI 发送接收数据进行 CRC 校验

2、使用环境

    软件开发环境：
        IDE工具：KEIL MDK-ARM 5.34
	       IAR EWARM 8.50.1
    
    硬件开发环境：
        基于评估板N32H497ZGL7_STB V1.0开发

3、使用说明
    
    1、时钟源：HSI+PLL
    2、系统时钟频率：240MHz
    3、SPI主机配置：
         SPI5配置：SCK--PF7、MISO--PF8、MOSI--PF9
    4、SPI2配置（从）：
         SCK--PC7、MISO--PC2、MOSI--PD2

   5、测试步骤与现象
    1、编译后下载程序复位运行；
    2、SPI主机、SPI2 同时收发数据 ，传输完成后，发送 CRC 数据，检查数据和 CRC 值，查看 TransferStatus1 和 TransferStatus2 状态为 PASSED，
         再查看 CRC 值；

4、注意事项
无


1. Function description

    1、SPI send and receive data for CRC check.

2. Use environment

    Software development environment:
        IDE tool: KEIL MDK-ARM 5.34
	       IAR EWARM 8.50.1
    
    Hardware development environment:
        Developed based on the evaluation board N32H497ZGL7_STB

3. Instructions for use
    
    1, clock source: HSI + PLL
    2、System clock frequency:240MHz
    3.SPI Master configuration:
          SPI5 configuration: SCK--PF7, MISO--PF8, MOSI--PF9
    4、SPI2 Configuration (Slave):
		  SCK--PC7, MISO--PC2, MOSI--PD2

   5, test steps and phenomena
    1, after compiling and downloading the program reset run;
    2, SPI Master, SPI2 send and receive data at the same time, after the completion of the transfer, send CRC data, check the data and CRC value, check TransferStatus1 and TransferStatus2 status is PASSED, and then check the CRC value.
         Then check the CRC value;

4. Attention
No