#ifndef MERAHM_MOUSE_CAM_SMOOTH_CONTROL
#define MERAHM_MOUSE_CAM_SMOOTH_CONTROL
#include "../fundamental/globals.h"

int decideDirectionX (void) { // -1 is left, 0 is stationary, 1 is right
    if (g_mousePos.x <= g_camMvTresholdX) {
        return -1;
    }
    if (g_mousePos.x >= g_windowW - g_camMvTresholdX) {
        return 1;
    }
    return 0;
}

int decideDirectionY(void)
{
    if (g_mousePos.y <= g_camMvTresholdY) {
        return -1;
    }
    if (g_mousePos.y >= g_windowH - g_camMvTresholdY) {
        return 1;     // bottom of screen
    }
    return 0;
}

void smoothCamMovement (void) {
    if (g_camLocked == true) return;
    g_dCam.target.x = g_dCam.target.x + (g_dt * g_camSpeed * decideDirectionX());
    g_dCam.target.y = g_dCam.target.y + (g_dt * g_camSpeed * decideDirectionY());
    TraceLog(LINFO, "Moved camera towards designated target: (%f, %f)", g_dCam.target.x, g_dCam.target.y);
}

void lockCam (bool state) {
    g_camLocked = state;
    TraceLog(LINFO, "g_camLocked has been set to %d", (int)state);
}

#endif