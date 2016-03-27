#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "folder.h"
#include "file.h"

struct folder_s
{
    int count;
    char * name;
};

folder_t * folder_new(char * name)
{
    folder_t * self = NULL;
    self = malloc(sizeof(struct folder_s));
    if(self == NULL)
        return NULL;
    self->name = malloc(sizeof(char) * strlen(name));
    if (self->name == NULL)
    {
        free(self);
        return NULL;
    }
    self->count = 0;
    return self;
}

int folder_get_files_count(folder_t * self)
{
    return self->count;
}

void folder_free(folder_t * self)
{
    if(self->count == 0)
        free(self);
    else
        printf("plz process files before you delete this folder\n");
}


file_t * folder_add_new_file(folder_t * self, char FileText[MAX_TEXT_SIZE])
{
    file_t * file = file_new(FileText);
    self->count++;
    return file;
}

void folder_process_and_remove_files(folder_t * self, file_t * fself, dic_t * dself)
{
    file_process(fself, dself);
    self->count--;
}

