#include <cstdio>
#if defined(_WIN32) || defined(_WIN64)
 #include "server_windows.h"
#else
 #include "server_unix.h"
#endif /* _WIN32 || _WIN64 */

namespace {

void serve(server::Socket& client) {
    char buf[256];
    int len;
    while ((len = client.recv(buf, sizeof(buf))) > 0) {
        printf("%s", buf);
    }
}

} // unnamed namespace

int main(void) {
    server::Server* server;

#if defined(_WIN32) || defined(_WIN64)
    server::WindowsServer windowsServer;
    server = &windowsServer;
#else
    server::UnixServer unixServer;
    server = &unixServer;
#endif /* _WIN32 || _WIN64 */

    server->RegisterService(serve);
    server->Run();
}
