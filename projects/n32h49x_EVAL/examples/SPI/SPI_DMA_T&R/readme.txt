1、功能说明
  1、SPI DMA 单线发送和单线接收数据

2、使用环境
    软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    硬件开发环境：
        基于评估板N32H497ZGL7_STB V1.0开发

3、使用说明

    1、时钟源：HSI+PLL
    2、系统时钟频率：240MHz
    3、	SPI主机配置：
           SPI5配置：NSS--PF6、SCK--PF7、MOSI--PF9
	4、SPI2配置（从）：
           	NSS--PD1、SCK--PC7、MISO--PC2

	5、测试步骤与现象
		1、编译后下载程序复位运行；
		2、SPI主机通过DMA发送数据，SPI2 通过 DMA 接收数据，数据传输完成后，查看 TransferStatus 状态为 PASSED；

4、注意事项
    1、“单线”数据线在主设备端为MOSI引脚，在从设备端为MISO引脚
    
1. Function description
   1、SPI DMA single line to receive data

2. Use environment
    Software development environment: 
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the evaluation board N32H497ZGL7_STB

3. Instructions for use

    1, clock source: HSI + PLL
    2、System clock frequency:240MHz
    3. SPI Master configuration:
           SPI5 configuration: NSS--PF6, SCK--PF7, MOSI--PF9
	4、SPI2 Configuration (Slave):
           NSS--PD1, SCK--PC7, MISO--PC2

	5, test steps and phenomena
		1, after compiling and downloading the program reset to run;
		2, SPI Master sends data, SPI2 receives data through DMA, after the data transfer is completed, check the status of TransferStatus is PASSED;

4. Attention
    1, "single line" data line in the master device terminal for the MOSI pin, in the slave device terminal for the MISO pin

