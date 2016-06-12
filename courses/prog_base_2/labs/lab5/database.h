#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "worker/worker.h"
#include <stdbool.h>

typedef struct db_s db_t;

db_t * db_new(const char * dbFileName);
void db_free(db_t * db_data);

void db_insertWorker(db_t* db_data, worker_t* work);
worker_t * db_getWorkerById(db_t* database, unsigned int id);
bool db_checkId(db_t*, unsigned int);
void db_fillWorkerArr(db_t*, worker_t**);

void db_deleteWorker(db_t* database, unsigned int id);
int db_countWorkers(db_t* database);
char* db_personalTask(db_t* base, char* salaryReq, int salaryVal, char* yearReq, int yearVal, worker_t** workers);


#endif // DATABASE_H_INCLUDED
