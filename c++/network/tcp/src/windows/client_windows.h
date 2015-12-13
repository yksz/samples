#ifndef TCP_CLIENT_WINDOWS_H
#define TCP_CLIENT_WINDOWS_H

#include <winsock2.h>
#include "client.h"

namespace tcp {

class WindowsClient final : public Client {
public:
    WindowsClient() : m_connected(false) {};
    ~WindowsClient();
    WindowsClient(const WindowsClient&) = delete;
    WindowsClient& operator=(const WindowsClient&) = delete;

    bool Connect(const char* host, int port);
    bool Disconnect();
    int Recv(char* buf, int len, int flags);
    int Send(const char* buf, int len, int flags);

private:
    SOCKET m_socket;
    bool m_connected;
};

} // namespace tcp

#endif // TCP_CLIENT_WINDOWS_H
