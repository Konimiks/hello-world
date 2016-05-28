#include <stdio.h>
#include <stdlib.h>
#include "socket.h"

typedef struct {
    char key[256];
    char value[256];
} keyvalue_t;

typedef struct {
    char method[20];
    char uri[256];
    keyvalue_t * form;
    int formLength;

} http_request_t;

void server_info(socket_t * client);
http_request_t http_request_parse(const char * const request);
void server_sent(socket_t* clientSocket, char* text);
