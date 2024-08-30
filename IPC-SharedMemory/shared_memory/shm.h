/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/IPC-SharedMemory
 * @LastEdit: 2024-05-16
 * @FilePath: shared_memory/shm.h
 * @Description: 共享内存API重封装
 */
#ifndef __SHM_H__
#define __SHM_H__


//配置共享内存的匹配KEY
//重要：reader和writer的 KEY_FILE_PATH 和 KEY_NUMBER 需要完全一致
//KEY_FILE_PATH 需要真实存在，文件或目录皆可，对权限无要求
//KEY_NUMBER 有效部分是小于256的部分
#define KEY_FILE_PATH               "/tmp"
#define KEY_NUMBER                  123

/*
    共享内存创建(使用本文件的默认KEY)
    参数：
        length:共享内存长度，单位字节
    返回值：
        成功返回共享内存ID，失败返回负数
*/
int shm_create(unsigned int length);

/*
    共享内存创建(使用参数传入的KEY)
    参数：
        length:共享内存长度，单位字节
    返回值：
        成功返回共享内存ID，失败返回负数
*/
int shm_create_with_key(unsigned int length, const char *key_file_path, int key_number);

/*
    共享内存销毁
    参数：
        shmid:共享内存ID
    返回值：
        成功返回0，失败返回负数
*/
int shm_destroy(int shmid);

/*
    共享内存连接
    参数：
        shmid:共享内存ID
    返回值：
        成功返回共享内存地址，失败返回NULL
*/
char *shm_connect(int shmid);

/*
    共享内存断开
    参数：
        mem_addr:共享内存地址
    返回值：
        成功返回0，失败返回-1
*/
int shm_detach(char *mem_addr);

#endif /* __SHM_H__ */

