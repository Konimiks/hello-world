#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include "list.h"

#define NO_FILE -1
#define SUCCESS 1

typedef struct text_s text_t;
typedef struct sent_s sent_t;

text_t * text_new(void);
void text_free(text_t * self);

sent_t * sent_new(void);
void sent_free(sent_t * self);

int text_addText(text_t * self, const char * frName);
void text_formListOfSent(text_t * self);

void text_sortWordsAndWrite(text_t * self, const char * fwName);
sent_t * sent_sort(sent_t * self);

int file_writeWordsToFile(text_t * self, const char * fwName);

#endif // TYPES_H_INCLUDED
