1、功能说明

    1、此例程展示了I2C模块使用中断方式与外部EEPROM的通信。

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
    4、I2C1 配置：
		时钟：400KHz
		地址：0xA0（7bit）
		引脚：
			SCL--PB6、SDA--PB7 

    5、测试步骤与现象
        1、检查EEPROM连接
        2、编译下载代码复位运行
        3、从串口看打印信息，验证结果

4、注意事项
    1、此处使用的EEPROM是AT24C02，32个page，每个page 8byte
    2、读写数据时若长度大于一个page，则器件地址会自动回卷

			
1. Function description

    1. This example shows the I2C module communicating with an external EEPROM using the interrupt method.

2. Use environment

     Software development environment:
        IDE tool: KEIL MDK-ARM 5.34
	       IAR EWARM 8.50.1
    
    Hardware development environment:
        Based on full-function board N32H497ZGL7_EVB V1.0 development
        



3. Instructions for use

     1. Clock source: HSI+PLL
     2. System clock frequency:
         240MHz
    3. Print: PA9 - baud rate 115200
    4. I2C1 Configuration:
		Clock: 400KHz
		Address: 0xA0 (7bit)
		Pin:
			SCL--PB6, SDA--PB7 

     5, test steps and phenomena
        1. check the EEPROM connection
        2. compile and download the code, reset and run
        3.  view the print information from the serial port and verify the result

4. Attention
    1. The EEPROM used here is AT24C02, 32 pages, 8 bytes per page
    2. When reading and writing data, if the length is greater than one page, the device address will be automatically rolled back

			