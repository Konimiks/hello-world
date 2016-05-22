#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdlib.h>

#define DEFINE_PTR(TYPE)              \
    void * TYPE ## _ptr(TYPE value) {       \
        TYPE * ptr = malloc(sizeof(TYPE));  \
        *ptr = value;                       \
        return ptr;                         \
    }

#define DEFINE_PTR_ALLOCATOR(TYPE, ALLOCATOR)\
    void * TYPE ## _ptr(TYPE value) {       \
        TYPE * ptr = malloc(sizeof(TYPE));  \
        *ptr = value;                       \
        ALLOCATOR(ptr);                     \
        return ptr;                         \
    }
// Name of type of list struct.
typedef struct list_s list_t;
// CALLBACK (??)
typedef void (* list_dealloc_fn)(void *);

// Creates a new list.
// @Returns: created list.
list_t * list_new(void);
// Creates a copy of $original list.
// @Returns: a copy of the list.
list_t * list_new_copy(list_t * original);
// Creates a new list with setting a callback (??).
// @Returns: created list (with included callback) (??).
list_t * list_new_dealloc(list_dealloc_fn deallocator);
// Destroys the list and frees the allocated memory.
void list_free(list_t * self);

// Adds a new element to the end of the list.
void list_push_back(list_t * self, void * data);
// Insertes a new element to the $position of the list.
void list_insert(list_t * self, int position, void * value);
// Deletes the last element of the list.
// @Returns: deleted element OR NULL if the list is empty.
void * list_pop_back(list_t * self);
// Deletes the element from $index of the list.
// @Returns: deleted element OR NULL if the index is improper.
void * list_remove(list_t * self, int index);
// Cleares the list (deletes all the elements).
// _dealloc for each element (??).
void list_clear(list_t * self);
// Gets the element by $index.
// @Returns: element OR NULL if the index is improper.
void * list_get(list_t * self, int index);
// Gets the index of the element with $data.
// @Returns: the index of the element OR -1 if the element was not found.
int list_findIndex(list_t * self, void * data);
// Gets the amount of the elements.
// @Returns: size.
int list_getSize(list_t * self);

#endif // LIST_H_INCLUDED
