#ifndef SERVER_UNIX_H
#define SERVER_UNIX_H

#include "server.h"
#include "thread_pool.h"

namespace tcp {

class UnixServer final : public Server {
public:
    UnixServer();
    ~UnixServer();
    UnixServer(const UnixServer&) = delete;
    UnixServer& operator=(const UnixServer&) = delete;

    bool Run(int port);

private:
    ThreadPool* m_threadPool;

    bool acceptClient(int serverfd);
};

} // namespace tcp

#endif /* SERVER_UNIX_H */
