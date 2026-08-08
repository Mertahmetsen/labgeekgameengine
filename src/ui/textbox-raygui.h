#ifndef MERAHM_TEXTBOX_RAYGUI
#define MERAHM_TEXTBOX_RAYGUI

#include "../fundamental/basic.h"

void prepTbBckgrnd(Rectangle bound, Color tbcolor);
int tbFull(Rectangle bound, const char* title, const char* message, const char* buttons, Color back);

#ifdef LABGEEK_IMPLEMENTATION
void prepTbBckgrnd(Rectangle bound, Color tbcolor) {
    traceFuncInfo(__func__, "Preparing message box background");
    DrawRectangle(bound.x, bound.y, bound.width, bound.height, tbcolor);
}

int tbFull (Rectangle bound, const char* title, const char* message, const char* buttons, Color back) {
    prepTbBckgrnd(bound, back);
    traceFuncInfo(__func__, "Drawing message box");
    return GuiMessageBox(bound, title, message, buttons);
}
#endif

#endif