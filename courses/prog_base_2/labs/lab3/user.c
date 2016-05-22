#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "user.h"

struct user_s {
	char name[25];
};

user_t * user_new(char * name) {
	user_t * self = malloc(sizeof(struct user_s));
	strcpy(self->name, name);
	return self;
}

void user_free(user_t * self) {
	free(self);
}

char * user_getName(const user_t * self) {
	char * name = malloc((strlen(self->name) + 1) * sizeof(char));
	strcpy(name, self->name);
	return name;
}

