#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static void sendMsgTo(char* host, int port, char* msg)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in send_addr;
    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(port);
    send_addr.sin_addr.s_addr = inet_addr(host);

    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr*) &send_addr, sizeof(send_addr));

    shutdown(sockfd, SHUT_RDWR);
}

int main(int argc, char** argv)
{
    if (argc <= 3) {
        printf("usage: %s <host> <port> <message>\n", argv[0]);
        exit(1);
    }
    char* host = argv[1];
    int port = atoi(argv[2]);
    char* msg = argv[3];
    sendMsgTo(host, port, msg);
    return 0;
}
