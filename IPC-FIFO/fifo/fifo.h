/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/IPC-FIFO
 * @LastEdit: 2024-04-30
 * @FilePath: fifo\fifo.h
 * @Description: fifo API重封装
 */
#ifndef __FIFO_H__
#define __FIFO_H__


//配置管道名
//重要：reader和writer的管道名称需要保持统一！
//#define FIFO_NAME                   "/tmp/.myfifo"
#define FIFO_NAME                   ".myfifo"

#define FIFO_WRITE                  0x01
#define FIFO_READ                   0x02
//配置管道的读写功能
#define FIFO_SUPPORT_CONFIG         (FIFO_READ|FIFO_WRITE)


#define FIFO_SUPPORT_READ           (FIFO_SUPPORT_CONFIG & FIFO_READ)
#define FIFO_SUPPORT_WRITE          (FIFO_SUPPORT_CONFIG & FIFO_WRITE)


/*
    fifo初始化
    reader:包含 fifo_create() 和 fifo_open()
    writer:仅含 fifo_open()
*/
int fifo_init(void);
/*
    fifo退出
    reader:包含 fifo_destroy() 和 fifo_close()
    writer:仅含 fifo_close()
*/
int fifo_exit(void);
/*
    fifo读取
    返回值：＞0：成功读到的长度；=0：未读到数据；＜0：出错
*/
#if (FIFO_SUPPORT_READ)
int fifo_read(char *buf, int len);
#endif
/*
    fifo写入
    返回值：＞0：成功写入的长度；＜0：出错
*/
#if (FIFO_SUPPORT_WRITE)
int fifo_write(const char *buf, int len);
#endif

#endif /* __FIFO_H__ */

