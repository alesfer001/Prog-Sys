#ifndef EXECUTE_AVANT_DELAI_H
#define EXECUTE_AVANT_DELAI_H

int
executer_avant_delai( void (*fun)(void *), void *parametre, int delai_en_seconde);
/* 
 * donne un delai borné en seconde à l'évaluation de fun(parametre) 
 * utilise le timer de la fonction alarm()
 * retourne 0 si l'évaluation a été interrompue, 1 autrement.
 * le delai 0 n'est pas pris en compte (execution normale)
 */

#endif
