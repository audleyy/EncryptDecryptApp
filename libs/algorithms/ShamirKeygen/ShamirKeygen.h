#ifndef SHAMIR_KEYGEN_H
#define SHAMIR_KEYGEN_H

#include <cstdint>
#include <stdexcept>
#include <string>

using namespace std;

struct ShamirKey {
    uint64_t primeValue;
    uint64_t caValue;
    uint64_t cbValue;
    uint64_t daValue;
    uint64_t dbValue;
};

bool IsShamirSecretKeyValid(uint64_t secretKey, uint64_t primeValue);
uint64_t CalculateShamirReverseKey(uint64_t secretKey, uint64_t primeValue);
ShamirKey GenerateShamirKey(uint64_t primeValue, uint64_t caValue, uint64_t cbValue);
uint64_t GenerateRandomShamirSecretKey(uint64_t primeValue);
ShamirKey GenerateRandomShamirKey(uint64_t minPrimeValue, uint64_t maxPrimeValue);

#endif
