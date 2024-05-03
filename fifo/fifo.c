#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "fifo.h"


//配置日志等级
#define LOG_LVL_NONE        0
#define LOG_LVL_ERR         1
#define LOG_LVL_WARN        2
#define LOG_LVL_INFO        3
#define LOG_LVL_DBG         4
#define LOG_LVL             LOG_LVL_ERR

#if (LOG_LVL >= LOG_LVL_ERR)
#define FIFO_LOGE(...)              printf("FifoError: "__VA_ARGS__)
#else
#define FIFO_LOGE(...)
#endif
#if (LOG_LVL >= LOG_LVL_WARN)
#define FIFO_LOGW(...)              printf("FifoWarn : "__VA_ARGS__)
#else
#define FIFO_LOGW(...)
#endif
#if (LOG_LVL >= LOG_LVL_INFO)
#define FIFO_LOGI(...)              printf("FifoInfo : "__VA_ARGS__)
#else
#define FIFO_LOGI(...)
#endif
#if (LOG_LVL >= LOG_LVL_DBG)
#define FIFO_LOGD(...)              printf("FifoDebug: "__VA_ARGS__)
#else
#define FIFO_LOGD(...)
#endif


struct fifo_para
{
    int read_fd;
    int write_fd;
};

static struct fifo_para fifo =
{
    .read_fd = -1,
    .write_fd = -1,
};


#if (FIFO_SUPPORT_READ)
int fifo_read_fd_open(void)
{
    if (fifo.read_fd < 0)
    {
        fifo.read_fd = open(FIFO_NAME, O_RDONLY|O_NONBLOCK);
        if (fifo.read_fd < 0)
        {
            FIFO_LOGE("%s:%d, open error.(%s)\n", __func__, __LINE__, strerror(errno));
            return fifo.read_fd;
        }
        FIFO_LOGI("%s:%d, open ok fd=%d.\n", __func__, __LINE__, fifo.read_fd);
    }
    return 0;
}
#endif

#if (FIFO_SUPPORT_WRITE)
int fifo_write_fd_open(void)
{
    if (fifo.write_fd < 0)
    {
        fifo.write_fd = open(FIFO_NAME, O_WRONLY|O_NONBLOCK);
        if (fifo.write_fd < 0)
        {
            FIFO_LOGE("%s:%d, open error.(%s)\n", __func__, __LINE__, strerror(errno));
            return fifo.write_fd;
        }
        FIFO_LOGI("%s:%d, open ok fd=%d.\n", __func__, __LINE__, fifo.write_fd);
    }
    return 0;
}
#endif

int fifo_create(void)
{
    if (access(FIFO_NAME, F_OK)) // if fifo file is not exist.
    {
        if (mkfifo(FIFO_NAME, 0777) < 0)
        {
            FIFO_LOGE("%s:%d, create %s fail\n", __func__, __LINE__, FIFO_NAME);
            return -1;
        }
        FIFO_LOGI("%s:%d, fifo %s is created\n", __func__, __LINE__, FIFO_NAME);
    }
    else
    {
        FIFO_LOGI("%s:%d, fifo %s already exist\n", __func__, __LINE__, FIFO_NAME);
    }
}

int fifo_destroy(void)
{
    if (!access(FIFO_NAME, F_OK)) // if fifo file is exist.
    {
        remove(FIFO_NAME);
        FIFO_LOGI("%s:%d, fifo %s removed\n", __func__, __LINE__, FIFO_NAME);
    }
    else
    {
        FIFO_LOGI("%s:%d, fifo %s is not exist\n", __func__, __LINE__, FIFO_NAME);
    }
}

int fifo_init(void)
{
    #if (FIFO_SUPPORT_READ)
    fifo_create();
    fifo_read_fd_open();
    #endif

    return 0;
}

int fifo_deinit(void)
{
    #if (FIFO_SUPPORT_READ)
    if (fifo.read_fd > 0)
    {
        close(fifo.read_fd);
        fifo.read_fd = -1;
    }
    fifo_destroy();
    #endif

    #if (FIFO_SUPPORT_WRITE)
    if (fifo.write_fd > 0)
    {
        close(fifo.write_fd);
        fifo.write_fd = -1;
    }
    #endif

    return 0;
}

#if (FIFO_SUPPORT_READ)
int fifo_read(char *buf, int len)
{
    int rlen = 0;

    if (fifo_read_fd_open())
    {
        return -1;
    }

    rlen = read(fifo.read_fd, buf, len);
    if (rlen <= 0)
    {
        if (rlen < 0)
        {
            FIFO_LOGD("%s:%d, read error.(%s)\n", __func__, __LINE__, strerror(errno));
        }
        return 0;
    }
    FIFO_LOGD("%s:%d, read ok len=%d.\n", __func__, __LINE__, rlen);

    return rlen;
}
#endif

#if (FIFO_SUPPORT_WRITE)
int fifo_write(const char *buf, int len)
{
    int wlen = 0;

    if (fifo_write_fd_open())
    {
        return 0;
    }

    wlen = write(fifo.write_fd, buf, len);
    if (wlen <= 0)
    {
        close(fifo.write_fd);
        fifo.write_fd = -1;
        FIFO_LOGE("%s:%d, write error.(%s)\n", __func__, __LINE__, strerror(errno));
        return -1;
    }
    FIFO_LOGD("%s:%d, write ok len=%d.\n", __func__, __LINE__, wlen);

    return wlen;
}
#endif

