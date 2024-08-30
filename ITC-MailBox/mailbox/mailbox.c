/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/ITC-MailBox
 * @LastEdit: 2024-05-09
 * @FilePath: ./mailbox/mailbox.c
 * @Description: 线程邮箱核心功能
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "mailbox.h"
#include "mailbox_user.h"


//获取当前线程用户名
static const char *get_my_name(mail_box_t *box)
{
    mail_user_t *user = box->user_list;

    while (user)
    {
        if (user->tid == pthread_self())
        {
            return user->name;
        }
        user = user->next;
    }
    return NULL;
}

//创建邮箱
mail_box_t *mailbox_create(void)
{
    int ret = 0;
    mail_box_t *box = NULL;

    box = malloc(sizeof(mail_box_t));
    if (!box)
    {
        printf("%s %d: fail to malloc\n", __func__, __LINE__);
        return NULL;
    }

    ret = pthread_mutex_init(&box->mutex, NULL);
    if (ret)
    {
        printf("%s %d: fail to pthread_mutex_init\n", __func__, __LINE__);
        free(box);
        return NULL;
    }
    box->user_list = NULL;
    printf("mail box create\n");
    return box;
}

//销毁邮箱
void mailbox_destroy(mail_box_t *box)
{
    pthread_mutex_destroy(&box->mutex);
    free(box);
    printf("mail box destroy\n");
}

//注册用户
int mailbox_regester_user(mail_box_t *box, const char *user_name, thread_function func)
{
    int ret = 0;
    mail_user_t *user = NULL;

    user = malloc(sizeof(mail_user_t));
    if (!user)
    {
        printf("%s %d: fail to malloc\n", __func__, __LINE__);
        return -1;
    }

    user->next = NULL;
    user->mail_list = NULL;
    strcpy(user->name, user_name);
    pthread_mutex_lock(&box->mutex);
    user_add(&box->user_list, user);
    pthread_mutex_unlock(&box->mutex);
    ret = pthread_create(&user->tid, NULL, func, (void*)&box);
    if (ret)
    {
        printf("%s %d: fail to pthread_create\n", __func__, __LINE__);
        free(user);
        return -1;
    }

    printf("register user to mail box: \"%s\"\n", user_name);
    return 0;
}

//注销用户
void mailbox_unregester_user(mail_box_t *box, const char *user_name)
{
    mail_user_t *user = NULL;

    user = user_find(box->user_list, user_name);
    if (user)
    {
        //printf("%s wait thread stop\n", __func__);
        pthread_join(user->tid, NULL);
        pthread_mutex_lock(&box->mutex);
        user_delete(&box->user_list, user);
        pthread_mutex_unlock(&box->mutex);
        free(user);
        printf("unregister user from mail box: \"%s\"\n", user_name);
    }
}

//发送邮件：将消息发往box邮箱的receiver用户
int send_mail(mail_box_t *box, const char *receiver, mail_data_t data)
{
    int ret = 0;
    mail_t *mail = NULL;
    const char *name = get_my_name(box);

    mail = malloc(sizeof(mail_t));
    if (!mail)
    {
        printf("%s %d: fail to malloc\n", __func__, __LINE__);
        return -1;
    }
    //查找接收者
    mail_user_t *user = user_find(box->user_list, receiver);
    if (!user)
    {
        printf("%s %d: fail to find receiver user\n", __func__, __LINE__);
        free(mail);
        return -1;
    }
    //填充信息
    if (name)
    {
        strcpy(mail->sender_name, name);
    }
    if (data)
    {
        strcpy(mail->data, data);
    }
    pthread_mutex_lock(&box->mutex);
    ret = user_mail_in(user, mail);
    pthread_mutex_unlock(&box->mutex);
    return ret;
}

//接收邮件：将消息取出到data，发件人取出到sender
int receive_mail(mail_box_t *box, char *sender, mail_data_t data)
{
    int ret = -1;

    //查找接收者
    mail_user_t *user = user_find(box->user_list, get_my_name(box));
    if (!user)
    {
        printf("%s %d: fail to find receiver user\n", __func__, __LINE__);
    }
    else //如果找到了
    {
        ret = 0;
        if (user->mail_list) //如果有消息
        {
            mail_t *mail = NULL;
            mail = malloc(sizeof(mail_t));
            if (!mail)
            {
                printf("%s %d: fail to malloc\n", __func__, __LINE__);
                return -1;
            }
            pthread_mutex_lock(&box->mutex);
            ret = user_mail_out(user, mail);
            pthread_mutex_unlock(&box->mutex);
            if (ret > 0)
            {
                if (sender)
                {
                    strcpy(sender, mail->sender_name);
                }
                if (data)
                {
                    strcpy(data, mail->data);
                }
            }
            free(mail);
        }
    }
    return ret;
}
