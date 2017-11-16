#ifndef EXECUTE_AVANT_DELAI_H
#define EXECUTE_AVANT_DELAI_H

int
executer_avant_delai( void (*fun)(void *), void *parametre, int delai_en_seconde);
/* 
 * donne un delai born� en seconde � l'�valuation de fun(parametre) 
 * utilise le timer de la fonction alarm()
 * retourne 0 si l'�valuation a �t� interrompue, 1 autrement.
 * le delai 0 n'est pas pris en compte (execution normale)
 */

#endif
