#ifndef MERAHM_MOUSE_CAM_SMOOTH_CONTROL
#define MERAHM_MOUSE_CAM_SMOOTH_CONTROL
#include "../fundamental/globals.h"

int decideDirectionX (void) { // -1 is left, 0 is stationary, 1 is right
    const int mouse = GetMouseX();
    if (mouse <= g_camMvTresholdX) {
        return -1;
    }
    if (mouse >= g_windowW - g_camMvTresholdX) {
        return 1;
    }
    return 0;
}

int decideDirectionY(void)
{
    const int mouse = GetMouseY();
    if (mouse <= g_camMvTresholdY) {
        return -1;
    }
    if (mouse >= g_windowH - g_camMvTresholdY) {
        return 1;     // bottom of screen
    }
    return 0;
}

void smoothCamMovement (void) {
    if (g_camLocked == true) return;
    g_dCam.target.x = g_dCam.target.x + (g_dt * g_camSpeed * decideDirectionX());
    g_dCam.target.y = g_dCam.target.y + (g_dt * g_camSpeed * decideDirectionY());
}

void lockCam (bool state) {
    g_camLocked = state;
}

#endif