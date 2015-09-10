#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

static const int PORT = 8080;
static const int QUEUE_SIZE = 5;

static void echo(SOCKET client_sock)
{
    char buf[1024];
    int len;

    while ((len = recv(client_sock, buf, sizeof(buf), 0)) > 0) {
        if (send(client_sock, buf, len, 0) == -1) {
            fprintf(stderr, "ERROR: send\n");
            exit(1);
        }
    }
    if (len == -1) {
        fprintf(stderr, "ERROR: recv\n");
        exit(1);
    }
}

static void accept_client(SOCKET server_sock)
{
    struct sockaddr_in client_addr;
    int len;
    SOCKET client_sock;

    len = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*) &client_addr, &len);
    if (client_sock == INVALID_SOCKET) {
        fprintf(stderr, "ERROR: socket: %d\n", WSAGetLastError());
        exit(1);
    }
    printf("%s connected\n", inet_ntoa(client_addr.sin_addr));

    echo(client_sock);

    closesocket(client_sock);
}

int main(int argc, char** argv)
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
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    if (bind(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        fprintf(stderr, "ERROR: bind: %d\n", WSAGetLastError());
        exit(1);
    }

    listen(sock, QUEUE_SIZE);
    printf("Listening on port %d\n", PORT);

    for (;;) {
        accept_client(sock);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
