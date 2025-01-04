/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/MsgQue
 * @LastEdit: 2025-01-04
 * @FilePath: msg\msg.h
 * @Description: MessageQueues API重封装
 */
#ifndef __MSG_H__
#define __MSG_H__


//配置消息队列的匹配KEY
//重要：reader和writer的 KEY_FILE_PATH 和 KEY_NUMBER 需要完全一致
//KEY_FILE_PATH 需要真实存在，文件或目录皆可，对权限无要求
//KEY_NUMBER 有效部分是小于256的部分
#define KEY_FILE_PATH               "/mnt"
#define KEY_NUMBER                  123


#define MSG_SIZE    128 //消息最大长度（bytes）


/*
    msg创建
    返回值：msgid（消息队列通信ID）
*/
int msg_create(void);
/*
    msg销毁
    返回值：0：成功；-1：失败
*/
int msg_destroy(int msgid);
/*
    msg写入
    返回值：＞0：成功写入的长度；＜0：出错
*/
int msg_write(int msgid, const char *buf, unsigned int len);
/*
    msg写入（带类型）
    返回值：＞0：成功写入的长度；＜0：出错
*/
int msg_write_with_type(int msgid, const char *buf, unsigned int len, long type);
/*
    msg读取
    返回值：＞0：成功读到的长度；=0：未读到数据；＜0：出错
*/
int msg_read(int msgid, char *buf, unsigned int len);
/*
    msg写入（带类型）
    返回值：＞0：成功写入的长度；＜0：出错
*/
int msg_read_with_type(int msgid, char *buf, unsigned int len, long type);

#endif /* __MSG_H__ */
