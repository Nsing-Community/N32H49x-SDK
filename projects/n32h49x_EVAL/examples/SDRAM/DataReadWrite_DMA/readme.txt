1、功能说明
    此例程展示了与外部SDRAM通过DMA方式通信

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34
                  IAR EWARM 8.50.1 

    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发

3、使用说明
    系统配置；
        1、时钟源： HSI+PLL
        
        2、系统时钟频率：
            240MHz 
            
        3、SDRAM配置：
            M12L64164A：
            A0->PF0,        A1->PF1,        A2->PF2,       A3->PF3,        A4->PF4,        A5->PF5,      
            A6->PF12,      A7->PF13,       A8->PF14,     A9->PF15,     A10->PG0,     A11->PG1,  
            D0->PD14,     D1->PD15,     D2->PD0,       D3->PD1,      D4->PE7,       D5->PE8,       D6->PE9,      D7->PE10, 
            D8->PE11,     D9->PA5,        D10->PE13,    D11->PE14,   D12->PC0,     D13->PD8,     D14->PD9,   D15->PD10, 
            BA0->PG4,    BA0->PG5,    NCE0->PC2,   NWE->PC0,    NRAS->PF11,        NCAS->PG15, 
            DQM0->PE0,  DQM1->PE1,   CKE0->PC3,    CLK->PG10  
           
            SDRAM CLK: 80MHz
            
        4、USART1配置：
            TX  -->  PA9       
            波特率：115200
    
        5、测试使用SDRAM型号:
           M12L64164A（容量1Mx16Bitx4Bank, 4096ROWx256COL）

    使用方法：
        a，编译下载代码复位运行
        b，从串口看打印信息，验证结果，若读取数据与写入数据一致则打印通过
        
4、注意事项
    无
    
1. Function description
    This example demonstrates the communication with the external SDRAM via DMA

2. Development environment

    Software development environment: KEIL MDK-ARM V5.34
                  IAR EWARM 8.50.1 

    Hardware development environment:
        Based on full-function board N32H497ZGL7_EVB V1.0 development

3. How to use
   System Configuration:
        1. Clock source: HSI+PLL
        
        2. System Clock frequency: 
            240MHz 
            
        3. SDRAM configuration:
           M12L64164A：
            A0->PF0,        A1->PF1,        A2->PF2,       A3->PF3,        A4->PF4,        A5->PF5,      
            A6->PF12,      A7->PF13,       A8->PF14,     A9->PF15,     A10->PG0,     A11->PG1,  
            D0->PD14,     D1->PD15,     D2->PD0,       D3->PD1,      D4->PE7,       D5->PE8,       D6->PE9,      D7->PE10, 
            D8->PE11,     D9->PA5,        D10->PE13,    D11->PE14,   D12->PC0,     D13->PD8,     D14->PD9,   D15->PD10, 
            BA0->PG4,    BA0->PG5,    NCE0->PC2,   NWE->PC0,    NRAS->PF11,        NCAS->PG15, 
            DQM0->PE0,  DQM1->PE1,   CKE0->PC3,    CLK->PG10  

            SDRAM CLK: 80MHz
            
        4. USART1 configuration:
             TX --> PA9
             Baud rate: 115200
    
        5. Test using SDRAM model:
            M12L164164A（capacity 1Mx16Bitx4Bank, 4096ROWx256COL）
        
     Test steps:
         a, compile and download the code, reset and run
         b, view the print information from the serial port and verify the result, If the read data is the same as the written data, the print passes.


4. Attention
    None

