#include <stdio.h>
#include <stdlib.h>

char elemfirst(char * str, char * p);
int elem (char * str, char * p, char word);

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
    char symbol = * p;
    int status = elem(str, p, symbol);
    if( *p == '\0' && status == 0)
        return '0';
    if( status == 1)
        return symbol;
    else {
            p++;
            elemfirst(str, p);
    }

}


int elem (char * str, char * p, char word){
    char* c = p;
    p++;
    if( (*p) == '\0'){
        p = c;
        return 0;
    }
    if( *p == word){
        p = c;
        return 1;
}
    else {
            elem(str, p, word);
    }
}
