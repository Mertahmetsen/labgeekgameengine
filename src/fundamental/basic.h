#ifndef MERAHM_BASIC
#define MERAHM_BASIC

#include "raylib.h"
#include "raygui.h"

#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define uchar unsigned char
#define LOGIC_AND &&
#define LOGIC_OR ||

typedef struct RenderOptions {
  Rectangle srcrec;
  Rectangle dstrec;
  Vector2 origin;
  float rotation;
  Color tint;
} RenderOptions;

typedef struct Render_t {
  Texture2D texture;
  RenderOptions options;
  bool enabled;
  bool enabledUser;
} Render_t;

typedef struct IntVector {
  int x;
  int y;
} IntVector;

typedef enum {
  TOPLEFT, TOPRIGHT, BOTLEFT, BOTRIGHT, MID
} WindowPos;

#define DBOX_TEXT_MAX_LEN 2048
#define DIR_MAX_LEN 256

typedef struct DialogueBox {
  char *text;
  Font font;
  float fontSize;
  float spacing;
  WindowPos position;
  Color color;
  Color outline;
  Color textColor;
} DialogueBox; // its actually a monologue box, but i cant be bothered

typedef struct DBoxFile {
  uint_fast16_t version;
  char text[DBOX_TEXT_MAX_LEN];
  char fontdir[DIR_MAX_LEN];
  float fontSize;
  float spacing;
  WindowPos position;
  Color color;
  Color outline;
  Color textColor;
  float lifetime;
  bool enabled;
} DBoxFile;

typedef struct TexturePointer {
  uint_fast16_t version;
  char rayTextureDir[DIR_MAX_LEN];
  int renderSlot;
} TexturePointer;

typedef enum VerboseStatus {
  NONE, ERR, ERRNWARN, ALL, COMPLETE
} VerboseStatus;
VerboseStatus g_b_verboseStatus = ALL;

typedef enum LogPreset {
  I_SUCCESS, E_INVPARAM, E_INVPTR, E_NOMEM, E_UNSPEC,
  E_INTERNAL
} LogPreset;

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

#define MAX_LOG_LEN 256
#define LINFO LOG_INFO
#define LERR LOG_ERROR
#define LWARN LOG_WARNING
// The NEW log handler, handles logLevel at runtime
// and supports text formatting.
void logHandler(int logtype, const char *format, va_list args)
{
    char buffer[MAX_LOG_LEN];
    switch (g_b_verboseStatus) {
        case ALL:
            if (logtype != LOG_ERROR &&
                logtype != LOG_FATAL &&
                logtype != LOG_WARNING &&
                logtype != LOG_INFO)
                return;
            break;

        case ERRNWARN:
            if (logtype != LOG_ERROR &&
                logtype != LOG_FATAL &&
                logtype != LOG_WARNING)
                return;
            break;

        case ERR:
            if (logtype != LOG_ERROR &&
                logtype != LOG_FATAL)
                return;
            break;

        case COMPLETE:
            break;

        case NONE:
        default:
            return;
    }
    vsnprintf(buffer, sizeof(buffer), format, args);
    printf("%s\n", buffer);
}
void initLogHandler (VerboseStatus status) {
  g_b_verboseStatus = status;
  SetTraceLogCallback(logHandler);
}
void logBasicImpl(const char* caller, LogPreset p) {
  char msg[256];
  int logtype;
  switch (p) {
    case I_SUCCESS:
      TextCopy(msg, "The function finished without errors.");
      logtype = LINFO;
      break;
    case E_INVPARAM:
      TextCopy(msg, "Invalid parameter(s).");
      logtype = LERR;
      break;
    case E_INVPTR:
      TextCopy(msg, "Invalid pointer(s).");
      logtype = LERR;
      break;
    case E_NOMEM:
      TextCopy(msg, "Memory allocation failure.");
      logtype = LERR;
      break;
    case E_UNSPEC:
      TextCopy(msg, "Unspecified error.");
      logtype = LERR;
      break;
    case E_INTERNAL:
      TextCopy(msg, "Internal error.");
      logtype = LERR;
      break;
    default:
      TextCopy(msg, "Invalid parameter(s).");
      logtype = LERR;
      break;
  }
  TraceLog(logtype, "[%s] %s", caller, msg);
}
#define TraceLogCaller(type, format, ...) \
    TraceLog(type, "[%s] " format, __func__, ##__VA_ARGS__)
#define logBasic(p) logBasicImpl(__func__, (p))

const char* g_b_gccFlags = "-O3 -lraylib -lm -Wall -Wextra -Wpedantic -fopt-info -ftime-report -g";
const char* g_b_binaryName = "./bin";
const char* g_b_mainSourcePath = "dev/src/main.c";
bool g_b_alreadyRecompiled = false;
const char* g_b_currentMapHeaderPath = "dev/src/map/current.h";

#endif