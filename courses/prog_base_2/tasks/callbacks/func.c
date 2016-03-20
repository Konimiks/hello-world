#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "func.h"



void detect()
{
    int size = rand() % 40 + 10;
    char str_rand [size];
    for(int i = 0; i < size; i++)
    {
        str_rand[i] = rand() % 93 + 33;
    }
    str_rand[size] = '\0';
    printf("Generated string is: %s", str_rand);
    printf("\n");

    char cin;
    while(1)
    {
        scanf("%c", &cin);
        if(cin == 'Q')
            break;

        if(cin == 'A')
        {
            int my_random_number = rand() % 3 + 0;
            if(my_random_number == 0)
                processCB(str_rand, size, make_zero);
            if(my_random_number == 1)
                processCB(str_rand, size, make_one);
            if(my_random_number == 2)
                processCB(str_rand, size, make_two);
        }

        if(cin == 'Z')
        {
            int color = rand() % 1999 - 999;
            if(color > 333)
                printCB(str_rand, size, green);
            else if(color < -333)
                printCB(str_rand, size, red);
            else
                printCB(str_rand, size, blue);
        }
    }


}

void printCB(char * arr, int len, void(*cb)())
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(cb == NULL)
        printf("ERROR");
    else
    {
        cb();
        for(int i = 0; i < len; i++)
            printf("%c", arr[i]);
        printf("\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    }
}

void red()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}

void green()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
}

void blue()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
}

void processCB(char *arr, int len, void(*cb)())
{
    if(cb == NULL)
        printf("ERROR");
    else
    {
        cb(arr, len);
    }
}

void make_zero(char *arr, int len)
{
    for(int i = 0; i < len; i++)
        arr[i] = '0';
}

void make_one(char *arr, int len)
{
        for(int i = 0; i < len; i++)
        arr[i] = '1';
}

void make_two(char *arr, int len)
{
        for(int i = 0; i < len; i++)
        arr[i] = '2';
}
