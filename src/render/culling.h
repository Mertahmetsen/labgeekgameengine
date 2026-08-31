#ifndef MERAHM_CULLING
#define MERAHM_CULLING
#include "../fundamental/basic.h"
#include "../fundamental/globals.h"
#include "raymath.h"

Rectangle GetCameraWorldAABB(Camera2D camera);

// 2. CALL THIS INSIDE YOUR RENDER LOOP FOR EACH OBJECT
// Ultra-fast culling check using bounding radius.
bool IsRenderableVisibleFast(Rectangle cameraAABB, const Render_t *renderable);

#endif