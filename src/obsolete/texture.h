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
/*
int findSlotInRenderList (void) {
    for (int i=0; i<RENDER_LIST_SIZE; ++i) {
        if (g_renders[i].texture.id == 0) {
            traceFuncInfo(__func__, TextFormat("Found empty slot in render list: %d", i));
            return i;
        }
    }
    traceFuncErr(__func__, "Could not find any empty slots in render list");
    return -1;
}

int addToRenderList (Texture2D texture, RenderOptions options) {
    int slot = findSlotInRenderList();
    if (slot == -1) {
        return -1;
        traceFuncErr(__func__, "Could not find any empty slots in render list");
    }
    g_renders[slot].texture = texture;
    g_renders[slot].options = options;
    traceFuncInfo(__func__, TextFormat("Texture %d with designated options has been located to slot %d"));
    return slot;
}

void setRender (int slot, bool state) {
    if (!inScope(0, RENDER_LIST_SIZE - 1, slot)) {
        traceFuncErr(__func__, TextFormat("Invalid slot: %d", slot));
        return;
    }
    g_renders[slot].enabled = state;
    traceFuncInfo(__func__, TextFormat("The render of the texture on slot %d has been set to %d", slot, (int)state));
}

void switchRenderPriority(int slot1, int slot2) {
    if (!inScope(0, RENDER_LIST_SIZE - 1, slot1) || !inScope(0, RENDER_LIST_SIZE - 1, slot2)) {
        traceFuncErr(__func__, "Invalid slots");
        return;
    }
    if (slot1 == slot2) {
        traceFuncWarn(__func__, "Both slots are the same?");
        return;
    }
    Render_t tmp = g_renders[slot1];
    g_renders[slot1] = g_renders[slot2];
    g_renders[slot2] = tmp;
    traceFuncInfo(__func__, TextFormat("Switched render priority of the textures in slots %d and %d", slot1, slot2));
}

#define increaseRenderPriority(x, n) switchRenderPriority(x, x + n)
#define decreaseRenderPriority(x, n) switchRenderPriority(x, x - n)

void render (void) {
    if (g_useRenderGroups == false) {
    traceFuncWarn(__func__, "g_useRenderGroups is set to false, using traditional render");
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
*/
#endif