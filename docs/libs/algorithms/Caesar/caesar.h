#pragma once

#include <cstdint>
#include <string>
#include <vector>

constexpr int CAESAR_ALPHABET_SIZE = 256;

struct CaesarKey {
    int shift;
};