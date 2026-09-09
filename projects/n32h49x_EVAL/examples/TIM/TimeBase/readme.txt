1、功能说明
    1、GTIM2 利用CH1 CH2 CH3 CH4 CC值产生定时中断，翻转IO电平
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
            GTIM2 比较中断打开
        4、端口配置：
            PC6选择为IO输出
            PC7选择为IO输出
            PC8选择为IO输出
            PC9选择为IO输出
        5、TIM：
            GTIM2输出冻结模式，CH1 CH2 CH3 CH4比较值产生中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察PC6、PC7、PC8、PC9的波形
        2、程序运行后，对应通道达到比较值后，比较值累加并翻转对应IO口电平
4、注意事项
无
    

1. Function description
    1. GTIM2 uses the CH1 CH2 CH3 CH4 CC value to generate a timing interrupt and flip the IO level
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
            GTIM2 compare interrupt is turned on
        4. Port configuration:
            PC6 is selected as IO output
            PC7 is selected as IO output
            PC8 is selected as IO output
            PC9 is selected as IO output
        5. TIM:
            GTIM2 output freeze mode, CH1 CH2 CH3 CH4 compare value interrupt
    Instructions:
        1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the waveforms of PC6, PC7, PC8, and PC9
        2. After the program runs, after the corresponding channel reaches the comparison value, the comparison value accumulates and flips the corresponding IO port level
4. Attention
None
