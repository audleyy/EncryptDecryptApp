#ifndef CRYPTO_MATH_UTILS_H
#define CRYPTO_MATH_UTILS_H

#include <cstdint>
#include <stdexcept>
#include <random>

using namespace std;

uint64_t modBinary(uint64_t base, uint64_t power, uint64_t modulo);
bool IsPrime(uint64_t x);
uint64_t calculateReverseElement(uint64_t base, uint64_t module);
uint64_t GenerateRandomUint64(uint64_t minValue, uint64_t maxValue);
uint64_t GenerateRandomPrimeInRange(uint64_t minValue, uint64_t maxValue);

#endif
