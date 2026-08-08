#ifndef MERAHM_MOUSE_CAM_SMOOTH_CONTROL
#define MERAHM_MOUSE_CAM_SMOOTH_CONTROL
#include "../fundamental/globals.h"

int decideDirectionX (void);
int decideDirectionY (void);
void smoothCamMovement (void);
void lockCam (bool state);

#ifdef LABGEEK_IMPLEMENTATION
int decideDirectionX (void) { // -1 is left, 0 is stationary, 1 is right
    if (g_mousePos.x <= g_camMvTresholdX) {
        traceFuncInfo(__func__, "The player-desired horizontal movement is left.");
        return -1;
    }
    if (g_mousePos.x >= g_windowW - g_camMvTresholdX) {
        traceFuncInfo(__func__, "The player-desired horizontal movement is right.");
        return 1;
    }
    return 0;
    traceFuncInfo(__func__, "The player-desired horizontal movement is stationary.");
}

int decideDirectionY(void)
{
    if (g_mousePos.y <= g_camMvTresholdY) {
        traceFuncInfo(__func__, "The player-desired vertical movement is stationary.");
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
    traceFuncInfo(__func__, TextFormat("Moved camera towards designated target: (%d, %d)", g_dCam.target.x, g_dCam.target.y));
}

void lockCam (bool state) {
    g_camLocked = state;
    traceFuncInfo(__func__, TextFormat("g_camLocked has been set to %d", (int)state));
}
#endif

#endif