#pragma once

#include <cstdint>
#include <vector>

const uint64_t CaesarAlphabetSize = 256;

struct CaesarKey {
    uint64_t shift;
};
