#include "main.h"

int DLL_EXPORT Check (list_t * l)
{
    int sum = 0;
    while(list_getCount(l))
        sum += list_delete(l, list_getCount(l) - 1);
    return sum;
}

void DLL_EXPORT Reaction (int val)
{
    if(val > 255)
        printf("OVERFLOW");
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
