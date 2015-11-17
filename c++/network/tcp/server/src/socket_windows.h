#ifndef TCP_SOCKET_WINDOWS_H
#define TCP_SOCKET_WINDOWS_H

#include <winsock2.h>
#include "socket.h"

namespace tcp {

class WindowsSocket final : public Socket {
public:
    WindowsSocket(SOCKET socket) : m_socket(socket), m_closed(false) {};
    ~WindowsSocket();
    WindowsSocket(const WindowsSocket&) = delete;
    WindowsSocket& operator=(const WindowsSocket&) = delete;

    int Close(void);
    bool IsClosed(void);
    int Recv(char* buf, int len, int flags);
    int Send(const char* buf, int len, int flags);

private:
    SOCKET m_socket;
    bool m_closed;
};

} // namespace tcp

#endif /* TCP_SOCKET_WINDOWS_H */
