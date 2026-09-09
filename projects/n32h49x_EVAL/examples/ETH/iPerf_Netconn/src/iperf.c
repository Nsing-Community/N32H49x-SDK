/**
*     Copyright (c) 2025, Nsing Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nsing Technologies Inc. (Hereinafter 
* referred to as Nsing). This software, and the product of Nsing described herein 
* (Hereinafter referred to as the Product) are owned by Nsing under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     Nsing does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     Nsing reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact Nsing and obtain 
* the latest version of this software before placing orders.

*     Although Nsing has attempted to provide accurate and reliable information, Nsing assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall Nsing be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     Nsing Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify Nsing and hold Nsing 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by Nsing, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     Nsing products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
*\*\file iperf.c
*\*\author Nsing
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nsing Technologies Inc. All rights reserved.
**/

#include "iperf.h"
#include "lwip/tcp.h"
#include "lwip/sys.h"
#include "lwip/api.h"

#include "FreeRTOS.h"
#include "task.h"

#define IPERF_DATA_LEN                (4 * 1024)
#define SOCKET_LISTEN_BACKLOG         (5)


extern void * pvPortMalloc( size_t xWantedSize );

static void iperf_server_netconn_thread(void *arg);
static void iperf_client_netconn_thread(void *arg);

/**
*\*\name    iperf_server_netconn_thread.
*\*\fun     iPerf server task entry function, programmed via NETCONN API.
*\*\param   arg
*\*\         - Task entry function parameter
*\*\return  none
**/
static void iperf_server_netconn_thread(void *arg)
{
    err_t Err;
    struct netconn *Conn = NULL;
    struct netconn *NewConn = NULL;
    struct netbuf *pBuf = NULL;
    
    LWIP_UNUSED_ARG(arg);
    
    printf("\r\nCall %s\r\n", __FUNCTION__);
    
#if LWIP_IPV6
    /* Create a new connection identifier */
    Conn = netconn_new(NETCONN_TCP_IPV6);
    LWIP_ERROR("Invalid Conn\n", (Conn != NULL), while (1););
    /* Bind local port and IP address */
    netconn_bind(Conn, IP6_ADDR_ANY, LOCAL_PORT);
#else /* LWIP_IPV6 */
    /* Create a new connection identifier */
    Conn = netconn_new(NETCONN_TCP);
    LWIP_ERROR("Invalid Conn\n", (Conn != NULL), while (1););
    /* Bind local port and IP address */
    netconn_bind(Conn, IP_ADDR_ANY, IPERF_PORT);
#endif /* LWIP_IPV6 */
    
    printf("Local port: %d\n", IPERF_PORT);
    printf("Start listening...\n");
    
    /* Tell connection to go into listening mode */
    netconn_listen(Conn);
    
    while (1)
    {
        /* Accept a new connection */
        Err = netconn_accept(Conn, &NewConn);
        if (Err == ERR_OK)
        {
            printf("Client %s:%d gets online\n", ipaddr_ntoa(&NewConn->pcb.tcp->remote_ip), NewConn->pcb.tcp->remote_port);
            
            while (1)
            {
                /* Receive data */
                if (netconn_recv(NewConn, &pBuf) != ERR_OK)
                {
                    printf("\r\n");
                    printf("iPerf done...\n");
                    printf("\r\n");
                    printf("To switch mode for testing, reset the development board first\n");
                    break;
                }
                /* Clears the allocated pBuf */
                netbuf_delete(pBuf);
            }
            /* Clears the allocated pBuf */
            netbuf_delete(pBuf);
            /* Close connection */
            netconn_close(NewConn);
            /* Discard connection identifier */
            netconn_delete(NewConn);
            while (1)
            {
                /* System can switch to other tasks */
                vTaskDelay(10);
            }
        }
    }
}

/**
*\*\name    iperf_client_netconn_thread.
*\*\fun     iPerf client task entry function, programmed via NETCONN API.
*\*\param   arg
*\*\         - Task entry function parameter
*\*\return  none
**/
static void iperf_client_netconn_thread(void *arg)
{
    int i = 0;
    err_t Err;
    struct netconn *Conn = NULL;
    char *pSendBuff = NULL;
    
    ip4_addr_t ServerAddr;
    
    LWIP_UNUSED_ARG(arg);
    
    printf("\r\nCall %s\r\n", __FUNCTION__);

    /* Requests a section of memory for send data */
    pSendBuff = (char *)pvPortMalloc(IPERF_DATA_LEN);
    if (pSendBuff == NULL)
    {
        printf("No memory\n");
        while (1)
        {
        }
    }
    
    for (i = 0; i < IPERF_DATA_LEN; i++)
    {
        pSendBuff[i] = (i & 0xFFU);
    }
    
    /* Set the server IP address */
    IP4_ADDR(&ServerAddr, REMOTE_IP_ADDR0, REMOTE_IP_ADDR1, REMOTE_IP_ADDR2, REMOTE_IP_ADDR3);
    printf("Server IP: %d.%d.%d.%d\n", REMOTE_IP_ADDR0, REMOTE_IP_ADDR1, REMOTE_IP_ADDR2, REMOTE_IP_ADDR3);
    printf("Server Port: %d\n", IPERF_PORT);
    
    while (1)
    {
        /* Create a connection structure */
        Conn = netconn_new(NETCONN_TCP);
        LWIP_ERROR("Invalid Conn\n", (Conn != NULL), while (1););
        
        /* Connect to a remote server with a specified IP address and port */
        Err = netconn_connect(Conn, &ServerAddr, IPERF_PORT);
        /* Connected successfully, ready to receive data, send data */
        if (Err == ERR_OK)
        {
            printf("The server is connected from local %s:%d\n", ipaddr_ntoa(&Conn->pcb.tcp->local_ip), Conn->pcb.tcp->local_port);
            
            while (1)
            {
                /* Sends the received data to the remote */
                if (netconn_write(Conn, pSendBuff, IPERF_DATA_LEN, NETCONN_COPY) != ERR_OK)
                {
                    printf("\r\n");
                    printf("iPerf done...\n");
                    printf("\r\n");
                    printf("To switch mode for testing, reset the development board first\n");
                    break;
                }
            }
            /* Close connection */
            netconn_close(Conn);
            /* Discard connection identifier */
            netconn_delete(Conn);
            while (1)
            {
                /* System can switch to other tasks */
                vTaskDelay(10);
            }
        }
        /* Connection fails, attempts to reconnect after a delay */
        /* The number of reconnections allowed is determined by MEMP_NUM_NETCONN */
        else
        {
            printf("Connect failed\n");
            netconn_close(Conn);
            vTaskDelay(5000);
            continue;
        }
    }
}

/**
*\*\name    LwIP_iPerfModeSelect.
*\*\fun     Select Mode: Server or Client Server mode tests reception; Client 
*\*\        mode tests transmission.
*\*\param   serverMode :
*\*\          - Server mode flag
*\*\param   clientMode :
*\*\          - Client mode flag
*\*\return  true or false.
**/
static bool LwIP_iPerfModeSelect(bool *serverMode, bool *clientMode)
{
    char code;

    printf("\r\n");
    printf("S: TCP Server Mode\n");
    printf("C: TCP Client Mode\n");
    printf("Please enter 'S' or 'C' to select the mode: ");
    
    code = getchar();
    printf("%c\n", code);
    
    switch (code)
    {
        case 'S':
            *serverMode = true;
            *clientMode = false;
            break;

        case 'C':
            *serverMode = false;
            *clientMode = true;
            break;

        default:
            return false;
    }

    return true;
}

/**
*\*\name    LwIP_iPerfInit.
*\*\fun     Initialize LwIP iPerf by creating a task thread.
*\*\param   none
*\*\return  none
**/
void LwIP_iPerfInit(void)
{
    bool bServer = false;
    bool bClient = false;
    
    printf("\r\nCall %s\r\n", __FUNCTION__);
    
    LwIP_iPerfModeSelect(&bServer, &bClient);
    
    if (bServer && (!bClient))
    {
        /* Create a TCP server task thread */
        sys_thread_new("iperf_server_netconn_thread", /* Task name */
                       iperf_server_netconn_thread,   /* Task entry function */
                       NULL,                          /* Task entry function parameter */
                       IPERF_SERVER_TASK_STACK_SIZE,  /* Task stack size */
                       IPERF_SERVER_TASK_PRIORITY);   /* Task priority */
    }
    else if ((!bServer) && bClient)
    {
        /* Create a TCP client task thread */
        sys_thread_new("iperf_client_netconn_thread", /* Task name */
                       iperf_client_netconn_thread,   /* Task entry function */
                       NULL,                          /* Task entry function parameter */
                       IPERF_CLIENT_TASK_STACK_SIZE,  /* Task stack size */
                       IPERF_CLIENT_TASK_PRIORITY);   /* Task priority */
    }
    else
    {
        printf("Incorrect mode selection. Please reset and re-enter...\r\n");
    }
}

