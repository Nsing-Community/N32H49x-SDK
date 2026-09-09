1、功能说明
    1、软件触发DAC1输出4094的电平信号，噪声幅度为1
    
2、使用环境

    软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发
        
3、使用说明
    系统配置；
        1、时钟源： HSI+PLL
        2、系统时钟频率：
           SystemClock：240MHz
        3、端口配置：
            PA4选择为模拟功能
        4、DAC配置：
            DAC选择软件触发，DAC1幅值为4094，开启噪声模式，噪声幅值为1
        5、主循环：
            一直触发DAC1输出

    使用方法：
        1、编译后打开调试模式，利用示波器观察PA4输出波形
        2、全速运行时，可看到PA4输出大约3.3V电平
4、注意事项
    无


1. Function description
    1. Software triggers DAC1 to output 4094 level signal, and the noise amplitude is 1

2. Use environment

    Software development environment: 
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0
        
3. Instructions for use
    System Configuration; 
        1. Clock source: HSI+PLL
        2. System Clock frequency: 
           SystemClock：240MHz
        3. Port Configuration:
            PA4 is selected as the analog function 
        4. DAC:
            DAC select software trigger, DAC1 amplitude is 4094, open noise mode, noise amplitude is 1
        5. Main loop:
            Always trigger DAC1 output
    Usage:
        1. Open the debug mode after compiling, and use the oscilloscope to observe the output waveform of the PA4
        2. When running at full speed, you can see that the PA4 output is about 3.3V level
4. Matters needing attention
    none
    
