1、功能说明
    1、GTIM1 CH1 CH2 CH3 CH4 达到CC值后，输出ACTIVE电平   
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
            PA5选择为GTIM1的CH1输出
            PA1选择为GTIM1的CH2输出
            PA2选择为GTIM1的CH3输出
            PA3选择为GTIM1的CH4输出
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察GTIM1 CH1 CH2 CH3 CH4的波形
        2、定时器运行到CC1 CC2 CC3 CC4之后，对应通道的输出变为Active
4、注意事项
无
    

1. Function description
     1. After GTIM1 CH1 CH2 CH3 CH4 reaches the CC value, it outputs ACTIVE level
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
            PA5 is selected as the CH1 output of GTIM1
            PA1 is selected as the CH2 output of GTIM1
            PA2 is selected as the CH3 output of GTIM1
            PA3 is selected as the CH4 output of GTIM1
    Instructions:
        1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveform of GTIM1 CH1 CH2 CH3 CH4
        2. After the timer runs to CC1 CC2 CC3 CC4, the output of the corresponding channel becomes Active
4. Attention
None
