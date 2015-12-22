#include "client_unix.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace tcp {

UnixClient::~UnixClient() {
    Disconnect();
}

bool UnixClient::Connect(const char* host, int port, int timeout) {
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

    int mode = 1;
    if (ioctl(sockfd, FIONBIO, &mode) == -1) {
        perror("ioctl");
        return false;
    }

    connect(sockfd, (struct sockaddr*) &serverAddr, sizeof(serverAddr));

    fd_set fdset;
    FD_ZERO(&fdset);
    FD_SET(sockfd, &fdset);

    struct timeval time;
    time.tv_sec = timeout / 1000;
    time.tv_usec = timeout % 1000 * 1000;

    int result = select(sockfd + 1, &fdset, NULL, NULL, &time);
    if (result == -1) {
        perror("select");
        return false;
    } else if (FD_ISSET(sockfd, &fdset)) {
        m_connected = true;
        m_socket = std::make_shared<UnixSocket>(sockfd);
        return true;
    } else {
        fprintf(stderr, "connect: timeout\n");
        return false;
    }
}

bool UnixClient::Disconnect() {
    if (!m_connected) {
        return true;
    }

    m_socket->Close();
    m_connected = false;
    return true;
}

bool UnixClient::IsConnected() {
    return m_connected;
}

int UnixClient::Recv(char* buf, int len, int flags) {
    if (!m_connected) {
        assert(0 && "Not connected");
        return -1;
    }

    return m_socket->Recv(buf, len, flags);
}

int UnixClient::Send(const char* buf, int len, int flags) {
    if (!m_connected) {
        assert(0 && "Not connected");
        return -1;
    }

    return m_socket->Send(buf, len, flags);
}

bool UnixClient::RecvFully(char* buf, int len, int flags) {
    if (!m_connected) {
        assert(0 && "Not connected");
        return false;
    }

    return m_socket->RecvFully(buf, len, flags);
}

bool UnixClient::SendFully(const char* buf, int len, int flags) {
    if (!m_connected) {
        assert(0 && "Not connected");
        return false;
    }

    return m_socket->SendFully(buf, len, flags);
}

} // namespace tcp
