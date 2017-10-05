#include "Shell.h"
#include "Affichage.h"

#include <stdio.h>


char *chaine_type[] = {
  "VIDE",	         	// Commande vide 
  "SIMPLE",        		// Commande simple 
  "SEQUENCE",      		// Séquence (;) 
  "SEQUENCE_ET",   		// Séquence conditionnelle (&&) 
  "SEQUENCE_OU",   		// Séquence conditionnelle (||) 
  "BG",	         		// Tache en arriere plan 
  "PIPE",	         	// Pipe 
  "REDIRECTION_I", 		// Redirection entree 
  "REDIRECTION_O", 		// Redirection sortie standard 
  "REDIRECTION_A", 		// Redirection sortie standard, mode append 
  "REDIRECTION_E", 		// Redirection sortie erreur 
  "REDIRECTION_EO"};



void indenter_vide(int indentation, int trait){
  for(int i = 1; i<= indentation + trait; i++)
    if ( i % trait == 0)
      putchar('|');
    else
      putchar(' ');
}

void indenter(int indentation, int trait){
  for(int i = 1; i< indentation; i++)
    if ( i % trait == 0)
      putchar('|');
    else
      putchar(' '); 
  putchar('+');
  for(int i = 2; i< trait; i++)
    if ( indentation % trait == 0)
      putchar('-');
  putchar('>');
}



  
void afficher_exprL(Expression *e, int indentation, int trait)
{
  if (e == NULL) return ;

  switch(e->type){

  case VIDE :
    indenter(indentation,trait);
    printf("%s\n", chaine_type[e->type]);
    break ;
    
  case SIMPLE :
    indenter(indentation,trait);
    printf("%s ", chaine_type[e->type]);
    for(int i=0; e->arguments[i] != NULL;i++)
      printf("[%s]",e->arguments[i]);
    putchar('\n');
    break;

  case REDIRECTION_I: 	
  case REDIRECTION_O: 	
  case REDIRECTION_A: 	
  case REDIRECTION_E: 	
  case REDIRECTION_EO :
    indenter(indentation,trait);    
    printf("%s fichier [%s]\n",chaine_type[e->type], e->arguments[0]);
    afficher_exprL(e->gauche, indentation + trait, trait);
    break;
  case BG:
    indenter(indentation,trait);
    printf("%s\n", chaine_type[e->type]);
    afficher_exprL(e->gauche, indentation + trait, trait);
    break;
  default :

    indenter(indentation,trait);
    printf("%s\n", chaine_type[e->type]);
    afficher_exprL(e->gauche, indentation + trait, trait);
    indenter_vide(indentation,trait);putchar('\n');
    afficher_exprL(e->droite, indentation + trait, trait);      
  }
}



void afficher_expr(Expression *e)
{
  afficher_exprL(e,4,4);
}
