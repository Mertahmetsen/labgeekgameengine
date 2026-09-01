#ifndef MERAHM_BITWISE
#define MERAHM_BITWISE
#include <stdint.h>
#include <stddef.h>

uint64_t bitmask (int bits);
uint64_t getValue (uint64_t packed, int offset, int bits);
uint64_t pack64 (const uint64_t* values, const uint8_t* bits, size_t count, uint8_t* offests);

#endif