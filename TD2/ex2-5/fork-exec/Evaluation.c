#include "Shell.h"
#include "Evaluation.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

void
verifier(int cond, char *s)
{
  if (!cond)
    {
      perror(s);
      exit(1);
    }
}

int executer_simple(Expression *e, char* file, int bg){
  if(fork() == 0){
    if(file){
      int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if(fd>0){
        dup2(fd, 1);
        close(fd);
      }
    }
    execvp(e->arguments[0], e->arguments);
    perror(e->arguments[0]);
    return -1;
  }
  int status = 0;
  if(!bg){
    wait(&status);
  }
  /*while(waitpid(-1, &status, WNOHANG) > 0)*/
  return status;
}

int
evaluer_expr(Expression *e)
{
  int bg=0;
  char *file = NULL;
  if(e->type == VIDE){
    return 0;
  }
  if(e->type == BG){
    bg = 1;
    e = e->gauche;
  }
  if(e->type == REDIRECTION_O){
    file = e->arguments[0];
    e = e->gauche;
  }
  if(e->type == SIMPLE){
    return executer_simple(e, file, bg);
  }
  if(e->type == SEQUENCE){
    evaluer_expr(e->gauche);
    evaluer_expr(e->droite);
  }

  return -1;
}
