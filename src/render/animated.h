#ifndef MERAHM_ANIMATED
#define MERAHM_ANIMATED
#include "../fundamental/globals.h"

bool animAlloc (Animation* a) {
    a->frames = malloc(sizeof(*a->frames) * a->totalFrames);
    if (!a->frames) return false;
    return true;
}

void animFree (Animation* a) {
    if (!a || !a->frames) return;
    for (int i = 0; i < a->totalFrames; i++) {
        UnloadTexture(a->frames[i].texture);
    }
    free(a->frames);
    a->frames = NULL;
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