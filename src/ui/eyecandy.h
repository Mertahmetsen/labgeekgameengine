#ifndef MERAHM_EYECANDY
#define MERAHM_EYECANDY
#include "../fundamental/time.h"
#include "../fundamental/globals.h"
#include <math.h>

Color ColorFToRaylib(ColorF cf) {
    return (Color){
        (unsigned char)cf.r,
        (unsigned char)cf.g,
        (unsigned char)cf.b,
        (unsigned char)cf.a
    };
}

void fade(float* alpha, float target, float seconds) {
    if (seconds <= 0.0f || *alpha == target) return;
    float speed = 255.0f / seconds; // Rate of alpha change per second
    if (*alpha < target) {
        *alpha += speed * g_dt;
        if (*alpha > target) *alpha = target;
    } else {
        *alpha -= speed * g_dt;
        if (*alpha < target) *alpha = target;
    }
}

void bounce(float* alpha, float* direction, float seconds) {
    if (seconds <= 0.0f) return;

    float speed = 255.0f / seconds;
    *alpha += speed * g_dt * (*direction);

    if (*alpha >= 255.0f) {
        *alpha = 255.0f;
        *direction = -1.0f; 
    }
    else if (*alpha <= 0.0f) {
        *alpha = 0.0f;
        *direction = 1.0f; 
    }
}

void blink(float* alpha, float seconds) {
    *alpha = (fmodf((float)GetTime(), seconds * 2.0f) < seconds) ? 255.0f : 0.0f;
}

void fadeColor(ColorF* c, Color t, float seconds) {
    fade(&c->r, (float)t.r, seconds);
    fade(&c->g, (float)t.g, seconds);
    fade(&c->b, (float)t.b, seconds);
    fade(&c->a, (float)t.a, seconds);
}

#endif