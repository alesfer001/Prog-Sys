#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){

  int status;
  printf("*** execution\n");
  if(fork() == 0){
    execvp(argv[1], argv+1);
    return -1;
  }
  wait(&status);
  printf("*** code de retour : %d\n", status);

  return 0;
}
