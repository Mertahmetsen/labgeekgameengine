#include "basic.h"

VerboseStatus g_b_verboseStatus = ALL;
char g_filterFuncBuffer[DIR_MAX_LEN] = {0};
char* filterFunc = NULL;

Rectangle boundary (float x, float y, const char* text, Font font)
{
  const Vector2 size = MeasureTextEx(font, text, GuiGetStyle(DEFAULT, TEXT_SIZE), GuiGetStyle(DEFAULT, TEXT_SPACING));
  return (Rectangle) {x, y, size.x, size.y};
}

Rectangle boundaryEx (float x, float y, const char* text, Font font, float fontsize, float spacing)
{
  Vector2 size = MeasureTextEx(font, text, fontsize, spacing);
  return (Rectangle){ x, y, size.x, size.y };
}

void guiSetAll (Font f, int textsize, int textspacing, int borderwidth)
{
  GuiSetFont(f);
  GuiSetStyle(DEFAULT, TEXT_SIZE, textsize);
  GuiSetStyle(DEFAULT, TEXT_SPACING, textspacing);
  GuiSetStyle(DEFAULT, BORDER_WIDTH, borderwidth);
  GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
}

bool inScope (int min, int max, int x)
{
  if (x > max || x < min) return false;
  return true;
}

void logHandler(int logtype, const char *format, va_list args)
{
    char buffer[MAX_LOG_LEN];
    switch (g_b_verboseStatus) {
        case ALL:
            if (logtype != LOG_ERROR &&
                logtype != LOG_FATAL &&
                logtype != LOG_WARNING &&
                logtype != LOG_INFO)
                return;
            break;

        case ERRNWARN:
            if (logtype != LOG_ERROR &&
                logtype != LOG_FATAL &&
                logtype != LOG_WARNING)
                return;
            break;

        case ERR:
            if (logtype != LOG_ERROR &&
                logtype != LOG_FATAL)
                return;
            break;

        case COMPLETE:
            break;

        case NONE:
        default:
            return;
    }
    vsnprintf(buffer, sizeof(buffer), format, args);
    if (filterFunc != NULL && filterFunc[0] != '\0') {
      char targetBracket[DIR_MAX_LEN];
      snprintf(targetBracket, sizeof(targetBracket), "[%s]", filterFunc);
      if (strstr(buffer, targetBracket) == NULL) {
        return;
      }
    }
    const char* colorCode = ANSI_COLOR_RESET;
    switch (logtype) {
        case LOG_TRACE:
        case LOG_DEBUG:
            colorCode = ANSI_COLOR_GRAY;
            break;
        case LOG_INFO:
            colorCode = ANSI_COLOR_GREEN;
            break;
        case LOG_WARNING:
            colorCode = ANSI_COLOR_YELLOW;
            break;
        case LOG_ERROR:
        case LOG_FATAL:
            colorCode = ANSI_COLOR_RED;
            break;
        default:
            colorCode = ANSI_COLOR_RESET;
            break;
    }
    printf("%s%s" ANSI_COLOR_RESET "\n", colorCode, buffer);
}

void initLogHandler (VerboseStatus status)
{
  g_b_verboseStatus = status;
  SetTraceLogCallback(logHandler);
}

void logBasicImpl(const char* caller, LogPreset p)
{
  char msg[256];
  int logtype;
  switch (p) {
    case I_SUCCESS:
      TextCopy(msg, "The function finished without errors.");
      logtype = LINFO;
      break;
    case E_INVPARAM:
      TextCopy(msg, "Invalid parameter(s).");
      logtype = LERR;
      break;
    case E_INVPTR:
      TextCopy(msg, "Invalid pointer(s).");
      logtype = LERR;
      break;
    case E_NOMEM:
      TextCopy(msg, "Memory allocation failure.");
      logtype = LERR;
      break;
    case E_UNSPEC:
      TextCopy(msg, "Unspecified error.");
      logtype = LERR;
      break;
    case E_INTERNAL:
      TextCopy(msg, "Internal error.");
      logtype = LERR;
      break;
    default:
      TextCopy(msg, "Invalid parameter(s).");
      logtype = LERR;
      break;
  }
  TraceLog(logtype, "[%s] %s", caller, msg);
}

Vector2 ivec2vec (IntVector2 iv)
{
  return (Vector2) {(float)iv.x, (float)iv.y};
}

IntVector2 vec2ivec (Vector2 v)
{
  return (IntVector2) {(int)truncf(v.x), (int)truncf(v.y)};
}