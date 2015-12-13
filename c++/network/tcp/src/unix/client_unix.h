#ifndef TCP_CLIENT_UNIX_H
#define TCP_CLIENT_UNIX_H

#include <atomic>
#include <memory>
#include "client.h"
#include "socket_unix.h"

namespace tcp {

class UnixClient final : public Client {
public:
    UnixClient() : m_connected(false) {};
    ~UnixClient();
    UnixClient(const UnixClient&) = delete;
    UnixClient& operator=(const UnixClient&) = delete;

    bool Connect(const char* host, int port);
    bool Disconnect();
    bool IsConnected();
    int Recv(char* buf, int len, int flags);
    int Send(const char* buf, int len, int flags);
    bool RecvFully(char* buf, int len, int flags);
    bool SendFully(const char* buf, int len, int flags);

private:
    std::shared_ptr<UnixSocket> m_socket;
    std::atomic<bool> m_connected;
};

} // namespace tcp

#endif // TCP_CLIENT_UNIX_H
