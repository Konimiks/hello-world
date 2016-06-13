#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/*-------------------------------->>>>> Private structures <<<<<--------------------------------*/

struct node_s
{
    void *value;
    struct node_s *next;
    struct node_s *prev;
};

struct list_s
{
    int size;
    node_t *header;
    node_t *trailer;
};

/*-------------------------------->>>>> Node functions <<<<<--------------------------------*/

node_t *node_new_empty()
{
    node_t *out = (node_t *) malloc ( sizeof( struct node_s ) );
    *out = (node_t)
    {
        .value = NULL, .next = NULL, .prev = NULL
    };
    return (out);
}

node_t *node_new(void *value, node_t *next, node_t *prev)
{
    node_t *out = (node_t *) malloc ( sizeof( struct node_s ) );
    *out = (node_t)
    {
        .value = value, .next = next, .prev = prev
    };
    return (out);
}

void node_delete(node_t *nodeObj)
{
    free(nodeObj);
}

void *node_getValue(const node_t *nodeObj)
{
    return (nodeObj->value);
}

node_t *node_getNext(const node_t *nodeObj)
{
    return (nodeObj->next);
}

node_t *node_getPrev(const node_t *nodeObj)
{
    return (nodeObj->prev);
}

void node_setValue(node_t *nodeObj, void *value)
{
    nodeObj->value = value;
}

void node_setNext(node_t *nodeObj, node_t *nodeNext)
{
    nodeObj->next = nodeNext;
}

void node_setPrev(node_t *nodeObj, node_t *nodePrev)
{
    nodeObj->prev = nodePrev;
}

node_t * node_copy(const node_t *toCopy)
{
    node_t *out = (node_t *) malloc ( sizeof( struct node_s ) );
    *out = *toCopy;
    return (out);
}

/*-------------------------------->>>>> List functions <<<<<--------------------------------*/

list_t *list_new()
{
    list_t *out = (list_t *) malloc ( sizeof( struct list_s ) );
    out->header = node_new_empty();
    out->trailer = node_new_empty();
    out->size = 0;
    out->header->next = out->trailer;
    out->trailer->prev = out->header;
    out->header->value = (void *)("__header__");
    out->trailer->value = (void *)("__trailer__");
    return (out);
}

void list_delete(list_t *listObj)
{
    node_t *curr = listObj->header;
    for (int i = 0; i < list_getSize(listObj); i++)
    {
        curr = curr->next;
        node_delete(curr->prev);
    }
    curr = curr->next;
    node_delete(curr->prev);
    node_delete(curr);
    free(listObj);
}

int list_getSize(const list_t *listObj)
{
    return (listObj->size);
}

void *list_getFirst(const list_t *listObj)
{
    if(list_isEmpty(listObj))
    {
        return (NULL);
    }
    return (listObj->header->next->value);
}

void *list_getLast(const list_t *listObj)
{
    if(list_isEmpty(listObj))
    {
        return (NULL);
    }
    return (listObj->trailer->prev->value);
}

node_t *list_getNodeByIndex(const list_t *listObj, int index)
{
    if(index < 0 || index >= list_getSize(listObj))
    {
        return (NULL);
    }
    node_t *curr = listObj->header;
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    return (curr->next);
}

void *list_getNodeValueByIndex(const list_t *listObj, int index)
{
    if(index < 0 || index >= list_getSize(listObj))
    {
        return (NULL);
    }
    node_t *curr = listObj->header;
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    return (curr->next->value);
}

void list_insertFirst(list_t *listObj, void *newValue)
{
    node_t *second = listObj->header->next;
    node_t *first = node_new(newValue, second, listObj->trailer);
    second->prev = first;
    listObj->header->next = first;
    listObj->size++;
}

void list_insertLast(list_t *listObj, void *newValue)
{
    node_t *preLast = listObj->trailer->prev;
    node_t *last = node_new(newValue, listObj->trailer, preLast);
    preLast->next = last;
    listObj->trailer->prev = last;
    listObj->size++;
}

void list_addByIndex(list_t *listObj, void *newValue, int index)
{
    if (index < 0 || index > listObj->size)
    {
        return;
    }
    if (index == 0)
    {
        list_insertFirst(listObj, newValue);
        return;
    }
    else if(index == listObj->size)
    {
        list_insertLast(listObj, newValue);
        return;
    }
    else
    {
        node_t *curr = listObj->header;
        for (int i = 0; i < index; i++)
        {
            curr = curr->next;
        }
        node_t *nodeToAdd = node_new(newValue, curr->next, curr);
        curr->next->prev = nodeToAdd;
        curr->next = nodeToAdd;
    }
    listObj->size++;
}

void *list_removeFirst(list_t *listObj)
{
    if (list_isEmpty(listObj))
    {
        return (NULL);
    }
    node_t *first = listObj->header->next;
    node_t *second = first->next;
    void *temp = first->value;
    listObj->header->next = second;
    second->prev = listObj->header;
    listObj->size--;
    return (temp);
}

void *list_removeLast(list_t *listObj)
{
    if (list_isEmpty(listObj))
    {
        return (NULL);
    }
    node_t *last = listObj->trailer->prev;
    node_t *preLast = last->prev;
    void *temp = last->value;
    listObj->trailer->prev = preLast;
    preLast->next = listObj->trailer;
    listObj->size--;
    return (temp);
}

void *list_removeByIndex(list_t *listObj, int index)
{
    if (index < 0 || index >= listObj->size)
    {
        return (NULL);
    }
    if (index == 0)
    {
        return (list_removeFirst(listObj));
    }
    else if (index == listObj->size - 1)
    {
        return (list_removeLast(listObj));
    }
    node_t *curr =  listObj->header;
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    void *temp = curr->next->value;
    curr->next = curr->next->next;
    curr->next->next->prev = curr;
    listObj->size--;
    return (temp);

}

void list_setNodeByIndex(list_t *listObj, int index, void *value)
{
    if (index < 0 || index >= list_getSize(listObj))
    {
        return;
    }
    node_t *curr = listObj->header;
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    curr->next->value = value;
}

int list_isEmpty(const list_t *listObj)
{
    return (listObj->size == 0);
}
