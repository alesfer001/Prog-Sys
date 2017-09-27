#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){

  int fd = open(argv[1], O_RDONLY);

  unsigned int x;
  //char buf[4];
  while(read(fd, &x /*buf*/, sizeof(unsigned int)) > 0){
    printf("%u\n", x);
    //printf("%u\n", *(unsigned int *) buf);
  }

  close(fd);
  return 0;
}
