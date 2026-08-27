#ifndef MERAHM_RENDER_GROUPS
#define MERAHM_RENDER_GROUPS
#include "../fundamental/globals.h"
/*
int findEmptyRenderGroup (void) {
    for (int i=0; i<RENDER_GROUPS_LIST_SIZE; ++i) {
        if (g_renderGroups[i].x == (IntVector2){0}.x && g_renderGroups[i].y == (IntVector2){0}.y) {
            traceFuncInfo(__func__, TextFormat("Found new empty render group slot: %d", i));
            return i;
        }
    }
    return -1;
    traceFuncErr(__func__, "Could not find an empty render group slot.");
}

bool validateRenderGroup(IntVector2 scope) {
    traceFuncInfo(__func__, TextFormat("Validating render group: %d,%d", scope.x, scope.y));
    return (bool) (
        inScope(0, RENDER_GROUPS_LIST_SIZE-1, scope.x) &&
        inScope(0, RENDER_GROUPS_LIST_SIZE-1, scope.y) &&
        (scope.x < scope.y)
    );
}

bool validateRenderGroupSlot (int slot) {
    traceFuncInfo(__func__, TextFormat("Validating render group slot: %d", slot));
    return inScope(0, RENDER_GROUPS_LIST_SIZE-1, slot);
}

int addRenderGroup(IntVector2 scope) {
    int slot = findEmptyRenderGroup();
    if (slot == -1) {
        traceFuncErr(__func__, "Could not find any empty render group slots.");
        return -1;
    }
    if (validateRenderGroup(scope) == false) {
        traceFuncErr(__func__, TextFormat("Invalid render group: %d,%d", scope.x, scope.y));
        return -1;
    }
    g_renderGroups[slot] = scope;
    traceFuncInfo(__func__, TextFormat("Render group (%d,%d) has been located to slot %d", scope.x, scope.y, slot));
    return slot;
}

void removeRenderGroup(int slot) {
    g_renderGroups[slot] = (IntVector2){0};
    traceFuncInfo(__func__, TextFormat("Removed the render group in slot %d", slot));
}

void setRenderGroups (bool state) {
    g_useRenderGroups = state;
    traceFuncInfo(__func__, TextFormat("g_useRenderGroups has been set to %d", (int)state));
}

void switchRenderGroupPriority (int slot1, int slot2) {
    if (!validateRenderGroupSlot(slot1) || !validateRenderGroupSlot(slot2)) {
        traceFuncErr(__func__, "Invalid render group slot");
        return;
    }
    IntVector2 tmp = g_renderGroups[slot1];
    g_renderGroups[slot1] = g_renderGroups[slot2];
    g_renderGroups[slot2] = tmp;
    traceFuncInfo(__func__, TextFormat("The render groups at slots %d and %d has swapped priority", slot1, slot2));
}
*/
#endif