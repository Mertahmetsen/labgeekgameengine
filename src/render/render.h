#ifndef MERAHM_RENDER_V2
#define MERAHM_RENDER_V2
#include "../fundamental/globals.h"
#include "culling.h"

int reserveSlot (int priority);

void switchSlot (int priority, int s1, int s2);

int switchPriority(int pOld, int pNew, int slot);

int addToRender (Render_t obj, int priority);

void removeFromRender (int priority, int slot);

Render_t texture2render (Texture t);

void modifyRender (int priority, int slot, RenderOptions options);

void modifyStates (int enabled, int enabledUser, int priority, int slot);

int rInit (Render_t* r, bool e, bool eu, Texture t, RenderOptions o, int p);

int rPInitBasic (Render_t* r, bool e, bool eu, const char* tPath, int p, Vector2 pos, Color tint);

int rInInitBasic (bool e, bool eu, Texture t, int p, Vector2 pos, Color tint);

int rInPInitBasic (bool e, bool eu, const char* tPath, int p, Vector2 pos, Color tint);

#define rUnInit(s, p) UnloadTexture(g_renderList[p][s].texture)

void drawRenderList (void);

#endif