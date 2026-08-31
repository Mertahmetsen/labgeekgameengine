#include "devtools.h"

void argTools (int argc, char** argv) {
    if (argc < 2) return;
    for (int i=1; i<argc; ++i) {
        if (TextIsEqual(argv[i], "--verbosity")) {
        if (argc<i+1) {
            logBasic(E_INVPARAM);
            continue;
        }
        g_b_verboseStatus = (VerboseStatus)TextToInteger(argv[++i]);
        }
    }
}