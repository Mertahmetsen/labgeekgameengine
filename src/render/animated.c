#include "animated.h"

bool animAlloc (Animation* a)
{
    a->frames = malloc(sizeof(*a->frames) * a->totalFrames);
    if (!a->frames) return false;
    return true;
}

void animFree (Animation* a)
{
    if (!a || !a->frames) return;
    for (int i = 0; i < a->totalFrames; i++) {
        UnloadTexture(a->frames[i].texture);
    }
    free(a->frames);
    a->frames = NULL;
}

void updateAnimation (Animation* a)
{
    a->timer += g_dt;
    if (a->timer >= a->frameDuration) {
        a->timer -= a->frameDuration;
        a->currentFrame = (a->currentFrame + 1) % a->totalFrames;
        g_renderList[a->renderSlotAddress.x][a->renderSlotAddress.y] = a->frames[a->currentFrame];
    }
}

bool loadAndInitAnimation(Animation* a, const char* folderPath, int totalFrames, float frameDuration, IntVector2 slotAddress)
{
    if (!a) return false;
    a->totalFrames = totalFrames;
    a->currentFrame = 0;
    a->frameDuration = frameDuration;
    a->timer = 0.0f;
    a->renderSlotAddress = slotAddress;
    if (!animAlloc(a)) {
        return false;
    }
    char filePath[256];
    for (int i = 0; i < a->totalFrames; i++) {
        snprintf(filePath, sizeof(filePath), "%s/%06d.png", folderPath, i + 1);

        Texture2D tex = LoadTexture(filePath);
        
        // Populate Render_t data structure
        a->frames[i].texture = tex;
        a->frames[i].enabled = true;
        a->frames[i].enabledUser = true;

        // Default transform and source rectangle initialization
        a->frames[i].options.srcrec = (Rectangle){ 0.0f, 0.0f, (float)tex.width, (float)tex.height };
        a->frames[i].options.dstrec = (Rectangle){ 0.0f, 0.0f, (float)tex.width, (float)tex.height };
        a->frames[i].options.origin = (Vector2){ 0.0f, 0.0f };
        a->frames[i].options.rotation = 0.0f;
        a->frames[i].options.tint = WHITE;
    }
    // Write initial frame state to the target slot in g_renderList
    if (a->totalFrames > 0) {
        g_renderList[a->renderSlotAddress.x][a->renderSlotAddress.y] = a->frames[0];
    }
    return true;
}
