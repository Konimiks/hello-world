#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "JSON/cJSON.h"
#include "worker/worker.h"
#include "read.h"

void read_parseWorkers(worker_t** workers)
{
    FILE *file = fopen("worker.json", "r");
    char text[10000];
    char line[100];
    while(fgets(line, 100, file) != NULL){
        strcat(text, line);
    }
    fclose(file);

    cJSON* jList = cJSON_Parse(text);
    int count = cJSON_GetArraySize(jList);
    for(int i = 0; i<count; i++){
        cJSON* jItem = cJSON_GetArrayItem(jList, i);
        char* name = cJSON_GetObjectItem(jItem, "name")->valuestring;
        char* surname = cJSON_GetObjectItem(jItem, "surname")->valuestring;
        char* birthdate = cJSON_GetObjectItem(jItem, "birthdate")->valuestring;
        int experience = cJSON_GetObjectItem(jItem, "experience")->valueint;
        double rating = cJSON_GetObjectItem(jItem, "rating")->valuedouble;
        worker_fill(workers[i], i, name, surname, birthdate, experience, rating);
    }
    cJSON_Delete(jList);
}
