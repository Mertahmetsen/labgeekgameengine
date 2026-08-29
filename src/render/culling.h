#ifndef MERAHM_CULLING
#define MERAHM_CULLING
#include "../fundamental/basic.h"
#include "../fundamental/globals.h"
#include "raymath.h"

Rectangle GetCameraWorldAABB(Camera2D camera) {
    float sw = (float)GetScreenWidth();
    float sh = (float)GetScreenHeight();

    // Transform 4 screen corners to world space
    Vector2 corners[4] = {
        GetScreenToWorld2D((Vector2){ 0, 0 }, camera),
        GetScreenToWorld2D((Vector2){ sw, 0 }, camera),
        GetScreenToWorld2D((Vector2){ sw, sh }, camera),
        GetScreenToWorld2D((Vector2){ 0, sh }, camera)
    };

    // Find min and max bounds to create an enclosing AABB
    Vector2 min = corners[0];
    Vector2 max = corners[0];

    for (int i = 1; i < 4; i++) {
        if (corners[i].x < min.x) min.x = corners[i].x;
        if (corners[i].y < min.y) min.y = corners[i].y;
        if (corners[i].x > max.x) max.x = corners[i].x;
        if (corners[i].y > max.y) max.y = corners[i].y;
    }

    return (Rectangle){ min.x, min.y, max.x - min.x, max.y - min.y };
}

// 2. CALL THIS INSIDE YOUR RENDER LOOP FOR EACH OBJECT
// Ultra-fast culling check using bounding radius.
bool IsRenderableVisibleFast(Rectangle cameraAABB, const Render_t *renderable) {
    // Early exit if disabled
    if (!renderable || !renderable->enabled || !renderable->enabledUser) {
        return false;
    }

    const RenderOptions *opts = &renderable->options;

    // Approximate the object's extent using its diagonal radius.
    // This safely accounts for ANY texture rotation around its origin.
    float halfWidth = opts->dstrec.width * 0.5f;
    float halfHeight = opts->dstrec.height * 0.5f;
    
    // Radius of bounding circle enclosing the texture quad
    float radius = sqrtf(halfWidth * halfWidth + halfHeight * halfHeight);

    // Center of the destination rectangle in world space
    float centerX = opts->dstrec.x + halfWidth - opts->origin.x;
    float centerY = opts->dstrec.y + halfHeight - opts->origin.y;

    // Fast AABB vs Circle-Bounding-Box check (4 float comparisons)
    if (centerX + radius < cameraAABB.x || 
        centerX - radius > cameraAABB.x + cameraAABB.width ||
        centerY + radius < cameraAABB.y || 
        centerY - radius > cameraAABB.y + cameraAABB.height) {
        return false; // Safely culled!
    }

    return true;
}

void InitTestRenderList(Texture2D placeholderTexture) {
    for (int c = 0; c < RENDERLISTCOUNT; c++) {
        for (int s = 0; s < RENDERLISTSIZE; s++) {
            Render_t *item = &g_renderList[c][s];

            // Assign the loaded placeholder texture
            item->texture = placeholderTexture;
            item->enabled = true;
            item->enabledUser = true;

            // Source rectangle (entire texture)
            item->options.srcrec = (Rectangle){
                0.0f, 0.0f,
                (float)placeholderTexture.width,
                (float)placeholderTexture.height
            };

            // Spread 65,536 objects across a 10,000 x 10,000 world grid
            float posX = (float)(rand() % 10000 - 5000);
            float posY = (float)(rand() % 10000 - 5000);

            // Set destination rectangle size (e.g., 64x64 sprites)
            item->options.dstrec = (Rectangle){ posX, posY, 64.0f, 64.0f };

            // Center origin for rotation
            item->options.origin = (Vector2){ 32.0f, 32.0f };

            // Random rotation (0 to 360 degrees)
            item->options.rotation = (float)(rand() % 360);

            // Tint color
            item->options.tint = WHITE;
        }
    }
}

#endif