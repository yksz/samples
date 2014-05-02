#include <stdio.h>

int main()
{
#ifdef _WIN32
    printf("Windows(32-bit or 64-bit)\n");
#elif __APPLE__ && __MACH__
    printf("Mac OS X\n");
#elif __linux
    printf("Linux\n");
#elif __unix
    printf("UNIX\n");
#else
    printf("Unknown OS\n");
#endif
}
