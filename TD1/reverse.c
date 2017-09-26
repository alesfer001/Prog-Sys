#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv){
  int in_fd = open(argv[1], O_RDONLY);
  int out_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

  int size_file = lseek(in_fd, 0, SEEK_END);

  char x;
  for(int i=0; i<size_file; i++){
    lseek(in_fd, size_file-i-1, SEEK_SET);
    read(in_fd, &x, sizeof(char));
    write(out_fd, &x, sizeof(char));
  }

  close(in_fd);
  close(out_fd);

  return 0;
}
