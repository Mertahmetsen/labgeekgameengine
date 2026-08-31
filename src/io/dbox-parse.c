#include "dbox-parse.h"

WindowPos parseWindowPos(const char* str)
{
    TraceLogCaller(LOG_INFO, "Interpreting '%s'", str);
    if (!strcmp(str, "TOPLEFT"))  return TOPLEFT;
    if (!strcmp(str, "TOPRIGHT")) return TOPRIGHT;
    if (!strcmp(str, "BOTLEFT"))  return BOTLEFT;
    if (!strcmp(str, "BOTRIGHT")) return BOTRIGHT;
    if (!strcmp(str, "MID"))      return MID;
    TraceLogCaller(LERR, "Unknown window position");
    return TOPLEFT;
}

Color parseColor(const char *str)
{
    TraceLogCaller(LOG_INFO, "Interpreting '%s'", str);
    if (!strcmp(str, "WHITE")) return WHITE;
    if (!strcmp(str, "BLACK")) return BLACK;
    if (!strcmp(str, "RED"))   return RED;
    if (!strcmp(str, "GREEN")) return GREEN;
    if (!strcmp(str, "BLUE"))  return BLUE;
    if (!strcmp(str, "YELLOW"))return YELLOW;
    TraceLogCaller(LERR, "Unknown color");
    return WHITE;
}