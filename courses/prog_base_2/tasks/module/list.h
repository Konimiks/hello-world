#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct list_s list_t;

list_t * list_new(void);
void list_free(list_t * self);

int list_getCount(list_t * self);

void list_add(list_t * self, int val, int position);
void list_delete(list_t * self, int position);

int list_get_count_positive(list_t * self);
int list_get_count_negative(list_t * self);
int list_get_count_zero(list_t * self);

void list_print(list_t * self);

#endif
