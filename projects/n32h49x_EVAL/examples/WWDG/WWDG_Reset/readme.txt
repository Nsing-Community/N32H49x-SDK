1、功能说明
    1、WWDG复位功能。
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
        3、指示灯：PA3(LED1)   PA8(LED3)
             
    测试步骤与现象：
        1、在KEIL下编译后烧录到评估板，上电后，指示灯LED3不停的闪烁。说明窗口值刷新正常，代码正常运行。
        2、当把systick_delay_ms()函数参数改成小于或者大于窗口时间时，整个系统将一直处于复位状态。LED1亮。
4、注意事项
    1、当窗口值很小时，系统处于频繁的复位状态，此时，容易引起程序无法正常下载。本例程中在开启WWDG前加了1秒延时来避免这个现象。当然也可以不用延时，直接将BOOT0引脚拉高即可正常下载。 
    

1. Function description
     WWDG reset function.
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
        3. light Indicator: PA3(LED1)   PA8(LED2)

    Test steps and phenomenon：
       1. Compile and download the code to reset and run, the indicator LED2 keeps flashing.
          It means that the window value is refreshed normally and the code is running normally.
       2. When the parameter of the systick_delay_ms() function is changed less than or greater than window time, 
          the entire system will always be in the reset state. LED1 is on.

4. Matters needing attention
    1. When the window value is very small, the system is in a frequent reset state, and at this time, it is easy to 
       cause the program to fail to download normally. In this routine, 1s delay is added before WWDG is 
       turned on to avoid this phenomenon. Of course, without delay, you can directly pull up the BOOT0 pin to download normally.