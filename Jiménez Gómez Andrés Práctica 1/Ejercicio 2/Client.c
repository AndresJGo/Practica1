#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[]) {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char *message, server_reply[2000];
    int recv_size;

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Error: No se pudo inicializar Winsock. Código de error: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Winsock inicializado.\n");

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Error: No se pudo crear el socket. Código de error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Socket creado.\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(12500);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Error: No se pudo conectar al servidor. Código de error: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("Conectado al servidor.\n");

    message = "Hola\n";
    if (send(sock, message, strlen(message), 0) < 0) {
        printf("Error: No se pudo enviar el mensaje.\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("Mensaje enviado.\n");

    if ((recv_size = recv(sock, server_reply, 2000, 0)) == SOCKET_ERROR) {
        printf("Error: No se pudo recibir la respuesta.\n");
    } else {
        server_reply[recv_size] = '\0';
        printf("Respuesta recibida: %s\n", server_reply);
    }

    closesocket(sock);
    WSACleanup();

    system("pause");

    return 0;
}