#pragma once
#include "../ChaCha20/ChaCha20Types.h"
#include "../DiffieHellman/DiffieHellman.h"
#include <cstdint>

struct ChaCha20Key {
    std::vector<uint8_t> key;
    std::vector<uint8_t> nonce;
    uint32_t counter;
};

struct DhChaCha20Params {
    uint64_t primeModulus;
    uint64_t generator;
    uint64_t privateKeyA;
    uint64_t privateKeyB;
};

ChaCha20Key GenerateRandomChaCha20Key();
ChaCha20Key GenerateChaCha20KeyFromDH(const DhChaCha20Params& params);
