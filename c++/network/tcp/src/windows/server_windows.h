#ifndef TCP_SERVER_WINDOWS_H
#define TCP_SERVER_WINDOWS_H

#include <cstddef>
#include <winsock2.h>
#include "server.h"
#include "thread_pool.h"

namespace tcp {

class WindowsServer final : public Server {
public:
    explicit WindowsServer(size_t numThreads);
    ~WindowsServer();
    WindowsServer(const WindowsServer&) = delete;
    WindowsServer& operator=(const WindowsServer&) = delete;

    bool Run(int port);

private:
    ThreadPool* m_threadPool;

    bool acceptClient(SOCKET& serversock);
};

} // namespace tcp

#endif // TCP_SERVER_WINDOWS_H
