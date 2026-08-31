#include "render.h"

int reserveSlot (int priority)
{
    if (!inScope(0, RENDERLISTCOUNT-1, priority)) {
        TraceLogCaller(LERR, "Invalid priority: %d", priority);
        return -1;
    }
    for (int i=0; i<RENDERLISTSIZE; ++i) {
        if (g_renderList[priority][i].texture.id == 0) {
            TraceLogCaller(LINFO, "Found unoccupied slot %d with priority %d", i, priority);
            return i;
        }
    }
    TraceLogCaller(LERR, "Could not find any unoccupied slots with priority %d", priority);
    return -1;
}

void switchSlot (int priority, int s1, int s2)
{
    if (
        s1 == s2
        LOGIC_OR
        !inScope(0, RENDERLISTSIZE-1, s1)
        LOGIC_OR
        !inScope(0, RENDERLISTSIZE-1, s2)
        LOGIC_OR
        !inScope(0, RENDERLISTCOUNT-1, priority)
    ) {
        TraceLogCaller(LERR, "Invalid parameters");
        return;
    }
    Render_t tmp = g_renderList[priority][s1];
    g_renderList[priority][s1] = g_renderList[priority][s2];
    g_renderList[priority][s2] = tmp;
    TraceLogCaller(LINFO, "Switched render objects [%d][%d] and [%d][%d]", priority, s1, priority, s2);
}

int switchPriority(int pOld, int pNew, int slot)
{
    if (
        pOld == pNew
        LOGIC_OR
        !inScope(0, RENDERLISTCOUNT-1, pOld)
        LOGIC_OR
        !inScope(0, RENDERLISTCOUNT-1, pNew)
        LOGIC_OR
        !inScope(0, RENDERLISTSIZE-1, slot)
    ) {
        TraceLogCaller(LERR, "Invalid parameters.");
        return -1;
    }
    const int newSlot = reserveSlot(pNew);
    if (newSlot == -1) {
        TraceLogCaller(LERR, "Could not reserve slot");
        return -1;
    }
    Render_t tmp = g_renderList[pOld][slot];
    g_renderList[pOld][slot] = g_renderList[pNew][newSlot];
    g_renderList[pNew][newSlot] = tmp;
    TraceLogCaller(LINFO, "Switched Render Objects [%d][%d] and [%d][%d]", pOld, slot, pNew, slot);
    return newSlot;
}

int addToRender (Render_t obj, int priority)
{
    const int slot = reserveSlot(priority);
    if (slot == -1) {
        TraceLogCaller(LERR, "Could not reserve slot.");
        return -1;
    }
    g_renderList[priority][slot] = obj;
    TraceLogCaller(LINFO, "Located given image to address [%d][%d]", priority, slot);
    return slot;
}

void removeFromRender (int priority, int slot)
{
    if (
        !inScope(0, RENDERLISTCOUNT-1, priority)
        LOGIC_OR
        !inScope(0, RENDERLISTSIZE-1, slot)
    ) {
        TraceLogCaller(LERR, "Invalid parameters.");
        return;
    }
    g_renderList[priority][slot] = (Render_t){0};
    TraceLogCaller(LINFO, "Removed image [%d][%d] from render list", priority, slot);
}

Render_t texture2render (Texture t)
{
    return (Render_t) {
        .texture = t
    };
}

void modifyRender (int priority, int slot, RenderOptions options)
{
    g_renderList[priority][slot].options = options;
}

void modifyStates (int enabled, int enabledUser, int priority, int slot)
{
    g_renderList[priority][slot].enabled = enabled;
    g_renderList[priority][slot].enabledUser = enabledUser;
}

int rInit (Render_t* r, bool e, bool eu, Texture t, RenderOptions o, int p)
{
    r->enabled = e;
    r->enabledUser = eu;
    r->options = o;
    r->texture = t;
    return addToRender(*r, p);
}

int rPInitBasic (Render_t* r, bool e, bool eu, const char* tPath, int p, Vector2 pos, Color tint)
{
    Texture t = LoadTexture(tPath);
    if (t.id == 0) {
        logBasic(E_INTERNAL);
        return -1;
    }
    return rInit(r, e, eu, t, roptbasic(pos, t, tint), p);
}

int rInInitBasic (bool e, bool eu, Texture t, int p, Vector2 pos, Color tint)
{ // r defined inside
    Render_t r;
    return rInit(&r, e, eu, t, roptbasic(pos, t, tint), p);
}

int rInPInitBasic (bool e, bool eu, const char* tPath, int p, Vector2 pos, Color tint)
{
    Texture t = LoadTexture(tPath);
    if (t.id == 0) {
        logBasic(E_INTERNAL);
        return -1;
    }
    return rInInitBasic(e, eu, t, p, pos, tint);
}

void drawRenderList(void)
{
    TraceLogCaller(LOG_ERROR, "Called.");

    g_dCamAABB = GetCameraWorldAABB(g_dCam);

    for (int i = RENDERLISTCOUNT - 1; i >= 0; --i) {
        for (int j = RENDERLISTSIZE - 1; j >= 0; --j) {

            Render_t *r = &g_renderList[i][j];

            if (
                r->texture.id == 0 ||
                !r->enabled ||
                !r->enabledUser ||
                !IsRenderableVisibleFast(g_dCamAABB, r)
            ) {
                continue;
            }

            TraceLogCaller(
                LOG_ERROR,
                "%d,%d,%d,%d,%d,%d",
                r->texture.id,
                r->enabled,
                r->enabledUser,
                i,
                j,
                IsRenderableVisibleFast(g_dCamAABB, r)
            );

            DrawTexturePro(
                r->texture,
                r->options.srcrec,
                r->options.dstrec,
                r->options.origin,
                r->options.rotation,
                r->options.tint
            );
        }
    }
}