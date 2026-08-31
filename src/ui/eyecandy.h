#ifndef MERAHM_EYECANDY
#define MERAHM_EYECANDY
#include "../fundamental/time.h"
#include "../fundamental/globals.h"
#include <math.h>

Color ColorFToRaylib(ColorF cf);

void fade(float* alpha, float target, float seconds);

void bounce(float* alpha, float* direction, float seconds);

void blink(float* alpha, float seconds);

void fadeColor(ColorF* c, Color t, float seconds);

void kaleidoscope(ColorF* c, float seconds);

#endif