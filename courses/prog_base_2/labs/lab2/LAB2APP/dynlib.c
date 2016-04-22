#include "dynlib.h"

dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->chk = NULL;
    dyn->react = NULL;
    if (NULL != dyn->hLib) {
        dyn->chk = (chk_f)GetProcAddress(dyn->hLib, "Check");
        dyn->react = (react_f)GetProcAddress(dyn->hLib, "Reaction");
        return dyn;
    } else {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn) {
    FreeLibrary(dyn->hLib);
    free(dyn);
}
