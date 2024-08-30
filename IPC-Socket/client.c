/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/IPC-Socket
 * @LastEdit: 2024-06-11
 * @FilePath: client.c
 * @Description: socket客户端测试
 */
#include <stdio.h>
#include <string.h>

#include "socket.h"

int main(void)
{
    //创建套接字
    socket_t sock = client_create();
    if (sock < 0)
    {
        return -1;
    }
    //读取服务端的数据
    char buf[64] = {0};
    socket_read(sock, buf, sizeof(buf)-1);
    printf("Client received message form server: %s\n", buf);
    //往服务端发送数据
    const char *str = "Hello, Server !";
    socket_write(sock, str, strlen(str));
    //关闭套接字
    socket_destroy(sock);
    return 0;
}