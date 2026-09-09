1、功能说明
    1、通过调节模拟看门狗的阈值来模拟comp的迟滞以及电平检测的功能
    
2、使用环境
    软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    硬件开发环境：
        基于评估板N32H497VEL7_STB V1.0开发
        
3、使用说明
    系统配置；
        1、时钟源： HSI+PLL
        2、系统时钟频率：
           SystemClock：240MHz
        3、中断：
            ADC1注入转换结果完成中断打开，抢断优先级0，子优先级0
        4、端口配置：
            PB0选择为模拟功能
            PB1选择为模拟功能
            PB2选择为通用IO推挽输出
            PB3选择为通用IO推挽输出
        5、ADC：
            ADC1独立工作模式、多通道模式，软件触发、12位数据右对齐，规则转换通道PB0,PB1的模拟电压数据

    使用方法：
        1、编译下载代码到芯片，全速运行；
        2、当PB0输入信号超过(1.25-0.03)V时，PB2会反转一次电平， 当PB1输入信号超过(1.25-0.03)V时，PB3会反转一次电平；
        
4、注意事项
    当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8)可以配置为HSE或者HSI
    当系统采用HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8)只能配置为HSI


1. Function description
    1. Simulate the hysteresis of the comparator and the function of level detection by adjusting the threshold of the analog watchdog.

2. Use environment
    Software development environment: 
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the evaluation board N32H497VEL7_STB V1.0
        
3. Instructions for use
    System Configuration; 
        1. Clock source: HSI+PLL
        2. System Clock frequency: 
           SystemClock：240MHz
        3. Interrupt:
            The ADC1 injected conversion result completion interrupt is enabled, with a preemption priority of 0 and a sub-priority of 0.
        4. Port configuration:
            PB0 is set to analog function.
            PB1 is set to analog function.
            PB2 is set to general-purpose IO push-pull output.
            PB3 is set to general-purpose IO push-pull output.
        5. ADC:
            ADC1 works in independent mode and multi-channel mode, with software triggering, 12-bit data right-aligned, and regular conversion channels for analog voltage data of PB0 and PB1.

    Instructions:
        1. Usage method:Compile and download the code to the chip, then run at full speed.
        2. When the input signal of PB0 exceeds (1.25 - 0.03)V, the level of PB2 will toggle once; when the input signal of PB1 exceeds (1.25 - 0.03)V, the level of PB3 will toggle once.
4. Attention
    When the system uses HSE clock (generally HSI is also turned on), RCC_ConfigAdc1mClk (RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8) can be configured as HSE or HSI
    When the system uses HSI clock (generally HSE is turned off), RCC_ConfigAdc1mClk (RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8) can only be configured as HSI