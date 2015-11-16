#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace {

void doSomething() {
    throw std::logic_error("doSomething");
}

} // unnamed namespace

int main(void) {
    try {
        doSomething();
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "exception caught: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        return EXIT_FAILURE;
    }
}
