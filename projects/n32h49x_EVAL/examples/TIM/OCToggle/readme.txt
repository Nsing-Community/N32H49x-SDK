1、功能说明
    1、GTIM1 CH1 CH2 CH3 CH4 达到CC值后输出翻转，并且比较值累加   
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
            GTIM1 比较中断打开
        4、端口配置：
            PA5选择为GTIM1的CH1输出
            PA1选择为GTIM1的CH2输出
            PA2选择为GTIM1的CH3输出
            PA3选择为GTIM1的CH4输出
        5、TIM：
            GTIM1 配置好CH1 CH2 CH3 CH4的比较值输出翻转，并打开比较中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察GTIM1 的CH1 CH2 CH3 CH4的波形
        2、每当达到比较值时，输出翻转，并且再增加同样的比较值，波形占空比为50%
4、注意事项
无
    

1. Function description
    1. When GTIM1 CH1 CH2 CH3 CH4 reaches the CC value, the output is reversed, and the comparison value is accumulated
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
            GTIM1 compare interrupt is turned on
        4. Port configuration:
            PA5 is selected as the CH1 output of GTIM1
            PA1 is selected as the CH2 output of GTIM1
            PA2 is selected as the CH3 output of GTIM1
            PA3 is selected as the CH4 output of GTIM1
        5. TIM:
            GTIM1 configures the comparison value output of CH1, CH2, CH3, CH4, and turns on the comparison interrupt
    Instructions:
        1. After compiling, turn on the debug mode and use an oscilloscope or logic analyzer to observe the waveform of CH1 CH2 CH3 CH4 of GTIM1
        2. Whenever the comparison value is reached, the output is reversed, and the same comparison value is increased again, and the waveform duty cycle is 50%
4. Attention
None
