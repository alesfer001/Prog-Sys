#ifndef ANALYSE
#define ANALYSE

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define NB_ARGS 50
#define TAILLE_ID 500

typedef enum expr_t {
  VIDE,	         		// Commande vide 
  SIMPLE,        		// Commande simple 
  SEQUENCE,      		// Séquence (;) 
  SEQUENCE_ET,   		// Séquence conditionnelle (&&) 
  SEQUENCE_OU,   		// Séquence conditionnelle (||) 
  BG,	         		// Tache en arriere plan 
  PIPE,	         		// Pipe 
  REDIRECTION_I, 		// Redirection entree 
  REDIRECTION_O, 		// Redirection sortie standard 
  REDIRECTION_A, 		// Redirection sortie standard, mode append 
  REDIRECTION_E, 		// Redirection sortie erreur 
  REDIRECTION_EO,		// Redirection sorties erreur et standard 
} expr_t;

typedef struct Expression {
  expr_t type;
  struct Expression *gauche;
  struct Expression *droite;
  char   **arguments;
} Expression;

extern int yyparse(void);
Expression *ConstruireNoeud (expr_t, Expression *, Expression *, char **);
char **AjouterArg (char **, char *);
char **InitialiserListeArguments (void);
int LongueurListe(char **);
void EndOfFile(void);

void yyerror (char *s);
Expression *ExpressionAnalysee;
extern int status;

#endif /* ANALYSE */
