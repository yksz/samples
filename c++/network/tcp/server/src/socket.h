#ifndef SOCKET_H
#define SOCKET_H

namespace server {

class Socket {
public:
    virtual ~Socket() {};
    virtual int recv(char* buf, int len, int flags = 0) = 0;
    virtual int send(const char* buf, int len, int flags = 0) = 0;
    virtual int close() = 0;
};

} // namespace server

#endif /* SCOKET_H */
