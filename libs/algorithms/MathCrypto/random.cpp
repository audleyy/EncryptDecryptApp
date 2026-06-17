#include "CryptoUtils.h"
#include <random>

uint64_t GenerateRandomUint64(uint64_t minValue, uint64_t maxValue) {
    if (minValue > maxValue) {
        throw invalid_argument("минимальное значение больше максимального");
    }
    random_device hardwareRandomDevice;
    mt19937_64 randomEngine(hardwareRandomDevice());
    uniform_int_distribution<uint64_t> uniformDistribution(minValue, maxValue);
    return uniformDistribution(randomEngine);
}

uint64_t GenerateRandomPrimeInRange(uint64_t minValue, uint64_t maxValue) {
    if (minValue > maxValue) {
        throw invalid_argument("минимальное значение больше максимального");
    }
    bool isFound = false;
    for (uint64_t value = minValue; value <= maxValue; value++) {
        if (IsPrime(value)) {
            isFound = true;
        }
    }
    if (!isFound) {
        throw runtime_error("в диапазоне нет простых чисел");
    }
    uint64_t primeValue = 0;
    while (!IsPrime(primeValue)) {
        primeValue = GenerateRandomUint64(minValue, maxValue);
    }
    return primeValue;
}
