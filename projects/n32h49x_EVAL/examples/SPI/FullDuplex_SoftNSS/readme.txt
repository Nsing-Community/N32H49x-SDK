1、功能说明

   1、SPI 全双工软件 NSS 模式发送接收数据

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

4、测试步骤与现象
    1、编译后下载程序复位运行；
    2、SPI主机 初始化位主机，发送数据，SPI2 初始化位从机，接收数据 ，传输完成后，检查数据，查看 TransferStatus1 和 TransferStatus2 状态为 PASSED，
	SPI2 初始化位主机，发送数据，SPI主机 初始化位丛机，接收数据 ，传输完成后，检查数据，查看 TransferStatus3 和 TransferStatus4 状态为 PASSED；

5、注意事项
无


1. Function description

     1. SPI full-duplex software NSS mode to send and receive data

2. Use environment

    Software development environment:
        IDE tool: KEIL MDK-ARM 5.34
	       IAR EWARM 8.50.1
    
    Hardware development environment:
        N32H497 Series:Based on evaluation board N32H497ZGL7_STB development
        N32H492 Series:Based on evaluation board N32H492ZGL7_STB development


3. Instructions for use

     1. Clock source: HSI+PLL
     2. System clock frequency:240MHz
	 3.SPI Master configuration:
           		SPI5 configuration: SCK--PF7, MISO--PF8, MOSI--PF9
     4、SPI2 Configuration (Slave):
           		SCK--PC7, MISO--PC2, MOSI--PD2

4. test steps and phenomena
     1. After compilation, the download program is reset and run;
     2. SPI Master initializes the bit host, sends data, SPI2 initializes the bit cluster machine, receives data, and after the transmission is completed, check the data, check that the status of TransferStatus1 and TransferStatus2 is PASSED,
         SPI2 initializes the bit host, sends data, SPI Master initializes the bit cluster machine, receives data, and after the transfer is completed, check the data, and check that the status of TransferStatus3 and TransferStatus4 is PASSED;

5. Attention
NO