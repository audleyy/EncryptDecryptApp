#include "ElGamalKeygen.h"
#include "../DiffieHellman/DiffieHellman.hpp"
#include "../MathCrypto/CryptoUtils.h"

uint64_t GenerateRandomElGamalGenerator(uint64_t primeModulus) {
    return GenerateRandomUint64(2, primeModulus - 2);
}

ElGamalKey GenerateElGamalKey(uint64_t primeModulus, uint64_t generatorValue, uint64_t privateKey) {
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
    uint64_t primeModulus = GenerateRandomPrimeInRange(257, 997);
    uint64_t generatorValue = GenerateRandomElGamalGenerator(primeModulus);
    uint64_t privateKey = GenerateRandomUint64(2, primeModulus - 2);

    return GenerateElGamalKey(primeModulus, generatorValue, privateKey);
}
