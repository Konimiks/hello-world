#ifndef MY_DATABASE_TABLE
#define MY_DATABASE_TABLE
#include "sqlite3.h"

// INSERT INTO Animal VALUES(....);
void dataInsert(sqlite3 *db, int id, char *data, char *name, char *surname, double years, double salary, int number);

// DELETE FROM Animal WHERE id = 34;
void dataDelete(sqlite3 *db, int id);

// UPDATE Animal SET years = 45.8 WHERE id = 3;
void dataUpdate(sqlite3 *db, int id, const char * data, char *name, char *surname, double years, double salary, int number);

// SELECT * FROM Animal ....;
void dataSelect(sqlite3 *db, double salary, double years);

//Prints table data
void dataPrintAll(sqlite3 *db);

#endif
