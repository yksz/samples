#include <cstdio>
#include <cstdlib>
#include <cstring>
#if defined(_WIN32) || defined(_WIN64)
 #include "client_windows.h"
#else
 #include "client_unix.h"
#endif /* _WIN32 || _WIN64 */

namespace {

tcp::Client* createClient() {
#if defined(_WIN32) || defined(_WIN64)
    return new tcp::WindowsClient();
#else
    return new tcp::UnixClient();
#endif /* _WIN32 || _WIN64 */
}

} // unnamed namespace

int main(int argc, char** argv) {
    if (argc <= 3) {
        printf("usage: %s <host> <port> <message>\n", argv[0]);
        exit(1);
    }
    char* host = argv[1];
    int port = atoi(argv[2]);
    char* msg = argv[3];

    tcp::Client* client = createClient();
    client->Connect(host, port);
    client->Send(msg, strlen(msg));
    client->Send("\n", 1);
    client->Close();
    delete client;
}
