#include <cstdio>
#include <cstring>
#if defined(_WIN32) || defined(_WIN64)
 #include "server_windows.h"
#else
 #include "server_unix.h"
#endif /* _WIN32 || _WIN64 */

namespace {

tcp::Server* createServer() {
#if defined(_WIN32) || defined(_WIN64)
    return new tcp::WindowsServer();
#else
    return new tcp::UnixServer();
#endif /* _WIN32 || _WIN64 */
}

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
    tcp::Server* server = createServer();
    server->RegisterService(serve);
    server->Run();
    delete server;
}
