#ifndef MERAHM_MAPS
#define MERAHM_MAPS
#include "../fundamental/basic.h"
#include "../fundamental/devtools.h"

bool reshapeIncludesForMap (const char* mapHeaderPath) {
    const char* text = TextFormat("#ifndef LGEEK_CMAP\n#define LGEEK_CMAP\n#include \"../../../%s\"\n#endif", mapHeaderPath);
    return SaveFileText(g_b_currentMapHeaderPath, text);
}

int loadMap (const char* mapHeaderPath, int argc, char** argv) {
    if (!FileExists(mapHeaderPath)) {
        TraceLogCaller(LERR, "Map \"%s\" does not exist, loading fallback map.", mapHeaderPath);
        const char* text = "#ifndef LGEEK_CMAP\n#define LGEEK_CMAP\n#include \"fallback.h\"\n#endif\n";
        if (!SaveFileText(g_b_currentMapHeaderPath, text)) {
            logBasic(E_UNSPEC);
            return -1;
        }
        return recompileBinary(argc, argv);
    }
    if (!reshapeIncludesForMap(mapHeaderPath)) {
        logBasic(E_UNSPEC);
        return -1;
    }
    return recompileBinary(argc, argv);
}

void mapLoadingScreen (void) {
    BeginDrawing();
    ClearBackground(WHITE);
    DrawText("Loading map...", g_windowW/2, g_windowH/2 ,20, BLACK);
    EndDrawing();
}

#endif