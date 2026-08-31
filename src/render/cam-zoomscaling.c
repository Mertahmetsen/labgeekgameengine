#include "cam-zoomscaling.h"

void camZoomscale (void)
{
    float scaleX = GetScreenWidth() / g_dRefWinWidth;
    float scaleY = GetScreenHeight() / g_dRefWinHeight;
    g_dCam.zoom = (scaleX < scaleY) ? scaleX : scaleY;
    TraceLogCaller(LINFO, "Scaled g_dCam's zoom with the resolution. g_dCam.zoom = %f", g_dCam.zoom);
}
