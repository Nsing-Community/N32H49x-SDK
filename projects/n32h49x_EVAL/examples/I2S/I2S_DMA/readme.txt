 1、功能说明

    1、I2S 通过 DMA 收发数据

2、使用环境

      软件开发环境：
        IDE工具：KEIL MDK-ARM 5.34
	       IAR EWARM 8.50.1
    
    硬件开发环境：
        基于评估板N32H497ZGL7_STB开发

3、使用说明
    
    1、时钟源：HSI+PLL
    2、系统时钟频率：240MHz
    3、GPIO：  
				I2S2:            I2S3:
                WS  -- PC6 <--> WS  -- PC2
                SCK -- PC7 <--> SCK -- PC3
                SD  -- PC9 <--> SD  -- PC1 

    4、DMA：I2S2 接收采用 DMA1_CH4 通道，I2S3 发送采用 DMA2_CH2 通道；

    5、测试步骤与现象
   	1、编译后下载程序复位运行；
    	2、I2S3 通过 DMA2_CH2 发送数据，I2S2 通过 DMA1_CH4 接收数据 ，运行完成后，查看 TransferStatus 状态为 PASSED

4、注意事项
无


1. Function description

    1、I2S sends and receives data through DMA.

2. Use environment

      Software development environment:
        IDE tool: KEIL MDK-ARM 5.34
	       IAR EWARM 8.50.1
    
    Hardware development environment:
        Developed based on the evaluation board N32H497ZGL7_STB

3. Instructions for use
    
    1, clock source: HSI + PLL
    2、System clock frequency:240MHz
    3、GPIO:  
				I2S2:      I2S3:
                WS -- PC6 <--> WS -- PC2
                SCK -- PC7 <--> SCK -- PC3
                SD -- PC9 <--> SD -- PC1 

    4、DMA：I2S2 receives using DMA1_CH4 channel, I2S3 transmits using DMA2_CH2 channel;

    5, test steps and phenomena
   	1. Compile and download the program to reset and run;
    	2. I2S3 sends data through DMA2_CH2, I2S2 receives data through DMA1_CH4, and after the operation is completed, check the status of TransferStatus is PASSED.

4. Attention
No
