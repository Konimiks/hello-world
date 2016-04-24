#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "animal.h"
#include "sqlite3.h"

int main(void)
{
    sqlite3 * db;
    int rc = 0;
    rc = sqlite3_open("workers.db", &db);
    if(SQLITE_OK != rc){
        printf("Error!");
        return 1;
    }
    dataPrintAll(db);
    dataInsert(db, 8, "2010-08-12", "R", "Poguhi", 1, 300, 5676845);
    dataPrintAll(db);
    dataDelete(db, 2);
    dataPrintAll(db);
    dataUpdate(db, 8, "2013-08-21", "Ruslan", "umkjnyhtbegvr", 15, 1000, 154222);
    dataPrintAll(db);
    dataSelect(db, 100, 5678);
    //dataInsert(db, 4, "2013-08-22", "Hutr", "Poi", 17, 34789, 5679845);
    //dataDelete(db, 4);
    //dataPrintAll(db);
    //dataUpdate(db, 4, "2013-08-21", "Hutrgou", "Poied", 18, 34589, 1111222);
    //dataSelect(db, 100, 5678);

    sqlite3_close(db);
    return 0;
}
