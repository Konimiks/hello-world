#ifndef MY_PARKING
#define MY_PARKING
#include <string.h>
#include "list.h"
#define MAX_PARKING_PLACES 10
#define OK 1
#define NOT_OK 0


//type of client for rates
typedef enum{
    CLIENT_VIP = 0,
    CLIENT_REGULAR,
    CLIENT_NEW
} client_type_t;

typedef enum{
    RED = 0,
    GREEN,
    BLACK,
    WHITE,
    BLUE
}color_t;

typedef struct parking_s parking_t;
typedef struct owners_s owners_t;
typedef struct owner_s owner_t;
typedef struct car_s car_t;

//parking
parking_t * parking_new();
void parking_free(parking_t * self);

//car
car_t * car_new(char * id, char * mark, color_t color, owner_t * owner);
void car_free(car_t * self);

//owner
owner_t * owner_new(char * Name, char * Surname, int Years, double Expirince, client_type_t Type);
void owner_free(owner_t * self);

char * getName(owner_t * self);
char * getSurname(owner_t * self);
int getYears(owner_t * self);
double getExperience(owner_t * self);
client_type_t getType(owner_t * self);

//----------------------------begin of 1st task
list_t * parking_getEntryList(parking_t * self);
list_t * parking_getExitList(parking_t * self);
int parking_getEntryCount(parking_t * self);
int parking_getExitCount(parking_t * self);
//----------------------------end of 1st task


//----------------------------begin of 3d task
int parking_letInForParking(parking_t * park_self, car_t * car_self);
//----------------------------end of 3d task


//----------------------------begin of 4th task
int parking_goOutFromParking(parking_t * park_self, car_t * car_self);
//----------------------------end of 4th task


//----------------------------begin of 5th task
list_t * parking_getCurrentList(parking_t * self);
//----------------------------end of 5th task

//----------------------------begin of 6th task
owner_t * getInformationAboutOwner(car_t * self);
//----------------------------end of 6th task
#endif // MY_PARKING

