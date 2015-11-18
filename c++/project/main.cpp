#include <stdio.h>
#include "myproject/myproject.h"

#define LEN(array) (sizeof(array) / sizeof(array[0]))

namespace mymath = myproject::newmath;

int main(void) {
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    printf("sum 1-9 = %d\n", mymath::Sum(array, LEN(array)));
    printf("average 1-9 = %f\n", mymath::Average(array, LEN(array)));
    return 0;
}
