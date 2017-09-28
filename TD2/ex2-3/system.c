#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int System(char* commande);

int main(int argc, char** argv){

  System(argv[1]);

  return 0;
}

int System(char* commande){
  if(fork() == 0){
    execlp("bash", "bash", "-c", commande, NULL);
    return -1;
  }
  wait(NULL);
  return 1;
}
