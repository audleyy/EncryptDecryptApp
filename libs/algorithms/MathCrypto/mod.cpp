#include "CryptoUtils.h"

uint64_t modBinary(uint64_t base, uint64_t power, uint64_t modulo){
    if (modulo == 0){
        throw runtime_error("Модуль не может быть равен нулю");
    }
    uint64_t result = 1;
    base %= modulo;
    while (power > 0){
        if (power % 2 == 1){
            result = (result * base) % modulo;
        }
        base = (base * base) % modulo;
        power /= 2;
    }
    return result;
}
