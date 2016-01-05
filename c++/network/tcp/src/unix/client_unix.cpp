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

static const int kBlockingMode = 0;
static const int kNonBlockingMode = 1;

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

    ioctl(sockfd, FIONBIO, &kNonBlockingMode);
    connect(sockfd, (struct sockaddr*) &serverAddr, sizeof(serverAddr));

    fd_set readfds, writefds;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);
    writefds = readfds;

    struct timeval connTimeout;
    connTimeout.tv_sec = timeout / 1000;
    connTimeout.tv_usec = timeout % 1000 * 1000;

    int result = select(sockfd + 1, &readfds, &writefds, NULL, &connTimeout);
    if (result == -1) {
        perror("select");
        return false;
    } else if (FD_ISSET(sockfd, &readfds) || FD_ISSET(sockfd, &writefds)) {
        m_connected = true;
        ioctl(sockfd, FIONBIO, &kBlockingMode);
        m_socket = std::make_shared<UnixSocket>(sockfd);
        m_socket->SetSocketTimeout(m_socketTimeout);
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

void UnixClient::SetSocketTimeout(int timeout) {
    m_socketTimeout = timeout;
    if (m_connected) {
        m_socket->SetSocketTimeout(m_socketTimeout);
    }
}

} // namespace tcp
