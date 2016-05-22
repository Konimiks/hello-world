#include <stdlib.h>
#include <stdio.h>

#include "alert.h"

struct alertArr_s {
	void ** arr;
	int maxSize;
	int curSize;
};

alertArr_t * alertArr_new(int size) {
	alertArr_t * self = malloc(sizeof(struct alertArr_s));
	self->arr = calloc(size, sizeof(void *));
	self->maxSize = size;
	self->curSize = 0;
	return self;
}

void alertArr_free(alertArr_t * self) {
	free(self->arr);
	free(self);
}

void alertArr_addLast(alertArr_t * self, void * elem) {
	if (alertArr_isFull != OK) {
		self->arr[self->curSize] = elem;
		self->curSize++;
	}
}

void * alertArr_getByInd(const alertArr_t * self, int index) {
	if (alertArr_isEmpty(self) == OK || index < 0 || index >= self->curSize) {
		return NULL;
	}
	else {
		void * elem = self->arr[index];
		return elem;
	}
}

int alertArr_getSize(const alertArr_t * self) {
	return self->curSize;
}

int alertArr_isEmpty(const alertArr_t * self) {
	if (self->curSize == 0) {
		return OK;
	}
	else {
		return NOT_OK;
	}
}

int alertArr_isFull(const alertArr_t * self) {
	if (self->curSize == self->maxSize) {
		return OK;
	}
	else {
		return NOT_OK;
	}
}
