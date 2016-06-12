#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "server/server.h"
#include "worker/worker.h"
#include "database.h"

#define PORT 5000

int main()
{
    db_t* base = db_new("workers.db");
    lib_init();

    socket_t* server = socket_new();
    socket_bind(server, PORT);
    socket_listen(server);

    char buffer[10000];
    while(true)
    {
        puts("Waiting for client...!");
        socket_t* client = socket_accept(server);

        if(socket_read(client, buffer, sizeof(buffer)) <= 0)
        {
            socket_close(client);
            socket_free(client);
            continue;
        }

        printf("Request:\n%s\n", buffer);

        http_request_t request = http_request_parse(buffer);

        server_answerRequest(request, client, base);

        socket_free(client);
    }

    socket_free(server);
    lib_free();
    db_free(base);
    return 0;
}
