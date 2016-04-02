#include "client.h"

void get_secret(char * output, char * address, SOCKET * socket)
{
    char buffer[BUF_SIZE];
    char request[200];
    int receive_size;
    sprintf(request, "GET %s HTTP/1.1\r\n\r\n", address);
    send(* socket, request, strlen(request), 0);
    receive_size = recv(* socket, buffer, BUF_SIZE, 0);
    char * word = "secret=";
    char * secret = strstr(buffer, word);
    int position = 0;

    while(secret[0] != '=')
        secret++;
    secret++;
    while(isalpha(secret[position]))
    {
        output[position] = secret[position];
        position++;
    }
    output[position] = '\0';
}

int get_array(int * output, int size, char * address, SOCKET * socket)
{
    char buffer[BUF_SIZE];
    char request[200];
    int receive_size;
    sprintf(request, "GET %s HTTP/1.1\r\n\r\n", address);
    send(* socket, request, strlen(request), 0);
    receive_size = recv(* socket, buffer, BUF_SIZE, 0);
    int current_number;
    char * buffer_pos = buffer;
    buffer[receive_size] = '\0';
    char * word = "Content-Length:";
    buffer_pos = strstr(buffer, word);
    int content_size;
    sscanf(buffer_pos, "Content-Length: %i", &content_size);

    while(buffer_pos[0] != '\n')
        buffer_pos++;
    //buffer_pos ++;
    char * token = strtok(buffer_pos, " ");
    int position = 0;

    while(token != NULL)
    {
        sscanf(token, "%i", &current_number);
        output[position] = current_number;
        position++;
        token = strtok(NULL, " ");
    }
    return position;
}

int sort_array(int * arr, int size)
{
    for(int i = 0; i < size; i++)
    {
        int current = i;
        while(current > 0 && arr[current] < arr[current - 1])
        {
            int tmp = arr[current];
            arr[current] = arr[current - 1];
            arr[current - 1] = tmp;
            current--;
        }
    }
}

int post_array(char * output, char * address, int * arr, int size, SOCKET * socket)
{
    int position = 0;
    int receive_size;
    char array_str[100] = "";
    for(int i = 0; i < size; i++)
    {
        char tmp[10];
        itoa(arr[i], tmp, 10);
        strcat(tmp, " ");
        strcat(array_str, tmp);
    }
    char result[200];
    sprintf(result, "result=%s", array_str);
    result[strlen(result) - 1] = '\0';
    char request[200];
    sprintf(request, "POST %s HTTP/1.1\r\nContent-length: %d\r\n\r\n%s", address, strlen(result), result);
    send(*socket, request, strlen(request), 0);
    receive_size = recv(*socket, output, BUF_SIZE, 0);
    return receive_size;

}
