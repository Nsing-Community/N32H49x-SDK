1、功能说明
    LPTIM1输出PWM波形
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
        PC1选择为LPTIM1输出

    LPTIM配置：
        LPTIM1 1分频LSI，输出PWM波形

    使用方法：
        1、编译后下载程序运行，可通过示波器或逻辑分析仪观察PC1输出的PWM波形

4、注意事项
无
    

1. Function description
    LPTIM1 output PWM waveforms
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
        PC1 selected for LPTIM1 output

    LPTIM Configuration:
        LPTIM1 1-division LSI, output PWM waveforms

    Usage:
        1, Compile and download the program to run, the PWM waveform output from PC1 can be observed by an oscilloscope or logic analyzer.

4. Matters needing attention
None
