#ifndef MERAHM_TEXTURE
#define MERAHM_TEXTURE
#include "globals.h"

int countEmptyInRenderList (void) {
    int cntr = 0;
    for (int i=0; i<RENDER_LIST_SIZE; ++i) {
        if (g_renders[i].texture.id != 0) {
            cntr++;
        }
    }
    return cntr;
}

int findSlotInRenderList (void) {
    for (int i=0; i<RENDER_LIST_SIZE; ++i) {
        if (g_renders[i].texture.id == 0) {
            return i;
        }
    }
    return -1;
}

int addToRenderList (Texture2D texture, RenderOptions options) {
    if (findSlotInRenderList() == -1) return -1;
    int slot = findSlotInRenderList();
    g_renders[slot].texture = texture;
    g_renders[slot].options = options;
    return slot;
}

void setRender (int slot, bool state) {
    if (!inScope(0, RENDER_LIST_SIZE - 1, slot)) return;
    g_renders[slot].enabled = state;
}

void switchRenderPriority(int slot1, int slot2) {
    if (!inScope(0, RENDER_LIST_SIZE - 1, slot1) || !inScope(0, RENDER_LIST_SIZE - 1, slot2)) return;
    if (slot1 == slot2) return;
    Render_t tmp = g_renders[slot1];
    g_renders[slot1] = g_renders[slot2];
    g_renders[slot2] = tmp;
}

#define increaseRenderPriority(x, n) switchRenderPriority(x, x + n)
#define decreaseRenderPriority(x, n) switchRenderPriority(x, x - n)

void render (void) {
    for (int i=RENDER_LIST_SIZE-1; i>=0; --i) {
        if (g_renders[i].texture.id != 0 && g_renders[i].enabled == true) {
        DrawTexturePro(
        g_renders[i].texture,
        g_renders[i].options.srcrec,
        g_renders[i].options.dstrec,
        g_renders[i].options.origin,
        g_renders[i].options.rotation,
        g_renders[i].options.tint);
        }
    }
}

#endif