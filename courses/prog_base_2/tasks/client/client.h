#ifndef MY_CLIENT
#define MY_CLIENT

#include <winsock2.h>
#define BUF_SIZE 10000

void get_secret(char * output, char * address, SOCKET * socket);
int get_array(int * output, int size, char * address, SOCKET * socket);
int sort_array(int * arr, int size);
int post_array(char * output, char * address, int * arr, int size, SOCKET * socket);

#endif // MY_CLIENT
