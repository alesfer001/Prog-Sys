#include <stdio.h>
#include <setjmp.h>

jmp_buf env;
void f();
void g();

int main(){
  int volatile i = 0;
  setjmp(env);
  printf("%d\n", i);
  i++;
  if(i < 10)
    f();

  return 0;
}

void f(){
  longjmp(env, 1);
}

void g(){
  setjmp(env);
}
