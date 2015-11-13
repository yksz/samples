#ifndef SERVER_WINDOWS_H
#define SERVER_WINDOWS_H

#include <winsock2.h>
#include "server.h"
#include "thread_pool.h"

namespace server {

class WindowsServer final : public Server {
public:
    WindowsServer();
    ~WindowsServer();
    WindowsServer(const WindowsServer&) = delete;
    WindowsServer& operator=(const WindowsServer&) = delete;

    bool Run(int port);

private:
    ThreadPool* m_threadPool;

    bool acceptClient(SOCKET serversock);
};

} // namespace server

#endif /* SERVER_WINDOWS_H */
