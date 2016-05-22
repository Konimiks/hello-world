#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

typedef struct user_s user_t;

user_t * user_new(char * name);
void user_free(user_t * self);

char * user_getName(const user_t * self);

#endif //USER_H_INCLUDED
