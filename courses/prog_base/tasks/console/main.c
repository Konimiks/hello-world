#include <stdlib.h>
#include <stdio.h>
#include <windows.h>


int main(void)
{
    int Yellow = BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
    int Green = BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
    int White = BACKGROUND_RED | BACKGROUND_GREEN |BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED;
    int Standart = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
    int k,t;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    for(pos.Y = 24 ;pos.Y>=0 ; pos.Y-- )
    {
        if(pos.Y%2==0)
        {
            for (pos.X = 0  ;pos.X<80 ; pos.X ++ )
            {
                SetConsoleCursorPosition(hConsole, pos);

                    if((pos.X+pos.Y)%3==0) SetConsoleTextAttribute(hConsole, Green );
                    if((pos.X+pos.Y)%3==1) SetConsoleTextAttribute(hConsole, Yellow);
                    if((pos.X+pos.Y)%3==2) SetConsoleTextAttribute(hConsole, White );
                puts("*");
                Sleep(10);
            }
        }
        if(pos.Y%2==1)
        {
            for (pos.X = 79;pos.X >=0 ; pos.X --)
            {
                SetConsoleCursorPosition(hConsole, pos);

                if((pos.X+pos.Y)%3==0) SetConsoleTextAttribute(hConsole, Green );
                if((pos.X+pos.Y)%3==1) SetConsoleTextAttribute(hConsole, Yellow );
                if((pos.X+pos.Y)%3==2) SetConsoleTextAttribute(hConsole, White );
                puts("*");
                Sleep(10);
            }
        }
    }

    SetConsoleTextAttribute(hConsole, Standart );
    pos.Y=25;
    pos.X=0;
    SetConsoleCursorPosition(hConsole, pos);

}
