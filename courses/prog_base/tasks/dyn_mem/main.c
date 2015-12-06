#include <stdlib.h>
#include <stdio.h>


int main(void) {

    char * string = NULL;
    string = malloc(sizeof (char) * 50);
    if(NULL == string)
    {
        printf("NO MEMORY");
        return 1;
    }
    printf("Enter your string (not more than 49 symbols and English)::");
    gets(string);
    printf("%s\n", string);

    char * number = NULL;
    number = malloc(sizeof(char) * 1);
    if(NULL == number)
    {
        return EXIT_FAILURE;
    }
    number = '0';
    int * i = NULL;
    i = malloc(sizeof(int) * 1);
    if(NULL == i)
    {
        return EXIT_FAILURE;
    }
    for((*i) = 0; (*i) <= 49; (*i)++)
    {
        if(string[*i] <= 'Z' && string[*i] >= 'A')
            number = string[*i];
        if(string[*i] == '\0')
        {
            free(i);
            break;
        }
    }

    printf("%c", number);
    free(string);
    free(number);
    return 0;
}

