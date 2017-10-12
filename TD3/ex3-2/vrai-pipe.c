#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

  int p[2];
  pipe(p);

  if(fork() == 0){
    close(p[0]);
    dup2(p[1], 1);
    close(p[1]);
    execlp(argv[1], argv[1], NULL);
    return -1;
  }
  else{
    close(p[1]);
    dup2(p[0], 0);
    close(p[0]);
    execvp(argv[2], argv + 2);
    return -1;
  }
  return 0;
}
