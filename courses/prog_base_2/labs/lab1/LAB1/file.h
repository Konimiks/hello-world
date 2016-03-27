#ifndef FILE_INCLUDE
#define FILE_INCLUDE

#include "dic.h"
#define MAX_FILENAME 50
#define MAX_TEXT_SIZE 1000

typedef struct file_s file_t;


file_t * file_new(char FileText[MAX_TEXT_SIZE]);


void file_process(file_t * fself, dic_t * dself);

void print_file(file_t * fself);
#endif // FILE_INCLUDE
