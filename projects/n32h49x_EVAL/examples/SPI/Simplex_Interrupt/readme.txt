1、功能说明

    1.SPI 单线中断发送和接收数据

2、使用环境
   软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

   硬件开发环境：
        基于评估板N32H497ZGL7_STB V1.0开发
		
3、使用说明
	1.时钟源：HSI+PLL
    2.系统时钟频率：240MHz
    3.SPI主机配置：
		SPI5配置：SCK--PF7、MOSI--PF9
    4.SPI2配置（从）：
        SCK--PC7、MISO--PC2
    5.测试步骤与现象
      1.编译后下载程序复位运行；
      2.SPI主机 有数据需要发送时进入 SPI5_IRQHandler 中断函数发送，SPI2 有数据需要接收时进入 SPI2_IRQHandler 中断函数接收，
      数据传输完成后，查看 TransferStatus 状态为 PASSED；

4、注意事项
   1.“单线”数据线在主设备端为MOSI引脚，在从设备端为MISO引脚
    
1, Function description
   1.SPI single line interrupt send and receive data

2, Use environment
    Software development environment: 
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the evaluation board N32H497ZGL7_STB

3, Instructions for use
    1. clock source: HSI + PLL
    2.System clock frequency:240MHz
	3.SPI Master configuration:
        SPI5 configuration: SCK--PF7, MOSI--PF9
	4.SPI2 Configuration (Slave):
         SCK--PC7, MISO--PC2

	5. Test steps and phenomena
		1. Compile and download the program reset run;
		2. SPI Master has data to be sent into the SPI5_IRQHandler interrupt function to send, SPI2 has data to be received into the SPI2_IRQHandler interrupt function to receive.
		After the data transfer is completed, check the TransferStatus status is PASSED;

4, Attention
    1，The "single wire" data line is MOSI pin on the master device side and MISO pin on the slave device side.
   