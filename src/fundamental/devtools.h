#ifndef MERAHM_DEVTOOLS
#define MERAHM_DEVTOOLS
#include "../fundamental/globals.h"

void devTools (int argc, char** argv);

#ifdef LABGEEK_IMPLEMENTATION
void devTools (int argc, char** argv) {
    if (argc > 1) {
        for (int i=1; i<argc; ++i) {
            if (TextIsEqual(argv[i], "--verbosity") && argc > 2) {
                int vb = TextToInteger(argv[++i]);
                if (!inScope(0, 4, vb)) {
                    logHandler(LOG_ERROR, "Verbosity state invalid.");
                    return;
                }
                g_b_verboseStatus = (VerboseStatus)vb;
            }
        }
    }
}
#endif

#endif