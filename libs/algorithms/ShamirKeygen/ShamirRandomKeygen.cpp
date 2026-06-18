#include "ShamirKeygen.h"

uint64_t GenerateRandomShamirSecretKey(uint64_t primeValue) {
    if (primeValue <= 255) {
        throw invalid_argument("p должно быть больше 255 для шифрования байтов");
    }
    uint64_t secretKey = 0;
    while (!IsShamirSecretKeyValid(secretKey, primeValue)) {
        secretKey = GenerateRandomUint64(2, primeValue - 2);
    }
    return secretKey;
}

ShamirKey GenerateRandomShamirKey(uint64_t minPrimeValue, uint64_t maxPrimeValue) {
    try {
        if (maxPrimeValue <= 255) {
            throw invalid_argument("верхняя граница должна быть больше 255");
        }
        if (minPrimeValue <= 255) {
            minPrimeValue = 256;
        }
        uint64_t primeValue = GenerateRandomPrimeInRange(minPrimeValue, maxPrimeValue);
        uint64_t caValue = GenerateRandomShamirSecretKey(primeValue);
        uint64_t cbValue = GenerateRandomShamirSecretKey(primeValue);
        return GenerateShamirKey(primeValue, caValue, cbValue);
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при случайной генерации ключа Шамира: ") + exceptionCaught.what());
    }
}
