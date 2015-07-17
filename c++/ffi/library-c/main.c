#include <stdio.h>
#include "newmath.h"

#define LEN(array) (sizeof(array) / sizeof(array[0]))

int main(void) {
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    printf("sum 1-9 = %d\n", sum(array, LEN(array)));
    return 0;
}
