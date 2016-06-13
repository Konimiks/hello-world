#include "chat.h"
#include <string.h>

struct chat_s{
    char *name;
    list_t *users;
    list_t *messages;
};

struct user_s{
    char *name;
    char *surname;
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
    list_free(self->users);
    list_free(self->messages);
    free(self);
}

char * get_chat_name(chat_t * self){
    return self->name;
}

list_t * chat_get_list_of_users(chat_t * self){
    return self->users;
}

void chat_add_user(chat_t * chat, user_t * user){
    list_push_back(chat->users, (void*) user);
}

user_t * chat_remove_user_by_surname(chat_t * chat, const char * Surname)
{
    for(int i = 0; i < list_getSize(chat->users); i++){
        user_t * tmp = list_get(chat->users, i);
        if(strcmp(user_get_surname(tmp), Surname) == 0){
            return list_remove(chat->users, i);
        }
    }
    return NULL;
}

void chat_add_message(chat_t * chat, message_t * msg){
    list_t * tmp = list_new();
    tmp = chat_get_list_of_users(chat);
    for(int  i = 0; i < list_getSize(tmp); i++){ // if new user print a message
        user_t * tmpUser = (user_t*) list_get(tmp, i);
        if(strcmp(user_get_name(tmpUser), user_get_name(msg->owner)) != 0 ||
           strcmp(user_get_surname(tmpUser), user_get_surname(msg->owner)) != 0 ||
           user_get_age(tmpUser) != user_get_age(msg->owner))
        {
            if( i == (list_getSize(tmp) - 1)){
                list_push_back(chat, (void *) user_new(user_get_name(msg->owner),
                                        user_get_surname(msg->owner),user_get_age(msg->owner)));
                break;
            }
            continue;
        }
        else {
            break;
        }
    }
    list_push_back(chat->messages, (void*) msg);
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

void user_free(user_t * user){
    free(user);
}

char * user_get_name(user_t * user){
    return user->name;
}

char * user_get_surname(user_t * user){
    return user->surname;
}

int user_get_age(user_t * user){
    return user->years;
}

message_t * message_new(const char * Msg, user_t * user){
    message_t * self = malloc(sizeof(message_t));
    self->owner = user_new(user_get_name(user), user_get_surname(user), user_get_age(user));
    self->msg = malloc(sizeof(char) * (strlen(Msg) + 1));
    self->msg = Msg;
    return self;
}

void message_free(message_t * msg){
    user_free(msg->owner);
    free(msg);
}

char * get_message_text(message_t * Msg){
    return Msg->msg;
}

list_t * get_list_of_messages_of_one_user(chat_t * chat, user_t * user){
    list_t * msgList = list_new();
    for(int i = 0; i < list_getSize(chat->messages); i++){
        message_t * tmp = list_get(chat->messages, i);
        if(strcmp(user_get_surname(tmp->owner), user_get_surname(user)) == 0 &&
                strcmp(user_get_name(tmp->owner), user_get_name(user)) == 0 &&
                    user_get_age(tmp->owner) == user_get_age(user))
            {
                list_push_back(msgList, (void*) tmp);
            }
        else continue;
    }
    return msgList;
}

user_t * get_owner(message_t * msg){
    return msg->owner;
}

list_t * get_last_messages(chat_t * chat, int count){
    if(count > list_getSize(chat->messages))
        return NULL;
    else{
        list_t * tmp = list_new();
        for(int i = list_getSize(chat->messages) - 1; i >= list_getSize(chat->messages) - count; i--){
            list_push_back(tmp, (void*) list_get(chat->messages, i));
        }
        return tmp;
    }
}
