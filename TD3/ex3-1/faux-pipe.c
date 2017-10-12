#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

  if(fork() == 0){
    int fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, 1);
    close(fd);
    execlp(argv[1], argv[1], NULL);
    return -1;
  }
  else{
    wait(NULL);
    int fd = open("tmp", O_RDONLY);
    unlink("tmp");
    dup2(fd, 0);
    close(fd);
    execvp(argv[2], argv + 2);
    return -1;
  }
  return 0;
}
