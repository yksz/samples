#include "socket_windows.h"
#include <cassert>
#include <cstdio>
#include <winsock2.h>

namespace tcp {

WindowsSocket::~WindowsSocket() {
    Close();
}

int WindowsSocket::Close(void) {
    if (IsClosed()) {
        return 0;
    }

    int result = closesocket(m_socket);
    if (result == -1) {
        fprintf(stderr, "ERROR: close: %d\n", WSAGetLastError());
    }
    m_closed = true;
    return result;
}

bool WindowsSocket::IsClosed(void) {
    return m_closed;
}

int WindowsSocket::Recv(char* buf, int len, int flags) {
    if (IsClosed()) {
        assert(0 && "Already closed");
        return -1;
    }

    int result = recv(m_socket, buf, len, flags);
    if (result == -1) {
        fprintf(stderr, "ERROR: recv: %d\n", WSAGetLastError());
    }
    return result;
}

int WindowsSocket::Send(const char* buf, int len, int flags) {
    if (IsClosed()) {
        assert(0 && "Already closed");
        return -1;
    }

    int result = send(m_socket, buf, len, flags);
    if (result == -1) {
        fprintf(stderr, "ERROR: send: %d\n", WSAGetLastError());
    }
    return result;
}

} // namespace tcp
