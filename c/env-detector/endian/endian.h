#ifndef ENDIAN_H
#define ENDIAN_H

#include <stdbool.h>
#include <stdint.h>

bool is_little_endian(void);

uint16_t byte_swap_16(uint16_t x);
uint32_t byte_swap_32(uint32_t x);
uint64_t byte_swap_64(uint64_t x);

#endif /* ENDIAN_H */
