#include <stdio.h>

int main(void)
{
#if defined(_WIN32) || defined(_WIN64)
    printf("Windows(32-bit or 64-bit)\n");
#elif defined(__APPLE__) && defined(__MACH__)
    printf("Mac OS X\n");
#elif __linux
    printf("Linux\n");
#elif __unix
    printf("UNIX\n");
#else
    printf("Unknown OS\n");
#endif
    return 0;
}
