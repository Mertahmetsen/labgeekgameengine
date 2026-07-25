#ifndef MERAHM_DBOXPARSE
#define MERAHM_DBOXPARSE
#include "tokenize.h"
#include "../fundamental/basic.h"

WindowPos parseWindowPos(const char* str) {
    traceFuncInfo(__func__, TextFormat("Interpreting '%s'", str));
    if (!strcmp(str, "TOPLEFT"))  return TOPLEFT;
    if (!strcmp(str, "TOPRIGHT")) return TOPRIGHT;
    if (!strcmp(str, "BOTLEFT"))  return BOTLEFT;
    if (!strcmp(str, "BOTRIGHT")) return BOTRIGHT;
    if (!strcmp(str, "MID"))      return MID;
    traceFuncErr(__func__, "Unknown window position");
    return TOPLEFT;
}

Color parseColor(const char *str)
{
    traceFuncInfo(__func__, TextFormat("Interpreting '%s'", str));
    if (!strcmp(str, "WHITE")) return WHITE;
    if (!strcmp(str, "BLACK")) return BLACK;
    if (!strcmp(str, "RED"))   return RED;
    if (!strcmp(str, "GREEN")) return GREEN;
    if (!strcmp(str, "BLUE"))  return BLUE;
    if (!strcmp(str, "YELLOW"))return YELLOW;
    traceFuncErr(__func__, "Unknown color");
    return WHITE;
}

DialogueBox loadDBox (const char* path, Font f) {
    const char* delim = "\n\r,";
    DialogueBox box;
    char* first = loadAndTokenize(path, delim);
    box.text      = strdup(first);
    box.font      = f;
    box.fontSize  = atof(loadAndTokenize(NULL, delim));
    box.spacing   = atof(loadAndTokenize(NULL, delim));
    box.position  = parseWindowPos(loadAndTokenize(NULL, delim));
    box.color     = parseColor(loadAndTokenize(NULL, delim));
    box.outline   = parseColor(loadAndTokenize(NULL, delim));
    box.textColor = parseColor(loadAndTokenize(NULL, delim));
    traceFuncInfo(__func__, TextFormat("%d,%d,%d,%d", box.textColor.r, box.textColor.g, box.textColor.b, box.textColor.a));
    return box;
}

#endif