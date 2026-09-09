1、功能说明

    /* 简单描述工程功能 */
    这个例程演示将多个函数代码存储在FLASH中，程序启动时由启动代码自动将其复制到CCM SRAM，
    并在CCM SRAM中执行的方法。例程使用三级嵌套调用链（CCM_WeightedSumOfSquares →
    CCM_SumOfSquares → CCM_Square），三个函数均在CCM SRAM中执行。例程在main()中完整
    演示了CCM SRAM的一键初始化、重新拷贝代码的全流程，通过串口打印
    三个函数的执行地址，验证代码确实运行在CCM SRAM中。


2、使用环境

    软件开发环境：
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    硬件开发环境：
        基于全功能板N32H497ZGL7_EVB V1.0开发
        

3、使用说明
    
    /* 描述相关模块配置方法；例如:时钟，I/O等 */
    系统时钟配置：
        SystemClock：240MHz
            
    打印串口配置：
            USART：TX - PA9，RX - PA10，波特率115200

    /* 描述Demo的测试步骤和现象 */
        1. 使用__CCM_FUNC宏标记需要在CCM SRAM中执行的函数：
           - Keil MDK：__attribute__((section("ccmram")))
           - IAR EWARM：_Pragma("location=\"CCM_CODE\"")（自定义section，避开IAR内置
                         __ramfunc的placement规则，由ICF显式指定到CCM_region）
        2. 工程使用自定义链接脚本，将标记函数的加载地址放在FLASH，执行地址放在CCM SRAM：
           - Keil MDK：Run_In_CCM.sct（ER_CCM区域）
           - IAR EWARM：Run_In_CCM.icf（CCM_region区域，section CCM_CODE）
        3. 编译后下载程序复位运行；
        4. 查看串口打印信息，程序按以下步骤执行：
           Step 1：CCM_SRAM_SaveCode()——把CCM SRAM当前内容（启动代码已拷贝好的
                   函数字节）镜像到普通SRAM的备份缓冲ccm_backup[]；
           Step 2：通过RCC一键初始化填充CCM SRAM全部为0x00000000，建立正确的
                   ECC位；
           Step 3：CCM_SRAM_RestoreCode()——把备份缓冲ccm_backup[]写回CCM SRAM，
                   写入时ECC已使能，写入数据带正确ECC位，三个函数恢复可执行；
           Step 4：打印三个函数的执行地址，确认均在CCM SRAM范围内，三个地址全部验证通过打印[PASS]；
           Step 5：执行三级嵌套调用链CCM_WeightedSumOfSquares(5)，确认返回值为448
                   （=1*1 + 2*5 + 3*14 + 4*30 + 5*55），验证通过打印
                   Run_In_CCM Test Passed；


4、注意事项
    1. CCM SRAM默认使能ECC校验。ECC要求每个存储单元的ECC位在
       首次使用前须有效，否则读操作可能触发ECC错误。一键初始化可同时填充数据和ECC位。
    2. 启动代码在main()执行前将CCM函数代码拷贝到CCM SRAM。main()中调用CCM_SRAM_Init()
       会清零全部CCM SRAM（包括已拷贝的函数代码），因此需在初始化完成后调用
       CCM_SRAM_CopyCode()重新拷贝。
    3. 一键初始化前需先向起始地址写入初始化值，且结束地址须不同于起始地址。
    4. Keil工程需使用自定义Scatter文件（MDK-ARM/Run_In_CCM.sct）；IAR工程需使用
       自定义ICF文件（EWARM/Run_In_CCM.icf），以指定CCM SRAM的加载地址和执行地址。

1. Function description

    /* Briefly describe the project function */
    This routine demonstrates placing multiple function code in FLASH, automatically copying
    them to CCM SRAM at startup via the startup code, and executing from CCM SRAM. The
    routine uses a three-level nested call chain (CCM_WeightedSumOfSquares ->
    CCM_SumOfSquares -> CCM_Square), with all three functions executing from CCM SRAM.
    The routine demonstrates in main() the complete flow of CCM SRAM 
    one-key initialization, and code re-copy. The execution addresses of all
    three functions are printed via USART to verify that the code runs from CCM SRAM.


2. Use environment

    Software development environment: 
        KEIL MDK-ARM V5.34
        IAR EWARM 8.50.1

    Hardware development environment:
        Developed based on the full-function board N32H497ZGL7_EVB V1.0
        

3. Instructions for use

    /* Describe related module configuration methods; for example: clock, I/O, etc. */
    System Clock Configuration:
        SystemClock：240MHz
            
    Print Serial Port Configuration:
            USART：TX - PA9，RX - PA10, baud rate 115200

    /* Describe the test steps and phenomena of the Demo */
         1. Mark functions for CCM SRAM execution using the __CCM_FUNC macro:
           - Keil MDK  : __attribute__((section("ccmram")))
           - IAR EWARM : _Pragma("location=\"CCM_CODE\"") (custom section, avoids IAR's
                         built-in __ramfunc placement override; ICF explicitly places
                         CCM_CODE in CCM_region)
        2. The project uses a custom linker script to place the marked function's load
           address in FLASH and execution address in CCM SRAM:
           - Keil MDK  : Run_In_CCM.sct (ER_CCM region)
           - IAR EWARM : Run_In_CCM.icf (CCM_region, section CCM_CODE)
        3. After compiling, download the program and reset to run;
        4. Check the serial port output; the program executes the following steps:
           Step 1: CCM_SRAM_SaveCode() mirrors the current CCM SRAM contents
                   (already populated by the startup code) into a regular-SRAM
                   backup buffer ccm_backup[];
           Step 2: Use RCC one-key initialization to fill all of CCM SRAM with
                   0x00000000, establishing correct ECC bits;
           Step 3: CCM_SRAM_RestoreCode() writes the backed-up bytes from
                   ccm_backup[] back to CCM SRAM. ECC is enabled so each restored
                   word carries valid ECC bits and the three functions become
                   callable again;
           Step 4: Print the execution addresses of all three functions; confirm all
                   are within CCM SRAM range; prints [PASS]
                   when all three addresses pass;
           Step 7: Execute the three-level nested call chain
                   CCM_WeightedSumOfSquares(5); confirm the return value is 448
                   (= 1*1 + 2*5 + 3*14 + 4*30 + 5*55);
                   prints Run_In_CCM Test Passed on success;


4. Attention
    1. CCM SRAM has ECC enabled by default. ECC requires that
       ECC bits be valid before any read; otherwise a read may trigger an ECC error.
       One-key initialization fills both data and ECC bits simultaneously.
    2. The startup code copies CCM function code to CCM SRAM before main() runs.
       Calling CCM_SRAM_Init() in main() zeros all of CCM SRAM (including the copied
       function code), so CCM_SRAM_CopyCode() must be called after initialization to
       re-copy the function.
    3. Before one-key initialization, write the initialization value to the start address
       first, and the end address must differ from the start address.
    4. Keil project requires the custom scatter file (MDK-ARM/Run_In_CCM.sct); IAR
       project requires the custom ICF file (EWARM/Run_In_CCM.icf) to specify the
       load and execution addresses for CCM SRAM.
