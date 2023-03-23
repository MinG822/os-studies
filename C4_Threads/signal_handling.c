// https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-pthread-kill-send-signal-thread
// https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-sigaction-examine-change-signal-action#rtsigac__trs1
// https://stackoverflow.com/questions/22947430/posix-pthread-kill
#include <pthread.h>
#include <signal.h> 
#include <stdio.h>
#include <stdlib.h>

int sum;
void *runner(void *param);

int main(int argc, char *argv[])
{
  printf("main\n");
  pthread_t tid;
  pthread_attr_t attr;
  int status;

  pthread_attr_init(&attr);
  status = pthread_create(&tid, &attr, runner, argv[1]);
  printf("status after created = %d\n", status);

  if ( status <  0) {                                                            
    perror("pthread_create failed");                                            
    exit(1);                                                                    
  } 

  sleep(3);

  status = pthread_kill(tid, SIGUSR2);
  printf("status after killed = %d\n", status);

  if ( status <  0)                                                              
    perror("pthread_kill failed");  

  status = pthread_join(tid, NULL);
  printf("status after joined = %d\n", status);
  if ( status <  0)                                                              
    perror("pthread_join failed"); 

  printf("sum = %d\n", sum);
  return 0;
}

void *runner(void *param)
{
  printf("runner\n");
  sigset_t set;

  sigemptyset(&set);
  if (sigaddset(&set, SIGUSR1) == -1) {
    perror("Sigaddset error");
    pthread_exit(0);
  }

  int i, upper = atoi(param);
  sum = 0;
  for (i = 1; i <= upper; i++)
    sum += i;

  pthread_exit(0);
}
