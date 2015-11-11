#include <stdio.h>
#include "endian.h"

int main()
{
    if (is_little_endian()) {
        printf("Little-endian\n");
    } else {
        printf("Big-endian\n");
    }

    printf("byte_swap_16(%d) = %d\n", 1, byte_swap_16(1));
    printf("byte_swap_32(%d) = %d\n", 1, byte_swap_32(1));
    printf("byte_swap_64(%d) = %ld\n", 1, byte_swap_64(1));
    return 0;
}
