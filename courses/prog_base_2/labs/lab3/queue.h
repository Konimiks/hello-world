#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#define QUEUE_MAXSIZE 10
#define OK 1
#define NOT_OK -1
#define DATA -10
#define EMPTY_ELEM -999.0
#define MAX_VALUE (float)20.0

typedef struct queue_s queue_t;

queue_t * queue_new(void);
void queue_free(queue_t * self);

float queue_getByInd(const queue_t * self, int index);

int queue_getSize(const queue_t * self);
int queuel(const queue_t * self);
int queue_isEmpty(const queue_t * self);

float queue_enqueueRand(queue_t * self);
int queue_firstEvent(const queue_t * self);
int queue_secondEvent(const queue_t * self);
int queue_thirdEvent(const queue_t * self);

#endif //QUEUE_H_INCLUDED
