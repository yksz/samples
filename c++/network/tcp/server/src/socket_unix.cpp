#include "socket_unix.h"
#include <cstdio>
#include <sys/socket.h>

namespace server {

UnixSocket::~UnixSocket() {
    close();
}

int UnixSocket::recv(char* buf, int len, int flags) {
    int result = ::recv(m_fd, buf, len, flags);
    if (result == -1) {
        perror("recv");
    }
    return result;
}

int UnixSocket::send(const char* buf, int len, int flags) {
    int result = ::send(m_fd, buf, len, flags);
    if (result == -1) {
        perror("send");
    }
    return result;
}

int UnixSocket::close(void) {
    int result = ::shutdown(m_fd, SHUT_RDWR);
    if (result == -1) {
        perror("shutdown");
    }
    return result;
}

} // namespace server
