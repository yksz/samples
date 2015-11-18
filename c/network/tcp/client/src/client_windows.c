#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

static void sendMsg(SOCKET* sock, char* msg) {
    if (send(*sock, msg, strlen(msg), 0) == -1) {
        fprintf(stderr, "ERROR: send: %d\n", WSAGetLastError());
        return;
    }
    if (send(*sock, "\n", 1, 0) == -1) {
        fprintf(stderr, "ERROR: send: %d\n", WSAGetLastError());
        return;
    }
}

static void sendMsgTo(char* host, int port, char* msg)
{
    WSADATA data;
    SOCKET sock;
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

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.S_un.S_addr = inet_addr(host);

    if (connect(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        fprintf(stderr, "ERROR: connect: %d\n", WSAGetLastError());
        exit(1);
    }

    sendMsg(&sock, msg);

    closesocket(sock);
    WSACleanup();
}

int main(int argc, char** argv)
{
    char* host;
    int port;
    char* msg;

    if (argc <= 3) {
        printf("usage: %s <host> <port> <message>\n", argv[0]);
        exit(1);
    }
    host = argv[1];
    port = atoi(argv[2]);
    msg = argv[3];
    sendMsgTo(host, port, msg);
    return 0;
}
