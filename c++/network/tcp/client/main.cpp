#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include "factory.h"

int main(int argc, char** argv) {
    if (argc <= 3) {
        printf("usage: %s <host> <port> <message>\n", argv[0]);
        exit(1);
    }
    char* host = argv[1];
    int port = atoi(argv[2]);
    char* msg = argv[3];

    tcp::Factory& factory = tcp::Factory::GetInstance();
    std::shared_ptr<tcp::Client> client = factory.createClient();
    client->SetSocketTimeout(10000);
    if (client->Connect(host, port, 5000)) {
        client->Send(msg, strlen(msg));
        client->Send("\n", 1);
        client->Disconnect();
    }
}
