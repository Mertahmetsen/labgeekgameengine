#ifndef MERAHM_ANIMATED
#define MERAHM_ANIMATED
#include "../fundamental/globals.h"

bool animAlloc (Animation* a) {
    a->frames = malloc(sizeof(Animation) * a->totalFrames);
    if (!a->frames) return false;
    return true;
}

void animFree (Animation* a) {
    free(a->frames);
}

void updateAnimation (Animation* a) {
    a->timer += g_dt;
    if (a->timer >= a->frameDuration) {
        a->timer -= a->frameDuration;
        a->currentFrame = (a->currentFrame + 1) % a->totalFrames;
        g_renderList[a->renderSlotAddress.x][a->renderSlotAddress.y] = a->frames[a->currentFrame];
    }
}

#endif