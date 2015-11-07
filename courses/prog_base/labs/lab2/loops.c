#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define M_PI 3.1415926535897932384626433832795

double calc(int n, int m)
{
    int i,j;
    double x=0.0;
    for(i=1; i<=n ; i++)
    {
        for(j=1; j<=m ; j++)
        {
            x+= i * cos(j* M_PI/2);
        }
    }
    return x;
}
