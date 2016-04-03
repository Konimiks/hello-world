#include "modules.h"
#include "stack.h"
#include "threads.h"
#include "time.h"


DWORD Producer(LPVOID args) {
    stack_t stack = (stack_t)args;
    srand(time(NULL));
    while (TRUE) {
        WaitForSingleObject(hMutex, INFINITE);
        stack_push(stack, rand() % 100);
        ReleaseMutex(hMutex);
        Sleep(50);
    }
}

DWORD Consumer(LPVOID args) {
    stack_t st = (stack_t)args;
    while (TRUE){
    WaitForSingleObject(hMutex, INFINITE);
    printf("Deleted element %i\n", stack_pop(st));
    ReleaseMutex(hMutex);
    Sleep(100);
    }
}

HANDLE * Consumer_new(stack_t stack){
    HANDLE * consumer = malloc(sizeof(HANDLE));
    consumer = newThread(Consumer, stack);
    return consumer;
}

void Consumer_free (HANDLE * consumer){
    CloseHandle(consumer);
}

HANDLE * Producer_new(stack_t stack){
    HANDLE * producer = malloc(sizeof(HANDLE));
    producer = newThread(Producer, stack);
    return producer;
}

void Producer_free(HANDLE * producer){
    CloseHandle(producer);
}
