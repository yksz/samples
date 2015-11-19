#ifndef TCP_SOCKET_UNIX_H
#define TCP_SOCKET_UNIX_H

#include "socket.h"

namespace tcp {

class UnixSocket final : public Socket {
public:
    UnixSocket(int socketfd) : m_socketfd(socketfd), m_closed(false) {};
    ~UnixSocket();
    UnixSocket(const UnixSocket&) = delete;
    UnixSocket& operator=(const UnixSocket&) = delete;

    int Close();
    bool IsClosed();
    int Recv(char* buf, int len, int flags);
    int Send(const char* buf, int len, int flags);

private:
    int m_socketfd;
    bool m_closed;
};

} // namespace tcp

#endif /* TCP_SOCKET_UNIX_H */
