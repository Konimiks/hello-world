#ifndef WORKER_H_INCLUDED
#define WORKER_H_INCLUDED

#define MAX_WORKERS 7

typedef struct worker_s worker_t;

worker_t * worker_new(void);
void worker_free(worker_t * worker);

void worker_fill(worker_t* worker, int id, char* name, char* surname, int salary, int year);

int worker_getId(worker_t* );
char* worker_getName(worker_t*);
char* worker_getSurname(worker_t*);
int worker_getSalary(worker_t* );
int worker_getYear(worker_t* worker);


char* worker_makeWorkerJSON(worker_t *worker);
void worker_print(worker_t *worker);
char* worker_getWorker(worker_t* worker);

#endif // WORKER_H_INCLUDED
