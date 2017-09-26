#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv){

  unsigned int n = atoi(argv[1]);

  int fd = open("toto", O_CREAT | O_WRONLY | O_TRUNC, 0777);

  for(unsigned int i=0; i<n; i++){
    write(fd, &i, sizeof(i));
  }

  close(fd);
  return 0;
}
