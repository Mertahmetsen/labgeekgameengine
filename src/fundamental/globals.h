#ifndef MERAHM_GLOBALS
#define MERAHM_GLOBALS
#include "basic.h"
#include <stddef.h>

// BINARY-WIDE DEFAULTS HAVE BEEN REMOVED.

extern Font g_dFont;
extern Color g_dTbColor;
extern Camera2D g_dCam;
extern int g_targetFPS;
extern int g_windowW; 
extern int g_windowH;
extern char* g_windowTitle;
extern int g_camSpeed;
extern int g_camMvTresholdX;
extern int g_camMvTresholdY;
extern float g_dt;
extern float g_dRefWinWidth; // window size reference, g_dCam.zoom scales with this.
extern float g_dRefWinHeight;
// #define RENDER_LIST_SIZE 2048
// Render_t g_renders[RENDER_LIST_SIZE];
extern bool g_camLocked;
extern Vector2 g_mousePos;
// #define RENDER_GROUPS_LIST_SIZE 32
// IntVector g_renderGroups[RENDER_GROUPS_LIST_SIZE]; // x->min, y->max
extern bool g_useRenderGroups;
extern int g_smoothingSegments;
extern IntVector g_tBoxSlideLength;
extern float g_tBoxRoundness;
extern IntVector g_tBoxTextSlideLength;
#define RENDERLISTSIZE 256
#define RENDERLISTCOUNT 32
extern Render_t g_renderList[RENDERLISTCOUNT][RENDERLISTSIZE];

void preWinInitGlobals(void);
void initCam(Vector2 target, float rotation, float zoom);
void delta (void);

#ifdef LABGEEK_IMPLEMENTATION
Font g_dFont;
Color g_dTbColor;
Camera2D g_dCam;
int g_targetFPS;
int g_windowW; 
int g_windowH;
char* g_windowTitle;
int g_camSpeed;
int g_camMvTresholdX;
int g_camMvTresholdY;
float g_dt;
float g_dRefWinWidth; // window size reference, g_dCam.zoom scales with this.
float g_dRefWinHeight;
// #define RENDER_LIST_SIZE 2048
// Render_t g_renders[RENDER_LIST_SIZE];
bool g_camLocked;
Vector2 g_mousePos;
// #define RENDER_GROUPS_LIST_SIZE 32
// IntVector g_renderGroups[RENDER_GROUPS_LIST_SIZE]; // x->min, y->max
bool g_useRenderGroups;
int g_smoothingSegments;
IntVector g_tBoxSlideLength;
float g_tBoxRoundness;
IntVector g_tBoxTextSlideLength;
#define RENDERLISTSIZE 256
#define RENDERLISTCOUNT 32
Render_t g_renderList[RENDERLISTCOUNT][RENDERLISTSIZE];

void preWinInitGlobals(void) {
    g_windowTitle = "Lab Geek";
    g_windowW = 1024;
    g_windowH = 768;
}

void initCam (Vector2 target, float rotation, float zoom) {
    g_dCam.target = target;
    g_dCam.zoom = zoom;
    g_dCam.rotation = rotation;
    traceFuncInfo(__func__, TextFormat("Initialized global camera: target=(%f,%f), zoom=%d, rotation=%f", target.x, target.y, zoom, rotation));
}

void delta (void) {
    g_dt = GetFrameTime();
    traceFuncInfo(__func__, TextFormat("A frame takes %f milliseconds", g_dt*1000.0f));
}
#endif

#endif