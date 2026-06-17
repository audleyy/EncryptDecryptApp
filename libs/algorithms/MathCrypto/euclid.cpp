#include "CryptoUtils.h"


uint64_t calculateReverseElement(uint64_t base, uint64_t module){
    int64_t r0 = module;
    int64_t r1 = base;
    int64_t u0 = 0;
    int64_t u1 = 1;
    while (r1 != 0){
        int64_t q = r0 / r1;
        int64_t nr = r0 - q * r1;
        int64_t nu = u0 - q * u1;
        r0 = r1;
        r1 = nr;
        u0 = u1;
        u1 = nu;
    }
    if (r0 != 1){
        throw runtime_error("Обратного элемента не существует");
    }
    while (u0 < 0) {
        u0 += module;
    }
    return u0;
}
