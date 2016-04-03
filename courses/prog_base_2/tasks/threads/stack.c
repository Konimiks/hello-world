#include "stack.h"


struct stack_s {
    int* arr;
    int size;
    status stat;
};

stack_t stack_new (void) {
    stack_t p = malloc(sizeof(struct stack_s));
    p->arr = malloc(sizeof(int)*5);
    p->stat = STACK_OK;
    p->size = 0;
    return p;
}

void stack_free (stack_t s){
    free(s->arr);
    free(s);
}

void stack_push (stack_t p, int element) {
    if (p->size == 5 || p->stat == STACK_OVERFLOW){
        p->size = 4;
        p->stat = STACK_OVERFLOW;
        return;
    }
    p->arr[p->size] = element;
    p->size++;
}

int stack_pop (stack_t p) {
    if (p->size == 0){
        return -1;
    }
    p->size--;
    int val = p->arr[p->size];
    p->stat = STACK_OK;
    return val;
}

