/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/IPC-SharedMemory
 * @LastEdit: 2024-05-16
 * @FilePath: reader.c
 * @Description: 共享内存通信的接收端测试
 */
#include <stdio.h>
#include "shm.h"


int main(void)
{
    int i = 0;
    int shmid = 0;
    char *mem = NULL;

    shmid = shm_create(512);
    if (shmid < 0)
    {
        printf("shm_create fail\n");
        return -1;
    }

    mem = shm_connect(shmid);
    if (mem < 0)
    {
        printf("shm_attach fail\n");
        return -1;
    }

    while (i++ < 10)
    {
        sleep(1);
        printf("received data: %s\n", mem);
    }

    shm_destroy(shmid);
    return 0;
}