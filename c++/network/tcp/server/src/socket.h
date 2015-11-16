#ifndef SOCKET_H
#define SOCKET_H

namespace tcp {

class Socket {
public:
    virtual ~Socket() {};
    virtual int Close(void) = 0;
    virtual int Recv(char* buf, int len, int flags = 0) = 0;
    virtual int Send(const char* buf, int len, int flags = 0) = 0;
};

} // namespace tcp

#endif /* SOCKET_H */
