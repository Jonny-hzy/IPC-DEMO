/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO
 * @LastEdit: 2024-05-16
 * @FilePath: shared_memory/shm.c
 * @Description: 共享内存API重封装
 */
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#include "shm.h"


//配置日志等级
#define LOG_LVL_NONE            0
#define LOG_LVL_ERR             1
#define LOG_LVL_WARN            2
#define LOG_LVL_INFO            3
#define LOG_LVL_DBG             4
#define LOG_LVL                 LOG_LVL_WARN

#define LOG_TAG                 "SHM"
#if (LOG_LVL >= LOG_LVL_ERR)
#define LOGE(...)               printf(LOG_TAG "Error: "__VA_ARGS__)
#else
#define LOGE(...)
#endif
#if (LOG_LVL >= LOG_LVL_WARN)
#define LOGW(...)               printf(LOG_TAG "Warn : "__VA_ARGS__)
#else
#define LOGW(...)
#endif
#if (LOG_LVL >= LOG_LVL_INFO)
#define LOGI(...)               printf(LOG_TAG " Info : "__VA_ARGS__)
#else
#define LOGI(...)
#endif
#if (LOG_LVL >= LOG_LVL_DBG)
#define LOGD(...)               printf(LOG_TAG " Debug: "__VA_ARGS__)
#else
#define LOGD(...)
#endif


int shm_create_with_key(unsigned int length, const char *key_file_path, int key_number)
{
    int shmid;
    int ret;
    key_t key;

    key = ftok(key_file_path, key_number);
    LOGD("%s key=%d\n", __func__, key);
    if (key < 0)
    {
        LOGE("%s ftok fail (file=%s) (%s)\n", __func__, KEY_FILE_PATH, strerror(errno));
        return key;
    }

    shmid = shmget(key, length, IPC_CREAT|0666);
    if (shmid <= 0)
    {
        LOGE("%s shmget fail (%s)\n", __func__, strerror(errno));
        return shmid;
    }
    LOGD("%s succeed (shmid=%d)\n", __func__, shmid);
}

int shm_create(unsigned int length)
{
    return shm_create_with_key(length, KEY_FILE_PATH, KEY_NUMBER);
}

int shm_destroy(int shmid)
{
    int ret = shmctl(shmid, IPC_RMID, NULL);
    if (ret < 0)
    {
        LOGE("%s shmctl fail (%s)\n", __func__, strerror(errno));
        return ret;
    }
    LOGD("%s succeed (shmid=%d)\n", __func__, shmid);
    return shmid;
}

char *shm_connect(int shmid)
{
    char *mem = shmat(shmid, NULL, 0);
    if (mem <= 0)
    {
        LOGE("%s shmat fail (%s)\n", __func__, strerror(errno));
        return mem;
    }
    LOGD("%s succeed (mem=0x%X)\n", __func__, (int)mem);
    return mem;
}

int shm_disattach(char *mem_addr)
{
    int ret = shmdt(mem_addr);
    if (ret < 0)
    {
        LOGE("%s shmdt fail (%s)\n", __func__, strerror(errno));
        return ret;
    }
    LOGD("%s succeed (mem=0x%X)\n", __func__, (int)mem_addr);
    mem_addr = NULL;
    return ret;
}