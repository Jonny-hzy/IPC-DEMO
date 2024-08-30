/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/ITC-MailBox
 * @LastEdit: 2024-05-09
 * @FilePath: ./mailbox/mailbox.h
 * @Description: 线程邮箱对外API
 */

#ifndef __MAILBOX_H__
#define __MAILBOX_H__

#include <pthread.h>


//定义邮件信息数组长度（字节）
#define MAX_NAME_LENGTH 64
//定义线程名称最大长度
#define MAX_DATA_LENGTH 128

typedef char mail_data_t[MAX_DATA_LENGTH];
typedef void *(*thread_function)(void *);

//邮件
typedef struct mail
{
    struct mail *next;
    char sender_name[MAX_NAME_LENGTH];
    mail_data_t data; //邮件信息
}mail_t;

//用户
typedef struct mail_user
{
    struct mail_user *next;
    pthread_t tid;
    char name[MAX_NAME_LENGTH];
    mail_t *mail_list;
}mail_user_t;

//邮箱
typedef struct mail_box
{
    pthread_mutex_t mutex;
    mail_user_t *user_list;
}mail_box_t;

//创建邮箱
mail_box_t *mailbox_create(void);
//销毁邮箱
void mailbox_destroy(mail_box_t *box);
//注册用户
int mailbox_regester_user(mail_box_t *box, const char *user_name, thread_function func);
//注销用户
void mailbox_unregester_user(mail_box_t *box, const char *user_name);
//发送邮件：将消息发往box邮箱的receiver用户
int send_mail(mail_box_t *box, const char *receiver, mail_data_t data);
//接收邮件：将消息取出到data，发件人取出到sender
int receive_mail(mail_box_t *box, char *sender, mail_data_t data);

#endif