#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

static const int DEFAULT_PORT = 8080;

static void wait_and_recv(SOCKET sock)
{
    char buf[64];
    for (;;) {
        memset(buf, 0, sizeof(buf));
        recvfrom(sock, buf, sizeof(buf), 0, NULL, NULL);
        printf("%s\n", buf);
    }
}

int main(int argc, char** argv)
{
    int port = DEFAULT_PORT;
    WSADATA data;
    SOCKET sock;
    struct sockaddr_in recv_addr;

    if (argc > 1) {
        port = atoi(argv[1]);
    }

    if (WSAStartup(MAKEWORD(2, 0), &data) != 0) {
        fprintf(stderr, "ERROR: WSAStartup: %d\n", WSAGetLastError());
        exit(1);
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "ERROR: socket: %d\n", WSAGetLastError());
        exit(1);
    }

    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(port);
    recv_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    if (bind(sock, (struct sockaddr*) &recv_addr, sizeof(recv_addr)) == SOCKET_ERROR) {
        fprintf(stderr, "ERROR: bind: %d\n", WSAGetLastError());
        exit(1);
    }

    printf("Listening on port %d\n", port);
    wait_and_recv(sock);

    closesocket(sock);
    WSACleanup();
    return 0;
}
