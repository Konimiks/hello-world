#include "stdio.h"
#include "math.h"
#include "stdlib.h"


int run(int moves[], int movesLen, int res[], int resLen)
{

    enum operations { Pop, Push, Break, Repeat, Continue, nothing };

    struct Move
    {
        enum operations lt;
        int rt;
    };
    movesLen = 4;
    resLen = movesLen;

    int currentState = 0;
    int currentMove;
    int k = 0;
    int i = 0;
    int CHECK;// cheking break
    int resNumbers = 0;
    struct Move automata[4][4];

automata[0][0].lt = 5;
automata[0][0].rt = 0;
automata[1][1].lt = Pop;
automata[1][1].rt = 2;
automata[2][2].lt = nothing;
automata[2][2].rt = nothing;
automata[3][3].lt = Break;
automata[3][3].rt = Break;
automata[0][1].lt = Pop;
automata[0][1].rt = 1;
automata[1][0].lt = nothing;
automata[1][0].rt = nothing;
automata[0][2].lt = nothing;
automata[0][2].rt = nothing;
automata[2][0].lt = Continue;
automata[2][0].rt = 3;
automata[0][3].lt = 551;
automata[0][3].rt = 1;
automata[3][0].lt = nothing;
automata[3][0].rt = nothing;
automata[1][2].lt = 552;
automata[1][2].rt = 1;
automata[2][1].lt = 555;
automata[2][1].rt = 3;
automata[1][3].lt = Repeat;
automata[1][3].rt = 2;
automata[3][1].lt = nothing;
automata[3][1].rt = nothing;
automata[2][3].lt = nothing;
automata[2][3].rt = nothing;
automata[3][2].lt = 100;
automata[3][2].rt = 0;


    while (1)
{
    switch (moves[k])
{
    case 4:
    currentMove = 0;
    break;
    case 8:
    currentMove = 1;
    break;
    case 13:
    currentMove = 2;
    break;
    case 103:
    currentMove = 3;
    break;
    default:
    CHECK = 1;
    break;
}
    if (CHECK == 1)
{
        break;
}

    switch (automata[currentState][currentMove].lt)
{
    case Break:
    CHECK = 1;
    break;
    case Pop:
    if (i>0)
{
    res[i - 1] = 0;
    i--;
    k++;
    currentState = automata[currentState][currentMove].rt;
    break;
}
    else
{
    CHECK = 1;
    break;
}
    case Repeat:
    currentState = automata[currentState][currentMove].rt;
    break;
    case Continue:
    k++;
    currentState = automata[currentState][currentMove].rt;
    break;
    default:
    res[i] = automata[currentState][currentMove].rt;
    i++;
    k++;
    currentState = automata[currentState][currentMove].rt;
    break;
}

    if (CHECK == 1)
    break;
}
    for (i = 0; i<resLen; i++)
{
    if (res[i] != 0)
    resNumbers++;
}

    return resNumbers;
}

