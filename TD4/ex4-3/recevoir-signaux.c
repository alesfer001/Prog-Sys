#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void myhandler(int signum);

int main(){
  printf("PID: %d\n", getpid());
  struct sigaction act;
  act.sa_handler = myhandler;
  act.sa_flags = SA_RESETHAND;
  sigemptyset(&act.sa_mask);
  for(int i=1; i<32; i++){
    sigaction(i, &act, NULL);
  }
  while(1) pause();

  return 0;
}

void myhandler(int signum){
  printf("Signal Number #%d\n", signum);
}
