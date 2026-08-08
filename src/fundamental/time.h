#ifndef MERAHM_TIME
#define MERAHM_TIME
#include "raylib.h"

void stopwatch (float* swatch);
bool countdown (float* cdown);

#ifdef LABGEEK_IMPLEMENTATION
void stopwatch (float* swatch) {
    *swatch += GetFrameTime();
}

bool countdown (float* cdown) {
    *cdown -= GetFrameTime();
    return (bool)(*cdown <= 0.0f);
}
#endif

#endif