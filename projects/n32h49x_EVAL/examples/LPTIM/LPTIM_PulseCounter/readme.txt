1、功能说明
    LPTIM1 计数IN1的上升沿个数
2、使用环境
    软件开发环境：KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1
    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发
3、使用说明
    系统配置:
        1、时钟源：HSI+PLL
        2、时钟频率：
            240MHz
        3、LPTIM CLK：LSI
        4、打印：PA9 - baud rate 115200

    端口配置：
        PC0选择为LPTIM1 IN1输入
        PB0选择为IO输出

    LPTIM配置：
        LPTIM1外部计数模式，利用内部LSI时钟连续计数IN1上升沿个数

    使用方法：
        1、连接PB0和PC0
        2、编译后下载程序运行，PB0输出10个脉冲周期，若tempCNT等于10，则系统运行正常，并打印“LPTIM_PulseCounter demo success!!!”，否则，打印“LPTIM_PulseCounter demo failed!!!”

4、注意事项
无
    

1. Function description
    LPTIM1 Counts the number of rising edges of IN1
2. Use environment
    Software development environment: KEIL MDK-ARM 5.34
                                      IAR EWARM 8.50.1
    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0
3. Instructions for use
    System Configuration;
        1. Clock source: HSI+PLL
        2. Clock frequency: 
            240MHz
        3, LPTIM CLK: LSI
        4, Printing: PA9 - baud rate 115200

    Port Configuration:
        PC0 selected for LPTIM1 IN1 input
        PB0 selected for IO output

    LPTIM Configuration:
        LPTIM1 external counting mode, utilizing the internal LSI clock to continuously count the number of IN1 rising edges.

    Usage:
        1, Connect PB0 and PC0.
        2, Compile and download the program to run, PB0 output 10 pulse cycles, if tempCNT is equal to 10, then the system is running normally, and print "LPTIM_PulseCounter demo success!!!". Otherwise, print "LPTIM_PulseCounter demo failed!!!".

4. Matters needing attention
None
