#ifndef MERAHM_CURSOR
#define MERAHM_CURSOR
#include "globals.h"

void updateMousePos (void) {
    g_mousePos = GetMousePosition();
}

#endif