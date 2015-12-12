#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void delempty (int size, char copy[size], char string[size]);
void digchar (int size, char copy[size], char string[size]);
void znak(int size, char copy[size], char string[size], char dopcopy[size]);

int main(int argc, char ** args){
    int size = 100;
    printf("Your string is::\n");

    FILE* fr = fopen(args[1], "r");
    if(NULL == fr) {
        printf("CANNOT READ");
        return 1;
    }
    FILE* fw = fopen(args[2], "w");
    if(NULL == fw) {
        printf("CANNOT WRITE");
        return 1;
    }
    char string[100];
    fgets(string, 100, fr);
    puts(string);

    puts("String that you have after proccessing:::\n");
    char copy[100];
    char copy1[100];
    char copy2[100];
    char copy3[100];
    delempty(size, copy, string);
    digchar(size, copy1, copy);
    znak(size, copy2, copy1, copy3);

    printf("%s", copy2);

    fprintf(fw, "%s", copy2);

    fclose(fr);
    fclose(fw);

    return 0;
}

void delempty (int size, char copy[size], char string[size])
{
    for(int i = 0, j = 0; i < size; i++)
        {
            if(string[i] != ' ' && string[i] != '\n'){
                copy[j] = string[i];
                j++;
            }
        }
}

void digchar (int size, char copy[size], char string[size])
{
    int j = 0;
    char * p = &string[0];
    for(int i = 0; i < size; i++)
    {
        if(isdigit(p[i])){
            copy[j] = string[i];
            j++;
        }

    }
    for(int i = 0; i < size; i++)
    {
        if(!isdigit(p[i])){
            copy[j] = string[i];
            j++;
        }
    }
}

void znak(int size, char copy[size], char string[size], char dopcopy[size])
{
    int j = 0;
    int k = 0;
    for(int i = 0; i < size; i++)
    {
        if(string[i] >= 48 && string[i] <= 57){
            copy[j] = string[i];
            j++;
        }
        else if(string[i] >= 65 && string[i] <= 90){
            copy[j] = string[i];
            j++;
        }
        else if(string[i] >= 97 && string[i] <= 122){
            copy[j] = string[i];
            j++;
        }
        else {
            if(string[i] == '\0'){
                dopcopy[k] = string[i];
                k++;
                break;

            }
            dopcopy[k] = string[i];
            k++;
        }
    }
    for(int i = 0; i < k; i ++){
        copy[j] = dopcopy[i];
        j++;
    }

}
