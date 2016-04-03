#include "threads.h"
HANDLE newThread(LPTHREAD_START_ROUTINE routine, stack_t ctx) {
    return CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE) routine,
        (LPVOID)ctx,
        0,
        NULL);
}
