#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "animal.h"

void dataInsert(sqlite3 * db, int id, char *data, char *name, char *surname, double years, double salary, int number){
    sqlite3_stmt *stmt = NULL;
    int rc = 0;
    char * sql = "INSERT INTO workers VALUES (?,?,?,?,?,?,?);";

    rc = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if(SQLITE_OK != rc){
        printf("Error prepare! %i\n", rc);
        return;
    }

    rc = sqlite3_bind_int(stmt, 1, id);
    if(SQLITE_OK != rc){
        printf("Error bind id! %i\n", rc);
        return;
    }
    rc = sqlite3_bind_text(stmt, 2, data, strlen(data), SQLITE_STATIC);
    if(SQLITE_OK != rc){
        printf("Error bind data! %i\n", rc);
        return;
    }
    rc = sqlite3_bind_text(stmt, 3, name, strlen(name), SQLITE_STATIC);
    if(SQLITE_OK != rc){
        printf("Error bind name! %i\n", rc);
        return;
    }
    rc = sqlite3_bind_text(stmt, 4, surname, strlen(surname), SQLITE_STATIC);
    if(SQLITE_OK != rc){
        printf("Error bind surname! %i\n", rc);
        return;
    }
    rc = sqlite3_bind_double(stmt, 5, years);
    if(SQLITE_OK != rc){
        printf("Error bind years! %i\n", rc);
        return;
    }
    rc = sqlite3_bind_double(stmt, 6, salary);
    if(SQLITE_OK != rc){
        printf("Error bind salary! %i\n", rc);
        return;
    }
    rc = sqlite3_bind_int(stmt, 7, number);
    if(SQLITE_OK != rc){
        printf("Error bind number! %i\n", rc);
        return;
    }

    if(SQLITE_DONE != (rc = sqlite3_step(stmt))){
        printf("Not inserted! %i\n", rc);
        return;
    }
    printf("Data inserted!\n");
    sqlite3_finalize(stmt);
}

void dataDelete(sqlite3 *db, int id){
    sqlite3_stmt *stmt = NULL;
    int rc = 0;
    char * sql = "DELETE FROM workers WHERE id=?;";

    if(SQLITE_OK != sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL)){
        printf("Not prepared!\n");
        return;
    }

    rc = sqlite3_bind_int(stmt, 1, id);
    if(SQLITE_OK != rc){
        printf("Error bind id! %i\n", rc);
        return;
    }

    if(SQLITE_DONE != (rc = sqlite3_step(stmt))){
        printf("Not deleted! %i\n", rc);
        return;
    }
    printf("Data deleted!\n");
    sqlite3_finalize(stmt);
}

void dataUpdate(sqlite3 *db, int id, char *data, char *name, char *surname, double years, double salary, int number){
    sqlite3_stmt *stmt = NULL;
    int rc = 0;
    char * sql = "UPDATE workers SET data = ?, Name = ?, Surname = ?, years = ?, salary = ?, number = ? WHERE id = ?;";

    rc = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if(SQLITE_OK != rc){
        printf("Error prepare! %i\n", rc);
        return;
    }

    rc = sqlite3_bind_int(stmt, 7, id);
    if(SQLITE_OK != rc){
        printf("Error bind id! %i\n", rc);
        return;
    }
    rc = sqlite3_bind_text(stmt, 1, data, strlen(data), SQLITE_STATIC);
    if(SQLITE_OK != rc){
        printf("Error bind data! %i\n", rc);
        return;
    }
    rc = sqlite3_bind_text(stmt, 2, name, strlen(name), SQLITE_STATIC);
    if(SQLITE_OK != rc){
        printf("Error bind name! %i\n", rc);
        return;
    }
    rc = sqlite3_bind_text(stmt, 3, surname, strlen(surname), SQLITE_STATIC);
    if(SQLITE_OK != rc){
        printf("Error bind surname! %i\n", rc);
        return;
    }
    rc = sqlite3_bind_double(stmt, 4, years);
    if(SQLITE_OK != rc){
        printf("Error bind years! %i\n", rc);
        return;
    }
    rc = sqlite3_bind_double(stmt, 5, salary);
    if(SQLITE_OK != rc){
        printf("Error bind salary! %i\n", rc);
        return;
    }
    rc = sqlite3_bind_int(stmt, 6, number);
    if(SQLITE_OK != rc){
        printf("Error bind number! %i\n", rc);
        return;
    }

    if(SQLITE_DONE != (rc = sqlite3_step(stmt))){
        printf("Not updated! %i\n", rc);
        return;
    }
    printf("Data updated!\n");
    sqlite3_finalize(stmt);
}

void dataSelect(sqlite3 *db, double salary, double years){
    sqlite3_stmt *stmt = NULL;
    int rc = 0;
    char * sql = "SELECT COUNT(*) FROM workers WHERE salary > ? AND years < ?;";

    if(SQLITE_OK != sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL)){
        printf("Not prepared!\n");
        return;
    }

    rc = sqlite3_bind_double(stmt, 1, salary);
    if(SQLITE_OK != rc){
        printf("Error bind salary! %i\n", rc);
        return;
    }
    rc = sqlite3_bind_double(stmt, 2, years);
    if(SQLITE_OK != rc){
        printf("Error bind count! %i\n", rc);
        return;
    }

    rc = sqlite3_step(stmt);
    if(SQLITE_ERROR == rc){
        printf("Error step! %i\n", rc);
        return;
    }

    int count = sqlite3_column_int(stmt, 0);
    printf("workers that have salary more than %f and worked less than %f years: %i\n", salary, years, count);
    sqlite3_finalize(stmt);
}

void dataPrintAll(sqlite3 *db){
    int rc = 0;
    sqlite3_stmt *stmt = NULL;
    const char * sql = "SELECT * FROM workers;";
    rc = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if(SQLITE_OK != rc){
        printf("Error prepare!");
        return;
    }

    while(1){
        rc = sqlite3_step(stmt);
        if(SQLITE_ERROR == rc){
            printf("Error step!");
            return;
        } else if(SQLITE_DONE == rc){
            break;
        }

        for(int i = 0; i < sqlite3_column_count(stmt); i++){
            const char * type = sqlite3_column_decltype(stmt, i);
            const char * colName = sqlite3_column_name(stmt, i);
            const unsigned char * text = sqlite3_column_text(stmt, i);
            printf("%10s [%7s]: %s\n", colName, type, text);
        }
        printf("\n");
    }
    sqlite3_finalize(stmt);
}
