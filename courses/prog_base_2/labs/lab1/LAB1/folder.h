#ifndef FOLDER_INCLUDED
#define FOLDER_INCLUDED

#include "file.h"
#define MAX_FILENAME 50
#define MAX_FILES_COUNT 20
#define MAX_TEXT_SIZE 1000

typedef struct folder_s folder_t;

folder_t * folder_new(char * name);

void folder_free(folder_t * self);

int folder_get_files_count(folder_t * self);
file_t * folder_add_new_file(folder_t * self, char FileText[MAX_TEXT_SIZE]);

void folder_process_and_remove_files(folder_t * self, file_t * fself, dic_t * dself);

#endif // FOLDER_INCLUDED
