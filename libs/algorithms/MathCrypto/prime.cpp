#include "CryptoUtils.h"

bool IsPrime(int64_t x) {
    bool is_prime_value = true;
    if (x < 2) {
        is_prime_value = false;
    } else {
        for (int64_t i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                is_prime_value = false;
            }
        }
    }
    return is_prime_value;
}