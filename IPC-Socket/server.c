/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/IPC-Socket
 * @LastEdit: 2024-06-11
 * @FilePath: server.c
 * @Description: socket服务端测试
 */
#include <stdio.h>
#include <string.h>

#include "socket.h"

int main(void)
{
    //创建套接字
    int server_sock = server_create();
    if (server_sock < 0)
    {
        return -1;
    }
    //接收客户端请求
    int client_sock = server_listen(server_sock);
    if (client_sock < 0)
    {
        return -1;
    }
    //向客户端发送数据
    const char *str = "Hello, Client !";
    socket_write(client_sock, str, strlen(str));
    //接收客户端的数据
    char buf[64] = {0};
    socket_read(client_sock, buf, sizeof(buf)-1);
    printf("Server received message form client: %s\n", buf);
    //关闭套接字
    socket_destroy(client_sock);
    socket_destroy(server_sock);
    return 0;
}