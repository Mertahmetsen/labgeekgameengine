#ifndef MERAHM_CURSOR
#define MERAHM_CURSOR
#include "../fundamental/globals.h"

void updateMousePos (void) {
    g_mousePos = GetMousePosition();
}

#endif