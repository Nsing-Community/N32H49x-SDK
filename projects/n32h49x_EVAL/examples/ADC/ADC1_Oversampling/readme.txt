1、功能说明
    1、ADC1开启过采样的条件下进行采样、转换PB0,PB1引脚的模拟电压
    2、其中ADC1转换结果通过DMA1_CH1通道读取到变量ADCConvertedValue[10]
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
            PB11选择为模拟功能
            PB1选择为模拟功能
        4、DMA：
            DMA1_CH1通道回环模式搬运一个半字的ADC1转换结果到ADCConvertedValue[10]变量
        5、ADC：
        ADC1独立工作模式、连续转换、扫描模式、软件触发、12位数据右对齐，转换PB0,PB1的模拟电压数据 ,过采样系数x2 无右移,在规则通道上使用过采样连续模式.
    使用方法：
        1、编译后打开调试模式，将变量ADCConvertedValue[10]添加到watch窗口观察
        2、通过改变PB0,PB1引脚的电压Voltage，可以看到转换结果变量同步改变，数据寄存器的结果Result = Voltage * 2* 4095/3.3. 
4、注意事项
    当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8)可以配置为HSE或者HSI
    当系统采用HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8)只能配置为HSI

1. Function description
    1. ADC1 performs sampling with gain compensation and offset compensation enabled ,converts the analog voltage of the PB0,PB1 pin
    2. The ADC1 conversion result is read to the variable ADCConvertedValue through the DMA1_CH1 channel
    
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
        3. Port configuration:
            PB0 selected as analog function
            PB1 selected as analog function
        4. DMA:
            DMA1_CH1 channel loopback mode transfers a halfword of ADC1 conversion result to ADCConvertedValue[10] variable
        5. ADC:
            ADC1 independent working mode, continuous conversion, scan mode, software trigger, 12-bit data is right-aligned,
            conversion the analog voltage data of PB11 PB1,The oversampling factor x2 , no right shift and the oversampling continuous mode on the regular channel .
    Instructions:
        1. After compiling, open the debug mode and add the variable ADCConvertedValue[10] to the watch window to observe
        2. By changing the voltage (Voltage) of the PB0,PB1 pin, you can see that the conversion result variable changes synchronously . the data register result = Voltage * 2 * 4095/3.3.
4. Attention
    When the system uses HSE clock (generally HSI is also turned on), RCC_ConfigAdc1mClk (RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8) can be configured as HSE or HSI
    When the system uses HSI clock (generally HSE is turned off), RCC_ConfigAdc1mClk (RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8) can only be configured as HSI