#include "ShamirKeygen.h"
#include "../MathCrypto/CryptoUtils.h"
#include <random>

int64_t GenerateRandomShamirNumber(int64_t minValue, int64_t maxValue) {
    random_device hardwareRandomDevice;
    mt19937_64 randomEngine(hardwareRandomDevice());
    uniform_int_distribution<int64_t> uniformDistribution(minValue, maxValue);
    return uniformDistribution(randomEngine);
}

int64_t GenerateRandomShamirPrime(int64_t minValue, int64_t maxValue) {
    if (minValue > maxValue) {
        throw invalid_argument("минимальное значение больше максимального");
    }
    int64_t primeValue = -1;
    bool IsFound = false;
    for (int64_t value = minValue; value <= maxValue; value++) {
        if (IsPrime(value)) {
            IsFound = true;
        }
    }
    if (!IsFound) {
        throw runtime_error("в диапазоне нет простых чисел");
    }
    while (!IsPrime(primeValue)) {
        primeValue = GenerateRandomShamirNumber(minValue, maxValue);
    }
    return primeValue;
}

int64_t GenerateRandomShamirSecretKey(int64_t primeValue) {
    if (primeValue <= 255) {
        throw invalid_argument("p должно быть больше 255 для шифрования байтов");
    }
    int64_t secretKey = -1;
    while (!IsShamirSecretKeyValid(secretKey, primeValue)) {
        secretKey = GenerateRandomShamirNumber(2, primeValue - 2);
    }
    return secretKey;
}

ShamirKey GenerateRandomShamirKey(int64_t minPrimeValue, int64_t maxPrimeValue) {
    try {
        if (maxPrimeValue <= 255) {
            throw invalid_argument("верхняя граница должна быть больше 255");
        }
        if (minPrimeValue <= 255) {
            minPrimeValue = 256;
        }
        int64_t primeValue = GenerateRandomShamirPrime(minPrimeValue, maxPrimeValue);
        int64_t caValue = GenerateRandomShamirSecretKey(primeValue);
        int64_t cbValue = GenerateRandomShamirSecretKey(primeValue);
        return GenerateShamirKey(primeValue, caValue, cbValue);
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при случайной генерации ключа Шамира: ") + exceptionCaught.what());
    }
}
