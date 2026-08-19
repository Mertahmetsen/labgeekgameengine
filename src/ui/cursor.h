#ifndef MERAHM_CURSOR
#define MERAHM_CURSOR
#include "../fundamental/globals.h"

void updateMousePos (void) {
    g_mousePos = GetMousePosition();
    TraceLog(LINFO, "Updated mouse position: (%f,%f)", g_mousePos.x, g_mousePos.y);
}

#endif