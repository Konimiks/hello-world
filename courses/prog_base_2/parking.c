#include "parking.h"

struct parking_s{
    list_t *entry;
    list_t *exit;
    list_t *curr;
    int totalPlaces;
    int freePlaces;
};

struct owners_s{
    list_t * owners;
};

struct car_s{
    owner_t * owner;
    char * identifyNumber;
    char * mark;
    color_t color;
};

struct owner_s{
    char * name;
    char * surname;
    int years;
    double expirience;
    client_type_t type;
    int payment;
};

//parking
parking_t * parking_new(){
    parking_t * self = malloc(sizeof(parking_t));
    self->entry = list_new();
    self->exit = list_new();
    self->curr = list_new();
    self->totalPlaces = MAX_PARKING_PLACES;
    self->freePlaces = MAX_PARKING_PLACES;
    return self;
}

void parking_free(parking_t * self){
    free(self);
}

//car
car_t * car_new(char * id, char * mark, color_t color, owner_t * owner) {
    car_t * self = malloc(sizeof(car_t));
    self->identifyNumber = malloc(sizeof(char) * strlen(id) + 1);
    self->identifyNumber = id;
    self->mark = malloc(sizeof(char) * strlen(mark) + 1);
    self->mark = mark;
    self->color = color;
    self->owner = owner_new();
    self->owner = owner;
    return self;
}

void car_free(car_t * self){
    free(self->owner);
    free(self);
}
//owner
owner_t * owner_new(char * Name, char * Surname, int Years, double Expirience, client_type_t Type){
    owner_t * self = malloc(sizeof(owner_t));
    self->type = Type;
    self->name = Name;
    self->surname = Surname;
    self->years = Years;
    self->expirience = Expirience;
    if(Type == CLIENT_NEW)
        self->payment = 10;
    else if(Type == CLIENT_REGULAR)
        self->payment = 5;
    else self->payment = 0;
    return self;
}

void owner_free(owner_t * self){
    free(self);
}

char * getName(owner_t * self){
    return self->name;
}
char * getSurname(owner_t * self){
    return self->surname;
}
int getYears(owner_t * self){
    return self->years;
}
double getExperience(owner_t * self){
    return self->expirience;
}
client_type_t getType(owner_t * self){
    return self->type;
}
int getPayment(owner_t * self){
    return self->payment;
}

//------------------------------begin of 1st task
list_t * parking_getEntryList(parking_t * self){
    list_t * copy = list_new();
    for (int i = 0; i < list_getSize(self->entry); i++){
        list_addByIndex(copy, (void *) list_getNodeValueByIndex(self->entry, i), i);
    }
    return copy;
}

list_t * parking_getExitList(parking_t * self){
    list_t * copy = list_new();
    for (int i = 0; i < list_getSize(self->exit); i++){
        list_addByIndex(copy, (void *) list_getNodeValueByIndex(self->exit, i), i);
    }
    return copy;
}

int parking_getEntryCount(parking_t * self){
    return list_getSize(self->entry);
}

int parking_getExitCount(parking_t * self){
    return list_getSize(self->exit);
}
//----------------------------end of 1st task


//----------------------------begin of 3d task
int parking_letInForParking(parking_t * park_self, car_t * car_self){
    int rc;
    if(park_self->freePlaces != 0){
        list_insertLast(park_self->entry, (void *) car_self);
        list_insertLast(park_self->curr, (void *) car_self);
        park_self->freePlaces--;
        rc = OK;
    }
    else rc = NOT_OK;
    return rc;
}
//----------------------------end of 3d task


//----------------------------begin of 4th task
int parking_goOutFromParking(parking_t * park_self, car_t * car_self){
    int rc = NOT_OK;
    car_t * tmp;
    for(int i = 0; i < list_getSize(park_self->curr); i++){
        tmp = (car_t *)list_getNodeValueByIndex(park_self->curr, i);
        if(strcmp(car_self->identifyNumber, tmp->identifyNumber) == 0){
            rc = OK;
            list_insertLast(park_self->exit, (void *) car_self);
            list_list_removeByIndex(park_self->curr, i);
            park_self->freePlaces++;
            return rc;
        }
        else continue;
    }
    return rc;
    //if we return 0 it means that there was not such car on parking!!!
}
//----------------------------end of 4th task


//----------------------------begin of 5th task
list_t * parking_getCurrentList(parking_t * self){
    list_t * copy = list_new();
    for (int i = 0; i < list_getSize(self->curr); i++){
        list_addByIndex(copy, (void *) list_getNodeByIndex(self->curr, i), i);
    }
    return copy;
}
//----------------------------end of 5th task


//----------------------------begin of 6th task
owner_t * getInformationAboutOwner(car_t * self){
    owner_t * copy = self->owner;
    return copy;
}
//----------------------------end of 6th task
