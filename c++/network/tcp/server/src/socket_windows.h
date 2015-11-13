#ifndef SOCKET_WINDOWS_H
#define SOCKET_WINDOWS_H

#include <winsock2.h>
#include "socket.h"

namespace tcp {

class WindowsSocket final : public Socket {
public:
    WindowsSocket(SOCKET socket) : m_socket(socket) {};
    ~WindowsSocket();
    WindowsSocket(const WindowsSocket&) = delete;
    WindowsSocket& operator=(const WindowsSocket&) = delete;

    int Close(void);
    int Recv(char* buf, int len, int flags);
    int Send(const char* buf, int len, int flags);

private:
    SOCKET m_socket;
};

} // namespace tcp

#endif /* SCOKET_WINDOWS_H */
