#ifndef MERAHM_BASIC
#define MERAHM_BASIC

#include "raylib.h"
#include "raygui.h"

#define uchar unsigned char

#define clr(r, g, b, a) (Color) {(uchar)r, (uchar)g, (uchar)b, (uchar)a}
#define rct(x, y, w, h) (Rectangle) {(float)x, (float)y, (float)w, (float)h}
#define vec(x, y) ((Vector2) {(float)x, (float)y})

Rectangle boundary (float x, float y, const char* text, Font font) {
  const Vector2 size = MeasureTextEx(font, text, GuiGetStyle(DEFAULT, TEXT_SIZE), GuiGetStyle(DEFAULT, TEXT_SPACING));
  return (Rectangle) {x, y, size.x, size.y};
}

void guiSetAll (Font f, int textsize, int textspacing, int borderwidth) {
  GuiSetFont(f);
  GuiSetStyle(DEFAULT, TEXT_SIZE, textsize);
  GuiSetStyle(DEFAULT, TEXT_SPACING, textspacing);
  GuiSetStyle(DEFAULT, BORDER_WIDTH, borderwidth);
  GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
}

#endif
