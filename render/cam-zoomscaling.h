#ifndef MERAHM_CAM_ZOOMSCALING
#define MERAHM_CAM_ZOOMSCALING
#include "../fundamental/globals.h"

void camZoomscale (void) {
    g_dCam.zoom = GetScreenWidth() / (float)g_dRefWinWidth;
}

#endif