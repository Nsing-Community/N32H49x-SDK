1、功能说明
    1、ATIM1 CH2门控CH1和GTIM5, GTIM5门控GTIM6    
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
        3、端口配置：
            PA8选择为ATIM1 CH1输出
            PA9选择为ATIM1 CH2输入
            PA2选择为GTIM5 CH1输出
            PD5选择为GTIM6 CH1输出    
        4、TIM：
            ATIM1 CH2门控CH1和GTIM5, GTIM5门控GTIM6
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察ATIM1 CH1,GTIM5 CH1,GTIM6 CH1的波形
        2、ATIM1 CH2高电平定时器开始计数，低电平停止
4、注意事项
     默认情况下，开发板的PA9和PA10跳线帽连接到NSLINK的虚拟串行端口。如果PA9和PA10未用作项目中的串行端口，而是用于其他用途，则必须拔掉串行端口跳线帽。
   

1. Function description
     1. ATIM1 CH2 gated CH1 and GTIM5, GTIM5 gated GTIM6
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
        3. Port configuration:
            PA8 is selected as ATIM1 CH1 output
            PA9 is selected as ATIM1 CH2 output
            PA2 is selected as GTIM5 CH1 output
            PD5 is selected as GTIM6 CH1 output
        4. TIM:
             ATIM1 CH2 gated CH1 and GTIM5, GTIM5 gated GTIM6
    Instructions:
         1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveforms of ATIM1 CH1, GTIM5 CH1, GTIM6 CH1
         2. ATIM1 CH2 high level timer starts counting, low level stops
4. Attention
        By default, the PA9 and PA10 jumper caps of the development board are connected to the virtual serial port of NSLINK. If PA9 and PA10 are not used as serial ports in the project, and are used for other purposes, the serial port jumper caps must be unplugged.

