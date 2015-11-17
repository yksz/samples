#include "socket_unix.h"
#include <cassert>
#include <cstdio>
#include <sys/socket.h>

namespace tcp {

UnixSocket::~UnixSocket() {
    Close();
}

int UnixSocket::Close(void) {
    if (IsClosed()) {
        return 0;
    }

    int result = shutdown(m_socketfd, SHUT_RDWR);
    if (result == -1) {
        perror("shutdown");
    }
    m_closed = true;
    return result;
}

bool UnixSocket::IsClosed(void) {
    return m_closed;
}

int UnixSocket::Recv(char* buf, int len, int flags) {
    if (IsClosed()) {
        assert(0 && "Already closed");
        return -1;
    }

    int result = recv(m_socketfd, buf, len, flags);
    if (result == -1) {
        perror("recv");
    }
    return result;
}

int UnixSocket::Send(const char* buf, int len, int flags) {
    if (IsClosed()) {
        assert(0 && "Already closed");
        return -1;
    }

    int result = send(m_socketfd, buf, len, flags);
    if (result == -1) {
        perror("send");
    }
    return result;
}

} // namespace tcp
