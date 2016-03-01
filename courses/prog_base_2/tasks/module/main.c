#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(void){
    list_t * list1 = list_new();
    list_print(list1);
    printf("List size is %i\n", list_getCount(list1));
    list_add(list1, 23, 0);
    printf("List size is %i\n", list_getCount(list1));
    list_add(list1, 13, 1);
    list_add(list1, 14, 2);
    list_add(list1, 52, 2);
    printf("List size is %i\n", list_getCount(list1));
    list_print(list1);
    list_delete(list1,1);
    printf("List size is %i\n", list_getCount(list1));
    list_print(list1);
    list_add(list1, -614, 2);
    list_print(list1);
    int pos = list_get_count_positive(list1);
    printf("%i\n", pos);
    int neg = list_get_count_negative(list1);
    printf("%i\n", neg);
    return 0;
}
