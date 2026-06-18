#ifndef EL_GAMAL_KEYGEN_H
#define EL_GAMAL_KEYGEN_H

#include "../DiffieHellman/DiffieHellman.h"
#include "../MathCrypto/CryptoUtils.h"
#include <cstdint>
#include <stdexcept>
#include <string>

using namespace std;

struct ElGamalKey {
    uint64_t primeModulus;
    uint64_t generatorValue;
    uint64_t privateKey;
    uint64_t publicKey;
};

ElGamalKey GenerateElGamalKey(uint64_t primeModulus, uint64_t generatorValue, uint64_t privateKey);
ElGamalKey GenerateRandomElGamalKey();

#endif
