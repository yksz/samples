#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include "client.h"

namespace tcp {

class Factory final {
public:
    static Factory& GetInstance();
    std::shared_ptr<Client> createClient();

private:
    Factory();
    ~Factory();
    Factory(const Factory&);
    void operator=(const Factory&);
};

} // namespace tcp

#endif /* FACTORY_H */
