#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  int fd = open("error", O_CREAT | O_WRONLY | O_APPEND, 0644);
  dup2(fd, 2);
  close(fd);

  printf("Hello World!\n");
  fprintf(stderr, "Bye bye\n");
}
