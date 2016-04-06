#include <cstdio>
#include <memory>
#include <stdexcept>

using error = std::exception;
using error_ptr = std::unique_ptr<error>;
using runtime_error_ptr = std::unique_ptr<std::runtime_error>;

static runtime_error_ptr calc(int x, int y, int& result) {
    return runtime_error_ptr(new std::runtime_error("calc error"));
}

int main(void) {
    int result;
    error_ptr err = calc(10, 20, result);
    if (err != nullptr) {
        printf("%s\n", err->what());
    } else {
        printf("No error\n");
    }
    return 0;
}
