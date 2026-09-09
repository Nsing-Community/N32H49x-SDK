1、功能说明
    1、GTIM5 CH2上升沿计算频率   
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
            GTIM5 CH2上升沿中断打开
        4、端口配置：
            PD2选择为GTIM5 CH2输入
            PA3选择为IO 输出
        5、TIM：
            GTIM5 CH2 上升沿捕获中断打开
    使用方法：
        1、编译后打开调试模式，连接PA3与PD2，将变量TIM5Freq添加到watch窗口
        2、通过调试窗口修改gOnePulsEn为1，PA3会有电平翻转
        3、程序控制PA3电平翻转后，查看TIM5Freq计算的频率值
4、注意事项
无
    

1. Function description
     1. GTIM5 CH2 rising edge calculation frequency
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
             GTIM5 CH2 rising edge interrupt is turned on
         4. Port configuration:
             PD2 is selected as GTIM5 CH2 input
             PA3 is selected as IO output
         5. TIM:
             GTIM5 CH2 rising edge capture interrupt is turned on
    Instructions:
         1. After compiling, open the debug mode, connect PA3 and PD2, and add the variable TIM5Freq to the watch window
         2. Modify gOnePulsEn to 1 in the debug mode and flip the PA3 pin level
         3. After the program controls the level of PA3 to flip, check the frequency value calculated by TIM5Freq
4. Attention
None
