#include <cstdio>
#include <cstring>
#include <memory>
#include "factory.h"

static void serve(tcp::Socket& clientSock) {
    char buf[256];
    int size;
    while ((size = clientSock.Recv(buf, sizeof(buf))) > 0) {
        for (int i = 0; i < size; i++) {
            printf("%c", buf[i]);
        }
        printf("\n");
    }
}

int main(void) {
    tcp::Factory& factory = tcp::Factory::GetInstance();
    std::shared_ptr<tcp::Server> server = factory.createServer(10);
    server->RegisterService(serve);
    server->Run();
}
