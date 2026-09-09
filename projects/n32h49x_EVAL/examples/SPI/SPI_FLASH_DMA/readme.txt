1、功能说明

    1、SPI DMA 读、写 W25Q128 数据

2、使用环境

     软件开发环境：
        IDE工具：KEIL MDK-ARM 5.34
	       IAR EWARM 8.50.1
    
    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发

3、使用说明：
    1、时钟源：HSI+PLL
    2、系统时钟频率：240MHz
    3、SPI配置：
          SPI3配置：NSS--PA15、SCK--PB3、MISO--PD11、MOSI--PD12
    4、USART配置：
          TX--PA9,115200,8bit data,1bit stop

   5、测试步骤与现象
    1、编译后下载程序复位运行；
    2、通过 SPI1 读取 W25Q128 的 ID，然后通过 DMA 写数据，再通过 DMA 读出来，比较读写数据，
         查看 TransferStatus1 状态为 PASSED，然后擦除块，检查擦除块正常。
    3、通过串口工具查看结果

4、注意事项
    1、只在大批量读写数据时使用 DMA，刚开始因为涉及到一些写命令，所以配置成全双工，在全双工模式下，读取 Flash 需要一直发送 0xFF，这样会限制 DMA 性能，
     所以在用 DMA 读取数据时，设置 SPI 为只读模式，这样在读取数据时不需要一直发送 0xFF，以此来提升性能。
     2、需要连接跳线帽J20



1. Function description

    1. SPI DMA read and write W25Q128 data

2. Use environment

    Software development environment: 
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1
    
    Hardware development environment:
        Developed based on the evaluation board N32H497ZGL7_EVB V1.0


3. Instructions for use
  
     1. Clock source: HSI+PLL
     2. System clock frequency:240MHz
    3、SPI configuration:
          SPI3 configuration: NSS--PA15、SCK--PB3、MISO--PD11、MOSI--PD12
    4、USART configuration:
          TX--PA9,115200,8bit data,1bit stop

     5. Instructions:
    a. After compiling, download the program to reset and run;
    b. Read the ID of W25Q128 through SPI1, then write the data through DMA, and then read it out through DMA,
       compare the read and write data, check that the status of TransferStatus1 is PASSED, then erase the block,
       and check that the erase block is normal.
    c. View the results through the serial port tool

4. Attention
    1. Only use DMA when reading and writing data in large batches. At the beginning, because some write commands are involved,
    it is configured as full-duplex. In full-duplex mode, 0xFF needs to be sent all the time to read Flash, 
    which will limit the DMA performance. When DMA reads data, set SPI to read-only mode,
    so that 0xFF does not need to be sent all the time when reading data, so as to improve performance.
    2. Jumpers J20 must be connected.
