/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/IPC-Signal
 * @LastEdit: 2025-04-19
 * @FilePath: sender.c
 * @Description: Signal发送端测试
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    pid_t pid = 0;
    if (argc < 2) {
        printf("Usage: %s <pid>\n", argv[0]);
        return 1;
    }
    pid = atoi(argv[1]);
    printf("Sender: send SIGUSR1 to %d\n", pid);
    kill(pid, SIGUSR1);
    sleep(2);
    printf("Sender: send SIGINT to %d\n", pid);
    kill(pid, SIGINT);
    sleep(2);
    printf("Sender: send SIGKILL to %d\n", pid);
    kill(pid, SIGKILL);
    return 0;
}