#include <pthread.h>
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
  status = pthread_cancel(tid);
  printf("status after cancel = %d\n", status);

  if ( status <  0)                                                              
    perror("pthread_cancel failed");  

  status = pthread_join(tid, NULL);
  printf("status after joined = %d\n", status);
  if ( status <  0)                                                              
    perror("pthread_join failed"); 

  printf("end");
  return 0;
}

void *runner(void *param)
{
  while (1) {
    printf("runner waiting cancelling\n");
    pthread_testcancel();
    sleep(1);
  }
  pthread_exit(0);
}
