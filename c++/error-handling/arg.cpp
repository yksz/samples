#include <cstdio>
#include <memory>
#include <stdexcept>

using error = std::exception;
using error_ptr = std::unique_ptr<error>;
using runtime_error_ptr = std::unique_ptr<std::runtime_error>;

static int calc(int x, int y, error_ptr& err) {
    err = runtime_error_ptr(new std::runtime_error("calc error"));
    return 0;
}

int main(void) {
    error_ptr err;
    int result = calc(10, 20, err);
    if (err != nullptr) {
        printf("%s\n", err->what());
    } else {
        printf("No error\n");
    }
    return 0;
}
