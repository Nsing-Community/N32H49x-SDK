1、功能说明
    1、通过设定唤醒时间触发中断。
    2、通过唤醒标志位来配置IO输出

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34
                  IAR EWARM 8.50.1
				  
    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发


3、使用说明
    
    系统配置:
        1、周期性唤醒时钟源：RTCCLK（1HZ）
        2、唤醒输出口：PC13
        3、串口配置：
                    - 串口为USART1（TX：PA9  RX：PA10）:
                    - 数据位：8
                    - 停止位：1
                    - 奇偶校验：无
                    - 波特率： 115200 
    使用方法：
        1、编译后烧录到评估板，上电后，串口每隔5s会打印唤醒时间
                
4、注意事项
    无


1. Function description

    1. Trigger interrupt by setting wake up time
    2. Configure IO output by wake up flag bit

2. Use environment

    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1
									  
    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0

3. Instructions for use

    System configuration:

        1. periodic wake up clock source: RTCCLK (1HZ)
        2. Wakeup IO output: PC13
        3. Serial port configuration:

                            - Serial port: USART1 (TX: PA9 RX: PA10) :
                            - Data bit: 8
                            - Stop bit: 1
                            - Parity check: None
                            - Baud rate: 115200

    Instructions:
        1. After compilation, it is burned to the evaluation board. After power-on, the serial port will print wakeup time every 5s

4. Attention
    None
