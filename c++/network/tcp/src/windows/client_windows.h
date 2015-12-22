#ifndef TCP_CLIENT_WINDOWS_H
#define TCP_CLIENT_WINDOWS_H

#include <atomic>
#include <memory>
#include <winsock2.h>
#include "client.h"
#include "socket_windows.h"

namespace tcp {

class WindowsClient final : public Client {
public:
    WindowsClient() : m_connected(false) {};
    ~WindowsClient();
    WindowsClient(const WindowsClient&) = delete;
    WindowsClient& operator=(const WindowsClient&) = delete;

    bool Connect(const char* host, int port);
    bool Disconnect();
    bool IsConnected();
    int Recv(char* buf, int len, int flags);
    int Send(const char* buf, int len, int flags);
    bool RecvFully(char* buf, int len, int flags);
    bool SendFully(const char* buf, int len, int flags);

private:
    std::shared_ptr<WindowsSocket> m_socket;
    std::atomic<bool> m_connected;
};

} // namespace tcp

#endif // TCP_CLIENT_WINDOWS_H