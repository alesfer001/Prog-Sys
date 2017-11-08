
#ifndef DEBUG_IS_DEF
#define DEBUG_IS_DEF


// La fonction PRINT_DEBUG permet d'afficher selectivement certains messages
// de debug. Le choix du type des messages s'effectue au moyen d'une
// chaine contenant des filtres. Ces filtres sont :
//
//      '+' -- active tous les messages de debug
//      'd' -- opérations ayant trait au disque (chargement/sauvegarde de map)
//      'm' -- gestion mémoire
//      'g' -- opérations graphiques
//      'a' -- routines d'animation
//      't' -- gestion des temporisateurs
//      'c' -- gestion des collisions
//      'p' -- information de profiling
//      's' -- gestion sur smartphones

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void debug_init (char *flags);
int debug_enabled (char flag);

extern char *debug_flags;

static inline void PRINT_DEBUG (char flag, char *format, ...)
{
  if (debug_flags != NULL && debug_enabled (flag)) {
    va_list ap;

    va_start (ap, format);
    vfprintf (stderr, format, ap);
    va_end (ap);
  }
}


#endif
