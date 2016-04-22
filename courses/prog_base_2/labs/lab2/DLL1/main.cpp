#include "main.h"
#include <stdio.h>

int Check (list_t * l)
{
    int sum = 0;
    while(list_getCount(l))
        sum += list_delete(l, list_getCount(l) - 1);
    if(sum >= 0)
        return 1;
    else return 0;
}

void Reaction (int val)
{
    if(val == 1)
        printf("POSITIVE");
    if(val == 0)
        printf("NEGATIVE");
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
