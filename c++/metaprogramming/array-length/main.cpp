#include <iostream>

template<typename T, size_t S>
size_t len(const T (&array)[S]) {
    return S;
}

int main() {
    int array1[10];
    int* array2 = new int[20];
    std::cout << len(array1) << std::endl;
//    std::cout << len(array2) << std::endl; // error
}
