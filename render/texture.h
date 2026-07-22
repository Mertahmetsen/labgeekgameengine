#ifndef MERAHM_TEXTURE
#define MERAHM_TEXTURE
#include "../fundamental/globals.h"
#include "render-groups.h"

/*int countUsedInRenderList (void) {
    int cntr = 0;
    for (int i=0; i<RENDER_LIST_SIZE; ++i) {
        if (g_renders[i].texture.id != 0) {
            cntr++;
        }
    }
    return cntr;
}*/

int findSlotInRenderList (void) {
    for (int i=0; i<RENDER_LIST_SIZE; ++i) {
        if (g_renders[i].texture.id == 0) {
            return i;
        }
    }
    return -1;
}

int addToRenderList (Texture2D texture, RenderOptions options) {
    int slot = findSlotInRenderList();
    if (slot == -1) return -1;
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
    if (g_useRenderGroups == false) {
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
    } else {
        for (int i=RENDER_GROUPS_LIST_SIZE-1; i>=0; --i) {
            if (!validateRenderGroup(g_renderGroups[i])) continue;
            for (int j=g_renderGroups[i].y; j>=g_renderGroups[i].x; --j) {
                if (g_renders[j].texture.id == 0 || !g_renders[j].enabled) continue;
                DrawTexturePro(
                    g_renders[j].texture,
                    g_renders[j].options.srcrec,
                    g_renders[j].options.dstrec,
                    g_renders[j].options.origin,
                    g_renders[j].options.rotation,
                    g_renders[j].options.tint
                );
            }
        }
    }
}

#endif