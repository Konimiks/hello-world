#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include <windows.h>
#include "stack.h"

HANDLE newThread(LPTHREAD_START_ROUTINE routine, stack_t ctx);

#endif // THREAD_H_INCLUDED
