#include "factory.h"
#if defined(_WIN32) || defined(_WIN64)
 #include "client_windows.h"
 #include "server_windows.h"
#else
 #include "client_unix.h"
 #include "server_unix.h"
#endif // _WIN32 || _WIN64

namespace tcp {

Factory& Factory::GetInstance() {
    static Factory instance;
    return instance;
}

std::shared_ptr<Client> Factory::createClient() {
#if defined(_WIN32) || defined(_WIN64)
    return std::make_shared<WindowsClient>();
#else
    return std::make_shared<UnixClient>();
#endif // _WIN32 || _WIN64
}

std::shared_ptr<Server> Factory::createServer(size_t numThreads) {
#if defined(_WIN32) || defined(_WIN64)
    return std::make_shared<WindowsServer>(numThreads);
#else
    return std::make_shared<UnixServer>(numThreads);
#endif // _WIN32 || _WIN64
}

} // namespace tcp