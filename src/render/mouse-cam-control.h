#ifndef MERAHM_MOUSE_CAM_SMOOTH_CONTROL
#define MERAHM_MOUSE_CAM_SMOOTH_CONTROL
#include "../fundamental/globals.h"

int decideDirectionX (void);

int decideDirectionY(void);

void smoothCamMovement (void);

void lockCam (bool state);

#endif