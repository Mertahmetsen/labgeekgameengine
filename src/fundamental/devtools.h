#ifndef MERAHM_DEVTOOLS
#define MERAHM_DEVTOOLS
#include "basic.h"

int recompileBinary (int argc, char** argv) {
    if (g_b_alreadyRecompiled) return 0;
    int result = system(TextFormat("gcc %s -o %s %s", g_b_mainSourcePath, g_b_binaryName, g_b_gccFlags));
    if (result != 0) {
        TraceLogCaller(LERR, "Could not recompile: GCC exited with code %d", result);
        return result;
    }
    char** newArgv = malloc ((argc+2)*sizeof(*newArgv));
    if (!newArgv) {
        logBasic(E_NOMEM);
        return -1;
    }
    newArgv[0] = argv[0];
    newArgv[1] = "--skip-recompilation";
    for (int i=1; i<argc; ++i) {
        newArgv[i+1] = argv[i];
    }
    newArgv[argc+1] = NULL;

    execv("./bin", newArgv);
    TraceLogCaller(LERR, "Internal error: execv failed.");
    free(newArgv);
    return -1;
}

void argTools (int argc, char** argv) {
    if (argc < 2) return;
    for (int i=1; i<argc; ++i) {
        if (TextIsEqual(argv[i], "--skip-recompilation")) { // use before --recompile
            g_b_alreadyRecompiled = true;
        }
        else if (TextIsEqual(argv[i], "--verbosity")) {
            if (argc<i+1) {
                logBasic(E_INVPARAM);
                return;
            }
            g_b_verboseStatus = (VerboseStatus)TextToInteger(argv[++i]);
        }
        else if (TextIsEqual(argv[i], "--recompile")) {
            const int rbin = recompileBinary(argc, argv);
            if (rbin != 0) {
                TraceLogCaller(LERR, "Compilation failed: Compilation function returned %d", rbin);
            }
        }
    }
}

#endif