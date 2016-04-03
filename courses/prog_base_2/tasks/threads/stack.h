#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct stack_s * stack_t;
typedef enum status{
    STACK_OK,
    STACK_OVERFLOW,
} status;

stack_t stack_new (void);
void stack_free (stack_t s);
void stack_push (stack_t p, int element);
int stack_pop (stack_t p);

#endif // STACK_H_INCLUDED
