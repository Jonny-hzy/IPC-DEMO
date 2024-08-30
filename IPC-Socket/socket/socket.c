/*
 * @Source:https://github.com/Jonny-hzy/IPC-DEMO/tree/main/IPC-Socket
 * @LastEdit: 2024-06-11
 * @FilePath: socket/socket.c
 * @Description: socket API重封装
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#include "socket.h"


//配置日志等级
#define LOG_LVL_NONE                0
#define LOG_LVL_ERR                 1
#define LOG_LVL_WARN                2
#define LOG_LVL_INFO                3
#define LOG_LVL_DBG                 4
#define LOG_LVL                     LOG_LVL_WARN

#if (LOG_LVL >= LOG_LVL_ERR)
#define SOCKET_LOGE(...)            printf("SocketError: "__VA_ARGS__)
#else
#define SOCKET_LOGE(...)
#endif
#if (LOG_LVL >= LOG_LVL_WARN)
#define SOCKET_LOGW(...)            printf("SocketWarn : "__VA_ARGS__)
#else
#define SOCKET_LOGW(...)
#endif
#if (LOG_LVL >= LOG_LVL_INFO)
#define SOCKET_LOGI(...)            printf("SocketInfo : "__VA_ARGS__)
#else
#define SOCKET_LOGI(...)
#endif
#if (LOG_LVL >= LOG_LVL_DBG)
#define SOCKET_LOGD(...)            printf("SocketDebug: "__VA_ARGS__)
#else
#define SOCKET_LOGD(...)
#endif


socket_t server_create(void)
{
    int server_sock;
    struct sockaddr_in sock_addr;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        SOCKET_LOGE("%s:%d, socket error.(%s) sock=%d\n", __func__, __LINE__, strerror(errno), server_sock);
        return server_sock;
    }
    //将套接字和IP、端口绑定
    sock_addr.sin_family = AF_INET; //使用IPv4地址
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY); //服务端是等待别人连接，不需要特定IP
    sock_addr.sin_port = htons(SOCKET_PORT); //端口
    if (bind(server_sock, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) < 0)
    {
        SOCKET_LOGE("%s:%d, bind error.(%s)\n", __func__, __LINE__, strerror(errno));
        return -1;
    }
    SOCKET_LOGD("%s\n", __func__);
    return server_sock;
}

socket_t server_listen(socket_t server_sock)
{
    SOCKET_LOGD("%s\n", __func__);
    //进入监听状态，等待用户发起请求
    listen(server_sock, SOMAXCONN); //SOMAXCONN表示由系统决定
    //接收客户端请求
    struct sockaddr_in sock_addr;
    socklen_t sock_addr_size = sizeof(sock_addr);
    return accept(server_sock, (struct sockaddr*)&sock_addr, &sock_addr_size);
}

int client_create(void)
{
    int client_sock;
    struct sockaddr_in sock_addr;

    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0)
    {
        SOCKET_LOGE("%s:%d, socket error.(%s) sock=%d\n", __func__, __LINE__, strerror(errno), client_sock);
        return client_sock;
    }
    //将套接字和IP、端口绑定
    sock_addr.sin_family = AF_INET; //使用IPv4地址
    sock_addr.sin_addr.s_addr = inet_addr(SOCKET_ADDR); //具体的IP地址
    sock_addr.sin_port = htons(SOCKET_PORT); //端口
    if (connect(client_sock, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) < 0)
    {
        SOCKET_LOGE("%s:%d, connect error.(%s)\n", __func__, __LINE__, strerror(errno));
        return -1;
    }
    SOCKET_LOGD("%s\n", __func__);
    return client_sock;
}

int socket_write(socket_t sock, const char *buf, unsigned int len)
{
    SOCKET_LOGD("%s\n", __func__);
    return write(sock, buf, len);
}

int socket_read(socket_t sock, char *buf, unsigned int len)
{
    SOCKET_LOGD("%s\n", __func__);
    return read(sock, buf, len);
}

void socket_destroy(socket_t sock)
{
    SOCKET_LOGD("%s\n", __func__);
    close(sock);
}
