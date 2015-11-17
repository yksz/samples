#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

namespace tcp {

class Client {
public:
    virtual ~Client() {};
    virtual bool Connect(const char* host, int port) = 0;
    virtual bool Disconnect() = 0;
    virtual int Recv(char* buf, int len, int flags = 0) = 0;
    virtual int Send(const char* buf, int len, int flags = 0) = 0;
};

} // namespace tcp

#endif /* TCP_CLIENT_H */
