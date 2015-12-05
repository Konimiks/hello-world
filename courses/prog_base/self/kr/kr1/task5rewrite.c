// VARIANT 14

#include <stdlib.h>
#include <stdio.h>

void fillrand(int size, int arr[size]);
void printneg(int size, int arr[size]);
int maxelem(int size, int arr[size]);

int main(void)
{
    int N;
    srand(time(NULL));
    printf("ENter the number of elements in massive::");
    scanf("%i", &N);
    int arr[N];
    fillrand(N, arr);
    printf("YOUR MASSIVE IS :::\n");
    for(int i =0; i < N; i++)
        printf("%i,  ", arr[i]);

    printf("\nNegative numbers of massive::\n");
    printneg(N, arr);
    printf("\n");
    printf("MAX ELEMENT of massive is::\n");
    int max = maxelem(N, arr);
    printf("%i", max);
    return 0;
}

void fillrand(int size, int arr[size])
{
    for(int i = 0; i < size; i++)
        arr[i] = rand() % 201 - 100;
}

void printneg(int size, int arr[size])
{
    for(int i = 0; i < size; i++)
        if(arr[i] < 0)
            printf("%i,  ", arr[i]);
}

int maxelem(int size, int arr[size])
{
    int max = -1000000;
    for(int i = 0; i < size; i++)
        if(arr[i] > max)
            max = arr[i];
    return max;
}
