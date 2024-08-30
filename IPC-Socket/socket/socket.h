/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/IPC-Socket
 * @LastEdit: 2024-04-30
 * @FilePath: socket\socket.h
 * @Description: socket API重封装
 */
#ifndef __SOCKET_H__
#define __SOCKET_H__

//配置IP
#define SOCKET_ADDR     "127.0.0.1"
//配置端口
#define SOCKET_PORT      1234

//定义socket句柄（避免和其它int变量混淆）
typedef int socket_t;

/*
    创建socket服务端
    返回值：
        成功：返回socket句柄
        失败：返回负数
*/
socket_t server_create(void);
/*
    创建socket客户端
    返回值：
        成功：返回socket文件描述符
        失败：返回负数
*/
socket_t client_create(void);

/*
    socket服务端监听
    server_sock：服务端socket句柄
    返回值：客户端socket句柄
*/
socket_t server_listen(socket_t server_sock);

/*
    发送数据
    sock：客户端socket句柄
    buf：待发送缓冲区
    len：待发送长度
    返回值：真实发送长度
*/
int socket_write(socket_t sock, const char *buf, unsigned int len);

/*
    读取数据
    sock：客户端socket句柄
    buf：读取缓冲区
    len：最大读取长度
    返回值：真实读取长度
*/
int socket_read(socket_t sock, char *buf, unsigned int len);

/*
    销毁socket
    sock：socket句柄
*/
void socket_destroy(socket_t sock);


#endif /* __SOCKET_H__ */

