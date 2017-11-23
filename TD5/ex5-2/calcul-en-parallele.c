#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX  100000000
double resultat[MAX];
int nb_threads;

void* calculate(void* strtfnsh);

int
main(int argc, char *argv[])
{
  nb_threads = atoi(argv[1]);
  pthread_t tid[nb_threads];
  int myargs[nb_threads];

  for(int i=0; i<nb_threads; i++){
    myargs[i] = i;
    pthread_create(&tid[i], NULL, calculate, &myargs[i]);
  }

  for(int i=0; i<nb_threads; i++){
    pthread_join(tid[i], NULL);
  }

  return EXIT_SUCCESS;
}

void *calculate(void* arg){
  int rank = *((int*)arg);
  int strt = rank * MAX / nb_threads;
  int fnsh = (rank+1) * MAX / nb_threads;
  for(int k=strt; k < fnsh; k++)
    resultat[k] = atan(tan((double)k));

  return NULL;
}
