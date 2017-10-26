#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void print(int signum);

int main(){
  struct sigaction my_action; //, old
  my_action.sa_handler = print;
  my_action.sa_flags = SA_RESETHAND;
  sigemptyset(&my_action.sa_mask);
  sigaction(SIGINT, &my_action, NULL /* old */);

  while(1) pause();

  return 0;
}

void print(int signum){
  printf("ctrl-c\n");
  //sigaction(SIGINT, &old, NULL);
}
