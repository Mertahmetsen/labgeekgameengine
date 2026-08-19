#ifndef MERAHM_MAP_FALLBACK
#define MERAHM_MAP_FALLBACK
#include "../fundamental/basic.h"

#ifndef LGEEK_CMAP
void map_onLoad (void) {
    TraceLogCaller(LWARN, "Fallback map loaded, doing nothing.");
}
void map_onUpdate (void) {
    TraceLogCaller(LWARN, "Fallback map update, doing nothing.");
}
void map_onFinish (void) {
    TraceLogCaller(LWARN, "Fallback map finished, doing nothing.");
}
#endif

#endif