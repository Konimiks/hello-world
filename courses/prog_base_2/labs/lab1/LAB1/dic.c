#include <stdlib.h>
#include <string.h>
#include "dic.h"

struct dictionary
{
    char key[25];
    int number;
};

struct dic_s
{
    int wordcount;
    struct dictionary mas[1000];
};

dic_t * dic_new(void)
{
    dic_t * self = NULL;
    self = malloc(sizeof(struct dic_s));
    if(self == NULL)
        return NULL;
    for(int i = 0; i < 1000; i ++)
    {
        self->mas[i].number = 0;
        for(int j = 0; j < 25; j++)
            self->mas[i].key[j] = ' ';
    }
    self->wordcount = 0;
    return self;
}

void dic_free(dic_t * self)
{
    free(self);
}

void write_dic(dic_t * self, char FileText[MAX_TEXT_SIZE])
{
    int status = 0;
    char * istr;
    istr = strtok(FileText, " .,!&?/");
    while(istr != NULL)
    {
        for(int i = 0; i < self->wordcount; i++)
        {
            if(strcmp(istr, self->mas[i].key) == 0)
            {
                status = 1;
                self->mas[i].number++;
                break;
            }
            else continue;
        }
        if(status == 0)
        {
            strcpy(self->mas[self->wordcount].key, istr);
            self->mas[self->wordcount].number++;
            self->wordcount++;
        }

        status = 0;
        istr = strtok(NULL, " .,!&?/");
    }

}

void printdic(dic_t * self)
{
    for(int i = 0; i < self->wordcount; i++)
    {
        printf("%i ", self->mas[i].number);
        printf("%s", self->mas[i].key);
        printf("\n");
    }
}

int dic_getwordscount(dic_t * self)
{
    return self->wordcount;
}

int dic_getwordcount(dic_t * self, char word[])
{
    for(int i = 0; i < self->wordcount; i ++)
    {
        if(strcmp(self->mas[i].key, word) == 0)
            return self->mas[i].number;
    }
    return 0;
}
