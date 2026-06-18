#pragma once

#include "../ChaCha20/ChaCha20Types.h"
#include <random>

using namespace std;

struct ChaCha20Key {
    ByteVec key;
    ByteVec nonce;
    uint32_t counter;
};

ChaCha20Key GenerateRandomChaCha20Key();
