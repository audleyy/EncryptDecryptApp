#include "RsaKeygen.h"

uint64_t GenerateRandomRsaPrivateKey(uint64_t phiValue) {
    if (phiValue <= 3) {
        throw invalid_argument("phi слишком маленькое для генерации ключа");
    }
    uint64_t privateKey = 0;
    while (!IsRsaPrivateKeyValid(privateKey, phiValue)) {
        privateKey = GenerateRandomUint64(2, phiValue - 1);
    }
    return privateKey;
}

RsaKey GenerateRandomRsaKey(uint64_t minPrimeValue, uint64_t maxPrimeValue) {
    try {
        uint64_t pValue = GenerateRandomPrimeInRange(minPrimeValue, maxPrimeValue);
        uint64_t qValue = GenerateRandomPrimeInRange(minPrimeValue, maxPrimeValue);
        while (qValue == pValue) {
            qValue = GenerateRandomPrimeInRange(minPrimeValue, maxPrimeValue);
        }
        uint64_t phiValue = CalculateRsaPhi(pValue, qValue);
        uint64_t privateKey = GenerateRandomRsaPrivateKey(phiValue);
        return GenerateRsaKey(pValue, qValue, privateKey);
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при случайной генерации ключа RSA: ") + exceptionCaught.what());
    }
}
