#ifndef SOCKET_WINDOWS_H
#define SOCKET_WINDOWS_H

#include <winsock2.h>
#include "socket.h"

namespace server {

class WindowsSocket final : public Socket {
public:
    WindowsSocket(SOCKET socket) : m_socket(socket) {};
    ~WindowsSocket();
    WindowsSocket(const WindowsSocket&) = delete;
    WindowsSocket& operator=(const WindowsSocket&) = delete;

    int recv(char* buf, int len, int flags);
    int send(const char* buf, int len, int flags);
    int close(void);

private:
    SOCKET m_socket;
};

} // namespace server

#endif /* SCOKET_WINDOWS_H */
