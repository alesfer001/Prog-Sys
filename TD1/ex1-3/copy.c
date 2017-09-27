#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void perror_and_exit_whenever(int assertion){
  if (assertion)
    {
      perror("");
      exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv){
  int power;
  size_t buffer_size;

  if (argc != 4)
    {
      fprintf(stderr,"%s : <input file name>"
	      " <output filename> <log2 of buffer length> \n", argv[0]);
      return EXIT_FAILURE;
    }

  power = strtoul(argv[3], NULL, 10);
  buffer_size = 1 << power;

  int fd_input = open(argv[1], O_RDONLY);
  int fd_output = open(argv[2], O_WRONLY | O_SYNC);

  char buf[buffer_size];
  while(read(fd_input, buf, buffer_size) > 0){
    write(fd_output, buf, buffer_size);
  }

  close(fd_input);
  close(fd_output);

  return EXIT_SUCCESS;
}
