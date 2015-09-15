#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

static const int DEFAULT_PORT = 8080;

static void wait_and_recv(int sockfd)
{
    char buf[64];
    for (;;) {
        memset(buf, 0, sizeof(buf));
        recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
        printf("%s\n", buf);
    }
}

int main(int argc, char** argv)
{
    int port = DEFAULT_PORT;
    if (argc > 1) {
        port = atoi(argv[1]);
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in recv_addr;
    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(port);
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr*) &recv_addr, sizeof(recv_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    printf("Listening on port %d\n", port);
    wait_and_recv(sockfd);

    close(sockfd);
    return 0;
}
