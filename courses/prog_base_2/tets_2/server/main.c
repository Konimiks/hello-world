#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"
#include "server.h"

int main()
{
    lib_init();
    socket_t * server = socket_new();
    socket_bind(server, 5000);
    socket_listen(server);
    char buf[10000];
    socket_t * client = NULL;
     while(1)
    {
        client = socket_accept(server);
        socket_read(client, buf, sizeof(buf));
        printf("%s",buf);
        if (strlen(buf) != 0){
        http_request_t rs;
        rs = http_request_parse(buf);
        if (strcmp(rs.method,"GET") == 0 && strcmp(rs.uri, "/info") == 0 )
        {
            server_info(client);
        }

        }
    }
    return 0;
}
