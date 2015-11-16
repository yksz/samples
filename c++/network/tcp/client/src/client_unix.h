#ifndef CLIENT_UNIX_H
#define CLIENT_UNIX_H

#include "client.h"

namespace tcp {

class UnixClient final : public Client {
public:
    UnixClient() : m_connected(false) {};
    ~UnixClient();
    UnixClient(const UnixClient&) = delete;
    UnixClient& operator=(const UnixClient&) = delete;

    bool Connect(const char* host, int port);
    bool Disconnect();
    int Recv(char* buf, int len, int flags);
    int Send(const char* buf, int len, int flags);

private:
    int m_socketfd;
    bool m_connected;
};

} // namespace tcp

#endif /* CLIENT_UNIX_H */
