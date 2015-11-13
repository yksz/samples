#ifndef SOCKET_UNIX_H
#define SOCKET_UNIX_H

#include "socket.h"

namespace tcp {

class UnixSocket final : public Socket {
public:
    UnixSocket(int socketfd) : m_socketfd(socketfd) {};
    ~UnixSocket();
    UnixSocket(const UnixSocket&) = delete;
    UnixSocket& operator=(const UnixSocket&) = delete;

    int Close(void);
    int Recv(char* buf, int len, int flags);
    int Send(const char* buf, int len, int flags);

private:
    int m_socketfd;
};

} // namespace tcp

#endif /* SCOKET_UNIX_H */
