#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct file {
    char name[20];
    int size;
    char author[20];
};

int count(int size, struct file arr[size]){
    int val = 0, i;
    for(i = 0; i < size; i++)
    {
        if( arr[i].size >= 50 )
        val ++;
    }
    return val;
}

void change(struct file * pVar, const char * newValue){
    strcpy(pVar->name, newValue);
}

void print(struct file * pVar){
    printf ("Changed array's fields: name:%s  size:%iKB  author:%s", pVar->name, pVar->size, pVar->author);
}


int main(void){
    fflush(stdin);
    srand(time(NULL));
    int size = 4;
    struct file files[size];
    strcpy(files[0].author, "Sanya");
    strcpy(files[1].author, "Dimas");
    strcpy(files[2].author, "Giro");
    strcpy(files[3].author, "Nutela");

    strcpy(files[0].name, "First");
    strcpy(files[1].name, "Second");
    strcpy(files[2].name, "Third");
    strcpy(files[3].name, "Forth");

    for(int i = 0; i < size; i++)
    {
       files[i].size = rand() % 100  ;
    }
    for(int i = 0; i < size; i++){
        printf("File name is: %s\t size is %iKB\t author is: %s\n", files[i].name, files[i].size, files[i].author);
    }
    printf("\n");

    int val;
    val = count(size, files);
    printf("The number of files that size is more than 50KB::: %i\n", val);

    int number;
    printf("Enter the letter number that name you want to change:");
    scanf("%i", &number);
    char newName [20];
    printf("Enter a new name of file(not more than 20 symbols)::");
    fflush(stdin);
    gets(newName);
    change(&files[number], newName);
    print(&files[number]);
    return 0;
}
