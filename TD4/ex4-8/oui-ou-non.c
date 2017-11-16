#include "executer-avant-delai.h"

#include <stdio.h>
#include <stdlib.h>

void
oui_ou_non(void *reponse)
{
  char c = getchar();
  *(int *)reponse = c == 'o' || c == 'O' ;
}

int
main()
{

  int rep ;

  printf(" oui ou non ? ");

  if( executer_avant_delai(oui_ou_non,&rep,5))
    printf("reponse : %c\n", rep == 1 ? 'O' : 'N');
  else
    printf("pas de réponse\n");

  printf(" oui ou non ? ");
  
  if( executer_avant_delai(oui_ou_non,&rep,5))
    printf("reponse : %c\n", rep == 1 ? 'O' : 'N');
  else
    printf("pas de réponse\n");

  return EXIT_SUCCESS;

}
