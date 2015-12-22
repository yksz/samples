#ifndef TCP_SERVER_UNIX_H
#define TCP_SERVER_UNIX_H

#include <cstddef>
#include "server.h"
#include "thread_pool.h"

namespace tcp {

class UnixServer final : public Server {
public:
    explicit UnixServer(size_t numThreads);
    ~UnixServer();
    UnixServer(const UnixServer&) = delete;
    UnixServer& operator=(const UnixServer&) = delete;

    bool Run(int port);

private:
    ThreadPool* m_threadPool;

    bool acceptClient(int serverfd);
};

} // namespace tcp

#endif // TCP_SERVER_UNIX_H