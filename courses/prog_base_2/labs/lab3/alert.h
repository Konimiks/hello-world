/* alert.h AND alert.c DESCRIBES THE ARRAY OF ALERTS IN event_s struct AND METHODS TO WORK WITH IT
IT'S CONSTRUCTED USING void * TYPE TO GAIN FLEXIBILITY */

#ifndef ALERTARR_H_INCLUDED
#define ALERTARR_H_INCLUDED

#define OK 1
#define NOT_OK -1

typedef struct alertArr_s alertArr_t;

alertArr_t * alertArr_new(int size);
void alertArr_free(alertArr_t * self);

void alertArr_addLast(alertArr_t * self, void * elem);
void * alertArr_getByInd(const alertArr_t * self, int index);

int alertArr_getSize(const alertArr_t * self);
int alertArr_isEmpty(const alertArr_t * self);
int alertArr_isFull(const alertArr_t * self);

#endif //ALERTARR_H_INCLUDED
