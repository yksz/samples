#include <stdbool.h>
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
    int i = 1;
    return *(char*)&i == 1;
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
