1、功能说明
    1、IWDG复位功能。
2、使用环境
    软件开发环境：KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1
    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发
3、使用说明
    系统配置:
        1、IWDG时钟源：LSI/128
        2、超时时间值：250ms
        3、指示灯：LED1(PA3) LED3(PA8)   
    测试步骤及现象：
        1、编译后烧录到评估板，上电后，指示灯LED2不停的闪烁。说明IWDG正常喂狗，代码正常运行。
        2、把SysTick_Delay_Ms(249)函数参数改成251以上，整个系统将一直处于复位状态，LED1亮。
4、注意事项
无    

1. Function description
     IWDG reset function.
2. Use environment
    Software development environment: KEIL MDK-ARM 5.34
                                      IAR EWARM 8.50.1
    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0
3. Instructions for use
    System Configuration;
        1. IWDG clock source: LSI/128
        2. Timeout value: 250ms
        3. light Indicator: LED1(PA3) LED3(PA8)

    Test steps and phenomenon：
        1. Compile and download the code to reset and run.The indicator LED3 
          keeps flashing. It means that IWDG feeds the dog normally and the code runs normally.
        2. Change the parameter of the SysTick_Delay_Ms() function from 249 to 251 or more, the whole system
          will always be in the reset state, and LED1 will be on.
4. Matters needing attention
    None