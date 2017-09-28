#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
  pid_t pid = fork();
  if(pid == 0){
    //sleep(1);
    printf("fils: pid= %d, ppid= %d\n", getpid(), getppid());
  }
  else{
    //wait(NULL);
    printf("père: pid= %d, childpid= %d\n", getpid(), pid);
    /*sleep(10);
    wait(NULL);*/
  }

  return 0;
}
