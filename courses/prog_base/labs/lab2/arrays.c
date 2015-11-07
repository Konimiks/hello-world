#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>




void fillRand1(int arr[], int size)
{
    int i;
    for(i=0 ; i<size ; i++)
        arr[i]=rand() % 99 + 1 ; /* [1....99] */
}


int checkRand1(int arr[], int size)
{
    int i;
    for(i=0 ; i <= size ; i++)
        if(arr[i] < 1 && arr[i] > 99) return 0;
    return 1;

}


float meanValue(int arr[], int size)
{
    int i;
    float x=0.0;
    float result;
    for (i=0 ; i < size ; i++)
        x += arr[i];
    result=x/size;
    return result;
}

int minValue(int arr[], int size)
{
    int i;
    int min=100; /* все елементы массива меньше ста */
    for(i=0 ; i < size ; i++)
        if(arr[i]<min) min=arr[i];
    return min;
}


int meanIndex(int arr[], int size )
{
    int i,k;
    float x=0.0;
    float avverage;
    int INDEX;
    float result = 100.0 ;
    for (k=0 ; k < size ; k++)
        x += (float)arr[k];
    avverage = x/(float)size;
    for(i=0 ; i < size ; i++)
    {
        if ((fabs(avverage - (float)arr[i]) < result ))
            {
                result = fabs(avverage - (float)arr[i]) ;
                INDEX = i;
            }
    }
    return INDEX;
}


int minIndex(int arr[], int size)
{
    int i;
    int max = 100 ;
    int index;
    for (i=0 ; i<size ; i++)
    {
        if(arr[i] < max)
        {
            max = arr[i];
            index = i;
        }
    }
    return index ;
}


int maxOccurance(int arr[], int size)
{
    int i ,j;
    int q = 1, p = 1;
    int max = arr[0];
    for (i = 0; i < size; i++){
        for (j = i + 1; j < size; j++)
            if (arr[j] == arr[i])
            p++;
            if (p >= q)
            {
                q = p;
                max = arr[i];
            }
            if(p == q && arr[i] > max)
            max = arr[i];

            p = 1;
        }
    return max;
}


int diff(int arr1[], int arr2[], int res[], int size)
{
    int i;
    for(i=0 ; i<size ; i++)
    {
        res[i] = arr1[i] - arr2[i];
    }
    int j;
    for(j=0 ; j<size ; j++)
        {
            if (res[j] != 0 ) return 0;
            if (j<(size-1) && res[j] == 0 ) continue;
            if (res[size-1]==0) return 1;
        }

}


void divid(int arr1[], int arr2[],int res[], int size)
{
    int i;
    for( i=0 ; i <size ; i ++)
        res[i]=arr1[i]/arr2[i];
}

int lteq(int arr1[], int arr2[], int size)
{
    int i;
    for( i=0 ; i<size ; i++)
        if (arr1[i] > arr2[i]) return 1;
    return 0;
}


void land(int arr1[], int arr2[], int res[], int size)
{
    int i;
    for ( i=0 ; i < size ; i++)
        res[i] = arr1[i] & arr2[i];
}
