#include <cstdio>
#include <cstring>
#include "factory.h"

namespace {

void serve(tcp::Socket& client) {
    char buf[256];
    int size;
    while ((size = client.Recv(buf, sizeof(buf))) > 0) {
        for (int i = 0; i < size; i++) {
            printf("%c", buf[i]);
        }
    }
}

} // unnamed namespace

int main(void) {
    tcp::Factory& factory = tcp::Factory::GetInstance();
    tcp::Server* server = factory.createServer();
    server->RegisterService(serve);
    server->Run();
    delete server;
}
