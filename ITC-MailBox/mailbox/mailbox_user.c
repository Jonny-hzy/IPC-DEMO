/*
 * @Source: https://github.com/Jonny-hzy/ITC-MailBox
 * @LastEdit: 2024-05-09
 * @FilePath: ./mailbox/mailbox_user..c
 * @Description: 线程邮箱用户管理
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mailbox_user.h"


void user_add(mail_user_t **user_list, mail_user_t *user)
{
    if (*user_list == NULL)
    {
        *user_list = user;
    }
    else
    {
        mail_user_t *last = *user_list;
        while (last->next) {
            last = last->next;
        }
        last->next = user;
    }
}

void user_delete(mail_user_t **user_list, mail_user_t *user)
{
    mail_user_t *found = *user_list;
    mail_user_t *prev = NULL;
    mail_user_t *next = NULL;
    char *name = user->name;

    while (found)
    {
        if (strncmp(found->name, name, strlen(name)) == 0)
        {
            if (prev)
            {
                prev->next = found->next;
            }
            else
            {
                *user_list = found->next;
            }
            break;
        }
        prev = found;
        found = found->next;
    }
}

mail_user_t *user_find(mail_user_t *user_list, const char *name)
{
    mail_user_t *user = user_list;

    if (!name)
    {
        printf("%s name=NULL\n", __func__);
        return NULL;
    }

    while (user)
    {
        if (strncmp(user->name, name, strlen(name)) == 0)
        {
            return user;
        }
        user = user->next;
    }
    return NULL;
}

int user_mail_in(mail_user_t *user, mail_t *mail)
{
    mail_t *mail_in = NULL;

    mail_in = malloc(sizeof(mail_t));
    if (!mail_in)
    {
        printf("%s %d: fail to malloc\n", __func__, __LINE__);
        return -1;
    }
    *mail_in = *mail;
    mail_in->next = NULL;

    if (user->mail_list == NULL)
    {
        user->mail_list = mail_in;
    }
    else
    {
        mail_t *last = user->mail_list;
        while (last->next) {
            last = last->next;
        }
        last->next = mail_in;
    }
    return 1;
}

int user_mail_out(mail_user_t *user, mail_t *mail)
{
    mail_t *mail_out = user->mail_list;
    if (!mail_out) //链表为空
    {
        return 0;
    }
    *mail = *mail_out; //取数据
    user->mail_list = mail_out->next; //指向下一个数据
    free(mail_out); //释放已取出的数据
    return 1;
}