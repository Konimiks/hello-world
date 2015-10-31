#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int N;
    scanf("%i",&N);
    int k=2*N;
    srand(time(NULL));
    int Array[k];
    for(int i=0;i<k;i++){
    Array[i]=rand() %1999 - 999;
    printf("%d, " , Array[i]);
    }
    printf("\n");
    int Arr[k];
    int l,y,m,v;
    for(l=0,m=0;l<k;l+2,m++)
    {
        Arr[l]=Array[m];
    }
    for(y=1,v=k;y<k; y+2, v--)
    {
        Arr[y]=Array[v];
    }
    for(int r=0; r<k; r++) printf("%d, ", Arr[r]);
}
//не закончено и не совсем работает
