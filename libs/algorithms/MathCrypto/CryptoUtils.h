#ifndef CRYPTO_MATH_UTILS_H
#define CRYPTO_MATH_UTILS_H

#include <cstdint>
#include <stdexcept>
using namespace std;

int64_t modBinary(int64_t base, int64_t power, int64_t modulo);
bool IsPrime(int64_t x);
int64_t calculateReverseElement(int64_t base, int64_t module);

#endif
