#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

void f();
int essayer(void (*f)(), int signum);
void myhandler(int signum);
void bar();

jmp_buf env;

int main(){
  int r;
  r = essayer(bar, SIGSEGV);
  if(r == 0)
    printf("L’exécution de f s’est déroulée sans problème\n");
  else
    printf("L’exécution de f a échoué\n");

  return 0;
}

void f(){
  //*((int *)NULL) = 1;
}

void bar(){
  essayer(f, SIGSEGV);
  *((int *)NULL) = 1;
}

int essayer(void (*f)(), int signum){
  struct sigaction act, old;
  act.sa_flags = 0;
  act.sa_handler = myhandler;
  sigemptyset(&act.sa_mask);

  sigaction(signum, &act, &old);

  int status;
  if(!sigsetjmp(env, 1)){
    f();
    status = 0;
  }
  else{
    status = -1;
  }

  sigaction(signum, &old, NULL);

  return status;
}

void myhandler(int signum){
  siglongjmp(env, 1);
}
