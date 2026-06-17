#include "ElGamalKeygen.h"
#include "../DiffieHellman/DiffieHellman.hpp"
#include "../MathCrypto/CryptoUtils.h"

int64_t GenerateRandomElGamalPrime(int64_t minValue, int64_t maxValue) {
    if (minValue > maxValue) {
        throw invalid_argument("минимальное значение больше максимального");
    }

    bool isFound = false;

    for (int64_t value = minValue; value <= maxValue; value++) {
        if (IsPrime(value)) {
            isFound = true;
        }
    }

    if (!isFound) {
        throw runtime_error("в диапазоне нет простых чисел");
    }

    int64_t primeModulus = -1;

    while (!IsPrime(primeModulus)) {
        primeModulus = GeneratePrivateKey(minValue, maxValue);
    }

    return primeModulus;
}

int64_t GenerateRandomElGamalGenerator(int64_t primeModulus) {
    return GeneratePrivateKey(2, primeModulus - 2);
}

ElGamalKey GenerateElGamalKey(int64_t primeModulus, int64_t generatorValue, int64_t privateKey) {
    try {
        if (!IsPrime(primeModulus)) {
            throw invalid_argument("p должно быть простым числом");
        }

        if (primeModulus <= 255) {
            throw invalid_argument("p должно быть больше 255 для шифрования байтов");
        }

        if (generatorValue <= 1 || generatorValue >= primeModulus) {
            throw invalid_argument("g должно быть больше 1 и меньше p");
        }

        if (privateKey <= 1 || privateKey >= primeModulus - 1) {
            throw invalid_argument("секретный ключ должен быть больше 1 и меньше p - 1");
        }

        ElGamalKey key;
        key.primeModulus = primeModulus;
        key.generatorValue = generatorValue;
        key.privateKey = privateKey;
        key.publicKey = GeneratePublicKey(generatorValue, privateKey, primeModulus);

        return key;
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при генерации ключа Эль-Гамаля: ") + exceptionCaught.what());
    }
}

ElGamalKey GenerateRandomElGamalKey() {
    int64_t primeModulus = GenerateRandomElGamalPrime(257, 997);
    int64_t generatorValue = GenerateRandomElGamalGenerator(primeModulus);
    int64_t privateKey = GeneratePrivateKey(2, primeModulus - 2);

    return GenerateElGamalKey(primeModulus, generatorValue, privateKey);
}
