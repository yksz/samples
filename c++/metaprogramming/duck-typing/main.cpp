#include <iostream>

template<class T>
void test(const T& t) {
    std::cout << t.sound() << std::endl;
}

struct Duck {
    const char* sound() const {
        return "quack";
    }
};

struct Cat {
    const char* sound() const {
        return "myaa";
    }
};

int main() {
    test(Duck());
    test(Cat());
}
