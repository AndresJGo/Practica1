#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int client_len, recv_size;
    char client_message[2000];
    int number;
    char str[12];

    printf("Inicializando Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Error al inicializar Winsock. Codigo: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Winsock inicializado.\n");

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("No se pudo crear el socket: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Socket creado.\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(12500);

    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Error al asociar el socket: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Socket asociado.\n");

    listen(server_socket, 3);

    printf("Esperando al cliente\n");

    client_len = sizeof(struct sockaddr_in);
    client_socket = accept(server_socket, (struct sockaddr *)&client, &client_len);
    if (client_socket == INVALID_SOCKET)
    {
        printf("Error al aceptar conexión: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Conexión aceptada.\n");

    do
    {
        recv_size = recv(client_socket, client_message, 2000, 0);
        if (recv_size == SOCKET_ERROR)
        {
            printf("Error al recibir datos.\n");
            return 1;
        }

        client_message[recv_size] = '\0';
        number = atoi(client_message);
        printf("Numero recibido: %i\n", number);

        
        if (number != 0)
        {
            number ++;
            const char *response = strcat (itoa(number, str, 10), "\n");
            send(client_socket, response, strlen(response), 0);
        }

    } while (number != 0);

    closesocket(client_socket);
    closesocket(server_socket);

    WSACleanup();

    system("pause");

    return 0;
}
