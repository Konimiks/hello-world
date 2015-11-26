#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

void arrrand(double arr[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        arr[i] = (float) rand() / RAND_MAX * 1999 - 999 ;
    }
}

void reset(double arr[], int size)
{
    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int g;
    for(g = 0; g < size; g++)
        arr[g] = 0;
    pos.X = 0;
    pos.Y = 1;
    int Aqua = BACKGROUND_GREEN | BACKGROUND_BLUE ;
    SetConsoleTextAttribute(hConsole, Aqua);
    SetConsoleCursorPosition(hConsole, pos);
    for(g = 0; g < size; g++)
        printf("%10.3f", arr[g]);
}

void change(double arr[], int size, int position, double number)
{
    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int Aqua = FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE ;
    if(position < 9) pos.Y = 1;
    else if(position < 17) pos.Y = 2;
    else if(position < 25) pos.Y = 3;
    else if(position < 33) pos.Y = 4;
    else if(position < 41) pos.Y = 5;
    else if(position < 49) pos.Y = 6;
    else if(position < 57) pos.Y = 7;
    else if(position < 65) pos.Y = 8;
    else if(position < 73) pos.Y = 9;
    else if(position < 85) pos.Y = 10;
    else if(position < 93) pos.Y = 11;
    else if(position < 101) pos.Y = 12;
    switch((position - 1) % 8 )
    {
        case 0:
            pos.X = 0;
            break;
        case 1:
            pos.X = 10;
            break;
        case 2:
            pos.X = 20;
            break;
        case 3:
            pos.X = 30;
            break;
        case 4:
            pos.X = 40;
            break;
        case 5:
            pos.X = 50;
            break;
        case 6:
            pos.X = 60;
            break;
        case 7:
            pos.X = 70;
            break;
        default:
            break;
    }
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, Aqua);
    printf("%10.3f", number);
}

void random(double arr[], int size, double max, double min)
{
    int i;
    for(i = 0; i < size; i++)
        arr[i] = (float) rand() / RAND_MAX * (max - min) + min ;
}

void backorder(double arr[], int size)
{
    double arr2[size];
    int j;
    for(j = 0; j < size; j++)
        arr2[j] = arr[j];
    int i;
    for(i = 0; i < size; i++)
        arr[i] = arr2[size - i - 1];
}

double sum(double arr[], int size)
{
    int i;
    double result = 0.0;
    for(i = 0; i < size; i++)
    {
            result += arr[i];
    }
    return result;
}

int negnumber(double arr[], int size)
{
    int resNumber = 0;
    int i;
    for(i = 0; i < size; i++)
    {
        if(arr[i] < 0.0)
            resNumber++;
    }
    return resNumber;
}

void rightshift(double arr[], int size, int number)
{

}

void myPower(double arr[], int size, double number)
{
    int i;
    for(i = 0; i < size; i++)
    {
        arr[i] = pow(arr[i], number);
    }
}

int minimal(double arr[], int size)
{
    int i, index = -1;
    double min = 9999999.0;
    for(i = 0; i < size; i++)
    {
        if(arr[i] < min)
        {
            min = arr[i];
            index = i;
        }
    }
    return index;
}

void maxtomin(double arr[], int size)
{
    double minimum = 9999999999.0;
    double maximum = -999999999.0;
    int minIndex = -1;
    int maxIndex = -1;
    for(int i = 0; i < size; i++)
    {
        if(arr[i] <= minimum)
        {
            minimum = arr[i];
            minIndex = i;
        }
        if(arr[i] >= maximum)
        {
            maximum = arr[i];
            maxIndex = i;
        }
    }
    double maxnumber;
    maxnumber = arr[maxIndex];
    arr[maxIndex] = arr[minIndex];
    arr[minIndex] = maxnumber;
}

int minindex(double arr[], int size)
{
    double minimum = 9999999999.0;
    int minIndex = -1;
    for(int i = 0; i < size; i++)
    {
        if(arr[i] <= minimum)
        {
            minimum = arr[i];
            minIndex = i;
        }
    }
    return minIndex;
}

int maxindex(double arr[], int size)
{
    double maximum = -999999999.0;
    int maxIndex = -1;
    for(int i = 0; i < size; i++)
    {
        if(arr[i] >= maximum)
        {
            maximum = arr[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

void simpleshift(double arr[], int size, int number)
{
    for(int j = 0; j < number; j++)
        for(int i = size - 1; i >= 0; i--)
            {
                if (i == 0)
                    arr[i] = 0;
                else
                    arr[i] = arr[i - 1];
            }
}

void circleshift(double arr[], int size, int number)
{
    double copy;
    for(int j = 0; j < number; j++)
        for(int i = size - 1; i >= 0; i--)
            {
                if(i == size - 1)
                    copy = arr[size - 1];
                if(i == 0)
                    arr[i] = copy;
                else
                    arr[i] = arr[i - 1];
            }
}
