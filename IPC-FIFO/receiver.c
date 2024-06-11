/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO
 * @LastEdit: 2024-04-30
 * @FilePath: receiver.c
 * @Description: fifo接收端测试
 */
#include <stdio.h>

#include "fifo.h"


int main(void)
{
    char buf[64] = {0};
    int i = 0;
    int ret = 0;

    fifo_init();
    while (i++ < 10)
    {
        ret = fifo_read(buf, sizeof(buf));
        if (ret > 0)
        {
            printf ("fifo read(%02d): %s\n", i, buf);
        }
        sleep(1);
    }
    fifo_deinit();
    return 0;
}