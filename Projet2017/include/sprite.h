
#ifndef SPRITE_IS_DEF
#define SPRITE_IS_DEF


#include "SDL.h"

#include "collision.h"

typedef struct {
  SDL_Texture *texture, *dyn_texture;
  SDL_Texture **textures;
  int xframes, frames;
  int native_width, native_height;
  int display_width, display_height;
  collision_mask_t mask;
} sprite_t;

extern sprite_t mario_sprite [],
  tnt_sprite,
  edit_sprite,
  bomb_sprite,
  mine_sprite,
  ouch_sprite,
  yeeha_sprite,
  plop_sprite,
  cannon_sprite,
  tank_sprite [],
  missile_sprite [],
  shot_sprite [],
  explosion_sprite [],
  torpedo_sprite [];

void sprite_init (void);


#endif
