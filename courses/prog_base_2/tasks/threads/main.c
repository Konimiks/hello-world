#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "modules.h"
#include "stack.h"



int main(void) {
    srand(time(NULL));
    stack_t stack = stack_new();
    hMutex = CreateMutex(
        NULL,
        FALSE,
        NULL);
    HANDLE * first_thread = Producer_new(stack);
    HANDLE * second_thread = Consumer_new(stack);
    while (!_kbhit());
    Producer_free(first_thread);
    Consumer_free(second_thread);
    CloseHandle(hMutex);
    getch();
    return 0;
}
