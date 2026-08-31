#ifndef MERAHM_ANIMATED
#define MERAHM_ANIMATED
#include "../fundamental/globals.h"

bool animAlloc (Animation* a);

void animFree (Animation* a);

void updateAnimation (Animation* a);

bool loadAndInitAnimation(Animation* a, const char* folderPath, int totalFrames, float frameDuration, IntVector2 slotAddress);

#endif