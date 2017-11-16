#include <signal.h>
#include <stdio.h>

volatile char *a=NULL, b='x';

void traitant(int s)
{
  printf("signal %d\n", s);
  a = &b;
}

int main()
{
  struct sigaction s;
  char x;
  s.sa_handler = traitant;
  sigemptyset(&s.sa_mask);
  s.sa_flags=0;

  sigaction(SIGSEGV,&s,NULL);

  x = *a;
  printf("fin %c\n",x);
  return 0;
}
