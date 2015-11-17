#include "client_unix.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace tcp {

UnixClient::~UnixClient() {
    Disconnect();
}

bool UnixClient::Connect(const char* host, int port) {
    if (m_connected) {
        return true;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return false;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(host);

    if (connect(sockfd, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0) {
        perror("connect");
        return false;
    }

    m_connected = true;
    m_socketfd = sockfd;
    return true;
}

bool UnixClient::Disconnect(void) {
    if (!m_connected) {
        return true;
    }

    int result = shutdown(m_socketfd, SHUT_RDWR);
    if (result == -1) {
        perror("shutdown");
        return false;
    }
    m_connected = false;
    return true;
}

int UnixClient::Recv(char* buf, int len, int flags) {
    if (!m_connected) {
        assert(0 && "Not connected");
        return -1;
    }

    int result = recv(m_socketfd, buf, len, flags);
    if (result == -1) {
        perror("recv");
    }
    return result;
}

int UnixClient::Send(const char* buf, int len, int flags) {
    if (!m_connected) {
        assert(0 && "Not connected");
        return -1;
    }

    int result = send(m_socketfd, buf, len, flags);
    if (result == -1) {
        perror("send");
    }
    return result;
}

} // namespace tcp
