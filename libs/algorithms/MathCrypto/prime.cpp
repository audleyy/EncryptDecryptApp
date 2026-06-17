#include "CryptoUtils.h"

bool IsPrime(uint64_t x) {
    bool IsPrimeValue = true;
    if (x < 2) {
        IsPrimeValue = false;
    } else {
        for (uint64_t i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                IsPrimeValue = false;
            }
        }
    }
    return IsPrimeValue;
}