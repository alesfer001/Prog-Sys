#include <stdio.h>

int main(){

  char buf;
  while(fread(&buf , 1, 1, stdin) > 0){
    fwrite(&buf, 1, 1, stdout);
  }
  return 0;
}
