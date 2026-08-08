#ifndef MERAHM_CURSOR
#define MERAHM_CURSOR
#include "../fundamental/globals.h"

void updateMousePos (void);

#ifdef LABGEEK_IMPLEMENTATION
void updateMousePos (void) {
    g_mousePos = GetMousePosition();
    traceFuncInfo(__func__, TextFormat("Updated mouse position: (%f,%f)", g_mousePos.x, g_mousePos.y));
}
#endif

#endif