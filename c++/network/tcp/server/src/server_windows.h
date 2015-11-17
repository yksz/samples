#ifndef TCP_SERVER_WINDOWS_H
#define TCP_SERVER_WINDOWS_H

#include <winsock2.h>
#include "server.h"
#include "thread_pool.h"

namespace tcp {

class WindowsServer final : public Server {
public:
    WindowsServer();
    ~WindowsServer();
    WindowsServer(const WindowsServer&) = delete;
    WindowsServer& operator=(const WindowsServer&) = delete;

    bool Run(int port);

private:
    ThreadPool* m_threadPool;

    bool acceptClient(SOCKET& serversock);
};

} // namespace tcp

#endif /* TCP_SERVER_WINDOWS_H */
