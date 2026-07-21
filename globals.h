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
int g_dRefWinWidth; // window size reference, g_dCam.zoom scales with this.
#define RENDER_LIST_SIZE 256
Texture2D g_renderList[RENDER_LIST_SIZE]; // Useful for culling?
RenderOptions g_renderOptions[RENDER_LIST_SIZE];

void defaultGlobals(void) {
    g_dFont = LoadFontEx("../resources/fonts/font1.ttf", 48, NULL, 0);
    g_dTbColor = WHITE;
    g_dCam.offset = vec(GetScreenWidth()/2.0f, GetScreenHeight()/2.0f);
    g_targetFPS = 60;
    g_camSpeed = 250;
    g_camMvTreshold = g_dCam.offset.x / 2;
    g_dRefWinWidth = 800;
    for (int i=0; i<RENDER_LIST_SIZE; ++i) {
        g_renderList[i] = (Texture){0};
        g_renderOptions[i] = (RenderOptions){0};
    }
}

void preWinInitGlobals(void) {
    g_windowTitle = "Lab Geek";
    g_windowW = 1024;
    g_windowH = 768;
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