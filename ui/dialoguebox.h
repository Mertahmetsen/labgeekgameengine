#ifndef MERAHM_DIALOGUEBOX
#define MERAHM_DIALOGUEBOX
#include "../fundamental/globals.h"
#include "../ui/window-pos.h"
#include "../fundamental/time.h"

void drawDialogueBox (DialogueBox dbox, float* cdown, bool* enabled) {
    if (!enabled || !cdown || !(*enabled)) return;
    // get the textbox position
    IntVector tboxPos = getWindowPos(dbox.position);
    // get the boundary
    Rectangle tboxBounds = boundaryEx(tboxPos.x, tboxPos.y, dbox.text, dbox.font, dbox.fontSize, dbox.spacing);
    // slide the textbox to the center and prevent out-of-bounds rendering (idk what im doing)
    switch (dbox.position) {
        case TOPLEFT:
            tboxPos = ivec(tboxPos.x + g_tBoxSlideLength.x, tboxPos.y + g_tBoxSlideLength.y);
            break;
        case TOPRIGHT:
            tboxPos = ivec(tboxPos.x - tboxBounds.width - g_tBoxSlideLength.x,
            tboxPos.y + g_tBoxSlideLength.y);
            break;
        case BOTLEFT:
            tboxPos = ivec(tboxPos.x + g_tBoxSlideLength.x, tboxPos.y - tboxBounds.height - g_tBoxSlideLength.y);
            break;
        case BOTRIGHT:
            tboxPos = ivec(tboxPos.x - g_tBoxSlideLength.x - tboxBounds.width,
            tboxPos.y - g_tBoxSlideLength.y - tboxBounds.height);
            break;
        case MID:
        default:
            return; // its midnight and i CANNOT be bothered to write this.
    }
    // re-set bounds with the new position
    tboxBounds.x = tboxPos.x;
    tboxBounds.y = tboxPos.y;
    // calculate where to draw the text
    IntVector textPos = ivec(tboxBounds.x + g_tBoxTextSlideLength.x, tboxBounds.y + g_tBoxTextSlideLength.y);
    // draw the bubble and the text
    DrawRectangleRounded(tboxBounds, g_tBoxRoundness, g_smoothingSegments, dbox.color);
    DrawRectangleRoundedLines(tboxBounds, g_tBoxRoundness, g_smoothingSegments, dbox.outline);
    DrawTextPro(dbox.font, dbox.text, vec(textPos.x, textPos.y), vec(0,0), 0.0f, dbox.fontSize, dbox.spacing, dbox.textColor);
    // disable the dialogue box when countdown hits zero.
    *enabled = !countdown(cdown);
    // DEBUG
    DrawText(TextFormat("%f,%f", tboxBounds.x, tboxBounds.y), -400, 160, 20, RED);
}

#endif