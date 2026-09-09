1、功能说明
    以EXTI0为例演示GPIO外部中断功能，分别将PC13/PA15做为EXTI0输入端口。

2、使用环境
    软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发

        
3、使用说明

    系统配置
        1、时钟源：HSI+PLL
        2、系统时钟频率：
            240MHz
        3、GPIO：
            PA3-D1, PB3-D2, PC13-KEY1, PA15-KEY2

        4、打印：PA9 - baud rate 115200

    使用方法：
        1、编译后将程序下载到开发板并复位运行,仅1个LED闪烁。
        2、默认状态下仅KEY1触发EXTI0外部中断，在中断处理中修改EXTI0输入端口为KEY2，之后仅KEY2可触发EXTI0中断。
        3、每次进入EXTI中断，EXTI0输入端口修改一次，按照顺序循环演示：KEY1->KEY2->KEY1->...
        4、EXTI0输入端口不同时，闪烁的LED也不同。
        5、系统启动和EXTI0输入端口发生变化时，串口都有相关提示信息输出。
        

4、注意事项
    无
    
1. Function description

     Uses EXTI0 as an example to shows the GPIO external interrupt function,
     and PC13/PA15 are all partly used as the EXTI0 input port.

2. Use environment

    Software development environment: 
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0


3. Instructions for use

    System Configuration:
        1. Clock source: HSI+PLL
        2. System Clock frequency: 
            240MHz
        3.GPIO:
            PA3-D1, PB3-D2, PC13-KEY1, PA15-KEY2
            
        4. printf: PA9 - baud rate 115200

     Instructions:
        1.  After compiling, download the program and reset, the program start running.
            And a led blink.
        2.  Only KEY1 triggers the EXTI0 external interrupt by default. 
            During interrupt processing, the EXTI0 input port changed to KEY2. 
            After that, only KEY2 can trigger the EXTI0 interrupt.
        3.  Each time the EXTI interrupt is entered, the EXTI0 input port is changed once, 
            and the demonstration is performed in sequence: KEY1->KEY2->KEY1->...
        4.  When the EXTI0 input port is changed, the blinked LED will also changed.
        5.  When the system starts and the EXTI0 input port changes, the serial port will 
            output relevant prompt information.

4. Attention
    None

