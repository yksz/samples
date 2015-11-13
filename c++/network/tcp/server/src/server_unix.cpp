#include "server_unix.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "socket_unix.h"

namespace server {

UnixServer::UnixServer()
        : m_threadPool(new ThreadPool(10)) {
}

UnixServer::~UnixServer() {
    delete m_threadPool;
}

bool UnixServer::Run(int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return false;
    }

    int soval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1) {
        perror("setsockopt");
        return false;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) {
        perror("bind");
        return false;
    }

    if (listen(sockfd, SOMAXCONN)) {
        perror("listen");
        return false;
    }

    printf("Listening on port %d\n", port);
    for (;;) {
        acceptClient(sockfd);
    }

    shutdown(sockfd, SHUT_RDWR);
    return true;
}

bool UnixServer::acceptClient(int serverfd) {
    struct sockaddr_in clientAddr;
    socklen_t len = sizeof(clientAddr);

    int clientfd = accept(serverfd, (struct sockaddr*) &clientAddr, &len);
    if (clientfd == -1) {
        perror("accept");
        return false;
    }
    printf("%s connected\n", inet_ntoa(clientAddr.sin_addr));

    m_threadPool->Dispatch([this, clientfd]() {
        UnixSocket client(clientfd);
        m_serve(client);
    });
    return true;
}

} // namespace server
