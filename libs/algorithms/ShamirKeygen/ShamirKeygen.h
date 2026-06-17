#ifndef SHAMIR_KEYGEN_H
#define SHAMIR_KEYGEN_H

#include <cstdint>
#include <stdexcept>
#include <string>

using namespace std;

struct ShamirKey {
    int64_t primeValue;
    int64_t caValue;
    int64_t cbValue;
    int64_t daValue;
    int64_t dbValue;
};

bool IsShamirSecretKeyValid(int64_t secretKey, int64_t primeValue);
int64_t CalculateShamirReverseKey(int64_t secretKey, int64_t primeValue);
ShamirKey GenerateShamirKey(int64_t primeValue, int64_t caValue, int64_t cbValue);
int64_t GenerateRandomShamirPrime(int64_t minValue, int64_t maxValue);
int64_t GenerateRandomShamirSecretKey(int64_t primeValue);
ShamirKey GenerateRandomShamirKey(int64_t minPrimeValue, int64_t maxPrimeValue);

#endif
