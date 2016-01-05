#include "socket_unix.h"
#include <cassert>
#include <cstdio>
#include <sys/socket.h>
#include <sys/time.h>

namespace tcp {

UnixSocket::~UnixSocket() {
    Close();
}

int UnixSocket::Close() {
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

bool UnixSocket::IsClosed() {
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

bool UnixSocket::SetSocketTimeout(int timeout) {
    if (IsClosed()) {
        assert(0 && "Already closed");
        return -1;
    }

    struct timeval soTimeout;
    soTimeout.tv_sec = timeout / 1000;
    soTimeout.tv_usec = timeout % 1000 * 1000;

    int rcvResult = setsockopt(m_socketfd, SOL_SOCKET, SO_RCVTIMEO, &soTimeout, sizeof(soTimeout));
    if (rcvResult == -1) {
        perror("setsockopt");
        return false;
    }
    int sndResult = setsockopt(m_socketfd, SOL_SOCKET, SO_SNDTIMEO, &soTimeout, sizeof(soTimeout));
    if (sndResult == -1) {
        perror("setsockopt");
        return false;
    }
    return true;
}

} // namespace tcp
