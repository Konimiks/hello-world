#ifndef WORKER_H_INCLUDED
#define WORKER_H_INCLUDED

#define MAX_WORKERS 7

typedef struct worker_s worker_t;

worker_t * worker_new(void);
void worker_free(worker_t * worker);

void worker_fill(worker_t* worker, int id, char* name, char* surname, char* birthdate, int exp, double rating);

int worker_getId(worker_t* );
char* worker_getName(worker_t*);
char* worker_getSurname(worker_t*);
char* worker_getBirthdate(worker_t*);
int worker_getExp(worker_t*);
double worker_getRate(worker_t*);

int worker_workersCount(worker_t** workers);

char* worker_makeWorkerJSON(worker_t *worker);
void worker_print(worker_t *worker);

#endif // WORKER_H_INCLUDED
