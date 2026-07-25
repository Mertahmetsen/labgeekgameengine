#ifndef MERAHM_BASIC
#define MERAHM_BASIC

#include "raylib.h"
#include "raygui.h"

#define uchar unsigned char

typedef struct {
  Rectangle srcrec;
  Rectangle dstrec;
  Vector2 origin;
  float rotation;
  Color tint;
} RenderOptions;

typedef struct {
  Texture2D texture;
  RenderOptions options;
  bool enabled;
} Render_t;

typedef struct {
  int x;
  int y;
} IntVector;

typedef enum {
  TOPLEFT, TOPRIGHT, BOTLEFT, BOTRIGHT, MID
} WindowPos;

typedef struct {
  char* text;
  Font font;
  float fontSize;
  float spacing;
  WindowPos position;
  Color color;
  Color outline;
  Color textColor;
} DialogueBox; // its actually a monologue box, but i cant be bothered


#define clr(r, g, b, a) (Color) {(uchar)(r), (uchar)(g), (uchar)(b), (uchar)(a)}
#define rct(x, y, w, h) (Rectangle) {(float)(x), (float)(y), (float)(w), (float)(h)}
#define vec(x, y) ((Vector2) {(float)(x), (float)(y)})
#define ropt(src, dst, origin, rot, t) (RenderOptions) {src,dst,origin,rot,t}
#define ivec(x, y) (IntVector) {(int)(x), (int)(y)}
#define roptbasic(pos, texture, t) (RenderOptions) {rct(0,0,texture.width, texture.height),rct(pos.x, pos.y, texture.width,texture.height),vec(0,0),0.0f,t}

Rectangle boundary (float x, float y, const char* text, Font font) {
  const Vector2 size = MeasureTextEx(font, text, GuiGetStyle(DEFAULT, TEXT_SIZE), GuiGetStyle(DEFAULT, TEXT_SPACING));
  return (Rectangle) {x, y, size.x, size.y};
}

Rectangle boundaryEx (float x, float y, const char* text, Font font, float fontsize, float spacing) {
  Vector2 size = MeasureTextEx(font, text, fontsize, spacing);
  return (Rectangle){ x, y, size.x, size.y };
}

void guiSetAll (Font f, int textsize, int textspacing, int borderwidth) {
  GuiSetFont(f);
  GuiSetStyle(DEFAULT, TEXT_SIZE, textsize);
  GuiSetStyle(DEFAULT, TEXT_SPACING, textspacing);
  GuiSetStyle(DEFAULT, BORDER_WIDTH, borderwidth);
  GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
}

bool inScope (int min, int max, int x) {
  if (x > max || x < min) return false;
  return true;
}

void traceFuncInfo (const char* fn, const char* msg) {
  TraceLog(LOG_INFO, TextFormat("At %lf: %s: %s", GetTime(), fn, msg));
}

void traceFuncErr (const char* fn, const char* msg) {
  TraceLog(LOG_ERROR, TextFormat("At %lf: %s: %s", GetTime(), fn, msg));
}

void traceFuncWarn (const char* fn, const char* msg) {
  TraceLog(LOG_ERROR, TextFormat("At %lf: %s: %s", GetTime(), fn, msg));
}

#endif
