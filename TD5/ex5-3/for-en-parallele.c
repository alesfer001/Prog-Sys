#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long volatile k = 0;
const unsigned long MAX = 100 * 1000;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void *for_en_parallele(void *p)
{
  for(unsigned long i=0; i < MAX; i++){
    pthread_mutex_lock(&mut);
    k++;
    pthread_mutex_unlock(&mut);
  }

  return NULL;
}

int
main(int argc, char *argv[])
{

  int n = atoi(argv[1]);
  pthread_t tids[n];

  for(int i = 0; i <n ; i++)
    pthread_create(tids + i, NULL, for_en_parallele, NULL);

  for(int i = 0; i <n ; i++)
    pthread_join(tids[i],NULL);

  printf("%lu\n",k);

  pthread_mutex_destroy(&mut);
  return EXIT_SUCCESS;
}
