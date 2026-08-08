#ifndef MERAHM_BASIC
#define MERAHM_BASIC

#include "raylib.h"
#include "raygui.h"

#include <stdint.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define uchar unsigned char
#define LOGIC_AND &&
#define LOGIC_OR ||

#if defined(__GNUC__)
#define EXPORT __attribute__((visibility("default")))
#else
#define EXPORT
#endif

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
extern VerboseStatus g_b_verboseStatus; // FIXME : implement

typedef struct MapPlugin {
  void (*onLoad)(void);
  void (*onUpdate)(void);
  void (*onUnload)(void);
} MapPlugin;

#define clr(r, g, b, a) (Color) {(uchar)(r), (uchar)(g), (uchar)(b), (uchar)(a)}
#define rct(x, y, w, h) (Rectangle) {(float)(x), (float)(y), (float)(w), (float)(h)}
#define vec(x, y) ((Vector2) {(float)(x), (float)(y)})
#define ropt(src, dst, origin, rot, t) (RenderOptions) {src,dst,origin,rot,t}
#define ivec(x, y) (IntVector) {(int)(x), (int)(y)}
#define roptbasic(pos, texture, t) (RenderOptions) {rct(0,0,texture.width, texture.height),rct(pos.x, pos.y, texture.width,texture.height),vec(0,0),0.0f,t}

Rectangle boundary (float x, float y, const char* text, Font font);
Rectangle boundaryEx (float x, float y, const char* text, Font font, float fontsize, float spacing);
void guiSetAll (Font f, int textsize, int textspacing, int borderwidth);
bool inScope (int min, int max, int x);
// FIXME: dont forget to implement the new log handler
void traceFuncInfo (const char* fn, const char* msg);
void traceFuncWarn (const char* fn, const char* msg);
void traceFuncErr (const char* fn, const char* msg);
void logHandler (int logtype, const char* format, ...);
void setLogVerbosity (VerboseStatus status);
void onLoad(void);
void onUpdate(void);
void onUnload(void);
EXPORT struct MapPlugin* getPlugin(void);

#ifdef LABGEEK_IMPLEMENTATION

VerboseStatus g_b_verboseStatus;

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

// FIXME : Implement 
#define GAME_LOGINFO
#define GAME_LOGERR
#define GAME_LOGWARN
void traceFuncInfo (const char* fn, const char* msg) {
  #ifdef GAME_LOGINFO
  TraceLog(LOG_INFO, TextFormat("At %lf: %s: %s", GetTime(), fn, msg));
  #endif
}
void traceFuncErr (const char* fn, const char* msg) {
  #ifdef GAME_LOGERR
  TraceLog(LOG_ERROR, TextFormat("At %lf: %s: %s", GetTime(), fn, msg));
  #endif
}
void traceFuncWarn (const char* fn, const char* msg) {
  #ifdef GAME_LOGWARN
  TraceLog(LOG_ERROR, TextFormat("At %lf: %s: %s", GetTime(), fn, msg));
  #endif
}
// The NEW log handler, handles logLevel at runtime
// and supports text formatting.
void logHandler (int logtype, const char* format, ...) {
  char buffer[256];
  va_list argv;
  switch (g_b_verboseStatus) {
    case ALL:
      switch (logtype) {
        case LOG_ERROR:
        case LOG_FATAL:
        case LOG_WARNING:
        case LOG_INFO:
          va_start(argv, format);
          vsnprintf(buffer, sizeof(buffer), format, argv);
          va_end(argv);
        default:
          break;
      }
    case ERRNWARN:
      switch (logtype) {
        case LOG_ERROR:
        case LOG_FATAL:
        case LOG_WARNING:
          va_start(argv, format);
          vsnprintf(buffer, sizeof(buffer), format, argv);
          va_end(argv);
        default:
          break;
      }
      break;
    case ERR:
      switch (logtype) {
        case LOG_ERROR:
        case LOG_FATAL:
          va_start(argv, format);
          vsnprintf(buffer, sizeof(buffer), format, argv);
          va_end(argv);
        default:
          break;
      }
      break;
    case COMPLETE:
      va_start(argv, format);
      vsnprintf(buffer, sizeof(buffer), format, argv);
      va_end(argv);
    case NONE:
    default:
      break; // nothing to log.
  }
}
void setLogVerbosity (VerboseStatus status) {
  g_b_verboseStatus = status;
}
#endif

#endif