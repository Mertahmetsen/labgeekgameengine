#include "bitwise.h"

uint64_t bitmask (int bits) {
    if (bits >= 64) return UINT64_MAX;
    if (bits <= 0) return 0;
    return (1ULL << bits) - 1;
}

uint64_t getValue(uint64_t packed, int offset, int bits)
{
    return (packed >> offset) & bitmask(bits);
}

uint64_t pack64 (const uint64_t* values, const uint8_t* bits, size_t count, uint8_t* offsets) {
    uint64_t result = 0;
    uint8_t shift = 0;
    for (size_t i = 0; i < count; ++i) {
        offsets[i] = shift;
        result |= (values[i] & bitmask(bits[i])) << shift;
        shift += bits[i];
    }
    return result;
}