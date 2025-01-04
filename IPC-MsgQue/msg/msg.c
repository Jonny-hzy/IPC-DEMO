/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/IPC-MsgQue
 * @LastEdit: 2025-01-04
 * @FilePath: msg\msg.c
 * @Description: MessageQueues API重封装
 */
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "msg.h"

//配置日志等级
#define LOG_LVL_NONE            0
#define LOG_LVL_ERR             1
#define LOG_LVL_WARN            2
#define LOG_LVL_INFO            3
#define LOG_LVL_DBG             4
#define LOG_LVL                 LOG_LVL_ERR

#if (LOG_LVL >= LOG_LVL_ERR)
#define LOGE(...)               printf("MqError: "__VA_ARGS__)
#else
#define LOGE(...)
#endif
#if (LOG_LVL >= LOG_LVL_WARN)
#define LOGW(...)               printf("MqWarn : "__VA_ARGS__)
#else
#define LOGW(...)
#endif
#if (LOG_LVL >= LOG_LVL_INFO)
#define LOGI(...)               printf("MqInfo : "__VA_ARGS__)
#else
#define LOGI(...)
#endif
#if (LOG_LVL >= LOG_LVL_DBG)
#define LOGD(...)               printf("MqDebug: "__VA_ARGS__)
#else
#define LOGD(...)
#endif



//定义消息队列结构体
struct msgbuf {
    long mtype; //消息的类型
    char mtext[MSG_SIZE]; //消息正文
};

int msg_create_with_key(const char *key_file_path, int key_number)
{
    int msgid;
    int ret;
    key_t key;

    key = ftok(key_file_path, key_number);
    LOGD("%s key=%d\n", __func__, key);
    if (key < 0)
    {
        LOGE("%s ftok fail (file=%s) (%s)\n", __func__, KEY_FILE_PATH, strerror(errno));
        return key;
    }

    msgid = msgget(key, IPC_CREAT|0666);
    if (msgid < 0)
    {
        LOGE("%s msgget fail (%s)\n", __func__, strerror(errno));
        return -1;
    }
    LOGD("%s succeed (msgid=%d)\n", __func__, msgid);
    return msgid;
}

int msg_create(void)
{
    return msg_create_with_key(KEY_FILE_PATH, KEY_NUMBER);
}

int msg_destroy(int msgid)
{
    return msgctl(msgid, IPC_RMID, NULL);
}

int msg_write_with_type(int msgid, const char *buf, unsigned int len, long type)
{
    int ret = 0;
    struct msgbuf msg;

    memset(&msg, 0, sizeof(msg));
    msg.mtype = type;
    if (len > MSG_SIZE)
    {
        len = MSG_SIZE;
    }
    memcpy(msg.mtext, buf, len);
    ret = msgsnd(msgid, &msg, len, IPC_NOWAIT);
    if (ret < 0)
    {
        LOGE("%s:%d, send error.(%s)\n", __func__, __LINE__, strerror(errno));
        return -1;
    }
    LOGD("%s:%d, send ok (len=%d type=%ld)\n", __func__, __LINE__, len, type);
    return len;
}

int msg_write(int msgid, const char *buf, unsigned int len)
{
    return msg_write_with_type(msgid, buf, len, 1);
}

int msg_read_with_type(int msgid, char *buf, unsigned int len, long type)
{
    int rlen = 0;
    struct msgbuf msg;

    rlen = msgrcv(msgid, &msg, sizeof(msg.mtext), type, IPC_NOWAIT);
    if (rlen <= 0)
    {
        LOGD("%s:%d, read error.(%s)\n", __func__, __LINE__, strerror(errno));
        return 0;
    }
    if (len > rlen)
    {
        len = rlen;
    }
    memcpy(buf, msg.mtext, len);
    LOGD("%s:%d, read ok len=%d.\n", __func__, __LINE__, len);
    return len;
}

int msg_read(int msgid, char *buf, unsigned int len)
{
    return msg_read_with_type(msgid, buf, len, 1);
}
