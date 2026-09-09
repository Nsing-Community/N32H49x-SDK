1、功能说明
    此例程展示了FDCAN 节点2如何通过轮询方式接收节点1发送的数据帧。

2、使用环境
    软件开发环境：
        KEIL MDK-ARM 5.34.0.0
        IAR EWARM 8.50.1
                
    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发

3、使用说明

    系统配置
        1、时钟源：HSI+PLL
        2、系统时钟频率：
            240MHz
        3、打印：PA9 - baud rate 115200
        4、节点1:
            FDCAN1:
                TX-PA4，RX-PA5
            时钟源：20MHz
            波特率：250Kbps（仲裁域），500Kbps（数据域）
            工作模式：普通模式
            标称位时序：预分频=2，TSEG1=31，TSEG2=8，同步跳转=8
            数据位时序：预分频=2，TSEG1=15，TSEG2=4，同步跳转=4
            帧格式：FDCAN，BRS ON，16字节数据
            标准接收过滤器：禁用
            扩展接收过滤器：1个，ID掩码过滤（ID=0x0AAAAAAA,掩码=0x1FFFFFFF），存储在RX FIFO0
            接收FIFO：启用FIFO0，大小为2，FIFO1禁用
            接收缓冲：禁用
            发送缓冲：1个
            发送FIFO：禁用
            发送事件FIFO：禁用
            时间戳：内部时间戳，16分频
            中断：TX BUFFER0发送完成中断，中断线1
            其他：拒绝远程帧与非匹配帧
        5、节点2:
            FDCAN2:
                TX-PG2，RX-PG3
            时钟源：20MHz
            波特率：250Kbps（标称），500Kbps（数据）
            工作模式：普通模式
            标称位时序：预分频=2，TSEG1=31，TSEG2=8，同步跳转=8
            数据位时序：预分频=2，TSEG1=15，TSEG2=4，同步跳转=4
            帧格式：FDCAN，BRS ON，16字节数据
            标准接收过滤器：禁用
            扩展接收过滤器：1个，ID掩码过滤（ID=0x15555555,掩码=0x1FFFFFFF），存储在RX FIFO0
            接收FIFO：启用FIFO1，大小为6，FIFO0禁用
            接收缓冲：禁用
            发送缓冲：禁用
            发送FIFO：禁用
            发送事件FIFO：禁用
            时间戳：内部时间戳，16分频
            中断：RX FIFO1水线中断（水线=2），中断线1
            其他：拒绝远程帧与非匹配帧
        6、EXTI
            EXTI Line1，PA15输入，上升沿触发

    使用方法：
        1、编译后将程序下载到开发板并复位运行。
        2、轻按按键，node1发送一个数据帧。
        3、发送完成后，node1发送完成中断后打印相关信息。
        4、连续接收到2个数据帧后，触发node2 RX FIFO1水线中断，输出接收数据。

4、注意事项
    连接跳帽J8/J2/J15/J9，不要连接跳帽J87/J89
    
1. Function description

     This example shows FDCAN node1 and node2 sending and receiving data to each other in classic CAN format.

2. Use environment

    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1

    Hardware development environment:
         Developed based on the full-function board N32H497ZGL7_EVB V1.0

3. Instructions for use

     System Configuration:
        1. Clock source: HSI+PLL
        2. System Clock frequency: 
             240MHz
        3. printf: PA9 - baud rate 115200
        4. node1:
            FDCAN1:
                TX-PA4，RX-PA5
            Clock source: 20MHz
            Baudrate: 250Kbps(nominal), 500Kbps(data)
            Working mode: normal mode
            Nominal bit timing: prescaler=2, TSEG1=31, TSEG2=8, sync jump=8
            Data bit timing: prescaler=2, TSEG1=15, TSEG2=4, synchronous jump=4
            Frame format: FDCAN, BRS ON, 16 bytes data
            Standard filter: disable
            Extended filter: 1, ID mask filter (ID=0x0AAAAAAA,mask=0x1FFFFFFF), stored in RX FIFO0
            Receive FIFO: FIFO0 enabled, size 2, FIFO1 disabled
            Receive buffer: disable
            Send buffer: 1
            Send FIFO: disable
            Send event FIFO: disable
            Timestamp: internal timestamp, divided by 16
            Interrupt:TX BUFFER0 transmission completion interrupt, interrupt line 1
            Others: Reject remote frames and non-matching frames
        5. node2:
            FDCAN2:
                TX-PG2，RX-PG3
            Clock source: 20MHz
            Baudrate: 250Kbps(nominal), 500Kbps(data)
            Working mode: normal mode
            Nominal bit timing: prescaler=2, TSEG1=31, TSEG2=8, sync jump=8
            Data bit timing: prescaler=2, TSEG1=15, TSEG2=4, synchronous jump=4
            Frame format: FDCAN, BRS ON, 16 bytes data
            Standard filter: disable
            Extended filter: 1, ID mask filter (ID=0x15555555,mask=0x1FFFFFFF), stored in RX FIFO1
            Receive FIFO: FIFO1 enabled, size 6, FIFO0 disabled
            Receive buffer: disable
            Send buffer: disable
            Send FIFO: disable
            Send event FIFO: disable
            Timestamp: internal timestamp, divided by 16
            Interrupt: RX FIFO1 watermark interrupt (watermark=2), interrupt line 1
            Others: Reject remote frames and non-matching frames
        6.EXTI
            EXTI line1,PA15 input,trigged at rising edge
             
     Instructions:
        1. After compiling, download the program and reset, the program start running.
        2. Press the button, node1 sends a data frame.
        3. After the transmission is completed, node1 prints relevant information 
            after the transmission completion interrupt.
        4. After receiving 2 data frames in a row, node2 RX FIFO1 watermark interrupt 
            is triggered, the received data is output.

4. Attention
    Connect jump caps J8/J2/J15/J9, do not connect jump caps J87/J89

