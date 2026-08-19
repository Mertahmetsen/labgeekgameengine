#ifndef MERAHM_MAPS
#define MERAHM_MAPS
#include "../fundamental/basic.h"
#include "../fundamental/devtools.h"

bool reshapeIncludesForMap (const char* mapHeaderPath) {
    const char* text = TextFormat("#ifndef LGEEK_CMAP\n#define LGEEK_CMAP\n#include \"../../../%s\"\n#endif", mapHeaderPath);
    return SaveFileText(g_b_currentMapHeaderPath, text);
}

int loadMap (const char* mapHeaderPath, int argc, char** argv) {
    if (!reshapeIncludesForMap(mapHeaderPath)) {
        logBasic(E_UNSPEC);
        return -1;
    }
    return recompileBinary(argc, argv);
}

#endif