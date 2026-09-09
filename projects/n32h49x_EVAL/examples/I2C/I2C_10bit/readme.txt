1、功能说明

    1、此例程展示了I2C模块10bit地址模式下的读写操作。

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
    4、 I2C1配置（主机）：
	时钟：100KHz
	地址：0x230(10bit)
	引脚：
         SCL--PB6、SDA--PB7           

    5、I2C2配置（从机）：
	时钟：100KHz
	地址：0x2A0(10bit)
	引脚：
         SCL--PB10、SDA--PB11        

    6、测试步骤与现象
        1、用杜邦线将与I2C从机连接
        2、编译下载代码复位运行
        3、从串口看打印信息，验证结果

4、注意事项
无 

1. Function description

    1, this routine shows the I2C module 10bit address mode read and write operations.

2. Use environment

      Software development environment:
        IDE tool: KEIL MDK-ARM 5.34
	       IAR EWARM 8.50.1
    
    Hardware development environment:
        Based on full-function board N32H497ZGL7_EVB V1.0 development
 
3. Instructions for use
    
    1, clock source: HSI + PLL
    2、System clock frequency:
        240MHz
    3. Print: PA9 - baud rate 115200
    4、I2C1 configuration(master):
	Clock: 100KHz
	Address: 0x230(10bit)
	Pinout: 
           SCL--PB6, SDA--PB7          

    5、I2C2 Configuration(slave):
	Clock: 100KHz
	Address: 0x2A0(10bit)
	Pinout: 
          SCL--PB10, SDA--PB11         

    6, test steps and phenomena
        1, with the DuPont line will be connected to the I2C slave
        2, compile and download the code reset run
        3, from the serial port to see the print information to verify the results

4. Attention
No