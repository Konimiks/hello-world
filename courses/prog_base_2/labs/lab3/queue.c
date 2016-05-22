#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "queue.h"

struct queue_s {
	float * queue;
	int maxSize;
	int curSize;
	int tail;
};

queue_t * queue_new(void) {
	queue_t * self = malloc(sizeof(struct queue_s));
	self->queue = (float *) calloc(QUEUE_MAXSIZE, sizeof(float));
	self->maxSize = QUEUE_MAXSIZE;
	self->curSize = 0;
	self->tail = 0;
	return self;
}

void queue_free(queue_t * self) {
	free(self->queue);
	free(self);
}

int queue_isFull(const queue_t * self) {
	if (self->curSize == self->maxSize) {
		return OK;
	}
	else {
		return NOT_OK;
	}
}

int queue_isEmpty(const queue_t * self) {
	if (self->curSize == 0) {
		return OK;
	}
	else {
		return NOT_OK;
	}
}

float queue_enqueueRand(queue_t * self) {
	if (queue_isFull(self) != OK) {
		self->curSize++;
	}
	if (self->tail == self->maxSize) {
		self->tail = 0;
	}
	float elem = (float)pow(-1, rand()) * ((float)((double)rand() / (double)(RAND_MAX)) * MAX_VALUE);
	self->queue[self->tail] = elem;
	self->tail++;
	return elem;
}

float queue_getByInd(const queue_t * self, int index) {
	if (queue_isEmpty(self) == OK || index < 0 || index >= self->curSize) {
		return EMPTY_ELEM;
	}
	float elem = self->queue[index];
	return elem;
}

int queue_getSize(const queue_t * self) {
	return self->curSize;
}

int queue_firstEvent(const queue_t * self) {
	if (queue_isFull(self) != OK) {
		return DATA;
	}
	else {
		float sum = 0;
		for (int i = 0; i < queue_getSize(self); i++) {
			sum += self->queue[i];
		}
		sum /= queue_getSize(self);
		sum = fabs(sum);
		if (sum <= 1) {
			return OK;
		}
		else {
			return NOT_OK;
		}
	}
}

int queue_secondEvent(const queue_t * self) {
	if (queue_getSize(self) < 5) {
		return DATA;
	}
	else {
		float sum = 0;
		if (self->tail >= 5) {
			for (int i = self->tail - 5; i < self->tail; i++) {
				sum += self->queue[i];
			}
		}
		else {
			for (int i = self->tail - 1; i >= 0; i--) {
				sum += self->queue[i];
			}
			for (int i = queue_getSize(self) - (5 - self->tail); i < queue_getSize(self); i++) {
				sum += self->queue[i];
			}
		}
		sum = fabs(sum);
		if (sum > 5) {
			return OK;
		}
		else {
			return NOT_OK;
		}
	}
}

int queue_thirdEvent(const queue_t * self) {
	if (queue_getSize(self) < 5) {
		return DATA;
	}
	else {
		float sum = 0;
		if (self->tail >= 5) {
			for (int i = self->tail - 5; i < self->tail; i++) {
				sum += self->queue[i];
			}
		}
		else {
			for (int i = self->tail - 1; i >= 0; i--) {
				sum += self->queue[i];
			}
			for (int i = queue_getSize(self) - (5 - self->tail); i < queue_getSize(self); i++) {
				sum += self->queue[i];
			}
		}
		sum = fabs(sum);
		if (sum > 10) {
			return OK;
		}
		else {
			return NOT_OK;
		}
	}
}
