#include <iostream>
#include "object.h"

static void func(const Object& o) {
    std::cout << "\nfunc(const &)" << std::endl;
}

static void func(Object&& o) {
    std::cout << "\nfunc(&&)" << std::endl;
}

static Object func() {
    std::cout << "\nfunc()" << std::endl;

    Object o;
    return o;
}

static Object func_optimize() {
    std::cout << "\nfunc_optimize()" << std::endl;

    return Object();
}

static Object func_move() {
    std::cout << "\nfunc_move()" << std::endl;

    Object o;
    return std::move(o);
}

int main(void) {
    Object o;
    func(o);
    func(std::move(o));
    func();
    func_optimize();
    func_move();
    std::cout << std::endl;
    return 0;
}
