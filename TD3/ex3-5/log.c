#define _POSIX_C_SOURCE 1

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  //int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  FILE* file = fopen(argv[1], "w");
  int p[2];
  pipe(p);

  if(fork() == 0){ /* Fils */
    close(p[0]);
    dup2(p[1], 1);
    close(p[1]);

    execvp(argv[2], argv + 2);
    return -1;
  }

  /* Pere */
  close(p[1]);
  char c;
  FILE* fp0 = fdopen(p[0], "r");
  while(/*read(p[0], &c, 1)*/ fread(&c, 1, 1, fp0)){
    //write(fd, &c, 1);
    //write(1, &c, 1);
    fwrite(&c, 1, 1, file);
    fwrite(&c, 1, 1, stdout);
  }
  fclose(file);
  fclose(fp0);

  return 0;
}
