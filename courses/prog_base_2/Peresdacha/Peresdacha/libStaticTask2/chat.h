#ifndef CHAT_H
#define CHAT_H
#include "list.h"

typedef struct user_s user_t;
typedef struct message_s message_t;
typedef struct chat_s chat_t;

chat_t * chat_new(const char * Name);
void chat_free(chat_t * self);
char * get_chat_name(chat_t * self);
list_t * chat_get_list_of_users(chat_t * self);
void chat_add_user(chat_t * chat, user_t * user);
user_t * chat_remove_user_by_surname(chat_t * chat, const char * Surname);
void chat_add_message(chat_t * chat, message_t * msg);

user_t * user_new(const char * Name, const char * Surname, int Years);
void user_free(user_t * user);
char * user_get_name(user_t * user);
char * user_get_surname(user_t * user);
int user_get_age(user_t * user);
user_t * get_owner(message_t * msg);
list_t * get_list_of_messages_of_one_user(chat_t * chat, user_t * user);

message_t * message_new(const char * Msg, user_t * user);
void message_free(message_t * msg);
char * get_message_text(message_t * Msg);

#endif // CHAT_H
