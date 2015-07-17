#include <iostream>
#include "newmath.h"

#define LEN(array) (sizeof(array) / sizeof(array[0]))

int main(void) {
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::cout << "sum 1-9 = " << sum(array, LEN(array)) << std::endl;
    return 0;
}
