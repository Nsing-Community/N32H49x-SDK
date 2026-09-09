1、功能说明

    1、此例程展示了I2C模块作从设备通过FIFO的读写操作。   

2、使用环境

    软件开发环境：
        IDE工具：KEIL MDK-ARM 5.34
	       IAR EWARM 8.50.1
    
    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发
        


3、使用说明
    
    1、时钟源：HSI+PLL
    2、系统时钟频率：
        240MHz
        
   3、打印：PA9 - baud rate 115200
    4、I2Cx 配置：
		时钟：100KHz
		地址：0x10（7bit）
		引脚：
			SCL--PB6、SDA--PB7 

    5、测试步骤与现象
        1、连接I2C主设备
        2、编译下载代码复位运行
        3、从串口看打印信息，验证结果

4、注意事项
无 

1. Function description

    1, this routine shows the I2C module as a slave device through the FIFO read and write operations.   

2. Use environment

    Software development environment:
        IDE tool: KEIL MDK-ARM 5.34
	       IAR EWARM 8.50.1
    
    Hardware development environment:
        Based on full-function board N32H497ZGL7_EVB V1.0 development
        


3. Instructions for use
    
    System configuration:
    1, clock source: HSI + PLL
    2, system clock frequency:
        240MHz

    3、Printing: PA9 - baud rate 115200
    4、I2Cx Configuration:
		Clock: 100KHz
		Address: 0x10 (7bit)
		Pinout:
			SCL--PB6, SDA--PB7 

    5, test steps and phenomena
        1, connect the I2C master device
        2, compile and download the code reset run
        3, from the serial port to see the print information to verify the results

4. Attention
No 
