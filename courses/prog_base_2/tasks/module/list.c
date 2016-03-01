#include <stdlib.h>
#include "list.h"

struct list_s {
    int array[100];
    int count;
};

list_t * list_new(void) {
    list_t * s = malloc(sizeof(struct list_s));
    s->count = 0;
    return s;
}

void list_free(list_t * self) {
    free(self);
}

int list_getCount(list_t * self) {
    return self->count;
}

void list_add(list_t * self, int val, int position) {
    if(position < 0 || position > self->count + 1)
        return  EXIT_FAILURE;
    else {
        for(int i = self->count - 1; i >= position; i--)
            self->array[i + 1] = self->array[i];
        self->array[position] = val;
        self->count++;
    }
}

void list_delete(list_t * self, int position){
    if(position < 0 || position > self->count - 1)
        return  EXIT_FAILURE;
    else {
        for(int i = position; i < self->count - 1; i++)
            self->array[i] = self->array[i + 1];
        self->count--;
    }
}

int list_get_count_positive(list_t * self){
    int number = 0;
    for(int i = 0; i < self->count; i++){
        if(self->array[i] > 0)
            number++;
    }
    return number;
}

int list_get_count_negative(list_t * self){
    int number = 0;
    for(int i = 0; i < self->count; i++){
        if(self->array[i] < 0)
            number++;
    }
    return number;
}

int list_get_count_zero(list_t * self){
    int number = 0;
    for(int i = 0; i < self->count; i++){
        if(self->array[i] == 0)
            number++;
    }
    return number;
}

void list_print(list_t * self){
    for(int i = 0; i < self->count; i++)
        printf("%i,", self->array[i]);
    printf("\n");
}
