/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/IPC-Pipe
 * @LastEdit: 2025-01-14
 * @FilePath: main.c
 * @Description: 匿名管道测试
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipefd[2];
    pid_t pid;

    pipe(pipefd); //创建管道
    pid = fork(); //创建子进程

    if (pid == 0) //子进程
    {
        char buf[256] = {0};
        close(pipefd[1]); //关闭写端
        read(pipefd[0], buf, sizeof(buf)-1);  //从管道读取数据
        printf("Child process received: %s\n", buf);
    }
    else //父进程
    {
        const char *msg = "msg from parent process!";
        close(pipefd[0]); //关闭读端
        write(pipefd[1], msg, strlen(msg));  //写入数据到管道
    }

    return 0;
}
