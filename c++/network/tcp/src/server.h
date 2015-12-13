#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "socket.h"

namespace tcp {

class Server {
public:
    virtual ~Server() {};
    virtual bool Run(int port = 8080) = 0;
    void RegisterService(void (*serve)(Socket& clientSock)) {
        m_serve = serve;
    }

protected:
    void (*m_serve)(Socket& clientSock);
};

} // namespace tcp

#endif // TCP_SERVER_H
