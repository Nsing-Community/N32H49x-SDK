1、功能说明
    1、GTIM2 周期门控GTIM5 GTIM6
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
            PA6选择为GTIM2的CH1输出
            PA2选择为GTIM5的CH1输出
            PD5选择为GTIM6的CH1输出
        4、TIM：
            GTIM2 周期触发门控GTIM5 GTIM6的CH1,即GTIM5为10倍周期GTIM2，即GTIM6为5倍周期GTIM2
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察GTIM2 CH1、GTIM5 CH1、GTIM6 CH1的波形
        2、GTIM6周期5倍于GTIM2，GTIM5周期10倍于GTIM2
4、注意事项
无
    

1. Function description
     1. GTIM2 cycle gated GTIM5 GTIM6
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
            PA6 is selected as CH1 output of GTIM2
            PA2 is selected as the CH1 output of GTIM5
            PD5 is selected as the CH1 output of GTIM6
        4. TIM:
            GTIM2 cycle triggers CH1 of gating GTIM5 GTIM6, that is, GTIM5 is 10 times period GTIM2, that is, GTIM6 is 5 times period GTIM2
    Instructions:
         1. After compiling, turn on the debug mode and use an oscilloscope or logic analyzer to observe the waveforms of GTIM2 CH1, GTIM5 CH1, and GTIM6 CH1
         2. The cycle of GTIM6 is 5 times that of GTIM2, and the cycle of GTIM5 is 10 times that of GTIM2.
4. Attention
None
