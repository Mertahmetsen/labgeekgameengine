#include "dialoguebox.h"

void drawDialogueBox (DialogueBox dbox, float* cdown, bool* enabled)
{
    if (!enabled || !cdown) {
        TraceLogCaller(LERR, "Invalid pointers as parameters");
        return;
    }
    if (!(*enabled)) {
        TraceLogCaller(LWARN, "Dialogue box is not enabled, not drawing");
        return;
    }
    // get the textbox position
    IntVector2 tboxPos = getWindowPos(dbox.position);
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
    IntVector2 textPos = ivec(tboxBounds.x + g_tBoxTextSlideLength.x, tboxBounds.y + g_tBoxTextSlideLength.y);
    // draw the bubble and the text
    TraceLogCaller(LINFO, "Drawing textbox");
    DrawRectangleRounded(tboxBounds, g_tBoxRoundness, g_smoothingSegments, dbox.color);
    DrawRectangleRoundedLines(tboxBounds, g_tBoxRoundness, g_smoothingSegments, dbox.outline);
    DrawTextPro(dbox.font, dbox.text, vec(textPos.x, textPos.y), vec(0,0), 0.0f, dbox.fontSize, dbox.spacing, dbox.textColor);
    // disable the dialogue box when countdown hits zero.
    *enabled = !countdown(cdown);
}

void drawDialogueBoxes (DialogueBox* dboxes, const float* cdowns, size_t count)
{ // MIGHT have a memory leak idk
    TraceLogCaller(LWARN, "drawDialogueBoxes() must be used with caution");
    static float* cds = NULL;
    static size_t cap = 0, currentbox = 0;
    static bool* states = NULL;
    static bool fullinit = false;
    if (cap != count) {
        free(cds);
        cds = malloc(count * sizeof(float));
        free(states);
        states = malloc(count * sizeof(bool));
        cap = count;
        fullinit = false;
    }
    if (!fullinit) {
        memcpy(cds, cdowns, count * sizeof(float));
        for (size_t i=0; i<count; ++i) {
            states[i] = true;
        }
        fullinit = true;
    }
    while (currentbox < count && !states[currentbox]) currentbox++;
    if (currentbox >= count) return;
    drawDialogueBox(dboxes[currentbox], &cds[currentbox], &states[currentbox]);
}
