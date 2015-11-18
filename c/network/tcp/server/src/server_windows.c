#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

static const int kDefaultPort = 8080;

static void recvAndPrint(SOCKET* client_sock)
{
    char buf[256];
    int size;
    int i;

    while ((size = recv(*client_sock, buf, sizeof(buf), 0)) > 0) {
        for (i = 0; i < size; i++) {
            printf("%c", buf[i]);
        }
    }
    if (size == -1) {
        fprintf(stderr, "ERROR: recv: %d\n", WSAGetLastError());
        return;
    }
}

static void acceptClient(SOCKET* server_sock)
{
    struct sockaddr_in client_addr;
    int len;
    SOCKET client_sock;

    len = sizeof(client_addr);
    client_sock = accept(*server_sock, (struct sockaddr*) &client_addr, &len);
    if (client_sock == INVALID_SOCKET) {
        fprintf(stderr, "ERROR: socket: %d\n", WSAGetLastError());
        exit(1);
    }
    printf("%s connected\n", inet_ntoa(client_addr.sin_addr));

    recvAndPrint(&client_sock);

    closesocket(client_sock);
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
        acceptClient(&sock);
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
