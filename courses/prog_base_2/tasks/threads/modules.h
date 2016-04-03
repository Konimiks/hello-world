#ifndef MODULES_H_INCLUDED
#define MODULES_H_INCLUDED

#include <windows.h>

HANDLE hMutex;

HANDLE * randomizer_new(int size, int * value);
void randomizer_del(HANDLE * consumers, int size);

HANDLE * zeroWriter_new(int size, int * value);
void zeroWriter_del(HANDLE * consumers, int size);

#endif // MODULES_H_INCLUDED
