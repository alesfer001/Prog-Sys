
#ifndef MARIO_IS_DEF
#define MARIO_IS_DEF

#include "object.h"

extern dynamic_object_t mario;

void animation_mario_moves (dynamic_object_t *obj, int left, int right);
int animation_mario_change_size (dynamic_object_t *obj, unsigned size);
void animation_mario_jumps (dynamic_object_t *obj);
void animation_mario_drops (dynamic_object_t *obj, int type);
void animation_mario_shots (dynamic_object_t *obj);


#endif
