#pragma once

#include <iostream>

class Object {
public:
    Object() {
        std::cout << "Object: constructor" << std::endl;
    }

    ~Object() {
        std::cout << "Object: destructor" << std::endl;
    }

    Object(const Object&) {
        std::cout << "Object: copy constructor" << std::endl;
    }

    Object& operator=(const Object&) {
        std::cout << "Object: copy assignment" << std::endl;
        return *this;
    }

    Object(Object&& other) {
        std::cout << "Object: move constructor" << std::endl;
    }

    Object& operator=(Object&&) {
        std::cout << "Object: move assignment" << std::endl;
        return *this;
    }
};
