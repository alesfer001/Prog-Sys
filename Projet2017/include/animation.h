
#ifndef ANIMATION_IS_DEF
#define ANIMATION_IS_DEF


#include "SDL.h"

#include "object.h"

extern int edit_mode;
extern int timers_are_implemented;

void animation_init (void);
void animation_keypressed (SDL_Keycode key);
void animation_mouse_move (int x, int y);
void animation_mouse_clic (int x, int y);
#ifdef TARGET_OS_IPHONE
void animation_touch_fingerdown (int x, int y, int *left_down, int *right_down, int *up, int *down);
void animation_touch_fingerup (int x, int y, int *left_down, int *right_down, int *up, int *down, int do_vertical_move);
#endif /* TARGET_OS_IPHONE */
void animation_change_mode (int edit);
void animation_one_step (int left, int right, int up, int down);
void animation_render_objects (void);
void animation_clean (void);

void animation_objects_save (int fd);
void animation_objects_load (int fd);

void animation_mobile_object_add (dynamic_object_t *obj);
int animation_play_if_onscreen (unsigned sound, dynamic_object_t *obj);
void animation_shut_up (dynamic_object_t *obj);

void animation_do_explode (dynamic_object_t *obj);
void animation_trigger_neighboor_objects (dynamic_object_t *obj);

void animation_timer_add (dynamic_object_t *obj, Uint32 delay);
void animation_timer_cancel (dynamic_object_t *obj);
void animation_timer_expired (void *arg1, void *arg2);

enum {
  COLLISION_CONT,
  COLLISION_STOP
};

int animation_collide_with_map (dynamic_object_t *obj);

void animation_object_refresh_mask (dynamic_object_t *obj);

#endif
