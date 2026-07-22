#ifndef MERAHM_WINDOWPOS
#define MERAHM_WINDOWPOS
#include "../fundamental/globals.h"
#include <math.h>

IntVector getWindowPos (WindowPos pos) {
    switch (pos) {
        case TOPRIGHT:
            return ivec(0, g_windowH);
        case BOTLEFT:
            return ivec(g_windowW, 0);
        case BOTRIGHT:
            return ivec(g_windowW, g_windowH);
        case MID:
            return ivec(g_windowW/2, g_windowH/2);
        case TOPLEFT:
        default:
            return ivec(0, 0);
    }
}

void slideWindowPos (IntVector* pos, IntVector slide, float ratio) {
    if (!pos) return;
    pos->x += (int)floorf((float)(slide.x - pos->x) * ratio);
    pos->y += (int)floorf((float)(slide.y - pos->y) * ratio);
}

#endif