1、功能说明
    1、加密算法库API使用示例
    2、demo展示了SM4、AES128/192/256、DES/2KEY3DES/3KEY3DES 、HASH、SM3、MD5、随机数的算法调用流程

2、使用环境
    软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发

3、使用说明
 
     系统配置
     1、时钟源：HSI+PLL
     2、系统时钟频率：
           240MHz
     3、算法库不支持240M主频，需要对系统时钟2分频，配置为120M
     4、打印：PA9 - baud rate 115200

    使用方法：
        1、在KEIL下编译后烧录到开发板，通电
        2、通过串口输出运行信息
        3、算法执行成功，打印出相应算法测试success，并返回0，算法执行失败，打印相应算法测试fail，并返回0x5A5A5A5A
               
4、注意事项
    无

1. Function description

     1. Encryption algorithm library API usage example
     2. This demo demonstrates the algorithm calling process for SM4, AES128/192/256 DES/2KEY3DES/3KEY3DES, HASH, SM3, MD5, and random

2. Use environment
    Software development environment: 
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0



3. Instructions for use
    
     System Configuration:
      1. Clock source: HSI+PLL
      2. System Clock frequency: 
            240MHz
      3、The algorithm library does not support 240M main frequency, so the system clock needs to be            divided by 2 and configured to 120M.
      4. printf: PA9 - baud rate 115200

     Instructions:
         1. Compile under KEIL and burn to the development board, then power on
         2. Output running information through serial port
         3. Algorithm execution successful, print out the corresponding algorithm test success and return 0, algorithm execution failed, print the corresponding algorithm test 
fail and return  0x5A5A5A5A

4. Matters needing attention
     None