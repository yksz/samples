#include <cstdlib>
#include <iostream>
#include <stdexcept>

static void doSomething() {
    throw std::logic_error("doSomething");
}

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
