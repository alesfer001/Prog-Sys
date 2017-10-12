#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int p[2];
  pipe(p);

  int i=0;
  while(1){
    write(p[1], "X", 1);
    printf("%d\n", i); // 65 535 bytes
    i++;
  }

  return 0;
}
