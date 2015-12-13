#include <cstdio>
#include <cstring>
#include <memory>
#include "factory.h"

static void serve(tcp::Socket& client) {
    char buf[256];
    int size;
    while ((size = client.Recv(buf, sizeof(buf))) > 0) {
        for (int i = 0; i < size; i++) {
            printf("%c", buf[i]);
        }
        printf("\n");
    }
}

int main(void) {
    tcp::Factory& factory = tcp::Factory::GetInstance();
    std::shared_ptr<tcp::Server> server = factory.createServer();
    server->RegisterService(serve);
    server->Run();
}
