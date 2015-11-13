#include "socket_unix.h"
#include <cstdio>
#include <sys/socket.h>

namespace tcp {

UnixSocket::~UnixSocket() {
    Close();
}

int UnixSocket::Close(void) {
    int result = shutdown(m_socketfd, SHUT_RDWR);
    if (result == -1) {
        perror("shutdown");
    }
    return result;
}

int UnixSocket::Recv(char* buf, int len, int flags) {
    int result = recv(m_socketfd, buf, len, flags);
    if (result == -1) {
        perror("recv");
    }
    return result;
}

int UnixSocket::Send(const char* buf, int len, int flags) {
    int result = send(m_socketfd, buf, len, flags);
    if (result == -1) {
        perror("send");
    }
    return result;
}

} // namespace tcp
