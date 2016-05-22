#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "alert.h"
#include "event.h"
#define USERS_MAXSIZE 100

struct alert_s {
	user_t * receiver;
	alert func;
};

typedef struct alert_s alert_t;

struct event_s {
	char desc[200];
	alert_t * alert_array;
};

event_t * event_new(char * description) {
	event_t * self = malloc(sizeof(struct event_s));
	strcpy(self->desc, description);
	self->alert_array = alertArr_new(USERS_MAXSIZE);
	return self;
}

void event_free(event_t * self) {
	int size = alertArr_getSize(self->alert_array);
	for (int i = 0; i < size; i++) {
		free(alertArr_getByInd(self->alert_array, i));
	}
	alertArr_free(self->alert_array);
	free(self);
}

char * event_getDesc(event_t * self) {
	char * desc = malloc((strlen(self->desc) + 1) * sizeof(char));
	strcpy(desc, self->desc);
	return desc;
}

void event_addAlertSingle(user_t * userPtr, event_t * evPtr, alert fn) {
	alert_t * alertSmp = malloc(sizeof(struct alert_s));
	alertSmp->receiver = userPtr;
	alertSmp->func = fn;
	alertArr_addLast(evPtr->alert_array, alertSmp);
}

void event_addAlertSeveral(user_t ** userArray, int userSize, event_t * evPtr, alert fn) {
	for (int i = 0; i < userSize; i++) {
		event_addAlertSingle(userArray[i], evPtr, fn);
	}
}

static void event_call(event_t * self) {
	event_t * event = self;
	int size = alertArr_getSize(self->alert_array);
	for (int i = 0; i < size; i++) {
		alert_t * alert = (alert_t *)alertArr_getByInd(self->alert_array, i);
		alert->func(alert->receiver, self);
	}
}

static int event_firstEvent(event_t * self, queue_t * queuePtr) {
	if (queue_firstEvent(queuePtr) == DATA) {
		return DATA;
	}
	else if (queue_firstEvent(queuePtr) == NOT_OK) {
		return NOT_OK;
	}
	else {
		puts("IT IS FIRST EVENT NOW!!!");
		event_call(self);
	}
}

static int event_secondEvent(event_t * self, queue_t * queuePtr) {
	if (queue_secondEvent(queuePtr) == DATA) {
		return DATA;
	}
	else if (queue_secondEvent(queuePtr) == NOT_OK) {
		return NOT_OK;
	}
	else {
		puts("IT IS SECOND EVENT NOW!!!");
		event_call(self);
	}
}

static int event_thirdEvent(event_t * self, queue_t * queuePtr) {
	if (queue_thirdEvent(queuePtr) == DATA) {
		return DATA;
	}
	else if (queue_thirdEvent(queuePtr) == NOT_OK) {
		return NOT_OK;
	}
	else {
		puts("IT IS THIRD EVENT NOW!!!");
		event_call(self);
	}
}

void event_start(event_t * firstEv, event_t * secondEv, event_t * thirdEv, queue_t * queuePtr) {
	puts("\nNew measurement:::");
	queue_enqueueRand(queuePtr);
	int check;
	Sleep(500);
	check = event_firstEvent(firstEv, queuePtr);
	if (check == DATA || check == NOT_OK) {
		puts("First event:");
		if (check == DATA) {
			puts("Nothing for first event");
		}
		else if (check == NOT_OK) {
			puts("Nothing special in first event");
		}
	}

	Sleep(500);
	check = event_secondEvent(secondEv, queuePtr);
	if (check == DATA || check == NOT_OK) {
		puts("Second event:");

		if (check == DATA) {
			puts("Nothing for second event");
		}
		else if (check == NOT_OK) {
			puts("Nothing special in second event...");
		}
	}

	Sleep(500);
	check = event_thirdEvent(thirdEv, queuePtr);
	if (check == DATA || check == NOT_OK) {
		puts("Third event:");

		if (check == DATA) {
			puts("Nothing for third event");
		}
		else if (check == NOT_OK) {
			puts("Nothing special in third event...");
		}
	}

	Sleep(500);
	puts("\n");
}
