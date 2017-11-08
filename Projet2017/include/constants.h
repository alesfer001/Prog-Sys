
#ifndef CONSTANTS_IS_DEF
#define CONSTANTS_IS_DEF

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif /* __APPLE__ */


// Warning: WIN_HEIGHT cannot exceed 1280
#define WIN_WIDTH   1280
#define WIN_HEIGHT  768

// Scrolling thresholds
#define X_SAFETY_BORDER    300
#define Y_SAFETY_TOP       200
#define Y_SAFETY_BOTTOM    300

#define TILE        64
#define LOG_TILE    6

#define modulo_tile(x)          ((x) & (TILE-1))
#define is_aligned(x)           (modulo_tile(x) == 0)
#define dist_from_aligned(x)    ((TILE - (x)) & (TILE - 1))
#define tile_rounded(x)         ((x) & ~(TILE-1))
#define tile_rounded_sup(x)     ((x + TILE - 1) & ~(TILE-1))
#define tile_span(x)            ((x + TILE - 1) >> LOG_TILE)
#define tile_no(x)              ((x) >> LOG_TILE)
#endif
