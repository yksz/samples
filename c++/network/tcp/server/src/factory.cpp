#include "factory.h"
#if defined(_WIN32) || defined(_WIN64)
 #include "server_windows.h"
#else
 #include "server_unix.h"
#endif /* _WIN32 || _WIN64 */

namespace tcp {

Factory& Factory::GetInstance() {
    static Factory instance;
    return instance;
}

Factory::Factory() {};

Factory::~Factory() {};

std::shared_ptr<Server> Factory::createServer() {
#if defined(_WIN32) || defined(_WIN64)
    return std::make_shared<tcp::WindowsServer>();
#else
    return std::make_shared<tcp::UnixServer>();
#endif /* _WIN32 || _WIN64 */
}

} // namespace tcp
