#include "newmath.h"

namespace myproject {

int sum(int* array, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += array[i];
    }
    return sum;
}

double average(int* array, int len) {
    int val = sum(array, len);
    return (double) val / len;
}

}
