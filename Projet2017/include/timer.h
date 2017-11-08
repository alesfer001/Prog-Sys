
#ifndef TIMER_IS_DEF
#define TIMER_IS_DEF

#include "SDL.h"
#include <stdint.h>

//#define USE_SDL_TIMERS

#if defined(USE_SDL_TIMERS) && !defined(PADAWAN) 
typedef SDL_TimerID timer_id_t;
#else
typedef intptr_t timer_id_t;
#endif

int timer_init (void);
timer_id_t timer_set (Uint32 delay, void *param);
int timer_cancel (timer_id_t timer_id);

void sdl_push_event (void *param);


#endif
