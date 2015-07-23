#include <cstdio>
#include <cstdlib>
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
        printf("exception caught: %s\n", e.what());
        return EXIT_FAILURE;
    } catch (...) {
        return EXIT_FAILURE;
    }
}
