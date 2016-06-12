#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "worker.h"
#include "../JSON/cJSON.h"


struct worker_s
{
    int id;
    char name[50];
    char surname[50];
    int salary;
    int year;
};

worker_t* worker_new(void){
    worker_t * worker = malloc(sizeof(struct worker_s));
    worker->id = -1;
    strcpy(worker->name, "NoName");
    strcpy(worker->surname, "NoSurname");
    worker->salary = 0;
    worker->year = 0;
    return worker;
}

void worker_free(worker_t * worker){
    free(worker);
}

int worker_getId(worker_t* worker){
    return worker->id;
}

char* worker_getName(worker_t* worker)
{
    return worker->name;
}

char* worker_getSurname(worker_t* worker){
    return worker->surname;
}

int worker_getSalary(worker_t* worker)
{
    return worker->salary;
}

int worker_getYear(worker_t* worker){
    return worker->year;
}

void worker_fill(worker_t* worker, int id, char* name, char* surname, int salary, int year)
{
    worker->id = id;

    strcpy(worker->name, name);
    strcpy(worker->surname, surname);

    worker->salary = salary;
    worker->year = year;
}

char* worker_makeWorkerJSON(worker_t *worker){
    if(worker == NULL)
        return NULL;

    char* inJsn = NULL;

    cJSON* workerJsn = cJSON_CreateObject();

    cJSON_AddItemToObject(workerJsn, "Id", cJSON_CreateNumber(worker->id));
    cJSON_AddItemToObject(workerJsn, "Name", cJSON_CreateString(worker->name));
    cJSON_AddItemToObject(workerJsn, "Surname", cJSON_CreateString(worker->surname));
    cJSON_AddItemToObject(workerJsn, "Salary", cJSON_CreateNumber(worker->salary));
    cJSON_AddItemToObject(workerJsn, "Year", cJSON_CreateNumber(worker->year));

    inJsn = cJSON_Print(workerJsn);
    cJSON_Delete(workerJsn);
    return inJsn;
}

void worker_print(worker_t * worker){
    printf("Id: %i\nName: %s\nSurname: %s\nSalary: %i\nYear: %i\n\n----------------------\n\n",
        worker->id, worker->name, worker->surname,
        worker->salary, worker->year);
}

char* worker_getWorker(worker_t* worker)
{
    char one[500];
    sprintf(one,
            "     Id: %i\n"
            "   Name: %s\n"
            "Surname: %s\n"
            " Salary: %i\n"
            "   Year: %i\n\n",
            worker->id, worker->name, worker->surname,
            worker->salary, worker->year);
    return one;
}
