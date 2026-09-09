1、功能说明
    1、ADC1采样转换内部VREFINT的模拟电压（1.2V）
    2、采用软件触发一次，采集一次的方式
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
        3、ADC：
            ADC1独立工作模式、软件触发转换、12位数据右对齐，转换VREFINT的模拟电压数据

    使用方法：
        1、编译后打开调试模式，将变量ADC1ConvertedValue添加到watch窗口观察.
        2、以2.5V的VREFBUF输出作为ADC1的参考电压,经过ADC1采样转换后,换算得到VREFINT约为1.2V.
4、注意事项
    

1. Function description
    1. ADC1 samples and converts the analog voltage of internal VREFINT (1.2V).
    2. The software triggers once and collects once
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
        3.ADC:
            ADC1 independent working mode, software-triggered conversion, 12-bit data is right-aligned, and analog voltage data of VREFINT is converted
            
    Instructions:
        1. Open the debug mode after compiling, add the variables ADC1ConvertedValue to the watch window for observation
        2. The VREFBUF output of 2.5V is used as the reference voltage for ADC1. After sampling and conversion by ADC1, the VREFINT is approximately 1.2V.
4. Matters needing attention
