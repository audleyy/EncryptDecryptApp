#ifndef EL_GAMAL_KEYGEN_H
#define EL_GAMAL_KEYGEN_H

#include <cstdint>
#include <stdexcept>
#include <string>

using namespace std;

struct ElGamalKey {
    int64_t primeModulus;
    int64_t generatorValue;
    int64_t privateKey;
    int64_t publicKey;
};

ElGamalKey GenerateElGamalKey(int64_t primeModulus, int64_t generatorValue, int64_t privateKey);
ElGamalKey GenerateRandomElGamalKey();

#endif
