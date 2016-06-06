#include <stdlib.h>

#include "../socket/socket.h"
#include "../worker/worker.h"
#include "server.h"
#include "../http/http.h"

static void server_notFound(socket_t* client);
static void server_send(socket_t* client, const char* smth);

static void server_homepage(socket_t* client)
{
    char buf[10224];
    char *pageText = "<html><head><title>Homepage</title></head>"
                     "<body><h1>Hi!</h1>"
                     "<p>Here you can see info about workers.</p>"
                     "<p><a href=\"/workers/\">All workers</a></p>"
                     "<p><a href=\"/api/workers\">All workers in jSON</a></p>"
                     "</body></html>";
    sprintf(buf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(pageText), pageText);

    socket_write_string(client, buf);
    socket_close(client);
}

static char* server_getAllWorkersJSON(worker_t** workers)
{
    int count = worker_workersCount(workers);
    char all[2000] = "";
    for(int i = 0; i < MAX_WORKERS; i++)
    {
        if(worker_getId(workers[i]) != -1)
            strcat(all, worker_makeWorkerJSON(workers[i]));
    }
    //puts(all);
    return all;
}

static void server_sendWorkersJSON(socket_t* client, worker_t** workers)
{
    char buf[10224];
    char pageText[1000];
    strcpy(pageText, server_getAllWorkersJSON(workers));
    sprintf(buf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(pageText)+1, pageText);

    socket_write_string(client, buf);
    socket_close(client);
}

static char* server_getAllWorkersHTML(worker_t** workers)
{
    char all[10000] = "";
    char one[1000];
    for(int i = 0; i < MAX_WORKERS; i++)
    {
        if(worker_getId(workers[i]) != -1)
        {
            sprintf(one,
                    "     <p>Id: %i<br>"
                    "     Name: <a href=\"/workers/%i\">%s</a><br>"
                    "     <a href=\"/workers/delete/%i\">Free worker</a>"
                    "     <br><br></p>",
                    i, worker_getId(workers[i]), worker_getName(workers[i]),
                    worker_getId(workers[i]));
            strcat(all, one);
                //puts(allOfTHem);
        }
    }
    strcat(all, "<a href=\"/workers/new/\">New worker</a>");
    return all;
}

static void server_sendWorkersHTML(socket_t* client, worker_t** workers)
{
    char buf[10224];
    char* pageText = server_getAllWorkersHTML(workers);
    char request[2000] = "<head><title>Workers</title></head><h1>Workers</h1>";
    strcat(request, pageText);
    sprintf(buf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(request), request);

    free(pageText);
    socket_write_string(client, buf);
    socket_close(client);
}

static void server_getByIdJSON(http_request_t request, socket_t* client, worker_t** workers)
{
    int id;
    char* getId = strpbrk(request.uri, "0123456");
    if(getId)
    {
        id = atoi(getId);
        if(id>6 || id<0 || worker_getId(workers[id]) == -1)
        {
            socket_write_string(client, "Wrong ID");
            return;
        }
    }
    else
    {
        server_notFound(client);
        return;
    }
    char buffer[1000] = "";
    char* worker = worker_makeWorkerJSON(workers[id]);

    sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(worker)+1, worker);

    socket_write_string(client, buffer);
    socket_close(client);
}

static char* server_getWorkerHTML(worker_t* worker)
{
    char one[500] = "";
    sprintf(one,
            "        Id: %i<br>"
            "      Name: %s<br>"
            "   Surname: %s<br>"
            "Birth date: %s<br>"
            "Experience: %i<br>"
            "    Rating: %.2f<br><br>"
            "<p><a href=\"/workers/delete/%i\">Delete</a></p>",
            worker_getId(worker), worker_getName(worker),
            worker_getSurname(worker), worker_getBirthdate(worker),
            worker_getExp(worker), worker_getRate(worker),
            worker_getId(worker));
    return one;
}

static void server_getByIdHTML(http_request_t request, socket_t* client, worker_t** workers)
{
    int id;
    char* getId = strpbrk(request.uri, "0123456");
    if(getId)
    {
        id = atoi(getId);
        if(id<0 || id>6 || worker_getId(workers[id]) == -1)
        {
            socket_write_string(client, "<h1>Wrong ID</h1><p><a href=\"/workers/\">All workers</a></p>");
            return;
        }
    }
    else
    {
        server_notFound(client);
        return;
    }
    char toSend[2000];
    char buffer[2000] = "<head><title>Worker</title></head><h1>Worker</h1><p><a href=\"/workers/\">All workers</a></p><p>";
    strcat(buffer, server_getWorkerHTML(workers[id]));
    strcat(buffer, "</p>");

    sprintf(toSend,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(buffer), buffer);
    socket_write_string(client, toSend);
    socket_close(client);
}

static void server_deleteByIdHTML(http_request_t request, socket_t* client, worker_t** workers)
{
    int id;
    char* getId = strpbrk(request.uri, "0123456");
    if(getId)
    {
        id = atoi(getId);
        if(id<0 || id>6 || worker_getId(workers[id]) == -1)
        {
            socket_write_string(client, "<h1>Wrong ID</h1><p><a href=\"/workers/\">All workers</a></p>");
            return;
        }
    }
    else
    {
        server_notFound(client);
        return;
    }
    char toSend[2000];
    char buffer[2000];
    sprintf(buffer,
            "<head><title>Delete</title></head>"
            "<h1>Success</h1><p><a href=\"/workers/\">All workers</a></p>"
            "<p>Worker %s successfully deleted!</p>", worker_getName(workers[id]));

    //workers[id] = worker_new();
    worker_fill(workers[id], -1, "qqq", "qqq", "1111-11-11", 0, 0);

    sprintf(toSend,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(buffer), buffer);

    socket_write_string(client, toSend);
    socket_close(client);
}

static void server_deleteByIdJSON(http_request_t request, socket_t* client, worker_t** workers)
{
    int id;
    char* getId = strpbrk(request.uri, "0123456");
    if(getId)
    {
        id = atoi(getId);
        if(id<0 || id>6 || worker_getId(workers[id]) == -1)
        {
            socket_write_string(client, "<h1>Wrong ID</h1><p><a href=\"/workers/\">All workers</a></p>");
            return;
        }
    }
    else
    {
        server_notFound(client);
        return;
    }
    char toSend[2000];
    char buffer[2000];
    sprintf(buffer,
            "Success!"
            "Worker %s successfully deleted!", worker_getName(workers[id]));

    workers[id] = worker_new();

    sprintf(toSend,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(buffer), buffer);

    socket_write_string(client, toSend);
    socket_close(client);
}

static void server_postHTML(socket_t* client, worker_t** workers)
{
    char buffer[2000] = "";
    int id = 0;
    int count = worker_workersCount(workers);

    if(count >= MAX_WORKERS)
    {
        char fail[] = "<html><head><title>Failure</head></title>"
                     "<body><h1>Failure</h1>"
                     "<p>List is full!</p>"
                     "<p><a href=\"/workers/\">Back to all workers</a></p>"
                     "</body></html>";
        sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(fail), fail);

        socket_write_string(client, buffer);
        socket_close(client);
        return;
    }

    for(int i = 0; i<MAX_WORKERS; i++, id++)
    {
        if(worker_getId(workers[i]) == -1)
            break;
    }

    char toSend[2000] = "";
    sprintf(toSend,
            "<html><head><title>Post</title></head>"
            "<body><h1>New worker</h1>"
            "<form action=\"/api/workers/%i\" method=\"POST\">"
            "Name:<br><input type=\"text\" name=\"name\"><br>"
            "Surname:<br><input type=\"text\" name=\"surname\"><br>"
            "Birthday:<br><input type=\"text\" name=\"birthdate\"><br>"
            "Experience:<br><input type=\"text\" name=\"experience\"><br>"
            "Rating:<br><input type=\"text\" name=\"rating\"><br>"
            "<input type=\"submit\" value=\"Send POST request\" /></form><br>"
            "<p><a href=\"/workers/\">Back to all workers</a></p>"
            "</body></html>", id);
    sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(toSend), toSend);

    socket_write_string(client, buffer);
    socket_close(client);
}

static void server_post(http_request_t request, socket_t* client, worker_t** workers)
{
    int id = 0;
    int count = worker_workersCount(workers);
    char buffer[2000] ="";
    char* str;
    char* name = http_request_getArg(&request, "name");
    char* surname = http_request_getArg(&request, "surname");
    char* birthdate = http_request_getArg(&request, "birthdate");
    char* experience = http_request_getArg(&request, "experience");
    char* rating = http_request_getArg(&request, "rating");

    if(strlen(name) <= 1 || strlen(surname) <= 1 || strlen(birthdate) <= 1)
    {
        server_send(client, "Name/Surname/Birthday wasn't filled in"
                            "<p><a href=\"/workers/new/\">Back to POST</a></p>");
        return;
    }

    str = birthdate;

   if(strlen(birthdate) > 10 || str[4] != '-' || str[7] != '-' || isdigit(birthdate[0])==0 || isdigit(experience[0]) == 0 || isdigit(rating[0])==0)
    {
        server_send(client, "Wrong input!"
                    "<p><a href=\"/workers/new/\">Back to POST</a></p>");
        return;
    }

    if(experience == " ")
        experience = "0";

    if(rating == " ")
        rating = "0.0";

    if(count >= MAX_WORKERS)
    {
        char fail[] = "Limit of workers!";
        sprintf(buffer,
            "HTTP/1.1 404 \n"
            "Content-Type: text\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(fail), fail);

        socket_write_string(client, buffer);
        socket_close(client);
        return;
    }

    for(int i = 0; i<MAX_WORKERS; i++, id++)
    {
        if(worker_getId(workers[i]) == -1)
            break;
    }

    int exp = atoi(experience);
    double rate = atof(rating);

    worker_fill(workers[id], id, name, surname, birthdate, exp, rate);
    server_send(client, "Success!!!"
                "<p><a href=\"/workers/\">All workers</a></p>");

}

static void server_send(socket_t* client, const char* smth)
{
    char buf[800];
    sprintf(buf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\n"
            "\n%s", strlen(smth), smth);
    socket_write_string(client, buf);
    socket_close(client);
}

static void server_notFound(socket_t* client)
{
    char buf[800];
    const char * pageText = "<h1>Error</h1><p><h1>404</h1><p>Page Not Found!</p></p>";
    sprintf(buf,
            "HTTP/1.1 404 \n"
            "Content-Type: text/html\n"
            "Content-Length: %i\n"
            "\n%s", strlen(pageText), pageText);
    free(pageText);
    socket_write_string(client, buf);
    socket_close(client);
}

void server_answerRequest(http_request_t request, socket_t* client, worker_t** workers)
{
    puts(request.method);
    puts(request.uri);
    if(!strcmp(request.uri, "/"))
    {
        server_homepage(client);
    }
    else if(!strcmp(request.uri, "/workers") || !strcmp(request.uri, "/workers/"))
    {
        server_sendWorkersHTML(client, workers);
    }
    else if(strncmp(request.uri, "/api/workers/", 13) == 0)
    {
        if(!strcmp(request.method, "GET"))
        {
            server_getByIdJSON(request, client, workers);
        }
        else if(!strcmp(request.method, "DELETE"))
        {
            server_deleteByIdJSON(request, client, workers);
        }
        else if(!strcmp(request.method, "POST"))
        {
            server_post(request, client, workers);
        }
    }
    else if(!strcmp(request.uri, "/api/workers"))
    {
        server_sendWorkersJSON(client, workers);
    }
    else if(!strcmp(request.uri, "/workers/new/") || !strcmp(request.uri, "/workers/new"))
    {
        server_postHTML(client, workers);
    }
    else if(strncmp(request.uri, "/workers/delete/", 16) == 0)
    {
        server_deleteByIdHTML(request, client, workers);
    }
    else if(strncmp(request.uri, "/workers/", 9) == 0)
    {
        server_getByIdHTML(request, client, workers);
    }

    else server_notFound(client);
}

