#ifndef MERAHM_RESOURCE
#define MERAHM_RESOURCE
#include "../fundamental/basic.h"
#include <stddef.h>

DialogueBox dbxf2dbox(DBoxFile dbxf, float* lifetime, bool* enabled);

DialogueBox loadDBFile (const char* path, float* lifetime, bool* enabled);

#endif