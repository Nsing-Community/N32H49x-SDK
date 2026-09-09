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
#include <lwip/sockets.h>

#include "FreeRTOS.h"
#include "task.h"

#define IPERF_DATA_LEN                (4 * 1024)
#define SOCKET_LISTEN_BACKLOG         (5)


extern void * pvPortMalloc( size_t xWantedSize );

static void iperf_server_socket_thread(void *arg);
static void iperf_client_socket_thread(void *arg);

/**
*\*\name    iperf_server_socket_thread.
*\*\fun     iPerf server task entry function, programmed via SOCKET API.
*\*\param   arg
*\*\         - Task entry function parameter
*\*\return  none
**/
static void iperf_server_socket_thread(void *arg)
{
    int Sock = -1;
    int SockNew = -1;
    int Flag = 1;
    int Len = 0;
    char *pData = NULL;
    
    struct sockaddr_in ServerAddr;
    struct sockaddr_in ClientAddr;
    socklen_t SinSize = sizeof(struct sockaddr_in);
    
    LWIP_UNUSED_ARG(arg);
    
    printf("\r\nCall %s\r\n", __FUNCTION__);
    
    memset(&ServerAddr, 0, sizeof(ServerAddr));
    memset(&ClientAddr, 0, sizeof(ClientAddr));
    
    /* Requests a section of memory for receiving data */
    pData = (char *)pvPortMalloc(IPERF_DATA_LEN);
    if (pData == NULL)
    {
        printf("No memory\n");
        while (1)
        {
        }
    }
    
    /* Creates a socket */
    Sock = socket(AF_INET, SOCK_STREAM, 0);
    if (Sock < 0)
    {
        printf("socket error\n");
        while (1)
        {
        }
    }
    
    /* Set the server address information */
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = INADDR_ANY;
    ServerAddr.sin_port = htons(IPERF_PORT);
    
    /* Bind local port and IP address */
    if (bind(Sock, (struct sockaddr *)&ServerAddr, sizeof(struct sockaddr)) != 0)
    {
        printf("Unable to bind\n");
        closesocket(Sock);
        free(pData);
        while (1)
        {
        }
    }
    
    printf("Local port: %d\n", IPERF_PORT);
    printf("Start listening...\n");
    
    /* Tell connection to go into listening mode */
    if (listen(Sock, SOCKET_LISTEN_BACKLOG) != 0)
    {
        printf("listen error\n");
        closesocket(Sock);
        free(pData);
        while (1)
        {
        }
    }
    
    while (1)
    {
        /* Accept a new connection, return a new socket */
        SockNew = accept(Sock, (struct sockaddr *)&ClientAddr, &SinSize);
        if (SockNew >= 0)
        {
            printf("Client %s:%d gets online\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));
            /* Sets options for the new socket */
            setsockopt(SockNew, IPPROTO_TCP, TCP_NODELAY, (void *)&Flag, sizeof(int));
            
            while (1)
            {
                /* Blocking Receive Data */
                Len = read(SockNew, pData, IPERF_DATA_LEN);
                /* If valid data is successfully received, process it */
                if (Len > 0)
                {
                    continue;
                }
                /* The client disconnects, jumps out of the loop, and accepts a new connection */
                else
                {
                    printf("\r\n");
                    printf("iPerf done...\n");
                    printf("\r\n");
                    printf("To switch mode for testing, reset the development board first\n");
                    break;
                }
            }
            /* Close the current accept socket */
            closesocket(SockNew);
            SockNew = -1;
            while (1)
            {
                /* System can switch to other tasks */
                vTaskDelay(10);
            }
        }
    }
}

/**
*\*\name    iperf_client_socket_thread.
*\*\fun     iPerf client task entry function, programmed via SOCKET API.
*\*\param   arg
*\*\         - Task entry function parameter
*\*\return  none
**/
static void iperf_client_socket_thread(void *arg)
{
    int i = 0;
    int Sock = -1;
    int Len = 0;
    ip4_addr_t IpAddr;
    char *pSendBuff = NULL;
    struct sockaddr_in ServerAddr;
    struct sockaddr_in ClientAddr;
    socklen_t AddrSize = sizeof(ClientAddr);
    
    LWIP_UNUSED_ARG(arg);
    
    printf("\r\nCall %s\r\n", __FUNCTION__);
    
    memset(&ServerAddr, 0, sizeof(ServerAddr));
    memset(&ClientAddr, 0, sizeof(ClientAddr));
    
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
    IP4_ADDR(&IpAddr, REMOTE_IP_ADDR0, REMOTE_IP_ADDR1, REMOTE_IP_ADDR2, REMOTE_IP_ADDR3);
    printf("Server IP: %d.%d.%d.%d\n", REMOTE_IP_ADDR0, REMOTE_IP_ADDR1, REMOTE_IP_ADDR2, REMOTE_IP_ADDR3);
    printf("Server Port: %d\n", IPERF_PORT);
    
    /* Set the server address information */
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = IpAddr.addr;
    ServerAddr.sin_port = htons(IPERF_PORT);
    
    while (1)
    {
        /* Creates a socket */
        Sock = socket(AF_INET, SOCK_STREAM, 0);
        if (Sock < 0)
        {
            printf("socket error\n");
            vTaskDelay(1000);
            continue;
        }
        
        /* Connect to a remote server with a specified IP address and port */
        if (connect(Sock, (struct sockaddr *)&ServerAddr, sizeof(struct sockaddr)) != 0)
        {
            printf("connect failed!\n");
            closesocket(Sock);
            vTaskDelay(10000);
            continue;
        }
        
        /* Get local address and port information */
        getsockname(Sock, (struct sockaddr *)&ClientAddr, &AddrSize);
        printf("The server is connected from local %s:%d\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));
        
        while (1)
        {
            /* Sends the data to the remote */
            Len = send(Sock, pSendBuff, IPERF_DATA_LEN, 0);
            if (Len < 0)
            {
                printf("\r\n");
                printf("iPerf done...\n");
                printf("\r\n");
                printf("To switch mode for testing, reset the development board first\n");
                break;
            }
        }
        /* Close the socket */
        closesocket(Sock);
        while (1)
        {
            /* System can switch to other tasks */
            vTaskDelay(10);
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
        sys_thread_new("iperf_server_socket_thread", /* Task name */
                       iperf_server_socket_thread,   /* Task entry function */
                       NULL,                         /* Task entry function parameter */
                       IPERF_SERVER_TASK_STACK_SIZE, /* Task stack size */
                       IPERF_SERVER_TASK_PRIORITY);  /* Task priority */
    }
    else if ((!bServer) && bClient)
    {
        /* Create a TCP client task thread */
        sys_thread_new("iperf_client_socket_thread", /* Task name */
                       iperf_client_socket_thread,   /* Task entry function */
                       NULL,                         /* Task entry function parameter */
                       IPERF_CLIENT_TASK_STACK_SIZE, /* Task stack size */
                       IPERF_CLIENT_TASK_PRIORITY);  /* Task priority */
    }
    else
    {
        printf("Incorrect mode selection. Please reset and re-enter...\r\n");
    }
}

