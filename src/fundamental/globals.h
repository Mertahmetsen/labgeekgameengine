#ifndef MERAHM_GLOBALS
#define MERAHM_GLOBALS
#include "basic.h"
#include <stddef.h>

// VARIABLE NAMES STARTING WITH "g_d" are BINARY-WIDE DEFAULTS.
// SOME FUNCTIONS GET SPECIFIC PARAMETERS WHILE OTHERS USE
// BINARY-WIDE DEFAULTS. FOR EXAMPLE: A FUNCTION THAT PRINTS A
// TEXT CAN BOTH BE "drawText(text)" OR "drawText(font, text)"
// IN CASE IT'S THE FORMER, THE FUNCTION WILL USE THE DEFAULT
// FONT THAT IS SET !INSIDE! !THIS! !FILE!.

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
// IntVector2 g_renderGroups[RENDER_GROUPS_LIST_SIZE]; // x->min, y->max
extern bool g_useRenderGroups;
extern int g_smoothingSegments;
extern IntVector2 g_tBoxSlideLength;
extern float g_tBoxRoundness;
extern IntVector2 g_tBoxTextSlideLength;
#define RENDERLISTSIZE 4096
#define RENDERLISTCOUNT 32
extern Render_t g_renderList[RENDERLISTCOUNT][RENDERLISTSIZE];
extern Rectangle g_dCamAABB;

void defaultGlobals(void);

void preWinInitGlobals(void);

void initCam (Vector2 target, float rotation, float zoom);

void delta (void);

#endif