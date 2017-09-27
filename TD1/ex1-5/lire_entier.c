#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){

  int fd = open(argv[1], O_RDONLY);
  int pos = atoi(argv[2]);

  unsigned int val;
  lseek(fd, pos * sizeof(unsigned int), SEEK_SET);
  read(fd, &val, sizeof(unsigned int));
  printf("%u\n", val);

  close(fd);
  return 0;
}
