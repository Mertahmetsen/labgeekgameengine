#include "culling.h"

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