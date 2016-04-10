#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <time.h>
#include <libxml/xmlmemory.h>
#define MAX_LENGTH 100

struct company{
    char post[MAX_LENGTH];
    char name[MAX_LENGTH];
};

struct salary{
    float amount;
    char valuta[MAX_LENGTH];
};

struct worker
{
    char name[MAX_LENGTH];
    char surname[MAX_LENGTH];
    struct company com;
    struct salary sal;
    int workingyears;
    time_t birthdate;
};

typedef struct worker worker;
int workers_fill_array(worker * workers_arr, size_t size);
void parse_worker(worker * w, xmlNodePtr w_node);
void copy_xmlcontents_to_buffer(char * buffer, xmlNodePtr node);
