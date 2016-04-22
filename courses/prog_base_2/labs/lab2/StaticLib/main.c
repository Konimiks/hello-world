#include "list.h"

struct list_s
{
    char elem[ELEMENTS_COUNT];
    int count;
};

list_t *list_new(void)
{
    list_t * l = malloc(sizeof(struct list_s));
    l->count = 0;
    return l;
}

void list_free(list_t * self) {
    free(self);
}

int list_getCount(list_t * self) {
    return self->count;
}

void list_add(list_t * self, int val) {
    if(self->count == ELEMENTS_COUNT){
        printf("Error while adding new element");
        return;
    }
        self->elem[self->count] = val;
        self->count++;
}

int list_delete(list_t * self, int position){
    if(position < 0 || position > self->count - 1)
        return 0;
    else {
        char tmp = self->elem[position];
        for(int i = position; i < self->count - 1; i++)
            self->elem[i] = self->elem[i + 1];
        self->count--;
        int val = tmp & 0xff;
        if(val > 128)
            val -= 256;
        return (val);
    }
}

int list_getElem(list_t * self, int position)
{
    if(position < 0 || position > self->count - 1)
        return 0;
    return (self->elem[position] & 0xff);
}

void list_print(list_t * self){
    for(int i = 0; i < self->count; i++)
        printf("%i,", (self->elem[i]));
    printf("\n");
}

