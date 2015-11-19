#include "client_windows.h"
#include <cassert>
#include <cstdio>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

namespace tcp {

WindowsClient::~WindowsClient() {
    Disconnect();
}

bool WindowsClient::Connect(const char* host, int port) {
    if (m_connected) {
        return true;
    }

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

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.S_un.S_addr = inet_addr(host);

    if (connect(sock, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        fprintf(stderr, "ERROR: connect: %d\n", WSAGetLastError());
        return false;
    }

    m_connected = true;
    m_socket = sock;
    return true;
}

bool WindowsClient::Disconnect() {
    if (!m_connected) {
        return true;
    }

    int result = closesocket(m_socket);
    if (result == -1) {
        fprintf(stderr, "ERROR: close: %d\n", WSAGetLastError());
        return false;
    }
    WSACleanup();
    m_connected = false;
    return true;
}

int WindowsClient::Recv(char* buf, int len, int flags) {
    if (!m_connected) {
        assert(0 && "Not connected");
        return -1;
    }

    int result = recv(m_socket, buf, len, flags);
    if (result == -1) {
        fprintf(stderr, "ERROR: recv: %d\n", WSAGetLastError());
    }
    return result;
}

int WindowsClient::Send(const char* buf, int len, int flags) {
    if (!m_connected) {
        assert(0 && "Not connected");
        return -1;
    }

    int result = send(m_socket, buf, len, flags);
    if (result == -1) {
        fprintf(stderr, "ERROR: send: %d\n", WSAGetLastError());
    }
    return result;
}

} // namespace tcp
