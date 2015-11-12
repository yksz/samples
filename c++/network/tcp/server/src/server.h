#ifndef SERVER_H
#define SERVER_H

#include "socket.h"

namespace server {

class Server {
public:
    virtual ~Server() {};
    virtual bool Run(int port = 8080) = 0;
    void RegisterService(void (*serve)(Socket& client)) {
        m_serve = serve;
    }

protected:
    void (*m_serve)(Socket& client);
};

} // namespace server

#endif /* SERVER_H */
