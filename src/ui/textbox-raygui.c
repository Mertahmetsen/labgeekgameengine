#include "textbox-raygui.h"

void prepTbBckgrnd(Rectangle bound, Color tbcolor)
{
    TraceLogCaller(LINFO, "Preparing textbox background");
    DrawRectangle(bound.x, bound.y, bound.width, bound.height, tbcolor);
}

int tbFull (Rectangle bound, const char* title, const char* message, const char* buttons, Color back)
{
    prepTbBckgrnd(bound, back);
    TraceLogCaller(LINFO, "Drawing textbox");
    return GuiMessageBox(bound, title, message, buttons);
}
