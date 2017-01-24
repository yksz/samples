#include <cstdlib>
#include <iostream>
#include <boost/exception/all.hpp>

namespace {

class my_error : public boost::exception, public std::exception {};

} // namespace

static void doSomething() {
    BOOST_THROW_EXCEPTION(my_error());
}

int main(void) {
    try {
        doSomething();
        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        std::cerr << "exception caught: " << e.what() << std::endl;
        std::cerr << boost::diagnostic_information(e);
        return EXIT_FAILURE;
    } catch (...) {
        return EXIT_FAILURE;
    }
}
