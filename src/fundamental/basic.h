#ifndef MERAHM_BASIC
#define MERAHM_BASIC

#include <raylib.h>
#include <raygui.h>

#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

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

typedef struct IntVector2 {
  int x;
  int y;
} IntVector2;

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
extern VerboseStatus g_b_verboseStatus;

typedef enum LogPreset {
  I_SUCCESS, E_INVPARAM, E_INVPTR, E_NOMEM, E_UNSPEC,
  E_INTERNAL
} LogPreset;

typedef struct {
  const char* name;
  void (*onLoad)(void);
  void (*onUpdate)(void);
  void (*onFinish)(void);
} Scene;

typedef struct {
  float r, g, b, a;
} ColorF;

typedef struct Animation {
  IntVector2 renderSlotAddress;
  Render_t* frames;
  int totalFrames;
  int currentFrame;
  float frameDuration;
  float timer;
} Animation;

#define clr(r, g, b, a) (Color) {(uchar)(r), (uchar)(g), (uchar)(b), (uchar)(a)}
#define rct(x, y, w, h) (Rectangle) {(float)(x), (float)(y), (float)(w), (float)(h)}
#define vec(x, y) ((Vector2) {(float)(x), (float)(y)})
#define ropt(src, dst, origin, rot, t) (RenderOptions) {src,dst,origin,rot,t}
#define ivec(x, y) (IntVector2) {(int)(x), (int)(y)}
#define roptbasic(pos, texture, t) (RenderOptions) {rct(0,0,texture.width, texture.height),rct(pos.x, pos.y, texture.width,texture.height),vec(0,0),0.0f,t}

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GRAY    "\x1b[90m"

Rectangle boundary (float x, float y, const char* text, Font font);

Rectangle boundaryEx (float x, float y, const char* text, Font font, float fontsize, float spacing);

void guiSetAll (Font f, int textsize, int textspacing, int borderwidth);

bool inScope (int min, int max, int x);

#define MAX_LOG_LEN 256
#define LINFO LOG_INFO
#define LERR LOG_ERROR
#define LWARN LOG_WARNING
// The NEW log handler, handles logLevel at runtime
// and supports text formatting.
void logHandler(int logtype, const char *format, va_list args);
void initLogHandler (VerboseStatus status);
void logBasicImpl(const char* caller, LogPreset p);
#define TraceLogCaller(type, format, ...) \
    TraceLog(type, "[%s] " format, __func__, ##__VA_ARGS__)
#define logBasic(p) logBasicImpl(__func__, (p))

Vector2 ivec2vec (IntVector2 iv);
IntVector2 vec2ivec (Vector2 v);

extern char* filterFunc;

#endif