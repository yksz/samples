#ifndef FACTORY_H
#define FACTORY_H

#include "server.h"

namespace tcp {

class Factory final {
public:
    static Factory& GetInstance();
    Server* createServer();

private:
    Factory();
    ~Factory();
    Factory(const Factory&);
    void operator=(const Factory&);
};

} // namespace tcp

#endif /* FACTORY_H */
