#define XOPEN_SOURCE  700
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>

int main(){
  for(int i=1; i<32; i++){
    printf("%d : %s\n", i, strsignal(i));
  }
}
