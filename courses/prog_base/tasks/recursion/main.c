#include <stdio.h>
#include <stdlib.h>

char elemfirst(char * str, char * p);

int main(void){
    printf("Please enter your string:::");
    char string[20];
    gets(string);
    char * p = string;

    printf("%c", elemfirst(string, p));

    return 0;
}

char elemfirst(char * str, char * p)
{
    if(*(p + 1) == '\0')
        return '0';
    else if(*p == *(p + 1))
        return *p;
    else return elemfirst(str, p + 1);

}
