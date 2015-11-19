#include <cstdio>
#include "array.h"

int main(void) {
    const int size = 10;

    Array<int> array(size);
    for (int i = 0; i < size; i++) {
        array.Set(i, i + 1);
    }
    for (int i = 0; i < size; i++) {
        printf("index %d: %d\n", i, array[i]);
    }
    return 0;
}
