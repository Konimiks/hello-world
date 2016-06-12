#include <stdlib.h>
#include <stdbool.h>

#include "../socket/socket.h"
#include "../worker/worker.h"
#include "server.h"
#include "../database.h"
#include "../http/http.h"

static void server_notFound(socket_t* client);
static void server_send(socket_t* client, const char* smth);

static void server_homepage(socket_t* client)
{
    char homeBuf[10224];
    char *pageText = "<html><head><title>Homepage</title></head>"
                     "<body><h1>Hi!</h1>"
                     "<p>Here you can see the list of workers.</p>"
                     "<p><a href=\"/workers/\">All workers</a></p>"
                     "<p><a href=\"/api/workers\">All workers in jSON</a></p>"
                     "</body></html>";
    sprintf(homeBuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(pageText), pageText);

    socket_write_string(client, homeBuf);
    socket_close(client);
}

static char* server_getAllWorkersJSON(db_t* base)
{
    char allOfTHem[4000] = "";
    int count = db_countWorkers(base);
    worker_t** workers[count];

    for(int i = 0; i<count; i++)
        workers[i] = worker_new();

    db_fillWorkerArr(base, workers);

    for(int i = 0; i < count; i++)
    {
        strcat(allOfTHem, worker_makeWorkerJSON(workers[i]));
    }

    for(int i = 0; i<count; i++)
        worker_free(workers[i]);

    return allOfTHem;
}

static void server_sendWorkersJSON(socket_t* client, db_t* base)
{
    char homeBuf[10224];
    char pageText[5000];
    strcpy(pageText, server_getAllWorkersJSON(base));
    sprintf(homeBuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(pageText)+1, pageText);

    socket_write_string(client, homeBuf);
    socket_close(client);
}

static char* server_getAllWorkersHTML(db_t* base)
{
    char allOfTHem[10000] = "";
    char one[1000];
    int count = db_countWorkers(base);
    worker_t** workers[count];
    for(int i = 0; i<count; i++)
        workers[i] = worker_new();

    db_fillWorkerArr(base, workers);

    for(int i = 0; i < count; i++)
    {
        sprintf(one,
                "    <p>Id: %i<br>"
                "     Name: <a href=\"/workers/%i\">%s</a><br>"
                "     <a href=\"/workers/delete/%i\">Free worker</a>"
                "     <br><br></p>",
                worker_getId(workers[i]), worker_getId(workers[i]), worker_getName(workers[i]),
                worker_getId(workers[i]));
        strcat(allOfTHem, one);
    }
    strcat(allOfTHem, "<a href=\"/workers/new/\">New worker</a>");
    for(int i = 0; i<count; i++)
        worker_free(workers[i]);
    return allOfTHem;
}

static void server_sendWorkersHTML(socket_t* client, db_t* base)
{
    char homeBuf[10224];
    char* pageText = server_getAllWorkersHTML(base);
    char request[2000] = "<head><title>Workers</title></head><h1>Workers</h1>";
    strcat(request, pageText);
    sprintf(homeBuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(request), request);

    free(pageText);
    socket_write_string(client, homeBuf);
    socket_close(client);
}

static void server_getByIdJSON(http_request_t request, socket_t* client, db_t* base)
{
    int id;
    char* getId = strpbrk(request.uri, "0123456789");
    if(getId)
    {
        id = atoi(getId);
        if(id <= 0 || !db_checkId(base, id))
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

    worker_t* worker = db_getWorkerById(base, id);
    char* workerJSON = worker_makeWorkerJSON(worker);
    if(workerJSON == NULL)
    {
        socket_write_string(client, "Wrong ID");
        return;
    }

    sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(workerJSON)+1, workerJSON);

    socket_write_string(client, buffer);
    worker_free(worker);
    socket_close(client);
}

static char* server_getWorkerHTML(worker_t* worker)
{
    char one[500] = "";
    sprintf(one,
            "     Id: %i<br>"
            "   Name: %s<br>"
            "Surname: %s<br>"
            " Salary: %i<br>"
            "   Year: %i<br><br>"
            "<p><a href=\"/workers/delete/%i\">Free</a></p>",
            worker_getId(worker), worker_getName(worker),
            worker_getSurname(worker), worker_getSalary(worker),
            worker_getYear(worker), worker_getId(worker));
    return one;
}

static void server_getByIdHTML(http_request_t request, socket_t* client, db_t* base)
{
    int id;
    char* getId = strpbrk(request.uri, "0123456789");
    if(getId)
    {
        id = atoi(getId);
        if(id<=0 || !db_checkId(base, id))
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
    worker_t* worker = db_getWorkerById(base, id);
    strcat(buffer, server_getWorkerHTML(worker));
    strcat(buffer, "</p>");

    sprintf(toSend,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(buffer), buffer);
    socket_write_string(client, toSend);
    worker_free(worker);
    socket_close(client);
}

static void server_deleteByIdHTML(http_request_t request, socket_t* client, db_t* base)
{
    int id;
    int count = db_countWorkers(base);
    char* getId = strpbrk(request.uri, "0123456789");
    if(getId)
    {
        id = atoi(getId);
        if(id<=0 || !db_checkId(base, id))
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
    worker_t* worker = db_getWorkerById(base, id);
    char toSend[2000];
    char buffer[2000];
    sprintf(buffer,
            "<head><title>Delete</title></head>"
            "<h1>Success</h1><p><a href=\"/workers/\">All workers</a></p>"
            "<p>Worker %s successfully deleted!</p>", worker_getName(worker));

    db_deleteWorker(base, id);

    sprintf(toSend,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(buffer), buffer);

    socket_write_string(client, toSend);
    socket_close(client);
}

static void server_deleteByIdJSON(http_request_t request, socket_t* client, db_t* base)
{
    int id;
    char* getId = strpbrk(request.uri, "0123456789");
    if(getId)
    {
        id = atoi(getId);
        if(id<=0 || !db_checkId(base, id))
        {
            socket_write_string(client, "{\nWrong ID\n}");
            return;
        }
    }
    else
    {
        server_notFound(client);
        return;
    }
    worker_t* worker = db_getWorkerById(base, id);
    char toSend[2000];
    char buffer[2000];
    sprintf(buffer,
            "Success!"
            "Worker %s successfully deleted!", worker_getName(worker));

    db_deleteWorker(base, id);

    sprintf(toSend,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(buffer), buffer);

    socket_write_string(client, toSend);
    socket_close(client);
}

static void server_postHTML(socket_t* client)
{
    char buffer[2000] = "";

    char toSend[2000] = "";
    strcpy(toSend,
            "<html><head><title>Post</title></head>"
            "<body><h1>New worker</h1>"
            "<form action=\"/api/workers/\" method=\"POST\">"
            "Name:<br><input type=\"text\" name=\"name\"><br>"
            "Surname:<br><input type=\"text\" name=\"surname\"><br>"
            "Salary:<br><input type=\"text\" name=\"salary\"><br>"
            "Year:<br><input type=\"text\" name=\"year\"><br>"
            "<input type=\"submit\" value=\"Send POST request\" /></form><br>"
            "<p><a href=\"/workers/\">Back to all workers</a></p>"
            "</body></html>");
    sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(toSend), toSend);

    socket_write_string(client, buffer);
    socket_close(client);
}

static void server_post(http_request_t request, socket_t* client, db_t* base)
{
    char buffer[2000] ="";

    char* name = http_request_getArg(&request, "name");
    char* surname = http_request_getArg(&request, "surname");
    char* salary = http_request_getArg(&request, "salary");
    char* year = http_request_getArg(&request, "year");

    if(strlen(name) <= 1 || strlen(surname) <= 1)
    {
        server_send(client, "Name/Surname wasn't filled in"
                            "<p><a href=\"/workers/new/\">Back to POST</a></p>");
        return;
    }

   if(isdigit(salary[0]) == 0 || isdigit(year[0])==0)
    {
        server_send(client, "Wrong data!"
                    "<p><a href=\"/workers/new/\">Back to POST</a></p>");
        return;
    }

    if(salary == " ")
        salary = "0";

    if(year == " ")
        year = "0";

    worker_t* worker = worker_new();
    worker_fill(worker, -1, name, surname, atoi(salary), atoi(year));
    db_insertWorker(base, worker);
    worker_free(worker);
    server_send(client, "Success"
                "<p><a href=\"/workers/\">All workers</a></p>");

}

static void server_send(socket_t* client, const char* smth)
{
    char homeBuf[800];
    sprintf(homeBuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %i\n"
            "\n%s", strlen(smth), smth);
    socket_write_string(client, homeBuf);
    socket_close(client);
}

static void server_notFound(socket_t* client)
{
    char homeBuf[800];
    const char * pageText = "<h1>Error</h1><h2>404</h2><p>Page Not Found!</p>";
    sprintf(homeBuf,
            "HTTP/1.1 404 \n"
            "Content-Type: text/html\n"
            "Content-Length: %i\n"
            "\n%s", strlen(pageText), pageText);
    free(pageText);
    socket_write_string(client, homeBuf);
    socket_close(client);
}

static void server_personalTask(http_request_t request, socket_t* client, db_t* base)
{
    char salaryReq[10], salaryVal[10], yearReq[10], yearVal[10], toSend[10000];
    char* str = strtok(request.uri, "?&=");
    str = strtok(NULL, "?&=");
    strcpy(salaryReq, str); // salary_m || salary_l
    str = strtok(NULL, "?&=");
    strcpy(salaryVal, str); // salary value
    str = strtok(NULL, "?&=");
    strcpy(yearReq, str);   // year_m || year_l
    str = strtok(NULL, "?&=");
    strcpy(yearVal, str);   // year value
    int count = db_countWorkers(base);

    worker_t** workers[count];
    for(int i = 0; i<count; i++)
        workers[i] = worker_new();

    str = db_personalTask(base, salaryReq, atoi(salaryVal), yearReq, atoi(yearVal), workers);

    sprintf(toSend,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %i\r\n\r\n"
            "\n%s", strlen(str)+1, str);

    for(int i = 0; i<count; i++)
        worker_free(workers[i]);

    socket_write_string(client, toSend);
    socket_close(client);
}

void server_answerRequest(http_request_t request, socket_t* client, db_t* base)
{
    puts(request.method);
    puts(request.uri);
    if(!strcmp(request.uri, "/"))
    {
        server_homepage(client);
    }
    else if(!strcmp(request.uri, "/workers") || !strcmp(request.uri, "/workers/"))
    {
        server_sendWorkersHTML(client, base);
    }
    else if(strncmp(request.uri, "/api/workers/", 13) == 0)
    {
        if(!strcmp(request.method, "POST"))
        {
            server_post(request, client, base);
        }
        else if(!strcmp(request.method, "GET"))
        {
            server_getByIdJSON(request, client, base);
        }
        else if(!strcmp(request.method, "DELETE"))
        {
            server_deleteByIdJSON(request, client, base);
        }
    }
    if(!strcmp(request.uri, "/api/workers") || !strcmp(request.uri, "/api/workers/"))
    {
        server_sendWorkersJSON(client, base);
    }
    else if(strstr(request.uri, "/api/workers/") == NULL && strstr(request.uri, "/api/workers") != NULL)
    {
        server_personalTask(request, client, base);
    }
    else if(!strcmp(request.uri, "/workers/new/") || !strcmp(request.uri, "/workers/new"))
    {
        server_postHTML(client);
    }
    else if(strncmp(request.uri, "/workers/delete/", 16) == 0)
    {
        server_deleteByIdHTML(request, client, base);
    }
    else if(strncmp(request.uri, "/workers/", 9) == 0)
    {
        server_getByIdHTML(request, client, base);
    }

    else server_notFound(client);
}

