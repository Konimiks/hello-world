#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "../http/http.h"
#include "../socket/socket.h"
#include "../worker/worker.h"

void server_answerRequest(http_request_t request, socket_t* client, worker_t** workers);

#endif // SERVER_H_INCLUDED
