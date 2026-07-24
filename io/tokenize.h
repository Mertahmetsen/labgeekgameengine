#ifndef MERAHM_TOKENIZE
#define MERAHM_TOKENIZE
#include <string.h>
#include "raylib.h"

char *loadAndTokenize(const char *path, const char *delim)
{
    static char *text = NULL;
    static char *rest = NULL;
    if (path != NULL)
    {
        if (text) UnloadFileText(text);
        text = LoadFileText(path);
        if (!text) return NULL;
        rest = text;
        return strtok_r(text, delim, &rest);
    }
    return strtok_r(NULL, delim, &rest);
}

#endif