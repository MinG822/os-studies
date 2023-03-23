#include <pthread.h>
#include <stdio.h>

#include <stdlib.h>

int sum = 0;
void *runner(void *param);

int main(int argc, char *argv[])
{
  printf("main\n");
  #define NUM_THREADS 10
  pthread_t workers[NUM_THREADS];
  pthread_attr_t attrs[NUM_THREADS];

  for (int i = 0; i < NUM_THREADS; i++)
  {
    pthread_attr_init(&attrs[i]);
    pthread_create(&workers[i], &attrs[i], runner, argv[1]);
  }

  printf("before join pthread\n");
  for (int i = 0; i < NUM_THREADS; i++)
    pthread_join(workers[i], NULL);
  
  printf("sum = %d\n", sum);
  return 0;
}

void *runner(void *param)
{
  printf("runner\n");
  int i, upper = atoi(param);
  for (i = 1; i <= upper; i++)
    sum += i;
  
  pthread_exit(0);
}
