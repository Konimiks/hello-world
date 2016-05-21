#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "list.h"
#include "parking.h"

int main()
{
    list_t * myfirstList = list_new();
    list_t * mysecondList = list_new();
    parking_t * myParking = parking_new();
    owner_t * owner1 = owner_new("Vlad", "Vavilov", 45, 14.5, CLIENT_VIP);
    car_t * car1 = car_new("ft456", "Audi", RED, owner1);
    if(0 == parking_letInForParking(myParking, car1))
        printf("Error while parking!");
    printf("Entry list size before adding: %i\n", list_getSize(myfirstList));
    myfirstList = parking_getEntryList(myParking);
    printf("Entry list size after adding: %i\n", list_getSize(myfirstList));
    if(0 == parking_goOutFromParking(myParking, car1))
        printf("Error while going out of parking!");
    printf("Exit list size before outting: %i\n", list_getSize(mysecondList));
    mysecondList = parking_getExitList(myParking);
    printf("Exit list size after outting: %i\n", list_getSize(mysecondList));

    return 0;
}


