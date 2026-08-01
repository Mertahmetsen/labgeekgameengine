#define RAYGUI_IMPLEMENTATION
#include "../src/fundamental/basic.h"
#include "../src/io/dbox-parse.h"

#define teq(str) TextIsEqual(argv[carg], str)

#define DBOXARGC 22
#define DBXVERSION (uint_fast16_t)1
#define TEXTUREARGC 7
#define TXTVERSION (uint_fast16_t)1
#define TFULLARGC
#define TFULLVERSION (uint_fast16_t)1

char *filename = "./out.resource";

void dboxgen (const char** argv) {
    DBoxFile dbox;
    memset(&dbox, 0, sizeof(dbox));
    int allset = 3;
    dbox.version = DBXVERSION;
    for (int carg=3; carg<DBOXARGC; ++carg) {
        if (teq("--text")) {
            TextCopy(dbox.text, argv[++carg]);
        }
        else if (teq("--fontFile")) {
            TextCopy(dbox.fontdir, argv[++carg]);
        }
        else if (teq("--fontSize")) {
            dbox.fontSize = TextToFloat(argv[++carg]);
        }
        else if (teq("--textSpacing")) {
            dbox.spacing = TextToFloat(argv[++carg]);
        }
        else if (teq("--position")) {
            dbox.position = parseWindowPos(argv[++carg]);
        }
        else if (teq("--backgroundColor")) {
            dbox.color = parseColor(argv[++carg]);
        }
        else if (teq("--outlineColor")) {
            dbox.outline = parseColor(argv[++carg]);
        }
        else if (teq("--textColor")) {
            dbox.textColor = parseColor(argv[++carg]);
        }
        else if (teq("--lifetime")) {
            dbox.lifetime = TextToFloat(argv[++carg]);
        }
        else if (teq("--enabledByDefault")) {
            dbox.enabled = (bool)TextToInteger(argv[++carg]);
        } else {
            TraceLog(LOG_FATAL, TextFormat("Unknown parameter: %s", argv[carg]));
            return;
        }
        allset+=2;
    }
    if (allset < DBOXARGC) {
        TraceLog(LOG_FATAL, "Not enough arguments");
        return;
    }
    const char* attribs = TextFormat(
            "(%s,%f,%f,%d,(%hhu,%hhu,%hhu,%hhu),(%hhu,%hhu,%hhu,%hhu),(%hhu,%hhu,%hhu,%hhu),%f,%d)", 
             dbox.fontdir, dbox.fontSize, dbox.spacing, dbox.position, 
            dbox.color.r, dbox.color.g, dbox.color.b, dbox.color.a,
            dbox.outline.r, dbox.outline.g, dbox.outline.b, dbox.outline.a,
            dbox.textColor.r, dbox.textColor.g, dbox.textColor.b, dbox.textColor.a,
            dbox.lifetime, (int)dbox.enabled
    );
    if (SaveFileData(filename, &dbox, sizeof(DBoxFile))) {
        TraceLog(LOG_INFO, TextFormat("Generated a new dialogue box %s with desired attributes %s", filename, attribs));
    } else {
        TraceLog(LOG_FATAL, TextFormat("Could not generate new dialogue box %s. Check attributes: %s", filename, attribs));
    }
    TraceLog(LOG_INFO, TextFormat("Resource file size is %d bytes (%f KBs)", sizeof(DBoxFile), (float)sizeof(DBoxFile)/1024.0f));
}

void igen (const char** argv) {
    TraceLog(LOG_FATAL, "Not supported yet");
}

void wgen (const char** argv) {
    TraceLog(LOG_FATAL, "Not supported yet");
}

/*void tgen (const char** argv) {
    TexturePointer tfile;
    int allset = 3;
    memset(&tfile, 0, sizeof(tfile));
    tfile.version = TXTVERSION;
    for (int carg=3; carg<TEXTUREARGC; ++carg) {
        if (teq("--path")) {
            TextCopy(tfile.rayTextureDir, argv[++carg]);
        } else if (teq("--renderSlot")) {
            tfile.renderSlot = TextToInteger(argv[++carg]);
        } else {
            TraceLog(LOG_FATAL, TextFormat("Unknown Parameter: %s", argv[carg]));
        }
        allset+=2;
    }
    if (allset < TEXTUREARGC) {
        TraceLog(LOG_FATAL, "Not enough arguments");
        return;
    }
    const char* attribs = TextFormat("(%s,%d)", tfile.rayTextureDir, tfile.renderSlot);
    if (SaveFileData(filename, &tfile, sizeof(tfile))) {
        TraceLog(LOG_INFO, TextFormat("Generated a new texture pointer %s with desired attributes: %s", filename, attribs));
    } else {
        TraceLog(LOG_FATAL, TextFormat("Could not generate new texture pointer %s. Check attributes: %s", filename, attribs));
    }
    TraceLog(LOG_INFO, TextFormat("Resource file size is %d bytes (%f KBs)", sizeof(tfile), (float)sizeof(tfile)/1024.0f));
}*/

int main(int argc, const char** argv) {
    if (argc < 3) {
        TraceLog(LOG_FATAL, "Insufficient number of arguments");
        return 1;
    }
    filename = argv[1];
    if (TextIsEqual(argv[2], "--dialogueBox")) {
        dboxgen(argv);
    } else if (TextIsEqual(argv[2], "--item")) {
        igen(argv);
    } else if (TextIsEqual(argv[2], "--world")) {
        wgen(argv);
    } else if (TextIsEqual(argv[2], "--texturePointer")) {
        tgen(argv);
    } 
    else {
        TraceLog(LOG_FATAL, TextFormat("Unknown resource type: %s", argv[1]));
        return 1;
    }
    TraceLog(LOG_INFO, "Finished execution");
    return 0;
}