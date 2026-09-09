1、功能说明
    1、通过FEMC将图片数据传输给LCD显示
    
2、使用环境
    软件开发环境：KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1
    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发

        基于TFT_LCD(320*240 驱动：ILI9341/800*480 或 驱动：ILI9806G)

3、使用说明
    系统配置；
        1、FEMC时钟源：AHB
        3、端口配置：
            LCD 端口:
                CS:PG12      RS:PD13      WR:PD5      RD:PD4      
                RST:PH5
                D0:PD14     D1:PD15     D2:PD0      D3:PD1      
                D4:PE7      D5:PE8      D6:PE9      D7:PE10     
                D8:PE11     D9:PE12     D10:PE13    D11:PE14    
                D12:PE15    D13:PD8     D14:PD9     D15:PD10
            LCD背光控制端口：PB5
            
    使用方法：
    1、编译并下载代码运行，LCD上显示LOG界面
    
4、注意事项



1. Function description
    1. FEMC transmits picture data to LCD display

2. Use environment
    Software development environment: KEIL MDK-ARM 5.34
                                      IAR EWARM 8.50.1
 
    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0

        Based on TFT_LCD(320*240 Driver: ILI9341/800*480 or Driver：ILI9806G)

3. Instructions for use
    System Configuration;
        1. FEMC clock source: AHB
        2. Port Configuration:
            LCD port:
                CS:PG12      RS:PD13      WR:PD5      RD:PD4      
                RST:PH5
                D0:PD14     D1:PD15     D2:PD0      D3:PD1      
                D4:PE7      D5:PE8      D6:PE9      D7:PE10     
                D8:PE11     D9:PE12     D10:PE13    D11:PE14    
                D12:PE15    D13:PD8     D14:PD9     D15:PD10
            LCD backlight control port：PB5
    Instructions:
        1、Compile and download the code to run, the LOG figure is displayed on the LCD.
        
4. Matters needing attention

    
