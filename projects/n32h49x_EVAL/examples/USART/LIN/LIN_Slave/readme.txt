1、功能说明

    该演示显示了USART模块LIN模式作为主节点轮询发送主请求帧（0x3C）和从应答帧（0x3D）。

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    
    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发
        

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
    系统时钟配置：240MHz
            
    打印串口配置：
      USART：TX - PA9，RX - PA10，波特率115200
    
    - LIN mode master     LIN mode slave
    - UART5_Tx.PG2  <-->  UART5_Rx.PA5  
    - UART5_Rx.PG3  <-->  UART5_Tx.PA4  
       
       Master_LIN.LIN与Slave_LIN.LIN连接，两板公地。

    
    测试步骤与现象：
    a、 跳线连接到主机的从属引脚
    b、 一个开发板编译并下载LIN_Master代码作为主代码
         另一个开发板编译并下载LIN_Slave代码作为从属代码
    c、 重置从设备，然后重置主设备
   d、 主轮询发送请求帧（0x3C）和应答帧（0x3D）
         发送请求帧（0x3C）：主设备向从设备发送一个8字节的0x0F，并打印相关信息
         发送应答帧（0x3D）：从机收到应答帧后，向主机回复8字节0x01消息，并且主控打印相关信息


4、注意事项




1. Function description

    This demo shows that the USART module LIN mode as the master node polling to send the master
     request frame (0x3C) and the slave reply frame (0x3D).


2. Use environment

    Software development environment: 
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1
    Hardware development environment:
        Developed based on the evaluation board N32H497ZGL7_EVB V1.0
        

3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
    System Clock Configuration:240MHz
    
    The USART configuration is as follows:
    -Baud rate = 9600baud
    -Word length = 8 data bits
    -1 stop bit
    -Parity control disabled
    -Hardware flow control disabled (RTS and CTS signals)
    -Receiver and transmitter enable
    -LIN mode enable

    Print Serial Port Configuration:
      USART:TX - PA9:RX - PA10, baud rate 115200
    
    - LIN mode master     LIN mode slave
    - UART5_Tx.PG2  <-->  UART5_Rx.PA5  
    - UART5_Rx.PG3  <-->  UART5_Tx.PA4  
       
       Master_LIN.LIN is connected to Slave_LIN.LIN with common ground for both boards.

    Test steps and phenomena:
    a, the jumper connects to the slave pin of the master
    b, one development board compiles and downloads LIN_Master code as the master and 
        the other development board compiles and downloads LIN_Slave code as the slave
    c, Reset the slave and then the master
    d, master polling sends request frame (0x3C) and reply frame (0x3D)
       Sending request frame (0x3C) : The master sends an 8-byte 0x0F to the slave and prints the related information
       Sending reply frame (0x3D) : After receiving a reply frame, the slave reply an 8-byte 0x01 message to the master, 
        and the master prints the related information

4. Attention
    none