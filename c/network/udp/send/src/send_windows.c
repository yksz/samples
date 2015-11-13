#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

static void sendMsgTo(char* host, int port, char* msg)
{
    WSADATA data;
    SOCKET sock;
    struct sockaddr_in send_addr;

    if (WSAStartup(MAKEWORD(2, 0), &data) != 0) {
        fprintf(stderr, "ERROR: WSAStartup: %d\n", WSAGetLastError());
        exit(1);
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "ERROR: socket: %d\n", WSAGetLastError());
        exit(1);
    }

    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(port);
    send_addr.sin_addr.S_un.S_addr = inet_addr(host);

    sendto(sock, msg, strlen(msg), 0, (struct sockaddr*) &send_addr, sizeof(send_addr));

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
