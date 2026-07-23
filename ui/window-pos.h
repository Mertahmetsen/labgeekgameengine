#ifndef MERAHM_WINDOWPOS
#define MERAHM_WINDOWPOS
#include "../fundamental/globals.h"
#include <math.h>

IntVector getWindowPos (WindowPos pos) {
    switch (pos) {
        case TOPRIGHT:
            return ivec(g_windowW, 0);
        case BOTLEFT:
            return ivec(0, g_windowH);
        case BOTRIGHT:
            return ivec(g_windowW, g_windowH);
        case MID:
            return ivec(g_windowW/2, g_windowH/2);
        case TOPLEFT:
        default:
            return ivec(0, 0);
    }
}

// the reference becomes the rectangle rather than the entire window
IntVector getWindowPosFromRect (Rectangle rect, WindowPos refpos) {
    switch (refpos) {
        case TOPLEFT:
            return ivec(rect.x, rect.y);
        case TOPRIGHT:
            return ivec(rect.x + rect.width, rect.y);
        case BOTLEFT:
            return ivec(rect.x, rect.y + rect.height);
        case BOTRIGHT:
            return ivec(rect.x + rect.width, rect.y + rect.height);
        case MID:
            return ivec(rect.x + (rect.width/2), rect.y + (rect.height/2));
        default:
            return ivec(0,0);
    }
}

void slideWindowPos (IntVector* pos, IntVector slide, float ratio) {
    if (!pos) return;
    pos->x += (int)floorf((float)(slide.x - pos->x) * ratio);
    pos->y += (int)floorf((float)(slide.y - pos->y) * ratio);
}

IntVector slideWindowPosFromRect (Rectangle rect, WindowPos refpos, IntVector slide, float ratio) {
    IntVector wpfr = getWindowPosFromRect(rect, refpos);
    slideWindowPos(&wpfr, slide, ratio);
    return wpfr;
}

#endif