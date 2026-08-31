#include "debuguis.h"

void drawDebugText(void)
{
    static ColorF c;
    kaleidoscope(&c, g_dt);
    DrawTextPro(g_dFont, TextFormat("DEBUG - %d", GetFPS()), ivec2vec(getWindowPos(MID)), vec(0, 0), 0.0f, 20.0f, 2.0f, ColorFToRaylib(c));
}
