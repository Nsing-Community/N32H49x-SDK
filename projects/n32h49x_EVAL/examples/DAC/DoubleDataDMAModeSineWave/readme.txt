1、功能说明
    1、GTIM1周期触发DAC1,DMA搬运正弦波数据到DAC1，在PA4输出正弦波形
    
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
            PA4选择为模拟功能DAC1_OUT
        4、GTIM1：
            GTIM1 更新事件作为触发输出给DAC1
        5、DAC配置：
            DAC选择GTIM1 TRGO信号触发，使能DAC1 DMA和DMA的双数据模式，开启DAC1
        6、DMA：
            DMA1_CH1通道回环模式搬运16个字的Sine32bit[16]数组到DAC1的数据保持寄存器

    使用方法：
        1、编译后打开调试模式，利用示波器观察PA4输出波形
        2、全速运行时，可看到PA4输出正弦波形
4、注意事项
    无


1. Function description
    1. GTIM1 cycle triggers DAC1, using DMA transfer sine wave data to DAC1, and output sine wave in PA4 pin.

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
            PA4 is selected as the analog function DAC1_OUT
        4. GTIM1:
            GTIM1 update event as trigger output to DAC1
        5. DAC1:
            The DAC selects the GTIM1 TRGO signal to trigger, enables the DAC1 DMA and double data DMA mode, turns on DAC1.
        6. DMA:
            DMA1_CH1 channel loopback mode transfers 16-word Sine32bit[32] array to DAC1 data hold register
    
    Usage:
        1. Open the debug mode after compiling, and use the oscilloscope to observe the output waveform of PA4 ;
        2. When running at full speed, you can see the output sine waveform of PA4 .
    
4. Matters needing attention
    none
    
