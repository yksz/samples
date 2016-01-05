#include "client_windows.h"
#include <cassert>
#include <cstdio>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

namespace tcp {

static unsigned long kBlockingMode = 0;
static unsigned long kNonBlockingMode = 1;

WindowsClient::~WindowsClient() {
    Disconnect();
}

bool WindowsClient::Connect(const char* host, int port, int timeout) {
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

    ioctlsocket(sock, FIONBIO, &kNonBlockingMode);
    connect(sock, (struct sockaddr*) &serverAddr, sizeof(serverAddr));

    fd_set readfds, writefds;
    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);
    writefds = readfds;

    struct timeval connTimeout;
    connTimeout.tv_sec = timeout / 1000;
    connTimeout.tv_usec = timeout % 1000 * 1000;

    int result = select(0, &readfds, &writefds, NULL, &connTimeout);
    if (result == -1) {
        fprintf(stderr, "ERROR: select: %d\n", WSAGetLastError());
        return false;
    } else if (FD_ISSET(sock, &readfds) || FD_ISSET(sock, &writefds)) {
        m_connected = true;
        ioctlsocket(sock, FIONBIO, &kBlockingMode);
        m_socket = std::make_shared<WindowsSocket>(sock);
        m_socket->SetSocketTimeout(m_socketTimeout);
        return true;
    } else {
        fprintf(stderr, "connect: timeout\n");
        return false;
    }
}

bool WindowsClient::Disconnect() {
    if (!m_connected) {
        return true;
    }

    m_socket->Close();
    m_connected = false;
    return true;
}

bool WindowsClient::IsConnected() {
    return m_connected;
}

int WindowsClient::Recv(char* buf, int len, int flags) {
    if (!m_connected) {
        assert(0 && "Not connected");
        return -1;
    }

    return m_socket->Recv(buf, len, flags);
}

int WindowsClient::Send(const char* buf, int len, int flags) {
    if (!m_connected) {
        assert(0 && "Not connected");
        return -1;
    }

    return m_socket->Send(buf, len, flags);
}

bool WindowsClient::RecvFully(char* buf, int len, int flags) {
    if (!m_connected) {
        assert(0 && "Not connected");
        return false;
    }

    return m_socket->RecvFully(buf, len, flags);
}

bool WindowsClient::SendFully(const char* buf, int len, int flags) {
    if (!m_connected) {
        assert(0 && "Not connected");
        return false;
    }

    return m_socket->SendFully(buf, len, flags);
}

void WindowsClient::SetSocketTimeout(int timeout) {
    m_socketTimeout = timeout;
    if (m_connected) {
        m_socket->SetSocketTimeout(m_socketTimeout);
    }
}

} // namespace tcp
