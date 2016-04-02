#include "client.h"

int main(int argc , char *argv[])
{
    int receive_size;
    WSADATA wsa;
    SOCKET recvSocket;
    SOCKET s;
    SOCKADDR_IN recvSocketAddress;
    struct hostent * he;
    char * hostname = "pb-homework.appspot.com";
    char * var = "/var/3";
    char * current_address[100];
    struct in_addr ** addr_list;
    struct in_addr * addr;
    char ip[100];
    char buf[BUF_SIZE];

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        return 1;

    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Can`t create socket : %d" , WSAGetLastError());
    }
    if ( (he = gethostbyname( hostname ) ) == NULL)
    {
        printf("gethostbyname failed : %d" , WSAGetLastError());
        return 1;
    }

    addr_list = (struct in_addr **) he->h_addr_list;

    for(int i = 0; addr_list[i] != NULL; i++)
    {
        addr = addr_list[i];
    }

    memset(&recvSocketAddress, 0, sizeof(recvSocketAddress));
    recvSocketAddress.sin_addr = *addr;
    recvSocketAddress.sin_family = AF_INET;
    recvSocketAddress.sin_port = htons( 80 );

    recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(recvSocket == INVALID_SOCKET)
	{
		printf("ERROR: socket wasn`t received!\r\n");
		system("pause");
		return 0;
	}

    if(connect(recvSocket, (SOCKADDR*)&recvSocketAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        printf("ERROR: socket can`t connect\r\n");
        closesocket(recvSocket);
        WSACleanup();
        return 0;
    }

    strcpy(current_address, hostname);
    strcat(current_address, var);
    get_secret(buf, current_address, &recvSocket);
    printf("The secret is - %s\n", buf);

    sprintf(current_address, "%s?secret=%s", current_address, buf);
    int arr[100];
    int arr_size = get_array(arr, 100, current_address, &recvSocket);
    puts("Received array is: ");
    for(int i = 0; i < arr_size; i++)
        printf("%i ", arr[i]);

    puts("");
    sort_array(arr, arr_size);
    puts("Sorted array is: ");
    for(int i = 0; i < arr_size; i++)
        printf("%i ", arr[i]);
    puts("");
    strcpy(current_address, hostname);
    strcat(current_address, var);
    receive_size = post_array(buf, current_address, arr, arr_size, &recvSocket);
    buf[receive_size] = '\0';
    puts("\nI received: \n");
    puts(buf);

    system("pause");
    closesocket(s);

    WSACleanup();

    return 0;
}
