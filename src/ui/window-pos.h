#ifndef MERAHM_WINDOWPOS
#define MERAHM_WINDOWPOS
#include "../fundamental/globals.h"
#include <math.h>

IntVector2 getWindowPos (WindowPos pos);

// the reference becomes the rectangle rather than the entire window
IntVector2 getWindowPosFromRect (Rectangle rect, WindowPos refpos);

void slideWindowPos (IntVector2* pos, IntVector2 slide, float ratio);

IntVector2 slideWindowPosFromRect (Rectangle rect, WindowPos refpos, IntVector2 slide, float ratio);

#endif