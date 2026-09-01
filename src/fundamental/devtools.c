#include "devtools.h"

// command-line options
static const struct cag_option clopts[] = {
    {
        .identifier = 'v',
        .access_letters = "vV",
        .access_name = "verbosity",
        .value_name = "VERBOSITY_LEVEL",
        .description = "Set how verbose the command-line output is."
    },
    {
        .identifier = 'l',
        .access_letters = "lLaA",
        .access_name = "log",
        .value_name = "FUNC_NAME",
        .description = "Prints only the output of the given function. Can be used with --verbosity."
    },
    {
        .identifier = 'h',
        .access_letters = "hH",
        .access_name = "help",
        .description = "Shows help message for command-line parameters."
    }
};

void argTools (int argc, char** argv) {
    cag_option_context context;
    cag_option_init(&context, clopts, CAG_ARRAY_SIZE(clopts), argc, argv);
    while (cag_option_fetch(&context)) {
        switch (cag_option_get_identifier(&context)) {
            case 'v':
                g_b_verboseStatus = (VerboseStatus)TextToInteger(cag_option_get_value(&context));
                break;
            case 'h':
                puts("bin [OPTIONS]...");
                cag_option_print(clopts, CAG_ARRAY_SIZE(clopts), stdout);
                exit(0);
                break;
            case 'l':
                const char* val = cag_option_get_value(&context);
                if (val) {
                    extern char g_filterFuncBuffer[];
                    TextCopy(g_filterFuncBuffer, val);
                    filterFunc = g_filterFuncBuffer;
                }
                break;
            case '?':
                cag_option_print_error(&context, stdout);
                break;
        }
    }
}