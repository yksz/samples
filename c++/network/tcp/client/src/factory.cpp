#include "factory.h"
#if defined(_WIN32) || defined(_WIN64)
 #include "client_windows.h"
#else
 #include "client_unix.h"
#endif /* _WIN32 || _WIN64 */

namespace tcp {

Factory& Factory::GetInstance() {
    static Factory instance;
    return instance;
}

Factory::Factory() {};

Factory::~Factory() {};

std::shared_ptr<Client> Factory::createClient() {
#if defined(_WIN32) || defined(_WIN64)
    return std::make_shared<tcp::WindowsClient>();
#else
    return std::make_shared<tcp::UnixClient>();
#endif /* _WIN32 || _WIN64 */
}

} // namespace tcp
