1、功能说明
    1、ATIM1 利用更新中断，产生定时翻转IO
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
        3、中断：
            ATIM1 更新中断打开
        4、端口配置：
            PC6选择为IO输出
        5、TIM：
            ATIM1使能周期中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察PC6的波形
        2、程序运行后，ATIM1的周期中断来临翻转PC6电平
4、注意事项
无
    

1. Function description
     1. ATIM1 uses the update interrupt to generate timing rollover IO
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
        3. Interruption:
            ATIM1 update interrupt is turned on
        4. Port configuration:
            PC6 is selected as IO output
        5. TIM:
            ATIM1 enables periodic interrupts
    Instructions:
        1. After compiling, turn on the debug mode and observe the waveform of PC6 with an oscilloscope or logic analyzer
        2. After the program runs, the periodic interrupt of ATIM1 comes to flip the PC6 level
4. Attention
None
