#include <stdio.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>
#include "executer-avant-delai.h"

jmp_buf env;

void myhandler(int signum);

int executer_avant_delai(void (*fun)(void *), void *parametre, int delai_en_seconde){
  struct sigaction act;
  act.sa_handler = myhandler;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);
  sigaction(SIGALRM, &act, NULL);

  alarm(delai_en_seconde);

  if(!sigsetjmp(env, 1)){
    fun(parametre);
    return 1;
  }

  return 0;
}

void myhandler(int signum){
  printf("Timeout\n");
  siglongjmp(env, 1);
}
