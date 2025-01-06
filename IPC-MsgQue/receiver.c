/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/IPC-MsgQue
 * @LastEdit: 2025-01-04
 * @FilePath: receiver.c
 * @Description: MessageQueues接收端测试
 */
#include <stdio.h>
#include <unistd.h>

#include "msg.h"


int main(void)
{
    char buf[64] = {0};
    int i = 0;
    int msgid = 0;
    int ret = 0;

    msgid = msg_create();
    do
    {
        ret = msg_read(msgid, buf, sizeof(buf));
        if (ret > 0)
        {
            printf ("msg read: %s\n", buf);
        }
        else
        {
            sleep(1);
        }
    } while(i++ < 10);
    msg_destroy(msgid);
    return 0;
}