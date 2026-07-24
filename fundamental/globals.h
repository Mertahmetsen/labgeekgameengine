#ifndef MERAHM_GLOBALS
#define MERAHM_GLOBALS
#include "basic.h"
#include <stddef.h>

Font g_dFont;
Color g_dTbColor;
Camera2D g_dCam;
int g_targetFPS;
int g_windowW; 
int g_windowH;
char* g_windowTitle;
int g_camSpeed;
int g_camMvTreshold;
float g_dt;
float g_dRefWinWidth; // window size reference, g_dCam.zoom scales with this.
float g_dRefWinHeight;
#define RENDER_LIST_SIZE 2048
Render_t g_renders[RENDER_LIST_SIZE]; // more forward-compatible
bool g_camLocked;
Vector2 g_mousePos;
#define RENDER_GROUPS_LIST_SIZE 32
IntVector g_renderGroups[RENDER_GROUPS_LIST_SIZE]; // x->min, y->max
bool g_useRenderGroups;
int g_smoothingSegments;
IntVector g_tBoxSlideLength;
float g_tBoxRoundness;
IntVector g_tBoxTextSlideLength;

void defaultGlobals(void) {
    g_dFont = LoadFontEx("../resources/fonts/font1.ttf", 48, NULL, 0);
    g_dTbColor = WHITE;
    g_dCam.offset = vec(GetScreenWidth()/2.0f, GetScreenHeight()/2.0f);
    g_targetFPS = 60;
    g_camSpeed = 250;
    g_camMvTreshold = g_dCam.offset.x / 2;
    g_dRefWinWidth = 800.0f;
    g_dRefWinHeight = 600.0f;
    for (int i=0; i<RENDER_LIST_SIZE; ++i) {
        g_renders[i].texture = (Texture){0};
        g_renders[i].options = (RenderOptions){0};
        g_renders[i].enabled = false;
    }
    g_camLocked = false;
    g_mousePos = GetMousePosition();
    for (int i=0; i<RENDER_GROUPS_LIST_SIZE; ++i) {
        g_renderGroups[i] = (IntVector){0};
    }
    g_useRenderGroups = true;
    g_smoothingSegments = 10;
    g_tBoxSlideLength = ivec(20,20);
    g_tBoxRoundness = 0.1f;
    g_tBoxTextSlideLength = ivec(2,2);
}

void preWinInitGlobals(void) {
    g_windowTitle = "Lab Geek";
    g_windowW = 640;
    g_windowH = 100;
}

void initCam (Vector2 target, float rotation, float zoom) {
    g_dCam.target = target;
    g_dCam.zoom = zoom;
    g_dCam.rotation = rotation;
}

void delta (void) {
    g_dt = GetFrameTime();
}

#endif