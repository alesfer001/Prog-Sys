
#ifndef GRAPHICS_IS_DEF
#define GRAPHICS_IS_DEF


#include "SDL.h"

#include "object.h"
#include "collision.h"

#define GFX_NONE      0
#define GFX_BLINK     1
#define GFX_FADE      2
#define GFX_CENTER    4
#define GFX_SCALE     8
#define GFX_HALO     16
#define GFX_FLOAT    32
#define GFX_ROTATE   64

void graphics_init (Uint32 render_flags, char *background_skin);
void graphics_scroll_if_needed (int x, int y, int width, int height, int *xscroll, int *yscroll);
void graphics_map_begin (unsigned map_objects);
void graphics_map_add (char *png_file, int frames);
void graphics_map_end (void);
void graphics_map_get_collision_mask (int obj, collision_mask_t **mask, int *frame);
void graphics_intro (void);
void graphics_mouse_move (int x, int y);
void graphics_mouse_clic (int x, int y);
void graphics_mouse_setxy (int x, int y);
#ifdef TARGET_OS_IPHONE
void graphics_touch_fingerdown (int x, int y, int *left_down, int *right_down, int *up, int *down);
void graphics_touch_fingerup (int x, int y, int *left_down, int *right_down, int *up, int *down, int do_vertical_move);
#endif /* TARGET_OS_IPHONE */
void graphics_render (void);
int graphics_object_is_on_screen (dynamic_object_t *obj);
void graphics_render_object (dynamic_object_t *obj);
void graphics_clean (void);
int graphics_get_windows_width();
int graphics_get_windows_height();

#endif
