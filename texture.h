#ifndef MERAHM_TEXTURE
#define MERAHM_TEXTURE
#include "globals.h"

int countEmptyInRenderList (void) {
    int cntr = 0;
    for (int i=0; i<RENDER_LIST_SIZE; ++i) {
        if (g_renderList[i].id != 0) {
            cntr++;
        }
    }
    return cntr;
}

int findSlotInRenderList (void) {
    for (int i=0; i<RENDER_LIST_SIZE; ++i) {
        if (g_renderList[i].id == 0) {
            return i;
        }
    }
    return -1;
}

void addToRenderList (Texture2D texture, RenderOptions options) {
    if (findSlotInRenderList() == -1) return;
    int slot = findSlotInRenderList();
    g_renderList[slot] = texture;
    g_renderOptions[slot] = options;
}

void switchRenderPriority(int slot1, int slot2) {
    if (!inScope(0, RENDER_LIST_SIZE - 1, slot1) || !inScope(0, RENDER_LIST_SIZE - 1, slot2)) return;
    if (slot1 == slot2) return;
    Texture2D tmp = g_renderList[slot1];
    g_renderList[slot1] = g_renderList[slot2];
    g_renderList[slot2] = tmp;
    RenderOptions opttmp = g_renderOptions[slot1];
    g_renderOptions[slot1] = g_renderOptions[slot2];
    g_renderOptions[slot2] = opttmp;
}

#define increaseRenderPriority(x, n) switchRenderPriority(x, x + n)
#define decreaseRenderPriority(x, n) switchRenderPriority(x, x - n)

void render (void) {
    for (int i=0; i<RENDER_LIST_SIZE; ++i) {
        if (g_renderList[i].id != 0) {
        DrawTexturePro(
        g_renderList[i],
        g_renderOptions[i].srcrec,
        g_renderOptions[i].dstrec,
        g_renderOptions[i].origin,
        g_renderOptions[i].rotation,
        g_renderOptions[i].tint);
        }
    }
}

#endif