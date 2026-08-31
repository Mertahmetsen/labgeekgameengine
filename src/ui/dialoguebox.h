#ifndef MERAHM_DIALOGUEBOX
#define MERAHM_DIALOGUEBOX
#include "../fundamental/globals.h"
#include "../ui/window-pos.h"
#include "../fundamental/time.h"

void drawDialogueBox (DialogueBox dbox, float* cdown, bool* enabled);

void drawDialogueBoxes (DialogueBox* dboxes, const float* cdowns, size_t count);

#endif