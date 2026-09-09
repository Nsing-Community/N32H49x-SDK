1、功能说明
    本工程为有操作系统（FreeRTOS）的JPerf工具测试网速示例。示例工程基于TCP协议，用socket API编程，支持服务器和客户端测试模式。JPerf工具见ETH文件夹下的jperf.zip，解压缩后双击jperf.bat即可运行使用（如PC环境未安装iPerf服务器，请先下载安装，方法参考网络搜索即可）。

2、使用环境

    软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发

3、使用说明
    
    系统配置：
        1、时钟源：HSI+PLL
        2、时钟频率：240MHz
        3、打印：PA9 - baud rate 115200

    以太网配置：
        1、PHY接口：RMII
        2、引脚分配：
            ETH_MDC<----->PC1
            ETH_MDIO<----->PA2
            ETH_RMII_REF_CLK<----->PA1
            ETH_RMII_CRS_DV<----->PA7
            ETH_RMII_RX_D0<----->PC4
            ETH_RMII_RX_D1<----->PC5
            ETH_RMII_TX_EN<----->PG11
            ETH_RMII_TX_D0<----->PG13
            ETH_RMII_TX_D1<----->PG14
            ETH_PPS_OUT<----->PB5

    使用方法：
        1、编译后下载程序运行，串口将打印本地IP地址、端口等信息，本示例使用静态IP地址
        2、根据串口调试助手的打印信息，选择测试模式；发送‘S’选择为服务器模式，发送‘C’选择为客户端模式
        3、根据串口调试助手的打印信息中的本地IP地址、端口号设置JPerf工具
        4、测试服务器模式时，先在串口调试助手中发送‘S’指令，后在JPerf工具中选择Client并点击Run IPerf
        5、测试客户端模式时，先在JPerf工具中选择Server并点击Run IPerf，后在串口调试助手中发送‘C’指令
        6、开发板正常运行后，即可通过JPerf工具查看网络带宽数据，包含网络带宽折线图

4、注意事项
    1、您使用的PHY芯片可能与demo默认选择的不一样，请在bsp_eth.h中切换或添加其他PHY的定义；请注意PHY_ADDR，PHY地址值必须与硬件设计保持一致
    2、开发板默认静态IP地址为：192.168.0.32，使用静态IP地址时要确保开发板与电脑处于同一网段，且无IP地址冲突


1. Function description
    This project is an example of network speed testing using the JPerf tool with an OS (FreeRTOS). The example project is based on the TCP protocol and utilizes the socket API for programming, supporting both server and client testing modes. The JPerf tool is located in the ETH folder as jperf.zip. After unzipping, double-click jperf.bat to run it. (If the iPerf server is not installed on your PC, please download and install it first. Refer to online searches for installation methods.)

2. Use environment

    Software development environment: 
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0

3. Instructions for use
    
    System configuration:
        1, clock source: HSI + PLL
        2, clock frequency: 240MHz
        3, print: PA9 - baud rate 115200

    Ethernet configuration:
        1, PHY interface: RMII
        2, Pin assignment:
            ETH_MDC<----->PC1
            ETH_MDIO<----->PA2
            ETH_RMII_REF_CLK<----->PA1
            ETH_RMII_CRS_DV<----->PA7
            ETH_RMII_RX_D0<----->PC4
            ETH_RMII_RX_D1<----->PC5
            ETH_RMII_TX_EN<----->PG11
            ETH_RMII_TX_D0<----->PG13
            ETH_RMII_TX_D1<----->PG14
            ETH_PPS_OUT<----->PB5

    Usage:
        1. After compiling and downloading the program, run it. The serial port will print local IP address, port, and other information. This example uses a static IP address.
        2. Based on the information printed by the Serial Debug Assistant, select the test mode: send ‘S’ to choose server mode, send ‘C’ to choose client mode.
        3. Configure the JPerf tool using the local IP address and port number from the information printed by the Serial Debug Assistant.
        4. When testing server mode: First send the‘S’command in the serial debugging assistant, then select Client in the JPerf tool and click Run IPerf.
        5. When testing client mode: First select Server in the JPerf tool and click Run IPerf, then send the‘C’command in the serial debugging assistant.
        6. Once the development board is running normally, you can view network bandwidth data via the JPerf tool, including a network bandwidth line chart.

4. Attention
    1, The PHY chip you are using may differ from the default selection in this demo. Please switch or add definitions for other PHYs in bsp_eth.h. Note that the PHY_ADDR value must match the hardware design.
    2, The default static IP address of the development board is 192.168.0.32. When using a static IP address, make sure that the board is on the same network segment as the computer and that there are no IP address conflicts.

