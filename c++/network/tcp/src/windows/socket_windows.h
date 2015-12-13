#ifndef TCP_SOCKET_WINDOWS_H
#define TCP_SOCKET_WINDOWS_H

#include <atomic>
#include <winsock2.h>
#include "socket.h"

namespace tcp {

class WindowsSocket final : public Socket {
public:
    explicit WindowsSocket(SOCKET socket) : m_socket(socket), m_closed(false) {};
    ~WindowsSocket();
    WindowsSocket(const WindowsSocket&) = delete;
    WindowsSocket& operator=(const WindowsSocket&) = delete;

    int Close();
    bool IsClosed();
    int Recv(char* buf, int len, int flags);
    int Send(const char* buf, int len, int flags);

private:
    SOCKET m_socket;
    std::atomic<bool> m_closed;
};

} // namespace tcp

#endif // TCP_SOCKET_WINDOWS_H
