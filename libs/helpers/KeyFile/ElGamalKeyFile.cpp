#include "KeyFile.h"
#include <vector>

void SaveElGamalKeyToFile(const string& filePath, const ElGamalKey& key) {
    vector<uint64_t> keyNumbers = {
        ElGamalAlgorithmId,
        key.primeModulus,
        key.generatorValue,
        key.privateKey,
        key.publicKey,
    };

    SaveKeyNumbersToFile(filePath, keyNumbers);
}

ElGamalKey ReadElGamalKeyFromFile(const string& filePath) {
    vector<uint64_t> keyNumbers = ReadKeyNumbersFromFile(filePath);

    if (keyNumbers.size() != 5 || keyNumbers[0] != ElGamalAlgorithmId) {
        throw runtime_error("Ошибка ключа: файл не является ключом Эль-Гамаля");
    }

    ElGamalKey key;
    key.primeModulus = keyNumbers[1];
    key.generatorValue = keyNumbers[2];
    key.privateKey = keyNumbers[3];
    key.publicKey = keyNumbers[4];

    return key;
}
