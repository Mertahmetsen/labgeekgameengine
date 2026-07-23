#ifndef MERAHM_TOKENIZE
#define MERAHM_TOKENIZE
#include <string.h>
#include "raylib.h"

static char* str = NULL;
static char* rest = NULL;

char* loadAndTokenize(const char* path, const char* delim) {
    if (str == NULL) {
        str = LoadFileText(path);
        if (!str) return NULL;
        rest = str;
    }
    char* token = strtok_r(NULL, delim, &rest);
    return token;
}

void resetTokenizer(void) {
    if (str) {
        UnloadFileText(str);
        str = NULL;
        rest = NULL;
    }
}

#endif