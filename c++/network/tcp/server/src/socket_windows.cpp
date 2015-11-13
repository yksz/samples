#include "socket_windows.h"
#include <stdio.h>
#include <winsock2.h>

namespace tcp {

WindowsSocket::~WindowsSocket() {
    Close();
}

int WindowsSocket::Close(void) {
    int result = closesocket(m_socket);
    if (result == -1) {
        fprintf(stderr, "ERROR: close: %d\n", WSAGetLastError());
    }
    return result;
}

int WindowsSocket::Recv(char* buf, int len, int flags) {
    int result = recv(m_socket, buf, len, flags);
    if (result == -1) {
        fprintf(stderr, "ERROR: recv: %d\n", WSAGetLastError());
    }
    return result;
}

int WindowsSocket::Send(const char* buf, int len, int flags) {
    int result = send(m_socket, buf, len, flags);
    if (result == -1) {
        fprintf(stderr, "ERROR: send: %d\n", WSAGetLastError());
    }
    return result;
}

} // namespace tcp
