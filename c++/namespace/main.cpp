#include <stdio.h>
#include "myproject.h"

#define LEN(array) (sizeof(array) / sizeof(array[0]))

int main(void) {
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    printf("average 1-9 = %f\n", myproject::average(array, LEN(array)));
    return 0;
}
