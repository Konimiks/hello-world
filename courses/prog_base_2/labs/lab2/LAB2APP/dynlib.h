#ifndef MY_DYN_LIB
#define MY_DYN_LIB

#include "list.h"
#include <windows.h>

typedef int (*chk_f)(list_t * l);
typedef void (*react_f)(int val);

typedef struct dynamic_s {
    HANDLE hLib;
    chk_f chk;
    react_f react;
} dynamic_t;

#endif // MY_DYN_LIB
