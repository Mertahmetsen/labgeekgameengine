#ifndef MERAHM_RENDER_V2
#define MERAHM_RENDER_V2
#include "../fundamental/globals.h"

int reserveSlot (int priority);
void switchSlot (int priority, int s1, int s2);
int switchPriority (int pOld, int pNew, int slot);
int addToRender (Render_t obj, int priority);
void removeFromRender (int priority, int slot);
Render_t texture2render (Texture t);
void modifyRender (int priority, int slot, RenderOptions options);
void modifyStates (int enabled, int enabledUser, int priority, int slot);
void drawRenderList (void);

#ifdef LABGEEK_IMPLEMENTATION
int reserveSlot (int priority) {
    if (!inScope(0, RENDERLISTCOUNT-1, priority)) {
        traceFuncErr(__func__, TextFormat("Invalid priority: %d", priority));
        return -1;
    }
    for (int i=0; i<RENDERLISTSIZE; ++i) {
        if (g_renderList[priority][i].texture.id == 0) {
            traceFuncInfo(__func__, TextFormat("Found unoccupied slot %d with priority %d", i, priority));
            return i;
        }
    }
    traceFuncErr(__func__, TextFormat("Could not find any unoccupied slots with priority %d", priority));
    return -1;
}

void switchSlot (int priority, int s1, int s2) {
    if (
        s1 == s2
        LOGIC_OR
        !inScope(0, RENDERLISTSIZE-1, s1)
        LOGIC_OR
        !inScope(0, RENDERLISTSIZE-1, s2)
        LOGIC_OR
        !inScope(0, RENDERLISTCOUNT-1, priority)
    ) {
        traceFuncErr(__func__, "Invalid parameters");
        return;
    }
    Render_t tmp = g_renderList[priority][s1];
    g_renderList[priority][s1] = g_renderList[priority][s2];
    g_renderList[priority][s2] = tmp;
    traceFuncInfo(__func__, TextFormat("Switched render objects [%d][%d] and [%d][%d]", priority, s1, priority, s2));
}

int switchPriority(int pOld, int pNew, int slot) {
    if (
        pOld == pNew
        LOGIC_OR
        !inScope(0, RENDERLISTCOUNT-1, pOld)
        LOGIC_OR
        !inScope(0, RENDERLISTCOUNT-1, pNew)
        LOGIC_OR
        !inScope(0, RENDERLISTSIZE-1, slot)
    ) {
        traceFuncErr(__func__, "Invalid parameters.");
        return -1;
    }
    const int newSlot = reserveSlot(pNew);
    if (newSlot == -1) {
        traceFuncErr(__func__, "Could not reserve slot.");
        return -1;
    }
    Render_t tmp = g_renderList[pOld][slot];
    g_renderList[pOld][slot] = g_renderList[pNew][newSlot];
    g_renderList[pNew][newSlot] = tmp;
    traceFuncInfo(__func__, TextFormat("Switched Render Objects [%d][%d] and [%d][%d]", pOld, slot, pNew, slot));
    return newSlot;
}

int addToRender (Render_t obj, int priority) {
    const int slot = reserveSlot(priority);
    if (slot == -1) {
        traceFuncErr(__func__, "Could not reserve slot.");
        return -1;
    }
    g_renderList[priority][slot] = obj;
    traceFuncInfo(__func__, TextFormat("Located given image to address [%d][%d]", priority, slot));
    return slot;
}

void removeFromRender (int priority, int slot) {
    if (
        !inScope(0, RENDERLISTCOUNT-1, priority)
        LOGIC_OR
        !inScope(0, RENDERLISTSIZE-1, slot)
    ) {
        traceFuncErr(__func__, "Invalid parameters.");
        return;
    }
    g_renderList[priority][slot] = (Render_t){0};
    traceFuncInfo(__func__, TextFormat("Removed image [%d][%d] from render list", priority, slot));
}

Render_t texture2render (Texture t) {
    return (Render_t) {
        .texture = t
    };
}

void modifyRender (int priority, int slot, RenderOptions options) {
    g_renderList[priority][slot].options = options;
}

void modifyStates (int enabled, int enabledUser, int priority, int slot) {
    g_renderList[priority][slot].enabled = enabled;
    g_renderList[priority][slot].enabledUser = enabledUser;
}

void drawRenderList (void) {
    for (int i=RENDERLISTCOUNT-1; i>=0; --i) {
        for (int j=RENDERLISTSIZE-1; j>=0; --j) {
            if (
                g_renderList[i][j].texture.id == 0
                LOGIC_OR
                !g_renderList[i][j].enabled
                LOGIC_OR
                !g_renderList[i][j].enabledUser
            ) {continue;}
            DrawTexturePro(
                g_renderList[i][j].texture,
                g_renderList[i][j].options.srcrec,
                g_renderList[i][j].options.dstrec,
                g_renderList[i][j].options.origin,
                g_renderList[i][j].options.rotation,
                g_renderList[i][j].options.tint
            );
        }
    }
}
#endif

#endif