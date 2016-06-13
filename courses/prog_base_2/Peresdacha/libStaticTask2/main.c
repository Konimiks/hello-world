#include "chat.h"

struct chat_s{
    char *name;
    list_t *users;
    list_t *messages;
};

struct user_s{
    char *name;
    char * surname;
    int years;
};

struct message_s{
    char *msg;
    user_t *owner;
};

chat_t * chat_new(const char * Name){
    chat_t * self = malloc(sizeof(chat_t));
    self->name = malloc(sizeof(char) * (strlen(Name) + 1));
    self->name = Name;
    self->users = list_new();
    self->messages = list_new();
    return self;
}

void chat_free(chat_t * self){
    list_delete(self->users);
    list_delete(self->messages);
    free(self);
}

char * get_chat_name(chat_t * self){
    return self->name;
}

list_t * chat_get_list_of_users(chat_t * self){
    return self->users;
}

void chat_add_user(chat_t * chat, user_t * user){
    list_insertLast(chat->users, (void*) user);
}

user_t * user_new(const char * Name, const char * Surname, int Years){
    user_t * self = malloc(sizeof(user_t));
    self->name = malloc(sizeof(char) * (strlen(Name) + 1));
    self->name = Name;
    self->surname = malloc(sizeof(char) * (strlen(Surname) + 1));
    self->surname = Surname;
    self->years = Years;
    return self;
}
