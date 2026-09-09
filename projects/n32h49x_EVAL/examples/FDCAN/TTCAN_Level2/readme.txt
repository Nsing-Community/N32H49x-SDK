1、功能说明
    此例程展示了TTCAN Level2严格时间触发模式的运行。

2、使用环境
    软件开发环境：
        KEIL MDK-ARM 5.34.0.0
        IAR EWARM 8.50.1
                
    硬件开发环境：
        基于评估板N32H497ZGL7_EVB V1.0开发

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
            波特率：500Kbps（仲裁域），1Mbps（数据域）
            工作模式：TTCAN Level2 + 正常模式
            标称位时序：预分频=1，TSEG1=31，TSEG2=8，同步跳转=8
            数据位时序：预分频=1，TSEG1=15，TSEG2=4，同步跳转=4
            帧格式：FDCAN，BRS ON，8字节数据
            标准接收过滤器：禁用
            扩展接收过滤器：1个，ID掩码过滤（ID=0x0AAAAAAA,掩码=0x00000000），存储在RX FIFO0
            接收FIFO：FIFO0禁用，FIFO1禁用
            接收缓冲：禁用
            发送缓冲：5个
            发送FIFO：0个
            发送事件FIFO：禁用
            时间戳：内部时间戳，16分频
            其他：拒绝远程帧与非匹配帧
        5、节点2:
            FDCAN2:
                TX-PG2，RX-PG3
            时钟源：20MHz
            波特率：500Kbps（标称），1Mbps（数据）
            工作模式：TTCAN Level2 + 普通模式
            标称位时序：预分频=1，TSEG1=31，TSEG2=8，同步跳转=8
            数据位时序：预分频=1，TSEG1=15，TSEG2=4，同步跳转=4
            帧格式：FDCAN，BRS ON，8字节数据
            标准接收过滤器：禁用
            扩展接收过滤器：2个，ID掩码过滤（ID=0x1AAAA754,掩码=0x1FFFFFFF），存储在RX FIFO0
            ID掩码过滤（ID=0x1AAAA755,掩码=0x1FFFFFFF），存储在RX FIFO1
            接收FIFO：启用FIFO0，大小为2，FIFO0启用，大小为2
            接收缓冲：禁用
            发送缓冲：禁用
            发送FIFO：禁用
            发送事件FIFO：禁用
            时间戳：内部时间戳，16分频
            其他：拒绝远程帧与非匹配帧
        6. TTCAN矩阵
            /*****************---------------------------------***************/
            周期 |                             FDCAN1时间标记
                 |     5000       10000       20000       20200        50000        60000      65000
              0  |   Node1_TX1                                       Node1_TXRef   TX_Watch   End_List
              1  |               Node1_TX2                           Node1_TXRef   TX_Watch   End_List
              2  |                           Node1_TX3   Node1_TX4   Node1_TXRef   TX_Watch   End_List
              3  |               Node1_TX2                           Node1_TXRef   TX_Watch   End_List
              4  |   Node1_TX1                                       Node1_TXRef   TX_Watch   End_List
              5  |               Node1_TX2                           Node1_TXRef   TX_Watch   End_List
              6  |                           Node1_TX3   Node1_TX4   Node1_TXRef   TX_Watch   End_List
              7  |               Node1_TX2                           Node1_TXRef   TX_Watch   End_List
        
        Node1_TX1 : TimeMark:5000     ID:0x1AAAA754
        Node1_TX2 : TimeMark:10000    ID:0x1AAAA755
        Node1_TX3 : TimeMark:20000    ID:0x1AAAA786
        Node1_TX4 : TimeMark:20200    ID:0x1AAAA787
        
            /*****************---------------------------------***************/
            周期 |                             FDCAN2时间标记
                 |     6000       11000                   30000                     60000      65000
              0  |   Node2_RX1                           Node2_TX1                 TX_Watch   
              1  |               Node2_RX2                                         TX_Watch   
              2  |                                                                 TX_Watch   
              3  |               Node2_RX2                                         TX_Watch   
              4  |   Node2_RX1                           Node2_TX1                 TX_Watch   
              5  |               Node2_RX2                                         TX_Watch   
              6  |                                                                 TX_Watch   
              7  |               Node2_RX2                                         TX_Watch   
        Node2_RX1 : TimeMark:6000     ID:0x1AAAA754
        Node2_RX2 : TimeMark:11000    ID:0x1AAAA755
        Node2_TX1 : TimeMark:30000    ID:0x16666754

    使用方法：
        1. 连接跳帽J8/J2/J15/J9，不要连接跳帽J87/J89
        2. N32H497ZGL7_EVB V1.0板需要焊接R26和R41两个120Ω电阻

4、注意事项
    N32H497ZGL7_EVB V1.0板需要焊接R26和R41两个120Ω电阻
    
1. Function description

     This routine demonstrates the operation of TTCAN Level 2 in strict time triggered mode.

2. Use environment

    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1

    Hardware development environment:
         Developed based on the evaluation board N32H497ZGL7_EVB V1.0

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
            Baudrate: 500Kbps(nominal), 1Mbps(data)
            Working mode: TTCAN Level2 + normal mode
            Nominal bit timing: prescaler=1, TSEG1=31, TSEG2=8, sync jump=8
            Data bit timing: prescaler=1, TSEG1=15, TSEG2=4, synchronous jump=4
            Frame format: FDCAN, BRS ON, 8 bytes data
            Standard filter: disable
            Extended filter: 1, ID mask filter (ID=0x0AAAAAAA,mask=0x00000000), stored in RX FIFO0
            Receive FIFO: FIFO0 disabled, FIFO1 disabled
            Receive buffer: disable
            Send buffer: disable
            Send FIFO: size 5
            Send event FIFO: disable
            Timestamp: internal timestamp, divided by 16
            Others: Reject remote frames and non-matching frames
        5. node2:
            FDCAN2:
                TX-PG2，RX-PG3
            Clock source: 20MHz
            Baudrate: 500Kbps(nominal), 1Mbps(data)
            Working mode: TTCAN Level2 + normal mode
            Nominal bit timing: prescaler=1, TSEG1=31, TSEG2=8, sync jump=8
            Data bit timing: prescaler=1, TSEG1=15, TSEG2=4, synchronous jump=4
            Frame format: FDCAN, BRS ON, 8 bytes data
            Standard filter: disable
            Extended filter: 2, ID mask filter (ID=0x1AAAA754,mask=0x1FFFFFFF), stored in RX FIFO0
            ID mask filter (ID=0x1AAAA755,mask=0x1FFFFFFF), stored in RX FIFO1
            Receive FIFO: FIFO0 enabled, size 32; FIFO1 enabled, size 32
            Receive buffer: disable
            Send buffer: disable
            Send FIFO: disable
            Send event FIFO: disable
            Timestamp: internal timestamp, divided by 16
            Others: Reject remote frames and non-matching frames
         6. TTCAN matrix
            /*****************---------------------------------***************/
           cycle |                             FDCAN1 time mark
                 |     5000       10000       20000       20200        50000        60000      65000
              0  |   Node1_TX1                                       Node1_TXRef   TX_Watch   End_List
              1  |               Node1_TX2                           Node1_TXRef   TX_Watch   End_List
              2  |                           Node1_TX3   Node1_TX4   Node1_TXRef   TX_Watch   End_List
              3  |               Node1_TX2                           Node1_TXRef   TX_Watch   End_List
              4  |   Node1_TX1                                       Node1_TXRef   TX_Watch   End_List
              5  |               Node1_TX2                           Node1_TXRef   TX_Watch   End_List
              6  |                           Node1_TX3   Node1_TX4   Node1_TXRef   TX_Watch   End_List
              7  |               Node1_TX2                           Node1_TXRef   TX_Watch   End_List
        
        Node1_TX1 : TimeMark:5000     ID:0x1AAAA754
        Node1_TX2 : TimeMark:10000    ID:0x1AAAA755
        Node1_TX3 : TimeMark:20000    ID:0x1AAAA786
        Node1_TX4 : TimeMark:20200    ID:0x1AAAA787
        
            /*****************---------------------------------***************/
           cycle |                             FDCAN2 time mark
                 |     6000       11000                   30000                     60000      65000
              0  |   Node2_RX1                           Node2_TX1                 TX_Watch   
              1  |               Node2_RX2                                         TX_Watch   
              2  |                                                                 TX_Watch   
              3  |               Node2_RX2                                         TX_Watch   
              4  |   Node2_RX1                           Node2_TX1                 TX_Watch   
              5  |               Node2_RX2                                         TX_Watch   
              6  |                                                                 TX_Watch   
              7  |               Node2_RX2                                         TX_Watch   
        Node2_RX1 : TimeMark:6000     ID:0x1AAAA754
        Node2_RX2 : TimeMark:11000    ID:0x1AAAA755
        Node2_TX1 : TimeMark:30000    ID:0x16666754
             
     Instructions:
        1. After compilation, download the program to the development board and reset it to run.
        2. Check the serial port printing. If the serial port is printed "runing" , not printed and there is an error, 
           it indicates that it is running normally.


4. Attention
    1. Connect jump caps J8/J2/J15/J9, do not connect jump caps J87/J89
    2. N32H497ZGL7-EVB V1.0 board requires soldering two 120 Ω resistors, R26 and R41

