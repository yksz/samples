#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static void sendMsg(int sockfd, char* msg) {
    if (send(sockfd, msg, strlen(msg), 0) == -1) {
        perror("write");
        return;
    }
    if (send(sockfd, "\n", 1, 0) == -1) {
        perror("write");
        return;
    }
}

static void sendMsgsTo(char* host, int port, char* msgs[], int msg_cnt)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(host);

    if (connect(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(1);
    }

    for (int i = 0; i < msg_cnt; i++) {
        sendMsg(sockfd, msgs[i]);
    }

    shutdown(sockfd, SHUT_RDWR);
}

int main(int argc, char** argv)
{
    int required_argc = 3;
    if (argc <= required_argc) {
        printf("usage: %s <host> <port> <messages>\n", argv[0]);
        exit(1);
    }
    char* host = argv[1];
    int port = atoi(argv[2]);
    int msg_cnt = argc - required_argc;
    char* msgs[msg_cnt];
    for (int i = 0; i < msg_cnt; i++) {
        msgs[i] = argv[required_argc + i];
    }
    sendMsgsTo(host, port, msgs, msg_cnt);
    return 0;
}
