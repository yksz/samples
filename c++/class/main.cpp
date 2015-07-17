#include <cstdio>
#include "int_array.h"

int main(void) {
    int size = 10;
    IntArray array(size);
    for (int i = 0; i < size; i++) {
        array.set(i, i + 1);
    }
    for (int i = 0; i < size; i++) {
        printf("index %d: %d\n", i, array.get(i));
    }
    return 0;
}
