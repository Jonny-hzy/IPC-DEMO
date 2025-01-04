/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/IPC-MsgQue
 * @LastEdit: 2025-01-04
 * @FilePath: receiver.c
 * @Description: MessageQueues发送端测试
 */
#include <stdio.h>
#include <string.h>

#include "msg.h"


int main(void)
{
    const char buf[][MSG_SIZE] = {
        "[MSG-TEST-EVENT_A]",
        "[MSG-TEST-EVENT_B]",
        "[MSG-TEST-EVENT_C]",
    };
    int i = 0;
    int msgid = 0;
    int ret = 0;

    msgid = msg_create();
    for (i=0; i<sizeof(buf)/sizeof(buf[0]); i++)
    {
        ret = msg_write(msgid, buf[i], strlen(buf[i]));
        if (ret > 0)
        {
            printf("msg write(%02d): OK\n", i+1);
        }
        else
        {
            printf("msg write(%02d): NG\n", i+1);
        }
        sleep(1);
    }
    //msg_destroy(msgid); //由“最终操作方”来销毁队列
    return 0;
}