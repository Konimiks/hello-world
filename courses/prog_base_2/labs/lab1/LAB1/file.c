#include <stdlib.h>
#include "file.h"

struct file_s
{
    char text[MAX_TEXT_SIZE];
};


file_t * file_new(char FileText[MAX_TEXT_SIZE])
{
    file_t * file = malloc(sizeof(struct file_s));
    if(file == NULL)
        return NULL;
    for(int i = 0; i < MAX_TEXT_SIZE; i++)
        file->text[i] = FileText[i];
    return file;
}

void file_process(file_t * fself, dic_t * dself)
{
    write_dic(dself, fself->text);
    free(fself);
}

void print_file(file_t * fself)
{
    printf("%s\n", fself->text);
}
