/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/ITC-MailBox
 * @LastEdit: 2024-05-09
 * @FilePath: ./main.c
 * @Description: 线程邮箱测试
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "mailbox.h"


void *print_thread(void *arg)
{
    mail_box_t *box = *(mail_box_t**)arg;
    char sender[MAX_NAME_LENGTH];
    mail_data_t data;
    int i = 0;

    while (i++ < 15) //设置一个退出条件，便于测试API
    {
        if (receive_mail(box, sender, data) > 0)
        {
            printf("\"print\" received mail from \"%s\": %s\n", sender, data);
        }
        sleep(1);
    }
    return NULL;
}

void *data_delay_thread(void *arg)
{
    mail_box_t *box = *(mail_box_t**)arg;

    //向cycle发数据
    send_mail(box, "cycle", "cycle_from_delay");
    //延时后向print发数据
    sleep(3);
    send_mail(box, "print", "delay1");
    send_mail(box, "print", "delay2");
    send_mail(box, "print", "delay3");
    send_mail(box, "print", "delay4");
    send_mail(box, "print", "delay5");
    return NULL;
}

void *data_cycle_thread(void *arg)
{
    mail_box_t *box = *(mail_box_t**)arg;
    int i = 0;
    mail_data_t data;

    //接收第一包数据（来自delay线程）
    while (1)
    {
        if (receive_mail(box, NULL, data) > 0) //可以不关心sender是谁
        {
            break;
        }
        sleep(1);
    }
    //将收到的数据发往print线程若干次
    while (i++ < 5)
    {
        send_mail(box, "print", data);
        sleep(1);
    }
    return NULL;
}

int main(void)
{
    mail_box_t *box = NULL;

    box = mailbox_create();
    mailbox_regester_user(box, "print", print_thread);
    mailbox_regester_user(box, "delay", data_delay_thread);
    mailbox_regester_user(box, "cycle", data_cycle_thread);

    mailbox_unregester_user(box, "print");
    mailbox_unregester_user(box, "delay");
    mailbox_unregester_user(box, "cycle");
    mailbox_destroy(box);

    return 0;
}