/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO
 * @LastEdit: 2024-05-09
 * @FilePath: ./mailbox/mailbox_user.h
 * @Description: 线程邮箱用户管理接口
 */

#ifndef __MAILBOX_USER_H__
#define __MAILBOX_USER_H__

#include "mailbox.h"


void user_add(mail_user_t **user_list, mail_user_t *user);
void user_delete(mail_user_t **user_list, mail_user_t *user);
mail_user_t *user_find(mail_user_t *user_list, const char *name);
int user_mail_in(mail_user_t *user, mail_t *mail);
int user_mail_out(mail_user_t *user, mail_t *mail);

#endif