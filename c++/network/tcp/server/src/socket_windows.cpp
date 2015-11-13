#include "socket_windows.h"
#include <stdio.h>
#include <winsock2.h>

namespace tcp {

WindowsSocket::~WindowsSocket() {
    close();
}

int WindowsSocket::recv(char* buf, int len, int flags) {
    int result = ::recv(m_socket, buf, len, flags);
    if (result == -1) {
        fprintf(stderr, "ERROR: recv: %d\n", WSAGetLastError());
    }
    return result;
}

int WindowsSocket::send(const char* buf, int len, int flags) {
    int result = ::send(m_socket, buf, len, flags);
    if (result == -1) {
        fprintf(stderr, "ERROR: send: %d\n", WSAGetLastError());
    }
    return result;
}

int WindowsSocket::close(void) {
    int result = ::closesocket(m_socket);
    if (result == -1) {
        fprintf(stderr, "ERROR: close: %d\n", WSAGetLastError());
    }
    return result;
}

} // namespace tcp
