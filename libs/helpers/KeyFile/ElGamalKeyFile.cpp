#include "KeyFile.h"
#include "../ConvertUtils.h"
#include <fstream>
#include <vector>

void SaveElGamalKeyToFile(const string& filePath, const ElGamalKey& key) {
    vector<int64_t> keyNumbers = {
        key.primeModulus,
        key.generatorValue,
        key.privateKey,
        key.publicKey,
    };

    vector<uint8_t> keyBytes = NumbersToBinary(keyNumbers);
    ofstream file(filePath, ios::binary);

    if (!file) {
        throw runtime_error("Не удалось открыть файл для записи ключа Эль-Гамаля");
    }

    for (uint8_t byte : keyBytes) {
        file.put(byte);
    }
}

ElGamalKey ReadElGamalKeyFromFile(const string& filePath) {
    ifstream file(filePath, ios::binary);

    if (!file) {
        throw runtime_error("Не удалось открыть файл для чтения ключа Эль-Гамаля");
    }

    vector<uint8_t> keyBytes;
    char symbol {};

    while (file.get(symbol)) {
        keyBytes.push_back(symbol);
    }

    vector<int64_t> keyNumbers = BinaryToNumbers(keyBytes);

    if (keyNumbers.size() != 4) {
        throw runtime_error("Некорректный размер файла ключа Эль-Гамаля");
    }

    ElGamalKey key;
    key.primeModulus = keyNumbers[0];
    key.generatorValue = keyNumbers[1];
    key.privateKey = keyNumbers[2];
    key.publicKey = keyNumbers[3];

    return key;
}
