
#ifndef COLLISION_IS_DEF
#define COLLISION_IS_DEF


#include "SDL.h"

#include "constants.h"

typedef Uint64 tile_mask_t [TILE];

typedef struct {
  unsigned rows, cols;
  int dx, dy;
  tile_mask_t *masks, *flip_masks;
} collision_mask_t;

enum {
  COLLISION_MASK_NONE    = -1,
  COLLISION_MASK_AS_IS   =  0,
  COLLISION_MASK_FLIPPED =  1,
  COLLISION_MASK_DYNAMIC =  2
};

void collision_init (void);
void collision_mask_zero (collision_mask_t *mask);

void collision_mask_set (SDL_Surface *surface, unsigned frames, unsigned xframes,
			 unsigned width, unsigned height, int flip,
			 SDL_Texture **tex, collision_mask_t *mask);

void collision_mask_refresh (collision_mask_t *mask, SDL_Texture *tex, double angle);
void collision_mask_display (collision_mask_t *mask, int direction, int frame);
void collision_mask_destroy (collision_mask_t *mask);

int collision_objects_collide (int x1, int y1, collision_mask_t *mask1, int direction1, int f1,
			       int x2, int y2, collision_mask_t *mask2, int direction2, int f2,
			       void *dyn1, void *dyn2);

#endif
