#ifndef SOCKET_UNIX_H
#define SOCKET_UNIX_H

#include "socket.h"

namespace tcp {

class UnixSocket final : public Socket {
public:
    UnixSocket(int fd) : m_fd(fd) {};
    ~UnixSocket();
    UnixSocket(const UnixSocket&) = delete;
    UnixSocket& operator=(const UnixSocket&) = delete;

    int recv(char* buf, int len, int flags);
    int send(const char* buf, int len, int flags);
    int close(void);

private:
    int m_fd;
};

} // namespace tcp

#endif /* SCOKET_UNIX_H */
