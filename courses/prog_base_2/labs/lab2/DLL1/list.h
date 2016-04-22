#ifndef LIST_H_LAB2
#define LIST_H_LAB2
#define ELEMENTS_COUNT 25
#include <stdio.h>
#include <stdlib.h>

typedef struct list_s list_t;

list_t *list_new(void);
void list_free(list_t * self);
int list_getCount(list_t * self);
void list_add(list_t * self, int val);
void list_print(list_t * self);
int list_delete(list_t * self, int position);
int list_getElem(list_t * self, int position);

#endif // LIST_H_LAB2
