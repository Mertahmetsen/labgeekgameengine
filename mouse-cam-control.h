#ifndef MERAHM_MOUSE_CAM_SMOOTH_CONTROL
#define MERAHM_MOUSE_CAM_SMOOTH_CONTROL
#include "globals.h"

int decideDirection (void) { // -1 is left, 0 is stationary, 1 is right
    const int mouse = GetMouseX();
    if (mouse <= g_camMvTreshold) {
        return -1;
    }
    if (mouse >= g_windowW - g_camMvTreshold) {
        return 1;
    }
    return 0;
}

void smoothCamMovement (void) {
    if (g_camLocked == true) return;
    g_dCam.target.x = g_dCam.target.x + (g_dt * g_camSpeed * decideDirection());
}

void lockCam (bool state) {
    g_camLocked = state;
}

#endif