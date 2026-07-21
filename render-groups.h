#ifndef MERAHM_RENDER_GROUPS
#define MERAHM_RENDER_GROUPS
#include "globals.h"

int findEmptyRenderGroup (void) {
    for (int i=0; i<RENDER_GROUPS_LIST_SIZE; ++i) {
        if (g_renderGroups[i].x == (IntVector){0}.x && g_renderGroups[i].y == (IntVector){0}.y) {
            return i;
        }
    }
    return -1;
}

bool validateRenderGroup(IntVector scope) {
    return (bool) (
        inScope(0, RENDER_GROUPS_LIST_SIZE-1, scope.x) &&
        inScope(0, RENDER_GROUPS_LIST_SIZE-1, scope.y) &&
        (scope.x < scope.y)
    );
}

bool validateRenderGroupSlot (int slot) {
    return inScope(0, RENDER_GROUPS_LIST_SIZE-1, slot);
}

int addRenderGroup(IntVector scope) {
    int slot = findEmptyRenderGroup();
    if (slot == -1) return -1;
    if (validateRenderGroup(scope) == false) return -1;
    g_renderGroups[slot] = scope;
    return slot;
}

void removeRenderGroup(int slot) {
    g_renderGroups[slot] = (IntVector){0};
}

void setRenderGroups (bool state) {
    g_useRenderGroups = state;
}

void switchRenderGroupPriority (int slot1, int slot2) {
    if (!validateRenderGroupSlot(slot1) || !validateRenderGroupSlot(slot2)) return;
    IntVector tmp = g_renderGroups[slot1];
    g_renderGroups[slot1] = g_renderGroups[slot2];
    g_renderGroups[slot2] = tmp;
}

#endif