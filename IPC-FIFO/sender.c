/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/IPC-FIFO
 * @LastEdit: 2024-04-30
 * @FilePath: receiver.c
 * @Description: fifo发送端测试
 */
#include <stdio.h>
#include <unistd.h>

#include "fifo.h"


int main(void)
{
    char buf[64] = "[FIFO-TEST-MESSAGE]";
    int i = 0;
    int ret = 0;

    fifo_init();
    while (i++ < 10)
    {
        ret = fifo_write(buf, sizeof(buf));
        if (ret == sizeof(buf))
        {
            printf("fifo write(%02d): OK\n", i);
        }
        else
        {
            printf("fifo write(%02d): NG\n", i);
        }
        sleep(1);
    }
    fifo_deinit();
    return 0;
}