#ifndef DIC_INCLUDE
#define DIC_INCLUDE

#define MAX_TEXT_SIZE 1000

typedef struct dic_s dic_t;

dic_t * dic_new(void);
void dic_free(dic_t * self);

void write_dic(dic_t * self, char FileText[MAX_TEXT_SIZE]);

void printdic(dic_t * self);

int dic_getwordscount(dic_t * self);

int dic_getwordcount(dic_t * self, char word[]);

#endif
