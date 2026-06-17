#include "RsaKeygen.h"
#include "../MathCrypto/CryptoUtils.h"
#include <random>

int64_t GenerateRandomNumber(int64_t minValue, int64_t maxValue) {
    random_device hardwareRandomDevice;
    mt19937_64 randomEngine(hardwareRandomDevice());
    uniform_int_distribution<int64_t> uniformDistribution(minValue, maxValue);
    return uniformDistribution(randomEngine);
}

int64_t GenerateRandomPrime(int64_t minValue, int64_t maxValue) {
    if (minValue > maxValue) {
        throw invalid_argument("минимальное значение больше максимального");
    }
    int64_t primeValue = -1;
    bool isFound = false;
    for (int64_t value = minValue; value <= maxValue; value++) {
        if (IsPrime(value)) {
            isFound = true;
        }
    }
    if (!isFound) {
        throw runtime_error("в диапазоне нет простых чисел");
    }
    while (!IsPrime(primeValue)) {
        primeValue = GenerateRandomNumber(minValue, maxValue);
    }
    return primeValue;
}

int64_t GenerateRandomRsaPrivateKey(int64_t phiValue) {
    if (phiValue <= 3) {
        throw invalid_argument("phi слишком маленькое для генерации ключа");
    }
    int64_t privateKey = -1;
    while (!IsRsaPrivateKeyValid(privateKey, phiValue)) {
        privateKey = GenerateRandomNumber(2, phiValue - 1);
    }
    return privateKey;
}

RsaKey GenerateRandomRsaKey(int64_t minPrimeValue, int64_t maxPrimeValue) {
    try {
        int64_t pValue = GenerateRandomPrime(minPrimeValue, maxPrimeValue);
        int64_t qValue = GenerateRandomPrime(minPrimeValue, maxPrimeValue);
        while (qValue == pValue) {
            qValue = GenerateRandomPrime(minPrimeValue, maxPrimeValue);
        }
        int64_t phiValue = CalculateRsaPhi(pValue, qValue);
        int64_t privateKey = GenerateRandomRsaPrivateKey(phiValue);
        return GenerateRsaKey(pValue, qValue, privateKey);
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при случайной генерации ключа RSA: ") + exceptionCaught.what());
    }
}
