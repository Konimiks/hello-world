#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

void arrrand(double arr[], int size);
void reset(double arr[], int size);
void change(double arr[], int size, int position, double number);
void random(double arr[], int size, double max, double min);
void backorder(double arr[], int size);
double sum(double arr[], int size);
int negnumber(double arr[], int size);
void myPower(double arr[], int size, double number);
int minimal(double arr[], int size);
void maxtomin(double arr[], int size);
int minindex(double arr[], int size);
int maxindex(double arr[], int size);
void simpleshift(double arr[], int size, int number);
void circleshift(double arr[], int size, int number);

int main (void)
{
    int elemc;
    int Aqua;
    int red, Red;
    int greenForeground;
    int Standart;
    int greenBackground = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    Red = FOREGROUND_RED | FOREGROUND_INTENSITY;
    red = FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY;
    Standart = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
    Aqua = BACKGROUND_GREEN | BACKGROUND_BLUE ;
    greenForeground = BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    START:;
    for(pos.Y = 0; pos.Y < 40 ;pos.Y++)
        for(pos.X = 0; pos.X < 80; pos.X++)
    {
        SetConsoleCursorPosition(hConsole, pos);
        SetConsoleTextAttribute(hConsole, Standart);
        puts(" ");
    }
    for(pos.Y = 7; pos.Y <= 19; pos.Y+=12 )
    {
        for(pos.X = 20; pos.X <= 59; pos.X++ )
        {
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, Aqua);
            puts("=");
        }
    }
    for(pos.Y = 8; pos.Y < 19; pos.Y++)
    {
        for(pos.X = 20; pos.X <= 58; pos.X++)
        {
            if(pos.X == 20 || pos.X == 58)
            {
                SetConsoleCursorPosition(hConsole, pos);
                puts("||");
            }
        }
    }
    for(pos.Y = 8; pos.Y < 19; pos.Y++)
    {
        for(pos.X = 22; pos.X < 58; pos.X++)
        {
            SetConsoleCursorPosition(hConsole, pos);
            puts(" ");
        }
    }

    SetConsoleTextAttribute(hConsole, greenForeground);
    for(pos.Y = 10; pos.Y <= 12; pos.Y++)
    {
        pos.X = 26;
        if(pos.Y == 10)
        {
            SetConsoleCursorPosition(hConsole, pos);
            printf(" Vvedite razmer odnommernogo");
        }
        if(pos.Y == 11)
        {
            SetConsoleCursorPosition(hConsole, pos);
            printf("  massiva drobovix chisel::");
        }
        if(pos.Y == 12)
        {
            SetConsoleCursorPosition(hConsole, pos);
            printf("\t   [1....100]");
        }
    }
    pos.Y = 14;
    pos.X = 39;
    SetConsoleCursorPosition(hConsole, pos);
    scanf("%i", &elemc);
    if(elemc < 1 || elemc > 100){
        SetConsoleTextAttribute(hConsole, red);
        pos.X = 28;
        pos.Y = 16;
        SetConsoleCursorPosition(hConsole, pos);
        printf("Invalid input, try again");
        Sleep(4000);
        goto START;
    }
    /*for(;elemc < 1 || elemc > 100;)
    {
        SetConsoleTextAttribute(hConsole, red);
        pos.X = 28;
        pos.Y = 16;
        SetConsoleCursorPosition(hConsole, pos);
        printf("Invalid input, try again");
        for(pos.Y = 14, pos.X = 38; pos.X <58; pos.X++)
        {
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, Aqua);
            puts(" ");
        }
        pos.Y = 14;
        pos.X = 39;
        SetConsoleCursorPosition(hConsole, pos);
        SetConsoleTextAttribute(hConsole, greenForeground);
        scanf("%i", &elemc);
    }*/
    for(pos.Y = 0; pos.Y < 30; pos.Y++)
        for(pos.X = 0; pos.X < 80; pos.X++)
    {
    SetConsoleTextAttribute(hConsole, Standart);
    SetConsoleCursorPosition(hConsole, pos);
    puts(" ");
    }
    for(pos.Y = 0; pos.Y < 15; pos.Y++)
        for(pos.X = 0; pos.X < 80; pos.X++)
    {
        if(pos.Y == 0 || pos.Y == 14)
        {
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, Aqua);
            puts("=");
        }else {
            SetConsoleCursorPosition(hConsole, pos);
            puts(" ");
        }
    }
    srand(time(NULL));
    double arr[elemc];
    pos.X = 0;
    pos.Y = 1;
    SetConsoleCursorPosition(hConsole, pos);
    arrrand(arr, elemc);
    int j;
    for(j = 0; j < elemc; j++)
    {
        printf("%10.3f", arr[j]);
    }
    METKA:;
    SetConsoleTextAttribute(hConsole, Standart);
    for(pos.Y = 16; pos.Y < 35; pos.Y++)
        for(pos.X = 0; pos.X < 80; pos.X++)
        {
            SetConsoleCursorPosition(hConsole, pos);
            puts(" ");
        }
    pos.X = 0;
    pos.Y = 16;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, greenBackground);
    printf("Enter your comand:\n>>");
    SetConsoleTextAttribute(hConsole, Standart);
    char comand[100] = {0};
    scanf("%s", &comand);
    if(comand[12] != 0)
    {
        SetConsoleTextAttribute(hConsole, Red);
        printf("INVALID COMMAND, ENTER !!help!! TO GET THE LIST OF COMMANDS !!!");
        Sleep(3000);
        goto METKA;
    }
    if (comand[0] == 'h')
        if(comand[1] == 'e')
            if(comand[2] == 'l')
                if(comand[3] == 'p')
                    {
                        printf("\t\tcommand list:::\n");
                        SetConsoleTextAttribute(hConsole, Red);
                        printf("\t\treset          ");
                        SetConsoleTextAttribute(hConsole, Standart);
                        printf("obnulyaet vse elementi massiva\n");
                        SetConsoleTextAttribute(hConsole, Red);
                        printf("\t\tchange         ");
                        SetConsoleTextAttribute(hConsole, Standart);
                        printf("izmenit element massiva na vvedennoe znachenie\n");
                        SetConsoleTextAttribute(hConsole, Red);
                        printf("\t\trandom         ");
                        SetConsoleTextAttribute(hConsole, Standart);
                        printf("Zapolnaet maasiv chislami v zadanom diapozone\n");
                        SetConsoleTextAttribute(hConsole, Red);
                        printf("\t\tbackorder      ");
                        SetConsoleTextAttribute(hConsole, Standart);
                        printf("Vivodit masiv v obratnom poryadke\n");
                        SetConsoleTextAttribute(hConsole, Red);
                        printf("\t\tsum            ");
                        SetConsoleTextAttribute(hConsole, Standart);
                        printf("Vivodit sumu elementov masiva\n");
                        SetConsoleTextAttribute(hConsole, Red);
                        printf("\t\tnegnumber      ");
                        SetConsoleTextAttribute(hConsole, Standart);
                        printf("Vivodit kolvo otrizatelnix elementov\n");
                        SetConsoleTextAttribute(hConsole, Red);
                        printf("\t\texit           ");
                        SetConsoleTextAttribute(hConsole, Standart);
                        printf("finish the programm\n");
                        SetConsoleTextAttribute(hConsole, Red);
                        printf("\t\trestart        ");
                        SetConsoleTextAttribute(hConsole, Standart);
                        printf("perezapusk programmi\n");
                        SetConsoleTextAttribute(hConsole, Red);
                        printf("\t\tpower          ");
                        SetConsoleTextAttribute(hConsole, Standart);
                        printf("podnosit vse elementi massiva v zadanuj stepen\n");
                        SetConsoleTextAttribute(hConsole, Red);
                        printf("\t\tminimal        ");
                        SetConsoleTextAttribute(hConsole, Standart);
                        printf("Vivodit minimalnii element i ego index\n");
                        SetConsoleTextAttribute(hConsole, Red);
                        printf("\t\tmaxminchange   ");
                        SetConsoleTextAttribute(hConsole, Standart);
                        printf("Menayet max i min element mestami\n");
                        SetConsoleTextAttribute(hConsole, Red);
                        printf("\t\tsimpleshift    ");
                        SetConsoleTextAttribute(hConsole, Standart);
                        printf("Sdvigaet masiv vpravo na vedenoe kolvo elementov\n");
                        SetConsoleTextAttribute(hConsole, Red);
                        printf("\t\tcircleshift    ");
                        SetConsoleTextAttribute(hConsole, Standart);
                        printf("ziklichno sdvigaet masive vpravo \n");

                        Sleep(10000);
                        goto METKA;
                    }
    if (comand[0] == 'r')
        if(comand[1] == 'e')
            if(comand[2] == 's')
                if(comand[3] == 'e')
                    if(comand[4] == 't')
                    {
                        reset(arr, elemc);
                        goto METKA;
                    }
    if (comand[0] == 'c')
        if(comand[1] == 'h')
            if(comand[2] == 'a')
                if(comand[3] == 'n')
                    if(comand[4] == 'g')
                        if(comand[5] == 'e')
                        {
                            int position;
                            double number;
                            CHANGE:;
                            for(pos.Y = 18; pos.Y < 20; pos.Y++)
                                for(pos.X = 0; pos.X < 80; pos.X++)
                                {
                                    SetConsoleCursorPosition(hConsole, pos);
                                    SetConsoleTextAttribute(hConsole, Standart);
                                    puts(" ");
                                }
                            pos.Y = 18;
                            pos.X = 0;
                            SetConsoleCursorPosition(hConsole, pos);
                            SetConsoleTextAttribute(hConsole, Standart);
                            printf("Enter the number of element that you whant to change::  ");
                            scanf("%i", &position);
                            if (position < 0 || position > elemc)
                            {
                                SetConsoleTextAttribute(hConsole, Red);
                                printf("ERROR;  Invalid input,plz enter [1...%d]", elemc);
                                Sleep(4000);
                                goto CHANGE;
                            }
                            CHANGE2:;
                            for(pos.Y = 19; pos.Y < 21; pos.Y++)
                                for(pos.X = 0; pos.X < 80; pos.X++)
                                {
                                    SetConsoleCursorPosition(hConsole, pos);
                                    SetConsoleTextAttribute(hConsole, Standart);
                                    puts(" ");
                                }
                            pos.Y = 19;
                            pos.X = 0;
                            SetConsoleCursorPosition(hConsole, pos);
                            printf("Enter the number on which you want to change::  ");
                            scanf("%lf", &number);
                            if(number > 999999.999 || number < -999999.999)
                            {
                                SetConsoleTextAttribute(hConsole, Red);
                                printf("ERROR;  Invalid input,plz enter [-999999.999...999999.999]");
                                Sleep(4000);
                                goto CHANGE2;
                            }
                            change(arr, elemc, position, number);
                            goto METKA;
                        }
    if (comand[0] == 'r')
        if(comand[1] == 'a')
            if(comand[2] == 'n')
                if(comand[3] == 'd')
                    if(comand[4] == 'o')
                        if(comand[5] == 'm')
                        {
                            double max, min;
                            RANDOM:;
                            for(pos.Y = 18; pos.Y < 20; pos.Y++)
                                for(pos.X = 0; pos.X < 80; pos.X++)
                                {
                                    SetConsoleCursorPosition(hConsole, pos);
                                    SetConsoleTextAttribute(hConsole, Standart);
                                    puts(" ");
                                }
                            pos.Y = 18;
                            pos.X = 0;
                            SetConsoleCursorPosition(hConsole, pos);
                            SetConsoleTextAttribute(hConsole, Standart);
                            printf("Enter the max number of diapozon::  ");
                            scanf("%lf", &max);
                            if(max > 99999.999 || max < -9999.999)
                            {
                                SetConsoleTextAttribute(hConsole, Red);
                                printf("ERROR;  Invalid input,plz enter [-999999.999...999999.999]");
                                Sleep(4000);
                                goto RANDOM;
                            }
                            RANDOM2:;
                            for(pos.Y = 19; pos.Y < 21; pos.Y++)
                                for(pos.X = 0; pos.X < 80; pos.X++)
                                {
                                    SetConsoleCursorPosition(hConsole, pos);
                                    SetConsoleTextAttribute(hConsole, Standart);
                                    puts(" ");
                                }
                            pos.Y = 19;
                            pos.X = 0;
                            SetConsoleCursorPosition(hConsole, pos);
                            SetConsoleTextAttribute(hConsole, Standart);
                            printf("Enter the min number of diapozon::  ");
                            scanf("%lf", &min);
                            if(min > 99999.999 || min < -9999.999 || min > max)
                            {
                                SetConsoleTextAttribute(hConsole, Red);
                                printf("ERROR;  Invalid input,plz enter [-9999.999...%f]", max);
                                Sleep(4000);
                                goto RANDOM2;
                            }
                            random(arr, elemc, max, min);
                            SetConsoleTextAttribute(hConsole, Aqua);
                            pos.X = 0;
                            pos.Y = 1;
                            SetConsoleCursorPosition(hConsole, pos);
                            for(j = 0; j < elemc; j++)
                                    printf("%10.3f", arr[j]);
                            goto METKA;
                        }
    if (comand[0] == 'b')
        if(comand[1] == 'a')
            if(comand[2] == 'c')
                if(comand[3] == 'k')
                    if(comand[4] == 'o')
                        if(comand[5] == 'r')
                            if (comand[6] == 'd')
                                if(comand[7] == 'e')
                                    if(comand[8] == 'r')
                        {
                            backorder(arr, elemc);
                            pos.X = 0;
                            pos.Y = 1;
                            SetConsoleTextAttribute(hConsole, Aqua);
                            SetConsoleCursorPosition(hConsole, pos);
                            for(int l = 0; l < elemc; l++)
                                printf("%10.3f", arr[l]);
                            goto METKA;
                        }
    if (comand[0] == 's')
        if(comand[1] == 'u')
            if(comand[2] == 'm')
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                printf("SUMMA = %f", sum(arr, elemc));
                Sleep(5000);
                for(pos.Y = 18; pos.Y < 20; pos.Y++)
                        for(pos.X = 0; pos.X < 80; pos.X++)
                            {
                                SetConsoleCursorPosition(hConsole, pos);
                                SetConsoleTextAttribute(hConsole, Standart);
                                puts(" ");
                            }
                goto METKA;
            }
    if (comand[0] == 'n')
        if(comand[1] == 'e')
            if(comand[2] == 'g')
                if(comand[3] == 'n')
                    if(comand[4] == 'u')
                        if(comand[5] == 'm')
                            if (comand[6] == 'b')
                                if(comand[7] == 'e')
                                    if(comand[8] == 'r')
                                    {
                                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                                        printf("KOLVO = %i", negnumber(arr, elemc));
                                        Sleep(5000);
                                        for(pos.Y = 18; pos.Y < 20; pos.Y++)
                                            for(pos.X = 0; pos.X < 80; pos.X++)
                                                {
                                                    SetConsoleCursorPosition(hConsole, pos);
                                                    SetConsoleTextAttribute(hConsole, Standart);
                                                    puts(" ");
                                                }
                                        goto METKA;
                                    }
    if (comand[0] == 'e')
        if(comand[1] == 'x')
            if(comand[2] == 'i')
                if(comand[3] == 't')
                    {
                        SetConsoleTextAttribute(hConsole, Standart);
                        printf("\n\n\n\n\n\n\n\n");
                        return 0;
                    }
    if (comand[0] == 's')
        if(comand[1] == 'i')
            if(comand[2] == 'm')
                if(comand[3] == 'p')
                    if(comand[4] == 'l')
                        if(comand[5] == 'e')
                            if (comand[6] == 's')
                                if(comand[7] == 'h')
                                    if(comand[8] == 'i')
                                        if(comand[9] == 'f')
                                            if(comand[10] == 't')
                                    {
                                        int shift;
                                        SHIFT:;
                                        for(pos.Y = 18; pos.Y < 20; pos.Y++)
                                        for(pos.X = 0; pos.X < 80; pos.X++)
                                            {
                                                SetConsoleCursorPosition(hConsole, pos);
                                                SetConsoleTextAttribute(hConsole, Standart);
                                                puts(" ");
                                            }
                                        pos.Y = 18;
                                        pos.X = 0;
                                        SetConsoleCursorPosition(hConsole, pos);
                                        SetConsoleTextAttribute(hConsole, Standart);
                                        printf("Enter number on how many positions you want to shift masive ::  ");
                                        scanf("%i", &shift);
                                        if(shift < 0 || shift > elemc)
                                        {
                                            SetConsoleTextAttribute(hConsole, Red);
                                            printf("ERROR;  Invalid input,plz enter [0...%i]", elemc);
                                            Sleep(4000);
                                            goto SHIFT;
                                        }
                                        simpleshift(arr, elemc, shift);
                                        SetConsoleTextAttribute(hConsole, Aqua);
                                        pos.X = 0;
                                        pos.Y = 1;
                                        SetConsoleCursorPosition(hConsole, pos);
                                        for(j = 0; j < elemc; j++)
                                            {
                                                printf("%10.3f", arr[j]);
                                            }
                                        goto METKA;
                                    }
    if (comand[0] == 'c')
        if(comand[1] == 'i')
            if(comand[2] == 'r')
                if(comand[3] == 'c')
                    if(comand[4] == 'l')
                        if(comand[5] == 'e')
                            if (comand[6] == 's')
                                if(comand[7] == 'h')
                                    if(comand[8] == 'i')
                                        if(comand[9] == 'f')
                                            if(comand[10] == 't')
                                {
                                    int shift2;
                                    SHIFT2:;
                                    for(pos.Y = 18; pos.Y < 20; pos.Y++)
                                    for(pos.X = 0; pos.X < 80; pos.X++)
                                        {
                                            SetConsoleCursorPosition(hConsole, pos);
                                            SetConsoleTextAttribute(hConsole, Standart);
                                            puts(" ");
                                        }
                                    pos.Y = 18;
                                    pos.X = 0;
                                    SetConsoleCursorPosition(hConsole, pos);
                                    SetConsoleTextAttribute(hConsole, Standart);
                                    printf("Enter number on how many positions you want to shift masive ::  ");
                                    scanf("%i", &shift2);
                                    if(shift2 < 0 || shift2 > 9999 )
                                        {
                                            SetConsoleTextAttribute(hConsole, Red);
                                            printf("ERROR;  Invalid input,plz enter [0...9999]");
                                            Sleep(4000);
                                            goto SHIFT2;
                                        }
                                    circleshift(arr, elemc, shift2);
                                    SetConsoleTextAttribute(hConsole, Aqua);
                                    pos.X = 0;
                                    pos.Y = 1;
                                    SetConsoleCursorPosition(hConsole, pos);
                                    for(j = 0; j < elemc; j++)
                                        {
                                            printf("%10.3f", arr[j]);
                                        }
                                    goto METKA;
                                }
    if (comand[0] == 'p')
        if(comand[1] == 'o')
            if(comand[2] == 'w')
                if(comand[3] == 'e')
                    if(comand[4] == 'r')
                    {
                        printf("Enter the power in which you want to up numbers::  ");
                        double numbeR;
                        scanf("%lf", &numbeR);
                        myPower(arr, elemc, numbeR);
                        SetConsoleTextAttribute(hConsole, Aqua);
                        pos.X = 0;
                        pos.Y = 1;
                        SetConsoleCursorPosition(hConsole, pos);
                        for(j = 0; j < elemc; j++)
                                printf("%10.3f", arr[j]);
                        goto METKA;
                    }
    if (comand[0] == 'r')
        if(comand[1] == 'e')
            if(comand[2] == 's')
                if(comand[3] == 't')
                    if(comand[4] == 'a')
                        if(comand[5] == 'r')
                            if (comand[6] == 't')
                            {
                                goto START;
                            }
    if (comand[0] == 'm')
        if(comand[1] == 'i')
            if(comand[2] == 'n')
                if(comand[3] == 'i')
                    if(comand[4] == 'm')
                        if(comand[5] == 'a')
                            if (comand[6] == 'l')
                            {
                                int minIndex = minimal(arr, elemc);
                                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                                printf("Minimal element = %10.3f\nindex of this elenet = %i", arr[minIndex], minIndex);
                                Sleep(5000);
                                for(pos.Y = 18; pos.Y < 21; pos.Y++)
                                for(pos.X = 0; pos.X < 80; pos.X++)
                                    {
                                        SetConsoleCursorPosition(hConsole, pos);
                                        SetConsoleTextAttribute(hConsole, Standart);
                                        puts(" ");
                                    }
                                goto METKA;
                            }
    if (comand[0] == 'm'){
        if(comand[1] == 'a')
            if(comand[2] == 'x')
            if(comand[3] == 'm')
            if(comand[4] == 'i')
            if(comand[5] == 'n')
            if(comand[6] == 'c')
            if(comand[7] == 'h')
            if(comand[8] == 'a')
            if(comand[9] == 'n')
            if(comand[10] == 'g')
            if(comand[11] == 'e')
            {
                maxtomin(arr, elemc);
                SetConsoleTextAttribute(hConsole, Aqua);
                pos.X = 0;
                pos.Y = 1;
                SetConsoleCursorPosition(hConsole, pos);
                for(j = 0; j < elemc; j++)
                {
                    if(j == maxindex(arr, elemc) || j == minindex(arr, elemc) )
                        SetConsoleTextAttribute(hConsole, red);
                    printf("%10.3f", arr[j]);
                    SetConsoleTextAttribute(hConsole, Aqua);
                }
                goto METKA;
            }
    }
    else {
        SetConsoleTextAttribute(hConsole, Red);
        printf("INVALID COMMAND, ENTER !!help!! TO GET THE LIST OF COMMANDS !!!");
        Sleep(3000);
        goto METKA;
    }


    SetConsoleTextAttribute(hConsole, Standart);
    printf("\n\n\n\n\n\n\n\n\n\n");
    return 0;
}

