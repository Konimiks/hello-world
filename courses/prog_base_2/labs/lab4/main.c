#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

#include "http/http.h"
#include "worker/worker.h"
#include "socket/socket.h"
#include "read.h"

#define PORT 5000


int main()
{
    lib_init();

    worker_t* workers[MAX_WORKERS];

    for(int i = 0; i<MAX_WORKERS; i++)
    {
        workers[i] = worker_new();
    }

    read_parseWorkers(workers);

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

        server_answerRequest(request, client, workers);

        socket_free(client);
    }

    for(int i = 0; i<MAX_WORKERS; i++)
        worker_free(workers[i]);

    socket_free(server);
    lib_free();
    return 0;
}
