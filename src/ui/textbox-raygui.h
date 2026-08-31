#ifndef MERAHM_TEXTBOX_RAYGUI
#define MERAHM_TEXTBOX_RAYGUI

#include "../fundamental/basic.h"

void prepTbBckgrnd(Rectangle bound, Color tbcolor);

int tbFull (Rectangle bound, const char* title, const char* message, const char* buttons, Color back);

#endif