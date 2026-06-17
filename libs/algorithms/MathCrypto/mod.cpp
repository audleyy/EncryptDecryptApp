#include "CryptoUtils.h"


int64_t modBinary(int64_t base, int64_t power, int64_t modulo){
    if (modulo == 0){
        throw runtime_error("Модуль не может быть равен нулю");
    }
    if (power < 0){
        throw runtime_error("Степень не может быть отрицательной");
    }
    int64_t result = 1;
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