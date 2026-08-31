#include "cursor.h"

void updateMousePos (void)
{
    g_mousePos = GetMousePosition();
    TraceLogCaller(LINFO, "Updated mouse position: (%f,%f)", g_mousePos.x, g_mousePos.y);
}
