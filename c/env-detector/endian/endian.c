#include "endian.h"

bool is_little_endian(void)
{
#if defined(__LITTLE_ENDIAN__)
    printf("defined __LITTLE_ENDIAN__\n");
    return true;
#elif defined(__BIG_ENDIAN__)
    printf("defined __BIG_ENDIAN__\n");
    return false;
#else
    uint16_t i = 1;
    return *(uint8_t*)&i == 1;
#endif
}

uint16_t byte_swap_16(uint16_t x)
{
    return ((x & 0x00ffU) << 8) |
           ((x & 0xff00U) >> 8);
}

uint32_t byte_swap_32(uint32_t x)
{
    return ((x & 0x000000ffUL) << 24) |
           ((x & 0x0000ff00UL) <<  8) |
           ((x & 0x00ff0000UL) >>  8) |
           ((x & 0xff000000UL) >> 24);
}

uint64_t byte_swap_64(uint64_t x)
{
    return ((x & 0x00000000000000ffULL) << 56) |
           ((x & 0x000000000000ff00ULL) << 40) |
           ((x & 0x0000000000ff0000ULL) << 24) |
           ((x & 0x00000000ff000000ULL) <<  8) |
           ((x & 0x000000ff00000000ULL) >>  8) |
           ((x & 0x0000ff0000000000ULL) >> 24) |
           ((x & 0x00ff000000000000ULL) >> 40) |
           ((x & 0xff00000000000000ULL) >> 56);
}
