#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *HelloGoodbye(void *p)
{
  printf("%p: bonjour\n", pthread_self());
  sleep(1);
  printf("%p: a bientot\n", pthread_self());

  return NULL;
}

int
main(int argc, char *argv[])
{
  int N = atoi(argv[1]);
  //void* HelloGoodbye(void*);
  pthread_t tid[N];
  for(int i=0; i<N; i++){
    pthread_create(&tid[i], NULL, HelloGoodbye, NULL);
  }

  for(int i=0; i<N; i++){
    pthread_join(tid[i], NULL);
  }

  return EXIT_SUCCESS;
}
