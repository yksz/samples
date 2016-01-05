#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

namespace tcp {

class Socket {
public:
    virtual ~Socket() {};
    virtual int Close() = 0;
    virtual bool IsClosed() = 0;
    virtual int Recv(char* buf, int len, int flags = 0) = 0;
    virtual int Send(const char* buf, int len, int flags = 0) = 0;
    bool RecvFully(char* buf, int len, int flags = 0);
    bool SendFully(const char* buf, int len, int flags = 0);
    virtual bool SetSocketTimeout(int timeout) = 0;
};

} // namespace tcp

#endif // TCP_SOCKET_H
