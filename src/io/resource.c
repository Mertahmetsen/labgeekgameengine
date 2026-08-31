#include "resource.h"

DialogueBox dbxf2dbox(DBoxFile dbxf, float* lifetime, bool* enabled)
{
    DialogueBox dbox;
    switch (dbxf.version) {
        case (unsigned long)1:
            dbox.text = MemAlloc(strlen(dbxf.text) + 1);
            TextCopy(dbox.text, dbxf.text);
            dbox.fontSize = dbxf.fontSize;
            dbox.font = LoadFontEx(dbxf.fontdir, dbxf.fontSize, NULL, 0);
            dbox.spacing = dbxf.spacing;
            dbox.position = dbxf.position;
            dbox.color = dbxf.color;
            dbox.outline = dbxf.outline;
            dbox.textColor = dbxf.textColor;
            *lifetime = dbxf.lifetime;
            *enabled = dbxf.enabled;
            return dbox;
        default:
            TraceLogCaller(LERR, "Unsupported version: %d, returning empty value", dbxf.version);
            return (DialogueBox){0};
    }
}

DialogueBox loadDBFile (const char* path, float* lifetime, bool* enabled)
{
    int bytesRead = 0;
    unsigned char* data = LoadFileData(path, &bytesRead);
    DBoxFile dbxf = {0};
    if (!data) {
        TraceLogCaller(LERR, "Couldn't load file %s, returning empty value", path);
        return (DialogueBox){0};
    }
    if (bytesRead != sizeof(DBoxFile)) {
        TraceLogCaller(LERR, "Invalid DBFile: %s (read %d bytes, expected %zu), returning empty value", path, bytesRead, sizeof(DBoxFile));
        UnloadFileData(data);
        return (DialogueBox){0};
    }
    memcpy(&dbxf, data, sizeof(DBoxFile));
    UnloadFileData(data);
    return dbxf2dbox(dbxf, lifetime, enabled);
}
