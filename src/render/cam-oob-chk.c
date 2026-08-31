#include "cam-oob-chk.h"

void pushCamToBounds (Camera2D* cam, Rectangle bounds)
{
    float halfViewWidth = GetScreenWidth() / (2.0f * cam->zoom);
    float halfViewHeight = GetScreenHeight() / (2.0f * cam->zoom);
    cam->target.x = Clamp(cam->target.x, bounds.x + halfViewWidth, bounds.x + bounds.width - halfViewWidth);
    cam->target.y = Clamp(cam->target.y, bounds.y + halfViewHeight, bounds.y + bounds.height - halfViewHeight);
    TraceLogCaller(LINFO, "Pushed camera into bounds.");
}
