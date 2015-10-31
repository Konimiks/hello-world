#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int isPowerOfTwo(unsigned int);

int main()
{
    int N;
    srand(time(NULL));
    scanf("%d",&N);
    int Array[N];
    int i,j;
    for(i=0;i<N;i++)
    { Array[i]=rand() % 1999 - 999 ;
       if(isPowerOfTwo(Array[i])) printf("%d, ", Array[i]);
    }// заполняем массив числами от нуля до 99
    printf("\n");
    int sum=0;
    for(int k=0; k<N; k++)
        sum+=Array[k];
    printf("Sum=%d", sum);

}

int isPowerOfTwo (unsigned int x) //проверка степени двойки возвращает True(1) или False(0)
{
    if(x<0) return 0;
return ((x != 0) && ((x & (~x + 1)) == x));
}

