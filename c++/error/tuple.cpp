#include <cstdio>
#include <memory>
#include <tuple>

using error = std::exception;
using error_ptr = std::unique_ptr<error>;
using runtime_error_ptr = std::unique_ptr<std::runtime_error>;

static std::tuple<int, runtime_error_ptr> calc(int x, int y) {
    auto err = runtime_error_ptr(new std::runtime_error("calc error"));
    return std::make_tuple(0, std::move(err));
}

int main(void) {
    int result;
    error_ptr err;
    std::tie(result, err) = calc(10, 20);
    if (err != nullptr) {
        printf("%s\n", err->what());
    } else {
        printf("No error\n");
    }
    return 0;
}
