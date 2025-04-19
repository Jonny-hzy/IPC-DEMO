/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/IPC-Signal
 * @LastEdit: 2025-04-19
 * @FilePath: receiver.c
 * @Description: Signal接收端测试
 */
 #include <stdio.h>
 #include <signal.h>
 #include <unistd.h>
 #include <sys/time.h> 
 
 static unsigned long systick = 0;

 unsigned long get_sys_tick_ms(void)
 {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec*1000 + tv.tv_usec/1000);
 }

 void sigint_handler(int sig)
 {
    if (sig == SIGUSR1) {
       printf("Receiver: received Signal: SIGUSR1\n");
    } else if (sig == SIGINT) {
       printf("Receiver: received Signal: SIGINT\n");
    }
 }
 
 int main()
 {
   systick = get_sys_tick_ms();
   signal(SIGUSR1, sigint_handler);
   signal(SIGINT, sigint_handler);
   while(1) {
      printf("Receiver: loop (tick=%lums)\n", get_sys_tick_ms()-systick);
      sleep(60);
   }
   printf("Receiver: exit (tick=%lums)\n", get_sys_tick_ms()-systick);
   return 0;
 }