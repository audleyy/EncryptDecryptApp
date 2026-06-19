#ifndef CAESAR_TYPES_H
#define CAESAR_TYPES_H

#include <cstdint>
#include <vector>

const uint64_t CaesarAlphabetSize = 256;

struct CaesarKey {
    uint64_t shift;
};

#endif // 