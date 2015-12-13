#ifndef TCP_FACTORY_H
#define TCP_FACTORY_H

#include <memory>
#include "client.h"

namespace tcp {

class Factory final {
public:
    static Factory& GetInstance();
    std::shared_ptr<Client> createClient();

private:
    Factory() = default;
    ~Factory() = default;
    Factory(const Factory&) = delete;
    void operator=(const Factory&) = delete;
};

} // namespace tcp

#endif // TCP_FACTORY_H
