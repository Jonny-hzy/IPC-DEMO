/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/IPC-SharedMemory
 * @LastEdit: 2024-05-16
 * @FilePath: sender.c
 * @Description: 共享内存的发送端测试
 */
#include <stdio.h>
#include <string.h>
#include "shm.h"


int main(void)
{
    int i = 0;
    int shmid = 0;
    char *mem = NULL;

    //demo省略了返回值错误检查(例子见receiver.c)
    shmid = shm_create(512);
    mem = shm_connect(shmid);

    //不断衔接
    for (i=0; i<5; i++)
    {
        mem[i] = 'A' + i;
        sleep(1);
    }

    //清除重写
    memset(mem, 0, strlen(mem));
    for (i=0; i<5; i++)
    {
        mem[0] = '1' + i;
        sleep(1);
    }

    shm_destroy(shmid);
    return 0;
}