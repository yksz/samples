#include <cstdio>
#include <memory>
#include <tuple>

using error = std::exception;
using p_error = std::unique_ptr<error>;
using p_runtime_error = std::unique_ptr<std::runtime_error>;

static std::tuple<int, p_runtime_error> calc(int x) {
    auto err = p_runtime_error(new std::runtime_error("calc error"));
    return std::make_tuple(0, std::move(err));
}

int main(void) {
    int x;
    p_error err;
    std::tie(x, err) = calc(100);
    if (err != nullptr) {
        printf("%s\n", err->what());
    } else {
        printf("No error\n");
    }
    return 0;
}
