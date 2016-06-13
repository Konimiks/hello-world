#include "list.h"
#include "chat.h"

int main(void){
    chat_t * chat = chat_new("First Chat");
    printf("First task(Chat name is) : %s\n", get_chat_name(chat));
    list_t * users_list = list_new();
    user_t * firstUser = user_new("Dima", "Diachenko", 18);
    chat_add_user(chat, firstUser);

    users_list = chat_get_list_of_users(chat);

    return 0;
}
