#include <functional>
#include <iostream>
#include "object.h"

static void func(const Object& o) {
    std::cout << "func(const &)" << std::endl;
}

static std::function<void()> func_lambda(const Object& o) {
    std::cout << "begin: func_lambda(const &)" << std::endl;
    std::function<void()> lambda = [o]() {
        std::cout << "lambda" << std::endl;
        func(o);
    };
    std::cout << "end  : func_lambda(const &)" << std::endl;
    return lambda;
}

static std::function<void()> func_lambda(Object&& o) {
    std::cout << "begin: func_lambda(&&)" << std::endl;
    std::function<void()> lambda = [o]() {
        std::cout << "lambda" << std::endl;
        func(o);
    };
    std::cout << "end  : func_lambda(&&)" << std::endl;
    return lambda;
}

static std::function<void()> func_struct(const Object& o) {
    std::cout << "begin: func_struct(const &)" << std::endl;
    struct Func {
        Object o;
        void operator()() const {
            std::cout << "Func" << std::endl;
            func(o);
        }
    };
    std::cout << "end  : func_struct(const &)" << std::endl;
    return Func{ std::move(o) };
}

static std::function<void()> func_struct(Object&& o) {
    std::cout << "begin: func_struct(&&)" << std::endl;
    struct Func {
        Object o;
        void operator()() const {
            std::cout << "Func" << std::endl;
            func(o);
        }
    };
    std::cout << "end  : func_struct(&&)" << std::endl;
    return Func{ std::move(o) };
}

int main(void) {
    {
        std::cout << std::endl;
        Object o;
        func_lambda(o)();
    }
    {
        std::cout << std::endl;
        Object o;
        func_lambda(std::move(o))();
    }
    {
        std::cout << std::endl;
        Object o;
        func_struct(o)();
    }
    {
        std::cout << std::endl;
        Object o;
        func_struct(std::move(o))();
    }
    return 0;
}
