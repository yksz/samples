#include "server_windows.h"
#include <cstdio>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

namespace server {

WindowsServer::WindowsServer()
        : m_threadPool(new ThreadPool(10)) {
}

WindowsServer::~WindowsServer() {
    delete m_threadPool;
}

bool WindowsServer::Run(int port) {
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 0), &data) != 0) {
        fprintf(stderr, "ERROR: WSAStartup: %d\n", WSAGetLastError());
        return false;
    }

    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        fprintf(stderr, "ERROR: socket: %d\n", WSAGetLastError());
        return false;
    }

    BOOL soval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*) &soval, sizeof(soval));

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    if (bind(sock, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        fprintf(stderr, "ERROR: bind: %d\n", WSAGetLastError());
        return false;
    }

    if (listen(sock, SOMAXCONN) == SOCKET_ERROR) {
        fprintf(stderr, "ERROR: listen: %d\n", WSAGetLastError());
        return false;
    }

    printf("Listening on port %d\n", port);
    for (;;) {
        acceptClient(sock);
    }

    closesocket(sock);
    WSACleanup();
    return true;
}

bool acceptClient(SOCKET server_sock)
{
    struct sockaddr_in clientAddr;
    int len;
    SOCKET clientsock;

    len = sizeof(clientAddr);
    clientsock = accept(server_sock, (struct sockaddr*) &clientAddr, &len);
    if (clientsock == INVALID_SOCKET) {
        fprintf(stderr, "ERROR: socket: %d\n", WSAGetLastError());
        return false;
    }
    printf("%s connected\n", inet_ntoa(clientAddr.sin_addr));

    m_threadPool->Dispatch([this, clientsock]() {
        WindowsSocket client(clientsock);
        m_serve(client);
    });
    return true;
}

} // namespace server
