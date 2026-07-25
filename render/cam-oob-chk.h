#ifndef MERAHM_CAM_OUT_OF_BOUNDS_CHECK
#define MERAHM_CAM_OUT_OF_BOUNDS_CHECK
#include "../fundamental/basic.h"
#include "raymath.h"

void pushCamToBounds (Camera2D* cam, Rectangle bounds) {
    float halfViewWidth = GetScreenWidth() / (2.0f * cam->zoom);
    float halfViewHeight = GetScreenHeight() / (2.0f * cam->zoom);
    cam->target.x = Clamp(cam->target.x, bounds.x + halfViewWidth, bounds.x + bounds.width - halfViewWidth);
    cam->target.y = Clamp(cam->target.y, bounds.y + halfViewHeight, bounds.y + bounds.height - halfViewHeight);
    traceFuncInfo(__func__, "Pushed camera into bounds.");
}

#endif