
#ifndef OBJECT_IS_DEF
#define OBJECT_IS_DEF


#include "SDL.h"

#include "sprite.h"
#include "list.h"
#include "timer.h"

enum {
  OBJECT_SIZE_NORMAL,
  OBJECT_SIZE_MINI,
  OBJECT_SIZE_MAXI
};

enum {
  OBJECT_TYPE_MARIO,
  OBJECT_TYPE_MISSILE,
  OBJECT_TYPE_EXPLOSION,
  OBJECT_TYPE_BOMB,
  OBJECT_TYPE_CURSOR,
  OBJECT_TYPE_MINE,
  OBJECT_TYPE_TEXT,
  OBJECT_TYPE_TANK,
  OBJECT_TYPE_TNT,
  OBJECT_TYPE_CANNON,
  __OBJECT_TYPE_NUM
};

enum {
  OBJECT_STATE_NORMAL,
  OBJECT_STATE_ARMED,
  OBJECT_STATE_TRIGGERED,
  OBJECT_STATE_EXPLODE,
  OBJECT_STATE_IN_AIR,
  OBJECT_STATE_DESTROYED
};

enum {
  COLLISION_TYPE_NONE,
  COLLISION_TYPE_TOTAL, // Collision is detected using complete objet
  COLLISION_TYPE_HORIZ_FRONT // Collision is detected using only the
                             // horizontal front side of moving object
};

enum {
  PROJECTILE_TYPE_NORMAL,
  PROJECTILE_TYPE_TORPEDO,
  PROJECTILE_TYPE_DEFECT
};

typedef struct _dyn_obj {
  int type;
  int state;
  unsigned size;
  int x, y; // position
  int xs, ys; // speed
  int xorig, yorig;
  int direction; // 1 = right, 0 = left
  int dir_orig;
  int hurt;
  int dammage;
  int in_water;
  int gfx;
  unsigned gfx_step;
  Uint32 alpha;
  double scale;
  double angle;
  int current_sprite;
  int tempo;
  int sound_channel;
  sprite_t *sprite;
  unsigned refcount;
  timer_id_t timer_id;
  int map_collision_type;
  int projectile_type;
  struct _dyn_obj *target;
  collision_mask_t dyn_mask;
  unsigned mask_need_refresh;
  struct list_head global_chain;
  struct list_head collid_chain;
  tile_mask_t dyn_tiles[1];
} dynamic_object_t;

typedef void (*map_add_func_t)(int xmap, int ymap, int from_file);
typedef int (*animate_func_t)(dynamic_object_t *obj);
typedef int (*map_collide_func_t)(dynamic_object_t *obj, int map_object, int xmap, int ymap);
typedef void (*map_post_collide_func_t)(dynamic_object_t *obj);
typedef int (*map_collidable_func_t)(dynamic_object_t *obj);
typedef void (*timer_func_t)(dynamic_object_t *obj);
typedef void (*load_func_t)(int fd);
typedef void (*save_func_t)(dynamic_object_t *obj, int fd);


enum {
  MAP_COLLIDE_COLLEC,
  MAP_COLLIDE_DESTRUC,
  MAP_COLLIDE_TOUGH,
  __MAP_COLLIDE_NUM
};

typedef struct {
  map_add_func_t map_add_func;
  animate_func_t animate_func;
  map_collidable_func_t map_collidable_func;
  map_collide_func_t map_collide_func [__MAP_COLLIDE_NUM];
  map_post_collide_func_t map_post_collide_func;
  timer_func_t timer_func;
  load_func_t load_func;
  save_func_t save_func;
} object_type_t;

extern object_type_t object_class [];
extern char *objtype2str [];

#define ANIMATION_F(name)         animation_##name
#define TIMER_EXP_F(name)         animation_##name##_timer_expired
#define MAP_ADD_F(name)           animation_##name##_add
#define COLLEC_COLLIDE_F(name)    animation_##name##_collec_collide
#define DESTRUC_COLLIDE_F(name)   animation_##name##_destruc_collide
#define TOUGH_COLLIDE_F(name)     animation_##name##_tough_collide
#define POST_COLLIDE_F(name)      animation_##name##_post_collide
#define MAP_COLLIDABLE_F(name)    animation_##name##_map_collidable
#define LOAD_F(name)              animation_##name##_load
#define SAVE_F(name)              animation_##name##_save

#define ANIMATION_PROTO(name) int ANIMATION_F(name) (dynamic_object_t *obj)
#define TIMER_EXP_PROTO(name) void TIMER_EXP_F(name) (dynamic_object_t *obj)
#define MAP_ADD_PROTO(name) void MAP_ADD_F(name) (int xmap, int ymap, int from_file)
#define COLLEC_COLLIDE_PROTO(name) int COLLEC_COLLIDE_F(name) (dynamic_object_t *obj, \
							       int map_object, int xmap, int ymap)
#define DESTRUC_COLLIDE_PROTO(name) int DESTRUC_COLLIDE_F(name) (dynamic_object_t *obj, \
								 int map_object, int xmap, int ymap)
#define TOUGH_COLLIDE_PROTO(name) int TOUGH_COLLIDE_F(name) (dynamic_object_t *obj, \
							     int map_object, int xmap, int ymap)

#define POST_COLLIDE_PROTO(name) void POST_COLLIDE_F(name) (dynamic_object_t *obj)
#define MAP_COLLIDABLE_PROTO(name) int MAP_COLLIDABLE_F(name) (dynamic_object_t *obj)
#define LOAD_PROTO(name) void LOAD_F(name) (int fd)
#define SAVE_PROTO(name) void SAVE_F(name) (dynamic_object_t *obj, int fd)

void object_init (void);
void object_object_init (dynamic_object_t *obj, sprite_t *sp, int type, int x, int y);
void object_object_refresh_mask (dynamic_object_t *obj);

extern ANIMATION_PROTO(missile);
extern ANIMATION_PROTO(explosion);
extern ANIMATION_PROTO(bomb);
extern ANIMATION_PROTO(mine);
extern ANIMATION_PROTO(text);
extern ANIMATION_PROTO(tank);
extern ANIMATION_PROTO(tnt);
extern ANIMATION_PROTO(cannon);

extern TIMER_EXP_PROTO(mario);
extern TIMER_EXP_PROTO(bomb);
extern TIMER_EXP_PROTO(mine);
extern TIMER_EXP_PROTO(tank);

extern MAP_ADD_PROTO(bomb);
extern MAP_ADD_PROTO(mine);
extern MAP_ADD_PROTO(tnt);

extern MAP_COLLIDABLE_PROTO(mario);
extern MAP_COLLIDABLE_PROTO(missile);
extern MAP_COLLIDABLE_PROTO(tank);

extern COLLEC_COLLIDE_PROTO(mario);
extern DESTRUC_COLLIDE_PROTO(missile);
extern TOUGH_COLLIDE_PROTO(missile);
extern TOUGH_COLLIDE_PROTO(tank);

extern POST_COLLIDE_PROTO(missile);
extern POST_COLLIDE_PROTO(tank);

extern SAVE_PROTO(mine);
extern SAVE_PROTO(tank);
extern SAVE_PROTO(tnt);
extern SAVE_PROTO(cannon);

extern LOAD_PROTO(mine);
extern LOAD_PROTO(tank);
extern LOAD_PROTO(tnt);
extern LOAD_PROTO(cannon);


#endif
