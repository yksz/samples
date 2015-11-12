#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static const int kDefaultPort = 8080;

static void echo(int clientfd)
{
    char buf[256];
    int len;
    while ((len = read(clientfd, buf, sizeof(buf))) > 0) {
        if (write(clientfd, buf, len) == -1) {
            perror("write");
            return;
        }
    }
    if (len == -1) {
        perror("read");
        return;
    }
}

static void acceptClient(int serverfd)
{
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    int clientfd = accept(serverfd, (struct sockaddr*) &client_addr, &len);
    if (clientfd == -1) {
        perror("accept");
        exit(1);
    }
    printf("%s connected\n", inet_ntoa(client_addr.sin_addr));

    echo(clientfd);

    shutdown(clientfd, SHUT_RDWR);
    close(clientfd);
}

static void startServer(int port)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    int soval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, SOMAXCONN)) {
        perror("listen");
        exit(1);
    }

    printf("Listening on port %d\n", port);
    for (;;) {
        acceptClient(sockfd);
    }

    close(sockfd);
}

int main(int argc, char** argv)
{
    int port = kDefaultPort;
    if (argc > 1) {
        int num = atoi(argv[1]);
        port = num ? num : port;
    }
    startServer(port);
    return 0;
}
