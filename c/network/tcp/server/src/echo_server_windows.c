#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

static const int kDefaultPort = 8080;

static void echo(SOCKET clientsock)
{
    char buf[256];
    int len;

    while ((len = recv(clientsock, buf, sizeof(buf), 0)) > 0) {
        if (send(clientsock, buf, len, 0) == -1) {
            fprintf(stderr, "ERROR: send: %d\n", WSAGetLastError());
            return;
        }
    }
    if (len == -1) {
        fprintf(stderr, "ERROR: recv: %d\n", WSAGetLastError());
        return;
    }
}

static void acceptClient(SOCKET server_sock)
{
    struct sockaddr_in client_addr;
    int len;
    SOCKET clientsock;

    len = sizeof(client_addr);
    clientsock = accept(server_sock, (struct sockaddr*) &client_addr, &len);
    if (clientsock == INVALID_SOCKET) {
        fprintf(stderr, "ERROR: socket: %d\n", WSAGetLastError());
        exit(1);
    }
    printf("%s connected\n", inet_ntoa(client_addr.sin_addr));

    echo(clientsock);

    closesocket(clientsock);
}

static void startServer(int port)
{
    WSADATA data;
    SOCKET sock;
    BOOL soval;
    struct sockaddr_in server_addr;

    if (WSAStartup(MAKEWORD(2, 0), &data) != 0) {
        fprintf(stderr, "ERROR: WSAStartup: %d\n", WSAGetLastError());
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "ERROR: socket: %d\n", WSAGetLastError());
        exit(1);
    }

    soval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*) &soval, sizeof(soval));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    if (bind(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        fprintf(stderr, "ERROR: bind: %d\n", WSAGetLastError());
        exit(1);
    }

    if (listen(sock, SOMAXCONN) == SOCKET_ERROR) {
        fprintf(stderr, "ERROR: listen: %d\n", WSAGetLastError());
        exit(1);
    }

    printf("Listening on port %d\n", port);
    for (;;) {
        acceptClient(sock);
    }

    closesocket(sock);
    WSACleanup();
}

int main(int argc, char** argv)
{
    int port = kDefaultPort;
    if (argc > 1) {
        int num = atoi(argv[1]);
        port = num ? num : port;
    }
    startServer(port);
    return 0;
}
