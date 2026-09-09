1、功能说明
   ATIM1触发DAC1生成锯齿波,复位值0x100,步进60.
    
2、使用环境
    软件开发环境：
        IDE工具:  KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1

    硬件环境：      
        基于全功能板N32H497ZGL7_EVB V1.0开发
        
3、使用说明
    系统配置；
        1、时钟源： HSI+PLL
        2、系统时钟频率：
           SystemClock：240MHz
        3、端口配置：
            PA4选择为模拟功能
        4、DAC配置： 
                DAC1选择步进触发源"DAC_Trigger_ATIM1_TRGO"，DAC1复位触发源为"DAC_Trigger2_Software"
                递增锯齿波步进值0x40 复位值0x100.
    使用方法：
        1、编译后打开调试模式，利用示波器观察PA4输出波形
        2、全速运行时，可看到PA4输出递增的锯齿波.
4、注意事项
    无


1. Function description
    ATIM1 triggers DAC1 to generate a sawtooth wave, with a reset value of 0x100 and a step value of 60.

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
                DAC1 selects the step trigger source "DAC_Trigger_ATIM1_TRGO", and the reset trigger source for DAC1 is "DAC_Trigger2_Software".
                The increment sawtooth step value is 0x40 and Reset value is 0x100.
    Usage:
        1. After compiling, open debug mode and observe the output waveform of PA4 using an oscilloscope
        2. When running at full speed, you can see the increasing sawtooth wave output from PA4.
4. Attention
    none
    
