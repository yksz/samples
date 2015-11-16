#ifndef FACTORY_H
#define FACTORY_H

#include <memory>
#include "server.h"

namespace tcp {

class Factory final {
public:
    static Factory& GetInstance();
    std::shared_ptr<Server> createServer();

private:
    Factory();
    ~Factory();
    Factory(const Factory&);
    void operator=(const Factory&);
};

} // namespace tcp

#endif /* FACTORY_H */
