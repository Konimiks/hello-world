#pragma once

/*-------------------------------->>>>> DLNode module <<<<<--------------------------------*/
typedef struct node_s node_t;

// Constructors and destructors.
node_t *node_new_empty();
node_t *node_new(void *value, node_t *next, node_t *prev);
void node_delete(node_t *nodeObj);

// Getters.
void *node_getValue(const node_t *nodeObj);
node_t *node_getNext(const node_t *nodeObj);
node_t *node_getPrev(const node_t *nodeObj);

// Setters.
void node_setValue(node_t *nodeObj, void *value);
void node_setNext(node_t *nodeObj, node_t *nodeNext);
void node_setPrev(node_t *nodeObj, node_t *nodePrev);

// Other node functions.
node_t * node_copy(const node_t *toCopy);

/*-------------------------------->>>>> List module <<<<<--------------------------------*/
typedef struct list_s list_t;

// Constructors and destructors.
list_t *list_new();
void list_delete(list_t *listObj);

// Getters and setters.
int list_getSize(const list_t *listObj);
void *list_getFirst(const list_t *listObj);
void *list_getLast(const list_t *listObj);
node_t *list_getNodeByIndex(const list_t *listObj, int index);
void *list_getNodeValueByIndex(const list_t *listObj, int index);

// Adding to and deleting from the list.
void list_insertFirst(list_t *listObj, void *newValue);
void list_insertLast(list_t *listObj, void *newValue);
void list_addByIndex(list_t *listObj, void *newValue, int index);
void *list_removeFirst(list_t *listObj);
void *list_removeLast(list_t *listObj);
void *list_removeByIndex(list_t *listObj, int index);

// Changing data in the list.
void list_setNodeByIndex(list_t *listObj, int index, void *value);

// Other helping functions.
int list_isEmpty(const list_t *listObj);
