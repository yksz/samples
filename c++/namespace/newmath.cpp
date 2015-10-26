#include "newmath.h"

namespace myproject {

int Sum(int* array, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += array[i];
    }
    return sum;
}

double Average(int* array, int len) {
    int val = Sum(array, len);
    return (double) val / len;
}

} // namespace myproject
