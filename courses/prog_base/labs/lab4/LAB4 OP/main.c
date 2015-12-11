#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>



struct City{
char name[10];
int index;
};


void seeroad(int value, int size, struct City arr[value], int array[value][value]);
void reName(int size, struct City arr[size]);
void buildcity(int size, int value, struct City arr[size], int array[size][size]);
void printlist(int number, struct City cities[number]);
void buildroad(int value, struct City arr[value], int array[value][value]);
void closeroad(int value, struct City arr[value], int array[value][value]);
void save(int number, int value, char rod[20], struct City arr[value], int array[value][value]);

int main(void) {
    int value = 20;
    FILE* fr = fopen("result.txt", "r");
    if(NULL == fr) {
        printf("CANNOT READ");
        return 1;
    }
    int number = 0;
    char read[1000];
    for(int i = 0; i < 50; i++){
		if (fgets(read, 1000, fr) == NULL)
            break;
        if (strstr(read, "roads:"))
            break;
        else number++;
	}
	//printf("%i\n", number);
	fclose(fr);
	FILE* fr2 = fopen("result.txt", "r");
	if(NULL == fr2) {
        printf("CANNOT READ");
        return 1;
    }
    struct City cities[value];
    printf("List of current cities :::\n");
    for(int i = 0; i < number; i++)
    {
        fscanf(fr2, "%i", &cities[i].index);
        fscanf(fr2, "%s", &cities[i].name);

        printf("%i ", cities[i].index);
        printf("%s\n", cities[i].name);
    }
    char rod[20];
    fscanf(fr2, "%s", &rod);

    int roads[value][value];
    for(int i = 0; i < number; i++)
        for(int j = 0; j< number; j++)
            fscanf(fr2, "%i", &roads[i][j]);


    fclose(fr2);

    printf("\n");


    METKA:;
    //for(int i = 0; i < number; i++)
    char comand[15] = {0};
    printf("ENTER YOUR COMMAND::");
    gets(comand);
    if(strcmp("seeroad", comand) == 0)
        seeroad(value, number, cities, roads);
    else if(strcmp("rename", comand) == 0)
        reName(number, cities);
    else if(strcmp("buildcity", comand) == 0)
    {
        buildcity(number, value, cities, roads);
        number++;
    }
    else if(strcmp("printlist", comand) == 0)
        printlist(number, cities);
    else if(strcmp("buildroad", comand) == 0)
        buildroad(value, cities, roads);
    else if(strcmp("closeroad", comand) == 0)
        closeroad(value, cities, roads);
    else if(strcmp("help", comand) == 0)
        help();
    else if(strcmp("save", comand) == 0)
        save(number, value, rod, cities, roads);
    else if(strcmp("exit", comand) == 0)
        return 0;
    else if(strcmp("maygo", comand) == 0)
    {
        int mas[20];
        for(int i = 0; i < 20; i++)
            mas[i] = -2;
        int hero = 0;
        printf("Enter the index of the city from which you want to go::");
        int start;
        int finish;
        scanf("%i", &start);
        printf("Enter the index of the city to which you want to go::");
        scanf("%i", &finish);
        maygo(value, number, number - 1, start, finish, start, roads, mas);
        for(int i = 0; i < value; i++)
        {
            if(mas[i] != -2)
                hero++;
        }
        hero--;
        if(start == finish)
            printf("YOU are already in this city!!!\n");
        else if(maygo(value, number, number - 1, start, finish, start, roads, mas) == -1)
            printf("You can`t go there!!(no roads)\n");
        else printf("You need to pass %i cities\n", hero);
    }
    fflush(stdin);
    goto METKA;



    return 0;
}


void seeroad(int value, int size, struct City arr[value], int array[value][value]){
    printf("Enter the index of city to see the rooads from this city::");
    int tocity;
    scanf("%i", &tocity);

    printf("From %s you may go to::\n", arr[tocity].name);
    for(int j = 0;j < size; j++){
        if(array[tocity][j] == 1)
        {
            printf("%s, ", arr[j].name);
        }
    }
    printf("\n\n");
}

void reName(int size, struct City arr[size])
{
    char newName [10] = {0};
    int number;
    char old [10];
    printf("Enter the index of city that you want to rename::");
    scanf("%i", &number);
    for(int i = 0; i < 10; i++)
    {
        old[i] = arr[number].name[i];
    }
    printf("Enter the new name of the city::");
    scanf("%s", &newName);
    for(int i = 0; i < 10; i++)
    {
        arr[number].name[i] = newName[i];
    }
    printf("City %s was renamed into %s\n", old, arr[number].name);
}

void buildcity(int size, int value, struct City arr[value], int array[value][value])
{
    char newName [10] = {0};
    printf("Enter the new name of the city::");
    scanf("%s", &newName);
    for(int i = 0; i < 10; i++)
    {
        arr[size].name[i] = newName[i];
    }
    arr[size].index = size;
    array[size][size] = 2;
    for(int i =0; i < size; i++){
        array[size][i] = 0;
        array[i][size] = 0;
    }
}

void printlist(int number, struct City cities[number])
{
    for(int i = 0; i < number; i++)
    {
        printf("%i ", cities[i].index);
        printf("%s\n", cities[i].name);
    }
}

void buildroad(int value, struct City arr[value], int array[value][value])
{
    int index;
    printf("Enter the index of city from which you want to build road::");
    scanf("%i", &index);
    int tocity;
    printf("Enter the index of city from which you want to build road::");
    scanf("%i", &tocity);
    array[index][tocity] = 1;
    array[tocity][index] = 1;
}

void closeroad(int value, struct City arr[value], int array[value][value])
{
    int index;
    printf("Enter the index of city from which you want to close road::");
    scanf("%i", &index);
    int tocity;
    printf("Enter the index of city from which you want to close road::");
    scanf("%i", &tocity);
    array[index][tocity] = 0;
    array[tocity][index] = 0;
}



void help(){
printf("List of comands::\nseeroad\nbuildcity\nbuildroad\nrename\nprintlist\ncloseroad\nsave\nmaygo\nexit\n");
}


void save(int number, int value, char rod[20], struct City arr[value], int array[value][value])
{
    FILE* fw = fopen("result.txt", "w");
    if(NULL == fw) {
        printf("CANNOT WRITE");
        return 1;
    }
    for(int i = 0; i < number; i++)
    {
        fprintf(fw, "%i ", arr[i].index);
        fprintf(fw, "%s\n", arr[i].name);
    }
    fprintf(fw, "%s\n", rod);

    for(int i = 0; i < number; i++)
        for(int j = 0; j < number; j++)
            fprintf(fw, "%i ", array[i][j]);

    fclose(fw);
}


int maygo(int value, int size, int n, int start, int finish, int point, int arr[value][value], int mas[value])
{
    int status, i;
    if (n == 0)
        return -1;
    if (arr[start][finish] == 1)
        {
        mas[n] = start;
        return 0;
        }
    for (i = 0; i < size; i++)
        if (arr[start][i] == 1 && i != start && i != point)
        {
            status = maygo(value, size, n - 1, i, finish, start, arr, mas);
            if(status == 0)
            {
                mas[n] = start;
                return 0;
            }
        }
    return -1;
}
