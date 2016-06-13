#include "list.h"
#include "chat.h"

int main(void){
    chat_t * chat = chat_new("First Chat");
    printf("1st task(Chat name is) : %s\n", get_chat_name(chat));//1st task

    user_t * firstUser = user_new("Dima", "Diachenko", 18);
    chat_add_user(chat, firstUser);
    user_t * secondUser = user_new("Gleb", "Davidov", 18);
    chat_add_user(chat, secondUser); //6th task

    list_t * users_list = list_new();
    users_list = chat_get_list_of_users(chat);

    printf("4th task (and 6th task)(Users in list) : %i\n", list_getSize(users_list));//4th task

    printf("2d task : List of users:\n"); // 2d task
    for(int i = 0; i < list_getSize(users_list); i++){
        user_t * tmp  = (user_t*) list_get(users_list, i);
        printf("%s %s %i\n", user_get_name(tmp), user_get_surname(tmp), user_get_age(tmp));
    }

    printf("7th task : %s - this user was removed!\n", user_get_surname(chat_remove_user_by_surname(chat, "Davidov")));//7th task

    users_list = chat_get_list_of_users(chat);

    printf("2d task : List of users:\n"); // 2d task
    for(int i = 0; i < list_getSize(users_list); i++){
        user_t * tmp  = (user_t*) list_get(users_list, i);
        printf("%s %s %i\n", user_get_name(tmp), user_get_surname(tmp), user_get_age(tmp));
    }

    message_t * msg1 = message_new("Hello!", firstUser);

    chat_add_message(chat, msg1);//8th task
    printf("8th task: added message to chat:\n%s:\t%s\n", user_get_surname(get_owner(msg1)), get_message_text(msg1));

    list_t * msgs_list = list_new();
    msgs_list = get_list_of_messages_of_one_user(chat, firstUser);//5th task
    printf("5th task : Messages of user %s\n", user_get_surname(firstUser));
    for(int i = 0; i < list_getSize(msgs_list); i++){
        message_t * tmpmsg = list_get(msgs_list, i);
        printf("%s\n", get_message_text(tmpmsg));
    }

    msgs_list = get_last_messages(chat, 1);
    printf("3d task : List of last messages(1):\n");
    for(int i = 0; i < list_getSize(msgs_list); i++){
        message_t * tmpmsg = list_get(msgs_list, i);
        printf("%s\n", get_message_text(tmpmsg));
    }

    return 0;
}
