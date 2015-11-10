#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static bool isSystemLittleEndian(void)
{
#if defined(__LITTLE_ENDIAN__)
    printf("defined __LITTLE_ENDIAN__\n");
    return true;
#elif defined(__BIG_ENDIAN__)
    printf("defined __BIG_ENDIAN__\n");
    return false;
#else
    int32_t i = 1;
    return *(int8_t*)&i == 1;
#endif
}

int main()
{
    if (isSystemLittleEndian()) {
        printf("Little-endian\n");
    } else {
        printf("Big-endian\n");
    }
    return 0;
}
