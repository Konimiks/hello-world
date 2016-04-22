#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dynlib.h"
#include "list.h"

const char* chooseLib (void);

int main()
{
    list_t *list = list_new();
    dynamic_t * dll = dynamic_init(chooseLib ());
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->chk) {
        printf("Can't get check function!\n");
        return 1;
    }
    if (NULL == dll->react) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!\n");
    srand(time(NULL));

    int i = 0;
    for (i = 0; i < 10; i++){
        list_add(list, rand() % 125);
    }
    list_print(list);
    dll->react(dll->chk(list));

    list_free(list);
    dynamic_clean(dll);
    return 0;
}

const char* chooseLib (void) {
    puts ("Enter number of library you want to use");
    puts ("DLL1 >> 1");
    puts ("DLL2 >> 2");
    printf("enter your choise >> ");
    int num;
    scanf("%i", &num);
    if (num == 1)
        return "DLL1.dll";
    if (num == 2)
        return "DLL2.dll";
}
