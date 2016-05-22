#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include "user.h"
#include "queue.h"

typedef struct event_s event_t;

typedef void (*alert)(user_t * receiver, event_t * event);

event_t * event_new(char * description);
void event_free(event_t * self);

char * event_getDesc(event_t * self);
void event_addAlertSingle(user_t * userPtr, event_t * evPtr, alert fn);
void event_addAlertSeveral(user_t ** userArray, int userSize, event_t * evPtr, alert fn);

void event_start(event_t * firstEv, event_t * secondEv, event_t * thirdEv, queue_t * queuePtr);

#endif // EVENT_H_INCLUDED
