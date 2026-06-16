#pragma once

#include "ChaCha20Types.h"

inline uint32_t rotl32(uint32_t x, uint32_t n) {
    return (x << n) | (x >> (32u - n));
}

inline uint32_t load32LE(const uint8_t* src) {
    return  (uint32_t)src[0]        |
           ((uint32_t)src[1] <<  8) |
           ((uint32_t)src[2] << 16) |
           ((uint32_t)src[3] << 24);
}

inline void store32LE(uint8_t* dst, uint32_t x) {
    dst[0] = (uint8_t)(x >>  0);
    dst[1] = (uint8_t)(x >>  8);
    dst[2] = (uint8_t)(x >> 16);
    dst[3] = (uint8_t)(x >> 24);
}

void quarterRound(
    uint32_t& a,
    uint32_t& b,
    uint32_t& c,
    uint32_t& d
);