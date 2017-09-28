#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char** argv){
  int N = atoi(argv[1]);
  for(int i=0; i<N; i++){
    if(fork() == 0){
      printf("fils %d (%d)\n", i, getpid());
      return 0;
    }
  }

  for(int i=0; i<N; i++){
    wait(NULL);
  }

  return 0;
}
